// calc.h

// --------------
// Refresh a rung
// --------------

#ifndef __CALC_H__
#define __CALC_H__

#ifdef __cplusplus
extern "C" {
#endif

void InitRungs(void);
void InitRung( StrRung * pRung );
void PrepareRungs(void);
void InitTimers(void);
void InitMonostables(void);
void InitCounters(void);
void InitTimersIEC(void);
void InitRegisters();
void PrepareAllDatasBeforeRun(void);
void InitArithmExpr(void);
int ReadVarForElement( StrElement * pElem, char * pInfoVarIsSet );
void WriteVarForElement( StrElement *pElem, int Value );
void RefreshASection( StrSection * pSection );
void ClassicLadder_RefreshAllSections(void);
void CopyRungToRung(StrRung * RungSrc,StrRung * RungDest);
void CopyElementToElement( StrElement * pEleSrc, StrElement *pEleDest );
char SaveRegisterFunctionBlockContent( int RegisterNbr, char * File, char Compressed );

#ifdef __cplusplus
}
#endif

#endif
