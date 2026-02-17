/* Ofront+ 1.0 -s2 -88 */
#include "SYSTEM.oh"
#include "CmdArgs.oh"
#include "arOut.oh"
#include "arChar.oh"
#include "arStringList.oh"
#include "arStrings.oh"
#include "arStringAssoc.oh"
#include "arText.oh"


#ifndef CHAR8_ARRAY_DEF
#define CHAR8_ARRAY_DEF
typedef struct CHAR8_ARRAY {
  INTEGER len[1];
  CHAR data[1];
} CHAR8_ARRAY;
#endif 



export arStrings_StringPtr arPattern_ExpandEnvironmentVariables (CHAR *string, INTEGER string__len);
export BOOLEAN arPattern_Match (CHAR *pattern, INTEGER pattern__len, CHAR *input, INTEGER input__len, arStringList_Array *result);
export arStringList_Array arPattern_ParseArgs (CHAR *string, INTEGER string__len);
export arStringList_Array arPattern_Split (CHAR *string, INTEGER string__len, CHAR delimiter);
export arStrings_StringPtr arPattern_Substitute (CHAR *string, INTEGER string__len, arStringAssoc_Assoc environment);


/*============================================================================*/

static struct Match__2 {
  CHAR *input;
  INTEGER input__len;
  INTEGER *inPos, *inLength;
  CHAR *ch;
  struct Match__2 *lnk;
} *Match__2_s;

static void __5 (void);

static void __5 (void)
{
  if ((*Match__2_s->inPos) < (*Match__2_s->inLength)) {
    (*Match__2_s->ch) = Match__2_s->input[__X((*Match__2_s->inPos), Match__2_s->input__len, (CHAR*)"arPattern", 14101)];
    (*Match__2_s->inPos) += 1;
  } else {
    (*Match__2_s->ch) = 0x00;
  }
}

BOOLEAN arPattern_Match (CHAR *pattern, INTEGER pattern__len, CHAR *input, INTEGER input__len, arStringList_Array *result)
{
  INTEGER i, patPos, patLength;
  CHAR patChar;
  INTEGER inPos, inLength;
  CHAR ch, terminator;
  INTEGER outPos;
  struct CHAR8_ARRAY *buffer = NIL;
  INTEGER fields, match, _for__4, _for__3;
  struct Match__2 _s;
  BOOLEAN __retval;
  _s.input = (void*)input; _s.input__len = input__len;
  _s.inPos = &inPos;
  _s.inLength = &inLength;
  _s.ch = &ch;
  _s.lnk = Match__2_s;
  Match__2_s = &_s;
  patPos = 0;
  patLength = arStrings_Length((void*)pattern, pattern__len);
  inPos = 0;
  inLength = arStrings_Length((void*)input, input__len);
  match = 0;
  buffer = __NEWARR(NIL, 1, 1, 1, 1, (SYSTEM_ARRLEN)(inLength + 1));
  fields = 0;
  _for__4 = patLength - 1;
  i = 0;
  while (i <= _for__4) {
    if (pattern[__X(i, pattern__len, (CHAR*)"arPattern", 19455)] == '*') {
      fields += 1;
    }
    i += 1;
  }
  if (fields == 0) {
    *result = NIL;
  } else {
    *result = __NEWARR(POINTER__typ, 8, 8, 1, 1, (SYSTEM_ARRLEN)fields);
    _for__3 = fields - 1;
    i = 0;
    while (i <= _for__3) {
      ((*result)->data)[__X(i, (*result)->len[0], (CHAR*)"arPattern", 21011)] = NIL;
      i += 1;
    }
  }
  __5();
  while (patPos < patLength) {
    patChar = pattern[__X(patPos, pattern__len, (CHAR*)"arPattern", 22556)];
    patPos += 1;
    switch (patChar) {
      case ' ': 
        if (ch != ' ') {
          __retval = 0;
          Match__2_s = _s.lnk;
          ;
          return __retval;
        }
        while (ch == ' ' || ch == 0x09) {
          __5();
        }
        break;
      case '*': 
        terminator = pattern[__X(patPos, pattern__len, (CHAR*)"arPattern", 25120)];
        outPos = 0;
        while (ch != terminator && ch != 0x00) {
          (buffer->data)[__X(outPos, buffer->len[0], (CHAR*)"arPattern", 25880)] = ch;
          outPos += 1;
          __5();
        }
        (buffer->data)[__X(outPos, buffer->len[0], (CHAR*)"arPattern", 26903)] = 0x00;
        ((*result)->data)[__X(match, (*result)->len[0], (CHAR*)"arPattern", 27428)] = arStringList_Copy(buffer->data, buffer->len[0]);
        match += 1;
        break;
      default: 
        if (ch != patChar) {
          __retval = 0;
          Match__2_s = _s.lnk;
          ;
          return __retval;
        }
        __5();
        break;
    }
  }
  __retval = 1;
  Match__2_s = _s.lnk;
  ;
  return __retval;
}

/*----------------------------------------------------------------------------*/
static struct Split__11 {
  CHAR *string;
  INTEGER string__len;
  arStringList_Array *result;
  SHORTINT *part;
  struct Split__11 *lnk;
} *Split__11_s;

static void __14 (INTEGER start, INTEGER count);

static void __14 (INTEGER start, INTEGER count)
{
  arStrings_StringPtr _ptr__16 = NIL;
  (((*Split__11_s->result))->data)[__X((*Split__11_s->part), ((*Split__11_s->result))->len[0], (CHAR*)"arPattern", 32540)] = __NEWARR(NIL, 1, 1, 1, 1, (SYSTEM_ARRLEN)(count + 1));
  _ptr__16 = (((*Split__11_s->result))->data)[__X((*Split__11_s->part), ((*Split__11_s->result))->len[0], (CHAR*)"arPattern", 32816)];
  arStrings_Extract((void*)Split__11_s->string, Split__11_s->string__len, start, count, _ptr__16->data, _ptr__16->len[0]);
  (*Split__11_s->part) += 1;
}

arStringList_Array arPattern_Split (CHAR *string, INTEGER string__len, CHAR delimiter)
{
  arStringList_Array result = NIL;
  INTEGER begin, i, length;
  SHORTINT part, nParts;
  INTEGER _for__13, _for__12;
  struct Split__11 _s;
  arStringList_Array __retval;
  _s.string = (void*)string; _s.string__len = string__len;
  _s.result = &result;
  _s.part = &part;
  _s.lnk = Split__11_s;
  Split__11_s = &_s;
  length = arStrings_Length((void*)string, string__len);
  nParts = 1;
  _for__13 = length - 1;
  i = 0;
  while (i <= _for__13) {
    if (string[__X(i, string__len, (CHAR*)"arPattern", 35119)] == delimiter) {
      nParts += 1;
    }
    i += 1;
  }
  result = __NEWARR(POINTER__typ, 8, 8, 1, 1, (SYSTEM_ARRLEN)nParts);
  part = 0;
  begin = 0;
  _for__12 = length - 1;
  i = 0;
  while (i <= _for__12) {
    if (string[__X(i, string__len, (CHAR*)"arPattern", 37893)] == delimiter) {
      __14(begin, i - begin);
      begin = i + 1;
    }
    i += 1;
  }
  if (begin <= length) {
    __14(begin, length - begin);
  }
  __ASSERT(part == nParts, 0, (CHAR*)"arPattern", 39190);
  __retval = result;
  Split__11_s = _s.lnk;
  ;
  return __retval;
}

/*----------------------------------------------------------------------------*/
static struct ParseArgs__7 {
  arText_Buffer *buffer;
  arStringList_List *list;
  struct ParseArgs__7 *lnk;
} *ParseArgs__7_s;

static void __9 (void);

static void __9 (void)
{
  arStringList_Add(&(*ParseArgs__7_s->list), (void*)__arText_Buffer_GetString(&(*ParseArgs__7_s->buffer), arText_Buffer__typ));
  __arText_Buffer_Init(&(*ParseArgs__7_s->buffer), arText_Buffer__typ, ((*ParseArgs__7_s->buffer)).capacity);
}

arStringList_Array arPattern_ParseArgs (CHAR *string, INTEGER string__len)
{
  arText_Buffer buffer = {0};
  arStringList_List list = NIL;
  INTEGER i;
  CHAR ch, lastCh;
  BOOLEAN inQuote;
  INTEGER _for__8;
  struct ParseArgs__7 _s;
  arStringList_Array __retval;
  _s.buffer = &buffer;
  _s.list = &list;
  _s.lnk = ParseArgs__7_s;
  ParseArgs__7_s = &_s;
  __arText_Buffer_Init(&buffer, arText_Buffer__typ, 32);
  list = NIL;
  lastCh = 0x00;
  inQuote = 0;
  _for__8 = arStrings_Length((void*)string, string__len) - 1;
  i = 0;
  while (i <= _for__8) {
    ch = string[__X(i, string__len, (CHAR*)"arPattern", 46865)];
    if (ch == ' ' && !inQuote) {
      if (lastCh != ' ') {
        __9();
      }
    } else if (ch == '\"') {
      inQuote = !inQuote;
    } else {
      __arText_Stream_Char((void*)&buffer, arText_Buffer__typ, ch);
    }
    lastCh = ch;
    i += 1;
  }
  __9();
  arStringList_Reverse(&list);
  __retval = arStringList_ToArray(list);
  ParseArgs__7_s = _s.lnk;
  ;
  return __retval;
}

/*----------------------------------------------------------------------------*/
arStrings_StringPtr arPattern_ExpandEnvironmentVariables (CHAR *string, INTEGER string__len)
{
  INTEGER i;
  CHAR ch;
  arText_Buffer outBuffer = {0}, keyBuffer = {0};
  arStrings_StringPtr key = NIL;
  CHAR arg[256];
  i = 0;
  __arText_Buffer_Init(&outBuffer, arText_Buffer__typ, 32);
  __arText_Buffer_Init(&keyBuffer, arText_Buffer__typ, 32);
  for (;;) {
    if (i >= string__len) {
      break;
    }
    ch = string[__X(i, string__len, (CHAR*)"arPattern", 54289)];
    i += 1;
    if (ch == '$') {
      __arText_Buffer_Clear(&keyBuffer, arText_Buffer__typ);
      ch = string[__X(i, string__len, (CHAR*)"arPattern", 55058)];
      i += 1;
      while (arChar_IsAlphaNumeric(ch)) {
        __arText_Stream_Char((void*)&keyBuffer, arText_Buffer__typ, ch);
        ch = string[__X(i, string__len, (CHAR*)"arPattern", 55827)];
        i += 1;
      }
      key = (arStrings_StringPtr)__arText_Buffer_GetString(&keyBuffer, arText_Buffer__typ);
      CmdArgs_GetEnv((void*)key->data, key->len[0], (void*)arg, 256);
      __arText_Stream_String((void*)&outBuffer, arText_Buffer__typ, (void*)arg, 256);
    }
    if (ch == 0x00) {
      break;
    }
    __arText_Stream_Char((void*)&outBuffer, arText_Buffer__typ, ch);
  }
  __arText_Buffer_Terminate(&outBuffer, arText_Buffer__typ);
  return (void*)(__arText_Buffer_GetString(&outBuffer, arText_Buffer__typ));
}

/*----------------------------------------------------------------------------*/
arStrings_StringPtr arPattern_Substitute (CHAR *string, INTEGER string__len, arStringAssoc_Assoc environment)
{
  INTEGER i;
  CHAR ch, terminator;
  BOOLEAN inFormat;
  arText_Buffer outBuffer = {0}, keyBuffer = {0};
  arStrings_StringPtr key = NIL;
  arStrings_StringPtr value = NIL;
  __DUP(string, string__len);
  i = 0;
  inFormat = 0;
  __arText_Buffer_Init(&outBuffer, arText_Buffer__typ, 32);
  __arText_Buffer_Init(&keyBuffer, arText_Buffer__typ, 32);
  for (;;) {
    if (i >= string__len) {
      break;
    }
    ch = string[__X(i, string__len, (CHAR*)"arPattern", 64017)];
    i += 1;
    if (ch == 0x00) {
      break;
    }
    if (inFormat) {
      if (ch == terminator) {
        inFormat = 0;
        key = (arStrings_StringPtr)__arText_Buffer_GetString(&keyBuffer, arText_Buffer__typ);
        value = arStringAssoc_Get(environment, key->data, key->len[0]);
        if (value != NIL) {
          if (terminator == ']') {
            value = arPattern_ExpandEnvironmentVariables((void*)value->data, value->len[0]);
          }
          __arText_Stream_String((void*)&outBuffer, arText_Buffer__typ, (void*)value->data, value->len[0]);
        } else {
          arOut_String((CHAR*)"Undefined key ", 15);
          arOut_String((void*)key->data, key->len[0]);
          arOut_Ln();
        }
      } else {
        __arText_Stream_Char((void*)&keyBuffer, arText_Buffer__typ, ch);
      }
    } else {
      switch (ch) {
        case '{': 
          inFormat = 1;
          terminator = '}';
          __arText_Buffer_Clear(&keyBuffer, arText_Buffer__typ);
          break;
        case '[': 
          inFormat = 1;
          terminator = ']';
          __arText_Buffer_Clear(&keyBuffer, arText_Buffer__typ);
          break;
        case '\\': 
          if (i < string__len) {
            ch = string[__X(i, string__len, (CHAR*)"arPattern", 72212)];
            i += 1;
            __arText_Stream_Char((void*)&outBuffer, arText_Buffer__typ, ch);
          }
          break;
        default: 
          __arText_Stream_Char((void*)&outBuffer, arText_Buffer__typ, ch);
          break;
      }
    }
  }
  return (void*)(__arText_Buffer_GetString(&outBuffer, arText_Buffer__typ));
}

/*----------------------------------------------------------------------------*/

export void *arPattern__init (void)
{
  __DEFMOD;
  __IMPORT(arChar__init);
  __IMPORT(CmdArgs__init);
  __IMPORT(arOut__init);
  __IMPORT(arStrings__init);
  __IMPORT(arStringAssoc__init);
  __IMPORT(arStringList__init);
  __IMPORT(arText__init);
  __REGMOD("arPattern", 0);
/* BEGIN */
  __ENDMOD;
}
