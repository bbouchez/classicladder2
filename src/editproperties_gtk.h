// editproperties_gtk.h

#ifndef __EDITPROPERTIES_GTK_H__
#define __EDITPROPERTIES_GTK_H__

#ifdef __cplusplus
extern "C" {
#endif

void SetProperty(int NumParam,char * LblParam,char * ValParam, char ReadOnlyPropertie, char SetFocus);
char * GetProperty(int NumParam);
void ShowPropertiesWindow( int Visible );
void PropertiesInitGtk();

#ifdef __cplusplus
}
#endif

#endif
