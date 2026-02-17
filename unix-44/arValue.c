/* Ofront+ 1.0 -s2 -44 */
#include "SYSTEM.oh"
#include "arText.oh"
#include "arCFormat.oh"
#include "arC.oh"
#include "arStrings.oh"

typedef
  struct arValue_Array__rec *arValue_Array;

typedef
  struct arValue_ObjectDesc {
    char _prvt0[1];
  } arValue_ObjectDesc;

typedef
  arValue_ObjectDesc *arValue_Object;

export arValue_Object arValue_Object_Copy (arValue_Object self);
export arValue_Object arValue_Object_DeepCopy (arValue_Object self);
export BOOLEAN arValue_Object_Equals (arValue_Object self, arValue_Object other);
export void arValue_Object_Format (arValue_Object self, arText_Writer *w, void **w__typ);
typedef
  struct arValue_String__rec *arValue_String;

export arValue_String arValue_Object_ToJSON (arValue_Object self);
export arValue_String arValue_Object_ToString (arValue_Object self);
#define __arValue_Object_Copy(self) __SEND(__TYPEOF(self), arValue_Object_Copy, 0, arValue_Object(*)(arValue_Object), (self))
#define __arValue_Object_DeepCopy(self) __SEND(__TYPEOF(self), arValue_Object_DeepCopy, 1, arValue_Object(*)(arValue_Object), (self))
#define __arValue_Object_Equals(self, other) __SEND(__TYPEOF(self), arValue_Object_Equals, 2, BOOLEAN(*)(arValue_Object, arValue_Object), (self, other))
#define __arValue_Object_Format(self, w, w__typ) __SEND(__TYPEOF(self), arValue_Object_Format, 3, void(*)(arValue_Object, arText_Writer*, void **), (self, w, w__typ))
#define __arValue_Object_ToJSON(self) __SEND(__TYPEOF(self), arValue_Object_ToJSON, 4, arValue_String(*)(arValue_Object), (self))
#define __arValue_Object_ToString(self) __SEND(__TYPEOF(self), arValue_Object_ToString, 5, arValue_String(*)(arValue_Object), (self))

typedef
  struct arValue_ObjectDesc_PTR_ARRAY *arValue_ObjectArray;

typedef
  struct arValue_Array__rec { /* arValue_ObjectDesc */
    arValue_ObjectArray value;
    INTEGER length;
  } arValue_Array__rec;

export arValue_Object arValue_Array_Copy (arValue_Array self);
static arValue_Array arValue_Array_CopyT (arValue_Array self, BOOLEAN deep);
export arValue_Object arValue_Array_DeepCopy (arValue_Array self);
export BOOLEAN arValue_Array_Equals (arValue_Array self, arValue_Object value);
export void arValue_Array_Format (arValue_Array self, arText_Writer *w, void **w__typ);
export arValue_Object arValue_Array_Get (arValue_Array self, INTEGER index);
export arValue_Object arValue_Array_Set (arValue_Array self, INTEGER index, arValue_Object value);
#define __arValue_Array_CopyT(self, deep) __SEND(__TYPEOF(self), arValue_Array_CopyT, 6, arValue_Array(*)(arValue_Array, BOOLEAN), (self, deep))
#define __arValue_Array_Get(self, index) __SEND(__TYPEOF(self), arValue_Array_Get, 7, arValue_Object(*)(arValue_Array, INTEGER), (self, index))
#define __arValue_Array_Set(self, index, value) __SEND(__TYPEOF(self), arValue_Array_Set, 8, arValue_Object(*)(arValue_Array, INTEGER, arValue_Object), (self, index, value))

typedef
  struct arValue_Boolean__rec *arValue_Boolean;

typedef
  struct arValue_Boolean__rec { /* arValue_ObjectDesc */
    BOOLEAN value;
  } arValue_Boolean__rec;

export arValue_Object arValue_Boolean_Copy (arValue_Boolean self);
export arValue_Boolean arValue_Boolean_CopyT (arValue_Boolean self);
export BOOLEAN arValue_Boolean_Equals (arValue_Boolean self, arValue_Object other);
export void arValue_Boolean_Format (arValue_Boolean self, arText_Writer *w, void **w__typ);
#define __arValue_Boolean_CopyT(self) __SEND(__TYPEOF(self), arValue_Boolean_CopyT, 6, arValue_Boolean(*)(arValue_Boolean), (self))

typedef
  struct INT32_ARRAY *arValue_IntArray;

typedef
  struct arValue_Integer__rec *arValue_Integer;

typedef
  struct arValue_Integer__rec { /* arValue_ObjectDesc */
    INTEGER value;
  } arValue_Integer__rec;

export arValue_Object arValue_Integer_Copy (arValue_Integer self);
export arValue_Integer arValue_Integer_CopyT (arValue_Integer self);
export BOOLEAN arValue_Integer_Equals (arValue_Integer self, arValue_Object other);
export void arValue_Integer_Format (arValue_Integer self, arText_Writer *w, void **w__typ);
#define __arValue_Integer_CopyT(self) __SEND(__TYPEOF(self), arValue_Integer_CopyT, 6, arValue_Integer(*)(arValue_Integer), (self))

typedef
  struct arValue_List__rec *arValue_List;

typedef
  struct arValue_ListElement__rec *arValue_ListElement;

typedef
  struct arValue_ListElement__rec {
    arValue_Object value;
    arValue_ListElement next;
  } arValue_ListElement__rec;

typedef
  struct arValue_List__rec { /* arValue_ObjectDesc */
    arValue_ListElement first, last;
    INTEGER length;
  } arValue_List__rec;

export void arValue_List_Append (arValue_List self, arValue_Object o);
export arValue_List arValue_List_Concat (arValue_List self, arValue_List value);
export arValue_Object arValue_List_Copy (arValue_List self);
export arValue_List arValue_List_CopyT (arValue_List self, BOOLEAN deep);
export arValue_Object arValue_List_DeepCopy (arValue_List self);
export BOOLEAN arValue_List_Equals (arValue_List self, arValue_Object other);
export void arValue_List_Extend (arValue_List self, arValue_List value);
export void arValue_List_Format (arValue_List self, arText_Writer *w, void **w__typ);
export arValue_Object arValue_List_Get (arValue_List self, INTEGER index);
export INTEGER arValue_List_IndexOf (arValue_List l, arValue_Object value);
export arValue_String arValue_List_Join (arValue_List self, CHAR *separator, INTEGER separator__len);
typedef
  arValue_Object (*arValue_MapFunction)(arValue_Object);

export arValue_List arValue_List_Map (arValue_List self, arValue_MapFunction func);
export void arValue_List_Prepend (arValue_List self, arValue_Object o);
export void arValue_List_Set (arValue_List self, INTEGER index, arValue_Object value);
static arValue_Array arValue_List_ToArray (arValue_List self);
export arValue_IntArray arValue_List_ToIntArray (arValue_List self);
export arValue_ObjectArray arValue_List_ToObjectArray (arValue_List self);
typedef
  struct CHAR8_ARRAY_PTR_ARRAY *arValue_StringArray;

export arValue_StringArray arValue_List_ToStringArray (arValue_List self);
#define __arValue_List_Append(self, o) __SEND(__TYPEOF(self), arValue_List_Append, 6, void(*)(arValue_List, arValue_Object), (self, o))
#define __arValue_List_Concat(self, value) __SEND(__TYPEOF(self), arValue_List_Concat, 7, arValue_List(*)(arValue_List, arValue_List), (self, value))
#define __arValue_List_CopyT(self, deep) __SEND(__TYPEOF(self), arValue_List_CopyT, 8, arValue_List(*)(arValue_List, BOOLEAN), (self, deep))
#define __arValue_List_Extend(self, value) __SEND(__TYPEOF(self), arValue_List_Extend, 9, void(*)(arValue_List, arValue_List), (self, value))
#define __arValue_List_Get(self, index) __SEND(__TYPEOF(self), arValue_List_Get, 10, arValue_Object(*)(arValue_List, INTEGER), (self, index))
#define __arValue_List_IndexOf(l, value) __SEND(__TYPEOF(l), arValue_List_IndexOf, 11, INTEGER(*)(arValue_List, arValue_Object), (l, value))
#define __arValue_List_Join(self, separator, separator__len) __SEND(__TYPEOF(self), arValue_List_Join, 12, arValue_String(*)(arValue_List, CHAR*, INTEGER ), (self, separator, separator__len))
#define __arValue_List_Map(self, func) __SEND(__TYPEOF(self), arValue_List_Map, 13, arValue_List(*)(arValue_List, arValue_MapFunction), (self, func))
#define __arValue_List_Prepend(self, o) __SEND(__TYPEOF(self), arValue_List_Prepend, 14, void(*)(arValue_List, arValue_Object), (self, o))
#define __arValue_List_Set(self, index, value) __SEND(__TYPEOF(self), arValue_List_Set, 15, void(*)(arValue_List, INTEGER, arValue_Object), (self, index, value))
#define __arValue_List_ToArray(self) __SEND(__TYPEOF(self), arValue_List_ToArray, 16, arValue_Array(*)(arValue_List), (self))
#define __arValue_List_ToIntArray(self) __SEND(__TYPEOF(self), arValue_List_ToIntArray, 17, arValue_IntArray(*)(arValue_List), (self))
#define __arValue_List_ToObjectArray(self) __SEND(__TYPEOF(self), arValue_List_ToObjectArray, 18, arValue_ObjectArray(*)(arValue_List), (self))
#define __arValue_List_ToStringArray(self) __SEND(__TYPEOF(self), arValue_List_ToStringArray, 19, arValue_StringArray(*)(arValue_List), (self))

typedef
  struct arValue_Real__rec *arValue_Real;

typedef
  struct arValue_Real__rec { /* arValue_ObjectDesc */
    REAL value;
  } arValue_Real__rec;

export arValue_Object arValue_Real_Copy (arValue_Real self);
export arValue_Real arValue_Real_CopyT (arValue_Real self);
export BOOLEAN arValue_Real_Equals (arValue_Real self, arValue_Object other);
export void arValue_Real_Format (arValue_Real self, arText_Writer *w, void **w__typ);
#define __arValue_Real_CopyT(self) __SEND(__TYPEOF(self), arValue_Real_CopyT, 6, arValue_Real(*)(arValue_Real), (self))

typedef
  struct arValue_Record__rec *arValue_Record;

typedef
  struct arValue_RecordElement__rec *arValue_RecordElement;

typedef
  struct arValue_RecordElement__rec {
    arValue_String key;
    arValue_Object value;
    arValue_RecordElement next;
  } arValue_RecordElement__rec;

typedef
  struct arValue_Record__rec { /* arValue_ObjectDesc */
    arValue_RecordElement scope;
    INTEGER length;
    arValue_RecordElement last;
  } arValue_Record__rec;

static void arValue_Record_Bind (arValue_Record self, CHAR *key, INTEGER key__len, arValue_Object value);
export arValue_Object arValue_Record_Copy (arValue_Record self);
export arValue_Record arValue_Record_CopyT (arValue_Record self, BOOLEAN deep);
export arValue_Object arValue_Record_DeepCopy (arValue_Record self);
export BOOLEAN arValue_Record_Equals (arValue_Record self, arValue_Object value);
export void arValue_Record_Format (arValue_Record self, arText_Writer *w, void **w__typ);
export arValue_Object arValue_Record_Get (arValue_Record self, CHAR *key, INTEGER key__len);
export arValue_Record arValue_Record_Map (arValue_Record self, arValue_MapFunction func);
export void arValue_Record_Set (arValue_Record self, CHAR *key, INTEGER key__len, arValue_Object value);
#define __arValue_Record_Bind(self, key, key__len, value) __SEND(__TYPEOF(self), arValue_Record_Bind, 6, void(*)(arValue_Record, CHAR*, INTEGER , arValue_Object), (self, key, key__len, value))
#define __arValue_Record_CopyT(self, deep) __SEND(__TYPEOF(self), arValue_Record_CopyT, 7, arValue_Record(*)(arValue_Record, BOOLEAN), (self, deep))
#define __arValue_Record_Get(self, key, key__len) __SEND(__TYPEOF(self), arValue_Record_Get, 8, arValue_Object(*)(arValue_Record, CHAR*, INTEGER ), (self, key, key__len))
#define __arValue_Record_Map(self, func) __SEND(__TYPEOF(self), arValue_Record_Map, 9, arValue_Record(*)(arValue_Record, arValue_MapFunction), (self, func))
#define __arValue_Record_Set(self, key, key__len, value) __SEND(__TYPEOF(self), arValue_Record_Set, 10, void(*)(arValue_Record, CHAR*, INTEGER , arValue_Object), (self, key, key__len, value))

typedef
  struct arValue_Set__rec *arValue_Set;

typedef
  struct arValue_Set__rec { /* arValue_ObjectDesc */
    SET value;
  } arValue_Set__rec;

export arValue_Object arValue_Set_Copy (arValue_Set self);
export arValue_Set arValue_Set_CopyT (arValue_Set self);
export BOOLEAN arValue_Set_Equals (arValue_Set self, arValue_Object other);
export void arValue_Set_Format (arValue_Set self, arText_Writer *w, void **w__typ);
#define __arValue_Set_CopyT(self) __SEND(__TYPEOF(self), arValue_Set_CopyT, 6, arValue_Set(*)(arValue_Set), (self))

typedef
  struct arValue_String__rec { /* arValue_ObjectDesc */
    arText_String value;
    INTEGER length;
  } arValue_String__rec;

export BYTE arValue_String_Compare (arValue_String self, CHAR *value, INTEGER value__len);
export arValue_String arValue_String_Concat (arValue_String self, arValue_String arg);
export arValue_Object arValue_String_Copy (arValue_String self);
export arValue_String arValue_String_CopyT (arValue_String self);
export BOOLEAN arValue_String_EndsWith (arValue_String self, CHAR *value, INTEGER value__len);
export BOOLEAN arValue_String_Equals (arValue_String self, arValue_Object other);
export arValue_String arValue_String_Extract (arValue_String self, INTEGER start, INTEGER count);
export void arValue_String_Format (arValue_String self, arText_Writer *w, void **w__typ);
export arValue_List arValue_String_Split (arValue_String self, CHAR separator);
export BOOLEAN arValue_String_StartsWith (arValue_String self, CHAR *value, INTEGER value__len);
export INTEGER arValue_String_ToInteger (arValue_String self);
export REAL arValue_String_ToReal (arValue_String self);
#define __arValue_String_Compare(self, value, value__len) __SEND(__TYPEOF(self), arValue_String_Compare, 6, BYTE(*)(arValue_String, CHAR*, INTEGER ), (self, value, value__len))
#define __arValue_String_Concat(self, arg) __SEND(__TYPEOF(self), arValue_String_Concat, 7, arValue_String(*)(arValue_String, arValue_String), (self, arg))
#define __arValue_String_CopyT(self) __SEND(__TYPEOF(self), arValue_String_CopyT, 8, arValue_String(*)(arValue_String), (self))
#define __arValue_String_EndsWith(self, value, value__len) __SEND(__TYPEOF(self), arValue_String_EndsWith, 9, BOOLEAN(*)(arValue_String, CHAR*, INTEGER ), (self, value, value__len))
#define __arValue_String_Extract(self, start, count) __SEND(__TYPEOF(self), arValue_String_Extract, 10, arValue_String(*)(arValue_String, INTEGER, INTEGER), (self, start, count))
#define __arValue_String_Split(self, separator) __SEND(__TYPEOF(self), arValue_String_Split, 11, arValue_List(*)(arValue_String, CHAR), (self, separator))
#define __arValue_String_StartsWith(self, value, value__len) __SEND(__TYPEOF(self), arValue_String_StartsWith, 12, BOOLEAN(*)(arValue_String, CHAR*, INTEGER ), (self, value, value__len))
#define __arValue_String_ToInteger(self) __SEND(__TYPEOF(self), arValue_String_ToInteger, 13, INTEGER(*)(arValue_String), (self))
#define __arValue_String_ToReal(self) __SEND(__TYPEOF(self), arValue_String_ToReal, 14, REAL(*)(arValue_String), (self))


#ifndef INT32_ARRAY_DEF
#define INT32_ARRAY_DEF
typedef struct INT32_ARRAY {
  INTEGER len[1];
  INTEGER data[1];
} INT32_ARRAY;
#endif 

#ifndef arValue_ObjectDesc_PTR_ARRAY_DEF
#define arValue_ObjectDesc_PTR_ARRAY_DEF
typedef struct arValue_ObjectDesc_PTR_ARRAY {
  INTEGER len[1];
  arValue_ObjectDesc *data[1];
} arValue_ObjectDesc_PTR_ARRAY;
#endif 

#ifndef CHAR8_ARRAY_PTR_ARRAY_DEF
#define CHAR8_ARRAY_PTR_ARRAY_DEF
typedef struct CHAR8_ARRAY_PTR_ARRAY {
  INTEGER len[1];
  struct CHAR8_ARRAY *data[1];
} CHAR8_ARRAY_PTR_ARRAY;
#endif 


export void **arValue_ObjectDesc__typ;
export void **arValue_String__rec__typ;
export void **arValue_Boolean__rec__typ;
export void **arValue_Integer__rec__typ;
export void **arValue_Real__rec__typ;
export void **arValue_Set__rec__typ;
export void **arValue_ListElement__rec__typ;
export void **arValue_List__rec__typ;
export void **arValue_Array__rec__typ;
export void **arValue_RecordElement__rec__typ;
export void **arValue_Record__rec__typ;

export arValue_Object arValue_Copy (arValue_Object o);
export arValue_Object arValue_DeepCopy (arValue_Object o);
export BOOLEAN arValue_Equals (arValue_Object a, arValue_Object b);
export void arValue_Format (arText_Writer *w, void **w__typ, arValue_Object o);
export void arValue_FormatQ (arText_Writer *w, void **w__typ, arValue_Object o);
export INTEGER arValue_Max (INTEGER a, INTEGER b);
export INTEGER arValue_Min (INTEGER a, INTEGER b);
static arValue_Array arValue_NewArray (INTEGER length);
export arValue_Boolean arValue_NewBoolean (BOOLEAN value);
export arValue_Integer arValue_NewInteger (INTEGER value);
export arValue_List arValue_NewList (void);
export arValue_Real arValue_NewReal (REAL value);
export arValue_Record arValue_NewRecord (void);
export arValue_Set arValue_NewSet (SET value);
export arValue_Boolean arValue_ParseBool (CHAR *value, INTEGER value__len);
export arValue_Integer arValue_ParseInt (CHAR *value, INTEGER value__len);
export arValue_Real arValue_ParseReal (CHAR *value, INTEGER value__len);
export arValue_List arValue_Split (CHAR *value, INTEGER value__len, CHAR separator);
export arValue_String arValue_StringFromBuffer (arText_Buffer *buffer, void **buffer__typ);
export arValue_String arValue_StringFromCharArray (CHAR *value, INTEGER value__len);
export arValue_String arValue_StringFromCharPointer (arText_String value);
export arValue_String arValue_ToJSON (arValue_Object self);
export arValue_String arValue_ToString (arValue_Object self);
export arValue_Array arValue_array2 (arValue_Object a, arValue_Object b);
export arValue_Array arValue_array3 (arValue_Object a, arValue_Object b, arValue_Object c);
export arValue_Array arValue_array4 (arValue_Object a, arValue_Object b, arValue_Object c, arValue_Object d);
export arValue_Boolean arValue_bool (BOOLEAN value);
export arValue_String arValue_char (CHAR value);
export arValue_Integer arValue_int (INTEGER value);
export arValue_List arValue_list (void);
export arValue_Real arValue_real (REAL value);
export arValue_Record arValue_record (void);
export arValue_Set arValue_set (SET value);
export arValue_String arValue_str (CHAR *value, INTEGER value__len);
export arValue_String arValue_strb (arText_Buffer *value, void **value__typ);
export arValue_String arValue_strp (arText_String value);


/*============================================================================*/

INTEGER arValue_Min (INTEGER a, INTEGER b)
{
  if (a < b) {
    return a;
  } else {
    return b;
  }
  __RETCHK((CHAR*)"arValue", 31013);
}

/*----------------------------------------------------------------------------*/
INTEGER arValue_Max (INTEGER a, INTEGER b)
{
  if (a > b) {
    return a;
  } else {
    return b;
  }
  __RETCHK((CHAR*)"arValue", 32293);
}

/*----------------------------------------------------------------------------*/
void arValue_Object_Format (arValue_Object self, arText_Writer *w, void **w__typ)
{
}

/*----------------------------------------------------------------------------*/
arValue_Object arValue_Object_Copy (arValue_Object self)
{
  return NIL;
}

/*----------------------------------------------------------------------------*/
arValue_Object arValue_Object_DeepCopy (arValue_Object self)
{
  return __arValue_Object_Copy(self);
}

/*----------------------------------------------------------------------------*/
arValue_String arValue_Object_ToString (arValue_Object self)
{
  arText_Buffer buffer = {0};
  __arText_Buffer_Init(&buffer, arText_Buffer__typ, 16);
  __arValue_Object_Format(self, (void*)&buffer, arText_Buffer__typ);
  return arValue_StringFromBuffer(&buffer, arText_Buffer__typ);
}

/*----------------------------------------------------------------------------*/
arValue_String arValue_Object_ToJSON (arValue_Object self)
{
  arText_Buffer buffer = {0};
  __arText_Buffer_Init(&buffer, arText_Buffer__typ, 16);
  buffer.quoteLiterals = 1;
  buffer.setAsList = 1;
  __arValue_Object_Format(self, (void*)&buffer, arText_Buffer__typ);
  return arValue_StringFromBuffer(&buffer, arText_Buffer__typ);
}

/*----------------------------------------------------------------------------*/
BOOLEAN arValue_Object_Equals (arValue_Object self, arValue_Object other)
{
  return 0;
}

/*----------------------------------------------------------------------------*/
arValue_String arValue_ToString (arValue_Object self)
{
  if (self == NIL) {
    return arValue_StringFromCharArray((CHAR*)"null", 5);
  }
  return __arValue_Object_ToString(self);
}

/*----------------------------------------------------------------------------*/
arValue_String arValue_ToJSON (arValue_Object self)
{
  if (self == NIL) {
    return arValue_StringFromCharArray((CHAR*)"null", 5);
  }
  return __arValue_Object_ToJSON(self);
}

/*----------------------------------------------------------------------------*/
void arValue_Format (arText_Writer *w, void **w__typ, arValue_Object o)
{
  if (o == NIL) {
    __arText_Stream_String((void*)w, w__typ, (CHAR*)"null", 5);
  } else {
    __arValue_Object_Format(o, w, w__typ);
  }
}

/*----------------------------------------------------------------------------*/
arValue_Object arValue_Copy (arValue_Object o)
{
  if (o == NIL) {
    return NIL;
  } else {
    return __arValue_Object_Copy(o);
  }
  __RETCHK((CHAR*)"arValue", 51217);
}

/*----------------------------------------------------------------------------*/
arValue_Object arValue_DeepCopy (arValue_Object o)
{
  if (o == NIL) {
    return NIL;
  } else {
    return __arValue_Object_DeepCopy(o);
  }
  __RETCHK((CHAR*)"arValue", 53525);
}

/*----------------------------------------------------------------------------*/
BOOLEAN arValue_Equals (arValue_Object a, arValue_Object b)
{
  if (a == NIL && b == NIL) {
    return 1;
  } else if (a == NIL || b == NIL) {
    return 0;
  } else {
    return __arValue_Object_Equals(a, b);
  }
  __RETCHK((CHAR*)"arValue", 56340);
}

/*----------------------------------------------------------------------------*/
void arValue_FormatQ (arText_Writer *w, void **w__typ, arValue_Object o)
{
  BOOLEAN wasQuoted;
  wasQuoted = (*w).quoteLiterals;
  (*w).quoteLiterals = 1;
  arValue_Format(w, w__typ, o);
  (*w).quoteLiterals = wasQuoted;
}

/*----------------------------------------------------------------------------*/
arValue_String arValue_StringFromCharArray (CHAR *value, INTEGER value__len)
{
  arValue_String s = NIL;
  __NEW(s, arValue_String__rec);
  s->length = arStrings_Length((void*)value, value__len);
  s->value = __NEWARR(NIL, 1, 1, 1, 1, (SYSTEM_ARRLEN)(s->length + 1));
  __COPY(value, s->value->data, __MIN(s->value->len[0], value__len));
  return s;
}

/*----------------------------------------------------------------------------*/
arValue_String arValue_char (CHAR value)
{
  CHAR array[2];
  array[0] = value;
  array[1] = 0x00;
  return arValue_StringFromCharArray((void*)array, 2);
}

/*----------------------------------------------------------------------------*/
arValue_String arValue_StringFromCharPointer (arText_String value)
{
  arValue_String s = NIL;
  __NEW(s, arValue_String__rec);
  s->value = value;
  s->length = arStrings_Length((void*)value->data, value->len[0]);
  return s;
}

/*----------------------------------------------------------------------------*/
arValue_String arValue_StringFromBuffer (arText_Buffer *buffer, void **buffer__typ)
{
  return arValue_StringFromCharPointer(__arText_Buffer_GetString(buffer, buffer__typ));
}

/*----------------------------------------------------------------------------*/
BOOLEAN arValue_String_Equals (arValue_String self, arValue_Object other)
{
  arText_String _ptr__16 = NIL;
  arText_String _ptr__15 = NIL;
  if (__ISP(other, arValue_String__rec, 1)) {
    return (_ptr__16 = self->value, 
      _ptr__15 = ((arValue_String)other)->value, 
      arStrings_Equal((void*)_ptr__16->data, _ptr__16->len[0], (void*)_ptr__15->data, _ptr__15->len[0]));
  } else {
    return 0;
  }
  __RETCHK((CHAR*)"arValue", 70911);
}

/*----------------------------------------------------------------------------*/
arValue_String arValue_String_CopyT (arValue_String self)
{
  return arValue_StringFromCharPointer(self->value);
}

/*----------------------------------------------------------------------------*/
arValue_Object arValue_String_Copy (arValue_String self)
{
  return (void*)(__arValue_String_CopyT(self));
}

/*----------------------------------------------------------------------------*/
void arValue_String_Format (arValue_String self, arText_Writer *w, void **w__typ)
{
  __arText_Writer_StringLiteral(w, w__typ, self->value->data, self->value->len[0]);
}

/*----------------------------------------------------------------------------*/
arValue_String arValue_String_Concat (arValue_String self, arValue_String arg)
{
  arValue_String result = NIL;
  arText_String _ptr__9 = NIL;
  arText_String _ptr__8 = NIL;
  __NEW(result, arValue_String__rec);
  result->length = self->length + arg->length;
  result->value = __NEWARR(NIL, 1, 1, 1, 1, (SYSTEM_ARRLEN)(result->length + 1));
  __COPY(self->value->data, result->value->data, __MIN(result->value->len[0], self->value->len[0]));
  _ptr__9 = arg->value;
  _ptr__8 = result->value;
  arStrings_Append((void*)_ptr__9->data, _ptr__9->len[0], (void*)_ptr__8->data, _ptr__8->len[0]);
  return result;
}

/*----------------------------------------------------------------------------*/
INTEGER arValue_String_ToInteger (arValue_String self)
{
  INTEGER i, res;
  i = 0;
  res = arCFormat_StringToInt(self->value->data, self->value->len[0], &i);
  return i;
}

/*----------------------------------------------------------------------------*/
REAL arValue_String_ToReal (arValue_String self)
{
  INTEGER res;
  REAL value;
  value = (REAL)0;
  res = arCFormat_StringToReal(self->value->data, self->value->len[0], &value);
  return value;
}

/*----------------------------------------------------------------------------*/
arValue_String arValue_String_Extract (arValue_String self, INTEGER start, INTEGER count)
{
  arText_String result = NIL;
  INTEGER i, _for__18;
  if (start < 0) {
    start = self->length + start;
  }
  start = arValue_Min(self->length, arValue_Max(start, 0));
  count = arValue_Min(arValue_Max(count, 0), self->length - start);
  result = __NEWARR(NIL, 1, 1, 1, 1, (SYSTEM_ARRLEN)(count + 1));
  _for__18 = count - 1;
  i = 0;
  while (i <= _for__18) {
    (result->data)[__X(i, result->len[0], (CHAR*)"arValue", 86271)] = (self->value->data)[__X(i + start, self->value->len[0], (CHAR*)"arValue", 86271)];
    i += 1;
  }
  (result->data)[__X(count, result->len[0], (CHAR*)"arValue", 86548)] = 0x00;
  return arValue_StringFromCharPointer(result);
}

/*----------------------------------------------------------------------------*/
BYTE arValue_String_Compare (arValue_String self, CHAR *value, INTEGER value__len)
{
  arText_String _ptr__6 = NIL;
  return (_ptr__6 = self->value, 
    arStrings_Compare((void*)_ptr__6->data, _ptr__6->len[0], (void*)value, value__len));
}

/*----------------------------------------------------------------------------*/
BOOLEAN arValue_String_EndsWith (arValue_String self, CHAR *value, INTEGER value__len)
{
  INTEGER i, length, _for__13;
  length = arStrings_Length((void*)value, value__len);
  if (self->length < length) {
    return 0;
  }
  _for__13 = length - 1;
  i = 0;
  while (i <= _for__13) {
    if (value[__X(i, value__len, (CHAR*)"arValue", 90438)] != (self->value->data)[__X((self->length - length) + i, self->value->len[0], (CHAR*)"arValue", 90438)]) {
      return 0;
    }
    i += 1;
  }
  return 1;
}

/*----------------------------------------------------------------------------*/
BOOLEAN arValue_String_StartsWith (arValue_String self, CHAR *value, INTEGER value__len)
{
  INTEGER i, length, _for__41;
  length = arStrings_Length((void*)value, value__len);
  if (self->length < length) {
    return 0;
  }
  _for__41 = length - 1;
  i = 0;
  while (i <= _for__41) {
    if (value[__X(i, value__len, (CHAR*)"arValue", 93235)] != (self->value->data)[__X(i, self->value->len[0], (CHAR*)"arValue", 93235)]) {
      return 0;
    }
    i += 1;
  }
  return 1;
}

/*----------------------------------------------------------------------------*/
arValue_Boolean arValue_NewBoolean (BOOLEAN value)
{
  arValue_Boolean b = NIL;
  __NEW(b, arValue_Boolean__rec);
  b->value = value;
  return b;
}

/*----------------------------------------------------------------------------*/
arValue_Boolean arValue_ParseBool (CHAR *value, INTEGER value__len)
{
  if (__STRCMPCC(value, (CHAR*)"true", 5, (CHAR*)"arValue", 98052) == 0) {
    return arValue_NewBoolean(1);
  } else if (__STRCMPCC(value, (CHAR*)"false", 6, (CHAR*)"arValue", 97305) == 0) {
    return arValue_NewBoolean(0);
  }
  return NIL;
}

/*----------------------------------------------------------------------------*/
arValue_Boolean arValue_Boolean_CopyT (arValue_Boolean self)
{
  return arValue_NewBoolean(self->value);
}

/*----------------------------------------------------------------------------*/
arValue_Object arValue_Boolean_Copy (arValue_Boolean self)
{
  return (void*)(__arValue_Boolean_CopyT(self));
}

/*----------------------------------------------------------------------------*/
BOOLEAN arValue_Boolean_Equals (arValue_Boolean self, arValue_Object other)
{
  if (__ISP(other, arValue_Boolean__rec, 1)) {
    return self->value == ((arValue_Boolean)other)->value;
  } else {
    return 0;
  }
  __RETCHK((CHAR*)"arValue", 103167);
}

/*----------------------------------------------------------------------------*/
void arValue_Boolean_Format (arValue_Boolean self, arText_Writer *w, void **w__typ)
{
  __arText_Writer_Boolean(w, w__typ, self->value);
}

/*----------------------------------------------------------------------------*/
arValue_Set arValue_NewSet (SET value)
{
  arValue_Set s = NIL;
  __NEW(s, arValue_Set__rec);
  s->value = value;
  return s;
}

/*----------------------------------------------------------------------------*/
BOOLEAN arValue_Set_Equals (arValue_Set self, arValue_Object other)
{
  if (__ISP(other, arValue_Set__rec, 1)) {
    return self->value == ((arValue_Set)other)->value;
  } else {
    return 0;
  }
  __RETCHK((CHAR*)"arValue", 108799);
}

/*----------------------------------------------------------------------------*/
arValue_Set arValue_Set_CopyT (arValue_Set self)
{
  return arValue_NewSet(self->value);
}

/*----------------------------------------------------------------------------*/
arValue_Object arValue_Set_Copy (arValue_Set self)
{
  return (void*)(__arValue_Set_CopyT(self));
}

/*----------------------------------------------------------------------------*/
void arValue_Set_Format (arValue_Set self, arText_Writer *w, void **w__typ)
{
  __arText_Writer_Set(w, w__typ, self->value);
}

/*----------------------------------------------------------------------------*/
arValue_Integer arValue_NewInteger (INTEGER value)
{
  arValue_Integer i = NIL;
  __NEW(i, arValue_Integer__rec);
  i->value = value;
  return i;
}

/*----------------------------------------------------------------------------*/
arValue_Integer arValue_ParseInt (CHAR *value, INTEGER value__len)
{
  INTEGER i, res;
  res = arCFormat_StringToInt(value, value__len, &i);
  if (res == 1) {
    return arValue_NewInteger(i);
  }
  return NIL;
}

/*----------------------------------------------------------------------------*/
BOOLEAN arValue_Integer_Equals (arValue_Integer self, arValue_Object other)
{
  if (__ISP(other, arValue_Integer__rec, 1)) {
    return self->value == ((arValue_Integer)other)->value;
  } else {
    return 0;
  }
  __RETCHK((CHAR*)"arValue", 120063);
}

/*----------------------------------------------------------------------------*/
arValue_Integer arValue_Integer_CopyT (arValue_Integer self)
{
  return arValue_NewInteger(self->value);
}

/*----------------------------------------------------------------------------*/
arValue_Object arValue_Integer_Copy (arValue_Integer self)
{
  return (void*)(__arValue_Integer_CopyT(self));
}

/*----------------------------------------------------------------------------*/
void arValue_Integer_Format (arValue_Integer self, arText_Writer *w, void **w__typ)
{
  __arText_Writer_Integer(w, w__typ, self->value);
}

/*----------------------------------------------------------------------------*/
arValue_Real arValue_NewReal (REAL value)
{
  arValue_Real r = NIL;
  __NEW(r, arValue_Real__rec);
  r->value = value;
  return r;
}

/*----------------------------------------------------------------------------*/
arValue_Real arValue_ParseReal (CHAR *value, INTEGER value__len)
{
  REAL r;
  INTEGER res;
  res = arCFormat_StringToReal(value, value__len, &r);
  if (res == 1) {
    return arValue_NewReal(r);
  }
  return NIL;
}

/*----------------------------------------------------------------------------*/
BOOLEAN arValue_Real_Equals (arValue_Real self, arValue_Object other)
{
  if (__ISP(other, arValue_Real__rec, 1)) {
    return self->value == ((arValue_Real)other)->value;
  } else {
    return 0;
  }
  __RETCHK((CHAR*)"arValue", 131839);
}

/*----------------------------------------------------------------------------*/
arValue_Real arValue_Real_CopyT (arValue_Real self)
{
  return arValue_NewReal(self->value);
}

/*----------------------------------------------------------------------------*/
arValue_Object arValue_Real_Copy (arValue_Real self)
{
  return (void*)(__arValue_Real_CopyT(self));
}

/*----------------------------------------------------------------------------*/
void arValue_Real_Format (arValue_Real self, arText_Writer *w, void **w__typ)
{
  __arText_Writer_Real(w, w__typ, self->value);
}

/*----------------------------------------------------------------------------*/
arValue_List arValue_NewList (void)
{
  arValue_List l = NIL;
  __NEW(l, arValue_List__rec);
  l->first = NIL;
  l->last = NIL;
  l->length = 0;
  return l;
}

/*----------------------------------------------------------------------------*/
BOOLEAN arValue_List_Equals (arValue_List self, arValue_Object other)
{
  arValue_ListElement a = NIL;
  arValue_ListElement b = NIL;
  if (__ISP(other, arValue_List__rec, 1)) {
    if (self->length != ((arValue_List)other)->length) {
      return 0;
    }
    a = self->first;
    b = ((arValue_List)other)->first;
    while (a != NIL && b != NIL) {
      if (!arValue_Equals(a->value, b->value)) {
        return 0;
      }
      a = a->next;
      b = b->next;
    }
    __ASSERT(a == b, 0, (CHAR*)"arValue", 143375);
    return 1;
  } else {
    return 0;
  }
  __RETCHK((CHAR*)"arValue", 144383);
}

/*----------------------------------------------------------------------------*/
void arValue_List_Format (arValue_List self, arText_Writer *w, void **w__typ)
{
  arValue_ListElement n = NIL;
  __arText_Stream_Char((void*)w, w__typ, '[');
  n = self->first;
  while (n != NIL) {
    arValue_FormatQ(w, w__typ, n->value);
    n = n->next;
    if (n != NIL) {
      __arText_Stream_Char((void*)w, w__typ, ',');
    }
  }
  __arText_Stream_Char((void*)w, w__typ, ']');
}

/*----------------------------------------------------------------------------*/
INTEGER arValue_List_IndexOf (arValue_List l, arValue_Object value)
{
  INTEGER i;
  arValue_ListElement a = NIL;
  i = 0;
  a = l->first;
  while (a != NIL) {
    if (arValue_Equals(value, a->value)) {
      return i;
    }
    i += 1;
    a = a->next;
  }
  return -1;
}

/*----------------------------------------------------------------------------*/
void arValue_List_Append (arValue_List self, arValue_Object o)
{
  arValue_ListElement node = NIL;
  __NEW(node, arValue_ListElement__rec);
  node->value = o;
  node->next = NIL;
  if (self->length == 0) {
    self->first = node;
  } else {
    self->last->next = node;
  }
  self->last = node;
  self->length += 1;
}

/*----------------------------------------------------------------------------*/
arValue_List arValue_List_Concat (arValue_List self, arValue_List value)
{
  arValue_List result = NIL;
  arValue_ListElement e = NIL;
  result = arValue_NewList();
  e = self->first;
  while (e != NIL) {
    __arValue_List_Append(result, e->value);
    e = e->next;
  }
  e = value->first;
  while (e != NIL) {
    __arValue_List_Append(result, e->value);
    e = e->next;
  }
  return result;
}

/*----------------------------------------------------------------------------*/
void arValue_List_Prepend (arValue_List self, arValue_Object o)
{
  arValue_ListElement node = NIL;
  __NEW(node, arValue_ListElement__rec);
  node->value = o;
  node->next = self->first;
  if (self->length == 0) {
    self->last = node;
  }
  self->first = node;
  self->length += 1;
}

/*----------------------------------------------------------------------------*/
void arValue_List_Extend (arValue_List self, arValue_List value)
{
  arValue_ListElement e = NIL;
  e = value->first;
  while (e != NIL) {
    __arValue_List_Append(self, e->value);
    e = e->next;
  }
}

/*----------------------------------------------------------------------------*/
arValue_IntArray arValue_List_ToIntArray (arValue_List self)
{
  INTEGER i, count;
  arValue_ListElement it = NIL;
  arValue_IntArray result = NIL;
  count = 0;
  it = self->first;
  while (it != NIL) {
    if (__ISP(it->value, arValue_Integer__rec, 1)) {
      count += 1;
    }
    it = it->next;
  }
  result = __NEWARR(NIL, 4, 4, 1, 1, (SYSTEM_ARRLEN)count);
  it = self->first;
  i = 0;
  while (it != NIL) {
    if (__ISP(it->value, arValue_Integer__rec, 1)) {
      (result->data)[__X(i, result->len[0], (CHAR*)"arValue", 170535)] = (__GUARDP(it->value, arValue_Integer__rec, 1))->value;
      i += 1;
    }
    it = it->next;
  }
  __ASSERT(i == count, 0, (CHAR*)"arValue", 171794);
  return result;
}

/*----------------------------------------------------------------------------*/
arValue_StringArray arValue_List_ToStringArray (arValue_List self)
{
  INTEGER i, count;
  arValue_ListElement it = NIL;
  arValue_StringArray result = NIL;
  count = 0;
  it = self->first;
  while (it != NIL) {
    if (__ISP(it->value, arValue_String__rec, 1)) {
      count += 1;
    }
    it = it->next;
  }
  result = __NEWARR(POINTER__typ, 4, 4, 1, 1, (SYSTEM_ARRLEN)count);
  it = self->first;
  i = 0;
  while (it != NIL) {
    if (__ISP(it->value, arValue_String__rec, 1)) {
      (result->data)[__X(i, result->len[0], (CHAR*)"arValue", 177702)] = (__GUARDP(it->value, arValue_String__rec, 1))->value;
      i += 1;
    }
    it = it->next;
  }
  __ASSERT(i == count, 0, (CHAR*)"arValue", 178962);
  return result;
}

/*----------------------------------------------------------------------------*/
arValue_ObjectArray arValue_List_ToObjectArray (arValue_List self)
{
  INTEGER i;
  arValue_ListElement it = NIL;
  arValue_ObjectArray result = NIL;
  result = __NEWARR(POINTER__typ, 4, 4, 1, 1, (SYSTEM_ARRLEN)self->length);
  it = self->first;
  i = 0;
  while (it != NIL) {
    (result->data)[__X(i, result->len[0], (CHAR*)"arValue", 182551)] = it->value;
    i += 1;
    it = it->next;
  }
  __ASSERT(i == self->length, 0, (CHAR*)"arValue", 183576);
  return result;
}

/*----------------------------------------------------------------------------*/
static arValue_Array arValue_List_ToArray (arValue_List self)
{
  arValue_Array a = NIL;
  __NEW(a, arValue_Array__rec);
  a->length = self->length;
  a->value = __arValue_List_ToObjectArray(self);
  return a;
}

arValue_Object arValue_List_Get (arValue_List self, INTEGER index)
{
  arValue_ListElement it = NIL;
  __ASSERT(index >= 0 && index < self->length, 0, (CHAR*)"arValue", 187693);
  it = self->first;
  while (index > 0) {
    it = it->next;
    index -= 1;
  }
  return it->value;
}

/*----------------------------------------------------------------------------*/
void arValue_List_Set (arValue_List self, INTEGER index, arValue_Object value)
{
  arValue_ListElement it = NIL;
  __ASSERT(index >= 0 && index < self->length, 0, (CHAR*)"arValue", 190509);
  it = self->first;
  while (index > 0) {
    it = it->next;
    index -= 1;
  }
  it->value = value;
}

/*----------------------------------------------------------------------------*/
arValue_String arValue_List_Join (arValue_List self, CHAR *separator, INTEGER separator__len)
{
  arText_Buffer b = {0};
  arValue_ListElement it = NIL;
  __arText_Buffer_Init(&b, arText_Buffer__typ, 32);
  it = self->first;
  while (it != NIL) {
    arValue_Format((void*)&b, arText_Buffer__typ, it->value);
    it = it->next;
    if (it != NIL) {
      __arText_Stream_String((void*)&b, arText_Buffer__typ, (void*)separator, separator__len);
    }
  }
  return arValue_StringFromBuffer(&b, arText_Buffer__typ);
}

/*----------------------------------------------------------------------------*/
arValue_List arValue_List_Map (arValue_List self, arValue_MapFunction func)
{
  arValue_Object funcResult = NIL;
  arValue_List result = NIL;
  arValue_ListElement it = NIL;
  result = arValue_NewList();
  it = self->first;
  while (it != NIL) {
    funcResult = (*func)(it->value);
    if (funcResult != NIL) {
      __arValue_List_Append(result, funcResult);
    }
    it = it->next;
  }
  return NIL;
}

/*----------------------------------------------------------------------------*/
arValue_List arValue_String_Split (arValue_String self, CHAR separator)
{
  arValue_List l = NIL;
  INTEGER begin, i, _for__39;
  l = arValue_NewList();
  begin = 0;
  _for__39 = self->length - 1;
  i = 0;
  while (i <= _for__39) {
    if ((self->value->data)[__X(i, self->value->len[0], (CHAR*)"arValue", 203781)] == separator) {
      __arValue_List_Append(l, (void*)__arValue_String_Extract(self, begin, i - begin));
      begin = i + 1;
    }
    i += 1;
  }
  if (begin <= self->length) {
    __arValue_List_Append(l, (void*)__arValue_String_Extract(self, begin, self->length - begin));
  }
  return l;
}

/*----------------------------------------------------------------------------*/
arValue_List arValue_List_CopyT (arValue_List self, BOOLEAN deep)
{
  arValue_ListElement e = NIL;
  arValue_List l = NIL;
  arValue_Object value = NIL;
  l = arValue_NewList();
  e = self->first;
  while (e != NIL) {
    value = e->value;
    if (deep) {
      value = arValue_DeepCopy(value);
    }
    __arValue_List_Append(l, value);
    e = e->next;
  }
  return l;
}

/*----------------------------------------------------------------------------*/
arValue_Object arValue_List_Copy (arValue_List self)
{
  return (void*)(__arValue_List_CopyT(self, 0));
}

/*----------------------------------------------------------------------------*/
arValue_Object arValue_List_DeepCopy (arValue_List self)
{
  return (void*)(__arValue_List_CopyT(self, 1));
}

/*----------------------------------------------------------------------------*/
arValue_Record arValue_NewRecord (void)
{
  arValue_Record r = NIL;
  __NEW(r, arValue_Record__rec);
  r->scope = NIL;
  r->last = NIL;
  r->length = 0;
  return r;
}

/*----------------------------------------------------------------------------*/
arValue_Object arValue_Record_Get (arValue_Record self, CHAR *key, INTEGER key__len)
{
  arValue_RecordElement elem = NIL;
  elem = self->scope;
  while (elem != NIL && __arValue_String_Compare(elem->key, (void*)key, key__len) != 0) {
    elem = elem->next;
  }
  if (elem != NIL) {
    return elem->value;
  }
  return NIL;
}

/*----------------------------------------------------------------------------*/
static void arValue_Record_Bind (arValue_Record self, CHAR *key, INTEGER key__len, arValue_Object value)
{
  arValue_RecordElement elem = NIL;
  __NEW(elem, arValue_RecordElement__rec);
  elem->key = arValue_StringFromCharArray((void*)key, key__len);
  elem->value = value;
  elem->next = NIL;
  if (self->scope == NIL) {
    self->scope = elem;
  } else {
    self->last->next = elem;
  }
  self->last = elem;
  self->length += 1;
}

BOOLEAN arValue_Record_Equals (arValue_Record self, arValue_Object value)
{
  arValue_RecordElement elem = NIL;
  arText_String _ptr__74 = NIL;
  if (__ISP(value, arValue_Record__rec, 1)) {
    if (((arValue_Record)value)->length != self->length) {
      return 0;
    }
    elem = self->scope;
    while (elem != NIL) {
      if (!arValue_Equals(elem->value, (_ptr__74 = elem->key->value, 
        __arValue_Record_Get(((arValue_Record)value), (void*)_ptr__74->data, _ptr__74->len[0])))) {
        return 0;
      }
      elem = elem->next;
    }
    return 1;
  } else {
    return 0;
  }
  __RETCHK((CHAR*)"arValue", 229134);
}

/*----------------------------------------------------------------------------*/
void arValue_Record_Set (arValue_Record self, CHAR *key, INTEGER key__len, arValue_Object value)
{
  arValue_RecordElement elem = NIL;
  elem = self->scope;
  while (elem != NIL && __arValue_String_Compare(elem->key, (void*)key, key__len) != 0) {
    elem = elem->next;
  }
  if (elem == NIL) {
    __arValue_Record_Bind(self, (void*)key, key__len, value);
  } else {
    elem->value = value;
  }
}

/*----------------------------------------------------------------------------*/
arValue_Record arValue_Record_Map (arValue_Record self, arValue_MapFunction func)
{
  arValue_Record r = NIL;
  arValue_RecordElement e = NIL;
  arValue_Object value = NIL;
  arText_String _ptr__78 = NIL;
  r = arValue_NewRecord();
  e = self->scope;
  while (e != NIL) {
    value = (*func)(e->value);
    if (value != NIL) {
      _ptr__78 = e->key->value;
      __arValue_Record_Bind(r, (void*)_ptr__78->data, _ptr__78->len[0], value);
    }
    e = e->next;
  }
  return r;
}

/*----------------------------------------------------------------------------*/
arValue_Record arValue_Record_CopyT (arValue_Record self, BOOLEAN deep)
{
  arValue_Record r = NIL;
  arValue_RecordElement e = NIL;
  arValue_Object value = NIL;
  arText_String _ptr__71 = NIL;
  r = arValue_NewRecord();
  e = self->scope;
  while (e != NIL) {
    value = e->value;
    if (deep) {
      value = arValue_DeepCopy(value);
    }
    _ptr__71 = e->key->value;
    __arValue_Record_Bind(r, (void*)_ptr__71->data, _ptr__71->len[0], value);
    e = e->next;
  }
  return r;
}

/*----------------------------------------------------------------------------*/
arValue_Object arValue_Record_Copy (arValue_Record self)
{
  return (void*)(__arValue_Record_CopyT(self, 0));
}

/*----------------------------------------------------------------------------*/
arValue_Object arValue_Record_DeepCopy (arValue_Record self)
{
  return (void*)(__arValue_Record_CopyT(self, 1));
}

/*----------------------------------------------------------------------------*/
void arValue_Record_Format (arValue_Record self, arText_Writer *w, void **w__typ)
{
  arValue_RecordElement elem = NIL;
  __arText_Stream_Char((void*)w, w__typ, '{');
  elem = self->scope;
  while (elem != NIL) {
    arValue_Format(w, w__typ, (void*)elem->key);
    __arText_Stream_Char((void*)w, w__typ, ':');
    arValue_FormatQ(w, w__typ, elem->value);
    elem = elem->next;
    if (elem != NIL) {
      __arText_Stream_Char((void*)w, w__typ, ',');
    }
  }
  __arText_Stream_Char((void*)w, w__typ, '}');
}

/*----------------------------------------------------------------------------*/
static arValue_Array arValue_NewArray (INTEGER length)
{
  arValue_Array a = NIL;
  __NEW(a, arValue_Array__rec);
  a->length = length;
  a->value = __NEWARR(POINTER__typ, 4, 4, 1, 1, (SYSTEM_ARRLEN)length);
  return a;
}

static arValue_Array arValue_Array_CopyT (arValue_Array self, BOOLEAN deep)
{
  arValue_Array a = NIL;
  INTEGER i;
  arValue_Object value = NIL;
  INTEGER _for__48;
  a = arValue_NewArray(self->length);
  _for__48 = self->length - 1;
  i = 0;
  while (i <= _for__48) {
    value = (self->value->data)[__X(i, self->value->len[0], (CHAR*)"arValue", 254488)];
    if (deep) {
      value = arValue_DeepCopy(value);
    }
    (a->value->data)[__X(i, a->value->len[0], (CHAR*)"arValue", 254997)] = value;
    i += 1;
  }
  return NIL;
}

arValue_Object arValue_Array_Copy (arValue_Array self)
{
  return (void*)(__arValue_Array_CopyT(self, 0));
}

/*----------------------------------------------------------------------------*/
arValue_Object arValue_Array_DeepCopy (arValue_Array self)
{
  return (void*)(__arValue_Array_CopyT(self, 0));
}

/*----------------------------------------------------------------------------*/
void arValue_Array_Format (arValue_Array self, arText_Writer *w, void **w__typ)
{
  INTEGER i, _for__53;
  __arText_Stream_Char((void*)w, w__typ, '[');
  _for__53 = self->length - 1;
  i = 0;
  while (i <= _for__53) {
    if (i > 0) {
      __arText_Stream_Char((void*)w, w__typ, ',');
    }
    arValue_FormatQ(w, w__typ, (self->value->data)[__X(i, self->value->len[0], (CHAR*)"arValue", 260635)]);
    i += 1;
  }
  __arText_Stream_Char((void*)w, w__typ, ']');
}

/*----------------------------------------------------------------------------*/
BOOLEAN arValue_Array_Equals (arValue_Array self, arValue_Object value)
{
  INTEGER i, _for__51;
  if (__ISP(value, arValue_Array__rec, 1)) {
    if (self->length != ((arValue_Array)value)->length) {
      return 0;
    }
    _for__51 = self->length - 1;
    i = 0;
    while (i <= _for__51) {
      if (!arValue_Equals((self->value->data)[__X(i, self->value->len[0], (CHAR*)"arValue", 263490)], (((arValue_Array)value)->value->data)[__X(i, ((arValue_Array)value)->value->len[0], (CHAR*)"arValue", 263490)])) {
        return 0;
      }
      i += 1;
    }
    return 1;
  } else {
    return 0;
  }
  __RETCHK((CHAR*)"arValue", 264703);
}

/*----------------------------------------------------------------------------*/
arValue_Object arValue_Array_Get (arValue_Array self, INTEGER index)
{
  __ASSERT(index >= 0 && index < self->length, 0, (CHAR*)"arValue", 266029);
  return (self->value->data)[__X(index, self->value->len[0], (CHAR*)"arValue", 266265)];
}

/*----------------------------------------------------------------------------*/
arValue_Object arValue_Array_Set (arValue_Array self, INTEGER index, arValue_Object value)
{
  __ASSERT(index >= 0 && index < self->length, 0, (CHAR*)"arValue", 267565);
  (self->value->data)[__X(index, self->value->len[0], (CHAR*)"arValue", 267803)] = value;
  return NIL;
}

/*----------------------------------------------------------------------------*/
arValue_List arValue_Split (CHAR *value, INTEGER value__len, CHAR separator)
{
  arValue_String s = NIL;
  s = arValue_StringFromCharArray((void*)value, value__len);
  return __arValue_String_Split(s, separator);
}

/*----------------------------------------------------------------------------*/
arValue_List arValue_list (void)
{
  return arValue_NewList();
}

/*----------------------------------------------------------------------------*/
arValue_Record arValue_record (void)
{
  return arValue_NewRecord();
}

/*----------------------------------------------------------------------------*/
arValue_Set arValue_set (SET value)
{
  return arValue_NewSet(value);
}

/*----------------------------------------------------------------------------*/
arValue_Boolean arValue_bool (BOOLEAN value)
{
  return arValue_NewBoolean(value);
}

/*----------------------------------------------------------------------------*/
arValue_Integer arValue_int (INTEGER value)
{
  return arValue_NewInteger(value);
}

/*----------------------------------------------------------------------------*/
arValue_Real arValue_real (REAL value)
{
  return arValue_NewReal(value);
}

/*----------------------------------------------------------------------------*/
arValue_Array arValue_array2 (arValue_Object a, arValue_Object b)
{
  arValue_Array result = NIL;
  result = arValue_NewArray(2);
  (result->value->data)[0] = a;
  (result->value->data)[__X(1, result->value->len[0], (CHAR*)"arValue", 280597)] = b;
  return result;
}

/*----------------------------------------------------------------------------*/
arValue_Array arValue_array3 (arValue_Object a, arValue_Object b, arValue_Object c)
{
  arValue_Array result = NIL;
  result = arValue_NewArray(3);
  (result->value->data)[0] = a;
  (result->value->data)[__X(1, result->value->len[0], (CHAR*)"arValue", 282901)] = b;
  (result->value->data)[__X(2, result->value->len[0], (CHAR*)"arValue", 283157)] = c;
  return result;
}

/*----------------------------------------------------------------------------*/
arValue_Array arValue_array4 (arValue_Object a, arValue_Object b, arValue_Object c, arValue_Object d)
{
  arValue_Array result = NIL;
  result = arValue_NewArray(3);
  (result->value->data)[0] = a;
  (result->value->data)[__X(1, result->value->len[0], (CHAR*)"arValue", 285461)] = b;
  (result->value->data)[__X(2, result->value->len[0], (CHAR*)"arValue", 285717)] = c;
  (result->value->data)[__X(3, result->value->len[0], (CHAR*)"arValue", 285973)] = d;
  return result;
}

/*----------------------------------------------------------------------------*/
arValue_String arValue_str (CHAR *value, INTEGER value__len)
{
  return arValue_StringFromCharArray((void*)value, value__len);
}

/*----------------------------------------------------------------------------*/
arValue_String arValue_strp (arText_String value)
{
  return arValue_StringFromCharPointer(value);
}

/*----------------------------------------------------------------------------*/
arValue_String arValue_strb (arText_Buffer *value, void **value__typ)
{
  return arValue_StringFromBuffer(value, value__typ);
}

/*----------------------------------------------------------------------------*/
__TDESC(arValue_ObjectDesc__desc, 7, 0) = {__TDFLDS("ObjectDesc", 1), {-4}};
__TDESC(arValue_String__rec__desc, 16, 1) = {__TDFLDS("String__rec", 8), {0, -8}};
__TDESC(arValue_Boolean__rec__desc, 8, 0) = {__TDFLDS("Boolean__rec", 1), {-4}};
__TDESC(arValue_Integer__rec__desc, 8, 0) = {__TDFLDS("Integer__rec", 4), {-4}};
__TDESC(arValue_Real__rec__desc, 8, 0) = {__TDFLDS("Real__rec", 8), {-4}};
__TDESC(arValue_Set__rec__desc, 8, 0) = {__TDFLDS("Set__rec", 4), {-4}};
__TDESC(arValue_ListElement__rec__desc, 2, 2) = {__TDFLDS("ListElement__rec", 8), {0, 4, -12}};
__TDESC(arValue_List__rec__desc, 21, 2) = {__TDFLDS("List__rec", 12), {0, 4, -12}};
__TDESC(arValue_Array__rec__desc, 10, 1) = {__TDFLDS("Array__rec", 8), {0, -8}};
__TDESC(arValue_RecordElement__rec__desc, 2, 3) = {__TDFLDS("RecordElement__rec", 12), {0, 4, 8, -16}};
__TDESC(arValue_Record__rec__desc, 12, 2) = {__TDFLDS("Record__rec", 12), {0, 8, -12}};

export void *arValue__init (void)
{
  __DEFMOD;
  __IMPORT(arStrings__init);
  __IMPORT(arText__init);
  __REGMOD("arValue", 0);
  __INITYP(arValue_ObjectDesc, arValue_ObjectDesc, 0);
  __INITBP(arValue_ObjectDesc, arValue_Object_Copy, 0);
  __INITBP(arValue_ObjectDesc, arValue_Object_DeepCopy, 1);
  __INITBP(arValue_ObjectDesc, arValue_Object_Equals, 2);
  __INITBP(arValue_ObjectDesc, arValue_Object_Format, 3);
  __INITBP(arValue_ObjectDesc, arValue_Object_ToJSON, 4);
  __INITBP(arValue_ObjectDesc, arValue_Object_ToString, 5);
  __INITYP(arValue_String__rec, arValue_ObjectDesc, 1);
  __INITBP(arValue_String__rec, arValue_String_Compare, 6);
  __INITBP(arValue_String__rec, arValue_String_Concat, 7);
  __INITBP(arValue_String__rec, arValue_String_Copy, 0);
  __INITBP(arValue_String__rec, arValue_String_CopyT, 8);
  __INITBP(arValue_String__rec, arValue_String_EndsWith, 9);
  __INITBP(arValue_String__rec, arValue_String_Equals, 2);
  __INITBP(arValue_String__rec, arValue_String_Extract, 10);
  __INITBP(arValue_String__rec, arValue_String_Format, 3);
  __INITBP(arValue_String__rec, arValue_String_Split, 11);
  __INITBP(arValue_String__rec, arValue_String_StartsWith, 12);
  __INITBP(arValue_String__rec, arValue_String_ToInteger, 13);
  __INITBP(arValue_String__rec, arValue_String_ToReal, 14);
  __INITYP(arValue_Boolean__rec, arValue_ObjectDesc, 1);
  __INITBP(arValue_Boolean__rec, arValue_Boolean_Copy, 0);
  __INITBP(arValue_Boolean__rec, arValue_Boolean_CopyT, 6);
  __INITBP(arValue_Boolean__rec, arValue_Boolean_Equals, 2);
  __INITBP(arValue_Boolean__rec, arValue_Boolean_Format, 3);
  __INITYP(arValue_Integer__rec, arValue_ObjectDesc, 1);
  __INITBP(arValue_Integer__rec, arValue_Integer_Copy, 0);
  __INITBP(arValue_Integer__rec, arValue_Integer_CopyT, 6);
  __INITBP(arValue_Integer__rec, arValue_Integer_Equals, 2);
  __INITBP(arValue_Integer__rec, arValue_Integer_Format, 3);
  __INITYP(arValue_Real__rec, arValue_ObjectDesc, 1);
  __INITBP(arValue_Real__rec, arValue_Real_Copy, 0);
  __INITBP(arValue_Real__rec, arValue_Real_CopyT, 6);
  __INITBP(arValue_Real__rec, arValue_Real_Equals, 2);
  __INITBP(arValue_Real__rec, arValue_Real_Format, 3);
  __INITYP(arValue_Set__rec, arValue_ObjectDesc, 1);
  __INITBP(arValue_Set__rec, arValue_Set_Copy, 0);
  __INITBP(arValue_Set__rec, arValue_Set_CopyT, 6);
  __INITBP(arValue_Set__rec, arValue_Set_Equals, 2);
  __INITBP(arValue_Set__rec, arValue_Set_Format, 3);
  __INITYP(arValue_ListElement__rec, arValue_ListElement__rec, 0);
  __INITYP(arValue_List__rec, arValue_ObjectDesc, 1);
  __INITBP(arValue_List__rec, arValue_List_Append, 6);
  __INITBP(arValue_List__rec, arValue_List_Concat, 7);
  __INITBP(arValue_List__rec, arValue_List_Copy, 0);
  __INITBP(arValue_List__rec, arValue_List_CopyT, 8);
  __INITBP(arValue_List__rec, arValue_List_DeepCopy, 1);
  __INITBP(arValue_List__rec, arValue_List_Equals, 2);
  __INITBP(arValue_List__rec, arValue_List_Extend, 9);
  __INITBP(arValue_List__rec, arValue_List_Format, 3);
  __INITBP(arValue_List__rec, arValue_List_Get, 10);
  __INITBP(arValue_List__rec, arValue_List_IndexOf, 11);
  __INITBP(arValue_List__rec, arValue_List_Join, 12);
  __INITBP(arValue_List__rec, arValue_List_Map, 13);
  __INITBP(arValue_List__rec, arValue_List_Prepend, 14);
  __INITBP(arValue_List__rec, arValue_List_Set, 15);
  __INITBP(arValue_List__rec, arValue_List_ToArray, 16);
  __INITBP(arValue_List__rec, arValue_List_ToIntArray, 17);
  __INITBP(arValue_List__rec, arValue_List_ToObjectArray, 18);
  __INITBP(arValue_List__rec, arValue_List_ToStringArray, 19);
  __INITYP(arValue_Array__rec, arValue_ObjectDesc, 1);
  __INITBP(arValue_Array__rec, arValue_Array_Copy, 0);
  __INITBP(arValue_Array__rec, arValue_Array_CopyT, 6);
  __INITBP(arValue_Array__rec, arValue_Array_DeepCopy, 1);
  __INITBP(arValue_Array__rec, arValue_Array_Equals, 2);
  __INITBP(arValue_Array__rec, arValue_Array_Format, 3);
  __INITBP(arValue_Array__rec, arValue_Array_Get, 7);
  __INITBP(arValue_Array__rec, arValue_Array_Set, 8);
  __INITYP(arValue_RecordElement__rec, arValue_RecordElement__rec, 0);
  __INITYP(arValue_Record__rec, arValue_ObjectDesc, 1);
  __INITBP(arValue_Record__rec, arValue_Record_Bind, 6);
  __INITBP(arValue_Record__rec, arValue_Record_Copy, 0);
  __INITBP(arValue_Record__rec, arValue_Record_CopyT, 7);
  __INITBP(arValue_Record__rec, arValue_Record_DeepCopy, 1);
  __INITBP(arValue_Record__rec, arValue_Record_Equals, 2);
  __INITBP(arValue_Record__rec, arValue_Record_Format, 3);
  __INITBP(arValue_Record__rec, arValue_Record_Get, 8);
  __INITBP(arValue_Record__rec, arValue_Record_Map, 9);
  __INITBP(arValue_Record__rec, arValue_Record_Set, 10);
/* BEGIN */
  __ENDMOD;
}
