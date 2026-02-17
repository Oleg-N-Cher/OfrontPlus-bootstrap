/* Ofront+ 1.0 -sC -44 */
#include "SYSTEM.oh"

typedef
  struct ecoVector_NodeRec *ecoVector_Node;

typedef
  struct ecoVector_ObjectRec *ecoVector_OBJECT;

typedef
  struct ecoVector_NodeRec {
    ecoVector_OBJECT data;
    ecoVector_Node next;
  } ecoVector_NodeRec;

typedef
  struct ecoVector_ObjectRec {
    char _prvt0[1];
  } ecoVector_ObjectRec;

typedef
  struct ecoVector_VectorRec *ecoVector_VECTOR;

typedef
  struct ecoVector_VectorRec {
    INTEGER len;
    ecoVector_Node head, tail;
  } ecoVector_VectorRec;

export ecoVector_OBJECT ecoVector_VECTOR_At (ecoVector_VECTOR vec, INTEGER pos);
export void ecoVector_VECTOR_Clear (ecoVector_VECTOR vec);
export void ecoVector_VECTOR_Delete (ecoVector_VECTOR vec, INTEGER pos);
export ecoVector_OBJECT ecoVector_VECTOR_Head (ecoVector_VECTOR vec);
export void ecoVector_VECTOR_Insert (ecoVector_VECTOR vec, INTEGER pos, ecoVector_OBJECT e);
export INTEGER ecoVector_VECTOR_Length (ecoVector_VECTOR vec);
export ecoVector_OBJECT ecoVector_VECTOR_PopBack (ecoVector_VECTOR vec);
export void ecoVector_VECTOR_PushBack (ecoVector_VECTOR vec, ecoVector_OBJECT e);
export void ecoVector_VECTOR_Swap (ecoVector_VECTOR vec, INTEGER p1, INTEGER p2);
export ecoVector_OBJECT ecoVector_VECTOR_Tail (ecoVector_VECTOR vec);
#define __ecoVector_VECTOR_At(vec, pos) __SEND(__TYPEOF(vec), ecoVector_VECTOR_At, 0, ecoVector_OBJECT(*)(ecoVector_VECTOR, INTEGER), (vec, pos))
#define __ecoVector_VECTOR_Clear(vec) __SEND(__TYPEOF(vec), ecoVector_VECTOR_Clear, 1, void(*)(ecoVector_VECTOR), (vec))
#define __ecoVector_VECTOR_Delete(vec, pos) __SEND(__TYPEOF(vec), ecoVector_VECTOR_Delete, 2, void(*)(ecoVector_VECTOR, INTEGER), (vec, pos))
#define __ecoVector_VECTOR_Head(vec) __SEND(__TYPEOF(vec), ecoVector_VECTOR_Head, 3, ecoVector_OBJECT(*)(ecoVector_VECTOR), (vec))
#define __ecoVector_VECTOR_Insert(vec, pos, e) __SEND(__TYPEOF(vec), ecoVector_VECTOR_Insert, 4, void(*)(ecoVector_VECTOR, INTEGER, ecoVector_OBJECT), (vec, pos, e))
#define __ecoVector_VECTOR_Length(vec) __SEND(__TYPEOF(vec), ecoVector_VECTOR_Length, 5, INTEGER(*)(ecoVector_VECTOR), (vec))
#define __ecoVector_VECTOR_PopBack(vec) __SEND(__TYPEOF(vec), ecoVector_VECTOR_PopBack, 6, ecoVector_OBJECT(*)(ecoVector_VECTOR), (vec))
#define __ecoVector_VECTOR_PushBack(vec, e) __SEND(__TYPEOF(vec), ecoVector_VECTOR_PushBack, 7, void(*)(ecoVector_VECTOR, ecoVector_OBJECT), (vec, e))
#define __ecoVector_VECTOR_Swap(vec, p1, p2) __SEND(__TYPEOF(vec), ecoVector_VECTOR_Swap, 8, void(*)(ecoVector_VECTOR, INTEGER, INTEGER), (vec, p1, p2))
#define __ecoVector_VECTOR_Tail(vec) __SEND(__TYPEOF(vec), ecoVector_VECTOR_Tail, 9, ecoVector_OBJECT(*)(ecoVector_VECTOR), (vec))



export void **ecoVector_ObjectRec__typ;
export void **ecoVector_NodeRec__typ;
export void **ecoVector_VectorRec__typ;

export ecoVector_VECTOR ecoVector_Vector (void);


/*============================================================================*/

ecoVector_VECTOR ecoVector_Vector (void)
{
  ecoVector_VECTOR vec = NIL;
  __NEW(vec, ecoVector_VectorRec);
  vec->len = 0;
  vec->head = NIL;
  vec->tail = NIL;
  return vec;
}

/*----------------------------------------------------------------------------*/
INTEGER ecoVector_VECTOR_Length (ecoVector_VECTOR vec)
{
  return vec->len;
}

/*----------------------------------------------------------------------------*/
void ecoVector_VECTOR_PushBack (ecoVector_VECTOR vec, ecoVector_OBJECT e)
{
  ecoVector_Node node = NIL;
  __NEW(node, ecoVector_NodeRec);
  node->next = NIL;
  node->data = e;
  if (vec->head == NIL) {
    vec->head = node;
  } else {
    vec->tail->next = node;
  }
  vec->tail = node;
  vec->len += 1;
}

/*----------------------------------------------------------------------------*/
ecoVector_OBJECT ecoVector_VECTOR_PopBack (ecoVector_VECTOR vec)
{
  ecoVector_Node prev = NIL;
  ecoVector_Node node = NIL;
  if (vec->tail == NIL) {
    return NIL;
  } else if (vec->head == vec->tail) {
    node = vec->head;
    vec->head = NIL;
    vec->tail = NIL;
    vec->len = 0;
    return node->data;
  } else {
    prev = vec->head;
    while (prev->next != vec->tail) {
      prev = prev->next;
    }
    node = prev->next;
    prev->next = NIL;
    vec->tail = prev;
    vec->len -= 1;
    return node->data;
  }
  __RETCHK((CHAR*)"ecoVector", 18943);
}

/*----------------------------------------------------------------------------*/
ecoVector_OBJECT ecoVector_VECTOR_Head (ecoVector_VECTOR vec)
{
  if (vec->head == NIL) {
    return NIL;
  } else {
    return vec->head->data;
  }
  __RETCHK((CHAR*)"ecoVector", 21020);
}

/*----------------------------------------------------------------------------*/
ecoVector_OBJECT ecoVector_VECTOR_Tail (ecoVector_VECTOR vec)
{
  if (vec->tail == NIL) {
    return NIL;
  } else {
    return vec->tail->data;
  }
  __RETCHK((CHAR*)"ecoVector", 23324);
}

/*----------------------------------------------------------------------------*/
ecoVector_OBJECT ecoVector_VECTOR_At (ecoVector_VECTOR vec, INTEGER pos)
{
  INTEGER i;
  ecoVector_Node node = NIL;
  INTEGER _for__2;
  if (pos < 0 || pos > vec->len - 1) {
    return NIL;
  } else {
    node = vec->head;
    _for__2 = pos - 1;
    i = 0;
    while (i <= _for__2) {
      node = node->next;
      i += 1;
    }
    return node->data;
  }
  __RETCHK((CHAR*)"ecoVector", 27160);
}

/*----------------------------------------------------------------------------*/
void ecoVector_VECTOR_Delete (ecoVector_VECTOR vec, INTEGER pos)
{
  INTEGER i;
  ecoVector_Node node = NIL;
  INTEGER _for__5;
  if (pos < 0 || pos > vec->len - 1) {
  } else if (pos == 0) {
    vec->head = vec->head->next;
    vec->len -= 1;
  } else {
    node = vec->head;
    _for__5 = pos - 1;
    i = 0;
    while (i <= _for__5) {
      node = node->next;
      i += 1;
    }
    node->next = NIL;
    vec->len -= 1;
  }
}

/*----------------------------------------------------------------------------*/
void ecoVector_VECTOR_Insert (ecoVector_VECTOR vec, INTEGER pos, ecoVector_OBJECT e)
{
  INTEGER i;
  ecoVector_Node node = NIL;
  ecoVector_Node prev = NIL;
  INTEGER _for__8;
  if (pos < 0) {
    pos = 0;
  }
  if (pos > vec->len) {
    pos = vec->len;
  }
  __NEW(node, ecoVector_NodeRec);
  node->data = e;
  if (pos == 0) {
    node->next = vec->head;
    vec->head = node;
  } else if (pos == vec->len - 1) {
    node->next = NIL;
    vec->tail->next = node;
    vec->tail = node;
  } else {
    prev = vec->head;
    _for__8 = pos - 2;
    i = 0;
    while (i <= _for__8) {
      prev = prev->next;
      i += 1;
    }
    node->next = prev->next;
    prev->next = node;
  }
  vec->len += 1;
}

/*----------------------------------------------------------------------------*/
void ecoVector_VECTOR_Clear (ecoVector_VECTOR vec)
{
  vec->head = NIL;
  vec->tail = NIL;
  vec->len = 0;
}

/*----------------------------------------------------------------------------*/
void ecoVector_VECTOR_Swap (ecoVector_VECTOR vec, INTEGER p1, INTEGER p2)
{
  INTEGER i;
  ecoVector_OBJECT o1 = NIL;
  ecoVector_OBJECT o2 = NIL;
  if (((p1 < 0 || p1 > vec->len - 1) || p2 < 0) || p2 > vec->len - 1) {
  } else if (p1 == p2) {
  } else {
    if (p1 > p2) {
      i = p1;
      p1 = p2;
      p2 = i;
    }
    o1 = __ecoVector_VECTOR_At(vec, p1);
    o2 = __ecoVector_VECTOR_At(vec, p2);
    __ecoVector_VECTOR_Delete(vec, p2);
    __ecoVector_VECTOR_Delete(vec, p1);
    __ecoVector_VECTOR_Insert(vec, p1, o2);
    __ecoVector_VECTOR_Insert(vec, p2, o1);
  }
}

/*----------------------------------------------------------------------------*/
__TDESC(ecoVector_ObjectRec__desc, 1, 0) = {__TDFLDS("ObjectRec", 1), {-4}};
__TDESC(ecoVector_NodeRec__desc, 2, 2) = {__TDFLDS("NodeRec", 8), {0, 4, -12}};
__TDESC(ecoVector_VectorRec__desc, 11, 2) = {__TDFLDS("VectorRec", 12), {4, 8, -12}};

export void *ecoVector__init (void)
{
  __DEFMOD;
  __REGMOD("ecoVector", 0);
  __INITYP(ecoVector_ObjectRec, ecoVector_ObjectRec, 0);
  __INITYP(ecoVector_NodeRec, ecoVector_NodeRec, 0);
  __INITYP(ecoVector_VectorRec, ecoVector_ObjectRec, 1);
  __INITBP(ecoVector_VectorRec, ecoVector_VECTOR_At, 0);
  __INITBP(ecoVector_VectorRec, ecoVector_VECTOR_Clear, 1);
  __INITBP(ecoVector_VectorRec, ecoVector_VECTOR_Delete, 2);
  __INITBP(ecoVector_VectorRec, ecoVector_VECTOR_Head, 3);
  __INITBP(ecoVector_VectorRec, ecoVector_VECTOR_Insert, 4);
  __INITBP(ecoVector_VectorRec, ecoVector_VECTOR_Length, 5);
  __INITBP(ecoVector_VectorRec, ecoVector_VECTOR_PopBack, 6);
  __INITBP(ecoVector_VectorRec, ecoVector_VECTOR_PushBack, 7);
  __INITBP(ecoVector_VectorRec, ecoVector_VECTOR_Swap, 8);
  __INITBP(ecoVector_VectorRec, ecoVector_VECTOR_Tail, 9);
/* BEGIN */
  __ENDMOD;
}
