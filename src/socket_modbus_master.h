// socket_modbus_master.h

#ifndef __SOCKET_MODBUS_MASTER_H__
#define __SOCKET_MODBUS_MASTER_H__

#ifdef __cplusplus
extern "C"
{
#endif

void InitSocketModbusMaster( void );
void ConfigSerialModbusMaster( void );
void CloseSockSlave( int SlaveIndex );
void CloseSocketModbusMaster( void );
void SocketModbusMasterLoop( void );
void GetSocketModbusMasterStats( int SlaveToDisplay, char * Buff );

#ifdef __cplusplus
}
#endif

#endif