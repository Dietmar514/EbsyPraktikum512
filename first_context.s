  AREA  asmcode, CODE, READONLY    

first_context PROC




	EXPORT first_context
	MOV sp, r0
	POP {r0-r12}
	
	POP {pc}
	BX LR
	ENDP
	END