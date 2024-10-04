/* vars_access.c
Classic Ladder 2 Project
Forked from Classic Ladder by Marc LE DOUARAIN
Copyright Marc LE DOUARAIN for Classic Ladder
Copyright Benoit BOUCHEZ for Classic Ladder 2 specific changes
https://github.com/bbouchez/classicladder2
*/

// Functions in this module have been completely rewritten by Benoit BOUCHEZ
// The switch...case structure used on original ClassicLadder project impacts very badly CPU performance as it forces the CPU to do many tests and jumps
// The new structure uses an array of pointers to call directly a function for each variable type based on the variable index

/* --------------------------------------- */
/* Access a variable for reading / writing */
/* --------------------------------------- */

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

#ifdef GTK_INTERFACE
#include <gtk/gtk.h>
#include "classicladder2_gtk.h"
#endif

#if defined(MODULE) && defined(RTAI)
#include <linux/kernel.h>
#include <linux/module.h>
#include "rtai.h"
#else
#include <stdio.h>
#include <stdlib.h>
#endif
#include "classicladder2.h"
#include "global.h"
#include "vars_access.h"
#ifdef COMPLETE_PLC
#include "log_events.h"
#endif

#define MASK_VAR_SETTED 0x80

void InitVars( char DoLogEvents )
{
	int NumVar;
	for (NumVar=0; NumVar<SIZE_VAR_ARRAY; NumVar++)
	{
		if ( DoLogEvents )
			WriteVar( VAR_MEM_BIT, NumVar, FALSE );
		else
			VarArray[NumVar] = FALSE;
	}
	for (NumVar=0; NumVar<SIZE_VAR_WORD_ARRAY; NumVar++)
		VarWordArray[NumVar] = 0;

	for (NumVar=0; NumVar<NBR_PHYS_INPUTS; NumVar++)
	{
		StrInputFilterAndState * pInput = &InputFilterAndStateArray[ NumVar ];
		pInput->FilterMask = 0x7;
		pInput->BuffRawInput = 0;
		pInput->InputStateForLogic = -1; // no "real" filtered value for now
	}

	/* to tell the GTK application to refresh the bits */
	InfosGene->CmdRefreshVarsBits = TRUE;
}  // InitVars
// --------------------------------

void InitSetsVars( void )
{
	int NumVar;
printf("-->init VarSetArray[] here...\n");
	for (NumVar=0; NumVar<SIZE_VAR_SET_ARRAY; NumVar++)
		VarSetArray[ NumVar ] = 0;
}  // InitSetVars
// --------------------------------

// BEB : this function can be kept with a switch..case structure as it is only called by LoadSetsVarList in preferences.c
// It is not called cyclically during PLC program execution
int GetNbrVarsForType( int TypeVar )
{
	switch(TypeVar)
	{
		case VAR_MEM_BIT:
			return NBR_BITS;
		case VAR_PHYS_INPUT:
			return NBR_PHYS_INPUTS;
		case VAR_PHYS_OUTPUT:
			return NBR_PHYS_OUTPUTS;
		case VAR_USER_LED:
			return NBR_USERS_LEDS;
		case VAR_SYSTEM:
			return NBR_VARS_SYSTEM;
#ifdef SEQUENTIAL_SUPPORT
		case VAR_STEP_ACTIVITY:
			return NBR_STEPS;
#endif
		case VAR_COUNTER_DONE:
			return NBR_COUNTERS;
		case VAR_COUNTER_EMPTY:
			return NBR_COUNTERS;
		case VAR_COUNTER_FULL:
			return NBR_COUNTERS;
		case VAR_TIMER_IEC_DONE:
			return NBR_TIMERS_IEC;
		case VAR_REGISTER_EMPTY:
		case VAR_REGISTER_FULL:
			return NBR_REGISTERS;
		case VAR_MEM_WORD:
			return NBR_WORDS;
		case VAR_PHYS_WORD_INPUT:
			return NBR_PHYS_WORDS_INPUTS;
		case VAR_PHYS_WORD_OUTPUT:
			return NBR_PHYS_WORDS_OUTPUTS;
		case VAR_WORD_SYSTEM:
			return NBR_VARS_WORDS_SYSTEM;
#ifdef SEQUENTIAL_SUPPORT
		case VAR_STEP_TIME:
			return NBR_STEPS;
#endif
		case VAR_COUNTER_PRESET:
			return NBR_COUNTERS;
		case VAR_COUNTER_VALUE:
			return NBR_COUNTERS;
		case VAR_TIMER_IEC_PRESET:
			return NBR_TIMERS_IEC;
		case VAR_TIMER_IEC_VALUE:
			return NBR_TIMERS_IEC;
		case VAR_REGISTER_IN_VALUE:
		case VAR_REGISTER_OUT_VALUE:
		case VAR_REGISTER_NBR_VALUES:
			return NBR_REGISTERS;
		default:
			rt_debug_printf("!!! Error : Type (=%d) not found in %s(%d)\n", TypeVar, __FUNCTION__, TypeVar);
	}
	return -1;
}  // GetNbrVarsForType
// --------------------------------

// *** Functions to read each variable type
// Prototype type for ReadVar function table
typedef int (*T_READVAR_FUNC) (int Offset);

static int ReadVarMemBitFunc (int Offset)
{
    return VarArray[Offset];
}

static int ReadVarPhysicalInputFunc (int Offset)
{
	if ( VarSetArray[ Offset ]&MASK_VAR_SETTED )
		return VarSetArray[ Offset ]&1;
    else
		return VarArray[NBR_BITS+Offset];
}

static int ReadVarPhysicalOutputFunc (int Offset)
{
    if ( VarSetArray[NBR_PHYS_INPUTS+Offset]&MASK_VAR_SETTED )
		return VarSetArray[NBR_PHYS_INPUTS+Offset]&1;
	else
        return VarArray[NBR_BITS+NBR_PHYS_INPUTS+Offset];
}

static int ReadVarSystemFunc (int Offset)
{
    return VarArray[NBR_BITS+NBR_PHYS_INPUTS+NBR_PHYS_OUTPUTS+Offset];
}

static int ReadVarUserLEDFunc (int Offset)
{
	return InfosGene->UserLedVar[Offset];
}

static int ReadVarTimerIECDoneFunc (int Offset)
{
    return NewTimerArray[Offset].Output;
}

static int ReadVarCounterDoneFunc (int Offset)
{
	return CounterArray[Offset].OutputDone;
}

static int ReadVarCounterEmptyFunc (int Offset)
{
	return CounterArray[Offset].OutputEmpty;
}

static int ReadVarCounterFullFunc (int Offset)
{
    return CounterArray[Offset].OutputFull;
}

static int ReadVarStepActivityFunc (int Offset)
{
    return VarArray[NBR_BITS+NBR_PHYS_INPUTS+NBR_PHYS_OUTPUTS+NBR_VARS_SYSTEM+Offset];
}

static int ReadVarRegisterEmptyFunc (int Offset)
{
    return RegisterArray[Offset].OutputEmpty;
}

static int ReadVarRegisterFullFunc (int Offset)
{
	return RegisterArray[Offset].OutputFull;
}

static int ReadVarMemWordFunc (int Offset)
{
    return VarWordArray[Offset];
}

static int ReadVarPhysicalInputWordFunc (int Offset)
{
    return VarWordArray[NBR_WORDS+Offset];
}

static int ReadVarPhysicalOutputWordFunc (int Offset)
{
    return VarWordArray[NBR_WORDS+NBR_PHYS_WORDS_INPUTS+Offset];
}

static int ReadVarSystemWordFunc (int Offset)
{
    return VarWordArray[NBR_WORDS+NBR_PHYS_WORDS_INPUTS+NBR_PHYS_WORDS_OUTPUTS+Offset];
}

static int ReadVarIECTimerValueFunc (int Offset)
{
    return NewTimerArray[Offset].Value;
}

static int ReadVarIECTimerPresetFunc (int Offset)
{
    return NewTimerArray[Offset].Preset;
}

static int ReadVarCounterValueFunc (int Offset)
{
    return CounterArray[Offset].Value;
}

static int ReadVarCounterPresetFunc (int Offset)
{
	return CounterArray[Offset].Preset;
}

static int ReadVarStepTimeFunc (int Offset)
{
    return VarWordArray[NBR_WORDS+NBR_PHYS_WORDS_INPUTS+NBR_PHYS_WORDS_OUTPUTS+NBR_VARS_WORDS_SYSTEM+Offset];
}

static int ReadVarRegisterInFunc (int Offset)
{
    return RegisterArray[Offset].ValueIn;
}

static int ReadVarRegisterOutFunc (int Offset)
{
    return RegisterArray[Offset].ValueOut;
}

static int ReadVarRegisterNbrFunc (int Offset)
{
    return RegisterArray[Offset].NbrValuesSaved;
}


// This table MUST be in the exact same order as Type IDs for variables in cl2_types_id.h
static T_READVAR_FUNC ReadVarFunctions[NUMBER_TYPE_VARIABLES] = {ReadVarMemBitFunc, ReadVarPhysicalInputFunc, ReadVarPhysicalOutputFunc, ReadVarSystemFunc, ReadVarUserLEDFunc,
                                                                ReadVarTimerIECDoneFunc, ReadVarCounterDoneFunc, ReadVarCounterEmptyFunc, ReadVarCounterFullFunc, ReadVarStepActivityFunc,
                                                                ReadVarRegisterEmptyFunc, ReadVarRegisterFullFunc, ReadVarMemWordFunc, ReadVarPhysicalInputWordFunc, ReadVarPhysicalOutputWordFunc,
                                                                ReadVarSystemWordFunc, ReadVarIECTimerValueFunc, ReadVarIECTimerPresetFunc, ReadVarCounterValueFunc, ReadVarCounterPresetFunc,
                                                                ReadVarStepTimeFunc, ReadVarRegisterInFunc, ReadVarRegisterOutFunc, ReadVarRegisterNbrFunc};

// This function has been completely rewritten from ClassicLadder by Benoit BOUCHEZ
// The switch...case structure impacts very badly CPU performance as it forces the CPU to do many tests and jumps
// The new structure uses an array of pointers to call directly a function for each variable type based on the variable index
int ReadVar (int TypeVar, int Offset)
{
    if (TypeVar<NUMBER_TYPE_VARIABLES)
    {
        return (ReadVarFunctions[TypeVar](Offset));
    }
    else
    {
        rt_debug_printf("!!! Error : Type (=%d) not found in ReadVar(%d,%d)\n", TypeVar, TypeVar, Offset);
        return 0;
    }
}  // ReadVar
// --------------------------------

// *** Functions to write each variable type
// Prototype type for WriteVar function table
typedef void (*T_WRITEVAR_FUNC) (int NumVar, int Value);

static void WriteVarMemBitFunc (int NumVar, int Value)
{
#ifdef COMPLETE_PLC
    if (InfosGene->LadderState==STATE_RUN)
    {
        //! TODO : modify VarStateChanged function to avoid to pass TypeVar as it is only used by a few types
        //! then uncomment the following block
        // log of this variable wanted ?
        /*
		if ( LogVarArray[ NumVar ] )
		{
            // a new state ?
			if ( VarArray[NumVar]!=Value )
				VarStateChanged( TypeVar, NumVar, Value );
        }
        */
    }
#endif
	VarArray[NumVar] = Value;
    /* to tell the GTK application to refresh the bits */
	InfosGene->CmdRefreshVarsBits = TRUE;
}

static void WriteVarPhysicalInputFunc (int NumVar, int Value)
{
	VarArray[NBR_BITS+NumVar] = Value;
    /* to tell the GTK application to refresh the bits */
	InfosGene->CmdRefreshVarsBits = TRUE;
}

static void WriteVarPhysicalOutputFunc (int NumVar, int Value)
{
	VarArray[NBR_BITS+NBR_PHYS_INPUTS+NumVar] = Value;
    /* to tell the GTK application to refresh the bits */
	InfosGene->CmdRefreshVarsBits = TRUE;
}

static void WriteVarSystemFunc (int NumVar, int Value)
{
	VarArray[NBR_BITS+NBR_PHYS_INPUTS+NBR_PHYS_OUTPUTS+NumVar] = Value;
}

static void WriteVarUserLEDFunc (int NumVar, int Value)
{
	InfosGene->UserLedVar[NumVar] = Value;
}

static void WriteVarTimerIECDoneFunc (int NumVar, int Value)
{
	NewTimerArray[NumVar].Output = Value;
}

static void WriteVarCounterDoneFunc (int NumVar, int Value)
{
    CounterArray[NumVar].OutputDone = Value;
}

static void WriteVarCounterEmptyFunc (int NumVar, int Value)
{
    CounterArray[NumVar].OutputEmpty = Value;
}

static void WriteVarCounterFullFunc (int NumVar, int Value)
{
	CounterArray[NumVar].OutputFull = Value;
}

static void WriteVarStepActivityFunc (int NumVar, int Value)
{
	VarArray[NBR_BITS+NBR_PHYS_INPUTS+NBR_PHYS_OUTPUTS+NBR_VARS_SYSTEM+NumVar] = Value;
}

static void WriteVarRegisterEmptyFunc (int NumVar, int Value)
{
	RegisterArray[NumVar].OutputEmpty = Value;
}

static void WriteVarRegisterFullFunc (int NumVar, int Value)
{
    RegisterArray[NumVar].OutputFull = Value;
}

static void WriteVarMemWordFunc (int NumVar, int Value)
{
	VarWordArray[NumVar] = Value;
}

static void WriteVarPhysicalInputWordFunc (int NumVar, int Value)
{
    VarWordArray[NBR_WORDS+NumVar] = Value;
}

static void WriteVarPhysicalOutputWordFunc (int NumVar, int Value)
{
	VarWordArray[NBR_WORDS+NBR_PHYS_WORDS_INPUTS+NumVar] = Value;
}

static void WriteVarSystemWordFunc (int NumVar, int Value)
{
	VarWordArray[NBR_WORDS+NBR_PHYS_WORDS_INPUTS+NBR_PHYS_WORDS_OUTPUTS+NumVar] = Value;
}

static void WriteVarIECTimerValueFunc (int NumVar, int Value)
{
    NewTimerArray[NumVar].Value = Value;
}

static void WriteVarIECTimerPresetFunc (int NumVar, int Value)
{
    NewTimerArray[NumVar].Preset = Value;
}

static void WriteVarCounterValueFunc (int NumVar, int Value)
{
    CounterArray[NumVar].Value = Value;
}

static void WriteVarCounterPresetFunc (int NumVar, int Value)
{
    CounterArray[NumVar].Preset = Value;
}

static void WriteVarStepTimeFunc (int NumVar, int Value)
{
	VarWordArray[NBR_WORDS+NBR_PHYS_WORDS_INPUTS+NBR_PHYS_WORDS_OUTPUTS+NBR_VARS_WORDS_SYSTEM+NumVar] = Value;
}

static void WriteVarRegisterInFunc (int NumVar, int Value)
{
	RegisterArray[NumVar].ValueIn = Value;
}

static void WriteVarRegisterOutFunc (int NumVar, int Value)
{
    RegisterArray[NumVar].ValueOut = Value;
}

static void WriteVarRegisterNbrFunc (int NumVar, int Value)
{
    RegisterArray[NumVar].NbrValuesSaved = Value;
}


// This table MUST be in the exact same order as Type IDs for variables in cl2_types_id.h
static T_WRITEVAR_FUNC WriteVarFunctions[NUMBER_TYPE_VARIABLES] = {WriteVarMemBitFunc, WriteVarPhysicalInputFunc, WriteVarPhysicalOutputFunc, WriteVarSystemFunc, WriteVarUserLEDFunc,
                                                                   WriteVarTimerIECDoneFunc, WriteVarCounterDoneFunc, WriteVarCounterEmptyFunc, WriteVarCounterFullFunc, WriteVarStepActivityFunc,
                                                                   WriteVarRegisterEmptyFunc, WriteVarRegisterFullFunc, WriteVarMemWordFunc, WriteVarPhysicalInputWordFunc, WriteVarPhysicalOutputWordFunc,
                                                                   WriteVarSystemWordFunc, WriteVarIECTimerValueFunc, WriteVarIECTimerPresetFunc, WriteVarCounterValueFunc, WriteVarCounterPresetFunc,
                                                                   WriteVarStepTimeFunc, WriteVarRegisterInFunc, WriteVarRegisterOutFunc, WriteVarRegisterNbrFunc };

void WriteVar (int TypeVar,int NumVar,int Value)
{
    if (TypeVar<NUMBER_TYPE_VARIABLES)
    {
        WriteVarFunctions[TypeVar](NumVar, Value);
    }
    else
    {
        rt_debug_printf("!!! Error : Type (=%d) not found in WriteVar(%d,%d)\n", TypeVar, TypeVar, NumVar);
    }
}  // WriteVar
// --------------------------------

void WriteBoolVarWithoutLog( int NumVar,int Value )
{
	VarArray[NumVar] = Value;
	/* to tell the GTK application to refresh the bits */
	InfosGene->CmdRefreshVarsBits = TRUE;
}  // WriteBoolVarWithoutLog
// --------------------------------

void SetVar( int TypeVar, int NumVar, int SetValue )
{
	switch( TypeVar )
	{
		case VAR_PHYS_INPUT:
			VarSetArray[ NumVar ] = SetValue|MASK_VAR_SETTED;
			InfosGene->BackgroundSaveSetVarsList = TRUE;
			/* to tell the GTK application to refresh the bits */
			InfosGene->CmdRefreshVarsBits = TRUE;
			break;
		case VAR_PHYS_OUTPUT:
			VarSetArray[NBR_PHYS_INPUTS+NumVar] = SetValue|MASK_VAR_SETTED;
			InfosGene->BackgroundSaveSetVarsList = TRUE;
			/* to tell the GTK application to refresh the bits */
			InfosGene->CmdRefreshVarsBits = TRUE;
			break;
		default:
			rt_debug_printf("!!! Error : Unsupported type in %s(%d,%d)\n", __FUNCTION__, TypeVar, NumVar);
			break;
	}
}  // SetVar
// --------------------------------

void UnsetVar( int TypeVar, int NumVar )
{
	switch( TypeVar )
	{
		case VAR_PHYS_INPUT:
			VarSetArray[ NumVar ] = 0;
			InfosGene->BackgroundSaveSetVarsList = TRUE;
			/* to tell the GTK application to refresh the bits */
			InfosGene->CmdRefreshVarsBits = TRUE;
			break;
		case VAR_PHYS_OUTPUT:
			VarSetArray[NBR_PHYS_INPUTS+NumVar] = 0;
			InfosGene->BackgroundSaveSetVarsList = TRUE;
			/* to tell the GTK application to refresh the bits */
			InfosGene->CmdRefreshVarsBits = TRUE;
			break;
		default:
			rt_debug_printf("!!! Error : Unsupported type in %s(%d,%d)\n", __FUNCTION__, TypeVar, NumVar);
			break;
	}
}  // UnsetVar
// --------------------------------

char IsVarSet( int TypeVar, int NumVar )
{
	char IsSet = FALSE;
	switch( TypeVar )
	{
		case VAR_PHYS_INPUT:
			IsSet = VarSetArray[ NumVar ]&MASK_VAR_SETTED;
			break;
		case VAR_PHYS_OUTPUT:
			IsSet = VarSetArray[NBR_PHYS_INPUTS+NumVar]&MASK_VAR_SETTED;
			break;
		default:
			rt_debug_printf("!!! Error : Unsupported type in %s(%d,%d)\n", __FUNCTION__, TypeVar, NumVar);
			break;
	}
	return IsSet;
}  // IsVarSet
// --------------------------------

void DumpVars(void)
{
	int NumVar;
	for (NumVar=0; NumVar<20; NumVar++)
		rt_debug_printf("Var %d=%d\n",NumVar,ReadVar(VAR_MEM_BIT,NumVar));
}  // DumpVars
// --------------------------------

/* these are only useful for the MAT-connected version */
void DoneVars(void) {}
void CycleStart(void) {}
void CycleEnd(void) {}

