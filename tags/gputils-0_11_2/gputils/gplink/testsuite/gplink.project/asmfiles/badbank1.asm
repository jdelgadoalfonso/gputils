; This file creates a block of file registers that exceeds the 
; size of one bank.

  processor 16f877a

.udata_badudata1 udata
too_big_array res 0x60
  
  end
