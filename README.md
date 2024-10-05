Classic Ladder 2 (CL2) is based on the Classic Ladder by Marc LE DOUARAIN (https://github.com/MaVaTi56/classicladder)

Please note that CL2 is *not* a evolution of Classic Ladder, and does not mean to replace it in any way!!
Marc LE DOUARAIN has allowed this fork of his work, but he is not related to this project, so please don't disturb him with questions/remarks about CL2 (thank you for him)

Project files are not compatible between CL2 and Classic Ladder, as there are many major differences between the two software.

Major differences between Classic Ladder 2 and Classic Ladder are :
* Better inclusion of IEC61131-3 norm for the Ladder language (variable name compliance, possibility to chain coils, etc...)
* Modified editor to comply with IEC61131-3 function blocks
* Totally rewritten engine to save CPU cycles when CL2 reads the rungs
* Prepared for inclusion in the future of the Instruction List language
* New project file format
* Possibility to extend the engine with external libraries

I mainly aim the Linux targets, especially the Raspberry Pi platform, so for now, CL2 is not guaranteed to work under Windows or any other OS.

The next big work is the replacement of GTK3 GUI by wxWidgets, as GTK3 is obsolete (and I know much better wxWidgets than GTK4...). 
For now, I have made the very first tests to prove that wxWidgets-based GUI will work, but I can't give any time frame for this major evolution
