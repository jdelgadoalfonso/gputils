; WHILE3.ASM

; This file tests illegal use of the WHILE directive.

	LIST	P=17C44, R=DEC

I = 1
	WHILE I = 0	; Illegal condition
	   NOP
	ENDW

I = 256+1
	WHILE I > 0	; Too many iterations
	   DATA	I
I--
	ENDW

I = 10
	WHILE I == 10	; Single pass, too many lines internal
	   DATA	1
	   DATA	2
	   DATA	3
	   DATA	4
	   DATA	5
	   DATA	6
	   DATA	7
	   DATA	8
	   DATA	9
	   DATA	10
	   DATA	11
	   DATA	12
	   DATA	13
	   DATA	14
	   DATA	15
	   DATA	16
	   DATA	17
	   DATA	18
	   DATA	19
	   DATA	20
	   DATA	21
	   DATA	22
	   DATA	23
	   DATA	24
	   DATA	25
	   DATA	26
	   DATA	27
	   DATA	28
	   DATA	29
	   DATA	30
	   DATA	31
	   DATA	32
	   DATA	33
	   DATA	34
	   DATA	35
	   DATA	36
	   DATA	37
	   DATA	38
	   DATA	39
	   DATA	40
	   DATA	41
	   DATA	42
	   DATA	43
	   DATA	44
	   DATA	45
	   DATA	46
	   DATA	47
	   DATA	48
	   DATA	49
	   DATA	50
	   DATA	51
	   DATA	52
	   DATA	53
	   DATA	54
	   DATA	55
	   DATA	56
	   DATA	57
	   DATA	58
	   DATA	59
	   DATA	60
	   DATA	61
	   DATA	62
	   DATA	63
	   DATA	64
	   DATA	65
	   DATA	66
	   DATA	67
	   DATA	68
	   DATA	69
	   DATA	70
	   DATA	71
	   DATA	72
	   DATA	73
	   DATA	74
	   DATA	75
	   DATA	76
	   DATA	77
	   DATA	78
	   DATA	79
	   DATA	80
	   DATA	81
	   DATA	82
	   DATA	83
	   DATA	84
	   DATA	85
	   DATA	86
	   DATA	87
	   DATA	88
	   DATA	89
	   DATA	90
	   DATA	91
	   DATA	92
	   DATA	93
	   DATA	94
	   DATA	95
	   DATA	96
	   DATA	97
	   DATA	98
	   DATA	99
	   DATA	100
I++
	ENDW

I = 1

	WHILE I != 0	; Nesting too deep
	WHILE I != 0
	WHILE I != 0
	WHILE I != 0
	WHILE I != 0
	WHILE I != 0
	WHILE I != 0
	WHILE I != 0
	WHILE I != 0
	   NOP		;*** Can't find nest error unless in execution path
I=0
	ENDW
	ENDW
	ENDW
	ENDW
	ENDW
	ENDW
	ENDW
	ENDW
	ENDW

	ENDW		; Unmatched ENDW

Label	WHILE	I != 0	; Illegal label
	ENDW		; (May give unmatched error)

	WHILE	I != 0
Label	ENDW		; Illegal label  **** Can't find this error currently
	ENDW		; (In case previous isn't taken)

	WHILE	I != 0

Label	ENDW		; Illegal label
	ENDW		; (In case previous isn't taken)

	WHILE		; No condition
	ENDW

	WHILE I == 0	; Unterminated WHILE
	   DATA	I

	END
