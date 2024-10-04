// vars_browser_gtk.h

#ifndef __VARS_BROWSER_GTK_H__
#define __VARS_BROWSER_GTK_H__

#ifdef __cplusplus
extern "C" {
#endif

void OpenBrowserVarsToReplace( GtkWidget *widget, GtkWidget * pEntryWidget );
void OpenBrowserVarsToAdd( GtkWidget *widget, GtkWidget * pEntryWidget );
void OpenBrowserVarsToReplaceOrAddIndex( GtkWidget *widget, GtkWidget * pEntryWidget );

char OpenBrowserVars( GtkWidget * pEntryWidget, char AddMode );

#ifdef __cplusplus
}
#endif

#endif
