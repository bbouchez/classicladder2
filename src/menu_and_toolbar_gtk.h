// menu_and_toolbar_gtk.h

#ifndef __MENU_AND_TOOLBAR_GTK_H__
#define __MENU_AND_TOOLBAR_GTK_H__

#ifdef __cplusplus
extern "C" {
#endif

GtkUIManager * InitMenusAndToolBar( GtkWidget *vbox );
void EnableDisableMenusAccordingSectionType( );
void SetToogleMenuForSectionsManagerWindow( gboolean OpenedWin );
void SetToggleMenuForEditorWindow( gboolean OpenedWin );
void SetToggleMenuForSymbolsWindow( gboolean OpenedWin );
void SetToggleMenuForBoolVarsWindow( gboolean OpenedWin );
void SetToggleMenuForFreeVarsWindow( gboolean OpenedWin );
void SetToggleMenuForLogWindow( gboolean OpenedWin );
void SetToggleMenuForMonitorWindow( int NumFramesLogWindow, gboolean OpenedWin );
gboolean SetGtkMenuStateForRunStopSwitch( gboolean * Running );
void SetGtkMenuStateForConnectDisconnectSwitch( gboolean TargetConnected );
void MenuToSetTargetClockTime( void );
void MenuRebootTarget( void );
void MenuHaltTarget( void );
void MenuSendProjectToTargetAction( void );
void MenuReceiveProjectFromTargetAction( void );
void MenuSendUpdateSoftToTargetAction( void );
void NextStepBeforeSendingUpdateSoftToTarget( void );
void MenuViewRegisterBlockContent( void );
void MenuViewLinuxSysLogDebug( void );

#ifdef __cplusplus
}
#endif

#endif
