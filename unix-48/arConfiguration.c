/* Ofront+ 1.0 -s2 -48 */
#include "SYSTEM.oh"
#include "Kernel.oh"
#include "Console.oh"
#include "arArgs.oh"
#include "Files.oh"
#include "Platform.oh"
#include "arSize.oh"
#include "arStringAssoc.oh"
#include "arStrings.oh"
#include "arStringList.oh"
#include "arPattern.oh"

typedef
  struct arConfiguration_Assoc__rec *arConfiguration_Assoc;

typedef
  struct arConfiguration_ValueDesc *arConfiguration_Value;

typedef
  struct arConfiguration_ValueDesc {
    arStrings_StringPtr name, synopsis, desc;
    arConfiguration_Value next;
  } arConfiguration_ValueDesc;

export void arConfiguration_Value_Accept (arConfiguration_Value self, arStringList_Array argv, INTEGER *pos);
export void arConfiguration_Value_Format (arConfiguration_Value self);
export void arConfiguration_Value_Init (arConfiguration_Value self, CHAR *name, INTEGER name__len, CHAR *desc, INTEGER desc__len);
#define __arConfiguration_Value_Accept(self, argv, pos) __SEND(__TYPEOF(self), arConfiguration_Value_Accept, 1, void(*)(arConfiguration_Value, arStringList_Array, INTEGER*), (self, argv, pos))
#define __arConfiguration_Value_Format(self) __SEND(__TYPEOF(self), arConfiguration_Value_Format, 2, void(*)(arConfiguration_Value), (self))
#define __arConfiguration_Value_Init(self, name, name__len, desc, desc__len) __SEND(__TYPEOF(self), arConfiguration_Value_Init, 3, void(*)(arConfiguration_Value, CHAR*, INTEGER , CHAR*, INTEGER ), (self, name, name__len, desc, desc__len))

typedef
  struct arConfiguration_Assoc__rec { /* arConfiguration_ValueDesc */
    arStrings_StringPtr name, synopsis, desc;
    arConfiguration_Value next;
    arStringAssoc_Assoc value;
    BOOLEAN multi;
  } arConfiguration_Assoc__rec;

export void arConfiguration_Assoc_Accept (arConfiguration_Assoc self, arStringList_Array argv, INTEGER *pos);

typedef
  struct arConfiguration_Boolean__rec *arConfiguration_Boolean;

typedef
  struct arConfiguration_Boolean__rec { /* arConfiguration_ValueDesc */
    arStrings_StringPtr name, synopsis, desc;
    arConfiguration_Value next;
    BOOLEAN value;
  } arConfiguration_Boolean__rec;

export void arConfiguration_Boolean_Accept (arConfiguration_Boolean self, arStringList_Array argv, INTEGER *pos);
export void arConfiguration_Boolean_Format (arConfiguration_Boolean self);

typedef
  void (*arConfiguration_Handler)(arStringList_Array, INTEGER*);

typedef
  struct arConfiguration_Integer__rec *arConfiguration_Integer;

typedef
  struct arConfiguration_Integer__rec { /* arConfiguration_ValueDesc */
    arStrings_StringPtr name, synopsis, desc;
    arConfiguration_Value next;
    SHORTINT value, min, max;
  } arConfiguration_Integer__rec;

export void arConfiguration_Integer_Accept (arConfiguration_Integer self, arStringList_Array argv, INTEGER *pos);
export void arConfiguration_Integer_Format (arConfiguration_Integer self);

typedef
  struct arConfiguration_Procedure__rec *arConfiguration_Procedure;

typedef
  struct arConfiguration_Procedure__rec { /* arConfiguration_ValueDesc */
    arStrings_StringPtr name, synopsis, desc;
    arConfiguration_Value next;
    arConfiguration_Handler value;
  } arConfiguration_Procedure__rec;

export void arConfiguration_Procedure_Accept (arConfiguration_Procedure self, arStringList_Array argv, INTEGER *pos);

typedef
  struct arConfiguration_String__rec *arConfiguration_String;

typedef
  struct arConfiguration_String__rec { /* arConfiguration_ValueDesc */
    arStrings_StringPtr name, synopsis, desc;
    arConfiguration_Value next;
    arStrings_StringPtr value;
  } arConfiguration_String__rec;

export void arConfiguration_String_Accept (arConfiguration_String self, arStringList_Array argv, INTEGER *pos);
export void arConfiguration_String_Format (arConfiguration_String self);


static INTEGER arConfiguration_argc;
export arStringList_Array arConfiguration_argv;
export arConfiguration_Value arConfiguration_values;
static arStrings_StringPtr arConfiguration_banner;
static arConfiguration_Assoc arConfiguration_settings;

export void **arConfiguration_ValueDesc__typ;
export void **arConfiguration_Boolean__rec__typ;
export void **arConfiguration_Integer__rec__typ;
export void **arConfiguration_String__rec__typ;
export void **arConfiguration_Procedure__rec__typ;
export void **arConfiguration_Assoc__rec__typ;

export void arConfiguration_CheckFinished (INTEGER pos);
export BOOLEAN arConfiguration_CheckOption (INTEGER *pos);
static arStringList_Array arConfiguration_CopyArgVec (arArgs_ArgVec p);
static void arConfiguration_Error (void);
static arConfiguration_Value arConfiguration_FindOption (CHAR *name, INTEGER name__len);
export void arConfiguration_GetArg (arStringList_Array argv, INTEGER *pos, arStrings_StringPtr *arg);
static void arConfiguration_Help (arStringList_Array argv, INTEGER *pos);
export arConfiguration_Assoc arConfiguration_NewAssoc (CHAR *name, INTEGER name__len, CHAR *desc, INTEGER desc__len, BOOLEAN multi);
export arConfiguration_Boolean arConfiguration_NewBoolean (CHAR *name, INTEGER name__len, CHAR *desc, INTEGER desc__len, BOOLEAN default_);
export arConfiguration_Integer arConfiguration_NewInteger (CHAR *name, INTEGER name__len, CHAR *desc, INTEGER desc__len, SHORTINT default_, SHORTINT min, SHORTINT max);
export void arConfiguration_NewProcedure (CHAR *name, INTEGER name__len, CHAR *desc, INTEGER desc__len, arConfiguration_Handler value);
export arConfiguration_String arConfiguration_NewString (CHAR *name, INTEGER name__len, CHAR *desc, INTEGER desc__len, CHAR *default_, INTEGER default___len);
static void arConfiguration_OutString (CHAR *string, INTEGER string__len);
export BOOLEAN arConfiguration_ParseBoolean (CHAR *arg, INTEGER arg__len, BOOLEAN *result);
export BOOLEAN arConfiguration_ParseInteger (CHAR *arg, INTEGER arg__len, SHORTINT *result);
static void arConfiguration_Read (arStringList_Array argv, INTEGER *pos);
static BOOLEAN arConfiguration_ReadLineFromFile (CHAR *line, INTEGER line__len, Files_Rider *rd, void **rd__typ);
export BOOLEAN arConfiguration_ReadOptions (CHAR *fileName, INTEGER fileName__len);
export void arConfiguration_ScanOptions (INTEGER *pos);
export void arConfiguration_SetBanner (CHAR *text, INTEGER text__len);
static void arConfiguration_Spaces (INTEGER count);
static void arConfiguration_StringWidth (CHAR *value, INTEGER value__len, SHORTINT width);
export void arConfiguration_Usage (void);


/*============================================================================*/

static arStringList_Array arConfiguration_CopyArgVec (arArgs_ArgVec p)
{
  SHORTINT len, strLen, i, j;
  arStringList_Array result = NIL;
  SHORTINT _for__17, _for__16;
  len = 0;
  while ((*p)[__X(len, 1024, (CHAR*)"arConfiguration", 36627)] != NIL) {
    len += 1;
  }
  result = __NEWARR(POINTER__typ, 4, 4, 1, 1, (SYSTEM_ARRLEN)len);
  _for__17 = len - 1;
  i = 0;
  while (i <= _for__17) {
    strLen = 0;
    while ((*(*p)[__X(i, 1024, (CHAR*)"arConfiguration", 38425)])[__X(strLen, 1024, (CHAR*)"arConfiguration", 38425)] != 0x00) {
      strLen += 1;
    }
    (result->data)[__X(i, result->len[0], (CHAR*)"arConfiguration", 39450)] = __NEWARR(NIL, 1, 1, 1, 1, (SYSTEM_ARRLEN)(strLen + 1));
    _for__16 = strLen;
    j = 0;
    while (j <= _for__16) {
      ((result->data)[__X(i, result->len[0], (CHAR*)"arConfiguration", 40191)]->data)[__X(j, (result->data)[__X(i, result->len[0], (CHAR*)"arConfiguration", 40191)]->len[0], (CHAR*)"arConfiguration", 40191)] = (*(*p)[__X(i, 1024, (CHAR*)"arConfiguration", 40191)])[__X(j, 1024, (CHAR*)"arConfiguration", 40191)];
      j += 1;
    }
    i += 1;
  }
  return result;
}

void arConfiguration_Value_Init (arConfiguration_Value self, CHAR *name, INTEGER name__len, CHAR *desc, INTEGER desc__len)
{
  arStringList_Array parts = NIL;
  __DUP(name, name__len);
  __DUP(desc, desc__len);
  self->synopsis = arStringList_Copy(name, name__len);
  parts = arPattern_Split((void*)name, name__len, ' ');
  self->name = (parts->data)[0];
  self->desc = arStringList_Copy(desc, desc__len);
  self->next = arConfiguration_values;
  arConfiguration_values = self;
}

/*----------------------------------------------------------------------------*/
void arConfiguration_Value_Format (arConfiguration_Value self)
{
}

/*----------------------------------------------------------------------------*/
void arConfiguration_Value_Accept (arConfiguration_Value self, arStringList_Array argv, INTEGER *pos)
{
}

/*----------------------------------------------------------------------------*/
static void arConfiguration_Spaces (INTEGER count)
{
  while (count > 0) {
    Console_Char(' ');
    count -= 1;
  }
}

static void arConfiguration_OutString (CHAR *string, INTEGER string__len)
{
  INTEGER i;
  CHAR ch;
  __DUP(string, string__len);
  i = 0;
  for (;;) {
    ch = string[__X(i, string__len, (CHAR*)"arConfiguration", 53265)];
    if (ch == 0x00) {
      return;
    }
    i += 1;
    if (ch == '\\') {
      if (string[__X(i, string__len, (CHAR*)"arConfiguration", 55302)] == 'n') {
        Console_Ln();
        i += 1;
      } else {
        Console_Char(ch);
      }
    } else {
      Console_Char(ch);
    }
  }
}

void arConfiguration_Usage (void)
{
  arConfiguration_Value value = NIL;
  INTEGER nameWidth, descWidth, length, sLength;
  arStrings_StringPtr _ptr__48 = NIL;
  arStrings_StringPtr _ptr__47 = NIL;
  arStrings_StringPtr _ptr__46 = NIL;
  arStrings_StringPtr _ptr__45 = NIL;
  arStrings_StringPtr _ptr__44 = NIL;
  arStrings_StringPtr _ptr__43 = NIL;
  if (arConfiguration_banner != NIL) {
    arConfiguration_OutString(arConfiguration_banner->data, arConfiguration_banner->len[0]);
  }
  nameWidth = 0;
  descWidth = 0;
  length = 0;
  value = arConfiguration_values;
  while (value != NIL) {
    nameWidth = arSize_Max(nameWidth, (_ptr__48 = value->synopsis, 
      arStrings_Length(_ptr__48->data, _ptr__48->len[0])));
    descWidth = arSize_Max(descWidth, (_ptr__47 = value->desc, 
      arStrings_Length(_ptr__47->data, _ptr__47->len[0])));
    length += 1;
    value = value->next;
  }
  nameWidth = arSize_Min(nameWidth, 15);
  if (length > 0) {
    Console_String((CHAR*)"Options:", 9);
    Console_Ln();
    value = arConfiguration_values;
    while (value != NIL) {
      Console_String((CHAR*)"  ", 3);
      Console_Char('-');
      _ptr__46 = value->synopsis;
      Console_String((void*)_ptr__46->data, _ptr__46->len[0]);
      sLength = (_ptr__45 = value->synopsis, 
        arStrings_Length(_ptr__45->data, _ptr__45->len[0]));
      if (sLength > nameWidth) {
        Console_Ln();
        arConfiguration_Spaces(3 + nameWidth);
      } else {
        arConfiguration_Spaces(nameWidth - sLength);
      }
      Console_String((CHAR*)"  ", 3);
      _ptr__44 = value->desc;
      Console_String((void*)_ptr__44->data, _ptr__44->len[0]);
      arConfiguration_Spaces((1 + descWidth) - (_ptr__43 = value->desc, 
        arStrings_Length(_ptr__43->data, _ptr__43->len[0])));
      Console_Char('(');
      __arConfiguration_Value_Format(value);
      Console_Char(')');
      Console_Ln();
      value = value->next;
    }
  }
}

/*----------------------------------------------------------------------------*/
static void arConfiguration_Error (void)
{
  arConfiguration_Usage();
  Kernel_Exit(1);
}

static void arConfiguration_Help (arStringList_Array argv, INTEGER *pos)
{
  arConfiguration_Usage();
  Kernel_Exit(0);
}

void arConfiguration_GetArg (arStringList_Array argv, INTEGER *pos, arStrings_StringPtr *arg)
{
  if (*pos < argv->len[0]) {
    *arg = arPattern_Substitute((argv->data)[__X(*pos, argv->len[0], (CHAR*)"arConfiguration", 74289)]->data, (argv->data)[__X(*pos, argv->len[0], (CHAR*)"arConfiguration", 74289)]->len[0], arConfiguration_settings->value);
    *pos += 1;
  } else {
    Console_String((CHAR*)"Missing argument at position ", 30);
    Console_Int(*pos, 0);
    Console_Ln();
    arConfiguration_Error();
  }
}

/*----------------------------------------------------------------------------*/
BOOLEAN arConfiguration_ParseInteger (CHAR *arg, INTEGER arg__len, SHORTINT *result)
{
  SHORTINT value, sign, pos;
  CHAR ch;
  value = 0;
  sign = 1;
  pos = 0;
  ch = arg[0];
  if (ch == '-') {
    sign = -1;
    pos += 1;
    ch = arg[__X(pos, arg__len, (CHAR*)"arConfiguration", 79386)];
  }
  while (ch >= '0' && ch <= '9') {
    value = (value * 10 + (SHORTINT)ch) - 48;
    pos += 1;
    ch = arg[__X(pos, arg__len, (CHAR*)"arConfiguration", 80410)];
  }
  if (ch != 0x00) {
    return 0;
  }
  *result = value * sign;
  return 1;
}

/*----------------------------------------------------------------------------*/
BOOLEAN arConfiguration_ParseBoolean (CHAR *arg, INTEGER arg__len, BOOLEAN *result)
{
  if (arStrings_Equal((void*)arg, arg__len, (CHAR*)"TRUE", 5)) {
    *result = 1;
  } else if (arStrings_Equal((void*)arg, arg__len, (CHAR*)"FALSE", 6)) {
    *result = 0;
  } else {
    return 0;
  }
  return 1;
}

/*----------------------------------------------------------------------------*/
static arConfiguration_Value arConfiguration_FindOption (CHAR *name, INTEGER name__len)
{
  arConfiguration_Value value = NIL;
  arStrings_StringPtr _ptr__20 = NIL;
  __DUP(name, name__len);
  value = arConfiguration_values;
  while (value != NIL) {
    if (_ptr__20 = value->name, 
      arStrings_Equal(_ptr__20->data, _ptr__20->len[0], (void*)name, name__len)) {
      return value;
    }
    value = value->next;
  }
  return NIL;
}

BOOLEAN arConfiguration_CheckOption (INTEGER *pos)
{
  arStrings_StringPtr arg = NIL;
  arConfiguration_Value value = NIL;
  arStrings_StringPtr option = NIL;
  INTEGER length;
  arg = (arConfiguration_argv->data)[__X(*pos, arConfiguration_argv->len[0], (CHAR*)"arConfiguration", 91921)];
  if ((arg->data)[0] == '-') {
    *pos += 1;
    length = arStrings_Length(arg->data, arg->len[0]);
    option = __NEWARR(NIL, 1, 1, 1, 1, (SYSTEM_ARRLEN)length);
    arStrings_Extract(arg->data, arg->len[0], 1, length - 1, option->data, option->len[0]);
    value = arConfiguration_FindOption(option->data, option->len[0]);
    if (value == NIL) {
      Console_String((CHAR*)"ERROR: Unknown option: ", 24);
      Console_String((void*)option->data, option->len[0]);
      Console_Ln();
      arConfiguration_Error();
    }
    __arConfiguration_Value_Accept(value, arConfiguration_argv, pos);
    return 1;
  }
  return 0;
}

/*----------------------------------------------------------------------------*/
void arConfiguration_ScanOptions (INTEGER *pos)
{
  while (*pos < arConfiguration_argc && arConfiguration_CheckOption(pos)) {
  }
}

/*----------------------------------------------------------------------------*/
void arConfiguration_SetBanner (CHAR *text, INTEGER text__len)
{
  __DUP(text, text__len);
  arConfiguration_banner = arStringList_Copy(text, text__len);
}

/*----------------------------------------------------------------------------*/
static BOOLEAN arConfiguration_ReadLineFromFile (CHAR *line, INTEGER line__len, Files_Rider *rd, void **rd__typ)
{
  SHORTINT i;
  CHAR ch;
  i = 0;
  Files_ReadChar(rd, rd__typ, &ch);
  if (ch == 0x00) {
    return 0;
  }
  while (ch != 0x0a && ch != 0x00) {
    if (ch != 0x0d && (INTEGER)i < line__len - 1) {
      line[__X(i, line__len, (CHAR*)"arConfiguration", 102672)] = ch;
      i += 1;
    }
    Files_ReadChar(rd, rd__typ, &ch);
  }
  line[__X(i, line__len, (CHAR*)"arConfiguration", 103694)] = 0x00;
  return 1;
}

static struct ReadOptions__33 {
  CHAR *fileName;
  INTEGER fileName__len;
  SHORTINT *nLines;
  struct ReadOptions__33 *lnk;
} *ReadOptions__33_s;

static void __35 (CHAR *reason, INTEGER reason__len, CHAR *context, INTEGER context__len);

static void __35 (CHAR *reason, INTEGER reason__len, CHAR *context, INTEGER context__len)
{
  __DUP(reason, reason__len);
  __DUP(context, context__len);
  Console_String((CHAR*)"ERROR: ", 8);
  Console_String((void*)reason, reason__len);
  Console_String((CHAR*)" \'", 3);
  Console_String((void*)context, context__len);
  Console_String((CHAR*)"\' on line ", 11);
  Console_Int((*ReadOptions__33_s->nLines), 0);
  Console_String((CHAR*)" of file ", 10);
  Console_String((void*)ReadOptions__33_s->fileName, ReadOptions__33_s->fileName__len);
  Console_Ln();
  arConfiguration_Error();
}

BOOLEAN arConfiguration_ReadOptions (CHAR *fileName, INTEGER fileName__len)
{
  CHAR line[1024];
  SHORTINT nLines;
  arStringList_Array match = NIL;
  Files_Rider rd = {0};
  Files_File file = NIL;
  arStrings_StringPtr name = NIL;
  arConfiguration_Value value = NIL;
  INTEGER pos;
  arStrings_StringPtr _ptr__34 = NIL;
  struct ReadOptions__33 _s;
  BOOLEAN __retval;
  __DUP(fileName, fileName__len);
  _s.fileName = (void*)fileName; _s.fileName__len = fileName__len;
  _s.nLines = &nLines;
  _s.lnk = ReadOptions__33_s;
  ReadOptions__33_s = &_s;
  file = Files_Old((void*)fileName, fileName__len);
  if (file == NIL) {
    __retval = 0;
    ReadOptions__33_s = _s.lnk;
    ;
    return __retval;
  }
  Files_Set(&rd, Files_Rider__typ, file, 0);
  nLines = 0;
  while (arConfiguration_ReadLineFromFile((void*)line, 1024, &rd, Files_Rider__typ)) {
    nLines += 1;
    if (line[0] == 0x00 || line[0] == '#') {
    } else if (arPattern_Match((CHAR*)"*: *", 5, (void*)line, 1024, &match)) {
      name = (match->data)[0];
      value = arConfiguration_FindOption(name->data, name->len[0]);
      if (value == NIL) {
        __35((CHAR*)"Unknown option", 15, name->data, name->len[0]);
      }
      match = (_ptr__34 = (match->data)[__X(1, match->len[0], (CHAR*)"arConfiguration", 114978)], 
        arPattern_ParseArgs((void*)_ptr__34->data, _ptr__34->len[0]));
      pos = 0;
      __arConfiguration_Value_Accept(value, match, &pos);
    } else {
      __35((CHAR*)"Malformed line", 15, line, 1024);
    }
  }
  Files_Close(file);
  __retval = 1;
  ReadOptions__33_s = _s.lnk;
  ;
  return __retval;
}

/*----------------------------------------------------------------------------*/
static void arConfiguration_Read (arStringList_Array argv, INTEGER *pos)
{
  arStrings_StringPtr arg = NIL;
  arConfiguration_GetArg(argv, pos, &arg);
  if (!arConfiguration_ReadOptions(arg->data, arg->len[0])) {
    Console_String((CHAR*)"Cannot read file: ", 19);
    Console_String((void*)arg->data, arg->len[0]);
    Console_Ln();
    arConfiguration_Error();
  }
}

void arConfiguration_CheckFinished (INTEGER pos)
{
  if (pos != arConfiguration_argc) {
    Console_String((CHAR*)"Unexpected arguments", 21);
    Console_Ln();
    arConfiguration_Error();
  }
}

/*----------------------------------------------------------------------------*/
void arConfiguration_Boolean_Format (arConfiguration_Boolean self)
{
  if (self->value) {
    Console_String((CHAR*)"TRUE", 5);
  } else {
    Console_String((CHAR*)"FALSE", 6);
  }
}

/*----------------------------------------------------------------------------*/
void arConfiguration_Boolean_Accept (arConfiguration_Boolean self, arStringList_Array argv, INTEGER *pos)
{
  arStrings_StringPtr arg = NIL;
  if (*pos < argv->len[0]) {
    arg = (argv->data)[__X(*pos, argv->len[0], (CHAR*)"arConfiguration", 126994)];
    if (arConfiguration_ParseBoolean((void*)arg->data, arg->len[0], &self->value)) {
      *pos += 1;
      return;
    }
  }
  self->value = !self->value;
}

/*----------------------------------------------------------------------------*/
arConfiguration_Boolean arConfiguration_NewBoolean (CHAR *name, INTEGER name__len, CHAR *desc, INTEGER desc__len, BOOLEAN default_)
{
  arConfiguration_Boolean result = NIL;
  __DUP(name, name__len);
  __DUP(desc, desc__len);
  __NEW(result, arConfiguration_Boolean__rec);
  __arConfiguration_Value_Init((void*)result, name, name__len, desc, desc__len);
  result->value = default_;
  return result;
}

/*----------------------------------------------------------------------------*/
void arConfiguration_Integer_Format (arConfiguration_Integer self)
{
  Console_Int(self->value, 0);
}

/*----------------------------------------------------------------------------*/
void arConfiguration_Integer_Accept (arConfiguration_Integer self, arStringList_Array argv, INTEGER *pos)
{
  arStrings_StringPtr arg = NIL;
  SHORTINT value;
  arConfiguration_GetArg(argv, pos, &arg);
  if (!arConfiguration_ParseInteger((void*)arg->data, arg->len[0], &value)) {
    Console_String((CHAR*)"ERROR: Illegal Integer value: ", 31);
    Console_String((void*)arg->data, arg->len[0]);
    Console_Ln();
    arConfiguration_Error();
  }
  if ((self->min != -32767 && value < self->min) || (self->max != -32767 && value > self->max)) {
    Console_String((CHAR*)"ERROR: Value ", 14);
    Console_Int(value, 0);
    if (self->min == -32767) {
      Console_String((CHAR*)" is greater than maximum of ", 29);
      Console_Int(self->max, 0);
    } else if (self->max == -32767) {
      Console_String((CHAR*)" is less than minimum of ", 26);
      Console_Int(self->min, 0);
    } else {
      Console_String((CHAR*)" out of range ", 15);
      Console_Int(self->min, 0);
      Console_String((CHAR*)" ... ", 6);
      Console_Int(self->max, 0);
    }
    Console_Ln();
    arConfiguration_Error();
  }
  self->value = value;
}

/*----------------------------------------------------------------------------*/
arConfiguration_Integer arConfiguration_NewInteger (CHAR *name, INTEGER name__len, CHAR *desc, INTEGER desc__len, SHORTINT default_, SHORTINT min, SHORTINT max)
{
  arConfiguration_Integer result = NIL;
  __DUP(name, name__len);
  __DUP(desc, desc__len);
  __NEW(result, arConfiguration_Integer__rec);
  __arConfiguration_Value_Init((void*)result, name, name__len, desc, desc__len);
  result->value = default_;
  result->min = min;
  result->max = max;
  return result;
}

/*----------------------------------------------------------------------------*/
static void arConfiguration_StringWidth (CHAR *value, INTEGER value__len, SHORTINT width)
{
  SHORTINT i;
  INTEGER length;
  SHORTINT _for__41;
  __DUP(value, value__len);
  length = arStrings_Length((void*)value, value__len);
  if (length > (INTEGER)(width - 3)) {
    _for__41 = width - 4;
    i = 0;
    while (i <= _for__41) {
      Console_Char(value[__X(i, value__len, (CHAR*)"arConfiguration", 147199)]);
      i += 1;
    }
    Console_String((CHAR*)"...", 4);
  } else {
    Console_String((void*)value, value__len);
  }
}

void arConfiguration_String_Format (arConfiguration_String self)
{
  arStrings_StringPtr _ptr__12 = NIL;
  Console_Char('\"');
  _ptr__12 = self->value;
  Console_String((void*)_ptr__12->data, _ptr__12->len[0]);
  Console_Char('\"');
}

/*----------------------------------------------------------------------------*/
void arConfiguration_String_Accept (arConfiguration_String self, arStringList_Array argv, INTEGER *pos)
{
  arConfiguration_GetArg(argv, pos, &self->value);
}

/*----------------------------------------------------------------------------*/
arConfiguration_String arConfiguration_NewString (CHAR *name, INTEGER name__len, CHAR *desc, INTEGER desc__len, CHAR *default_, INTEGER default___len)
{
  arConfiguration_String result = NIL;
  __DUP(name, name__len);
  __DUP(desc, desc__len);
  __DUP(default_, default___len);
  __NEW(result, arConfiguration_String__rec);
  __arConfiguration_Value_Init((void*)result, name, name__len, desc, desc__len);
  result->value = arStringList_Copy(default_, default___len);
  return result;
}

/*----------------------------------------------------------------------------*/
void arConfiguration_Procedure_Accept (arConfiguration_Procedure self, arStringList_Array argv, INTEGER *pos)
{
  (*self->value)(argv, pos);
}

/*----------------------------------------------------------------------------*/
void arConfiguration_NewProcedure (CHAR *name, INTEGER name__len, CHAR *desc, INTEGER desc__len, arConfiguration_Handler value)
{
  arConfiguration_Procedure result = NIL;
  __DUP(name, name__len);
  __DUP(desc, desc__len);
  __NEW(result, arConfiguration_Procedure__rec);
  __arConfiguration_Value_Init((void*)result, name, name__len, desc, desc__len);
  result->value = value;
}

/*----------------------------------------------------------------------------*/
void arConfiguration_Assoc_Accept (arConfiguration_Assoc self, arStringList_Array argv, INTEGER *pos)
{
  arStrings_StringPtr key = NIL;
  arStrings_StringPtr value = NIL;
  arConfiguration_GetArg(argv, pos, &key);
  arConfiguration_GetArg(argv, pos, &value);
  if (self->multi) {
    arStringAssoc_Set0(&self->value, key->data, key->len[0], value->data, value->len[0]);
  } else {
    arStringAssoc_Set(&self->value, key->data, key->len[0], value->data, value->len[0]);
  }
}

/*----------------------------------------------------------------------------*/
arConfiguration_Assoc arConfiguration_NewAssoc (CHAR *name, INTEGER name__len, CHAR *desc, INTEGER desc__len, BOOLEAN multi)
{
  arConfiguration_Assoc result = NIL;
  __DUP(name, name__len);
  __DUP(desc, desc__len);
  __NEW(result, arConfiguration_Assoc__rec);
  __arConfiguration_Value_Init((void*)result, name, name__len, desc, desc__len);
  result->value = NIL;
  result->multi = multi;
  return result;
}

/*----------------------------------------------------------------------------*/
static void EnumPtrs(void (*P)(void*))
{
  P(arConfiguration_argv);
  P(arConfiguration_values);
  P(arConfiguration_banner);
  P(arConfiguration_settings);
}

__TDESC(arConfiguration_ValueDesc__desc, 5, 4) = {__TDFLDS("ValueDesc", 16), {0, 4, 8, 12, -20}};
__TDESC(arConfiguration_Boolean__rec__desc, 5, 4) = {__TDFLDS("Boolean__rec", 20), {0, 4, 8, 12, -20}};
__TDESC(arConfiguration_Integer__rec__desc, 5, 4) = {__TDFLDS("Integer__rec", 24), {0, 4, 8, 12, -20}};
__TDESC(arConfiguration_String__rec__desc, 5, 5) = {__TDFLDS("String__rec", 20), {0, 4, 8, 12, 16, -24}};
__TDESC(arConfiguration_Procedure__rec__desc, 5, 4) = {__TDFLDS("Procedure__rec", 20), {0, 4, 8, 12, -20}};
__TDESC(arConfiguration_Assoc__rec__desc, 5, 5) = {__TDFLDS("Assoc__rec", 24), {0, 4, 8, 12, 16, -24}};

export void *arConfiguration__init (void)
{
  __DEFMOD;
  __IMPORT(arArgs__init);
  __IMPORT(Console__init);
  __IMPORT(Files__init);
  __IMPORT(Kernel__init);
  __IMPORT(arPattern__init);
  __IMPORT(arStringAssoc__init);
  __IMPORT(arStringList__init);
  __IMPORT(arSize__init);
  __IMPORT(arStrings__init);
  __REGMOD("arConfiguration", EnumPtrs);
  __REGCMD("Usage", arConfiguration_Usage);
  __INITYP(arConfiguration_ValueDesc, arConfiguration_ValueDesc, 0);
  __INITBP(arConfiguration_ValueDesc, arConfiguration_Value_Accept, 1);
  __INITBP(arConfiguration_ValueDesc, arConfiguration_Value_Format, 2);
  __INITBP(arConfiguration_ValueDesc, arConfiguration_Value_Init, 3);
  __INITYP(arConfiguration_Boolean__rec, arConfiguration_ValueDesc, 1);
  __INITBP(arConfiguration_Boolean__rec, arConfiguration_Boolean_Accept, 1);
  __INITBP(arConfiguration_Boolean__rec, arConfiguration_Boolean_Format, 2);
  __INITYP(arConfiguration_Integer__rec, arConfiguration_ValueDesc, 1);
  __INITBP(arConfiguration_Integer__rec, arConfiguration_Integer_Accept, 1);
  __INITBP(arConfiguration_Integer__rec, arConfiguration_Integer_Format, 2);
  __INITYP(arConfiguration_String__rec, arConfiguration_ValueDesc, 1);
  __INITBP(arConfiguration_String__rec, arConfiguration_String_Accept, 1);
  __INITBP(arConfiguration_String__rec, arConfiguration_String_Format, 2);
  __INITYP(arConfiguration_Procedure__rec, arConfiguration_ValueDesc, 1);
  __INITBP(arConfiguration_Procedure__rec, arConfiguration_Procedure_Accept, 1);
  __INITYP(arConfiguration_Assoc__rec, arConfiguration_ValueDesc, 1);
  __INITBP(arConfiguration_Assoc__rec, arConfiguration_Assoc_Accept, 1);
/* BEGIN */
  arConfiguration_argv = arConfiguration_CopyArgVec(arArgs_argv);
  arConfiguration_argc = arConfiguration_argv->len[0];
  arConfiguration_banner = NIL;
  arConfiguration_values = NIL;
  arConfiguration_NewProcedure((CHAR*)"help", 5, (CHAR*)"Display this message", 21, arConfiguration_Help);
  arConfiguration_NewProcedure((CHAR*)"read", 5, (CHAR*)"Read parameters from file", 26, arConfiguration_Read);
  arConfiguration_settings = arConfiguration_NewAssoc((CHAR*)"set", 4, (CHAR*)"Define a macro parameter", 25, 0);
  __ENDMOD;
}
