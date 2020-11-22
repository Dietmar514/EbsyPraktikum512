#ifndef _FIRST_CONTEXT_H
   #define _SWTICH_CONTEXT_H


#include <stdint.h>

/*************************************************************************/
/* -------------- E X P O R T E D   D E F I N I T I O N S -------------- */
/*************************************************************************/


/*  - T y p e s                                                          */


/*  - C o n s t a n t s                                                  */


/*  - V a r i a b l e s                                                  */



/*  - M a c r o s                                                        */


/*  - F l a g s / B i t  M a s k s                                       */


/*  - F u n c t i o n  P r o t o t y p e s                               */

   void  switch_context(uint32_t* p_old_stack, uint32_t* p_new_stack);


#endif  // _SWTICH_CONTEXT_H
