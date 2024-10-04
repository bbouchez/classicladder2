// socket_server.h

#ifndef __SOCKET_SERVER_H__
#define __SOCKET_SERVER_H__

#ifdef __cplusplus
extern "C"
{
#endif

void InitSocketServer( int UseUdpMode, int PortNbr );
void SocketServerTcpMainLoop( void );
void CloseSocketServer( void );

#ifdef __cplusplus
}
#endif

#endif