/* Ofront+ 1.0 -s2 -44 */
#include "SYSTEM.oh"
#include "arC.oh"
#include "arCString.oh"

typedef
  struct arDir_FileFinder {
    INTEGER dir, ent;
  } arDir_FileFinder;

export void arDir_FileFinder_Close (arDir_FileFinder *f, void **f__typ);
export BOOLEAN arDir_FileFinder_Next (arDir_FileFinder *f, void **f__typ, CHAR *name, INTEGER name__len);
export BOOLEAN arDir_FileFinder_Open (arDir_FileFinder *f, void **f__typ, CHAR *path, INTEGER path__len);
#define __arDir_FileFinder_Close(f, f__typ) __SEND(f__typ, arDir_FileFinder_Close, 1, void(*)(arDir_FileFinder*, void **), (f, f__typ))
#define __arDir_FileFinder_Next(f, f__typ, name, name__len) __SEND(f__typ, arDir_FileFinder_Next, 2, BOOLEAN(*)(arDir_FileFinder*, void **, CHAR*, INTEGER ), (f, f__typ, name, name__len))
#define __arDir_FileFinder_Open(f, f__typ, path, path__len) __SEND(f__typ, arDir_FileFinder_Open, 3, BOOLEAN(*)(arDir_FileFinder*, void **, CHAR*, INTEGER ), (f, f__typ, path, path__len))



export void **arDir_FileFinder__typ;


#include <dirent.h>
#define arDir_closedir(dir)  closedir((DIR*) dir)
#define arDir_getdirname(ent)  (CHAR *)(((struct dirent *) ent) -> d_name)
#define arDir_getdirtype(ent)  (int)((struct dirent *) ent) -> d_type)
#define arDir_opendir(name, name__len)  (SYSTEM_ADRINT) opendir((const char *)name)
#define arDir_readdir(dir)  (SYSTEM_ADRINT) readdir((DIR*) dir)
#define arDir_typeDir()  DT_DIR
#define arDir_typeLink()  DT_LNK
#define arDir_typeReg()  DT_REG

/*============================================================================*/

BOOLEAN arDir_FileFinder_Open (arDir_FileFinder *f, void **f__typ, CHAR *path, INTEGER path__len)
{
  (*f).dir = arDir_opendir(path, path__len);
  return (*f).dir != 0;
}

/*----------------------------------------------------------------------------*/
BOOLEAN arDir_FileFinder_Next (arDir_FileFinder *f, void **f__typ, CHAR *name, INTEGER name__len)
{
  __ASSERT((*f).dir != 0, 0, (CHAR*)"arDir", 9746);
  (*f).ent = arDir_readdir((*f).dir);
  if ((*f).ent == 0) {
    return 0;
  }
  arCString_CopyToArray(arDir_getdirname((*f).ent), (void*)name, name__len);
  return 1;
}

/*----------------------------------------------------------------------------*/
void arDir_FileFinder_Close (arDir_FileFinder *f, void **f__typ)
{
  if ((*f).dir != 0) {
    arDir_closedir((*f).dir);
  }
}

/*----------------------------------------------------------------------------*/
