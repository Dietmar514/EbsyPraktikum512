  AREA  asmcode, CODE, READONLY    

    extern curr
    extern next

PendSV_Handler PROC

	EXPORT PendSV_Handler
		
	LDR R3, =curr
	MRS R0, PSP
	STMDB R0!, {R4-R11}	
	LDR R3, [R3]
	STR R0, [R3]
	
	LDR R0, =next
	LDR R1, [R0]
	MSR PSP, R1
	LDMIA R0!, {R4-R11}
	LDR R0, =0xFFFFFFFD
    BX R0
	ENDP
	END
	

