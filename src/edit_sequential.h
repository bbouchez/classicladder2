// edit_sequential.h

#ifndef __EDIT_SEQUENTIAL_H__
#define __EDIT_SEQUENTIAL_H__

#ifdef __cplusplus
extern "C" {
#endif

void SaveSeqElementProperties( void );
void ModifyCurrentSeqPage(void);
void CancelSeqPageEdited(void);
void ApplySeqPageEdited(void);
int SearchTransiElement( StrSequential * pSeqSearch, int PageNumber, int PositionX, int PositionY );
void InitSeqElementsOfPage( int NumPage );
void EditElementInSeqPage(double x,double y);

#ifdef __cplusplus
}
#endif

#endif
