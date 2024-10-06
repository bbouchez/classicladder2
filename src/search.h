// search.h

#ifndef __SEARCH_H__
#define __SEARCH_H__

#ifdef __cplusplus
extern "C" {
#endif

void InitSearchDatas( void );

void GoToFirstRung( void );
void GoToLastRung( void );

char SearchTestIfLadderEleMatch( StrElement * pEle );
char SearchTestIfSeqTransiMatch( StrTransition * pTransi );
char SearchTestIfOnCurrent( int DisplayedRung, int DisplayedPosX, int DisplayedPoxY );
void SearchAndGoToNextElement( void );
void SearchAndGoToPreviousElement( void );
void SearchNewElement( int IndexTypeSelected, char * StringEntered );

#ifdef __cplusplus
}
#endif

#endif
