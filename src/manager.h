// manager.h

#ifndef __MANAGER_H__
#define __MANAGER_H__

#ifdef __cplusplus
extern "C" {
#endif

void InitSections( void );
int SearchSubRoutineWithItsNumber( int SubRoutineNbrToFind );
int SearchSectionWithName( char * SectionNameToFind );
void SetSectionSelected( int NumSec /*char * SectionName*/ );
int AddSection( char * NewSectionName, int TypeLangageSection, int SubRoutineNbr );
void ModifySectionProperties( int NumSec /*char * OriginalSectionName*/, char * NewSectionName );
int NbrSectionsDefined( void );
int VerifyIfSectionNameAlreadyExist( char * Name );
int VerifyIfSubRoutineNumberExist( int SubRoutineNbr );
void DelSection( int NumSec /*char * SectionNameToErase*/ );
int GetPrevNextSection( int RefSectionNbr, char NextSearch );
void SwapSections( int SectionNbr1, int SectionNbr2 /*char * SectionName1, char * SectionName2*/ );
int FindFreeSequentialPage( void );

#ifdef __cplusplus
}
#endif

#endif
