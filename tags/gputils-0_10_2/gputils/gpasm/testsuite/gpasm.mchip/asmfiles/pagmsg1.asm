; PAGWRN1.ASM

	LIST	P=16C77

	ORG	0
PAGE0_SUBROUTINE
	CALL	PAGE0_SUBROUTINE
	CALL	PAGE1_SUBROUTINE
	CALL	PAGE2_SUBROUTINE
	CALL	PAGE3_SUBROUTINE

	ORG	0X800
PAGE1_SUBROUTINE
	CALL	PAGE0_SUBROUTINE
	CALL	PAGE1_SUBROUTINE
	CALL	PAGE2_SUBROUTINE
	CALL	PAGE3_SUBROUTINE

	ORG	0X1000
PAGE2_SUBROUTINE
	CALL	PAGE0_SUBROUTINE
	CALL	PAGE1_SUBROUTINE
	CALL	PAGE2_SUBROUTINE
	CALL	PAGE3_SUBROUTINE

	ORG	0X1800
PAGE3_SUBROUTINE
	CALL	PAGE0_SUBROUTINE
	CALL	PAGE1_SUBROUTINE
	CALL	PAGE2_SUBROUTINE
	CALL	PAGE3_SUBROUTINE

	END



