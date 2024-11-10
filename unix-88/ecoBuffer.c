/* Ofront+ 1.0 -sC -88 */
#include "SYSTEM.oh"


export BOOLEAN ecoBuffer_nonempty, ecoBuffer_nonfull;
static INTEGER ecoBuffer_in, ecoBuffer_out, ecoBuffer_n;
static INTEGER ecoBuffer_buf[100];


export void ecoBuffer_get (INTEGER *x);
export void ecoBuffer_put (INTEGER x);


/*============================================================================*/

void ecoBuffer_put (INTEGER x)
{
  if (ecoBuffer_n < 100) {
    ecoBuffer_buf[__X(ecoBuffer_in, 100, (CHAR*)"ecoBuffer", 2322)] = x;
    ecoBuffer_in = __MOD(ecoBuffer_in + 1, 100);
    ecoBuffer_n += 1;
    ecoBuffer_nonfull = ecoBuffer_n < 100;
    ecoBuffer_nonempty = 1;
  }
}

/*----------------------------------------------------------------------------*/
void ecoBuffer_get (INTEGER *x)
{
  if (ecoBuffer_n > 0) {
    *x = ecoBuffer_buf[__X(ecoBuffer_out, 100, (CHAR*)"ecoBuffer", 4115)];
    ecoBuffer_out = __MOD(ecoBuffer_out + 1, 100);
    ecoBuffer_n -= 1;
    ecoBuffer_nonempty = ecoBuffer_n > 0;
    ecoBuffer_nonfull = 1;
  }
}

/*----------------------------------------------------------------------------*/

export void *ecoBuffer__init (void)
{
  __DEFMOD;
  __REGMOD("ecoBuffer", 0);
/* BEGIN */
  ecoBuffer_n = 0;
  ecoBuffer_in = 0;
  ecoBuffer_out = 0;
  ecoBuffer_nonempty = 0;
  ecoBuffer_nonfull = 1;
  __ENDMOD;
}
