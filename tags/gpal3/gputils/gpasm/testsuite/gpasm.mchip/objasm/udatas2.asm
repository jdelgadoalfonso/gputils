; UDATAS2.ASM

; This file tests illegal usage of the UDATA_SHR directive.
; It should be placed in the list comparison section for
; object files.

	list	p=17c44

Data1	udata_shr			; Two segments, same name
	res		1
Data1	udata_shr
	res		1

Data2	udata_shr	xyz		; Illegal address

Data3	udata_shr
	nop				; Program code
	db		1		; Data byte

	end