; This file creates a block of data in program memory that exceeds
; the size of one page.

  processor 16f877a

  code
  fill 0xff, 0x801
  
  end
