; HD65A.ASM

; This file tests header file usage for the specified processor.

	LIST	P=16C65A
	INCLUDE	"p16c65a.inc"

 	DATA	_CP_ALL, 0x00CF		; This changes per device
	DATA	_CP_75, 0X15DF
	DATA	_CP_50, 0X2AEF
	DATA	_CP_OFF, 0X3FFF
	DATA	_BODEN_ON, 0X3FFF
	DATA	_BODEN_OFF, 0X3FBF
	DATA	_PWRTE_ON, 0x3FF7	; This changes per device
	DATA	_PWRTE_OFF, 0X3FFF
	DATA	_WDT_ON, 0X3FFF
	DATA	_WDT_OFF, 0X3FFB
	DATA	_LP_OSC, 0X3FFC
	DATA	_XT_OSC, 0X3FFD
	DATA	_HS_OSC, 0X3FFE
	DATA	_RC_OSC, 0X3FFF

	DATA	INDF, 0			;Register Files
	DATA	TMR0, 1
	DATA	PCL, 2
	DATA	STATUS, 3
	DATA	FSR, 4
	DATA	PORTA, 5
	DATA	PORTB, 6
	DATA	PORTC, 7		; Processor Specific
	DATA	PORTD, 8		; Register Files
	DATA	PORTE, 9
	DATA	PCLATH, 0x0A
	DATA	INTCON, 0x0B
	DATA	PIR1, 0XC
	DATA	PIR2, 0XD
	DATA	TMR1L, 0XE
	DATA	TMR1H, 0XF
	DATA	T1CON, 0X10
	DATA	TMR2, 0X11
	DATA	T2CON, 0X12
	DATA	SSPBUF, 0X13
	DATA	SSPCON, 0X14
	DATA	CCPR1L, 0X15
	DATA	CCPR1H, 0X16
	DATA	CCP1CON, 0X17
	DATA	RCSTA, 0X18
	DATA	TXREG, 0X19
	DATA	RCREG, 0X1A
	DATA	CCPR2L, 0X1B
	DATA	CCPR2H, 0X1C
	DATA	CCP2CON, 0X1D

	DATA	OPTION_REG, 0x81
	DATA	TRISA, 0X85
	DATA	TRISB, 0X86
	DATA	TRISC, 0X87
	DATA	TRISD, 0X88
	DATA	TRISE, 0X89
	DATA	PIE1, 0X8C
	DATA	PIE2, 0X8D
	DATA	PCON, 0X8E
	DATA	PR2, 0X92
	DATA	SSPADD, 0X93
	DATA	SSPSTAT, 0X94
	DATA	TXSTA, 0X98
	DATA	SPBRG, 0X99

	
	DATA	IRP, 7			;STATUS
	DATA	RP1, 6
	DATA	RP0, 5
	DATA	NOT_TO, 4
	DATA	NOT_PD, 3
	DATA	Z, 2
	DATA	DC, 1
	DATA	C, 0

	DATA	GIE, 7			; INTCON
	DATA	PEIE, 6
	DATA	T0IE, 5
	DATA	INTE, 4
	DATA	RBIE, 3
	DATA	T0IF, 2
	DATA	INTF, 1
	DATA	RBIF, 0	

	DATA	PSPIF, 7		; PIR1
	DATA	RCIF, 5
	DATA	TXIF, 4
	DATA	SSPIF, 3
	DATA	CCP1IF, 2
	DATA	TMR2IF, 1
	DATA	TMR1IF, 0

	DATA	CCP2IF, 0		; PIR2

	DATA	T1CKPS1, 5		; T1CON
	DATA	T1CKPS0, 4
	DATA	T1OSCEN, 3
	DATA	T1INSYNC, 2
	DATA	TMR1CS, 1
	DATA	TMR1ON, 0

	DATA	TOUTPS3, 6		; T2CON
	DATA	TOUTPS2, 5
	DATA	TOUTPS1, 4
	DATA	TOUTPS0, 3
	DATA	TMR2ON, 2
	DATA	T2CKPS1, 1
	DATA	T2CKPS0, 0

	DATA	WCOL, 7			; SSPCON
	DATA	SSPOV, 6	
	DATA	SSPEN, 5
	DATA	CKP, 4
	DATA	SSPM3, 3
	DATA	SSPM2, 2
	DATA	SSPM1, 1
	DATA	SSPM0, 0

	DATA	CCP1X, 5		; CCP1CON
	DATA	CCP1Y, 4
	DATA	CCP1M3, 3
	DATA	CCP1M2, 2
	DATA	CCP1M1, 1
	DATA	CCP1M0, 0

	DATA	SPEN, 7			; RCSTA
	DATA	RC9, 6
	DATA	NOT_RC8, 6
	DATA	RC8_9, 6
	DATA	SREN, 5
	DATA	CREN, 4
	DATA	FERR, 2
	DATA	OERR, 1
	DATA	RCD8, 0

	DATA	CCP2X, 5		; CCP2CON
	DATA	CCP2Y, 4
	DATA	CCP2M3, 3
	DATA	CCP2M2, 2
	DATA	CCP2M1, 1
	DATA	CCP2M0, 0


	DATA	NOT_RBPU, 7		; OPTION
	DATA	INTEDG, 6
	DATA	T0CS, 5
	DATA	T0SE, 4
	DATA	PSA, 3
	DATA	PS2, 2
	DATA	PS1, 1
	DATA	PS0, 0

	DATA	IBF, 7			; TRISE
	DATA	OBF, 6
	DATA	IBOV, 5
	DATA	PSPMODE, 4
	DATA	TRISE2, 2
	DATA	TRISE1, 1
	DATA	TRISE0, 0

	DATA	PSPIE, 7		; PIE1
	DATA	RCIE, 5
	DATA	TXIE, 4
	DATA	SSPIE, 3
	DATA	CCP1IE, 2
	DATA	TMR2IE, 1
	DATA	TMR1IE, 0

	DATA	CCP2IE, 0		; PIE2

	DATA	NOT_POR, 1		; PCON
	DATA	NOT_BO, 0

	DATA	D, 5			; SSPSTAT
	DATA	I2C_DATA, 5
	DATA	NOT_A, 5
	DATA	NOT_ADDRESS, 5
	DATA	D_A, 5
	DATA	DATA_ADDRESS, 5
	DATA	P, 4
	DATA	I2C_STOP, 4
	DATA	S, 3
	DATA	I2C_START, 3
	DATA	R, 2
	DATA	I2C_READ, 2
	DATA	NOT_W, 2
	DATA	NOT_WRITE, 2
	DATA	R_W, 2
	DATA	READ_WRITE, 2
	DATA	UA, 1
	DATA	BF, 0

	DATA	CSRC, 7			; TXSTA
	DATA	TX9, 6
	DATA	NOT_TX8, 6
	DATA	TX8_9, 6
	DATA	TXEN, 5
	DATA 	SYNC, 4
	DATA	BRGH, 2
	DATA	TRMT, 1
	DATA	TXD8, 0

	END
