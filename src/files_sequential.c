/* files_sequential.c
Classic Ladder 2 Project
Forked from Classic Ladder by Marc LE DOUARAIN
Copyright Marc LE DOUARAIN for Classic Ladder
Copyright Benoit BOUCHEZ for Classic Ladder 2 specific changes
https://github.com/bbouchez/classicladder2
*/

/* ------------------------------------------------------------------------------------- */
/* Load/Save Sequential pages parameters */
/* ------------------------------------------------------------------------------------- */

/* This library is free software; you can redistribute it and/or */
/* modify it under the terms of the GNU Lesser General Public */
/* License as published by the Free Software Foundation; either */
/* version 2.1 of the License, or (at your option) any later version. */

/* This library is distributed in the hope that it will be useful, */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU */
/* Lesser General Public License for more details. */

/* You should have received a copy of the GNU Lesser General Public */
/* License along with this library; if not, write to the Free Software */
/* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "classicladder2.h"
#include "global.h"
#include "files.h"
#include "files_sequential.h"

#ifdef debug
#define dbg_printf printf
#else
static inline int dbg_printf(char *f, ...) {return 0;}
#endif



char ConvTypeOffsetVar(char * RawLine,int *VarType,int * VarOffset)
{
	char * StartOfValue;
	char * EndOfValue;

	StartOfValue = RawLine;
	EndOfValue = RawLine;

	/* Extract Var Type */
	StartOfValue = EndOfValue;
	do
	{
		EndOfValue++;
	}
	while(*EndOfValue!='/' && *EndOfValue!='\0');
	*EndOfValue++ = '\0';
	*VarType = atoi(StartOfValue);
	/* Extract Var Offset in the type table */
	StartOfValue = EndOfValue;
	do
	{
		EndOfValue++;
	}
	while( *EndOfValue!=10  && *EndOfValue!='\0');
	*EndOfValue++ = '\0';
	*VarOffset = atoi(StartOfValue);
	return TRUE;
}

char LoadSequential(char * FileName)
{
	FILE * File;
	char Okay = FALSE;
	char Line[300];
	char * LineOk;
	int NumPage,NumStep,NumTransi,ScanStep,NumSeqComment;
	StrStep * pStep;
	StrTransition * pTransi;
	StrSeqComment * pSeqComment;
	char * pCommentString;
	int StepData[100];
	int ScanData;
	char * pSearch;
	File = fopen(FileName,"rt");
	if (File)
	{
		do
		{
			LineOk = cl_fgets(Line,300,File);
			if (LineOk)
			{
				switch(Line[0])
				{
					case ';':
						break;
					case '#':
						if(strncmp(&Line[1],"VER=",4)==0)
						{
							if (atoi(&Line[5])>1)
							{
								printf("Sequential version not supported...\n");
								LineOk = FALSE;
							}
						}
						break;
					case 'P':
						NumPage = atoi( &Line[1] );
						if ( NumPage>=0 && NumPage<NBR_SEQUENTIAL_PAGES )
							strcpy( Sequential->PageComment[NumPage], &Line[3] );
						break;
					case 'S':
						ConvRawLineOfNumbers(&Line[1],6,StepData,0/*DefaultValueToComplete*/);
						NumStep = StepData[ 0 ];
						pStep = &Sequential->Step[ NumStep ];
						pStep->InitStep = StepData[ 1 ];
						pStep->StepNumber = StepData[ 2 ];
						pStep->NumPage = StepData[ 3 ];
						pStep->PosiX = StepData[ 4 ];
						pStep->PosiY = StepData[ 5 ];
						break;
					case 'T':
						ConvRawLineOfNumbers(&Line[1],1+4*NBR_SWITCHS_MAX+3,StepData,0/*DefaultValueToComplete*/);
						ScanData = 0;
						NumTransi = StepData[ ScanData++ ];
						pTransi = &Sequential->Transition[ NumTransi ];
						for ( ScanStep=0; ScanStep<NBR_SWITCHS_MAX; ScanStep++ )
							pTransi->NumStepToActiv[ ScanStep ] = StepData[ ScanData++ ];
						for ( ScanStep=0; ScanStep<NBR_SWITCHS_MAX; ScanStep++ )
							pTransi->NumStepToDesactiv[ ScanStep ] = StepData[ ScanData++ ];
						for ( ScanStep=0; ScanStep<NBR_SWITCHS_MAX; ScanStep++ )
							pTransi->NumTransLinkedForStart[ ScanStep ] = StepData[ ScanData++ ];
						for ( ScanStep=0; ScanStep<NBR_SWITCHS_MAX; ScanStep++ )
							pTransi->NumTransLinkedForEnd[ ScanStep ] = StepData[ ScanData++ ];
						pTransi->NumPage = StepData[ ScanData++ ];
						pTransi->PosiX = StepData[ ScanData++ ];
						pTransi->PosiY = StepData[ ScanData++ ];
						break;
					case 'C':
						NumTransi = atoi( &Line[1] );
						pTransi = &Sequential->Transition[ NumTransi ];
						pSearch = Line;
						do
						{
							pSearch++;
						}
						while( *pSearch!=',' );
						pSearch++;
						pSearch++;
						pSearch++;
						ConvTypeOffsetVar( pSearch, &pTransi->VarTypeCondi, &pTransi->VarNumCondi );
						break;
					case 'N':
						pCommentString = ConvRawLineOfNumbers( &Line[1], 4, StepData ,0/*DefaultValueToComplete*/ );
						ScanData = 0;
						NumSeqComment = StepData[ ScanData++ ];
						pSeqComment = &Sequential->SeqComment[ NumSeqComment ];
						pSeqComment->NumPage = StepData[ ScanData++ ];
						pSeqComment->PosiX = StepData[ ScanData++ ];
						pSeqComment->PosiY = StepData[ ScanData++ ];
						if ( *pCommentString!='\0' )
						{
							strcpy( pSeqComment->Comment, pCommentString );
//							RemoveEndLine( pSeqComment->Comment );
						}
						break;
				}
			}
		}
		while(LineOk);
		fclose(File);
		Okay = TRUE;
	}
	return (Okay);
}

void SaveArray( FILE * File, short int * pArray )
{
	int ScanStep = 0;
	do
	{
//		if ( ScanStep>0 )
//			fprintf( File, "-" );
		fprintf( File, "%d", pArray[ ScanStep ] );
			fprintf( File, "," );
		ScanStep++;
	}
	while( ScanStep<NBR_SWITCHS_MAX /*&& pArray[ ScanStep ]!=-1*/ );
//	fprintf( File, "," );
}
char SaveSequential(char * FileName)
{
	FILE * File;
	char Okay = FALSE;
	int ScanPage,NumStep,NumTransi,NumSeqComment;
	File = fopen(FileName,"wt");
	if (File)
	{
//		fprintf(File,"; Sequential\n");
		fprintf(File,S_LINE "#VER=1.0" E_LINE "\n");
		for (ScanPage=0; ScanPage<NBR_SEQUENTIAL_PAGES; ScanPage++ )
		{
			if ( Sequential->PageComment[ScanPage][0]!='\0' )
			{
				fprintf( File, S_LINE "P%d,%s", ScanPage, Sequential->PageComment[ScanPage] );
				fprintf( File, E_LINE "\n" );
			}
		}
		for (NumStep=0; NumStep<NBR_STEPS; NumStep++)
		{
			StrStep * pStep = &Sequential->Step[ NumStep ];
			if ( pStep->NumPage!=-1 )
			{
				fprintf( File, S_LINE "S%d,%d,%d,%d,%d,%d", NumStep, pStep->InitStep, pStep->StepNumber,
					pStep->NumPage, pStep->PosiX, pStep->PosiY );
				fprintf( File, E_LINE "\n" );
			}
		}
		for (NumTransi=0; NumTransi<NBR_TRANSITIONS; NumTransi++ )
		{
			StrTransition * pTransi = &Sequential->Transition[ NumTransi ];
			if ( pTransi->NumPage!=-1 )
			{
				fprintf( File, S_LINE "T%d,", NumTransi );
				SaveArray( File, pTransi->NumStepToActiv );
				SaveArray( File, pTransi->NumStepToDesactiv );
				SaveArray( File, pTransi->NumTransLinkedForStart );
				SaveArray( File, pTransi->NumTransLinkedForEnd );
				fprintf( File, "%d,%d,%d", pTransi->NumPage, pTransi->PosiX, pTransi->PosiY );
				fprintf( File, E_LINE "\n" );
			}
		}
		for (NumTransi=0; NumTransi<NBR_TRANSITIONS; NumTransi++ )
		{
			StrTransition * pTransi = &Sequential->Transition[ NumTransi ];
			if ( pTransi->NumPage!=-1 )
			{
				fprintf( File, S_LINE "C%d,0,%d/%d", NumTransi, pTransi->VarTypeCondi, pTransi->VarNumCondi );
				fprintf( File, E_LINE "\n" );
			}
		}
		for( NumSeqComment=0; NumSeqComment<NBR_SEQ_COMMENTS; NumSeqComment++ )
		{
			StrSeqComment * pSeqComment = &Sequential->SeqComment[ NumSeqComment ];
			if ( pSeqComment->NumPage!=-1 )
			{
				fprintf( File, S_LINE "N%d,", NumSeqComment );
				fprintf( File, "%d,%d,%d,", pSeqComment->NumPage, pSeqComment->PosiX, pSeqComment->PosiY );
				fprintf( File, "%s",  pSeqComment->Comment );
				fprintf( File, E_LINE "\n" );
			}
		}
		fclose(File);
		Okay = TRUE;
	}
	return (Okay);
}


