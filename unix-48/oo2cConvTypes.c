/* Ofront+ 1.0 -sC -48 */
#include "SYSTEM.oh"

typedef
  struct oo2cConvTypes_ScanDesc *oo2cConvTypes_ScanState;

typedef
  struct oo2cConvTypes_ScanDesc {
    void (*p)(CHAR, SHORTINT*, oo2cConvTypes_ScanState*);
  } oo2cConvTypes_ScanDesc;



export void **oo2cConvTypes_ScanDesc__typ;



/*============================================================================*/

__TDESC(oo2cConvTypes_ScanDesc__desc, 2, 0) = {__TDFLDS("ScanDesc", 4), {-4}};

export void *oo2cConvTypes__init (void)
{
  __DEFMOD;
  __REGMOD("oo2cConvTypes", 0);
  __INITYP(oo2cConvTypes_ScanDesc, oo2cConvTypes_ScanDesc, 0);
/* BEGIN */
  __ENDMOD;
}
