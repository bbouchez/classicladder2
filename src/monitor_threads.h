// monitor_threads.h

#ifndef __MONITOR_THREADS_H__
#define __MONITOR_THREADS_H__

#ifdef __cplusplus
extern "C"
{
#endif

void InitGeneralMonitor( int ListenPortForSlave, char InitOnlyTheSlave );
void EndGeneralMonitor( void );
void MonitorSlaveLoopThread( int SlaveThreadForSerial );
void MonitorMasterLoopThread( void );

#ifdef GTK_INTERFACE
//////gboolean DoDisconnectTargetInGtkWithLock( void );
gboolean DoFlipFlopConnectDisconnectTargetInGtk( void );
#endif

#ifdef __cplusplus
}
#endif

#endif