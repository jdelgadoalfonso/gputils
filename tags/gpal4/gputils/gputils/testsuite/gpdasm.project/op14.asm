;  This file is used to test gpdasm with the 14 bit instruction set.

     list p=16c84,f=inhx8m

insn macro file 
     ADDLW 0xff
     ADDWF file,1 
     ANDLW 0xff
     ANDWF file,1
     BCF file,7
     BSF file,7
     BTFSC file,1
     BTFSS file,1
     CALL 0x100
     CLRF file
     CLRW
     CLRWDT
     COMF file,1
     DECF file,1
     DECFSZ file,1
     GOTO 0x100
     INCF file,1
     INCFSZ file,1
     IORLW 0xff
     IORWF file,1
     MOVF  file,1
     MOVLW 0xff
     MOVWF file
     NOP
     OPTION 
     RETFIE
     RETLW 0
     RETURN
     RLF file,1
     RRF file,1
     SLEEP
     SUBLW 0xff
     SUBWF file,1
     SWAPF file,1
     TRIS 5
     XORLW 0xff
     XORWF file,1
     endm

     org 0
     insn 10
     org 400
     insn 20
     org 800
     insn 25
     end
