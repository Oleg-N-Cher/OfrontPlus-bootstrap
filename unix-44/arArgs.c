/* Ofront+ 1.0 -s2 -44 */
#include "SYSTEM.oh"
#include "Platform.oh"

typedef
  CHAR (*arArgs_ArgPtr)[1024];

typedef
  arArgs_ArgPtr (*arArgs_ArgVec)[1024];


export INTEGER arArgs_argc;
export arArgs_ArgVec arArgs_argv;


__EXTERN INTEGER __getmainargs (INTEGER *argc, arArgs_ArgVec *argv, SYSTEM_PTR *env, INTEGER wildcard, SYSTEM_PTR *startupinfo);

#define arArgs_Argc()  SYSTEM_argc
#define arArgs_Argv()  (arArgs_ArgVec)SYSTEM_argv
#define arArgs_getMainArgs()  void *tmp; __getmainargs(&arArgs_argc, &arArgs_argv, &tmp, 0, &tmp)

/*============================================================================*/


export void *arArgs__init (void)
{
  __DEFMOD;
  __IMPORT(Platform__init);
  __REGMOD("arArgs", 0);
/* BEGIN */
  arArgs_argc = arArgs_Argc();
  arArgs_argv = arArgs_Argv();
  __ENDMOD;
}
