// cl2_types_id.h
// Classic Ladder 2
// Copyright Benoit BOUCHEZ 2024

// ClassicLadder2 uses different ID than original ClassicLadder for var types and rung elements
// The organization in CL2 allows to use indexed arrays to reach functions rather than switch..case
// sequences used in ClassicLadder which consumes CPU power and times
// IDs for var types and rung elements must be consecutive

#ifndef __CL2_TYPES_ID_H__
#define __CL2_TYPES_ID_H__

//! Type IDs for variables
// Boolean must be in the first part of the table
// %Bx Bit memory (boolean)
#define VAR_MEM_BIT     0
// %Ix Physical input   (boolean)
#define VAR_PHYS_INPUT  1
// %Qx Physical output  (boolean)
#define VAR_PHYS_OUTPUT 2
// %Sx System bit       (boolean)
#define VAR_SYSTEM      3
// QLEDx User LED       (boolean)
#define VAR_USER_LED    4
// %TMxx.Q : IEC Timer xx output (boolean)
// NOTE : VAR_TIMER_DONE, VAR_TIMER_RUNING and VAR_MONOSTABLE_RUNNING are removed (OLD_TIMERS_MONO is removed in CL2)
#define VAR_TIMER_IEC_DONE  5
// %Cxx.Q : Counter xx done (boolean, user read only) - will be replaced by %CTUxx.Q, %CTDxx.Q or %CTUDxx.Q
// %Cxx.Q replaces %cXX.D from classicladder as defined in IEC61131-3
#define VAR_COUNTER_DONE    6
// %Cxx.E : Counter xx empty overflow (boolean) - will be removed with IEC counters
#define VAR_COUNTER_EMPTY   7
// %Cxx.F : Counter xx full overflow (boolean, user read only) - will be removed with IEC counters
#define VAR_COUNTER_FULL    8
// %Xxxx.X : Step xx is active (sequential language - boolean). Note : this is changed from .A in classicladder (.X is the notation from IEC61131-3)
//! TODO : in classicladder, variable name was A (for active). Change code to use X
#define VAR_STEP_ACTIVITY   9
// %Rxxx.E : Register xx empty (boolean)
#define VAR_REGISTER_EMPTY  10
// %Rxxx.F : Register xx full (boolean)
#define VAR_REGISTER_FULL   11

#define VAR_ARE_WORD        12      // MUST BE THE SAME AS VAR_ARE_WORD (mark limit between boolean and integer types)
// %Wxxx : Word memory xx (integer)
#define VAR_MEM_WORD        12
// %IWxxx : Physical word input xx (integer)
#define VAR_PHYS_WORD_INPUT 13
// %QWxxx : Physical word output xx (integer)
#define VAR_PHYS_WORD_OUTPUT    14
// %SWxxx : System word (integer)
#define VAR_WORD_SYSTEM     15
//%TMxx.V : IEC Timer xx current value (integer) - is called .ET in IEC61131-3
#define VAR_TIMER_IEC_VALUE 16
// %TMxx.P : IEC Timer xx preset (integer) - is called .PT in IEC61131-3
#define VAR_TIMER_IEC_PRESET    17
// %Cxx.V : Counter xx current value (integer) - is replaced by CV in IEC61131-3 counters
#define VAR_COUNTER_VALUE   18
// %Cxx.P : Counter xx preset (integer) - is replaced by PV in IEC61131-3 counters
#define VAR_COUNTER_PRESET  19
// %Xxxx.V : Time of activity in seconds of step xx (sequential language)
//! TODO : check how step duration is represented in IEC61131-3
#define VAR_STEP_TIME   20
// %Rxxx.I : Register xx input value (integer)
#define VAR_REGISTER_IN_VALUE   21
// %Rxxx.O : Register xx output value (integer)
#define VAR_REGISTER_OUT_VALUE  22
// %Rxxx.S : Register xx nbr values currently stored (integer)
#define VAR_REGISTER_NBR_VALUES 23

#define NUMBER_TYPE_VARIABLES   24

#define TEST_VAR_IS_A_BOOL( type ) (type<VAR_ARE_WORD)

//! Type IDs for Rung elements
// Empty rung cell
#define ELE_FREE            0
// Locked / unusable cell
#define ELE_UNUSABLE        1
// Horizontal line cell
#define ELE_CONNECTION      2
// NO contact cell
#define ELE_INPUT           3
// NC contact cell
#define ELE_INPUT_NOT       4
// Rising edge contact cell
#define ELE_RISING_INPUT    5
// Falling edge contact cell
#define ELE_FALLING_INPUT   6
// Comparator contact cell
#define ELE_COMPAR          7
// Normal coil cell
#define ELE_OUTPUT          8
// Inverse coil cell
#define ELE_OUTPUT_NOT      9
// SET coil cell
#define ELE_OUTPUT_SET      10
// RESET coil cell
#define ELE_OUTPUT_RESET    11
// Rising edge coil cell
//! TODO : to be implemented in CL2
#define ELE_OUTPUT_RISING   12
// Falling edge coil cell
//! TODO : to be implemented in CL2
#define ELE_OUTPUT_FALLING  13
// JUMP block cell
#define ELE_OUTPUT_JUMP     14
// RETURN block cell
//! TODO : to be implemented in CL2
#define ELE_OUTPUT_RETURN   15
// CALL block cell
#define ELE_OUTPUT_CALL     16
// OPERATE block
#define ELE_OUTPUT_OPERATE  17
// IEC timer block (TON, TOF, TP)
#define ELE_TIMER_IEC       18
// Counter block
//! TODO : implement IEC counters
#define ELE_COUNTER         20
// Register block
#define ELE_REGISTER        21

#define NUMBER_TYPE_ELEM   22

#endif
