; SZ554.ASM

; This file tests for the processor-specific items for the selected
; processor.

	LIST	P=16C554, R=HEX

MAXROM	EQU	01FF
MAXRAM	EQU	006F

	RETLW	12		; 0812 = 12-BIT
				; 3412 = 14-BIT
				; B612 = 16-BIT

	MOVWF	MAXRAM		; OK
	MOVWF	MAXRAM+1	; MESSAGE

	ORG	MAXROM
	NOP			; OK
	NOP			; ERROR

   IFDEF __16C84		; EE Processors
	ORG	2100
	FILL	33, 40		; OK
	DE	44		; ERROR
   ENDIF

	END
