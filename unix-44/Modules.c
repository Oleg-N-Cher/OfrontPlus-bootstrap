/* Ofront+ 1.0 -sC -44 */
#include "SYSTEM.oh"
#include "Platform.oh"
#include "Heap.oh"


export INTEGER Modules_res;
export CHAR Modules_resMsg[256];
export Heap_ModuleName Modules_imported, Modules_importing;


export void Modules_Free (CHAR *name, INTEGER name__len, BOOLEAN all);
export Heap_Command Modules_ThisCommand (Heap_Module mod, CHAR *name, INTEGER name__len);
export Heap_Module Modules_ThisMod (CHAR *name, INTEGER name__len);

#define Modules_modules()  (Heap_Module)Heap_modules

/*============================================================================*/

Heap_Module Modules_ThisMod (CHAR *name, INTEGER name__len)
{
  Heap_Module m = NIL;
  CHAR bodyname[64];
  Heap_Command body = NIL;
  CHAR _str__5[256];
  m = Modules_modules();
  while (m != NIL && __STRCMPCC(m->name, name, name__len, (CHAR*)"Modules", 7205) != 0) {
    m = m->next;
  }
  if (m != NIL) {
    Modules_res = 0;
    Modules_resMsg[0] = 0x00;
  } else {
    Modules_res = 1;
    __STRCOPYCC(name, Modules_importing, __MIN(48, name__len), (CHAR*)"Modules", 7717);
    __STRCOPYCC((CHAR*)" module \"", _str__5, 256, (CHAR*)"Modules", 8191);
    __STRAPNDCC(name, name__len, _str__5, 256, (CHAR*)"Modules", 8191);
    __STRAPNDCC((CHAR*)"\" not found", 12, _str__5, 256, (CHAR*)"Modules", 8191);
    __STRCOPYCC(_str__5, Modules_resMsg, 256, (CHAR*)"Modules", 7717);
  }
  return m;
}

/*----------------------------------------------------------------------------*/
Heap_Command Modules_ThisCommand (Heap_Module mod, CHAR *name, INTEGER name__len)
{
  Heap_Cmd c = NIL;
  CHAR _str__3[256];
  c = mod->cmds;
  while (c != NIL && __STRCMPCC(c->name, name, name__len, (CHAR*)"Modules", 10021) != 0) {
    c = c->next;
  }
  if (c != NIL) {
    Modules_res = 0;
    Modules_resMsg[0] = 0x00;
    return c->cmd;
  } else {
    Modules_res = 2;
    __STRCOPYCC(name, Modules_importing, __MIN(48, name__len), (CHAR*)"Modules", 10533);
    __STRCOPYCC((CHAR*)" command \"", _str__3, 256, (CHAR*)"Modules", 10820);
    __STRAPNDCC(mod->name, 48, _str__3, 256, (CHAR*)"Modules", 10820);
    __STRAPNDCC((CHAR*)".", 2, _str__3, 256, (CHAR*)"Modules", 10820);
    __STRAPNDCC(name, name__len, _str__3, 256, (CHAR*)"Modules", 10820);
    __STRAPNDCC((CHAR*)"\" not found", 12, _str__3, 256, (CHAR*)"Modules", 10820);
    __STRCOPYCC(_str__3, Modules_resMsg, 256, (CHAR*)"Modules", 10533);
    return NIL;
  }
  __RETCHK((CHAR*)"Modules", 11263);
}

/*----------------------------------------------------------------------------*/
void Modules_Free (CHAR *name, INTEGER name__len, BOOLEAN all)
{
  Heap_Module m = NIL;
  Heap_Module p = NIL;
  LONGINT refcount;
  m = Modules_modules();
  if (all) {
    Modules_res = 1;
    __MOVE((CHAR*)"unloading \"all\" not yet supported", Modules_resMsg, 34);
  } else {
    refcount = Heap_FreeModule((void*)name, name__len);
    if (refcount == 0) {
      Modules_res = 0;
    } else {
      if (refcount < 0) {
        __MOVE((CHAR*)"module not found", Modules_resMsg, 17);
      } else {
        __MOVE((CHAR*)"clients of this module exist", Modules_resMsg, 29);
      }
      Modules_res = 1;
    }
  }
}

/*----------------------------------------------------------------------------*/

export void *Modules__init (void)
{
  __DEFMOD;
  __IMPORT(Heap__init);
  __IMPORT(Platform__init);
  __REGMOD("Modules", 0);
/* BEGIN */
  __ENDMOD;
}
