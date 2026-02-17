/* Ofront+ 1.0 -s2 -48 */
#include "SYSTEM.oh"
#include "arStrings.oh"

typedef
  struct CHAR8_ARRAY_PTR_ARRAY *arStringList_Array;

typedef
  struct arStringList_List__rec *arStringList_List;

typedef
  struct arStringList_List__rec {
    arStrings_StringPtr name;
    arStringList_List next;
  } arStringList_List__rec;


#ifndef CHAR8_ARRAY_PTR_ARRAY_DEF
#define CHAR8_ARRAY_PTR_ARRAY_DEF
typedef struct CHAR8_ARRAY_PTR_ARRAY {
  INTEGER len[1];
  struct CHAR8_ARRAY *data[1];
} CHAR8_ARRAY_PTR_ARRAY;
#endif 


export void **arStringList_List__rec__typ;

export void arStringList_Add (arStringList_List *list, arStrings_StringPtr string);
export BOOLEAN arStringList_ArrayContains (arStringList_Array array, arStrings_StringPtr string);
export BOOLEAN arStringList_Contains (arStringList_List list, arStrings_StringPtr string);
export arStrings_StringPtr arStringList_Copy (CHAR *name, INTEGER name__len);
export void arStringList_Include (arStringList_List *list, arStrings_StringPtr string);
export void arStringList_Merge (arStringList_List src, arStringList_List *dest);
export void arStringList_Reverse (arStringList_List *list);
export arStringList_Array arStringList_ToArray (arStringList_List list);


/*============================================================================*/

arStrings_StringPtr arStringList_Copy (CHAR *name, INTEGER name__len)
{
  arStrings_StringPtr result = NIL;
  __DUP(name, name__len);
  result = __NEWARR(NIL, 1, 1, 1, 1, (SYSTEM_ARRLEN)(arStrings_Length((void*)name, name__len) + 1));
  __COPY(name, result->data, __MIN(result->len[0], name__len));
  return result;
}

/*----------------------------------------------------------------------------*/
BOOLEAN arStringList_Contains (arStringList_List list, arStrings_StringPtr string)
{
  arStrings_StringPtr _ptr__6 = NIL;
  while (list != NIL) {
    if (_ptr__6 = list->name, 
      arStrings_Equal(_ptr__6->data, _ptr__6->len[0], string->data, string->len[0])) {
      return 1;
    }
    list = list->next;
  }
  return 0;
}

/*----------------------------------------------------------------------------*/
void arStringList_Add (arStringList_List *list, arStrings_StringPtr string)
{
  arStringList_List element = NIL;
  __NEW(element, arStringList_List__rec);
  element->name = string;
  element->next = *list;
  *list = element;
}

/*----------------------------------------------------------------------------*/
void arStringList_Reverse (arStringList_List *list)
{
  arStringList_List l = NIL;
  arStringList_List this = NIL;
  l = *list;
  *list = NIL;
  while (l != NIL) {
    this = l;
    l = l->next;
    this->next = *list;
    *list = this;
  }
}

/*----------------------------------------------------------------------------*/
arStringList_Array arStringList_ToArray (arStringList_List list)
{
  arStringList_List l = NIL;
  arStringList_Array a = NIL;
  INTEGER length;
  l = list;
  length = 0;
  while (l != NIL) {
    length += 1;
    l = l->next;
  }
  a = __NEWARR(POINTER__typ, 4, 4, 1, 1, (SYSTEM_ARRLEN)length);
  l = list;
  length = 0;
  while (l != NIL) {
    (a->data)[__X(length, a->len[0], (CHAR*)"arStringList", 19477)] = l->name;
    length += 1;
    l = l->next;
  }
  return a;
}

/*----------------------------------------------------------------------------*/
void arStringList_Include (arStringList_List *list, arStrings_StringPtr string)
{
  if (!arStringList_Contains(*list, string)) {
    arStringList_Add(list, string);
  }
}

/*----------------------------------------------------------------------------*/
void arStringList_Merge (arStringList_List src, arStringList_List *dest)
{
  while (src != NIL) {
    arStringList_Include(dest, src->name);
    src = src->next;
  }
}

/*----------------------------------------------------------------------------*/
BOOLEAN arStringList_ArrayContains (arStringList_Array array, arStrings_StringPtr string)
{
  INTEGER i, _for__4;
  arStrings_StringPtr _ptr__3 = NIL;
  _for__4 = array->len[0] - 1;
  i = 0;
  while (i <= _for__4) {
    if (_ptr__3 = (array->data)[__X(i, array->len[0], (CHAR*)"arStringList", 26165)], 
      arStrings_Equal(_ptr__3->data, _ptr__3->len[0], string->data, string->len[0])) {
      return 1;
    }
    i += 1;
  }
  return 0;
}

/*----------------------------------------------------------------------------*/
__TDESC(arStringList_List__rec__desc, 2, 2) = {__TDFLDS("List__rec", 8), {0, 4, -12}};

export void *arStringList__init (void)
{
  __DEFMOD;
  __IMPORT(arStrings__init);
  __REGMOD("arStringList", 0);
  __INITYP(arStringList_List__rec, arStringList_List__rec, 0);
/* BEGIN */
  __ENDMOD;
}
