; FILES1.ASM

; This file tests the generation of the various output files.  If you
; are generating an object file, also assemble with the option /dMakeObj.

	LIST	P=16C54

#define Def1	1

#ifdef MakeObj
	CODE
#endif

Label1

#ifdef MakeObj
	EXTERN		Extern1
Global1 = 1
Global2 = 2
	GLOBAL		Global1, Global2
	DATA		Extern1, Global1, Global2
#endif

Label2

MyMac	MACRO	Label, Num
	LOCAL	MacLoc=Num
	WHILE MacLoc > 0
Label#v(MacLoc)	DATA	Num, MacLoc
	   MacLoc--
	ENDW
	ENDM


	CONSTANT	Const1=111, Const2=222
	VARIABLE	Var1, Var2 = 22

	Var3 = 33

	DATA	Def1
	DATA	Const1, Const2
	DATA	Var1, Var2, Var3

	Var3++
	DATA	Var3

Label3

	MyMac	CallOne, 3
	MyMac	CallTwo, 2

        ERROR   "This is my error message"
	ADDWF	0x20, 0			; Generates a warning
	MESSG	"This is my message

;***** Test for SSR 1553

#include "files1.inc"

	OutSideMac

;***** End Test

	END
