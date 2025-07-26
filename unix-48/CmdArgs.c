/* Ofront+ 1.0 -sxpC -48 */
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
export BOOLEAN CmdArgs_Truncated;


export INTEGER CmdArgs_EnvCount (void);
export void CmdArgs_Get (INTEGER n, CHAR *val, INTEGER val__len);
export void CmdArgs_GetEnv (CHAR *var, INTEGER var__len, CHAR *val, INTEGER val__len);
export void CmdArgs_GetEnvN (INTEGER n, CHAR *val, INTEGER val__len);
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
  INTEGER i;
  val[0] = 0x00;
  CmdArgs_Truncated = 0;
  if (n < CmdArgs_argc()) {
    av = CmdArgs_argv();
    i = 0;
    while (((av)[n])[i] != 0x00) {
      if (i < val__len - 1) {
        val[i] = ((av)[n])[i];
      } else {
        val[i] = 0x00;
        CmdArgs_Truncated = 1;
        return;
      }
      i += 1;
    }
    val[i] = 0x00;
  }
}

/*----------------------------------------------------------------------------*/
void CmdArgs_GetInt (INTEGER n, INTEGER *val)
{
  CHAR s[16];
  INTEGER d, i;
  CmdArgs_Get(n, (void*)s, 16);
  i = 0;
  if (s[0] == '-') {
    i = 1;
  }
  while (s[i] == '0') {
    i += 1;
  }
  *val = 0;
  d = (INTEGER)s[i] - 48;
  while (d >= 0 && d <= 9) {
    *val = *val * 10 + d;
    i += 1;
    d = (INTEGER)s[i] - 48;
  }
  if (s[0] == '-') {
    *val = -*val;
  }
}

/*----------------------------------------------------------------------------*/
INTEGER CmdArgs_Pos (CHAR *s, INTEGER s__len)
{
  INTEGER i;
  CHAR arg[1024];
  i = 0;
  CmdArgs_Get(i, (void*)arg, 1024);
  while (i < CmdArgs_argc() && (__STRCMPCC(s, arg, 1024, (CHAR*)"CmdArgs", 14641) != 0 || CmdArgs_Truncated)) {
    i += 1;
    CmdArgs_Get(i, (void*)arg, 1024);
  }
  return i;
}

/*----------------------------------------------------------------------------*/
void CmdArgs_GetEnv (CHAR *var, INTEGER var__len, CHAR *val, INTEGER val__len)
{
  CmdArgs_EnvPtr p;
  INTEGER i;
  CmdArgs_Truncated = 0;
  p = CmdArgs_getenv(var, var__len);
  if (p != NIL) {
    i = 0;
    while ((p)[i] != 0x00) {
      if (i < val__len - 1) {
        val[i] = (p)[i];
      } else {
        val[i] = 0x00;
        CmdArgs_Truncated = 1;
        return;
      }
      i += 1;
    }
    val[i] = 0x00;
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
void CmdArgs_GetEnvN (INTEGER n, CHAR *val, INTEGER val__len)
{
  CmdArgs_Environ p;
  INTEGER i;
  CmdArgs_Truncated = 0;
  p = CmdArgs_environ();
  p = CmdArgs_nextenviron(p, n);
  if (p->e != NIL) {
    i = 0;
    while ((p->e)[i] != 0x00) {
      if (i < val__len - 1) {
        val[i] = (p->e)[i];
      } else {
        val[i] = 0x00;
        CmdArgs_Truncated = 1;
        return;
      }
      i += 1;
    }
    val[i] = 0x00;
  } else {
    val[0] = 0x00;
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
