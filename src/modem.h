// modem.h

#ifndef __MODEM_H__
#define __MODEM_H__

#ifdef __cplusplus
extern "C" {
#endif

void InitModem( void );
void AnalyseCharsReceivedFromModem( char * StrReceived, int StrLgt );
char InitAndConfigModem( StrModem * pModemParameters );
char CallModem( char * CallStringCommand, char * StrTelephoneNumber );
void HangUpModem( );
void SetModemSerialNumPort( int NumPort );
char GetIfModemIsConnected( );
char GetIfModemInitAndConfigOk( );

void ModemAlarmsTransmitForSms( void );
void RemoteAlarmsTransmitModemSendSmsIfEventConcerned( int ScanAlarmSlot, char ForEnd, StrEventLog * pEvent );

#ifdef __cplusplus
}
#endif

#endif
