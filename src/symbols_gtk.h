// symbols_gtk.h

#ifndef __SYMBOLS_GTK_H__
#define __SYMBOLS_GTK_H__

#ifdef __cplusplus
extern "C"
{
#endif

void DisplaySymbols( );
void OpenSymbolsWindow( GtkAction * ActionOpen, gboolean OpenIt );
void RememberSymbolsWindowPrefs( void );
void SymbolsInitGtk();

#ifdef __cplusplus
}
#endif

#endif