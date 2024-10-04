// drawing_sequential.h

#ifndef __DRAWING_SEQUENTIAL_H__
#define __DRAWING_SEQUENTIAL_H__

#ifdef __cplusplus
extern "C" {
#endif

void DrawSeqStep( cairo_t * cr,int x,int y,int Size,StrStep * pStep,char DrawingOption );
void DrawSeqTransition( cairo_t * cr, int PageNbr, int x,int y,int Size,int NumTransi/*StrTransition * pTransi*/,int TheHeaderSeqCommentHeight,char DrawingOption );

void DrawSequentialPage( cairo_t * cr, int PageNbr, int SeqPxSize, char DrawingOption );

void DrawSeqElementForToolBar( cairo_t * cr, int x, int y, int Size, int NumElement );

#ifdef __cplusplus
}
#endif

#endif
