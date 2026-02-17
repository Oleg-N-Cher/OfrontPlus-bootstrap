/* Ofront+ 1.0 -s2 -44 */
#include "SYSTEM.oh"
#include "arOut.oh"
#include "arStrings.oh"




export void arPath_BaseName (CHAR *path, INTEGER path__len, CHAR *base, INTEGER base__len);
export void arPath_DirName (CHAR *path, INTEGER path__len, CHAR *dir, INTEGER dir__len);
export void arPath_ExtName (CHAR *path, INTEGER path__len, CHAR *ext, INTEGER ext__len);


/*============================================================================*/

void arPath_DirName (CHAR *path, INTEGER path__len, CHAR *dir, INTEGER dir__len)
{
  INTEGER index;
  index = arStrings_LastIndexOf((void*)path, path__len, '/', -1);
  if (index >= 0) {
    arStrings_Extract((void*)path, path__len, 0, index, (void*)dir, dir__len);
  } else {
    dir[0] = 0x00;
  }
}

/*----------------------------------------------------------------------------*/
void arPath_BaseName (CHAR *path, INTEGER path__len, CHAR *base, INTEGER base__len)
{
  INTEGER index;
  index = arStrings_LastIndexOf((void*)path, path__len, '/', -1);
  if (index >= 0) {
    arStrings_Extract((void*)path, path__len, index + 1, base__len, (void*)base, base__len);
  } else {
    arStrings_Assign((void*)path, path__len, (void*)base, base__len);
  }
}

/*----------------------------------------------------------------------------*/
void arPath_ExtName (CHAR *path, INTEGER path__len, CHAR *ext, INTEGER ext__len)
{
  INTEGER index;
  index = arStrings_LastIndexOf((void*)path, path__len, '.', -1);
  if (index >= 0 && arStrings_IndexOf((void*)path, path__len, '/', index) < 0) {
    arStrings_Extract((void*)path, path__len, index, ext__len, (void*)ext, ext__len);
  } else {
    ext[0] = 0x00;
  }
}

/*----------------------------------------------------------------------------*/

export void *arPath__init (void)
{
  __DEFMOD;
  __IMPORT(arOut__init);
  __IMPORT(arStrings__init);
  __REGMOD("arPath", 0);
/* BEGIN */
  __ENDMOD;
}
