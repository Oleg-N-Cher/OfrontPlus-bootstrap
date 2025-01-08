/* Ofront+ 1.0 -sC -44 */
#include "SYSTEM.oh"

typedef
  struct ecoListen_ElementDesc *ecoListen_Element;

typedef
  BOOLEAN (*ecoListen_CompareProc)(ecoListen_Element, ecoListen_Element);

typedef
  struct ecoListen_ElementDesc {
    char _prvt0[1];
  } ecoListen_ElementDesc;

typedef
  struct ecoListen_ListDesc *ecoListen_Liste;

typedef
  struct ecoListen_ListDesc {
    ecoListen_Element e;
    ecoListen_Liste rest;
  } ecoListen_ListDesc;



export void **ecoListen_ElementDesc__typ;
export void **ecoListen_ListDesc__typ;

export ecoListen_Liste ecoListen_Append (ecoListen_Liste list, ecoListen_Element e);
export ecoListen_Liste ecoListen_Concat (ecoListen_Element head, ecoListen_Liste tail);
export ecoListen_Element ecoListen_Find (ecoListen_Element e, ecoListen_Liste l, ecoListen_CompareProc equal);
export ecoListen_Element ecoListen_Head (ecoListen_Liste l);
export BOOLEAN ecoListen_IsElement (ecoListen_Element e, ecoListen_Liste l, ecoListen_CompareProc equal);
export ecoListen_Liste ecoListen_Tail (ecoListen_Liste l);


/*============================================================================*/

ecoListen_Liste ecoListen_Concat (ecoListen_Element head, ecoListen_Liste tail)
{
  ecoListen_Liste temp = NIL;
  __NEW(temp, ecoListen_ListDesc);
  temp->e = head;
  temp->rest = tail;
  return temp;
}

/*----------------------------------------------------------------------------*/
ecoListen_Element ecoListen_Head (ecoListen_Liste l)
{
  return l->e;
}

/*----------------------------------------------------------------------------*/
ecoListen_Liste ecoListen_Tail (ecoListen_Liste l)
{
  return l->rest;
}

/*----------------------------------------------------------------------------*/
ecoListen_Liste ecoListen_Append (ecoListen_Liste list, ecoListen_Element e)
{
  if (list == NIL) {
    return ecoListen_Concat(e, NIL);
  } else {
    return ecoListen_Concat(ecoListen_Head(list), ecoListen_Append(ecoListen_Tail(list), e));
  }
  __RETCHK((CHAR*)"ecoListen", 10239);
}

/*----------------------------------------------------------------------------*/
BOOLEAN ecoListen_IsElement (ecoListen_Element e, ecoListen_Liste l, ecoListen_CompareProc equal)
{
  if (l == NIL) {
    return 0;
  } else if ((*equal)(e, ecoListen_Head(l))) {
    return 1;
  } else {
    return ecoListen_IsElement(e, ecoListen_Tail(l), equal);
  }
  __RETCHK((CHAR*)"ecoListen", 12543);
}

/*----------------------------------------------------------------------------*/
ecoListen_Element ecoListen_Find (ecoListen_Element e, ecoListen_Liste l, ecoListen_CompareProc equal)
{
  if (l == NIL) {
    return NIL;
  } else if ((*equal)(e, ecoListen_Head(l))) {
    return ecoListen_Head(l);
  } else {
    return ecoListen_Find(e, ecoListen_Tail(l), equal);
  }
  __RETCHK((CHAR*)"ecoListen", 14591);
}

/*----------------------------------------------------------------------------*/
__TDESC(ecoListen_ElementDesc__desc, 1, 0) = {__TDFLDS("ElementDesc", 1), {-4}};
__TDESC(ecoListen_ListDesc__desc, 2, 2) = {__TDFLDS("ListDesc", 8), {0, 4, -12}};

export void *ecoListen__init (void)
{
  __DEFMOD;
  __REGMOD("ecoListen", 0);
  __INITYP(ecoListen_ElementDesc, ecoListen_ElementDesc, 0);
  __INITYP(ecoListen_ListDesc, ecoListen_ListDesc, 0);
/* BEGIN */
  __ENDMOD;
}
