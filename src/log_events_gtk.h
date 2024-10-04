// log_events_gtk.h

#ifndef __LOG_EVENTS_GTK_H__
#define __LOG_EVENTS_GTK_H__

#ifdef __cplusplus
extern "C" {
#endif

void DisplayLogBookEvents( char OnLogContentModified );
gboolean DisplayLogBookEventsFromCsvFile( char * LogBookFileCsv );
void OpenLogBookWindow( GtkAction * ActionOpen, gboolean OpenIt );
void RememberLogBookWindowPrefs( void );
void LogBookInitGtk();

#ifdef __cplusplus
}
#endif

#endif
