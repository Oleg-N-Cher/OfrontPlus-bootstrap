/* Ofront+ 1.0 -m2 -88 */
#include "SYSTEM.oh"
#include "Kernel.oh"
#include "Console.oh"
#include "Files.oh"
#include "Platform.oh"
#include "arArgs.oh"
#include "arOut.oh"
#include "arPath.oh"
#include "arChar.oh"
#include "arText.oh"
#include "arPattern.oh"
#include "arStrings.oh"
#include "arStringList.oh"
#include "arStringAssoc.oh"
#include "arConfiguration.oh"

typedef
  struct OMake_Import__rec *OMake_Import;

typedef
  struct OMake_Module__rec *OMake_Module;

typedef
  struct OMake_Import__rec {
    arStrings_StringPtr name;
    OMake_Module module;
    OMake_Import next;
  } OMake_Import__rec;

typedef
  struct OMake_Keyword__rec *OMake_Keyword;

typedef
  struct OMake_Keyword__rec {
    arStrings_StringPtr name;
    SHORTINT symbol;
    OMake_Keyword next;
  } OMake_Keyword__rec;

typedef
  struct OMake_Module__rec {
    arStrings_StringPtr name, file;
    BOOLEAN inLibrary, built;
    arStrings_StringPtr flags, extFlags;
    arStringList_List links;
    OMake_Import imports;
    OMake_Module next;
  } OMake_Module__rec;


static arConfiguration_String OMake_path, OMake_exclude, OMake_require;
static arConfiguration_Boolean OMake_debug, OMake_script;
static arConfiguration_String OMake_compiler, OMake_linker;
static arConfiguration_Assoc OMake_libraries, OMake_linkFlags, OMake_extensions, OMake_builtin;
static arStringList_Array OMake_sPath, OMake_sExclude, OMake_sRequire;
static OMake_Module OMake_modules;
static OMake_Keyword OMake_keywords, OMake_makeKeywords;

export void **OMake_Keyword__rec__typ;
export void **OMake_Import__rec__typ;
export void **OMake_Module__rec__typ;

static void OMake_AddSymbol (CHAR *name, INTEGER name__len, SHORTINT symbol);
static void OMake_BuildModule (OMake_Module module);
static void OMake_CheckFileType (arStrings_StringPtr path, arStrings_StringPtr *flags);
static void OMake_Command (void);
static BOOLEAN OMake_CompileModule (OMake_Module module, arStringList_List *libs, arStringList_List *objs, BOOLEAN main);
static OMake_Module OMake_FindModule (CHAR *name, INTEGER name__len);
static BOOLEAN OMake_LinkModule (OMake_Module module, arStringList_List libs, arStringList_List objs);
static void OMake_LocateModule (CHAR *name, INTEGER name__len, arStrings_StringPtr *result, arStrings_StringPtr *library);
static OMake_Module OMake_ParseFile (arStrings_StringPtr fileName);
static OMake_Module OMake_ProcessFile (arStrings_StringPtr name);
static INTEGER OMake_Run (arStrings_StringPtr command);
static void OMake_ShowAllModules (void);
static void OMake_ShowModule (OMake_Module m);


/*============================================================================*/

static void OMake_AddSymbol (CHAR *name, INTEGER name__len, SHORTINT symbol)
{
  OMake_Keyword keyword = NIL;
  __DUP(name, name__len);
  __NEW(keyword, OMake_Keyword__rec);
  keyword->name = arStringList_Copy(name, name__len);
  keyword->symbol = symbol;
  keyword->next = OMake_keywords;
  OMake_keywords = keyword;
}

static void OMake_LocateModule (CHAR *name, INTEGER name__len, arStrings_StringPtr *result, arStrings_StringPtr *library)
{
  INTEGER i, j;
  arStrings_StringPtr fileName = NIL;
  arStrings_StringPtr path = NIL;
  arStrings_StringPtr ext = NIL;
  arText_Buffer buffer = {0};
  arStringAssoc_Assoc item = NIL;
  INTEGER _for__24;
  __DUP(name, name__len);
  __arText_Buffer_Init(&buffer, arText_Buffer__typ, 64);
  _for__24 = OMake_sPath->len[0] - 1;
  i = 0;
  while (i <= _for__24) {
    path = (OMake_sPath->data)[__X(i, OMake_sPath->len[0], (CHAR*)"OMake", 27666)];
    *library = arStringAssoc_GetKey(OMake_libraries->value, path->data, path->len[0]);
    item = OMake_extensions->value;
    while (item != NIL) {
      ext = item->key;
      __arText_Buffer_Clear(&buffer, arText_Buffer__typ);
      __arText_Stream_String((void*)&buffer, arText_Buffer__typ, (void*)path->data, path->len[0]);
      __arText_Stream_String((void*)&buffer, arText_Buffer__typ, (CHAR*)"/", 2);
      __arText_Stream_String((void*)&buffer, arText_Buffer__typ, (void*)name, name__len);
      __arText_Stream_String((void*)&buffer, arText_Buffer__typ, (CHAR*)".", 2);
      __arText_Stream_String((void*)&buffer, arText_Buffer__typ, (void*)ext->data, ext->len[0]);
      fileName = (arStrings_StringPtr)__arText_Buffer_GetString(&buffer, arText_Buffer__typ);
      if (Platform_FileExists((void*)fileName->data, fileName->len[0])) {
        *result = fileName;
        return;
      }
      item = item->next;
    }
    i += 1;
  }
  *result = NIL;
}

static OMake_Module OMake_FindModule (CHAR *name, INTEGER name__len)
{
  OMake_Module m = NIL;
  arStrings_StringPtr _ptr__16 = NIL;
  __DUP(name, name__len);
  m = OMake_modules;
  while (m != NIL) {
    if (_ptr__16 = m->name, 
      arStrings_Equal(_ptr__16->data, _ptr__16->len[0], (void*)name, name__len)) {
      return m;
    }
    m = m->next;
  }
  return NIL;
}

static void OMake_ShowModule (OMake_Module m)
{
  OMake_Import i = NIL;
  arStringList_List l = NIL;
  arStrings_StringPtr _ptr__69 = NIL;
  arStrings_StringPtr _ptr__68 = NIL;
  arStrings_StringPtr _ptr__67 = NIL;
  arStrings_StringPtr _ptr__66 = NIL;
  arStrings_StringPtr _ptr__65 = NIL;
  Console_String((CHAR*)"MODULE ", 8);
  _ptr__69 = m->name;
  Console_String((void*)_ptr__69->data, _ptr__69->len[0]);
  if (m->flags != NIL) {
    Console_String((CHAR*)" FLAGS \'", 9);
    _ptr__68 = m->flags;
    Console_String((void*)_ptr__68->data, _ptr__68->len[0]);
    Console_String((CHAR*)"\'", 2);
  }
  if (m->imports != NIL) {
    Console_String((CHAR*)" IMPORTS ", 10);
    i = m->imports;
    while (i != NIL) {
      _ptr__67 = i->name;
      Console_String((void*)_ptr__67->data, _ptr__67->len[0]);
      i = i->next;
      if (i != NIL) {
        Console_Char(',');
      }
    }
  }
  if (m->links != NIL) {
    l = m->links;
    Console_String((CHAR*)" LINKS ", 8);
    while (l != NIL) {
      _ptr__66 = l->name;
      Console_String((void*)_ptr__66->data, _ptr__66->len[0]);
      l = l->next;
      if (l != NIL) {
        Console_Char(',');
      }
    }
  }
  Console_String((CHAR*)" IN FILE ", 10);
  _ptr__65 = m->file;
  Console_String((void*)_ptr__65->data, _ptr__65->len[0]);
  Console_Ln();
}

static void OMake_ShowAllModules (void)
{
  OMake_Module m = NIL;
  m = OMake_modules;
  while (m != NIL) {
    OMake_ShowModule(m);
    m = m->next;
  }
}

static void OMake_CheckFileType (arStrings_StringPtr path, arStrings_StringPtr *flags)
{
  CHAR extension[32];
  arPath_ExtName((void*)path->data, path->len[0], (void*)extension, 32);
  arStrings_Extract((void*)extension, 32, 1, 32, (void*)extension, 32);
  *flags = arStringAssoc_Get(OMake_extensions->value, extension, 32);
}

static struct ParseFile__25 {
  arStrings_StringPtr *fileName;
  SHORTINT *line, *column;
  Files_Rider *rd;
  SHORTINT *sym;
  CHAR *ch;
  arText_Buffer *ident;
  struct ParseFile__25 *lnk;
} *ParseFile__25_s;

static void __26 (void);
static arStrings_StringPtr __30 (void);
static void __32 (CHAR *reason, INTEGER reason__len);
static void __34 (CHAR *reason, INTEGER reason__len, CHAR *str, INTEGER str__len);
static void __36 (SHORTINT symbol);
static void __38 (void);
static void __40 (void);
static void __42 (OMake_Module m);
static void __44 (OMake_Module m);
static void __46 (OMake_Module m);
static void __48 (OMake_Module m);
static void __51 (CHAR term);
static void __53 (void);
static void __55 (void);
static void __57 (void);
static void __59 (void);

static void __34 (CHAR *reason, INTEGER reason__len, CHAR *str, INTEGER str__len)
{
  __DUP(reason, reason__len);
  __DUP(str, str__len);
  if ((*ParseFile__25_s->line) > 0) {
    Console_String((CHAR*)"At line=", 9);
    Console_Int((*ParseFile__25_s->line), 0);
    Console_String((CHAR*)", column=", 10);
    Console_Int((*ParseFile__25_s->column), 0);
    Console_String((CHAR*)" in file ", 10);
    Console_String((void*)((*ParseFile__25_s->fileName))->data, ((*ParseFile__25_s->fileName))->len[0]);
    Console_Ln();
  }
  Console_String((CHAR*)"ERROR: ", 8);
  Console_String((void*)reason, reason__len);
  if (str[0] != 0x00) {
    Console_String((CHAR*)" : ", 4);
    Console_String((void*)str, str__len);
  }
  Console_Ln();
  Kernel_Exit(1);
}

static void __32 (CHAR *reason, INTEGER reason__len)
{
  __DUP(reason, reason__len);
  __34(reason, reason__len, (CHAR*)"", 1);
}

static void __40 (void)
{
  if ((*ParseFile__25_s->ch) == 0x0a) {
    (*ParseFile__25_s->column) = 0;
    (*ParseFile__25_s->line) += 1;
  }
  Files_ReadChar(&(*ParseFile__25_s->rd), Files_Rider__typ, &(*ParseFile__25_s->ch));
  (*ParseFile__25_s->column) += 1;
}

static void __38 (void)
{
  __arText_Buffer_Clear(&(*ParseFile__25_s->ident), arText_Buffer__typ);
  do {
    __arText_Stream_Char((void*)&(*ParseFile__25_s->ident), arText_Buffer__typ, (*ParseFile__25_s->ch));
    __40();
  } while (!(!arChar_IsLetter((*ParseFile__25_s->ch)) && !arChar_IsDigit((*ParseFile__25_s->ch))));
  __arText_Buffer_Terminate(&(*ParseFile__25_s->ident), arText_Buffer__typ);
  (*ParseFile__25_s->sym) = 1;
}

static arStrings_StringPtr __30 (void)
{
  return arStringList_Copy(((*ParseFile__25_s->ident)).value->data, ((*ParseFile__25_s->ident)).value->len[0]);
}

static void __26 (void)
{
  OMake_Keyword keyword = NIL;
  arStrings_StringPtr _ptr__29 = NIL;
  arText_String _ptr__28 = NIL;
  keyword = OMake_keywords;
  while (keyword != NIL) {
    if (_ptr__29 = keyword->name, 
      _ptr__28 = ((*ParseFile__25_s->ident)).value, 
      arStrings_Equal(_ptr__29->data, _ptr__29->len[0], (void*)_ptr__28->data, _ptr__28->len[0])) {
      (*ParseFile__25_s->sym) = keyword->symbol;
      return;
    }
    keyword = keyword->next;
  }
}

static void __51 (CHAR term)
{
  __40();
  __arText_Buffer_Clear(&(*ParseFile__25_s->ident), arText_Buffer__typ);
  while ((*ParseFile__25_s->ch) != term) {
    if ((*ParseFile__25_s->ch) == 0x00 || (*ParseFile__25_s->ch) == 0x0a) {
      __32((CHAR*)"Unterminated String", 20);
    }
    __arText_Stream_Char((void*)&(*ParseFile__25_s->ident), arText_Buffer__typ, (*ParseFile__25_s->ch));
    __40();
  }
  __arText_Buffer_Terminate(&(*ParseFile__25_s->ident), arText_Buffer__typ);
  __40();
  (*ParseFile__25_s->sym) = 2;
}

static void __55 (void)
{
  while (arChar_IsSpace((*ParseFile__25_s->ch))) {
    __40();
  }
}

static void __59 (void)
{
  __55();
  switch ((*ParseFile__25_s->ch)) {
    case 0x00: 
      (*ParseFile__25_s->sym) = 0;
      break;
    case 'a': case 'b': case 'c': case 'd': case 'e': 
    case 'f': case 'g': case 'h': case 'i': case 'j': 
    case 'k': case 'l': case 'm': case 'n': case 'o': 
    case 'p': case 'q': case 'r': case 's': case 't': 
    case 'u': case 'v': case 'w': case 'x': case 'y': 
    case 'z': case 'A': case 'B': case 'C': case 'D': 
    case 'E': case 'F': case 'G': case 'H': case 'I': 
    case 'J': case 'K': case 'L': case 'M': case 'N': 
    case 'O': case 'P': case 'Q': case 'R': case 'S': 
    case 'T': case 'U': case 'V': case 'W': case 'X': 
    case 'Y': case 'Z': case '_': 
      __38();
      __26();
      break;
    case '\"': 
      __51('\"');
      break;
    case '\'': 
      __51('\'');
      break;
    case ';': 
      (*ParseFile__25_s->sym) = 101;
      __40();
      break;
    case ',': 
      (*ParseFile__25_s->sym) = 100;
      __40();
      break;
    case ':': 
      (*ParseFile__25_s->sym) = 102;
      __40();
      if ((*ParseFile__25_s->ch) == '=') {
        __40();
        (*ParseFile__25_s->sym) = 103;
      }
      break;
    case '(': 
      (*ParseFile__25_s->sym) = 104;
      __40();
      if ((*ParseFile__25_s->ch) == '*') {
        (*ParseFile__25_s->sym) = 106;
        __40();
      }
      break;
    case ')': 
      (*ParseFile__25_s->sym) = 105;
      __40();
      break;
    case '*': 
      (*ParseFile__25_s->sym) = 108;
      __40();
      if ((*ParseFile__25_s->ch) == ')') {
        (*ParseFile__25_s->sym) = 107;
        __40();
      }
      break;
    default: 
      __32((CHAR*)"Unexpected symbol", 18);
      break;
  }
  if (OMake_debug->value) {
    Console_Int((*ParseFile__25_s->sym), 0);
    Console_Ln();
  }
}

static void __53 (void)
{
  CHAR lastCh;
  SHORTINT level;
  level = 1;
  lastCh = 0x00;
  for (;;) {
    if ((*ParseFile__25_s->ch) == ')' && lastCh == '*') {
      level -= 1;
      if (level == 0) {
        __40();
        return;
      }
    } else if ((*ParseFile__25_s->ch) == '*' && lastCh == '(') {
      level += 1;
      __40();
    }
    lastCh = (*ParseFile__25_s->ch);
    __40();
  }
}

static void __57 (void)
{
  __59();
  while ((*ParseFile__25_s->sym) == 106) {
    __53();
    __59();
  }
}

static void __36 (SHORTINT symbol)
{
  if ((*ParseFile__25_s->sym) != symbol) {
    Console_String((CHAR*)"Expected=", 10);
    Console_Int(symbol, 0);
    Console_String((CHAR*)" Found=", 8);
    Console_Int((*ParseFile__25_s->sym), 0);
    Console_Ln();
    __32((CHAR*)"Unexpected symbol", 18);
  }
}

static void __42 (OMake_Module m)
{
  OMake_Import i = NIL;
  arStrings_StringPtr name = NIL;
  __36(1);
  name = __30();
  __57();
  if ((*ParseFile__25_s->sym) == 103) {
    __57();
    __36(1);
    name = __30();
    __57();
  }
  __NEW(i, OMake_Import__rec);
  i->name = name;
  i->next = m->imports;
  m->imports = i;
}

static void __44 (OMake_Module m)
{
  __36(2);
  arStringList_Add(&m->links, __30());
  __59();
}

static void __46 (OMake_Module m)
{
  if ((*ParseFile__25_s->sym) == 2) {
    m->flags = __30();
    __59();
  }
  if ((*ParseFile__25_s->sym) == 300) {
    __59();
    __44(m);
    while ((*ParseFile__25_s->sym) == 100) {
      __59();
      __44(m);
    }
  }
}

static void __48 (OMake_Module m)
{
  OMake_Keyword original = NIL;
  arText_String _ptr__50 = NIL;
  __36(200);
  __57();
  __36(1);
  m->name = __30();
  __57();
  __36(101);
  __59();
  while ((*ParseFile__25_s->sym) == 106) {
    __55();
    if ((*ParseFile__25_s->ch) == 'O') {
      __38();
      if (_ptr__50 = ((*ParseFile__25_s->ident)).value, 
        arStrings_Equal((void*)_ptr__50->data, _ptr__50->len[0], (CHAR*)"OMAKE", 6)) {
        original = OMake_keywords;
        OMake_keywords = OMake_makeKeywords;
        __59();
        __46(m);
        __36(107);
        OMake_keywords = original;
      } else {
        __53();
      }
      __59();
    } else {
      __53();
      __59();
    }
  }
  if ((*ParseFile__25_s->sym) == 201) {
    __57();
    __42(m);
    while ((*ParseFile__25_s->sym) == 100) {
      __57();
      __42(m);
    }
    __36(101);
  }
}

static OMake_Module OMake_ParseFile (arStrings_StringPtr fileName)
{
  SHORTINT line, column;
  Files_Rider rd = {0};
  Files_File file = NIL;
  SHORTINT sym;
  CHAR ch;
  arText_Buffer ident = {0};
  arStrings_StringPtr importName = NIL;
  arStrings_StringPtr library = NIL;
  OMake_Module m = NIL;
  OMake_Import imp = NIL;
  struct ParseFile__25 _s;
  OMake_Module __retval;
  _s.fileName = &fileName;
  _s.line = &line;
  _s.column = &column;
  _s.rd = &rd;
  _s.sym = &sym;
  _s.ch = &ch;
  _s.ident = &ident;
  _s.lnk = ParseFile__25_s;
  ParseFile__25_s = &_s;
  __arText_Buffer_Init(&ident, arText_Buffer__typ, 64);
  if (OMake_debug->value) {
    Console_String((CHAR*)"Parse file ", 12);
    Console_String((void*)fileName->data, fileName->len[0]);
    Console_Ln();
  }
  m = NIL;
  line = 0;
  column = 0;
  file = Files_Old((void*)fileName->data, fileName->len[0]);
  if (file == NIL) {
    __34((CHAR*)"Cannot open file", 17, fileName->data, fileName->len[0]);
  }
  Files_Set(&rd, Files_Rider__typ, file, 0);
  ch = 0x0a;
  __57();
  __NEW(m, OMake_Module__rec);
  m->name = NIL;
  m->file = fileName;
  m->flags = NIL;
  OMake_CheckFileType(m->file, &m->extFlags);
  m->links = NIL;
  m->imports = NIL;
  m->inLibrary = 0;
  m->built = 0;
  __48(m);
  Files_Close(file);
  imp = m->imports;
  while (imp != NIL) {
    if (!arStringList_ArrayContains(OMake_sExclude, imp->name)) {
      imp->module = OMake_FindModule(imp->name->data, imp->name->len[0]);
      if (imp->module == NIL) {
        OMake_LocateModule(imp->name->data, imp->name->len[0], &importName, &library);
        if (importName == NIL) {
          __34((CHAR*)"Cannot locate module source", 28, imp->name->data, imp->name->len[0]);
        }
        imp->module = OMake_ParseFile(importName);
        if (library != NIL) {
          arStringList_Add(&imp->module->links, library);
          imp->module->inLibrary = 1;
        }
      }
    }
    imp = imp->next;
  }
  m->next = OMake_modules;
  OMake_modules = m;
  __retval = m;
  ParseFile__25_s = _s.lnk;
  ;
  return __retval;
}

static INTEGER OMake_Run (arStrings_StringPtr command)
{
  INTEGER result, i;
  CHAR ch;
  if (OMake_script->value) {
    Console_String((void*)command->data, command->len[0]);
    Console_Ln();
    return 0;
  } else {
    Console_String((CHAR*)"--> ", 5);
    Console_String((void*)command->data, command->len[0]);
    Console_Ln();
    return Platform_System((void*)command->data, command->len[0]);
  }
  __RETCHK((CHAR*)"OMake", 132898);
}

static BOOLEAN OMake_CompileModule (OMake_Module module, arStringList_List *libs, arStringList_List *objs, BOOLEAN main)
{
  arText_Buffer buffer = {0};
  INTEGER result;
  OMake_Import import_ = NIL;
  arStrings_StringPtr _ptr__14 = NIL;
  arStrings_StringPtr _ptr__13 = NIL;
  arStrings_StringPtr _ptr__12 = NIL;
  arStrings_StringPtr _ptr__11 = NIL;
  arStrings_StringPtr _ptr__10 = NIL;
  if (module->built) {
    return 1;
  }
  arStringList_Merge(module->links, libs);
  if (module->inLibrary) {
    return 1;
  }
  arStringList_Add(objs, module->name);
  import_ = module->imports;
  while (import_ != NIL) {
    if (import_->module != NIL) {
      if (!OMake_CompileModule(import_->module, libs, objs, 0)) {
        return 0;
      }
    }
    import_ = import_->next;
  }
  __arText_Buffer_Init(&buffer, arText_Buffer__typ, 128);
  _ptr__14 = OMake_compiler->value;
  __arText_Stream_String((void*)&buffer, arText_Buffer__typ, (void*)_ptr__14->data, _ptr__14->len[0]);
  __arText_Stream_Char((void*)&buffer, arText_Buffer__typ, ' ');
  if (module->flags != NIL) {
    _ptr__13 = module->flags;
    __arText_Stream_String((void*)&buffer, arText_Buffer__typ, (void*)_ptr__13->data, _ptr__13->len[0]);
    __arText_Stream_Char((void*)&buffer, arText_Buffer__typ, ' ');
  }
  if (module->extFlags != NIL) {
    _ptr__12 = module->extFlags;
    __arText_Stream_String((void*)&buffer, arText_Buffer__typ, (void*)_ptr__12->data, _ptr__12->len[0]);
    __arText_Stream_Char((void*)&buffer, arText_Buffer__typ, ' ');
  }
  if (main) {
    __arText_Stream_String((void*)&buffer, arText_Buffer__typ, (CHAR*)"-m ", 4);
  }
  _ptr__11 = module->file;
  __arText_Stream_String((void*)&buffer, arText_Buffer__typ, (void*)_ptr__11->data, _ptr__11->len[0]);
  if (!OMake_script->value) {
    Console_String((CHAR*)"Building Module ", 17);
    _ptr__10 = module->name;
    Console_String((void*)_ptr__10->data, _ptr__10->len[0]);
    Console_Ln();
  }
  result = OMake_Run((void*)__arText_Buffer_GetString(&buffer, arText_Buffer__typ));
  module->built = 1;
  return result == 0;
}

static BOOLEAN OMake_LinkModule (OMake_Module module, arStringList_List libs, arStringList_List objs)
{
  arText_Buffer buffer = {0};
  INTEGER i, result;
  arStringList_List l = NIL;
  arStringList_List flag = NIL;
  arStrings_StringPtr name = NIL;
  arStringList_List omitLibs = NIL;
  arStrings_StringPtr _ptr__22 = NIL;
  INTEGER _for__21;
  arStrings_StringPtr _ptr__20 = NIL;
  arStrings_StringPtr _ptr__19 = NIL;
  arStrings_StringPtr _ptr__18 = NIL;
  omitLibs = NIL;
  __arText_Buffer_Init(&buffer, arText_Buffer__typ, 128);
  _ptr__22 = OMake_linker->value;
  __arText_Stream_String((void*)&buffer, arText_Buffer__typ, (void*)_ptr__22->data, _ptr__22->len[0]);
  __arText_Stream_String((void*)&buffer, arText_Buffer__typ, (CHAR*)" ", 2);
  if (OMake_sRequire != NIL) {
    _for__21 = OMake_sRequire->len[0] - 1;
    i = 0;
    while (i <= _for__21) {
      arStringList_Include(&libs, (OMake_sRequire->data)[__X(i, OMake_sRequire->len[0], (CHAR*)"OMake", 153120)]);
      i += 1;
    }
  }
  l = libs;
  while (l != NIL) {
    flag = arStringAssoc_GetAll(OMake_linkFlags->value, l->name->data, l->name->len[0]);
    while (flag != NIL) {
      name = flag->name;
      if (arStrings_Equal(name->data, name->len[0], (CHAR*)"NOLIB", 6)) {
        arStringList_Include(&omitLibs, l->name);
      } else {
        __arText_Stream_String((void*)&buffer, arText_Buffer__typ, (void*)name->data, name->len[0]);
        __arText_Stream_Char((void*)&buffer, arText_Buffer__typ, ' ');
      }
      flag = flag->next;
    }
    l = l->next;
  }
  l = objs;
  while (l != NIL) {
    _ptr__20 = l->name;
    __arText_Stream_String((void*)&buffer, arText_Buffer__typ, (void*)_ptr__20->data, _ptr__20->len[0]);
    __arText_Stream_String((void*)&buffer, arText_Buffer__typ, (CHAR*)".c ", 4);
    l = l->next;
  }
  __arText_Stream_String((void*)&buffer, arText_Buffer__typ, (CHAR*)"-o ", 4);
  _ptr__19 = module->name;
  __arText_Stream_String((void*)&buffer, arText_Buffer__typ, (void*)_ptr__19->data, _ptr__19->len[0]);
  __arText_Stream_Char((void*)&buffer, arText_Buffer__typ, ' ');
  l = libs;
  while (l != NIL) {
    if (!arStringList_Contains(omitLibs, l->name)) {
      __arText_Stream_String((void*)&buffer, arText_Buffer__typ, (CHAR*)"-l", 3);
      _ptr__18 = l->name;
      __arText_Stream_String((void*)&buffer, arText_Buffer__typ, (void*)_ptr__18->data, _ptr__18->len[0]);
      __arText_Stream_Char((void*)&buffer, arText_Buffer__typ, ' ');
    }
    l = l->next;
  }
  result = OMake_Run((void*)__arText_Buffer_GetString(&buffer, arText_Buffer__typ));
  return result == 0;
}

static void OMake_BuildModule (OMake_Module module)
{
  arStringList_List libs = NIL;
  arStringList_List objs = NIL;
  arStrings_StringPtr _ptr__3 = NIL;
  libs = NIL;
  objs = NIL;
  if (OMake_script->value) {
    Console_String((CHAR*)"# OMake generated script for ", 30);
    _ptr__3 = module->name;
    Console_String((void*)_ptr__3->data, _ptr__3->len[0]);
    Console_Ln();
  }
  if (OMake_CompileModule(module, &libs, &objs, 1)) {
    if (OMake_LinkModule(module, libs, objs)) {
    }
  }
}

static OMake_Module OMake_ProcessFile (arStrings_StringPtr name)
{
  arStrings_StringPtr file = NIL;
  arStrings_StringPtr library = NIL;
  OMake_Module module = NIL;
  if (arStrings_LastIndexOf(name->data, name->len[0], '.', -1) >= 0) {
    return OMake_ParseFile(name);
  } else {
    OMake_LocateModule(name->data, name->len[0], &file, &library);
    if (file == NIL) {
      Console_String((CHAR*)"Cannot locate module source ", 29);
      Console_String((void*)name->data, name->len[0]);
      Console_Ln();
      Kernel_Exit(1);
    }
    return OMake_ParseFile(file);
  }
  __RETCHK((CHAR*)"OMake", 173567);
}

static void OMake_Command (void)
{
  INTEGER pos;
  OMake_Module m = NIL;
  arStrings_StringPtr _ptr__8 = NIL;
  arStrings_StringPtr _ptr__7 = NIL;
  arStrings_StringPtr _ptr__6 = NIL;
  OMake_debug = arConfiguration_NewBoolean((CHAR*)"debug", 6, (CHAR*)"Debug output", 13, 0);
  OMake_path = arConfiguration_NewString((CHAR*)"source", 7, (CHAR*)"Search path for Oberon source modules", 38, (CHAR*)"", 1);
  OMake_extensions = arConfiguration_NewAssoc((CHAR*)"extension", 10, (CHAR*)"Define compiler flags for accepted extensions", 46, 1);
  OMake_exclude = arConfiguration_NewString((CHAR*)"exclude", 8, (CHAR*)"Don\'t parse these module sources", 33, (CHAR*)"Platform,SYSTEM", 16);
  OMake_require = arConfiguration_NewString((CHAR*)"require", 8, (CHAR*)"Libraries which must always be linked", 38, (CHAR*)"Ofront", 7);
  OMake_libraries = arConfiguration_NewAssoc((CHAR*)"lib", 4, (CHAR*)"Define library source location", 31, 0);
  OMake_linkFlags = arConfiguration_NewAssoc((CHAR*)"linkflag", 9, (CHAR*)"Define linker flags for library", 32, 1);
  OMake_compiler = arConfiguration_NewString((CHAR*)"compile", 8, (CHAR*)"Compile command", 16, (CHAR*)"Ofront+", 8);
  OMake_linker = arConfiguration_NewString((CHAR*)"link", 5, (CHAR*)"Link command", 13, (CHAR*)"gcc", 4);
  OMake_script = arConfiguration_NewBoolean((CHAR*)"script", 7, (CHAR*)"Generate script instead of building", 36, 0);
  if (arConfiguration_ReadOptions((CHAR*)"omake.ini", 10)) {
  }
  pos = 1;
  arConfiguration_ScanOptions(&pos);
  while (pos < arConfiguration_argv->len[0]) {
    OMake_sPath = (_ptr__8 = OMake_path->value, 
      arPattern_Split((void*)_ptr__8->data, _ptr__8->len[0], ','));
    OMake_sExclude = (_ptr__7 = OMake_exclude->value, 
      arPattern_Split((void*)_ptr__7->data, _ptr__7->len[0], ','));
    OMake_sRequire = (_ptr__6 = OMake_require->value, 
      arPattern_Split((void*)_ptr__6->data, _ptr__6->len[0], ','));
    m = OMake_ProcessFile((arConfiguration_argv->data)[__X(pos, arConfiguration_argv->len[0], (CHAR*)"OMake", 180511)]);
    OMake_BuildModule(m);
    pos += 1;
    arConfiguration_ScanOptions(&pos);
  }
  arConfiguration_CheckFinished(pos);
}

static void EnumPtrs(void (*P)(void*))
{
  P(OMake_path);
  P(OMake_exclude);
  P(OMake_require);
  P(OMake_debug);
  P(OMake_script);
  P(OMake_compiler);
  P(OMake_linker);
  P(OMake_libraries);
  P(OMake_linkFlags);
  P(OMake_extensions);
  P(OMake_builtin);
  P(OMake_sPath);
  P(OMake_sExclude);
  P(OMake_sRequire);
  P(OMake_modules);
  P(OMake_keywords);
  P(OMake_makeKeywords);
}

__TDESC(OMake_Keyword__rec__desc, 2, 2) = {__TDFLDS("Keyword__rec", 24), {0, 16, -24}};
__TDESC(OMake_Import__rec__desc, 2, 3) = {__TDFLDS("Import__rec", 24), {0, 8, 16, -32}};
__TDESC(OMake_Module__rec__desc, 2, 7) = {__TDFLDS("Module__rec", 64), {0, 8, 24, 32, 40, 48, 56, -64}};

int main (int argc, char **argv)
{
  __INIT(argc, argv);
  __IMPORT(arArgs__init);
  __IMPORT(arConfiguration__init);
  __IMPORT(arChar__init);
  __IMPORT(Console__init);
  __IMPORT(Files__init);
  __IMPORT(Kernel__init);
  __IMPORT(arOut__init);
  __IMPORT(arPath__init);
  __IMPORT(arPattern__init);
  __IMPORT(Platform__init);
  __IMPORT(arStringAssoc__init);
  __IMPORT(arStringList__init);
  __IMPORT(arStrings__init);
  __IMPORT(arText__init);
  __REGMAIN("OMake", EnumPtrs);
  __INITYP(OMake_Keyword__rec, OMake_Keyword__rec, 0);
  __INITYP(OMake_Import__rec, OMake_Import__rec, 0);
  __INITYP(OMake_Module__rec, OMake_Module__rec, 0);
/* BEGIN */
  OMake_modules = NIL;
  OMake_libraries = NIL;
  OMake_keywords = NIL;
  OMake_AddSymbol((CHAR*)"LINK", 5, 300);
  OMake_makeKeywords = OMake_keywords;
  OMake_keywords = NIL;
  OMake_AddSymbol((CHAR*)"MODULE", 7, 200);
  OMake_AddSymbol((CHAR*)"IMPORT", 7, 201);
  OMake_Command();
  __FINI;
}
