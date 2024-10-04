// symbols.h

#ifndef __SYMBOLS_H__
#define __SYMBOLS_H__

#ifdef __cplusplus
extern "C"
{
#endif

void InitSymbols( void );
StrSymbol * ConvVarNameInSymbolPtr( char * tcVarNameVar );
char * ConvVarNameToSymbol( char * VarNameParam );
char * ConvSymbolToVarName( char * SymbolParam );

#ifdef __cplusplus
}
#endif

#endif