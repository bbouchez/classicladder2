// monitor_protocol_adds_serial.h

#ifndef __MONITOR_PROTOCOL_ADDS_SERIAL_H__
#define __MONITOR_PROTOCOL_ADDS_SERIAL_H__

#ifdef __cplusplus
extern "C" {
#endif


#define CHAR_STX 2
#define CHAR_ETX 3

#define LGT_MONITOR_SERIAL_BUFFER 1280

#define NBR_MONITOR_SERIALS_BUFFERS 2
#define MONITOR_SERIAL_SLAVE 0
#define MONITOR_SERIAL_MASTER 1

typedef struct StrMonitorSerialBuffer
{
	char BuffRecv[ LGT_MONITOR_SERIAL_BUFFER ];
	int CurrLgtRecv; // -1 if searching for first character STX
}
StrMonitorSerialBuffer;

int MonitorAddSerialEncapsul( char * Frame, int LgtPureFrame );
int MonitorSerialDatasReceivedIsEnd( int SerialChannel, char * SerialDatasRecv, int LgtSerialDatasRecv, char * CompletePureFrameToStoreThere );

#ifdef __cplusplus
}
#endif

#endif
