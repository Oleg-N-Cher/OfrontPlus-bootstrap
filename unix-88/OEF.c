/* Ofront+ 1.0 -m2 -88 */
#include "SYSTEM.oh"
#include "Kernel.oh"
#include "Files.oh"
#include "Platform.oh"
#include "CmdArgs.oh"
#include "Console.oh"
#include "arPattern.oh"
#include "arStrings.oh"
#include "arStringList.oh"
#include "arStringAssoc.oh"
#include "arConfiguration.oh"

typedef
  struct OEF_Message__rec *OEF_Message;

typedef
  struct OEF_Message__rec {
    SHORTINT line, column, code;
    arStrings_StringPtr text;
    OEF_Message next;
  } OEF_Message__rec;


static arConfiguration_Integer OEF_contextLines, OEF_tabSize;
static arConfiguration_Boolean OEF_showSeparators, OEF_alwaysWrap;
static arConfiguration_Integer OEF_width;
static arConfiguration_Boolean OEF_withLineNumbers;
static CHAR OEF_OBERON[1024];

export void **OEF_Message__rec__typ;

static void OEF_CondOutString (BOOLEAN condition, CHAR *string, INTEGER string__len);
static void OEF_EmitArrow (SHORTINT position, CHAR body, CHAR tip);
static void OEF_EmitLine (CHAR *buffer, INTEGER buffer__len, SHORTINT *position, INTEGER position__len);
static void OEF_InsertMessage (OEF_Message list, OEF_Message item);
static SHORTINT OEF_Max (SHORTINT x, SHORTINT y);
static SHORTINT OEF_Min (SHORTINT x, SHORTINT y);
static void OEF_Options (void);
static void OEF_ProcessFile (CHAR *fileName, INTEGER fileName__len, OEF_Message message);
static void OEF_ProcessInput (void);
static BOOLEAN OEF_ReadLineFromFile (CHAR *line, INTEGER line__len, Files_Rider *rd, void **rd__typ);
static BOOLEAN OEF_ReadLineFromStdin (CHAR *line, INTEGER line__len);
static SHORTINT OEF_StringToInt (CHAR *s, INTEGER s__len);


/*============================================================================*/

static SHORTINT OEF_Min (SHORTINT x, SHORTINT y)
{
  if (x < y) {
    return x;
  } else {
    return y;
  }
  __RETCHK((CHAR*)"OEF", 23845);
}

static SHORTINT OEF_Max (SHORTINT x, SHORTINT y)
{
  if (x > y) {
    return x;
  } else {
    return y;
  }
  __RETCHK((CHAR*)"OEF", 25125);
}

static SHORTINT OEF_StringToInt (CHAR *s, INTEGER s__len)
{
  SHORTINT value, i;
  CHAR ch;
  value = 0;
  i = 0;
  ch = s[__X(i, s__len, (CHAR*)"OEF", 27411)];
  while (ch >= '0' && ch <= '9') {
    value = (value * 10 + (SHORTINT)ch) - 48;
    i += 1;
    ch = s[__X(i, s__len, (CHAR*)"OEF", 28180)];
  }
  return value;
}

static void OEF_CondOutString (BOOLEAN condition, CHAR *string, INTEGER string__len)
{
  __DUP(string, string__len);
  if (condition) {
    Console_String((void*)string, string__len);
  }
}

static BOOLEAN OEF_ReadLineFromFile (CHAR *line, INTEGER line__len, Files_Rider *rd, void **rd__typ)
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
      line[__X(i, line__len, (CHAR*)"OEF", 34832)] = ch;
      i += 1;
    }
    Files_ReadChar(rd, rd__typ, &ch);
  }
  line[__X(i, line__len, (CHAR*)"OEF", 35854)] = 0x00;
  return 1;
}

static BOOLEAN OEF_ReadLineFromStdin (CHAR *line, INTEGER line__len)
{
  SHORTINT i;
  CHAR ch;
  i = 0;
  Console_Read(&ch);
  if (ch == 0x00) {
    return 0;
  }
  while (ch != 0x0a && ch != 0x00) {
    if (ch != 0x0d && (INTEGER)i < line__len - 1) {
      line[__X(i, line__len, (CHAR*)"OEF", 40208)] = ch;
      i += 1;
    }
    Console_Read(&ch);
  }
  line[__X(i, line__len, (CHAR*)"OEF", 41230)] = 0x00;
  return 1;
}

static void OEF_InsertMessage (OEF_Message list, OEF_Message item)
{
  while (list->next != NIL && (list->next->line < item->line || (list->next->line == item->line && list->next->column < item->column))) {
    list = list->next;
  }
  item->next = list->next;
  list->next = item;
}

static void OEF_EmitLine (CHAR *buffer, INTEGER buffer__len, SHORTINT *position, INTEGER position__len)
{
  SHORTINT i, pos;
  CHAR ch;
  i = 0;
  pos = 0;
  ch = buffer[__X(i, buffer__len, (CHAR*)"OEF", 46882)];
  while (ch != 0x00) {
    position[__X(i, position__len, (CHAR*)"OEF", 47380)] = pos;
    if (ch == 0x09) {
      Console_Char(' ');
      pos += 1;
      while (__MODF(pos, OEF_tabSize->value) != 0) {
        Console_Char(' ');
        pos += 1;
      }
    } else {
      Console_Char(ch);
      pos += 1;
    }
    i += 1;
    ch = buffer[__X(i, buffer__len, (CHAR*)"OEF", 49689)];
  }
  Console_Ln();
}

static void OEF_EmitArrow (SHORTINT position, CHAR body, CHAR tip)
{
  SHORTINT i;
  CHAR ch;
  position -= 1;
  while (position > 0) {
    position -= 1;
    Console_Char(body);
  }
  Console_Char(tip);
}

static void OEF_ProcessFile (CHAR *fileName, INTEGER fileName__len, OEF_Message message)
{
  SHORTINT line, trailingContext;
  CHAR buffer[128];
  SHORTINT position[128];
  Files_Rider rd = {0};
  Files_File file = NIL;
  BOOLEAN needSeparator;
  SHORTINT columnPosition;
  arStrings_StringPtr _ptr__10 = NIL;
  arStrings_StringPtr _ptr__9 = NIL;
  __DUP(fileName, fileName__len);
  trailingContext = 0;
  needSeparator = 0;
  file = Files_Old((void*)fileName, fileName__len);
  if (file == NIL) {
    Console_String((CHAR*)"Cannot open file: ", 19);
    Console_String((void*)fileName, fileName__len);
    Console_Ln();
    return;
  }
  Files_Set(&rd, Files_Rider__typ, file, 0);
  line = 0;
  while (OEF_ReadLineFromFile((void*)buffer, 128, &rd, Files_Rider__typ)) {
    line += 1;
    if (line <= trailingContext || (message != NIL && __ABS(line - message->line) <= OEF_contextLines->value)) {
      if (line > trailingContext && needSeparator) {
        needSeparator = 0;
        OEF_CondOutString(OEF_withLineNumbers->value, (CHAR*)"-----", 6);
        Console_Ln();
      }
      if (OEF_withLineNumbers->value) {
        Console_Int(line, 4);
        Console_String((CHAR*)"| ", 3);
      }
      OEF_EmitLine((void*)buffer, 128, (void*)position, 128);
      while (message != NIL && message->line == line) {
        trailingContext = line + OEF_contextLines->value;
        needSeparator = OEF_showSeparators->value;
        OEF_CondOutString(OEF_withLineNumbers->value, (CHAR*)"    +-", 7);
        columnPosition = position[__XF(OEF_Max(0, OEF_Min(127, message->column - 1)), 128, (CHAR*)"OEF", 66126)];
        OEF_EmitArrow(columnPosition, '-', '^');
        if (!OEF_alwaysWrap->value && ((INTEGER)columnPosition + (_ptr__10 = message->text, 
          arStrings_Length(_ptr__10->data, _ptr__10->len[0]))) + 7 < (INTEGER)OEF_width->value) {
          Console_String((CHAR*)" ", 2);
        } else {
          Console_Ln();
          OEF_CondOutString(OEF_withLineNumbers->value, (CHAR*)"    | ", 7);
        }
        _ptr__9 = message->text;
        Console_String((void*)_ptr__9->data, _ptr__9->len[0]);
        if (!OEF_withLineNumbers->value) {
          Console_String((CHAR*)" @", 3);
          Console_Int(message->line, 0);
          Console_String((CHAR*)":", 2);
          Console_Int(message->column, 0);
        }
        Console_Ln();
        message = message->next;
      }
    }
  }
  Files_Close(file);
}

static void OEF_ProcessInput (void)
{
  CHAR line[128];
  arStrings_StringPtr fileName = NIL;
  arStringList_Array match = NIL;
  OEF_Message message = NIL;
  OEF_Message list = NIL;
  arStrings_StringPtr _ptr__14 = NIL;
  arStrings_StringPtr _ptr__13 = NIL;
  arStrings_StringPtr _ptr__12 = NIL;
  __NEW(list, OEF_Message__rec);
  list->next = NIL;
  fileName = NIL;
  while (OEF_ReadLineFromStdin((void*)line, 128)) {
    if (arPattern_Match((CHAR*)"* translating *", 16, (void*)line, 128, &match)) {
      if (fileName != NIL && list->next != NIL) {
        OEF_ProcessFile(fileName->data, fileName->len[0], list->next);
        __NEW(list, OEF_Message__rec);
        list->next = NIL;
      }
      fileName = (match->data)[0];
      Console_String((void*)line, 128);
      Console_Ln();
    } else if (arPattern_Match((CHAR*)" *:* err * *", 13, (void*)line, 128, &match)) {
      __NEW(message, OEF_Message__rec);
      message->line = (_ptr__14 = (match->data)[0], 
        OEF_StringToInt((void*)_ptr__14->data, _ptr__14->len[0]));
      message->column = (_ptr__13 = (match->data)[__X(1, match->len[0], (CHAR*)"OEF", 78379)], 
        OEF_StringToInt((void*)_ptr__13->data, _ptr__13->len[0]));
      message->code = (_ptr__12 = (match->data)[__X(2, match->len[0], (CHAR*)"OEF", 78633)], 
        OEF_StringToInt((void*)_ptr__12->data, _ptr__12->len[0]));
      message->text = (match->data)[__X(3, match->len[0], (CHAR*)"OEF", 78875)];
      (message->text->data)[0] = __CAP((message->text->data)[0]);
      OEF_InsertMessage(list, message);
    } else {
      Console_String((void*)line, 128);
      Console_Ln();
    }
  }
  if (fileName != NIL) {
    OEF_ProcessFile(fileName->data, fileName->len[0], list->next);
  }
}

static void OEF_Options (void)
{
  INTEGER pos;
  OEF_withLineNumbers = arConfiguration_NewBoolean((CHAR*)"numbers", 8, (CHAR*)"Show line numbers before source lines", 38, 1);
  OEF_alwaysWrap = arConfiguration_NewBoolean((CHAR*)"wrap", 5, (CHAR*)"Always show error message on separate line", 43, 0);
  OEF_showSeparators = arConfiguration_NewBoolean((CHAR*)"separate", 9, (CHAR*)"Separate discontiguous source lines", 36, 1);
  OEF_contextLines = arConfiguration_NewInteger((CHAR*)"context <N>", 12, (CHAR*)"Show <N> context lines before and after message", 48, 1, 0, 10);
  OEF_tabSize = arConfiguration_NewInteger((CHAR*)"tabs <N>", 9, (CHAR*)"Set <N> spaces per tab character", 33, 2, 1, -32767);
  OEF_width = arConfiguration_NewInteger((CHAR*)"width <N>", 10, (CHAR*)"Wrap messages extending past column <N>", 40, 80, 40, -32767);
  if (arConfiguration_ReadOptions((CHAR*)"oef.ini", 8)) {
  }
  pos = 1;
  arConfiguration_ScanOptions(&pos);
  arConfiguration_CheckFinished(pos);
}

static void EnumPtrs(void (*P)(void*))
{
  P(OEF_contextLines);
  P(OEF_tabSize);
  P(OEF_showSeparators);
  P(OEF_alwaysWrap);
  P(OEF_width);
  P(OEF_withLineNumbers);
}

__TDESC(OEF_Message__rec__desc, 2, 2) = {__TDFLDS("Message__rec", 24), {8, 16, -24}};

int main (int argc, char **argv)
{
  __INIT(argc, argv);
  __IMPORT(arConfiguration__init);
  __IMPORT(CmdArgs__init);
  __IMPORT(Console__init);
  __IMPORT(Files__init);
  __IMPORT(Kernel__init);
  __IMPORT(arPattern__init);
  __IMPORT(arStrings__init);
  __REGMAIN("OEF", EnumPtrs);
  __INITYP(OEF_Message__rec, OEF_Message__rec, 0);
/* BEGIN */
  CmdArgs_GetEnv((CHAR*)"OBERON", 7, (void*)OEF_OBERON, 1024);
  if (OEF_OBERON[0] == 0x00) {
    __MOVE((CHAR*)".", OEF_OBERON, 2);
  }
  Files_SetSearchPath((void*)OEF_OBERON, 1024);
  arConfiguration_SetBanner((CHAR*)"oef - Ofront+ Error Filter\\nThis tool shows source code context for Ofront+ compiler messages\\nUsage:\\n  ofront+ ... Module.Mod | oef [options]\\n", 146);
  OEF_Options();
  OEF_ProcessInput();
  __FINI;
}
