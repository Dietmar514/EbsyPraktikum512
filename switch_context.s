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

	;lr 31, r4 30, r5 29, r6 28, r7 27, r8 26, r9 25, r10 24, r11 23, r12 22