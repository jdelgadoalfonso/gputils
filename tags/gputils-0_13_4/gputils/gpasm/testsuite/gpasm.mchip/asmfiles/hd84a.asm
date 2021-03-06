; HD84A.ASM

; This file tests header file usage for the specified processor.

        LIST    P=16F84A
        INCLUDE "p16f84a.inc"



        DATA    _CP_ON,         000F
        DATA    _CP_OFF,        3FFF
        DATA    _PWRTE_ON,      3FF7
        DATA    _PWRTE_OFF,     3FF7
        DATA    _WDT_ON,        3FFF
        DATA    _WDT_OFF,       3FFB
        DATA    _LP_OSC,        3FFC
        DATA    _XT_OSC,        3FFD
        DATA    _HS_OSC,        3FFE
        DATA    _RC_OSC,        3FFF


	DATA    INDF, 0                 ;Register Files
	DATA    TMR0, 1
	DATA    PCL, 2
	DATA    STATUS, 3
	DATA    FSR, 4
	DATA    PORTA, 5
	DATA    PORTB, 6
	DATA    PCLATH, 0x0A
	DATA    INTCON, 0x0B
	DATA    OPTION_REG, 0x81
	DATA    TRISA, 0X85
	DATA    TRISB, 0X86

	DATA    EEDATA, 8               ; Processor-specific
	DATA    EEADR, 9                ; Register Files
	DATA    EECON1, 0X88
	DATA    EECON2, 0X89

	DATA    EEIF, 4                 ; EECON1
	DATA    WRERR, 3
	DATA    WREN, 2
	DATA    WR, 1
	DATA    RD, 0

	DATA    GIE, 7                  ; INTCON
	DATA    EEIE, 6
	DATA    T0IE, 5
	DATA    INTE, 4
	DATA    RBIE, 3
	DATA    T0IF, 2
	DATA    INTF, 1
	DATA    RBIF, 0

	DATA    NOT_RBPU, 7             ; OPTION
	DATA    INTEDG, 6
	DATA    T0CS, 5
	DATA    T0SE, 4
	DATA    PSA, 3
	DATA    PS2, 2
	DATA    PS1, 1
	DATA    PS0, 0


	DATA    IRP, 7                  ;STATUS
	DATA    RP1, 6
	DATA    RP0, 5
	DATA    NOT_TO, 4
	DATA    NOT_PD, 3
	DATA    Z, 2
	DATA    DC, 1
	DATA    C, 0

        END
