  AREA  asmcode, CODE, READONLY    

first_context PROC


	EXPORT first_context
	MSR PSP, R0
	STMDB R0!, {R4-R11}
	BX LR
	ENDP
	END