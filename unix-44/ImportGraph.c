/* Ofront+ 1.0 -mC -44 */
#include "SYSTEM.oh"
#include "Console.oh"
#include "CmdArgs.oh"
#include "Files.oh"
#include "Platform.oh"
#include "Strings.oh"

struct ImportGraph__1 {
  INTEGER sym;
  CHAR id[7];
};

typedef
  CHAR ImportGraph_FileName[260];

typedef
  struct ImportGraph_ModuleDesc *ImportGraph_Module;

typedef
  struct ImportGraph_ModuleRefDesc *ImportGraph_ModuleRef;

typedef
  struct ImportGraph_ModuleDesc {
    CHAR name[64];
    ImportGraph_ModuleRef imp;
    SET attr;
    SHORTINT mark;
    ImportGraph_Module next;
  } ImportGraph_ModuleDesc;

typedef
  struct ImportGraph_ModuleRefDesc {
    ImportGraph_Module mod;
    ImportGraph_ModuleRef next;
  } ImportGraph_ModuleRefDesc;


static CHAR ImportGraph_ch;
static BOOLEAN ImportGraph_eot;
static Files_File ImportGraph_f;
static Files_Rider ImportGraph_r;
static CHAR ImportGraph_id[64], ImportGraph_arg[64];
static struct ImportGraph__1 ImportGraph_keyTab[2];
static INTEGER ImportGraph_numKW;
static ImportGraph_Module ImportGraph_first;

export void **ImportGraph_ModuleDesc__typ;
export void **ImportGraph_ModuleRefDesc__typ;
export void **ImportGraph__1__typ;

static BOOLEAN ImportGraph_BlackListed (CHAR *name, INTEGER name__len);
static ImportGraph_ModuleRef ImportGraph_EnlistModule (CHAR *name, INTEGER name__len);
static void ImportGraph_ExtractSubsystem (CHAR *ident, INTEGER ident__len, CHAR *subsystem, INTEGER subsystem__len, CHAR *name, INTEGER name__len);
static void ImportGraph_GetSym (INTEGER *sym);
static void ImportGraph_InitScanner (void);
static void ImportGraph_LoadImports (ImportGraph_Module m);
static Files_File ImportGraph_OpenFile (CHAR *path, INTEGER path__len);
static BOOLEAN ImportGraph_OpenStream (CHAR *fname, INTEGER fname__len);
static BOOLEAN ImportGraph_OutputData (ImportGraph_Module m, BOOLEAN markedImportOnly);
static void ImportGraph_OutputImports (BOOLEAN reduced);
static void ImportGraph_Read (void);


/*============================================================================*/

static void ImportGraph_Read (void)
{
  if (!ImportGraph_eot) {
    Files_ReadChar(&ImportGraph_r, Files_Rider__typ, &ImportGraph_ch);
    ImportGraph_eot = ImportGraph_r.eof;
  } else {
    ImportGraph_ch = 0x00;
  }
}

static struct GetSym__4 {
  INTEGER *sym;
  struct GetSym__4 *lnk;
} *GetSym__4_s;

static void __5 (void);
static void __7 (void);
static void __9 (void);
static void __11 (void);

static void __5 (void)
{
  ImportGraph_Read();
  for (;;) {
    for (;;) {
      while (ImportGraph_ch == '(') {
        ImportGraph_Read();
        if (ImportGraph_ch == '*') {
          __5();
        }
      }
      if (ImportGraph_ch == '*') {
        ImportGraph_Read();
        break;
      }
      if (ImportGraph_eot) {
        break;
      }
      ImportGraph_Read();
    }
    if (ImportGraph_ch == ')') {
      ImportGraph_Read();
      break;
    }
    if (ImportGraph_eot) {
      break;
    }
  }
}

static void __7 (void)
{
  ImportGraph_Read();
  for (;;) {
    for (;;) {
      if (ImportGraph_ch == '*') {
        ImportGraph_Read();
        break;
      }
      if (ImportGraph_eot) {
        break;
      }
      ImportGraph_Read();
    }
    if (ImportGraph_ch == '>') {
      ImportGraph_Read();
      break;
    }
    if (ImportGraph_eot) {
      break;
    }
  }
}

static void __11 (void)
{
  ImportGraph_Read();
  for (;;) {
    if (ImportGraph_ch == 0x0d || ImportGraph_ch == 0x0a) {
      ImportGraph_Read();
      break;
    }
    if (ImportGraph_eot) {
      break;
    }
    ImportGraph_Read();
  }
}

static void __9 (void)
{
  INTEGER i;
  i = 0;
  do {
    if (i < 64) {
      ImportGraph_id[__X(i, 64, (CHAR*)"ImportGraph", 34349)] = ImportGraph_ch;
      i += 1;
    }
    ImportGraph_Read();
  } while (!((ImportGraph_ch < '0' || (ImportGraph_ch > '9' && __CAP(ImportGraph_ch) < 'A')) || __CAP(ImportGraph_ch) > 'Z'));
  ImportGraph_id[__X(i, 64, (CHAR*)"ImportGraph", 35090)] = 0x00;
  i = 0;
  while (i < ImportGraph_numKW && __STRCMPCC(ImportGraph_id, ImportGraph_keyTab[__X(i, 2, (CHAR*)"ImportGraph", 35630)].id, 7, (CHAR*)"ImportGraph", 35630) != 0) {
    i += 1;
  }
  if (i < ImportGraph_numKW) {
    *GetSym__4_s->sym = ImportGraph_keyTab[__X(i, 2, (CHAR*)"ImportGraph", 35885)].sym;
  } else {
    *GetSym__4_s->sym = 5;
  }
}

static void ImportGraph_GetSym (INTEGER *sym)
{
  struct GetSym__4 _s;
  _s.sym = sym;
  _s.lnk = GetSym__4_s;
  GetSym__4_s = &_s;
  while (!ImportGraph_eot && ImportGraph_ch <= ' ') {
    ImportGraph_Read();
  }
  if (ImportGraph_eot) {
    *sym = 6;
  } else {
    switch (ImportGraph_ch) {
      case 'A': case 'B': case 'C': case 'D': case 'E': 
      case 'F': case 'G': case 'H': case 'I': case 'J': 
      case 'K': case 'L': case 'M': case 'N': case 'O': 
      case 'P': case 'Q': case 'R': case 'S': case 'T': 
      case 'U': case 'V': case 'W': case 'X': case 'Y': 
      case 'Z': case 'a': case 'b': case 'c': case 'd': 
      case 'e': case 'f': case 'g': case 'h': case 'i': 
      case 'j': case 'k': case 'l': case 'm': case 'n': 
      case 'o': case 'p': case 'q': case 'r': case 's': 
      case 't': case 'u': case 'v': case 'w': case 'x': 
      case 'y': case 'z': 
        __9();
        break;
      case ':': 
        ImportGraph_Read();
        if (ImportGraph_ch == '=') {
          ImportGraph_Read();
          *sym = 1;
        } else {
          *sym = 7;
        }
        break;
      case ';': 
        ImportGraph_Read();
        *sym = 4;
        break;
      case ',': 
        ImportGraph_Read();
        *sym = 3;
        break;
      case '(': 
        ImportGraph_Read();
        if (ImportGraph_ch == '*') {
          __5();
          ImportGraph_GetSym(sym);
        } else {
          *sym = 9;
        }
        break;
      case '<': 
        ImportGraph_Read();
        if (ImportGraph_ch == '*') {
          __7();
          ImportGraph_GetSym(sym);
        } else {
          *sym = 10;
        }
        break;
      case '-': 
        ImportGraph_Read();
        if (ImportGraph_ch == '-') {
          __11();
          ImportGraph_GetSym(sym);
        } else {
          *sym = 11;
        }
        break;
      default: 
        ImportGraph_Read();
        *sym = 0;
        break;
    }
  }
  GetSym__4_s = _s.lnk;
}

static ImportGraph_ModuleRef ImportGraph_EnlistModule (CHAR *name, INTEGER name__len)
{
  ImportGraph_Module m = NIL;
  ImportGraph_Module new = NIL;
  ImportGraph_ModuleRef res = NIL;
  m = ImportGraph_first;
  while (m->next != NIL && __STRCMPCC(m->next->name, name, name__len, (CHAR*)"ImportGraph", 46638) != 0) {
    m = m->next;
  }
  if (m->next == NIL) {
    __NEW(new, ImportGraph_ModuleDesc);
    __STRCOPYCC(name, new->name, __MIN(64, name__len), (CHAR*)"ImportGraph", 47383);
    new->attr = 0x0;
    m->next = new;
  }
  __NEW(res, ImportGraph_ModuleRefDesc);
  res->mod = m->next;
  return res;
}

static void ImportGraph_ExtractSubsystem (CHAR *ident, INTEGER ident__len, CHAR *subsystem, INTEGER subsystem__len, CHAR *name, INTEGER name__len)
{
  INTEGER i;
  i = 0;
  while ((ident[__X(i, ident__len, (CHAR*)"ImportGraph", 51267)] != 0x00 && 'A' <= ident[__X(i, ident__len, (CHAR*)"ImportGraph", 51267)]) && ident[__X(i, ident__len, (CHAR*)"ImportGraph", 51267)] <= 'Z') {
    i += 1;
  }
  while ((ident[__X(i, ident__len, (CHAR*)"ImportGraph", 52035)] != 0x00 && 'a' <= ident[__X(i, ident__len, (CHAR*)"ImportGraph", 52035)]) && ident[__X(i, ident__len, (CHAR*)"ImportGraph", 52035)] <= 'z') {
    i += 1;
  }
  subsystem[0] = 0x00;
  if (ident[__X(i, ident__len, (CHAR*)"ImportGraph", 54534)] != 0x00) {
    Strings_Extract((void*)ident, ident__len, 0, i, (void*)subsystem, subsystem__len);
    name[0] = 0x00;
    Strings_Extract((void*)ident, ident__len, i, name__len, (void*)name, name__len);
  } else {
    __STRCOPYCC(ident, name, __MIN(name__len, ident__len), (CHAR*)"ImportGraph", 54292);
  }
}

static BOOLEAN ImportGraph_BlackListed (CHAR *name, INTEGER name__len)
{
  ImportGraph_FileName sub, tmp;
  ImportGraph_ExtractSubsystem((void*)ImportGraph_id, 64, (void*)sub, 260, (void*)tmp, 260);
  return (__STRCMPCC(name, (CHAR*)"SYSTEM", 7, (CHAR*)"ImportGraph", 57087) == 0 || __STRCMPCC(name, (CHAR*)"COM", 4, (CHAR*)"ImportGraph", 57087) == 0) || __STRCMPCC(sub, (CHAR*)"Win", 4, (CHAR*)"ImportGraph", 57087) == 0;
}

static Files_File ImportGraph_OpenFile (CHAR *path, INTEGER path__len)
{
  INTEGER i;
  i = 0;
  while (i < path__len && path[__X(i, path__len, (CHAR*)"ImportGraph", 59180)] != 0x00) {
    if (path[__X(i, path__len, (CHAR*)"ImportGraph", 59441)] == '\\') {
      path[__X(i, path__len, (CHAR*)"ImportGraph", 59437)] = '/';
    }
    i += 1;
  }
  return Files_Old((void*)path, path__len);
}

static BOOLEAN ImportGraph_OpenStream (CHAR *fname, INTEGER fname__len)
{
  ImportGraph_FileName name, full;
  __STRCOPYCC(fname, name, __MIN(260, fname__len), (CHAR*)"ImportGraph", 63249);
  Strings_Append((CHAR*)".Mod", 5, (void*)name, 260);
  ImportGraph_f = ImportGraph_OpenFile((void*)name, 260);
  if (ImportGraph_f == NIL) {
    __MOVE((CHAR*)"Mod\\", full, 5);
    Strings_Append((void*)name, 260, (void*)full, 260);
    ImportGraph_f = ImportGraph_OpenFile((void*)full, 260);
    if (ImportGraph_f == NIL) {
      __MOVE((CHAR*)"Lib\\Mod\\", full, 9);
      Strings_Append((void*)name, 260, (void*)full, 260);
      ImportGraph_f = ImportGraph_OpenFile((void*)full, 260);
      if (ImportGraph_f == NIL) {
        ImportGraph_ExtractSubsystem((void*)fname, fname__len, (void*)full, 260, (void*)name, 260);
        if (full[0] != 0x00) {
          Strings_Append((CHAR*)"\\Mod\\", 6, (void*)full, 260);
        } else {
          __MOVE((CHAR*)"System\\Mod\\", full, 12);
        }
        Strings_Append((void*)name, 260, (void*)full, 260);
        Strings_Append((CHAR*)".odc", 5, (void*)full, 260);
        ImportGraph_f = ImportGraph_OpenFile((void*)full, 260);
      }
    }
  }
  if (ImportGraph_f != NIL) {
    Files_Set(&ImportGraph_r, Files_Rider__typ, ImportGraph_f, 0);
  }
  return ImportGraph_f != NIL;
}

static struct LoadImports__16 {
  ImportGraph_Module *m;
  INTEGER *sym;
  struct LoadImports__16 *lnk;
} *LoadImports__16_s;

static void __17 (void);
static BOOLEAN __19 (void);
static BOOLEAN __21 (void);

static BOOLEAN __21 (void)
{
  ImportGraph_eot = 0;
  ImportGraph_Read();
  do {
    ImportGraph_GetSym(&(*LoadImports__16_s->sym));
  } while (!(ImportGraph_eot || (*LoadImports__16_s->sym) == 8));
  if ((*LoadImports__16_s->sym) == 8) {
    ImportGraph_GetSym(&(*LoadImports__16_s->sym));
    if ((*LoadImports__16_s->sym) == 5) {
      ImportGraph_GetSym(&(*LoadImports__16_s->sym));
      if ((*LoadImports__16_s->sym) == 4) {
        return 1;
      }
    }
  }
  return 0;
}

static BOOLEAN __19 (void)
{
  if (!ImportGraph_eot) {
    do {
      ImportGraph_GetSym(&(*LoadImports__16_s->sym));
    } while (!(ImportGraph_eot || (*LoadImports__16_s->sym) == 2));
    if ((*LoadImports__16_s->sym) == 2) {
      ImportGraph_GetSym(&(*LoadImports__16_s->sym));
      return 1;
    }
  }
  return 0;
}

static void __17 (void)
{
  ImportGraph_ModuleRef ref = NIL;
  BOOLEAN err;
  ImportGraph_FileName sub, name;
  err = 0;
  while ((*LoadImports__16_s->sym) == 5 && !err) {
    ImportGraph_GetSym(&(*LoadImports__16_s->sym));
    if ((*LoadImports__16_s->sym) == 1) {
      ImportGraph_GetSym(&(*LoadImports__16_s->sym));
      err = (*LoadImports__16_s->sym) != 5;
      if (!err) {
        ImportGraph_GetSym(&(*LoadImports__16_s->sym));
        err = (*LoadImports__16_s->sym) != 3 && (*LoadImports__16_s->sym) != 4;
      }
    }
    if (!err) {
      if ((*LoadImports__16_s->sym) == 3 || (*LoadImports__16_s->sym) == 4) {
        if (__STRCMPCC(ImportGraph_id, (CHAR*)"SYSTEM", 7, (CHAR*)"ImportGraph", 87570) == 0) {
          ((*LoadImports__16_s->m))->attr |= __SETOF(2);
        } else if ((((((__STRCMPCC(ImportGraph_id, (CHAR*)"KERNEL32", 9, (CHAR*)"ImportGraph", 84776) == 0 || __STRCMPCC(ImportGraph_id, (CHAR*)"GDI32", 6, (CHAR*)"ImportGraph", 84776) == 0) || __STRCMPCC(ImportGraph_id, (CHAR*)"USER32", 7, (CHAR*)"ImportGraph", 84776) == 0) || __STRCMPCC(ImportGraph_id, (CHAR*)"SHELL32", 8, (CHAR*)"ImportGraph", 84776) == 0) || __STRCMPCC(ImportGraph_id, (CHAR*)"COMDLG32", 9, (CHAR*)"ImportGraph", 84776) == 0) || __STRCMPCC(ImportGraph_id, (CHAR*)"ADVAPI32", 9, (CHAR*)"ImportGraph", 84776) == 0) || __STRCMPCC(ImportGraph_id, (CHAR*)"COM", 4, (CHAR*)"ImportGraph", 84776) == 0) {
          ((*LoadImports__16_s->m))->attr |= __SETOF(3);
        } else {
          ImportGraph_ExtractSubsystem((void*)ImportGraph_id, 64, (void*)sub, 260, (void*)name, 260);
          if (__STRCMPCC(sub, (CHAR*)"Win", 4, (CHAR*)"ImportGraph", 87317) == 0) {
            ((*LoadImports__16_s->m))->attr |= __SETOF(3);
          }
        }
        if (!ImportGraph_BlackListed((void*)ImportGraph_id, 64)) {
          ref = ImportGraph_EnlistModule((void*)ImportGraph_id, 64);
          ref->next = ((*LoadImports__16_s->m))->imp;
          ((*LoadImports__16_s->m))->imp = ref;
        }
        if ((*LoadImports__16_s->sym) == 3) {
          ImportGraph_GetSym(&(*LoadImports__16_s->sym));
        }
      }
    }
  }
  if (err) {
    ((*LoadImports__16_s->m))->attr |= __SETOF(1);
  }
}

static void ImportGraph_LoadImports (ImportGraph_Module m)
{
  INTEGER sym;
  struct LoadImports__16 _s;
  _s.m = &m;
  _s.sym = &sym;
  _s.lnk = LoadImports__16_s;
  LoadImports__16_s = &_s;
  if (ImportGraph_OpenStream((void*)m->name, 64)) {
    m->attr |= __SETOF(0);
    if (__21()) {
      __STRCOPYCC(ImportGraph_id, m->name, 64, (CHAR*)"ImportGraph", 92210);
      if (__19()) {
        __17();
      }
    }
  }
  LoadImports__16_s = _s.lnk;
}

static struct OutputData__25 {
  struct OutputData__25 *lnk;
} *OutputData__25_s;

static void __26 (ImportGraph_Module from, ImportGraph_Module to);
static void __28 (ImportGraph_Module m);

static void __28 (ImportGraph_Module m)
{
  Console_Char('\"');
  Console_String((void*)m->name, 64);
  Console_Char('\"');
}

static void __26 (ImportGraph_Module from, ImportGraph_Module to)
{
  __28(from);
  Console_String((CHAR*)"->", 3);
  __28(to);
  Console_String((CHAR*)"; ", 3);
}

static BOOLEAN ImportGraph_OutputData (ImportGraph_Module m, BOOLEAN markedImportOnly)
{
  BOOLEAN res;
  ImportGraph_ModuleRef ref = NIL;
  struct OutputData__25 _s;
  BOOLEAN __retval;
  _s.lnk = OutputData__25_s;
  OutputData__25_s = &_s;
  if (__IN(0, m->attr)) {
    res = 0;
    if (!__IN(1, m->attr)) {
      if (__IN(2, m->attr)) {
        __28(m);
        Console_String((CHAR*)" [fontcolor = red]; ", 21);
        res = 1;
      }
      if (__IN(3, m->attr)) {
        __28(m);
        Console_String((CHAR*)" [shape = box]; ", 17);
        res = 1;
      }
      ref = m->imp;
      if (markedImportOnly) {
        while (ref != NIL) {
          if ((INTEGER)ref->mod->mark == 1) {
            __26(m, ref->mod);
            res = 1;
          }
          ref = ref->next;
        }
      } else {
        res = res || ref != NIL;
        while (ref != NIL) {
          __26(m, ref->mod);
          ref = ref->next;
        }
      }
    }
  } else {
    res = 1;
    Console_String((void*)m->name, 64);
    Console_String((CHAR*)" [shape = plaintext];", 22);
  }
  __retval = res;
  OutputData__25_s = _s.lnk;
  ;
  return __retval;
}

static struct InitScanner__13 {
  struct InitScanner__13 *lnk;
} *InitScanner__13_s;

static void __14 (INTEGER sym, CHAR *id, INTEGER id__len);

static void __14 (INTEGER sym, CHAR *id, INTEGER id__len)
{
  ImportGraph_keyTab[__X(ImportGraph_numKW, 2, (CHAR*)"ImportGraph", 111647)].sym = sym;
  __STRCOPYCC(id, ImportGraph_keyTab[__X(ImportGraph_numKW, 2, (CHAR*)"ImportGraph", 111673)].id, __MIN(7, id__len), (CHAR*)"ImportGraph", 111673);
  ImportGraph_numKW += 1;
}

static void ImportGraph_InitScanner (void)
{
  struct InitScanner__13 _s;
  _s.lnk = InitScanner__13_s;
  InitScanner__13_s = &_s;
  ImportGraph_numKW = 0;
  __14(8, (CHAR*)"MODULE", 7);
  __14(2, (CHAR*)"IMPORT", 7);
  InitScanner__13_s = _s.lnk;
}

static struct OutputImports__30 {
  ImportGraph_Module *m;
  struct OutputImports__30 *lnk;
} *OutputImports__30_s;

static void __31 (void);
static void __33 (ImportGraph_ModuleRef ref);

static void __31 (void)
{
  ImportGraph_Module m = NIL;
  m = ImportGraph_first->next;
  while (m != NIL) {
    m->mark = 0;
    m = m->next;
  }
}

static void __33 (ImportGraph_ModuleRef ref)
{
  while (ref != NIL) {
    if (ref->mod != (*OutputImports__30_s->m)) {
      if ((INTEGER)ref->mod->mark < 2) {
        ref->mod->mark += 1;
        if ((INTEGER)ref->mod->mark < 2) {
          __33(ref->mod->imp);
        }
      }
    }
    ref = ref->next;
  }
}

static void ImportGraph_OutputImports (BOOLEAN reduced)
{
  INTEGER i;
  ImportGraph_Module m = NIL;
  ImportGraph_ModuleRef tmp = NIL;
  struct OutputImports__30 _s;
  _s.m = &m;
  _s.lnk = OutputImports__30_s;
  OutputImports__30_s = &_s;
  ImportGraph_InitScanner();
  i = 1;
  __NEW(ImportGraph_first, ImportGraph_ModuleDesc);
  ImportGraph_first->name[0] = 0x00;
  while (i <= CmdArgs_Count) {
    CmdArgs_Get(i, (void*)ImportGraph_arg, 64);
    if (__STRCMPCC(ImportGraph_arg, (CHAR*)"-r", 3, (CHAR*)"ImportGraph", 124169) == 0) {
      reduced = !reduced;
    } else {
      tmp = ImportGraph_EnlistModule((void*)ImportGraph_arg, 64);
    }
    i += 1;
  }
  m = ImportGraph_first->next;
  while (m != NIL) {
    ImportGraph_LoadImports(m);
    m = m->next;
  }
  m = ImportGraph_first->next;
  while (m != NIL) {
    if (reduced) {
      __31();
      __33(m->imp);
    }
    if (ImportGraph_OutputData(m, reduced)) {
      Console_Ln();
    }
    m = m->next;
  }
  OutputImports__30_s = _s.lnk;
}

static void EnumPtrs(void (*P)(void*))
{
  P(ImportGraph_f);
  __ENUMR(&ImportGraph_r, Files_Rider__typ, 24, 1, P);
  P(ImportGraph_first);
}

__TDESC(ImportGraph_ModuleDesc__desc, 2, 2) = {__TDFLDS("ModuleDesc", 80), {64, 76, -12}};
__TDESC(ImportGraph_ModuleRefDesc__desc, 2, 2) = {__TDFLDS("ModuleRefDesc", 8), {0, 4, -12}};
__TDESC(ImportGraph__1__desc, 1, 0) = {__TDFLDS("", 12), {-4}};

int main (int argc, char **argv)
{
  __INIT(argc, argv);
  __IMPORT(CmdArgs__init);
  __IMPORT(Files__init);
  __IMPORT(Console__init);
  __IMPORT(Platform__init);
  __IMPORT(Strings__init);
  __REGMAIN("ImportGraph", EnumPtrs);
  __INITYP(ImportGraph_ModuleDesc, ImportGraph_ModuleDesc, 0);
  __INITYP(ImportGraph_ModuleRefDesc, ImportGraph_ModuleRefDesc, 0);
  __INITYP(ImportGraph__1, ImportGraph__1, 0);
/* BEGIN */
  if (CmdArgs_Count != 0) {
    Files_SetSearchPath((CHAR*)".", 2);
    Console_String((CHAR*)"strict digraph G{", 18);
    Console_Ln();
    ImportGraph_OutputImports(0);
    Console_Char('}');
    Console_Ln();
  } else {
    Console_String((CHAR*)"Usage: [-r] module1 [module2 ...]", 34);
    Console_Ln();
    Console_String((CHAR*)"  If \"-r\", then use marking to reduce the number of import links shown.", 72);
    Console_Ln();
    Console_String((CHAR*)"  E.g., given (A->B, B->C, A->C) do not display A->C.", 54);
    Console_Ln();
  }
  __FINI;
}
