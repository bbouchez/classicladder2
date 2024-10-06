// protocol_modbus_slave.h

#ifndef __PROTOCOL_MODBUS_SLAVE_H__
#define __PROTOCOL_MODBUS_SLAVE_H__

#ifdef __cplusplus
extern "C"
{
#endif

int ModbusRequestToRespond( unsigned char * Question, int LgtQuestion, unsigned char * Response );
int GetMobdusSlaveNbrVars( unsigned char FunctCode );
void SetVarFromModbusSlave( unsigned char FunctCode, int ModbusNum, int Value );
int GetVarForModbusSlave( unsigned char FunctCode, int ModbusNum );

#ifdef __cplusplus
}
#endif

#endif