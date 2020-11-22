  AREA  asmcode, CODE, READONLY    

first_context PROC

   EXPORT first_context
   MOV sp, r0
   POP {r8-r12}
   POP {r4-r7, pc}
   ENDP





