// vars_names.h

#ifndef __VARS_NAMES_H__
#define __VARS_NAMES_H__

#ifdef __cplusplus
extern "C" {
#endif

int GetSizeVarsForTypeVar( int iTypeVarToSearch );
char * CreateVarName(int Type, int Offset, char SymbolNameIfAvail);
char TextParserForAVar( char * TextToParse, int * VarTypeFound, int * VarOffsetFound, int * pNumberOfChars, char PartialNames );
char TestVarIsReadWrite( int TypeVarTested, int OffsetVarTested );

#ifdef __cplusplus
}
#endif

#endif
