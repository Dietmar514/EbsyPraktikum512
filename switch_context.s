  AREA  asmcode, CODE, READONLY    

switch_context PROC

	EXPORT switch_context
	
	MOV sp, r0
	PUSH {lr}
	PUSH {r4-r12}
	
	MOV sp, r1
	POP {r4-r12}
	POP {pc}
    BX LR
	ENDP
	END