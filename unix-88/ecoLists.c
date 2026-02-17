/* Ofront+ 1.0 -sC -88 */
#include "SYSTEM.oh"

typedef
  struct ecoLists_Node *ecoLists_NodePtr;

typedef
  void (*ecoLists_DoProc)(ecoLists_NodePtr);

typedef
  struct ecoLists_List {
    ecoLists_NodePtr head, tail;
    SHORTINT remallowed;
  } ecoLists_List;

typedef
  struct ecoLists_Node {
    ecoLists_NodePtr next, prev;
  } ecoLists_Node;



export void **ecoLists_Node__typ;
export void **ecoLists_List__typ;

export void ecoLists_AddBefore (ecoLists_List *list, void **list__typ, ecoLists_NodePtr n, ecoLists_NodePtr x);
export void ecoLists_AddBehind (ecoLists_List *list, void **list__typ, ecoLists_NodePtr n, ecoLists_NodePtr x);
export void ecoLists_AddHead (ecoLists_List *list, void **list__typ, ecoLists_NodePtr n);
export void ecoLists_AddMarkBefore (ecoLists_List *list, void **list__typ, ecoLists_List mark, ecoLists_NodePtr x);
export void ecoLists_AddMarkBehind (ecoLists_List *list, void **list__typ, ecoLists_List mark, ecoLists_NodePtr x);
export void ecoLists_AddMarkHead (ecoLists_List *list, void **list__typ, ecoLists_List mark);
export void ecoLists_AddMarkTail (ecoLists_List *list, void **list__typ, ecoLists_List mark);
export void ecoLists_AddTail (ecoLists_List *list, void **list__typ, ecoLists_NodePtr n);
export INTEGER ecoLists_CountElements (ecoLists_List *list, void **list__typ);
export void ecoLists_DoBackward (ecoLists_List *list, void **list__typ, ecoLists_DoProc proc);
export void ecoLists_DoForward (ecoLists_List *list, void **list__typ, ecoLists_DoProc proc);
export BOOLEAN ecoLists_Empty (ecoLists_List *list, void **list__typ);
export ecoLists_NodePtr ecoLists_GetPred (ecoLists_NodePtr n);
export ecoLists_NodePtr ecoLists_GetSucc (ecoLists_NodePtr n);
export void ecoLists_GoBackward (ecoLists_List list, ecoLists_NodePtr *n, INTEGER num);
export void ecoLists_GoForward (ecoLists_List list, ecoLists_NodePtr *n, INTEGER num);
export ecoLists_NodePtr ecoLists_Head (ecoLists_List *list, void **list__typ);
export void ecoLists_Init (ecoLists_List *list, void **list__typ);
export BOOLEAN ecoLists_IsElement (ecoLists_List *list, void **list__typ, ecoLists_NodePtr e);
export BOOLEAN ecoLists_Next (ecoLists_NodePtr *n);
export void ecoLists_Pred (ecoLists_NodePtr *n);
export BOOLEAN ecoLists_Previous (ecoLists_NodePtr *n);
export ecoLists_NodePtr ecoLists_RemHead (ecoLists_List *list, void **list__typ);
export ecoLists_NodePtr ecoLists_RemTail (ecoLists_List *list, void **list__typ);
export void ecoLists_Remove (ecoLists_List *list, void **list__typ, ecoLists_NodePtr n);
export void ecoLists_RemoveMark (ecoLists_List *list, void **list__typ, ecoLists_List mark);
export void ecoLists_SetMark (ecoLists_List *mark, void **mark__typ, ecoLists_NodePtr h, ecoLists_NodePtr t);
export void ecoLists_Succ (ecoLists_NodePtr *n);
export void ecoLists_Swap (ecoLists_List *list, void **list__typ, ecoLists_NodePtr a, ecoLists_NodePtr b);
export ecoLists_NodePtr ecoLists_Tail (ecoLists_List *list, void **list__typ);


/*============================================================================*/

void ecoLists_Init (ecoLists_List *list, void **list__typ)
{
  (*list).head = NIL;
  (*list).tail = NIL;
  (*list).remallowed = 0;
}

/*----------------------------------------------------------------------------*/
void ecoLists_AddHead (ecoLists_List *list, void **list__typ, ecoLists_NodePtr n)
{
  n->next = (*list).head;
  n->prev = NIL;
  if (n->next == NIL) {
    (*list).tail = n;
  } else {
    n->next->prev = n;
  }
  (*list).head = n;
}

/*----------------------------------------------------------------------------*/
void ecoLists_AddTail (ecoLists_List *list, void **list__typ, ecoLists_NodePtr n)
{
  n->prev = (*list).tail;
  n->next = NIL;
  if (n->prev == NIL) {
    (*list).head = n;
  } else {
    n->prev->next = n;
  }
  (*list).tail = n;
}

/*----------------------------------------------------------------------------*/
void ecoLists_AddBefore (ecoLists_List *list, void **list__typ, ecoLists_NodePtr n, ecoLists_NodePtr x)
{
  n->prev = x->prev;
  n->next = x;
  x->prev = n;
  if (n->prev == NIL) {
    (*list).head = n;
  } else {
    n->prev->next = n;
  }
}

/*----------------------------------------------------------------------------*/
void ecoLists_AddBehind (ecoLists_List *list, void **list__typ, ecoLists_NodePtr n, ecoLists_NodePtr x)
{
  n->next = x->next;
  n->prev = x;
  x->next = n;
  if (n->next == NIL) {
    (*list).tail = n;
  } else {
    n->next->prev = n;
  }
}

/*----------------------------------------------------------------------------*/
void ecoLists_Remove (ecoLists_List *list, void **list__typ, ecoLists_NodePtr n)
{
  if (n != NIL) {
    if ((INTEGER)(*list).remallowed != 0) {
      __HALT(20, (CHAR*)"ecoLists", 24872);
    }
    if (n->next != NIL) {
      n->next->prev = n->prev;
    } else {
      (*list).tail = n->prev;
    }
    if (n->prev != NIL) {
      n->prev->next = n->next;
    } else {
      (*list).head = n->next;
    }
  }
}

/*----------------------------------------------------------------------------*/
ecoLists_NodePtr ecoLists_RemHead (ecoLists_List *list, void **list__typ)
{
  ecoLists_NodePtr n = NIL;
  n = (*list).head;
  ecoLists_Remove(list, list__typ, n);
  return n;
}

/*----------------------------------------------------------------------------*/
ecoLists_NodePtr ecoLists_RemTail (ecoLists_List *list, void **list__typ)
{
  ecoLists_NodePtr n = NIL;
  n = (*list).tail;
  ecoLists_Remove(list, list__typ, n);
  return n;
}

/*----------------------------------------------------------------------------*/
void ecoLists_DoForward (ecoLists_List *list, void **list__typ, ecoLists_DoProc proc)
{
  ecoLists_NodePtr n = NIL;
  (*list).remallowed += 1;
  n = (*list).head;
  while (n != NIL) {
    (*proc)(n);
    n = n->next;
  }
  (*list).remallowed -= 1;
}

/*----------------------------------------------------------------------------*/
void ecoLists_DoBackward (ecoLists_List *list, void **list__typ, ecoLists_DoProc proc)
{
  ecoLists_NodePtr n = NIL;
  (*list).remallowed += 1;
  n = (*list).tail;
  while (n != NIL) {
    (*proc)(n);
    n = n->prev;
  }
  (*list).remallowed -= 1;
}

/*----------------------------------------------------------------------------*/
BOOLEAN ecoLists_Next (ecoLists_NodePtr *n)
{
  *n = (*n)->next;
  return *n != NIL;
}

/*----------------------------------------------------------------------------*/
BOOLEAN ecoLists_Previous (ecoLists_NodePtr *n)
{
  *n = (*n)->prev;
  return *n != NIL;
}

/*----------------------------------------------------------------------------*/
void ecoLists_Succ (ecoLists_NodePtr *n)
{
  *n = (*n)->next;
}

/*----------------------------------------------------------------------------*/
void ecoLists_Pred (ecoLists_NodePtr *n)
{
  *n = (*n)->prev;
}

/*----------------------------------------------------------------------------*/
ecoLists_NodePtr ecoLists_GetSucc (ecoLists_NodePtr n)
{
  return n->next;
}

/*----------------------------------------------------------------------------*/
ecoLists_NodePtr ecoLists_GetPred (ecoLists_NodePtr n)
{
  return n->prev;
}

/*----------------------------------------------------------------------------*/
ecoLists_NodePtr ecoLists_Head (ecoLists_List *list, void **list__typ)
{
  return (*list).head;
}

/*----------------------------------------------------------------------------*/
ecoLists_NodePtr ecoLists_Tail (ecoLists_List *list, void **list__typ)
{
  return (*list).tail;
}

/*----------------------------------------------------------------------------*/
void ecoLists_GoForward (ecoLists_List list, ecoLists_NodePtr *n, INTEGER num)
{
  while (num > 0 && *n != NIL) {
    *n = (*n)->next;
    num -= 1;
  }
  if (*n == NIL) {
    *n = list.tail;
  }
}

/*----------------------------------------------------------------------------*/
void ecoLists_GoBackward (ecoLists_List list, ecoLists_NodePtr *n, INTEGER num)
{
  while (num > 0 && *n != NIL) {
    *n = (*n)->prev;
    num -= 1;
  }
  if (*n == NIL) {
    *n = list.head;
  }
}

/*----------------------------------------------------------------------------*/
BOOLEAN ecoLists_Empty (ecoLists_List *list, void **list__typ)
{
  return (*list).head == NIL;
}

/*----------------------------------------------------------------------------*/
BOOLEAN ecoLists_IsElement (ecoLists_List *list, void **list__typ, ecoLists_NodePtr e)
{
  ecoLists_NodePtr n = NIL;
  n = (*list).head;
  while (n != NIL) {
    if (n == e) {
      return 1;
    }
    n = n->next;
  }
  return 0;
}

/*----------------------------------------------------------------------------*/
INTEGER ecoLists_CountElements (ecoLists_List *list, void **list__typ)
{
  INTEGER i;
  ecoLists_NodePtr n = NIL;
  i = 0;
  n = (*list).head;
  while (n != NIL) {
    n = n->next;
    i += 1;
  }
  return i;
}

/*----------------------------------------------------------------------------*/
void ecoLists_Swap (ecoLists_List *list, void **list__typ, ecoLists_NodePtr a, ecoLists_NodePtr b)
{
  ecoLists_NodePtr c = NIL;
  c = a->next;
  if (b->next != a) {
    ecoLists_Remove(list, list__typ, a);
    ecoLists_AddBehind(list, list__typ, a, b);
  }
  if (c != b) {
    ecoLists_Remove(list, list__typ, b);
    if (c == NIL) {
      ecoLists_AddTail(list, list__typ, b);
    } else {
      ecoLists_AddBefore(list, list__typ, b, c);
    }
  }
}

/*----------------------------------------------------------------------------*/
void ecoLists_AddMarkBefore (ecoLists_List *list, void **list__typ, ecoLists_List mark, ecoLists_NodePtr x)
{
  mark.head->prev = x->prev;
  mark.tail->next = x;
  x->prev = mark.tail;
  if (mark.head->prev == NIL) {
    (*list).head = mark.head;
  } else {
    mark.head->prev->next = mark.head;
  }
  mark.remallowed += 1;
}

/*----------------------------------------------------------------------------*/
void ecoLists_AddMarkBehind (ecoLists_List *list, void **list__typ, ecoLists_List mark, ecoLists_NodePtr x)
{
  mark.tail->next = x->next;
  mark.head->prev = x;
  x->next = mark.head;
  if (mark.tail->next == NIL) {
    (*list).tail = mark.tail;
  } else {
    mark.tail->next->prev = mark.tail;
  }
  mark.remallowed += 1;
}

/*----------------------------------------------------------------------------*/
void ecoLists_AddMarkHead (ecoLists_List *list, void **list__typ, ecoLists_List mark)
{
  mark.tail->next = (*list).head;
  mark.head->prev = NIL;
  if (mark.tail->next == NIL) {
    (*list).tail = mark.tail;
  } else {
    mark.tail->next->prev = mark.tail;
  }
  (*list).head = mark.head;
  mark.remallowed += 1;
}

/*----------------------------------------------------------------------------*/
void ecoLists_AddMarkTail (ecoLists_List *list, void **list__typ, ecoLists_List mark)
{
  mark.head->prev = (*list).tail;
  mark.tail->next = NIL;
  if (mark.head->prev == NIL) {
    (*list).head = mark.head;
  } else {
    mark.head->prev->next = mark.head;
  }
  (*list).tail = mark.tail;
  mark.remallowed += 1;
}

/*----------------------------------------------------------------------------*/
void ecoLists_RemoveMark (ecoLists_List *list, void **list__typ, ecoLists_List mark)
{
  if (mark.head != NIL && mark.tail != NIL) {
    if ((INTEGER)(*list).remallowed != 0) {
      __HALT(20, (CHAR*)"ecoLists", 80168);
    }
    if (mark.tail->next != NIL) {
      mark.tail->next->prev = mark.head->prev;
    } else {
      (*list).tail = mark.head->prev;
    }
    if (mark.head->prev != NIL) {
      mark.head->prev->next = mark.tail->next;
    } else {
      (*list).head = mark.tail->next;
    }
  }
  mark.remallowed -= 1;
}

/*----------------------------------------------------------------------------*/
void ecoLists_SetMark (ecoLists_List *mark, void **mark__typ, ecoLists_NodePtr h, ecoLists_NodePtr t)
{
  if (h == NIL && t == NIL) {
    (*mark).head = NIL;
    (*mark).tail = NIL;
  } else {
    if (h != NIL) {
      (*mark).head = h;
    }
    if (t != NIL) {
      (*mark).tail = t;
    }
  }
  if ((INTEGER)(*mark).remallowed == 0) {
    (*mark).remallowed = 1;
  }
}

/*----------------------------------------------------------------------------*/
__TDESC(ecoLists_Node__desc, 2, 2) = {__TDFLDS("Node", 16), {0, 8, -24}};
__TDESC(ecoLists_List__desc, 1, 2) = {__TDFLDS("List", 24), {0, 8, -24}};

export void *ecoLists__init (void)
{
  __DEFMOD;
  __REGMOD("ecoLists", 0);
  __INITYP(ecoLists_Node, ecoLists_Node, 0);
  __INITYP(ecoLists_List, ecoLists_List, 0);
/* BEGIN */
  __ENDMOD;
}
