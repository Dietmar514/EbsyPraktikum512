  AREA  asmcode, CODE, READONLY    

switch_context PROC

   EXPORT switch_context
   
   MOV sp, r0
   PUSH {r8-r12}
   PUSH {r4-r7, pc}

   MOV sp, r1
   POP {r8-r12}
   POP {r4-r7, pc}
   
ENDP