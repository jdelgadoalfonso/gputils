        LIST
; P18CXXX.INC  Standard Header File, Version 1.00   Microchip Technology, Inc.
        NOLIST

; This header file defines the list of processor specific header files.  It is
; used to include the appropriate header file.

; Note that the processor must be selected before this file is included.  The
; processor may be selected the following ways:

; Using the PIC18C452 as an example
;       1. Command line switch:
;               C:\ MPASM MYFILE.ASM /PIC18C452
;       2. LIST directive in the source file
;               LIST   P=PIC18C452
;       3. Processor Type entry in the MPASM full-screen interface
;       4. Setting the processor in the MPLAB Project Dialog

;==========================================================================
;
;       Revision History
;
;==========================================================================
; Rev:   Date:         Details:                                        Who:
; 1.10   06/13/02      Removing 18F010/18F020    (pas)
;==========================================================================
;
;       Verify Processor
;
;==========================================================================

  IFDEF __18CXX
     INCLUDE <P18C452.INC>
  ENDIF
  IFDEF __18C242
     INCLUDE <P18C242.INC>
  ENDIF
  IFDEF __18F242
     INCLUDE <P18F242.INC>
  ENDIF
  IFDEF __18F248
     INCLUDE <P18F248.INC>
  ENDIF
  IFDEF __18C252
     INCLUDE <P18C252.INC>
  ENDIF
  IFDEF __18F252
     INCLUDE <P18F252.INC>
  ENDIF
  IFDEF __18F258
     INCLUDE <P18F258.INC>
  ENDIF
  IFDEF __18C442
     INCLUDE <P18C442.INC>
  ENDIF
  IFDEF __18F442
     INCLUDE <P18F442.INC>
  ENDIF
  IFDEF __18F448
     INCLUDE <P18F448.INC>
  ENDIF
  IFDEF __18C452
     INCLUDE <P18C452.INC>
  ENDIF
  IFDEF __18F452
     INCLUDE <P18F452.INC>
  ENDIF
  IFDEF __18F458
     INCLUDE <P18F458.INC>
  ENDIF
  IFDEF __18C601
     INCLUDE <P18C601.INC>
  ENDIF
  IFDEF __18C658
     INCLUDE <P18C658.INC>
  ENDIF
  IFDEF __18C801
     INCLUDE <P18C801.INC>
  ENDIF
  IFDEF __18C858
     INCLUDE <P18C858.INC>
  ENDIF
  IFDEF __18F1220
     INCLUDE <P18F1220.INC>
  ENDIF
  IFDEF __18F1320
     INCLUDE <P18F1320.INC>
  ENDIF
  IFDEF __18F2220
     INCLUDE <P18F2220.INC>
  ENDIF
  IFDEF __18F2320
     INCLUDE <P18F2320.INC>
  ENDIF
  IFDEF __18F4220
     INCLUDE <P18F4220.INC>
  ENDIF
  IFDEF __18F4320
     INCLUDE <P18F4320.INC>
  ENDIF
  IFDEF __18F6520
     INCLUDE <P18F6520.INC>
  ENDIF
  IFDEF __18F6620
     INCLUDE <P18F6620.INC>
  ENDIF
  IFDEF __18F6720
     INCLUDE <P18F6720.INC>
  ENDIF
  IFDEF __18F8520
     INCLUDE <P18F8520.INC>
  ENDIF
  IFDEF __18F8620
     INCLUDE <P18F8620.INC>
  ENDIF
  IFDEF __18F8720
     INCLUDE <P18F8720.INC>
  ENDIF
  IFDEF __18F2439
     INCLUDE <P18F2439.INC>
  ENDIF
  IFDEF __18F2539
     INCLUDE <P18F2539.INC>
  ENDIF
  IFDEF __18F4439
     INCLUDE <P18F4439.INC>
  ENDIF
  IFDEF __18F4539
     INCLUDE <P18F4539.INC>
  ENDIF
  IFDEF __18F8680
     INCLUDE <P18F8680.INC>
  ENDIF
  IFDEF __18F6680
     INCLUDE <P18F6680.INC>
  ENDIF
  IFDEF __18F8585
     INCLUDE <P18F8585.INC>
  ENDIF
  IFDEF __18F6585
     INCLUDE <P18F6585.INC>
  ENDIF
  IFDEF __18F6621
     INCLUDE <P18F6621.INC>
  ENDIF
  IFDEF __18F8621
     INCLUDE <P18F8621.INC>
  ENDIF
  IFDEF __18F6525
     INCLUDE <P18F6525.INC>
  ENDIF
  IFDEF __18F8525
     INCLUDE <P18F8525.INC>
  ENDIF
  IFDEF __18F2331
     INCLUDE <P18F2331.INC>
  ENDIF
  IFDEF __18F2431
     INCLUDE <P18F2431.INC>
  ENDIF
  IFDEF __18F4331
     INCLUDE <P18F4331.INC>
  ENDIF
  IFDEF __18F4431
     INCLUDE <P18F4431.INC>
  ENDIF
  IFDEF __18F2515
     INCLUDE <P18F2515.INC>
  ENDIF
  IFDEF __18F2525
     INCLUDE <P18F2525.INC>
  ENDIF
  IFDEF __18F2610
     INCLUDE <P18F2610.INC>
  ENDIF
  IFDEF __18F2620
     INCLUDE <P18F2620.INC>
  ENDIF
  IFDEF __18F4515
     INCLUDE <P18F4515.INC>
  ENDIF
  IFDEF __18F4525
     INCLUDE <P18F4525.INC>
  ENDIF
  IFDEF __18F4610
     INCLUDE <P18F4610.INC>
  ENDIF
  IFDEF __18F4620
     INCLUDE <P18F4620.INC>
  ENDIF
  IFDEF __18F6410
     INCLUDE <P18F6410.INC>
  ENDIF
  IFDEF __18F6490
     INCLUDE <P18F6490.INC>
  ENDIF
  IFDEF __18F8410
     INCLUDE <P18F8410.INC>
  ENDIF
  IFDEF __18F8490
     INCLUDE <P18F8490.INC>
  ENDIF
  IFDEF __18F2585
     INCLUDE <P18F2585.INC>
  ENDIF
  IFDEF __18F2680
     INCLUDE <P18F2680.INC>
  ENDIF
  IFDEF __18F2681
     INCLUDE <P18F2681.INC>
  ENDIF
  IFDEF __18F4585
     INCLUDE <P18F4585.INC>
  ENDIF
  IFDEF __18F4680
     INCLUDE <P18F4680.INC>
  ENDIF
  IFDEF __18F4681
     INCLUDE <P18F4681.INC>
  ENDIF
  IFDEF __18F2510
     INCLUDE <P18F2510.INC>
  ENDIF
  IFDEF __18F2520
     INCLUDE <P18F2520.INC>
  ENDIF
  IFDEF __18F4510
     INCLUDE <P18F4510.INC>
  ENDIF
  IFDEF __18F4520
     INCLUDE <P18F4520.INC>
  ENDIF
  IFDEF __18F2455
     INCLUDE <P18F2455.INC>
  ENDIF
  IFDEF __18F2550
     INCLUDE <P18F2550.INC>
  ENDIF
  IFDEF __18F4455
     INCLUDE <P18F4455.INC>
  ENDIF
  IFDEF __18F4550
     INCLUDE <P18F4550.INC>
  ENDIF