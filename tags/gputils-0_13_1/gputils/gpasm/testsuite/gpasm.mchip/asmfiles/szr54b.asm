; SZR54B.ASM

; This file tests for the processor-specific items for the selected
; processor.

	LIST	P=16CR54B, R=HEX

MAXROM	EQU	01FF
MAXRAM	EQU	001F

	RETLW	12		; 0812 = 12-BIT
				; 3412 = 14-BIT
				; B612 = 16-BIT

	MOVWF	MAXRAM		; OK
	MOVWF	MAXRAM+1	; MESSAGE

	ORG	MAXROM
	NOP			; OK
	NOP			; ERROR

	END
