; HD642.ASM

; This file tests header file usage for the specified processor.

	LIST	P=16C642
	INCLUDE	"p16c642.inc"

 	DATA	_CP_ALL,	0x00CF	; This changes per device
	DATA	_CP_75,		0X15DF
	DATA	_CP_50,		0X2AEF
	DATA	_CP_OFF,	0X3FFF

	DATA	_MPEEN_ON,	0x3FFF
	DATA	_MPEEN_OFF,	0x3F7F

	DATA	_BODEN_ON,	0X3FFF
	DATA	_BODEN_OFF,	0X3FBF

	DATA	_PWRTE_ON,	0x3FF7	; This changes per device
	DATA	_PWRTE_OFF,	0X3FFF

	DATA	_WDT_ON,	0X3FFF
	DATA	_WDT_OFF,	0X3FFB

	DATA	_LP_OSC,	0X3FFC
	DATA	_XT_OSC,	0X3FFD
	DATA	_HS_OSC,	0X3FFE
	DATA	_RC_OSC,	0X3FFF

	DATA	INDF,		0	;Register Files
	DATA	TMR0,		1
	DATA	PCL,		2
	DATA	STATUS,		3
	DATA	FSR,		4
	DATA	PORTA,		5
	DATA	PORTB,		6
	DATA	PORTC,		0x07

	DATA	PCLATH,		0x0A
	DATA	INTCON,		0x0B
	DATA	PIR1,		0X0C	; Processor Specific
					;
	DATA	CMCON,		0X1F	; Register Files

	DATA	OPTION_REG,	0x81
	DATA	TRISA,		0X85
	DATA	TRISB,		0X86
	DATA	TRISC,		0x87
	DATA	PIE1,		0X8C
	DATA	PCON,		0X8E

	DATA	VRCON,		0X9F
	

	DATA	IRP,		7	; STATUS Bits
	DATA	RP1,		6
	DATA	RP0,		5
	DATA	NOT_TO,		4
	DATA	NOT_PD,		3
	DATA	Z,		2
	DATA	DC,		1
	DATA	C,		0

	DATA	GIE,		7	; INTCON
	DATA	PEIE,		6
	DATA	T0IE,		5
	DATA	INTE,		4
	DATA	RBIE,		3
	DATA	T0IF,		2
	DATA	INTF,		1
	DATA	RBIF,		0	

	DATA	CMIF,		6	; PIR1

	DATA	C2OUT,		7	; CMCON
	DATA	C1OUT,		6
	DATA	CIS,		3
	DATA	CM2,		2
	DATA	CM1,		1
	DATA	CM0,		0


	DATA	NOT_RBPU,	7	; OPTION
	DATA	INTEDG,		6
	DATA	T0CS,		5
	DATA	T0SE,		4
	DATA	PSA,		3
	DATA	PS2,		2
	DATA	PS1,		1
	DATA	PS0,		0

	DATA	CMIE,		6	; PIE1

	DATA	MPEEN,		7	; PCON
	DATA	NOT_PER,	2
	DATA	NOT_POR,	1
	DATA	NOT_BO,		0
	DATA	NOT_BOR,	0

	DATA	VREN,		7	; VRCON
	DATA	VROE,		6
	DATA	VRR,		5
	DATA	VR3,		3
	DATA	VR2,		2
	DATA	VR1,		1
	DATA	VR0,		0

	END
