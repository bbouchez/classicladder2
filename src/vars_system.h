// vars_system.h

#ifndef __VARS_SYSTEM_H__
#define __VARS_SYSTEM_H__

#ifdef __cplusplus
extern "C" {
#endif

void InitSystemVars( char HardwareStart );
void UpdateSystemVars( void );

void VerifyAutoAdjustSummerWinterTime( void );

#ifdef __cplusplus
}
#endif

#endif
