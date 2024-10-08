/* socket_server.c
Classic Ladder 2 Project
Forked from Classic Ladder by Marc LE DOUARAIN
Copyright Marc LE DOUARAIN for Classic Ladder
Copyright Benoit BOUCHEZ for Classic Ladder 2 specific changes
https://github.com/bbouchez/classicladder2
*/

/* -------------------------------------- */
/* Socket server used for modbus protocol */
/* -------------------------------------- */

/* This library is free software; you can redistribute it and/or */
/* modify it under the terms of the GNU Lesser General Public */
/* License as published by the Free Software Foundation; either */
/* version 2.1 of the License, or (at your option) any later version. */

/* This library is distributed in the hope that it will be useful, */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU */
/* Lesser General Public License for more details. */

/* You should have received a copy of the GNU Lesser General Public */
/* License along with this library; if not, write to the Free Software */
/* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __WIN32__
#include <winsock2.h>
#include <windows.h>
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#endif
#include <errno.h>

#include "classicladder2.h"
#include "global.h"
#include "protocol_modbus_defines.h"
#include "protocol_modbus_slave.h"
#include "socket_server.h"
//////#include "protocol_modbus_master.h" // some Modbus defines shared
#include "frames_log_buffers.h"


#ifdef __WIN32__
#define SOCK_FD SOCKET
#define SOCK_INVALID SOCKET_ERROR
HANDLE ThreadHandle = NULL;
DWORD ThreadId;
#else
#define SOCK_FD unsigned int
#define SOCK_INVALID -1
pthread_t thread_socket_server;
#endif

#define BUF_SIZE 512
SOCK_FD server_s;             // Server socket descriptor
struct sockaddr_in server_addr;          // Server Internet address

int SocketOpened = 0;
int SocketRunning = 0;


/* TODO: Add support for Modbus/UDP. TCP sucks for a such serial protocol ! ;-) */
void InitSocketServer( int UseUdpMode, int PortNbr )
{

#ifdef __WIN32__
	WORD wVersionRequested = MAKEWORD(1,1);       // Stuff for WSA functions
	WSADATA wsaData;                              // Stuff for WSA functions
	// This stuff initializes winsock
	WSAStartup(wVersionRequested, &wsaData);
#else
	// to not receive "Broken pipe" exception
	signal(SIGPIPE, SIG_IGN);
#endif

//printf("INIT SOCKET!!!\n");
	// Create a socket
	server_s = socket(AF_INET, SOCK_STREAM, 0);
	if ( server_s==SOCK_INVALID )
	{
		debug_printf(DBG_HEADER_ERR "Failed to open socket server...\n");
		FrameLogString( FRAMES_LOG_MODBUS_SLAVE_IP, 'i', "Failed to open socket server..." );
	}
	else
	{
		int Error = 0;
		SocketOpened = 1;
		// Fill-in my socket's address information and bind the socket
		server_addr.sin_family = AF_INET;
		server_addr.sin_port = htons( PortNbr );
		server_addr.sin_addr.s_addr = htonl( INADDR_ANY );
		Error = bind(server_s, (struct sockaddr *)&server_addr, sizeof(server_addr));
		if ( Error==SOCK_INVALID )
		{
			debug_printf(DBG_HEADER_ERR "Failed to bind socket server...(error=%s)\n", strerror(errno));
			FrameLogString( FRAMES_LOG_MODBUS_SLAVE_IP, 'i', "Failed to bind socket server..." );
			CloseSocketServer( );
		}
		else
		{
			// Listen for connections and then accept
			Error = listen(server_s, 1);
			if ( Error==SOCK_INVALID )
			{
				debug_printf(DBG_HEADER_ERR "Failed to listen socket server...(error=%s)\n", strerror(errno));
				FrameLogString( FRAMES_LOG_MODBUS_SLAVE_IP, 'i', "Failed to listen socket server..." );
				CloseSocketServer( );
			}
			else
			{
				SocketRunning = 1;

#ifdef __WIN32__
				ThreadHandle = CreateThread( NULL/*no security attributes*/, 16*1024L/*default stack size*/,
					(LPTHREAD_START_ROUTINE)SocketServerTcpMainLoop/* thread function*/,
					NULL/*argument to thread function*/,
					THREAD_QUERY_INFORMATION/*use default creation flags*/,
					&ThreadId/* returns the thread identifier*/);
	  			if ( ThreadHandle==NULL )
#else
				Error = pthread_create( &thread_socket_server, NULL, (void *(*)(void *))SocketServerTcpMainLoop, (void *)NULL );
				if (Error)
#endif
				{
					debug_printf(DBG_HEADER_ERR "Failed to create thread socket server...\n");
					CloseSocketServer( );
				}
				else
				{
					debug_printf( DBG_HEADER_INFO "Server socket init ok (modbus - port %d)!\n", PortNbr);
					FrameLogString( FRAMES_LOG_MODBUS_SLAVE_IP, 'i', "Socket server modbus slave init Ok." );
				}

			}
		}

	}
}

int AskAndAnswer( unsigned char * Ask, int LgtAsk, unsigned char * Answer )
{
	int LgtModbusReply = 0;
	int LgtHeaderReply = 0;
	int i;
	printf("-> ");
	for (i=0; i<LgtAsk; i++)
	{
		if ( i==LGT_MODBUS_IP_HEADER )
			printf("- ");
		printf ("%02X ", Ask[i]);
	}
	printf("\n");
	FrameLogDatas( FRAMES_LOG_MODBUS_SLAVE_IP, '(', Ask, LgtAsk );

	LgtModbusReply = ModbusRequestToRespond( &Ask[ LGT_MODBUS_IP_HEADER ], LgtAsk, &Answer[ LGT_MODBUS_IP_HEADER ] );
	// Send response to the client
	if ( LgtModbusReply>0 )
	{
		// add IP specific header
		// invocation identifier
		Answer[ LgtHeaderReply++ ] = Ask[ 0 ];
		Answer[ LgtHeaderReply++ ] = Ask[ 1 ];
		// protocol identifier
		Answer[ LgtHeaderReply++ ] = 0;
		Answer[ LgtHeaderReply++ ] = 0;
		// length
		Answer[ LgtHeaderReply++ ] = (unsigned char)((LgtModbusReply+1)>>8);
		Answer[ LgtHeaderReply++ ] = (unsigned char)(LgtModbusReply+1);
		// unit identifier
		Answer[ LgtHeaderReply++ ] = 1;
printf("MODBUS RESPONSE LGT=%d+%d !\n", LgtHeaderReply, LgtModbusReply );
		printf("<- ");
		for (i=0; i<LgtHeaderReply+LgtModbusReply; i++)
		{
			if ( i==LGT_MODBUS_IP_HEADER )
				printf("- ");
			printf ("%02X ", Answer[i]);
		}
		printf("\n");
		FrameLogDatas( FRAMES_LOG_MODBUS_SLAVE_IP, ')', Answer, LgtHeaderReply+LgtModbusReply );
	}
	return LgtHeaderReply+LgtModbusReply;
}

/* Main loop for tcp mode connections */
void SocketServerTcpMainLoop( void )
{
	SOCK_FD client_s;             // Client socket descriptor
	struct sockaddr_in client_addr;          // Client Internet address
	unsigned int addr_len;             // Internet address length
	unsigned char in_buf[BUF_SIZE];     // Input buffer for resquest
	unsigned char out_buf[BUF_SIZE];    // Output buffer for response

	int retcode;

#ifdef __XENO__
	pthread_set_name_np(pthread_self(), __FUNCTION__);
#endif
#ifdef __COBALT__
	pthread_setname_np(pthread_self(), __FUNCTION__);
#endif

	while( SocketRunning )
	{
		if( ModbusConfig.ModbusDebugLevel>=2 )
			debug_printf(DBG_HEADER_INFO "SOCKET WAITING...\n");
		addr_len = sizeof(client_addr);
		client_s = accept(server_s, (struct sockaddr *)&client_addr, &addr_len);
		if ( client_s!=-1 )
		{
			if( ModbusConfig.ModbusDebugLevel>=2 )
				debug_printf(DBG_HEADER_INFO "SOCKET CLIENT ACCEPTED...\n");
			do
			{
				// Request received from the client
				//  - The return code from recv() is the number of bytes received
				retcode = recv(client_s, in_buf, BUF_SIZE, 0);
//printf("SOCKED RECEIVED=%d !\n", retcode);
				if ( retcode==-1 )
				{
					debug_printf(DBG_HEADER_ERR "Failed to recv socket server...(error=%s)\n", strerror(errno));
					FrameLogString( FRAMES_LOG_MODBUS_SLAVE_IP, 'i', "Failed to recv socket server..." );
				}
				else
				{
					if ( retcode>0 )
					{
						int LgtReply = AskAndAnswer( in_buf, retcode, out_buf );
						if ( LgtReply>0 )
							send(client_s, out_buf, LgtReply, 0);
					}
				}

			}
			while( retcode>0 );
			if( ModbusConfig.ModbusDebugLevel>=2 )
				debug_printf(DBG_HEADER_INFO "CLOSE SOCK CLIENT.\n");
			#ifdef __WIN32__
			closesocket(client_s);
			#else
			close(client_s);
			#endif
		}
	}
#ifndef __WIN32__
	pthread_exit(NULL);
#endif
}

void CloseSocketServer( void )
{
	SocketRunning = 0;
#ifdef __WIN32__
	if ( ThreadHandle )
		TerminateThread( ThreadHandle, 0);
#endif
	// close socket server
	if ( SocketOpened )
	{
#ifdef __WIN32__
		closesocket(server_s);
		WSACleanup();
#else
		close(server_s);
#endif
		SocketOpened = 0;
		debug_printf( DBG_HEADER_INFO "Server socket closed!\n" );
	}
}



