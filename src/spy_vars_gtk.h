// spy_vars_gtk.h

#ifndef __SPY_VARS_GTK_H__
#define __SPY_VARS_GTK_H__

#ifdef __cplusplus
extern "C"
{
#endif

//void RefreshOneBoolVar( int Type, int Num, int Val );
void RefreshAllBoolsVars( );
void UpdateAllLabelsBoolsVars( int OnlyThisColumn );
void OpenSpyBoolVarsWindow( GtkAction * ActionOpen, gboolean OpenIt );
void RememberBoolVarsWindowPrefs( void );
void DisplayFreeVarSpy( );
void UpdateAllLabelsFreeVars( int OnlyThisOne, char * VarName );
void OpenSpyFreeVarsWindow( GtkAction * ActionOpen, gboolean OpenIt );
void RememberFreeVarsWindowPrefs( void );
void ConvertInfoDiskStats( char * BuffConv );
void DisplayTargetInfosVersion( void );
void DisplayProjectProperties( void );
void VarsWindowInitGtk( );

#ifdef __cplusplus
}
#endif

#endif