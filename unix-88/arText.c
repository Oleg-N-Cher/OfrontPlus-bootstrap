/* Ofront+ 1.0 -s2 -88 */
#include "SYSTEM.oh"
#include "Platform.oh"
#include "arCFormat.oh"
#include "arC.oh"

typedef
  struct arText_Stream {
    char _prvt0[1];
  } arText_Stream;

export void arText_Stream_Char (arText_Stream *self, void **self__typ, CHAR value);
export void arText_Stream_Flush (arText_Stream *self, void **self__typ);
export void arText_Stream_String (arText_Stream *self, void **self__typ, CHAR *value, INTEGER value__len);
#define __arText_Stream_Char(self, self__typ, value) __SEND(self__typ, arText_Stream_Char, 0, void(*)(arText_Stream*, void **, CHAR), (self, self__typ, value))
#define __arText_Stream_Flush(self, self__typ) __SEND(self__typ, arText_Stream_Flush, 1, void(*)(arText_Stream*, void **), (self, self__typ))
#define __arText_Stream_String(self, self__typ, value, value__len) __SEND(self__typ, arText_Stream_String, 2, void(*)(arText_Stream*, void **, CHAR*, INTEGER ), (self, self__typ, value, value__len))

typedef
  struct arText_Writer { /* arText_Stream */
    CHAR intFormat[8];
    CHAR hexFormat[8];
    CHAR realFormat[8];
    BOOLEAN quoteLiterals, setAsList;
  } arText_Writer;

export void arText_Writer_Boolean (arText_Writer *self, void **self__typ, BOOLEAN value);
export void arText_Writer_Hex (arText_Writer *self, void **self__typ, INTEGER value);
export void arText_Writer_InitWriter (arText_Writer *self, void **self__typ);
export void arText_Writer_Integer (arText_Writer *self, void **self__typ, INTEGER value);
export void arText_Writer_Ln (arText_Writer *self, void **self__typ);
export void arText_Writer_Real (arText_Writer *self, void **self__typ, REAL value);
export void arText_Writer_Set (arText_Writer *self, void **self__typ, SET value);
export void arText_Writer_StringLiteral (arText_Writer *self, void **self__typ, CHAR *value, INTEGER value__len);
#define __arText_Writer_Boolean(self, self__typ, value) __SEND(self__typ, arText_Writer_Boolean, 3, void(*)(arText_Writer*, void **, BOOLEAN), (self, self__typ, value))
#define __arText_Writer_Hex(self, self__typ, value) __SEND(self__typ, arText_Writer_Hex, 4, void(*)(arText_Writer*, void **, INTEGER), (self, self__typ, value))
#define __arText_Writer_InitWriter(self, self__typ) __SEND(self__typ, arText_Writer_InitWriter, 5, void(*)(arText_Writer*, void **), (self, self__typ))
#define __arText_Writer_Integer(self, self__typ, value) __SEND(self__typ, arText_Writer_Integer, 6, void(*)(arText_Writer*, void **, INTEGER), (self, self__typ, value))
#define __arText_Writer_Ln(self, self__typ) __SEND(self__typ, arText_Writer_Ln, 7, void(*)(arText_Writer*, void **), (self, self__typ))
#define __arText_Writer_Real(self, self__typ, value) __SEND(self__typ, arText_Writer_Real, 8, void(*)(arText_Writer*, void **, REAL), (self, self__typ, value))
#define __arText_Writer_Set(self, self__typ, value) __SEND(self__typ, arText_Writer_Set, 9, void(*)(arText_Writer*, void **, SET), (self, self__typ, value))
#define __arText_Writer_StringLiteral(self, self__typ, value, value__len) __SEND(self__typ, arText_Writer_StringLiteral, 10, void(*)(arText_Writer*, void **, CHAR*, INTEGER ), (self, self__typ, value, value__len))

typedef
  struct CHAR8_ARRAY *arText_String;

typedef
  struct arText_Buffer { /* arText_Writer */
    CHAR intFormat[8];
    CHAR hexFormat[8];
    CHAR realFormat[8];
    BOOLEAN quoteLiterals, setAsList;
    INTEGER length, capacity;
    arText_String value;
  } arText_Buffer;

export void arText_Buffer_Char (arText_Buffer *self, void **self__typ, CHAR value);
export void arText_Buffer_Clear (arText_Buffer *self, void **self__typ);
static void arText_Buffer_EnsureCapacity (arText_Buffer *self, void **self__typ, INTEGER capacity);
export arText_String arText_Buffer_GetString (arText_Buffer *self, void **self__typ);
export void arText_Buffer_Init (arText_Buffer *self, void **self__typ, INTEGER capacity);
export void arText_Buffer_String (arText_Buffer *self, void **self__typ, CHAR *value, INTEGER value__len);
export void arText_Buffer_Terminate (arText_Buffer *self, void **self__typ);
#define __arText_Buffer_Clear(self, self__typ) __SEND(self__typ, arText_Buffer_Clear, 11, void(*)(arText_Buffer*, void **), (self, self__typ))
#define __arText_Buffer_EnsureCapacity(self, self__typ, capacity) __SEND(self__typ, arText_Buffer_EnsureCapacity, 12, void(*)(arText_Buffer*, void **, INTEGER), (self, self__typ, capacity))
#define __arText_Buffer_GetString(self, self__typ) __SEND(self__typ, arText_Buffer_GetString, 13, arText_String(*)(arText_Buffer*, void **), (self, self__typ))
#define __arText_Buffer_Init(self, self__typ, capacity) __SEND(self__typ, arText_Buffer_Init, 14, void(*)(arText_Buffer*, void **, INTEGER), (self, self__typ, capacity))
#define __arText_Buffer_Terminate(self, self__typ) __SEND(self__typ, arText_Buffer_Terminate, 15, void(*)(arText_Buffer*, void **), (self, self__typ))

typedef
  arText_Stream *arText_StreamPtr;

typedef
  struct arText_StreamWriter { /* arText_Writer */
    CHAR intFormat[8];
    CHAR hexFormat[8];
    CHAR realFormat[8];
    BOOLEAN quoteLiterals, setAsList;
    arText_StreamPtr stream;
  } arText_StreamWriter;

export void arText_StreamWriter_Char (arText_StreamWriter *self, void **self__typ, CHAR value);
export void arText_StreamWriter_Flush (arText_StreamWriter *self, void **self__typ);
export void arText_StreamWriter_Init (arText_StreamWriter *self, void **self__typ, arText_StreamPtr stream);
export void arText_StreamWriter_String (arText_StreamWriter *self, void **self__typ, CHAR *value, INTEGER value__len);
#define __arText_StreamWriter_Init(self, self__typ, stream) __SEND(self__typ, arText_StreamWriter_Init, 11, void(*)(arText_StreamWriter*, void **, arText_StreamPtr), (self, self__typ, stream))


#ifndef CHAR8_ARRAY_DEF
#define CHAR8_ARRAY_DEF
typedef struct CHAR8_ARRAY {
  INTEGER len[1];
  CHAR data[1];
} CHAR8_ARRAY;
#endif 


export void **arText_Stream__typ;
export void **arText_Writer__typ;
export void **arText_StreamWriter__typ;
export void **arText_Buffer__typ;



/*============================================================================*/

void arText_Stream_Char (arText_Stream *self, void **self__typ, CHAR value)
{
}

/*----------------------------------------------------------------------------*/
void arText_Stream_String (arText_Stream *self, void **self__typ, CHAR *value, INTEGER value__len)
{
}

/*----------------------------------------------------------------------------*/
void arText_Stream_Flush (arText_Stream *self, void **self__typ)
{
}

/*----------------------------------------------------------------------------*/
void arText_Writer_InitWriter (arText_Writer *self, void **self__typ)
{
  __MOVE((CHAR*)"%d", (*self).intFormat, 3);
  __MOVE((CHAR*)"%x", (*self).hexFormat, 3);
  __MOVE((CHAR*)"%g", (*self).realFormat, 3);
  (*self).quoteLiterals = 0;
  (*self).setAsList = 0;
}

/*----------------------------------------------------------------------------*/
void arText_Writer_StringLiteral (arText_Writer *self, void **self__typ, CHAR *value, INTEGER value__len)
{
  __DUP(value, value__len);
  if ((*self).quoteLiterals) {
    __arText_Stream_Char((void*)self, self__typ, '\"');
    __arText_Stream_String((void*)self, self__typ, (void*)value, value__len);
    __arText_Stream_Char((void*)self, self__typ, '\"');
  } else {
    __arText_Stream_String((void*)self, self__typ, (void*)value, value__len);
  }
}

/*----------------------------------------------------------------------------*/
void arText_Writer_Integer (arText_Writer *self, void **self__typ, INTEGER value)
{
  CHAR buffer[32];
  arCFormat_IntToString((void*)buffer, 32, (*self).intFormat, 8, value);
  __arText_Stream_String((void*)self, self__typ, (void*)buffer, 32);
}

/*----------------------------------------------------------------------------*/
void arText_Writer_Hex (arText_Writer *self, void **self__typ, INTEGER value)
{
  CHAR buffer[32];
  arCFormat_IntToString((void*)buffer, 32, (*self).hexFormat, 8, value);
  __arText_Stream_String((void*)self, self__typ, (void*)buffer, 32);
}

/*----------------------------------------------------------------------------*/
void arText_Writer_Real (arText_Writer *self, void **self__typ, REAL value)
{
  CHAR buffer[32];
  arCFormat_RealToString((void*)buffer, 32, (*self).realFormat, 8, value);
  __arText_Stream_String((void*)self, self__typ, (void*)buffer, 32);
}

/*----------------------------------------------------------------------------*/
void arText_Writer_Boolean (arText_Writer *self, void **self__typ, BOOLEAN value)
{
  if (value) {
    __arText_Stream_String((void*)self, self__typ, (CHAR*)"true", 5);
  } else {
    __arText_Stream_String((void*)self, self__typ, (CHAR*)"false", 6);
  }
}

/*----------------------------------------------------------------------------*/
void arText_Writer_Set (arText_Writer *self, void **self__typ, SET value)
{
  SHORTINT i, count;
  count = 0;
  if ((*self).setAsList) {
    __arText_Stream_Char((void*)self, self__typ, '[');
  } else {
    __arText_Stream_Char((void*)self, self__typ, '{');
  }
  i = 0;
  while ((INTEGER)i <= 31) {
    if (__IN(i, value)) {
      if (count > 0) {
        __arText_Stream_Char((void*)self, self__typ, ',');
      }
      __arText_Writer_Integer(self, self__typ, i);
      count += 1;
    }
    i += 1;
  }
  if ((*self).setAsList) {
    __arText_Stream_Char((void*)self, self__typ, ']');
  } else {
    __arText_Stream_Char((void*)self, self__typ, '}');
  }
}

/*----------------------------------------------------------------------------*/
void arText_Writer_Ln (arText_Writer *self, void **self__typ)
{
  __arText_Stream_String((void*)self, self__typ, (CHAR*)"\x0a", 2);
}

/*----------------------------------------------------------------------------*/
void arText_Buffer_Init (arText_Buffer *self, void **self__typ, INTEGER capacity)
{
  __arText_Writer_InitWriter((void*)self, self__typ);
  (*self).length = 0;
  if (capacity < 8) {
    capacity = 8;
  }
  (*self).capacity = capacity;
  (*self).value = __NEWARR(NIL, 1, 1, 1, 1, (SYSTEM_ARRLEN)capacity);
}

/*----------------------------------------------------------------------------*/
static void arText_Buffer_EnsureCapacity (arText_Buffer *self, void **self__typ, INTEGER capacity)
{
  INTEGER newCapacity;
  arText_String newValue = NIL;
  if ((*self).length < capacity) {
    newCapacity = (*self).capacity;
    while (newCapacity < capacity) {
      newCapacity = __ASHL(newCapacity, 1, INTEGER);
    }
    (*self).capacity = newCapacity;
    newValue = __NEWARR(NIL, 1, 1, 1, 1, (SYSTEM_ARRLEN)newCapacity);
    __MOVE((SYSTEM_ADRINT)&((*self).value->data)[0], (SYSTEM_ADRINT)&(newValue->data)[0], (*self).length);
    (*self).value = newValue;
  }
}

void arText_Buffer_Char (arText_Buffer *self, void **self__typ, CHAR value)
{
  __arText_Buffer_EnsureCapacity(self, self__typ, (*self).length + 1);
  ((*self).value->data)[__X((*self).length, (*self).value->len[0], (CHAR*)"arText", 45345)] = value;
  (*self).length += 1;
}

/*----------------------------------------------------------------------------*/
void arText_Buffer_String (arText_Buffer *self, void **self__typ, CHAR *value, INTEGER value__len)
{
  INTEGER i, length, _for__18;
  length = 0;
  while (length < value__len && value[__X(length, value__len, (CHAR*)"arText", 47665)] != 0x00) {
    length += 1;
  }
  __arText_Buffer_EnsureCapacity(self, self__typ, (*self).length + length);
  _for__18 = length - 1;
  i = 0;
  while (i <= _for__18) {
    ((*self).value->data)[__X((*self).length + i, (*self).value->len[0], (CHAR*)"arText", 48935)] = value[__X(i, value__len, (CHAR*)"arText", 48935)];
    i += 1;
  }
  (*self).length += length;
}

/*----------------------------------------------------------------------------*/
void arText_Buffer_Terminate (arText_Buffer *self, void **self__typ)
{
  __arText_Buffer_EnsureCapacity(self, self__typ, (*self).length + 1);
  ((*self).value->data)[__X((*self).length, (*self).value->len[0], (CHAR*)"arText", 51230)] = 0x00;
}

/*----------------------------------------------------------------------------*/
void arText_Buffer_Clear (arText_Buffer *self, void **self__typ)
{
  (*self).length = 0;
}

/*----------------------------------------------------------------------------*/
arText_String arText_Buffer_GetString (arText_Buffer *self, void **self__typ)
{
  __arText_Buffer_Terminate(self, self__typ);
  return (*self).value;
}

/*----------------------------------------------------------------------------*/
void arText_StreamWriter_Init (arText_StreamWriter *self, void **self__typ, arText_StreamPtr stream)
{
  __arText_Writer_InitWriter((void*)self, self__typ);
  (*self).stream = stream;
}

/*----------------------------------------------------------------------------*/
void arText_StreamWriter_Char (arText_StreamWriter *self, void **self__typ, CHAR value)
{
  __arText_Stream_Char((*self).stream, __TYPEOF((*self).stream), value);
}

/*----------------------------------------------------------------------------*/
void arText_StreamWriter_String (arText_StreamWriter *self, void **self__typ, CHAR *value, INTEGER value__len)
{
  __arText_Stream_String((*self).stream, __TYPEOF((*self).stream), (void*)value, value__len);
}

/*----------------------------------------------------------------------------*/
void arText_StreamWriter_Flush (arText_StreamWriter *self, void **self__typ)
{
  __arText_Stream_Flush((*self).stream, __TYPEOF((*self).stream));
}

/*----------------------------------------------------------------------------*/
__TDESC(arText_Stream__desc, 4, 0) = {__TDFLDS("Stream", 1), {-8}};
__TDESC(arText_Writer__desc, 12, 0) = {__TDFLDS("Writer", 26), {-8}};
__TDESC(arText_StreamWriter__desc, 13, 1) = {__TDFLDS("StreamWriter", 40), {32, -16}};
__TDESC(arText_Buffer__desc, 17, 1) = {__TDFLDS("Buffer", 48), {40, -16}};

export void *arText__init (void)
{
  __DEFMOD;
  __IMPORT(Platform__init);
  __REGMOD("arText", 0);
  __INITYP(arText_Stream, arText_Stream, 0);
  __INITBP(arText_Stream, arText_Stream_Char, 0);
  __INITBP(arText_Stream, arText_Stream_Flush, 1);
  __INITBP(arText_Stream, arText_Stream_String, 2);
  __INITYP(arText_Writer, arText_Stream, 1);
  __INITBP(arText_Writer, arText_Writer_Boolean, 3);
  __INITBP(arText_Writer, arText_Writer_Hex, 4);
  __INITBP(arText_Writer, arText_Writer_InitWriter, 5);
  __INITBP(arText_Writer, arText_Writer_Integer, 6);
  __INITBP(arText_Writer, arText_Writer_Ln, 7);
  __INITBP(arText_Writer, arText_Writer_Real, 8);
  __INITBP(arText_Writer, arText_Writer_Set, 9);
  __INITBP(arText_Writer, arText_Writer_StringLiteral, 10);
  __INITYP(arText_StreamWriter, arText_Writer, 2);
  __INITBP(arText_StreamWriter, arText_StreamWriter_Char, 0);
  __INITBP(arText_StreamWriter, arText_StreamWriter_Flush, 1);
  __INITBP(arText_StreamWriter, arText_StreamWriter_Init, 11);
  __INITBP(arText_StreamWriter, arText_StreamWriter_String, 2);
  __INITYP(arText_Buffer, arText_Writer, 2);
  __INITBP(arText_Buffer, arText_Buffer_Char, 0);
  __INITBP(arText_Buffer, arText_Buffer_Clear, 11);
  __INITBP(arText_Buffer, arText_Buffer_EnsureCapacity, 12);
  __INITBP(arText_Buffer, arText_Buffer_GetString, 13);
  __INITBP(arText_Buffer, arText_Buffer_Init, 14);
  __INITBP(arText_Buffer, arText_Buffer_String, 2);
  __INITBP(arText_Buffer, arText_Buffer_Terminate, 15);
/* BEGIN */
  __ENDMOD;
}
