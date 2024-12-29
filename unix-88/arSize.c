/* Ofront+ 1.0 -s2 -88 */
#include "SYSTEM.oh"




export INTEGER arSize_Max (INTEGER a, INTEGER b);
export REAL arSize_MaxLReal (REAL a, REAL b);
export SHORTREAL arSize_MaxReal (SHORTREAL a, SHORTREAL b);
export INTEGER arSize_Min (INTEGER a, INTEGER b);
export REAL arSize_MinLReal (REAL a, REAL b);
export SHORTREAL arSize_MinReal (SHORTREAL a, SHORTREAL b);


/*============================================================================*/

INTEGER arSize_Min (INTEGER a, INTEGER b)
{
  if (a < b) {
    return a;
  } else {
    return b;
  }
  __RETCHK((CHAR*)"arSize", 1829);
}

/*----------------------------------------------------------------------------*/
INTEGER arSize_Max (INTEGER a, INTEGER b)
{
  if (a > b) {
    return a;
  } else {
    return b;
  }
  __RETCHK((CHAR*)"arSize", 3109);
}

/*----------------------------------------------------------------------------*/
SHORTREAL arSize_MinReal (SHORTREAL a, SHORTREAL b)
{
  if (a < b) {
    return a;
  } else {
    return b;
  }
  __RETCHK((CHAR*)"arSize", 4389);
}

/*----------------------------------------------------------------------------*/
SHORTREAL arSize_MaxReal (SHORTREAL a, SHORTREAL b)
{
  if (a > b) {
    return a;
  } else {
    return b;
  }
  __RETCHK((CHAR*)"arSize", 5669);
}

/*----------------------------------------------------------------------------*/
REAL arSize_MinLReal (REAL a, REAL b)
{
  if (a < b) {
    return a;
  } else {
    return b;
  }
  __RETCHK((CHAR*)"arSize", 6949);
}

/*----------------------------------------------------------------------------*/
REAL arSize_MaxLReal (REAL a, REAL b)
{
  if (a > b) {
    return a;
  } else {
    return b;
  }
  __RETCHK((CHAR*)"arSize", 8229);
}

/*----------------------------------------------------------------------------*/

export void *arSize__init (void)
{
  __DEFMOD;
  __REGMOD("arSize", 0);
/* BEGIN */
  __ENDMOD;
}
