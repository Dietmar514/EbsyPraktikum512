  AREA  asmcode, CODE, READONLY    

first_context PROC

	EXPORT first_context
	MOV sp, r0
	PUSH {r1}
	PUSH {r4-r12}
	bx lr
	ENDP
	END