; PRR43.ASM

; This file tests the processor directive.

	PROCESSOR	17CR43

	RETLW	12		; 0812 = 12-BIT
				; 3412 = 14-BIT
				; B612 = 16-BIT

	END
