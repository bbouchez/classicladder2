// hardware.h

#ifndef __HARDWARE_H__
#define __HARDWARE_H__

#ifdef __cplusplus
extern "C" {
#endif

//#define USE_PARPORT1
//////#define USE_PARPORT2

//#define PARPORT1_IO_ADDRESS 0x378
//#define PARPORT2_IO_ADDRESS 0x278

void InitIOConf( void );

void ReadPhysicalInputs( void );
void CopyInputsStatesToInputsVars( void );
void WritePhysicalOutputs( char OnlyForLifeLed );

char InitHardware( void );
void EndHardware( void );
void OpenHardware( int ComediToOpenMask );
void ConfigHardware( char ForOutputs );
void ConfigHardwareForLifeUsersLeds( );

#ifdef __cplusplus
}
#endif

#endif
