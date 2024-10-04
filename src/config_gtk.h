// config_gtk.h

#ifndef __CONFIG_GTK_H__
#define __CONFIG_GTK_H__

#ifdef __cplusplus
extern "C" {
#endif

void OpenConfigWindowGtk( );
void FillComboBoxConfigSlavesList( MyGtkComboBox * pComboBox, char ListForStatsSelect, char CleanUpBefore );

#ifdef __cplusplus
}
#endif

#endif
