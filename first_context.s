  AREA  asmcode, CODE, READONLY    

first_context PROC


	EXPORT first_context
	MSR PSP, R0
	BX LR
	ENDP
	END