/* Ofront+ 1.0 -sxpC -88 */
#include "SYSTEM.oh"

typedef
  CHAR *CmdArgs_ArgPtr;

typedef
  CmdArgs_ArgPtr *CmdArgs_ArgVec;

typedef
  CHAR *CmdArgs_EnvPtr;

typedef
  struct CmdArgs_Environ__rec *CmdArgs_Environ;

typedef
  struct CmdArgs_Environ__rec {
    CmdArgs_EnvPtr e;
  } CmdArgs_Environ__rec;


export INTEGER CmdArgs_Count;


export INTEGER CmdArgs_EnvCount (void);
export void CmdArgs_Get (INTEGER n, CHAR *val, INTEGER val__len);
export void CmdArgs_GetEnv (CHAR *var, INTEGER var__len, CHAR *val, INTEGER val__len);
export void CmdArgs_GetEnvN (INTEGER n, CHAR *s, INTEGER s__len);
export void CmdArgs_GetInt (INTEGER n, INTEGER *val);
export INTEGER CmdArgs_Pos (CHAR *s, INTEGER s__len);

extern INTEGER SYSTEM_argc;
extern void *SYSTEM_argv;
extern void **environ;
#define CmdArgs_argc()  SYSTEM_argc
#define CmdArgs_argv()  (CmdArgs_ArgVec)SYSTEM_argv
#define CmdArgs_environ()  (CmdArgs_Environ)environ
#define CmdArgs_getenv(var, var__len)  (CmdArgs_EnvPtr)getenv((char*)var)
#include <stdlib.h>
#define CmdArgs_nextenviron(p, n)  p + n

/*============================================================================*/

void CmdArgs_Get (INTEGER n, CHAR *val, INTEGER val__len)
{
  CmdArgs_ArgVec av;
  if (n < CmdArgs_argc()) {
    av = CmdArgs_argv();
    if (val__len > __CSTRLEN((av)[n])) {
      __STRCOPYCC((av)[n], val, val__len, (CHAR*)"CmdArgs", 7220);
    }
  }
}

/*----------------------------------------------------------------------------*/
void CmdArgs_GetInt (INTEGER n, INTEGER *val)
{
  CHAR s[64];
  INTEGER k, d, i;
  s[0] = 0x00;
  CmdArgs_Get(n, (void*)s, 64);
  i = 0;
  if (s[0] == '-') {
    i = 1;
  }
  k = 0;
  d = (INTEGER)s[i] - 48;
  while (d >= 0 && d <= 9) {
    k = k * 10 + d;
    i += 1;
    d = (INTEGER)s[i] - 48;
  }
  if (s[0] == '-') {
    k = -k;
    i -= 1;
  }
  if (i > 0) {
    *val = k;
  }
}

/*----------------------------------------------------------------------------*/
INTEGER CmdArgs_Pos (CHAR *s, INTEGER s__len)
{
  INTEGER i;
  CHAR arg[256];
  i = 0;
  CmdArgs_Get(i, (void*)arg, 256);
  while (i < CmdArgs_argc() && __STRCMPCC(s, arg, 256, (CHAR*)"CmdArgs", 12066) != 0) {
    i += 1;
    CmdArgs_Get(i, (void*)arg, 256);
  }
  return i;
}

/*----------------------------------------------------------------------------*/
void CmdArgs_GetEnv (CHAR *var, INTEGER var__len, CHAR *val, INTEGER val__len)
{
  CmdArgs_EnvPtr p;
  p = CmdArgs_getenv(var, var__len);
  if (p != NIL) {
    __STRCOPYCC(p, val, val__len, (CHAR*)"CmdArgs", 15134);
  } else {
    val[0] = 0x00;
  }
}

/*----------------------------------------------------------------------------*/
INTEGER CmdArgs_EnvCount (void)
{
  INTEGER count;
  CmdArgs_Environ p;
  p = CmdArgs_environ();
  count = 0;
  while (p->e != NIL) {
    count += 1;
    p = CmdArgs_nextenviron(p, 1);
  }
  return count;
}

/*----------------------------------------------------------------------------*/
void CmdArgs_GetEnvN (INTEGER n, CHAR *s, INTEGER s__len)
{
  CmdArgs_Environ p;
  p = CmdArgs_environ();
  p = CmdArgs_nextenviron(p, n);
  if (p->e != NIL) {
    __STRCOPYCC(p->e, s, s__len, (CHAR*)"CmdArgs", 20768);
  } else {
    s[0] = 0x00;
  }
}

/*----------------------------------------------------------------------------*/

export void *CmdArgs__init (void)
{
  __DEFMOD;
  __REGMOD("CmdArgs", 0);
/* BEGIN */
  CmdArgs_Count = CmdArgs_argc() - 1;
  __ENDMOD;
}
