/* Ofront+ 1.0 -sC -48 */
#include "SYSTEM.oh"


static INTEGER oo2cRandomNumbers_z;


export void oo2cRandomNumbers_GetSeed (INTEGER *seed);
static void oo2cRandomNumbers_NextRND (void);
export void oo2cRandomNumbers_PutSeed (INTEGER seed);
export INTEGER oo2cRandomNumbers_RND (INTEGER range);
export SHORTREAL oo2cRandomNumbers_Random (void);


/*============================================================================*/

void oo2cRandomNumbers_GetSeed (INTEGER *seed)
{
  *seed = oo2cRandomNumbers_z;
}

/*----------------------------------------------------------------------------*/
void oo2cRandomNumbers_PutSeed (INTEGER seed)
{
  seed = __MOD(seed, 2147483647);
  if (seed == 0) {
    oo2cRandomNumbers_z = 1;
  } else {
    oo2cRandomNumbers_z = seed;
  }
}

/*----------------------------------------------------------------------------*/
static void oo2cRandomNumbers_NextRND (void)
{
  INTEGER lo, hi, test;
  hi = __DIV(oo2cRandomNumbers_z, 127773);
  lo = __MOD(oo2cRandomNumbers_z, 127773);
  test = 16807 * lo - 2836 * hi;
  if (test > 0) {
    oo2cRandomNumbers_z = test;
  } else {
    oo2cRandomNumbers_z = test + 2147483647;
  }
}

INTEGER oo2cRandomNumbers_RND (INTEGER range)
{
  oo2cRandomNumbers_NextRND();
  return __MODF(oo2cRandomNumbers_z, range);
}

/*----------------------------------------------------------------------------*/
SHORTREAL oo2cRandomNumbers_Random (void)
{
  oo2cRandomNumbers_NextRND();
  return (SHORTREAL)((REAL)(oo2cRandomNumbers_z - 1) * 4.6566128774142015e-10);
}

/*----------------------------------------------------------------------------*/

export void *oo2cRandomNumbers__init (void)
{
  __DEFMOD;
  __REGMOD("oo2cRandomNumbers", 0);
/* BEGIN */
  oo2cRandomNumbers_z = 1;
  __ENDMOD;
}
