;LIST10D.ASM
;	This series of files tests symbol table and memory map
;	generation in the list file.

	list	p=16c54

	list	mm=off, st=off

	cblock	0
	   aa, bb, cc, dd, ee
	endc
	
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop

	end
