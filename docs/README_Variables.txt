Classic Ladder 2 Project
Forked from Classic Ladder by Marc LE DOUARAIN
Copyright Marc LE DOUARAIN for Classic Ladder
Copyright Benoit BOUCHEZ for Classic Ladder 2 specific changes
https://github.com/bbouchez/classicladder2


AVAILABLE VARIABLES :
=====================

%Bxxx : Bit memory xx (boolean)
%Wxxx : Word memory xx (32 bits integer)
%Ixxx : Physical input xx (boolean) - typically received from MODBUS modules
%Qxxx : Physical output xx (boolean) - typically sent to MODBUS modules
%IWxxx : Physical word input xx (integer), most of the time analog input - typically received from MODBUS modules
%QWxxx : Physical word output xx (integer), most of the time analog output - typically sent to MODBUS modules
%QLEDx : LED located on PLC hardware - depends on hardware used
%Sxxx : System bit, see list below (boolean)
%SWxxx : System word, see list below (boolean)
%Cxx.Q : Counter xx done (boolean, user read only) - indicates when counter value equals preset value
%Cxx.E : Counter xx empty overflow (boolean, user read only) - indicates when counter wraps from 2147483647 to -2147483648 (positive overflow)
%Cxx.F : Counter xx full overflow (boolean, user read only) - indicates when counter wraps from -2147483648 to 2147483647 (negative overflow)
%Cxx.V : Counter xx current value (integer)
%Cxx.P : Counter xx preset (integer)
%TMxx.Q : IEC61131-3 Timer xx output (boolean, user read only)
%TMxx.V : IEC Timer xx current value (integer, user read only)
%TMxx.P : IEC Timer xx preset (integer)
%Rxxx.E : Register xx empty (boolean, user read only)
%Rxxx.F : Register xx full (boolean, user read only)
%Rxxx.I : Register xx input value (integer)
%Rxxx.O : Register xx output value (integer, user read only)
%Rxxx.S : Register xx nbr values currently stored (integer, user read only)
%Xxxx.X : Activity state of step xx (sequential language) - 0 = step is not active, 1 = step is active
%Xxxx.V : Time of activity in seconds of step xx (sequential language)


LIST OF SYSTEM VARIABLES :
==========================

%SW0: time in BCD
%SW1: date (year/month/day) in BCD
%SW2: week of day (0=sunday)
%S0: 1hz flash
%S1: 1hz flash inverted
%S2: 1 min flash
%S3: 1 min flash inverted
%S4: cold start
%S5: hot start
%S7: divide per zero error
%S8: out bit for SHL()/SHR()/ROL()/ROR() functions.
%S9: summer period
%S10: error of communication in the modbus master with Slave N°0.
... to %S19: error of communication in the modbus master with Slave N°9.
%S40: modem init & config is ok
%S41: modem connected

for-example, you can have on user led %QLED0 modem state with the following rung:
 |-[%S40]-+-[%S41]---[%S0]-+------(%QLED0)-|
 |        |                |               |
 |        +-NOT[%S41]------+               |
(led is on if modem init/config ok, and blinking during connection).


SYMBOLS :
=========

Each variable can be associated to a symbol name that can be then used instead of the
real variable name.
Partial symbol or complete symbol are possible.
A complete symbol corresponds directly to a real variable name:
ex: "InputK4" => %I17
A partial symbol is a part of a variable name without any attribute:
ex: "MyTimer" => %TM0 (that can not be used directly, but by adding
the attribute wanted: "MyTimer.Q" => %TM0.Q


INDEXED VARIABLES :
===================

In the arithmetic expressions and contacts/coils, variables indexed with another
one can be used.
Examples:
%W0[%W4] => if %W4 equals 23 it corresponds to %W23 !
%I0[%W20] => if %W20 equals 5 it corresponds to %I5 !
%B100[%W6] => if %W6 equals 56 it corresponds to %B156 !


CONSTANTS :
===========

Examples of constants usable in the arithmetic expressions:
=> 45 (decimal, per default)
=> $10 (hexadecimal, starting with $ character)
=> 'G' (character), between '').


LIST OF KNOWN OPERATORS IN ARITHMETIC EXPRESSIONS STRINGS :
===========================================================

& | ^   : and or xor
+ - * / % : plus minus mult div modulo
! : not

Functions available list (with variables or constants parameters) :
-------------------------------------------------------------------
ABS(a) : Absolute value
MINI(a,...,z) : Minimum value
MAXI(a,...,z) : Maximum value
AVG(a,...,z) : Average value
POW(a,b) : a power b
SHL(a,i) ROL(a,i) : Logic Shift or Rotate Left (out bit is stored in %SY8, for Rotate out bit is stored in bit 0)
SHR(a,i) ROR(a,i) : Logic Shift or Rotate Right (out bit is stored in %SY8, for Rotate out bit is stored in bit 31)


