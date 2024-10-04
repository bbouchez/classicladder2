// edit_copy.h

#ifndef __EDIT_COPY_H__
#define __EDIT_COPY_H__

#ifdef __cplusplus
extern "C" {
#endif

void StartOrMotionPartSelection(double x,double y, char StartToClick);
void EndPartSelection( );
void GetSizesOfTheSelectionToCopy( int * pSizeX, int * pSizeY );
char GetIsOutputEleLastColumnSelection( );
void CopyRungPartSrcToDest( StrRung *RungSrc, StrRung *pRungDest, int PosiDestX, int PosiDestY, char JustRungCopyInBuffer );
void CleanUpSrcWhenStartMoving( );
void CopyNowPartSelected( double x,double y );

#ifdef __cplusplus
}
#endif

#endif
