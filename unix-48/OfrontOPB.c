/* Ofront+ 1.0 -sC -48 */
#include "SYSTEM.oh"
#include "OfrontOPT.oh"
#include "OfrontOPS.oh"
#include "OfrontOPM.oh"


#ifndef CHAR16_ARRAY_DEF
#define CHAR16_ARRAY_DEF
typedef struct CHAR16_ARRAY {
  INTEGER len[1];
  LONGCHAR data[1];
} CHAR16_ARRAY;
#endif 

export void (*OfrontOPB_typSize)(OfrontOPT_Struct);
static SHORTINT OfrontOPB_exp;


export void OfrontOPB_Assign (OfrontOPT_Node *x, OfrontOPT_Node y);
static void OfrontOPB_AssignString (OfrontOPT_Node *x, OfrontOPT_Node str);
static void OfrontOPB_BindNodes (BYTE class, OfrontOPT_Struct typ, OfrontOPT_Node *x, OfrontOPT_Node y);
static INTEGER OfrontOPB_BoolToInt (BOOLEAN b);
export void OfrontOPB_Call (OfrontOPT_Node *x, OfrontOPT_Node apar, OfrontOPT_Object fp);
static void OfrontOPB_CharToString16 (OfrontOPT_Node n);
static void OfrontOPB_CharToString8 (OfrontOPT_Node n);
export void OfrontOPB_CheckAssign (OfrontOPT_Struct x, OfrontOPT_Node *ynode);
export void OfrontOPB_CheckBuffering (OfrontOPT_Node *n, OfrontOPT_Node left, OfrontOPT_Object par, OfrontOPT_Node *stat, OfrontOPT_Node *last);
static void OfrontOPB_CheckLeaf (OfrontOPT_Node x, BOOLEAN dynArrToo);
export void OfrontOPB_CheckParameters (OfrontOPT_Object fp, OfrontOPT_Object ap, BOOLEAN checkNames);
static void OfrontOPB_CheckProc (OfrontOPT_Struct x, OfrontOPT_Object y);
static void OfrontOPB_CheckPtr (OfrontOPT_Node x, OfrontOPT_Node y);
static void OfrontOPB_CheckRealType (INTEGER f, SHORTINT nr, OfrontOPT_Const x);
static void OfrontOPB_CheckReceiver (OfrontOPT_Node *x, OfrontOPT_Object fp);
static void OfrontOPB_CheckString (OfrontOPT_Node n, OfrontOPT_Struct typ, SHORTINT e);
export void OfrontOPB_CheckVarParBuffering (OfrontOPT_Node *n, OfrontOPT_Node *stat, OfrontOPT_Node *last);
static void OfrontOPB_ConstOp (SHORTINT op, OfrontOPT_Node x, OfrontOPT_Node y);
export void OfrontOPB_Construct (BYTE class, OfrontOPT_Node *x, OfrontOPT_Node y);
static void OfrontOPB_Convert (OfrontOPT_Node *x, OfrontOPT_Struct typ);
export void OfrontOPB_DeRef (OfrontOPT_Node *x);
static void OfrontOPB_DynArrParCheck (OfrontOPT_Struct ftyp, OfrontOPT_Node *ap, BOOLEAN fvarpar);
export OfrontOPT_Node OfrontOPB_EmptySet (void);
export void OfrontOPB_Enter (OfrontOPT_Node *procdec, OfrontOPT_Node stat, OfrontOPT_Object proc);
export void OfrontOPB_Field (OfrontOPT_Node *x, OfrontOPT_Object y);
static void OfrontOPB_GetMaxLength (OfrontOPT_Node n, OfrontOPT_Node *stat, OfrontOPT_Node *last, OfrontOPT_Node *length);
static void OfrontOPB_GetRealConstType (INTEGER f, SHORTINT nr, OfrontOPT_Const x, OfrontOPT_Struct *typ);
static void OfrontOPB_GetStaticLength (OfrontOPT_Node n, INTEGER *length);
export void OfrontOPB_GetTempVar (CHAR *name, INTEGER name__len, OfrontOPT_Struct typ, OfrontOPT_Object *obj);
export void OfrontOPB_In (OfrontOPT_Node *x, OfrontOPT_Node y);
export void OfrontOPB_Index (OfrontOPT_Node *x, OfrontOPT_Node y);
export void OfrontOPB_Inittd (OfrontOPT_Node *inittd, OfrontOPT_Node *last, OfrontOPT_Struct typ);
static BOOLEAN OfrontOPB_IntToBool (LONGINT i);
static SET OfrontOPB_IntToSet (INTEGER x);
export void OfrontOPB_Link (OfrontOPT_Node *x, OfrontOPT_Node *last, OfrontOPT_Node y);
export void OfrontOPB_MOp (BYTE op, OfrontOPT_Node *x);
export LONGINT OfrontOPB_Max (BYTE form);
export LONGINT OfrontOPB_Min (BYTE form);
export void OfrontOPB_NewArrConst (OfrontOPT_Node *x);
export OfrontOPT_Node OfrontOPB_NewBoolConst (BOOLEAN boolval);
export OfrontOPT_Node OfrontOPB_NewIntConst (LONGINT intval);
export OfrontOPT_Node OfrontOPB_NewLeaf (OfrontOPT_Object obj);
export OfrontOPT_Node OfrontOPB_NewRealConst (REAL realval, OfrontOPT_Struct typ);
export OfrontOPT_Node OfrontOPB_NewShortConst (LONGINT uintval, INTEGER size);
export OfrontOPT_Node OfrontOPB_NewString (OfrontOPS_String str, struct CHAR16_ARRAY *lstr, INTEGER len);
export OfrontOPT_Node OfrontOPB_Nil (void);
static BOOLEAN OfrontOPB_NotVar (OfrontOPT_Node x);
export void OfrontOPB_Op (BYTE op, OfrontOPT_Node *x, OfrontOPT_Node y);
export void OfrontOPB_OptIf (OfrontOPT_Node *x);
static BOOLEAN OfrontOPB_Overlap (OfrontOPT_Node left, OfrontOPT_Node right);
export void OfrontOPB_Param (OfrontOPT_Node *ap, OfrontOPT_Object fp);
export void OfrontOPB_PrepCall (OfrontOPT_Node *x, OfrontOPT_Object *fpar);
static void OfrontOPB_Promote (OfrontOPT_Node *left, OfrontOPT_Node *right, INTEGER op);
static void OfrontOPB_PromoteByte (OfrontOPT_Node *left, OfrontOPT_Node *right);
export void OfrontOPB_Return (OfrontOPT_Node *x, OfrontOPT_Object proc);
export void OfrontOPB_SetElem (OfrontOPT_Node *x);
static void OfrontOPB_SetIntType (OfrontOPT_Node node, BOOLEAN raw);
export void OfrontOPB_SetRange (OfrontOPT_Node *x, OfrontOPT_Node y);
static INTEGER OfrontOPB_SetToInt (SET s);
export LONGINT OfrontOPB_Short2Size (LONGINT n, BYTE form);
export void OfrontOPB_StFct (OfrontOPT_Node *par0, BYTE fctno, SHORTINT parno);
export void OfrontOPB_StPar0 (OfrontOPT_Node *par0, SHORTINT fctno);
export void OfrontOPB_StPar1 (OfrontOPT_Node *par0, OfrontOPT_Node x, BYTE fctno);
export void OfrontOPB_StParN (OfrontOPT_Node *par0, OfrontOPT_Node x, SHORTINT fctno, SHORTINT n);
export void OfrontOPB_StaticLink (BYTE dlev);
export void OfrontOPB_StrDeref (OfrontOPT_Node *x);
static void OfrontOPB_String16ToString8 (OfrontOPT_Node n);
static void OfrontOPB_String8ToString16 (OfrontOPT_Node n);
export void OfrontOPB_TypTest (OfrontOPT_Node *x, OfrontOPT_Object obj, BOOLEAN guard);
static void OfrontOPB_err (SHORTINT n);
static LONGINT OfrontOPB_log (LONGINT x);


/*============================================================================*/

static void OfrontOPB_err (SHORTINT n)
{
  OfrontOPM_err(n);
}

OfrontOPT_Node OfrontOPB_NewLeaf (OfrontOPT_Object obj)
{
  OfrontOPT_Node node = NIL;
  switch (obj->mode) {
    case 1: 
      node = OfrontOPT_NewNode(0);
      node->readonly = (INTEGER)obj->vis == 2 && (INTEGER)obj->mnolev < 0;
      break;
    case 2: 
      node = OfrontOPT_NewNode(1);
      node->readonly = (INTEGER)obj->vis == 3 || (INTEGER)obj->vis == 2;
      break;
    case 3: 
      node = OfrontOPT_NewNode(7);
      node->conval = OfrontOPT_NewConst();
      __GUARDEQP(node->conval, OfrontOPT_ConstDesc) = *obj->conval;
      break;
    case 5: 
      node = OfrontOPT_NewNode(8);
      break;
    case 6: case 7: case 8: case 9: case 10: 
      node = OfrontOPT_NewNode(9);
      break;
    default: 
      OfrontOPB_err(127);
      node = OfrontOPT_NewNode(0);
      break;
  }
  node->obj = obj;
  node->typ = obj->typ;
  return node;
}

/*----------------------------------------------------------------------------*/
void OfrontOPB_Construct (BYTE class, OfrontOPT_Node *x, OfrontOPT_Node y)
{
  OfrontOPT_Node node = NIL;
  node = OfrontOPT_NewNode(class);
  node->typ = OfrontOPT_notyp;
  node->left = *x;
  node->right = y;
  *x = node;
}

/*----------------------------------------------------------------------------*/
void OfrontOPB_Link (OfrontOPT_Node *x, OfrontOPT_Node *last, OfrontOPT_Node y)
{
  if (*x == NIL) {
    *x = y;
  } else {
    (*last)->link = y;
  }
  while (y->link != NIL) {
    y = y->link;
  }
  *last = y;
}

/*----------------------------------------------------------------------------*/
static INTEGER OfrontOPB_BoolToInt (BOOLEAN b)
{
  if (b) {
    return 1;
  } else {
    return 0;
  }
  __RETCHK((CHAR*)"OfrontOPB", 30498);
}

static BOOLEAN OfrontOPB_IntToBool (LONGINT i)
{
  return i != 0;
}

static INTEGER OfrontOPB_SetToInt (SET s)
{
  INTEGER x, i;
  i = 31;
  x = 0;
  if (__IN(31, s)) {
    x = -1;
  }
  while (i > 0) {
    x = __ASHL(x, 1, INTEGER);
    i -= 1;
    if (__IN(i, s)) {
      x += 1;
    }
  }
  return x;
}

static SET OfrontOPB_IntToSet (INTEGER x)
{
  INTEGER i;
  SET s;
  i = 0;
  s = 0x0;
  while (i < 32) {
    if (__ODD(x)) {
      s |= __SETOF(i);
    }
    x = __ASHR(x, 1, INTEGER);
    i += 1;
  }
  return s;
}

OfrontOPT_Node OfrontOPB_NewBoolConst (BOOLEAN boolval)
{
  OfrontOPT_Node x = NIL;
  x = OfrontOPT_NewNode(7);
  x->typ = OfrontOPT_booltyp;
  x->conval = OfrontOPT_NewConst();
  x->conval->intval = OfrontOPB_BoolToInt(boolval);
  return x;
}

/*----------------------------------------------------------------------------*/
void OfrontOPB_OptIf (OfrontOPT_Node *x)
{
  OfrontOPT_Node if_ = NIL;
  OfrontOPT_Node pred = NIL;
  if_ = (*x)->left;
  while ((INTEGER)if_->left->class == 7) {
    if (OfrontOPB_IntToBool(if_->left->conval->intval)) {
      *x = if_->right;
      return;
    } else if (if_->link == NIL) {
      *x = (*x)->right;
      return;
    } else {
      if_ = if_->link;
      (*x)->left = if_;
    }
  }
  pred = if_;
  if_ = if_->link;
  while (if_ != NIL) {
    if ((INTEGER)if_->left->class == 7) {
      if (OfrontOPB_IntToBool(if_->left->conval->intval)) {
        pred->link = NIL;
        (*x)->right = if_->right;
        return;
      } else {
        if_ = if_->link;
        pred->link = if_;
      }
    } else {
      pred = if_;
      if_ = if_->link;
    }
  }
}

/*----------------------------------------------------------------------------*/
OfrontOPT_Node OfrontOPB_Nil (void)
{
  OfrontOPT_Node x = NIL;
  x = OfrontOPT_NewNode(7);
  x->typ = OfrontOPT_niltyp;
  x->conval = OfrontOPT_NewConst();
  x->conval->intval = 0;
  return x;
}

/*----------------------------------------------------------------------------*/
OfrontOPT_Node OfrontOPB_EmptySet (void)
{
  OfrontOPT_Node x = NIL;
  x = OfrontOPT_NewNode(7);
  x->typ = OfrontOPT_settyp;
  x->conval = OfrontOPT_NewConst();
  x->conval->setval = 0x0;
  return x;
}

/*----------------------------------------------------------------------------*/
void OfrontOPB_GetTempVar (CHAR *name, INTEGER name__len, OfrontOPT_Struct typ, OfrontOPT_Object *obj)
{
  OfrontOPS_Name n;
  OfrontOPT_Object o = NIL;
  __MOVE((CHAR*)"@@  ", n, 5);
  OfrontOPT_Insert((void*)n, 48, obj);
  __STRCOPYCC(name, (*obj)->name->data, __MIN((*obj)->name->len[0], name__len), (CHAR*)"OfrontOPB", 50229);
  (*obj)->mode = 1;
  (*obj)->typ = typ;
  o = OfrontOPT_topScope->scope;
  if (o == NIL) {
    OfrontOPT_topScope->scope = *obj;
  } else {
    while (o->link != NIL) {
      o = o->link;
    }
    o->link = *obj;
  }
}

/*----------------------------------------------------------------------------*/
static void OfrontOPB_SetIntType (OfrontOPT_Node node, BOOLEAN raw)
{
  LONGINT v;
  v = node->conval->intval;
  if (!raw) {
    raw = OfrontOPM_Lang != 'C' && OfrontOPM_Lang != '7';
  }
  if ((raw && -128 <= v) && v <= 127) {
    node->typ = OfrontOPT_bytetyp;
  } else if (((raw || (INTEGER)OfrontOPM_AdrSize == 2) && -32768 <= v) && v <= 32767) {
    node->typ = OfrontOPT_sinttyp;
  } else if ((-2147483647-1) <= v && v <= 2147483647) {
    node->typ = OfrontOPT_inttyp;
  } else {
    node->typ = OfrontOPT_linttyp;
  }
}

OfrontOPT_Node OfrontOPB_NewIntConst (LONGINT intval)
{
  OfrontOPT_Node x = NIL;
  x = OfrontOPT_NewNode(7);
  x->conval = OfrontOPT_NewConst();
  x->conval->intval = intval;
  OfrontOPB_SetIntType(x, 0);
  return x;
}

/*----------------------------------------------------------------------------*/
void OfrontOPB_NewArrConst (OfrontOPT_Node *x)
{
  INTEGER n;
  OfrontOPT_Struct typ = NIL;
  OfrontOPT_ConstArr y = NIL;
  OfrontOPT_Object fp = NIL;
  n = 1;
  typ = (*x)->typ;
  while ((INTEGER)typ->form == 16 && (INTEGER)typ->comp == 2) {
    n = n * typ->n;
    typ = typ->BaseTyp;
  }
  if (__IN(typ->form, 0x407e)) {
    fp = OfrontOPT_NewObj();
    fp->typ = (*x)->obj->typ->BaseTyp;
    fp->mode = 1;
    __NEW(y, OfrontOPT_ConstArr__rec);
    switch (typ->size) {
      case 1: 
        y->val1 = __NEWARR(NIL, 1, 1, 1, 1, (SYSTEM_ARRLEN)n);
        break;
      case 2: 
        y->val2 = __NEWARR(NIL, 2, 2, 1, 1, (SYSTEM_ARRLEN)n);
        break;
      case 4: 
        y->val4 = __NEWARR(NIL, 4, 4, 1, 1, (SYSTEM_ARRLEN)n);
        break;
      case 8: 
        y->val8 = __NEWARR(NIL, 8, 8, 1, 1, (SYSTEM_ARRLEN)n);
        break;
      default: __CASECHK((CHAR*)"OfrontOPB", 63999);
    }
    fp = (*x)->obj;
    *x = OfrontOPB_Nil();
    (*x)->typ = OfrontOPT_undftyp;
    (*x)->conval->intval = 0;
    (*x)->conval->intval2 = n;
    (*x)->conval->arr = y;
    (*x)->obj = fp;
  } else {
    OfrontOPB_err(51);
  }
}

/*----------------------------------------------------------------------------*/
LONGINT OfrontOPB_Min (BYTE form)
{
  LONGINT min;
  switch (form) {
    case 14: 
      min = 0;
      break;
    case 1: 
      min = -128;
      break;
    case 4: 
      min = -32768;
      break;
    case 5: 
      min = (-2147483647-1);
      break;
    case 6: 
      min = (-9223372036854775807LL-1);
      break;
    default: __CASECHK((CHAR*)"OfrontOPB", 69375);
  }
  return min;
}

/*----------------------------------------------------------------------------*/
LONGINT OfrontOPB_Max (BYTE form)
{
  LONGINT max;
  switch (form) {
    case 14: 
      max = 255;
      break;
    case 1: 
      max = 127;
      break;
    case 4: 
      max = 32767;
      break;
    case 5: 
      max = 2147483647;
      break;
    case 6: 
      max = 9223372036854775807LL;
      break;
    default: __CASECHK((CHAR*)"OfrontOPB", 72703);
  }
  return max;
}

/*----------------------------------------------------------------------------*/
LONGINT OfrontOPB_Short2Size (LONGINT n, BYTE form)
{
  switch (form) {
    case 14: 
      n = __MASK(n, -256);
      break;
    case 1: 
      n = (BYTE)n;
      break;
    case 4: 
      n = (SHORTINT)n;
      break;
    case 5: 
      n = (INTEGER)n;
      break;
    case 6: 
      break;
    default: __CASECHK((CHAR*)"OfrontOPB", 75519);
  }
  return n;
}

/*----------------------------------------------------------------------------*/
OfrontOPT_Node OfrontOPB_NewShortConst (LONGINT uintval, INTEGER size)
{
  OfrontOPT_Node x = NIL;
  x = OfrontOPT_NewNode(7);
  x->conval = OfrontOPT_NewConst();
  switch (size) {
    case 1: 
      uintval = (BYTE)uintval;
      break;
    case 2: 
      uintval = (SHORTINT)uintval;
      break;
    case 4: 
      uintval = (INTEGER)uintval;
      break;
    case 8: 
      break;
    default: __CASECHK((CHAR*)"OfrontOPB", 79359);
  }
  x->conval->intval = uintval;
  OfrontOPB_SetIntType(x, 0);
  return x;
}

/*----------------------------------------------------------------------------*/
OfrontOPT_Node OfrontOPB_NewRealConst (REAL realval, OfrontOPT_Struct typ)
{
  OfrontOPT_Node x = NIL;
  x = OfrontOPT_NewNode(7);
  x->conval = OfrontOPT_NewConst();
  x->conval->realval = realval;
  x->typ = typ;
  x->conval->intval = -1;
  return x;
}

/*----------------------------------------------------------------------------*/
OfrontOPT_Node OfrontOPB_NewString (OfrontOPS_String str, struct CHAR16_ARRAY *lstr, INTEGER len)
{
  INTEGER i, j, c;
  OfrontOPT_Node x = NIL;
  OfrontOPS_String ext = NIL;
  x = OfrontOPT_NewNode(7);
  x->conval = OfrontOPT_NewConst();
  if (lstr != NIL) {
    x->typ = OfrontOPT_string16typ;
    ext = __NEWARR(NIL, 1, 1, 1, 1, (SYSTEM_ARRLEN)(3 * len));
    i = 0;
    j = 0;
    do {
      c = (INTEGER)(lstr->data)[__X(i, lstr->len[0], (CHAR*)"OfrontOPB", 84507)];
      i += 1;
      OfrontOPM_PutUtf8((void*)ext->data, ext->len[0], c, &j);
    } while (!(c == 0));
    x->conval->ext = ext;
  } else {
    x->typ = OfrontOPT_string8typ;
    x->conval->ext = str;
  }
  x->conval->intval = -1;
  x->conval->intval2 = len;
  return x;
}

/*----------------------------------------------------------------------------*/
static void OfrontOPB_CharToString8 (OfrontOPT_Node n)
{
  CHAR ch;
  n->typ = OfrontOPT_string8typ;
  ch = (CHAR)n->conval->intval;
  n->conval->ext = __NEWARR(NIL, 1, 1, 1, 1, (SYSTEM_ARRLEN)2);
  if (ch == 0x00) {
    n->conval->intval2 = 1;
  } else {
    n->conval->intval2 = 2;
    (n->conval->ext->data)[__X(1, n->conval->ext->len[0], (CHAR*)"OfrontOPB", 87903)] = 0x00;
  }
  (n->conval->ext->data)[0] = ch;
  n->conval->intval = -1;
  n->obj = NIL;
}

static void OfrontOPB_CharToString16 (OfrontOPT_Node n)
{
  INTEGER i;
  OfrontOPS_String _ptr__7 = NIL;
  n->typ = OfrontOPT_string16typ;
  n->conval->ext = __NEWARR(NIL, 1, 1, 1, 1, (SYSTEM_ARRLEN)4);
  if (n->conval->intval == 0) {
    (n->conval->ext->data)[0] = 0x00;
    n->conval->intval2 = 1;
  } else {
    i = 0;
    _ptr__7 = n->conval->ext;
    OfrontOPM_PutUtf8((void*)_ptr__7->data, _ptr__7->len[0], (INTEGER)n->conval->intval, &i);
    (n->conval->ext->data)[__X(i, n->conval->ext->len[0], (CHAR*)"OfrontOPB", 90904)] = 0x00;
    n->conval->intval2 = 2;
  }
  n->conval->intval = -1;
  n->obj = NIL;
}

static void OfrontOPB_String8ToString16 (OfrontOPT_Node n)
{
  INTEGER i, j, x;
  OfrontOPS_String ext = NIL;
  OfrontOPS_String new = NIL;
  n->typ = OfrontOPT_string16typ;
  ext = n->conval->ext;
  new = __NEWARR(NIL, 1, 1, 1, 1, (SYSTEM_ARRLEN)(__ASHL(n->conval->intval2, 1, INTEGER)));
  i = 0;
  j = 0;
  do {
    x = (SHORTINT)(ext->data)[__X(i, ext->len[0], (CHAR*)"OfrontOPB", 93465)];
    i += 1;
    OfrontOPM_PutUtf8((void*)new->data, new->len[0], x, &j);
  } while (!(x == 0));
  n->conval->ext = new;
  n->obj = NIL;
}

static void OfrontOPB_String16ToString8 (OfrontOPT_Node n)
{
  INTEGER i, j, x;
  OfrontOPS_String ext = NIL;
  OfrontOPS_String new = NIL;
  n->typ = OfrontOPT_string8typ;
  ext = n->conval->ext;
  new = __NEWARR(NIL, 1, 1, 1, 1, (SYSTEM_ARRLEN)n->conval->intval2);
  i = 0;
  j = 0;
  do {
    OfrontOPM_GetUtf8((void*)ext->data, ext->len[0], &x, &i);
    (new->data)[__X(j, new->len[0], (CHAR*)"OfrontOPB", 95809)] = (CHAR)__MASK(x, -256);
    j += 1;
  } while (!(x == 0));
  n->conval->ext = new;
  n->obj = NIL;
}

static void OfrontOPB_CheckString (OfrontOPT_Node n, OfrontOPT_Struct typ, SHORTINT e)
{
  OfrontOPT_Struct ntyp = NIL;
  ntyp = n->typ;
  if ((__IN(typ->comp, 0x0c) && (INTEGER)typ->BaseTyp->form == 3) || (INTEGER)typ->form == 10) {
    if ((INTEGER)n->class == 7 && (INTEGER)ntyp->form == 3) {
      OfrontOPB_CharToString8(n);
    } else if ((__IN(ntyp->comp, 0x0c) && (INTEGER)ntyp->BaseTyp->form == 3) || (INTEGER)ntyp->form == 10) {
    } else {
      OfrontOPB_err(e);
    }
  } else if ((__IN(typ->comp, 0x0c) && (INTEGER)typ->BaseTyp->form == 17) || (INTEGER)typ->form == 18) {
    if ((INTEGER)n->class == 7 && __IN(ntyp->form, 0x020008)) {
      OfrontOPB_CharToString16(n);
    } else if ((INTEGER)n->class == 7 && (INTEGER)ntyp->form == 10) {
      OfrontOPB_String8ToString16(n);
    } else if ((__IN(ntyp->comp, 0x0c) && (INTEGER)ntyp->BaseTyp->form == 17) || (INTEGER)ntyp->form == 18) {
    } else {
      OfrontOPB_err(e);
    }
  } else {
    OfrontOPB_err(e);
  }
}

static void OfrontOPB_BindNodes (BYTE class, OfrontOPT_Struct typ, OfrontOPT_Node *x, OfrontOPT_Node y)
{
  OfrontOPT_Node node = NIL;
  node = OfrontOPT_NewNode(class);
  node->typ = typ;
  node->left = *x;
  node->right = y;
  *x = node;
}

static BOOLEAN OfrontOPB_NotVar (OfrontOPT_Node x)
{
  return (((INTEGER)x->class >= 7 && (((INTEGER)x->class != 11 || (INTEGER)x->subcl != 34) || OfrontOPB_NotVar(x->left))) || __IN(x->typ->form, 0x040400)) || ((INTEGER)x->class == 5 && OfrontOPB_NotVar(x->left));
}

void OfrontOPB_DeRef (OfrontOPT_Node *x)
{
  OfrontOPT_Object strobj = NIL;
  OfrontOPT_Object bstrobj = NIL;
  OfrontOPT_Struct typ = NIL;
  OfrontOPT_Struct btyp = NIL;
  typ = (*x)->typ;
  if (((INTEGER)(*x)->class == 7 || (INTEGER)(*x)->class == 8) || (INTEGER)(*x)->class == 9) {
    OfrontOPB_err(78);
  } else if ((INTEGER)typ->form == 13) {
    if (typ == OfrontOPT_sysptrtyp) {
      OfrontOPB_err(57);
    }
    btyp = typ->BaseTyp;
    strobj = typ->strobj;
    bstrobj = btyp->strobj;
    if (((strobj != NIL && strobj->name != OfrontOPT_null) && bstrobj != NIL) && bstrobj->name != OfrontOPT_null) {
      btyp->pbused = 1;
    }
    OfrontOPB_BindNodes(3, btyp, x, NIL);
  } else {
    OfrontOPB_err(84);
  }
}

/*----------------------------------------------------------------------------*/
void OfrontOPB_StrDeref (OfrontOPT_Node *x)
{
  OfrontOPT_Struct typ = NIL;
  OfrontOPT_Struct btyp = NIL;
  typ = (*x)->typ;
  if (((INTEGER)(*x)->class == 7 || (INTEGER)(*x)->class == 8) || (INTEGER)(*x)->class == 9) {
    OfrontOPB_err(78);
  } else if (__IN(typ->comp, 0x0c) && __IN(typ->BaseTyp->form, 0x020008)) {
    if (typ->BaseTyp != NIL && (INTEGER)typ->BaseTyp->form == 3) {
      btyp = OfrontOPT_string8typ;
    } else {
      btyp = OfrontOPT_string16typ;
    }
    OfrontOPB_BindNodes(3, btyp, x, NIL);
    (*x)->subcl = 1;
  } else {
    OfrontOPB_err(90);
  }
}

/*----------------------------------------------------------------------------*/
void OfrontOPB_Index (OfrontOPT_Node *x, OfrontOPT_Node y)
{
  SHORTINT f;
  OfrontOPT_Struct typ = NIL;
  f = y->typ->form;
  if ((INTEGER)(*x)->class >= 7) {
    OfrontOPB_err(79);
  } else if (!__IN(f, 0x4072) || __IN(y->class, 0x0300)) {
    OfrontOPB_err(80);
    y->typ = OfrontOPT_inttyp;
  }
  if ((INTEGER)(*x)->typ->comp == 2) {
    typ = (*x)->typ->BaseTyp;
    if ((INTEGER)y->class == 7 && (y->conval->intval < 0 || y->conval->intval >= (LONGINT)(*x)->typ->n)) {
      OfrontOPB_err(81);
    }
  } else if ((INTEGER)(*x)->typ->comp == 3) {
    typ = (*x)->typ->BaseTyp;
    if ((INTEGER)y->class == 7 && y->conval->intval < 0) {
      OfrontOPB_err(81);
    }
  } else {
    OfrontOPB_err(82);
    typ = OfrontOPT_undftyp;
  }
  OfrontOPB_BindNodes(4, typ, x, y);
  (*x)->readonly = (*x)->left->readonly;
}

/*----------------------------------------------------------------------------*/
void OfrontOPB_Field (OfrontOPT_Node *x, OfrontOPT_Object y)
{
  if ((INTEGER)(*x)->class >= 7) {
    OfrontOPB_err(77);
  }
  if (y != NIL && __IN(y->mode, 0x2010)) {
    OfrontOPB_BindNodes(2, y->typ, x, NIL);
    (*x)->obj = y;
    (*x)->readonly = (*x)->left->readonly || ((INTEGER)y->vis == 2 && (INTEGER)y->mnolev < 0);
  } else {
    OfrontOPB_err(83);
    (*x)->typ = OfrontOPT_undftyp;
  }
}

/*----------------------------------------------------------------------------*/
static struct TypTest__78 {
  OfrontOPT_Node *x;
  OfrontOPT_Object *obj;
  BOOLEAN *guard;
  struct TypTest__78 *lnk;
} *TypTest__78_s;

static void __79 (OfrontOPT_Struct t0, OfrontOPT_Struct t1);

static void __79 (OfrontOPT_Struct t0, OfrontOPT_Struct t1)
{
  OfrontOPT_Node node = NIL;
  if ((t0 != NIL && OfrontOPT_SameType(t0, t1)) && ((*TypTest__78_s->guard) || (INTEGER)(*TypTest__78_s->x)->class != 5)) {
    if (!(*TypTest__78_s->guard)) {
      *TypTest__78_s->x = OfrontOPB_NewBoolConst(1);
    }
  } else if ((t0 == NIL || OfrontOPT_Extends(t1, t0)) || (INTEGER)t0->form == 0) {
    if ((*TypTest__78_s->guard)) {
      OfrontOPB_BindNodes(5, NIL, TypTest__78_s->x, NIL);
      (*TypTest__78_s->x)->readonly = (*TypTest__78_s->x)->left->readonly;
    } else {
      node = OfrontOPT_NewNode(11);
      node->subcl = 18;
      node->left = *TypTest__78_s->x;
      node->obj = (*TypTest__78_s->obj);
      *TypTest__78_s->x = node;
    }
  } else {
    OfrontOPB_err(85);
  }
}

void OfrontOPB_TypTest (OfrontOPT_Node *x, OfrontOPT_Object obj, BOOLEAN guard)
{
  struct TypTest__78 _s;
  _s.x = x;
  _s.obj = &obj;
  _s.guard = &guard;
  _s.lnk = TypTest__78_s;
  TypTest__78_s = &_s;
  if (OfrontOPB_NotVar(*x)) {
    OfrontOPB_err(112);
  } else if ((INTEGER)(*x)->typ->form == 13) {
    if ((INTEGER)(*x)->typ->BaseTyp->comp != 4 && (*x)->typ != OfrontOPT_sysptrtyp) {
      OfrontOPB_err(85);
    } else if ((INTEGER)obj->typ->form == 13) {
      __79((*x)->typ->BaseTyp, obj->typ->BaseTyp);
    } else {
      OfrontOPB_err(86);
    }
  } else if ((((INTEGER)(*x)->typ->comp == 4 && (INTEGER)(*x)->class == 1) && (INTEGER)(*x)->obj->vis != 4) && (INTEGER)obj->typ->comp == 4) {
    __79((*x)->typ, obj->typ);
  } else {
    OfrontOPB_err(87);
  }
  if (guard) {
    (*x)->typ = obj->typ;
  } else {
    (*x)->typ = OfrontOPT_booltyp;
  }
  TypTest__78_s = _s.lnk;
}

/*----------------------------------------------------------------------------*/
void OfrontOPB_In (OfrontOPT_Node *x, OfrontOPT_Node y)
{
  SHORTINT f;
  LONGINT k;
  f = (*x)->typ->form;
  if ((((INTEGER)(*x)->class == 8 || (INTEGER)(*x)->class == 9) || (INTEGER)y->class == 8) || (INTEGER)y->class == 9) {
    OfrontOPB_err(126);
  } else if (__IN(f, 0x4072) && (INTEGER)y->typ->form == 9) {
    if ((INTEGER)(*x)->class == 7) {
      k = (*x)->conval->intval;
      if (k < 0 || k > (LONGINT)OfrontOPM_MaxSet) {
        OfrontOPB_err(202);
      } else if ((INTEGER)y->class == 7) {
        (*x)->conval->intval = OfrontOPB_BoolToInt(__IN(k, y->conval->setval));
        (*x)->obj = NIL;
      } else {
        OfrontOPB_BindNodes(12, OfrontOPT_booltyp, x, y);
        (*x)->subcl = 17;
      }
    } else {
      OfrontOPB_BindNodes(12, OfrontOPT_booltyp, x, y);
      (*x)->subcl = 17;
    }
  } else {
    OfrontOPB_err(92);
  }
  (*x)->typ = OfrontOPT_booltyp;
}

/*----------------------------------------------------------------------------*/
static LONGINT OfrontOPB_log (LONGINT x)
{
  OfrontOPB_exp = 0;
  if (x > 0) {
    while (!__ODD(x)) {
      x = __ASHR(x, 1, LONGINT);
      OfrontOPB_exp += 1;
    }
  }
  return x;
}

static void OfrontOPB_CheckRealType (INTEGER f, SHORTINT nr, OfrontOPT_Const x)
{
  REAL min, max, r;
  if (f == 7) {
    min = OfrontOPM_MinReal32;
    max = OfrontOPM_MaxReal32;
  } else {
    min = OfrontOPM_MinReal64;
    max = OfrontOPM_MaxReal64;
  }
  r = __ABS(x->realval);
  if ((r > max || r < min) && r != OfrontOPM_InfReal) {
    OfrontOPB_err(nr);
    x->realval = (REAL)1;
  } else if (f == 7) {
    x->realval = (SHORTREAL)x->realval;
  }
  x->intval = -1;
}

static void OfrontOPB_GetRealConstType (INTEGER f, SHORTINT nr, OfrontOPT_Const x, OfrontOPT_Struct *typ)
{
  if (OfrontOPM_Lang == 'C' && __IN(f, 0x0180)) {
    *typ = OfrontOPT_lrltyp;
    f = 8;
  }
  OfrontOPB_CheckRealType(f, nr, x);
}

static struct MOp__39 {
  struct MOp__39 *lnk;
} *MOp__39_s;

static OfrontOPT_Node __40 (BYTE op, OfrontOPT_Struct typ, OfrontOPT_Node z);

static OfrontOPT_Node __40 (BYTE op, OfrontOPT_Struct typ, OfrontOPT_Node z)
{
  OfrontOPT_Node node = NIL;
  node = OfrontOPT_NewNode(11);
  node->subcl = op;
  node->typ = typ;
  node->left = z;
  return node;
}

void OfrontOPB_MOp (BYTE op, OfrontOPT_Node *x)
{
  INTEGER f;
  OfrontOPT_Struct typ = NIL;
  OfrontOPT_Node z = NIL;
  struct MOp__39 _s;
  _s.lnk = MOp__39_s;
  MOp__39_s = &_s;
  z = *x;
  if ((((INTEGER)z->class == 8 || (INTEGER)z->class == 9) && (INTEGER)op != 31) && (INTEGER)op != 39) {
    OfrontOPB_err(126);
  } else {
    typ = z->typ;
    f = typ->form;
    switch (op) {
      case 35: 
        if (f == 2) {
          if ((INTEGER)z->class == 7) {
            z->conval->intval = OfrontOPB_BoolToInt(!OfrontOPB_IntToBool(z->conval->intval));
            z->obj = NIL;
          } else {
            z = __40(op, typ, z);
          }
        } else {
          OfrontOPB_err(98);
        }
        break;
      case 8: 
        if (!__IN(f, 0x41f2)) {
          OfrontOPB_err(96);
        }
        break;
      case 9: 
        if (__IN(f, 0x43f2)) {
          if ((INTEGER)z->class == 7) {
            if (__IN(f, 0x4072)) {
              if (z->conval->intval == (-9223372036854775807LL-1)) {
                OfrontOPB_err(203);
              } else {
                z->conval->intval = -z->conval->intval;
                OfrontOPB_SetIntType(z, 0);
              }
            } else if (__IN(f, 0x0180)) {
              z->conval->realval = -z->conval->realval;
            } else {
              z->conval->setval = ~z->conval->setval;
            }
            z->obj = NIL;
          } else {
            if (OfrontOPM_Lang == 'C' && f < 5) {
              if ((INTEGER)OfrontOPM_AdrSize == 2) {
                OfrontOPB_Convert(&z, OfrontOPT_sinttyp);
              } else {
                OfrontOPB_Convert(&z, OfrontOPT_inttyp);
              }
            }
            z = __40(op, z->typ, z);
          }
        } else {
          OfrontOPB_err(97);
        }
        break;
      case 23: 
        if (__IN(f, 0x41f2)) {
          if ((INTEGER)z->class == 7) {
            if (__IN(f, 0x4072)) {
              if (z->conval->intval == (-9223372036854775807LL-1)) {
                OfrontOPB_err(203);
              } else {
                z->conval->intval = __ABS(z->conval->intval);
                OfrontOPB_SetIntType(z, 0);
              }
            } else {
              z->conval->realval = __ABS(z->conval->realval);
            }
            z->obj = NIL;
          } else {
            if (OfrontOPM_Lang == 'C' && f < 5) {
              if ((INTEGER)OfrontOPM_AdrSize == 2) {
                OfrontOPB_Convert(&z, OfrontOPT_sinttyp);
              } else {
                OfrontOPB_Convert(&z, OfrontOPT_inttyp);
              }
            }
            z = __40(op, z->typ, z);
          }
        } else {
          OfrontOPB_err(111);
        }
        break;
      case 24: 
        if (__IN(f, 0x020008)) {
          if ((INTEGER)z->class == 7) {
            if (__ODD(__ASHR(z->conval->intval, 5, LONGINT))) {
              z->conval->intval -= 32;
            }
            z->obj = NIL;
          } else {
            z = __40(op, typ, z);
          }
        } else {
          OfrontOPB_err(111);
          z->typ = OfrontOPT_char8typ;
        }
        break;
      case 25: 
        if (__IN(f, 0x4072)) {
          if ((INTEGER)z->class == 7) {
            z->conval->intval = OfrontOPB_BoolToInt(__ODD(z->conval->intval));
            z->obj = NIL;
          } else {
            z = __40(op, typ, z);
          }
        } else {
          OfrontOPB_err(111);
        }
        z->typ = OfrontOPT_booltyp;
        break;
      case 31: 
        if (((INTEGER)z->class == 7 && f == 3) && z->conval->intval >= 32) {
          OfrontOPB_CharToString8(z);
          f = 10;
        } else if (((INTEGER)z->class == 7 && f == 17) && z->conval->intval >= 32) {
          OfrontOPB_CharToString16(z);
          f = 18;
        }
        if ((INTEGER)z->class == 9 && (INTEGER)z->obj->mode != 9) {
          if ((INTEGER)z->obj->mnolev > 0) {
            OfrontOPB_err(73);
          } else if ((INTEGER)z->obj->mode == 6) {
            z->obj->mode = 7;
          }
          z = __40(op, typ, z);
        } else if ((INTEGER)z->class == 8) {
          if ((INTEGER)z->obj->typ->sysflag != 0 || ((INTEGER)typ->comp == 1 && f != 13)) {
            OfrontOPB_err(111);
          }
          z = __40(op, typ, z);
        } else if ((INTEGER)z->class < 7 || ((INTEGER)z->class == 7 && __IN(f, 0x040400))) {
          z = __40(op, typ, z);
        } else {
          OfrontOPB_err(127);
        }
        switch (OfrontOPM_AdrSize) {
          case 4: 
            z->typ = OfrontOPT_inttyp;
            break;
          case 8: 
            z->typ = OfrontOPT_linttyp;
            break;
          default: 
            z->typ = OfrontOPT_sinttyp;
            break;
        }
        break;
      case 39: 
        z = __40(op, typ, z);
        switch (OfrontOPM_AdrSize) {
          case 4: 
            z->typ = OfrontOPT_inttyp;
            break;
          case 8: 
            z->typ = OfrontOPT_linttyp;
            break;
          default: 
            z->typ = OfrontOPT_sinttyp;
            break;
        }
        break;
      case 40: 
        if (__IN(f, 0x4072)) {
          z = __40(op, typ, z);
        } else {
          OfrontOPB_err(127);
        }
        break;
      default: __CASECHK((CHAR*)"OfrontOPB", 166717);
    }
  }
  *x = z;
  MOp__39_s = _s.lnk;
}

/*----------------------------------------------------------------------------*/
static void OfrontOPB_CheckPtr (OfrontOPT_Node x, OfrontOPT_Node y)
{
  SHORTINT g;
  OfrontOPT_Struct p = NIL;
  OfrontOPT_Struct q = NIL;
  OfrontOPT_Struct t = NIL;
  g = y->typ->form;
  if ((INTEGER)g == 13) {
    p = x->typ->BaseTyp;
    q = y->typ->BaseTyp;
    if ((INTEGER)p->comp == 4 && (INTEGER)q->comp == 4) {
      if ((INTEGER)p->extlev < (INTEGER)q->extlev) {
        t = p;
        p = q;
        q = t;
      }
      while ((p != q && p != NIL) && p != OfrontOPT_undftyp) {
        p = p->BaseTyp;
      }
      if (p == NIL) {
        OfrontOPB_err(100);
      }
    } else {
      OfrontOPB_err(100);
    }
  } else if ((INTEGER)g != 11) {
    OfrontOPB_err(100);
  }
}

static void OfrontOPB_Promote (OfrontOPT_Node *left, OfrontOPT_Node *right, INTEGER op)
{
  INTEGER f, g;
  OfrontOPT_Struct new = NIL;
  f = (*left)->typ->form;
  g = (*right)->typ->form;
  new = (*left)->typ;
  if (OfrontOPM_Lang > '3' && __IN(f, 0x41f2)) {
    if (__IN(g, 0x41f2)) {
      if (OfrontOPM_Lang == '7' && __IN(f, 0x4072) != __IN(g, 0x4072)) {
        OfrontOPB_err(100);
      } else if ((((f == 7 && (INTEGER)(*right)->class == 7) && __IN(g, 0x0180)) && (INTEGER)(*left)->class != 7) || (((g == 7 && (INTEGER)(*left)->class == 7) && __IN(f, 0x0180)) && (INTEGER)(*right)->class != 7)) {
        new = OfrontOPT_realtyp;
      } else if (f == 8 || g == 8) {
        new = OfrontOPT_lrltyp;
      } else if (f == 7 || g == 7) {
        new = OfrontOPT_realtyp;
      } else if (op == 2 && OfrontOPM_Lang != '7') {
        new = OfrontOPT_lrltyp;
      } else if (f == 6 || g == 6) {
        new = OfrontOPT_linttyp;
      } else if (f == 5 || g == 5) {
        new = OfrontOPT_inttyp;
      } else if ((INTEGER)OfrontOPM_AdrSize == 2) {
        new = OfrontOPT_sinttyp;
      } else {
        new = OfrontOPT_inttyp;
      }
    } else {
      OfrontOPB_err(100);
    }
    if (g != (INTEGER)new->form) {
      OfrontOPB_Convert(right, new);
    }
    if (f != (INTEGER)new->form) {
      OfrontOPB_Convert(left, new);
    }
  } else if (__IN(f, 0x060408)) {
    if (__IN(g, 0x060408)) {
      if (((f == 18 || g == 18) || (f == 17 && g == 10)) || (f == 10 && g == 17)) {
        new = OfrontOPT_string16typ;
      } else if ((f == 17 || g == 17) && op != 8) {
        new = OfrontOPT_char16typ;
      } else if (f == 10 || g == 10) {
        new = OfrontOPT_string8typ;
      } else if (op == 8) {
        if (f == 17 || g == 17) {
          new = OfrontOPT_string16typ;
        } else {
          new = OfrontOPT_string8typ;
        }
      }
      if (__IN(new->form, 0x040400) && ((__IN(f, 0x020008) && (INTEGER)(*left)->class != 7) || (__IN(g, 0x020008) && (INTEGER)(*right)->class != 7))) {
        OfrontOPB_err(100);
      }
    } else {
      OfrontOPB_err(100);
    }
    if (g != (INTEGER)new->form) {
      OfrontOPB_Convert(right, new);
    }
    if (f != (INTEGER)new->form) {
      OfrontOPB_Convert(left, new);
    }
  }
}

static void OfrontOPB_PromoteByte (OfrontOPT_Node *left, OfrontOPT_Node *right)
{
  INTEGER f, g;
  OfrontOPT_Struct new = NIL;
  f = (*left)->typ->form;
  g = (*right)->typ->form;
  new = (*left)->typ;
  if (__IN(f, 0x41f2) && __IN(g, 0x41f2)) {
    if (f == 8 || g == 8) {
      new = OfrontOPT_lrltyp;
    } else if (f == 7 || g == 7) {
      new = OfrontOPT_realtyp;
    } else if (f == 6 || g == 6) {
      new = OfrontOPT_linttyp;
    } else if (f == 5 || g == 5) {
      new = OfrontOPT_inttyp;
    } else if ((INTEGER)OfrontOPM_AdrSize == 2 || OfrontOPM_Lang <= '3') {
      new = OfrontOPT_sinttyp;
    } else {
      new = OfrontOPT_inttyp;
    }
    if (g != (INTEGER)new->form) {
      (*right)->typ = new;
    }
    if (f != (INTEGER)new->form) {
      (*left)->typ = new;
    }
  }
}

void OfrontOPB_CheckParameters (OfrontOPT_Object fp, OfrontOPT_Object ap, BOOLEAN checkNames)
{
  OfrontOPT_Struct ft = NIL;
  OfrontOPT_Struct at = NIL;
  while (fp != NIL) {
    if (ap != NIL) {
      ft = fp->typ;
      at = ap->typ;
      if (fp->ptyp != NIL) {
        ft = fp->ptyp;
      }
      if (ap->ptyp != NIL) {
        at = ap->ptyp;
      }
      if ((((!OfrontOPT_EqualType(ft, at) || (INTEGER)fp->mode != (INTEGER)ap->mode) || (INTEGER)fp->sysflag != (INTEGER)ap->sysflag) || (INTEGER)fp->vis != (INTEGER)ap->vis) || (checkNames && __STRCMPCC(fp->name->data, ap->name->data, ap->name->len[0], (CHAR*)"OfrontOPB", 190526) != 0)) {
        OfrontOPB_err(115);
      }
      ap = ap->link;
    } else {
      OfrontOPB_err(116);
    }
    fp = fp->link;
  }
  if (ap != NIL) {
    OfrontOPB_err(116);
  }
}

/*----------------------------------------------------------------------------*/
static void OfrontOPB_CheckProc (OfrontOPT_Struct x, OfrontOPT_Object y)
{
  if (__IN(y->mode, 0x04c0) && (INTEGER)x->sysflag == (INTEGER)y->sysflag) {
    if ((INTEGER)y->mode == 6) {
      if ((INTEGER)y->mnolev == 0) {
        y->mode = 7;
      } else {
        OfrontOPB_err(73);
      }
    }
    if (OfrontOPT_EqualType(x->BaseTyp, y->typ)) {
      OfrontOPB_CheckParameters(x->link, y->link, 0);
    } else {
      OfrontOPB_err(117);
    }
  } else {
    OfrontOPB_err(113);
  }
}

static struct ConstOp__19 {
  OfrontOPT_Node *x;
  INTEGER *f;
  OfrontOPT_Const *xval, *yval;
  struct ConstOp__19 *lnk;
} *ConstOp__19_s;

static SHORTINT __20 (void);

static SHORTINT __20 (void)
{
  SHORTINT res;
  switch ((*ConstOp__19_s->f)) {
    case 0: 
      res = 11;
      break;
    case 1: case 3: case 4: case 5: case 6: 
    case 17: 
      if (((*ConstOp__19_s->xval))->intval < ((*ConstOp__19_s->yval))->intval) {
        res = 13;
      } else if (((*ConstOp__19_s->xval))->intval > ((*ConstOp__19_s->yval))->intval) {
        res = 15;
      } else {
        res = 11;
      }
      break;
    case 7: case 8: 
      if (((*ConstOp__19_s->xval))->realval < ((*ConstOp__19_s->yval))->realval) {
        res = 13;
      } else if (((*ConstOp__19_s->xval))->realval > ((*ConstOp__19_s->yval))->realval) {
        res = 15;
      } else {
        res = 11;
      }
      break;
    case 2: 
      if (((*ConstOp__19_s->xval))->intval != ((*ConstOp__19_s->yval))->intval) {
        res = 12;
      } else {
        res = 11;
      }
      break;
    case 9: 
      if (((*ConstOp__19_s->xval))->setval != ((*ConstOp__19_s->yval))->setval) {
        res = 12;
      } else {
        res = 11;
      }
      break;
    case 10: case 18: 
      if (__STRCMPCC(((*ConstOp__19_s->xval))->ext->data, ((*ConstOp__19_s->yval))->ext->data, ((*ConstOp__19_s->yval))->ext->len[0], (CHAR*)"OfrontOPB", 205055) < 0) {
        res = 13;
      } else if (__STRCMPCC(((*ConstOp__19_s->xval))->ext->data, ((*ConstOp__19_s->yval))->ext->data, ((*ConstOp__19_s->yval))->ext->len[0], (CHAR*)"OfrontOPB", 204287) > 0) {
        res = 15;
      } else {
        res = 11;
      }
      break;
    case 11: case 13: case 15: 
      if (((*ConstOp__19_s->xval))->intval != ((*ConstOp__19_s->yval))->intval) {
        res = 12;
      } else {
        res = 11;
      }
      break;
    default: __CASECHK((CHAR*)"OfrontOPB", 205823);
  }
  ((*ConstOp__19_s->x))->typ = OfrontOPT_booltyp;
  return res;
}

static void OfrontOPB_ConstOp (SHORTINT op, OfrontOPT_Node x, OfrontOPT_Node y)
{
  INTEGER f, g, i, j;
  OfrontOPT_Const xval = NIL;
  OfrontOPT_Const yval = NIL;
  OfrontOPS_String ext = NIL;
  LONGINT xv, yv;
  BOOLEAN temp;
  struct ConstOp__19 _s;
  _s.x = &x;
  _s.f = &f;
  _s.xval = &xval;
  _s.yval = &yval;
  _s.lnk = ConstOp__19_s;
  ConstOp__19_s = &_s;
  f = x->typ->form;
  g = y->typ->form;
  xval = x->conval;
  yval = y->conval;
  if (f != g) {
    switch (f) {
      case 3: case 17: 
        if (g == 10) {
          OfrontOPB_CharToString8(x);
        } else if (g == 18) {
          OfrontOPB_CharToString16(x);
        } else {
          OfrontOPB_err(100);
          y->typ = x->typ;
          __GUARDEQP(yval, OfrontOPT_ConstDesc) = *xval;
        }
        break;
      case 1: 
        if (__IN(g, 0x4072)) {
          x->typ = y->typ;
        } else if (g == 7) {
          x->typ = OfrontOPT_realtyp;
          xval->realval = xval->intval;
        } else if (g == 8) {
          x->typ = OfrontOPT_lrltyp;
          xval->realval = xval->intval;
        } else {
          OfrontOPB_err(100);
          y->typ = x->typ;
          __GUARDEQP(yval, OfrontOPT_ConstDesc) = *xval;
        }
        break;
      case 4: 
        if (g == 1) {
          y->typ = OfrontOPT_sinttyp;
        } else if (__IN(g, 0x4072)) {
          x->typ = y->typ;
        } else if (g == 7) {
          x->typ = OfrontOPT_realtyp;
          xval->realval = xval->intval;
        } else if (g == 8) {
          x->typ = OfrontOPT_lrltyp;
          xval->realval = xval->intval;
        } else {
          OfrontOPB_err(100);
          y->typ = x->typ;
          __GUARDEQP(yval, OfrontOPT_ConstDesc) = *xval;
        }
        break;
      case 5: 
        if (__IN(g, 0x12)) {
          y->typ = OfrontOPT_inttyp;
        } else if (__IN(g, 0x4072)) {
          x->typ = y->typ;
        } else if (g == 7) {
          x->typ = OfrontOPT_realtyp;
          xval->realval = xval->intval;
        } else if (g == 8) {
          x->typ = OfrontOPT_lrltyp;
          xval->realval = xval->intval;
        } else {
          OfrontOPB_err(100);
          y->typ = x->typ;
          __GUARDEQP(yval, OfrontOPT_ConstDesc) = *xval;
        }
        break;
      case 6: 
        if (__IN(g, 0x4072)) {
          y->typ = OfrontOPT_linttyp;
        } else if (g == 7) {
          x->typ = OfrontOPT_realtyp;
          xval->realval = xval->intval;
        } else if (g == 8) {
          x->typ = OfrontOPT_lrltyp;
          xval->realval = xval->intval;
        } else {
          OfrontOPB_err(100);
          y->typ = x->typ;
          __GUARDEQP(yval, OfrontOPT_ConstDesc) = *xval;
        }
        break;
      case 7: 
        if (__IN(g, 0x4072)) {
          y->typ = x->typ;
          yval->realval = yval->intval;
        } else if (g == 8) {
          x->typ = OfrontOPT_lrltyp;
        } else {
          OfrontOPB_err(100);
          y->typ = x->typ;
          __GUARDEQP(yval, OfrontOPT_ConstDesc) = *xval;
        }
        break;
      case 8: 
        if (__IN(g, 0x4072)) {
          y->typ = x->typ;
          yval->realval = yval->intval;
        } else if (g == 7) {
          y->typ = OfrontOPT_lrltyp;
        } else {
          OfrontOPB_err(100);
          y->typ = x->typ;
          __GUARDEQP(yval, OfrontOPT_ConstDesc) = *xval;
        }
        break;
      case 10: case 18: 
        if (g == 3) {
          OfrontOPB_CharToString8(y);
          g = 10;
        } else if (g == 17) {
          OfrontOPB_CharToString16(y);
          g = 18;
        } else {
          OfrontOPB_err(100);
          y->typ = x->typ;
          __GUARDEQP(yval, OfrontOPT_ConstDesc) = *xval;
        }
        break;
      case 11: 
        if (!__IN(g, 0xa000)) {
          OfrontOPB_err(100);
        }
        break;
      case 13: 
        OfrontOPB_CheckPtr(x, y);
        break;
      case 15: 
        if (g != 11) {
          OfrontOPB_err(100);
        }
        break;
      default: 
        OfrontOPB_err(100);
        y->typ = x->typ;
        __GUARDEQP(yval, OfrontOPT_ConstDesc) = *xval;
        break;
    }
    f = x->typ->form;
  }
  switch (op) {
    case 1: 
      if (__IN(f, 0x4072)) {
        xv = xval->intval;
        yv = yval->intval;
        if (((((xv == 0 || yv == 0) || ((xv > 0 && yv > 0) && yv <= __DIVFL(9223372036854775807LL, xv))) || ((xv > 0 && yv < 0) && yv >= __DIVFL((-9223372036854775807LL-1), xv))) || ((xv < 0 && yv > 0) && xv >= __DIVFL((-9223372036854775807LL-1), yv))) || ((((xv < 0 && yv < 0) && xv != (-9223372036854775807LL-1)) && yv != (-9223372036854775807LL-1)) && -xv <= __DIVFL(9223372036854775807LL, -yv))) {
          xval->intval = xv * yv;
          OfrontOPB_SetIntType(x, 0);
        } else {
          OfrontOPB_err(204);
        }
      } else if (__IN(f, 0x0180)) {
        temp = __ABS(yval->realval) <= (REAL)1;
        if (temp || __ABS(xval->realval) <= OfrontOPM_MaxReal64 / (REAL)__ABS(yval->realval)) {
          xval->realval = xval->realval * yval->realval;
          OfrontOPB_GetRealConstType(f, 204, xval, &x->typ);
        } else {
          OfrontOPB_err(204);
        }
      } else if (f == 9) {
        xval->setval = xval->setval & yval->setval;
      } else if (f != 0) {
        OfrontOPB_err(101);
      }
      break;
    case 2: 
      if (__IN(f, 0x4072)) {
        if (yval->intval != 0) {
          xval->realval = (REAL)xval->intval / (REAL)(REAL)yval->intval;
          OfrontOPB_GetRealConstType(7, 205, xval, &x->typ);
        } else {
          OfrontOPB_err(205);
          xval->realval = (REAL)1;
        }
        x->typ = OfrontOPT_realtyp;
      } else if (__IN(f, 0x0180)) {
        temp = __ABS(yval->realval) >= (REAL)1;
        if (temp || __ABS(xval->realval) <= OfrontOPM_MaxReal64 * __ABS(yval->realval)) {
          xval->realval = xval->realval / yval->realval;
          OfrontOPB_GetRealConstType(f, 205, xval, &x->typ);
        } else {
          OfrontOPB_err(205);
        }
      } else if (f == 9) {
        xval->setval = xval->setval ^ yval->setval;
      } else if (f != 0) {
        OfrontOPB_err(102);
      }
      break;
    case 3: 
      if (__IN(f, 0x4072)) {
        if (xval->intval == (-9223372036854775807LL-1) && yval->intval == -1) {
          OfrontOPB_err(204);
        } else if (yval->intval != 0) {
          xval->intval = __DIVFL(xval->intval, yval->intval);
          OfrontOPB_SetIntType(x, 0);
        } else {
          OfrontOPB_err(205);
        }
      } else if (f != 0) {
        OfrontOPB_err(103);
      }
      break;
    case 5: 
      if (!__IN(16, OfrontOPM_opt)) {
        OfrontOPB_err(-303);
      }
      if (__IN(f, 0x4072)) {
        if (xval->intval == (-9223372036854775807LL-1) && yval->intval == -1) {
          OfrontOPB_err(204);
        } else if (yval->intval != 0) {
          xval->intval = OfrontOPM_Div0(xval->intval, yval->intval);
          OfrontOPB_SetIntType(x, 0);
        } else {
          OfrontOPB_err(205);
        }
      } else if (f != 0) {
        OfrontOPB_err(140);
      }
      break;
    case 4: 
      if (__IN(f, 0x4072)) {
        if (yval->intval != 0) {
          xval->intval = __MODFL(xval->intval, yval->intval);
          OfrontOPB_SetIntType(x, 0);
        } else {
          OfrontOPB_err(205);
        }
      } else if (f != 0) {
        OfrontOPB_err(104);
      }
      break;
    case 6: 
      if (!__IN(16, OfrontOPM_opt)) {
        OfrontOPB_err(-303);
      }
      if (__IN(f, 0x4072)) {
        if (yval->intval != 0) {
          xval->intval = OfrontOPM_Rem0(xval->intval, yval->intval);
          OfrontOPB_SetIntType(x, 0);
        } else {
          OfrontOPB_err(205);
        }
      } else if (f != 0) {
        OfrontOPB_err(141);
      }
      break;
    case 7: 
      if (f == 2) {
        xval->intval = OfrontOPB_BoolToInt(OfrontOPB_IntToBool(xval->intval) && OfrontOPB_IntToBool(yval->intval));
      } else {
        OfrontOPB_err(94);
      }
      break;
    case 8: 
      if (__IN(f, 0x4072)) {
        temp = yval->intval >= 0 && xval->intval <= 9223372036854775807LL - yval->intval;
        if (temp || (yval->intval < 0 && xval->intval >= (-9223372036854775807LL-1) - yval->intval)) {
          xval->intval += yval->intval;
          OfrontOPB_SetIntType(x, 0);
        } else {
          OfrontOPB_err(206);
        }
      } else if (__IN(f, 0x0180)) {
        temp = yval->realval >= (REAL)0 && xval->realval <= OfrontOPM_MaxReal64 - yval->realval;
        if (temp || (yval->realval < (REAL)0 && xval->realval >= OfrontOPM_MinReal64 - yval->realval)) {
          xval->realval = xval->realval + yval->realval;
          OfrontOPB_GetRealConstType(f, 206, xval, &x->typ);
        } else {
          OfrontOPB_err(206);
        }
      } else if (f == 9) {
        xval->setval = xval->setval | yval->setval;
      } else if ((((OfrontOPM_Lang == 'C' || OfrontOPM_Lang == '3') && __IN(f, 0x040400)) && xval->ext != NIL) && yval->ext != NIL) {
        ext = __NEWARR(NIL, 1, 1, 1, 1, (SYSTEM_ARRLEN)(xval->ext->len[0] + yval->ext->len[0]));
        i = 0;
        while ((xval->ext->data)[__X(i, xval->ext->len[0], (CHAR*)"OfrontOPB", 247075)] != 0x00) {
          (ext->data)[__X(i, ext->len[0], (CHAR*)"OfrontOPB", 247100)] = (xval->ext->data)[__X(i, xval->ext->len[0], (CHAR*)"OfrontOPB", 247100)];
          i += 1;
        }
        j = 0;
        while ((yval->ext->data)[__X(j, yval->ext->len[0], (CHAR*)"OfrontOPB", 247331)] != 0x00) {
          (ext->data)[__X(i, ext->len[0], (CHAR*)"OfrontOPB", 247356)] = (yval->ext->data)[__X(j, yval->ext->len[0], (CHAR*)"OfrontOPB", 247356)];
          i += 1;
          j += 1;
        }
        (ext->data)[__X(i, ext->len[0], (CHAR*)"OfrontOPB", 247569)] = 0x00;
        xval->ext = ext;
        xval->intval2 += yval->intval2 - 1;
      } else if (f != 0) {
        OfrontOPB_err(105);
      }
      break;
    case 9: 
      if (__IN(f, 0x4072)) {
        if ((yval->intval >= 0 && xval->intval >= (-9223372036854775807LL-1) + yval->intval) || (yval->intval < 0 && xval->intval <= 9223372036854775807LL + yval->intval)) {
          xval->intval -= yval->intval;
          OfrontOPB_SetIntType(x, 0);
        } else {
          OfrontOPB_err(207);
        }
      } else if (__IN(f, 0x0180)) {
        temp = yval->realval >= (REAL)0 && xval->realval >= OfrontOPM_MinReal64 + yval->realval;
        if (temp || (yval->realval < (REAL)0 && xval->realval <= OfrontOPM_MaxReal64 + yval->realval)) {
          xval->realval = xval->realval - yval->realval;
          OfrontOPB_GetRealConstType(f, 207, xval, &x->typ);
        } else {
          OfrontOPB_err(207);
        }
      } else if (f == 9) {
        xval->setval = xval->setval & ~yval->setval;
      } else if (f != 0) {
        OfrontOPB_err(106);
      }
      break;
    case 36: 
      if (__IN(f, 0x41fa)) {
        if ((INTEGER)__20() == 15) {
          __GUARDEQP(xval, OfrontOPT_ConstDesc) = *yval;
        }
        x->typ = y->typ;
      } else if (f != 0) {
        OfrontOPB_err(111);
      }
      break;
    case 37: 
      if (__IN(f, 0x41fa)) {
        if ((INTEGER)__20() == 13) {
          __GUARDEQP(xval, OfrontOPT_ConstDesc) = *yval;
        }
        x->typ = y->typ;
      } else if (f != 0) {
        OfrontOPB_err(111);
      }
      break;
    case 10: 
      if (f == 2) {
        xval->intval = OfrontOPB_BoolToInt(OfrontOPB_IntToBool(xval->intval) || OfrontOPB_IntToBool(yval->intval));
      } else {
        OfrontOPB_err(95);
      }
      break;
    case 11: 
      xval->intval = OfrontOPB_BoolToInt((INTEGER)__20() == 11);
      break;
    case 12: 
      xval->intval = OfrontOPB_BoolToInt((INTEGER)__20() != 11);
      break;
    case 13: 
      if (__IN(f, 0x2a04)) {
        OfrontOPB_err(108);
      } else {
        xval->intval = OfrontOPB_BoolToInt((INTEGER)__20() == 13);
      }
      break;
    case 14: 
      if (__IN(f, 0x2a04)) {
        OfrontOPB_err(108);
      } else {
        xval->intval = OfrontOPB_BoolToInt((INTEGER)__20() != 15);
      }
      break;
    case 15: 
      if (__IN(f, 0x2a04)) {
        OfrontOPB_err(108);
      } else {
        xval->intval = OfrontOPB_BoolToInt((INTEGER)__20() == 15);
      }
      break;
    case 16: 
      if (__IN(f, 0x2a04)) {
        OfrontOPB_err(108);
      } else {
        xval->intval = OfrontOPB_BoolToInt((INTEGER)__20() != 13);
      }
      break;
    default: __CASECHK((CHAR*)"OfrontOPB", 261887);
  }
  ConstOp__19_s = _s.lnk;
}

static void OfrontOPB_Convert (OfrontOPT_Node *x, OfrontOPT_Struct typ)
{
  OfrontOPT_Node node = NIL;
  INTEGER f, g;
  LONGINT k;
  REAL r;
  f = (*x)->typ->form;
  g = typ->form;
  if ((INTEGER)(*x)->class == 7) {
    if (__IN(f, 0x4072)) {
      if (g == 9) {
        (*x)->conval->setval = OfrontOPB_IntToSet((INTEGER)(*x)->conval->intval);
      } else if (__IN(g, 0x4072)) {
        if (f > g) {
          OfrontOPB_SetIntType(*x, 1);
          if ((g != 1 && (INTEGER)(*x)->typ->form > g) || (g == 1 && ((*x)->conval->intval < -128 || (*x)->conval->intval > 127))) {
            OfrontOPB_err(203);
            (*x)->conval->intval = 1;
          }
        }
      } else if (__IN(g, 0x0180)) {
        (*x)->conval->realval = (*x)->conval->intval;
        (*x)->conval->intval = -1;
      } else {
        k = (*x)->conval->intval;
        if ((g == 3 && k >= 0) && k <= 255) {
        } else if ((g == 17 && k >= 0) && k <= 65535) {
        } else {
          OfrontOPB_err(220);
        }
      }
    } else if (__IN(f, 0x0180)) {
      if (__IN(g, 0x0180)) {
        OfrontOPB_CheckRealType(g, 203, (*x)->conval);
      } else {
        r = (*x)->conval->realval;
        if (r < -9223372036854775600.0 || r > 9223372036854775600.0) {
          OfrontOPB_err(203);
          r = (REAL)1;
        }
        (*x)->conval->intval = __ENTIERL(r);
        OfrontOPB_SetIntType(*x, 0);
      }
    } else if (f == 9) {
      (*x)->conval->intval = OfrontOPB_SetToInt((*x)->conval->setval);
      (*x)->conval->realval = (REAL)0;
      (*x)->conval->setval = 0x0;
    } else if (g == 10) {
      if (f == 18) {
        OfrontOPB_String16ToString8(*x);
      } else if (__IN(f, 0x020008)) {
        OfrontOPB_CharToString8(*x);
      } else {
        typ = OfrontOPT_undftyp;
      }
    } else if (g == 18) {
      if (f == 10) {
        OfrontOPB_String8ToString16(*x);
      } else if (__IN(f, 0x020008)) {
        OfrontOPB_CharToString16(*x);
      } else {
        typ = OfrontOPT_undftyp;
      }
    }
    (*x)->obj = NIL;
  } else if (((INTEGER)(*x)->class == 11 && (INTEGER)(*x)->subcl == 22) && ((INTEGER)(*x)->left->typ->form < f || f > g)) {
    if ((*x)->left->typ == typ) {
      *x = (*x)->left;
    }
  } else {
    node = OfrontOPT_NewNode(11);
    node->subcl = 22;
    node->left = *x;
    *x = node;
  }
  (*x)->typ = typ;
}

static struct Op__53 {
  struct Op__53 *lnk;
} *Op__53_s;

static void __54 (BYTE op, OfrontOPT_Struct typ, OfrontOPT_Node *x, OfrontOPT_Node y);

static void __54 (BYTE op, OfrontOPT_Struct typ, OfrontOPT_Node *x, OfrontOPT_Node y)
{
  OfrontOPT_Node node = NIL;
  node = OfrontOPT_NewNode(12);
  node->subcl = op;
  node->typ = typ;
  node->left = *x;
  node->right = y;
  *x = node;
}

void OfrontOPB_Op (BYTE op, OfrontOPT_Node *x, OfrontOPT_Node y)
{
  INTEGER f, g;
  OfrontOPT_Node t = NIL;
  OfrontOPT_Node z = NIL;
  OfrontOPT_Struct typ = NIL;
  BOOLEAN do_;
  LONGINT val;
  struct Op__53 _s;
  _s.lnk = Op__53_s;
  Op__53_s = &_s;
  z = *x;
  if ((INTEGER)z->class == 8 || (INTEGER)y->class == 8) {
    OfrontOPB_err(126);
  } else {
    if ((INTEGER)z->typ->form == 14 || (INTEGER)y->typ->form == 14) {
      OfrontOPB_PromoteByte(&z, &y);
    } else {
      OfrontOPB_Promote(&z, &y, op);
    }
    if ((INTEGER)z->class == 7 && (INTEGER)y->class == 7) {
      OfrontOPB_ConstOp(op, z, y);
      z->obj = NIL;
    } else {
      if ((INTEGER)z->class == 9) {
        if ((INTEGER)y->class == 9) {
          OfrontOPB_err(126);
        } else if ((INTEGER)y->typ->form == 15) {
          OfrontOPB_CheckProc(y->typ, z->obj);
        } else {
          OfrontOPB_err(100);
        }
      } else if ((INTEGER)y->class == 9) {
        if ((INTEGER)z->class == 9) {
          OfrontOPB_err(126);
        } else if ((INTEGER)z->typ->form == 15) {
          OfrontOPB_CheckProc(z->typ, y->obj);
        } else {
          OfrontOPB_err(100);
        }
      } else {
        f = z->typ->form;
        g = y->typ->form;
        if (z->typ != y->typ && !(f == g && __IN(f, 0x0203fe))) {
          switch (f) {
            case 3: case 17: 
              if ((INTEGER)z->class == 7) {
                OfrontOPB_CheckString(z, y->typ, 100);
              }
              break;
            case 1: 
              if (__IN(g, 0x41f2)) {
                OfrontOPB_Convert(&z, y->typ);
              } else {
                OfrontOPB_err(100);
              }
              break;
            case 4: 
              if (g == 1) {
                OfrontOPB_Convert(&y, z->typ);
              } else if (__IN(g, 0x41f2)) {
                OfrontOPB_Convert(&z, y->typ);
              } else {
                OfrontOPB_err(100);
              }
              break;
            case 5: 
              if (__IN(g, 0x12)) {
                OfrontOPB_Convert(&y, z->typ);
              } else if (__IN(g, 0x41f2)) {
                OfrontOPB_Convert(&z, y->typ);
              } else {
                OfrontOPB_err(100);
              }
              break;
            case 6: 
              if (__IN(g, 0x4072)) {
                OfrontOPB_Convert(&y, z->typ);
              } else if (__IN(g, 0x0180)) {
                OfrontOPB_Convert(&z, y->typ);
              } else {
                OfrontOPB_err(100);
              }
              break;
            case 7: 
              if (__IN(g, 0x4072)) {
                OfrontOPB_Convert(&y, z->typ);
              } else if (__IN(g, 0x0180)) {
                OfrontOPB_Convert(&z, y->typ);
              } else {
                OfrontOPB_err(100);
              }
              break;
            case 8: 
              if (__IN(g, 0x41f2)) {
                OfrontOPB_Convert(&y, z->typ);
              } else if (__IN(g, 0x0180)) {
                OfrontOPB_Convert(&y, z->typ);
              } else {
                OfrontOPB_err(100);
              }
              break;
            case 11: 
              if (!__IN(g, 0xa000)) {
                OfrontOPB_err(100);
              }
              break;
            case 13: 
              OfrontOPB_CheckPtr(z, y);
              break;
            case 15: 
              if (g != 11) {
                OfrontOPB_err(100);
              }
              break;
            case 10: case 18: 
              break;
            case 16: 
              if ((INTEGER)z->typ->comp == 4) {
                OfrontOPB_err(100);
              }
              break;
            default: 
              OfrontOPB_err(100);
              break;
          }
        }
      }
      typ = z->typ;
      f = typ->form;
      g = y->typ->form;
      switch (op) {
        case 1: 
          do_ = 1;
          if (__IN(f, 0x4072)) {
            if ((INTEGER)z->class == 7) {
              val = z->conval->intval;
              if (val == 1) {
                do_ = 0;
                z = y;
              } else if (val == 0) {
                do_ = 0;
              } else if (OfrontOPB_log(val) == 1) {
                t = y;
                y = z;
                z = t;
                op = 19;
                y->typ = OfrontOPT_bytetyp;
                y->conval->intval = OfrontOPB_exp;
                y->obj = NIL;
              }
            } else if ((INTEGER)y->class == 7) {
              val = y->conval->intval;
              if (val == 1) {
                do_ = 0;
              } else if (val == 0) {
                do_ = 0;
                z = y;
              } else if (OfrontOPB_log(val) == 1) {
                op = 19;
                y->typ = OfrontOPT_bytetyp;
                y->conval->intval = OfrontOPB_exp;
                y->obj = NIL;
              }
            }
          } else if (!__IN(f, 0x0381)) {
            OfrontOPB_err(105);
            typ = OfrontOPT_undftyp;
          }
          if (do_) {
            __54(op, typ, &z, y);
          }
          break;
        case 2: 
          if (__IN(f, 0x4072)) {
            if ((INTEGER)y->class == 7 && y->conval->intval == 0) {
              OfrontOPB_err(205);
            }
            OfrontOPB_Convert(&z, OfrontOPT_realtyp);
            OfrontOPB_Convert(&y, OfrontOPT_realtyp);
            typ = OfrontOPT_realtyp;
          } else if (__IN(f, 0x0180)) {
            if ((INTEGER)y->class == 7 && y->conval->realval == (REAL)0) {
              OfrontOPB_err(205);
            }
          } else if (f != 9 && f != 0) {
            OfrontOPB_err(102);
            typ = OfrontOPT_undftyp;
          }
          __54(op, typ, &z, y);
          break;
        case 3: 
          do_ = 1;
          if (__IN(f, 0x4072)) {
            if ((INTEGER)y->class == 7) {
              val = y->conval->intval;
              if (val == 0) {
                OfrontOPB_err(205);
              } else if (val == 1) {
                do_ = 0;
              } else if (OfrontOPB_log(val) == 1) {
                op = 19;
                y->typ = OfrontOPT_bytetyp;
                y->conval->intval = -((INTEGER)OfrontOPB_exp);
                y->obj = NIL;
              }
            }
          } else if (f != 0) {
            OfrontOPB_err(103);
            typ = OfrontOPT_undftyp;
          }
          if (do_) {
            __54(op, typ, &z, y);
          }
          break;
        case 5: 
          if (!__IN(16, OfrontOPM_opt)) {
            OfrontOPB_err(-303);
          }
          do_ = 1;
          if (__IN(f, 0x4072)) {
            if ((INTEGER)y->class == 7) {
              val = y->conval->intval;
              if (val == 0) {
                OfrontOPB_err(205);
              } else if (val == 1) {
                do_ = 0;
              } else if (OfrontOPB_log(val) == 1) {
                op = 19;
                y->typ = OfrontOPT_bytetyp;
                y->conval->intval = -((INTEGER)OfrontOPB_exp);
                y->obj = NIL;
              }
            }
          } else if (f != 0) {
            OfrontOPB_err(140);
            typ = OfrontOPT_undftyp;
          }
          if (do_) {
            __54(op, typ, &z, y);
          }
          break;
        case 4: 
          if (__IN(f, 0x4072)) {
            if ((INTEGER)y->class == 7) {
              if (y->conval->intval == 0) {
                OfrontOPB_err(205);
              } else if (OfrontOPB_log(y->conval->intval) == 1) {
                op = 20;
                y->conval->intval = __ASH(-1, OfrontOPB_exp, LONGINT);
                y->obj = NIL;
              }
            }
          } else if (f != 0) {
            OfrontOPB_err(104);
            typ = OfrontOPT_undftyp;
          }
          __54(op, typ, &z, y);
          break;
        case 6: 
          if (!__IN(16, OfrontOPM_opt)) {
            OfrontOPB_err(-303);
          }
          if (__IN(f, 0x4072)) {
            if ((INTEGER)y->class == 7) {
              if (y->conval->intval == 0) {
                OfrontOPB_err(205);
              } else if (OfrontOPB_log(y->conval->intval) == 1) {
                op = 20;
                y->conval->intval = __ASH(-1, OfrontOPB_exp, LONGINT);
                y->obj = NIL;
              }
            }
          } else if (f != 0) {
            OfrontOPB_err(141);
            typ = OfrontOPT_undftyp;
          }
          __54(op, typ, &z, y);
          break;
        case 7: 
          if (f == 2) {
            if ((INTEGER)z->class == 7) {
              if (OfrontOPB_IntToBool(z->conval->intval)) {
                z = y;
              }
            } else if ((INTEGER)y->class == 7 && OfrontOPB_IntToBool(y->conval->intval)) {
            } else {
              __54(op, typ, &z, y);
            }
          } else if (f != 0) {
            OfrontOPB_err(94);
            z->typ = OfrontOPT_undftyp;
          }
          break;
        case 8: 
          if (!__IN(f, 0x0447f3)) {
            OfrontOPB_err(105);
            typ = OfrontOPT_undftyp;
          }
          do_ = 1;
          if (__IN(f, 0x4072)) {
            if ((INTEGER)z->class == 7 && z->conval->intval == 0) {
              do_ = 0;
              z = y;
            }
            if ((INTEGER)y->class == 7 && y->conval->intval == 0) {
              do_ = 0;
            }
          } else if (__IN(f, 0x040400)) {
            if (OfrontOPM_Lang != 'C' && OfrontOPM_Lang != '3') {
              OfrontOPB_err(105);
              typ = OfrontOPT_undftyp;
              do_ = 0;
            } else {
              if ((INTEGER)z->class == 7 && z->conval->intval2 == 1) {
                do_ = 0;
                z = y;
              }
              if ((INTEGER)y->class == 7 && y->conval->intval2 == 1) {
                do_ = 0;
              }
              if (do_) {
                if ((INTEGER)z->class == 12) {
                  t = z;
                  while ((INTEGER)t->right->class == 12) {
                    t = t->right;
                  }
                  if ((INTEGER)t->right->class == 7 && (INTEGER)y->class == 7) {
                    OfrontOPB_ConstOp(op, t->right, y);
                    do_ = 0;
                  } else if (((INTEGER)t->right->class == 7 && (INTEGER)y->class == 12) && (INTEGER)y->left->class == 7) {
                    OfrontOPB_ConstOp(op, t->right, y->left);
                    y->left = t->right;
                    t->right = y;
                    do_ = 0;
                  } else {
                    __54(op, typ, &t->right, y);
                    do_ = 0;
                  }
                } else {
                  if (((INTEGER)z->class == 7 && (INTEGER)y->class == 12) && (INTEGER)y->left->class == 7) {
                    OfrontOPB_ConstOp(op, z, y->left);
                    y->left = z;
                    z = y;
                    do_ = 0;
                  }
                }
              }
            }
          }
          if (do_) {
            __54(op, typ, &z, y);
          }
          break;
        case 9: 
          if (!__IN(f, 0x43f3)) {
            OfrontOPB_err(106);
            typ = OfrontOPT_undftyp;
          }
          if ((!__IN(f, 0x4072) || (INTEGER)y->class != 7) || y->conval->intval != 0) {
            __54(op, typ, &z, y);
          }
          break;
        case 36: case 37: 
          if (!__IN(f, 0x0241fb)) {
            OfrontOPB_err(111);
            typ = OfrontOPT_undftyp;
          }
          __54(op, typ, &z, y);
          break;
        case 10: 
          if (f == 2) {
            if ((INTEGER)z->class == 7) {
              if (!OfrontOPB_IntToBool(z->conval->intval)) {
                z = y;
              }
            } else if ((INTEGER)y->class == 7 && !OfrontOPB_IntToBool(y->conval->intval)) {
            } else {
              __54(op, typ, &z, y);
            }
          } else if (f != 0) {
            OfrontOPB_err(95);
            z->typ = OfrontOPT_undftyp;
          }
          break;
        case 11: case 12: case 13: case 14: case 15: 
        case 16: 
          if (__IN(f, 0x040400)) {
            if ((((f == 18 && (INTEGER)z->class == 11) && (INTEGER)z->subcl == 22) && (INTEGER)y->class == 11) && (INTEGER)y->subcl == 22) {
              z = z->left;
              y = y->left;
            } else if (((INTEGER)z->class == 7 && z->conval->intval2 == 1) && (INTEGER)y->class == 3) {
              y = y->left;
              OfrontOPB_Index(&y, OfrontOPB_NewIntConst(0));
              z->typ = y->typ;
              z->conval->intval = 0;
              z->obj = NIL;
            } else if (((INTEGER)y->class == 7 && y->conval->intval2 == 1) && (INTEGER)z->class == 3) {
              z = z->left;
              OfrontOPB_Index(&z, OfrontOPB_NewIntConst(0));
              y->typ = z->typ;
              y->conval->intval = 0;
              y->obj = NIL;
            }
            typ = OfrontOPT_booltyp;
          } else if (__IN(f, 0x0241fb) || ((INTEGER)op <= 12 && __IN(f, 0xaa04))) {
            typ = OfrontOPT_booltyp;
          } else {
            if ((INTEGER)op <= 12) {
              OfrontOPB_err(107);
            } else {
              OfrontOPB_err(108);
            }
            typ = OfrontOPT_undftyp;
          }
          __54(op, typ, &z, y);
          break;
        default: __CASECHK((CHAR*)"OfrontOPB", 335615);
      }
    }
  }
  *x = z;
  Op__53_s = _s.lnk;
}

/*----------------------------------------------------------------------------*/
void OfrontOPB_SetRange (OfrontOPT_Node *x, OfrontOPT_Node y)
{
  LONGINT k, l;
  if ((((INTEGER)(*x)->class == 8 || (INTEGER)(*x)->class == 9) || (INTEGER)y->class == 8) || (INTEGER)y->class == 9) {
    OfrontOPB_err(126);
  } else if (__IN((*x)->typ->form, 0x4072) && __IN(y->typ->form, 0x4072)) {
    if ((INTEGER)(*x)->class == 7) {
      k = (*x)->conval->intval;
      if (0 > k || k > (LONGINT)OfrontOPM_MaxSet) {
        OfrontOPB_err(202);
      }
    }
    if ((INTEGER)y->class == 7) {
      l = y->conval->intval;
      if (0 > l || l > (LONGINT)OfrontOPM_MaxSet) {
        OfrontOPB_err(202);
      }
    }
    if ((INTEGER)(*x)->class == 7 && (INTEGER)y->class == 7) {
      if (k <= l) {
        (*x)->conval->setval = __SETRNG(k, l);
      } else {
        OfrontOPB_err(201);
        (*x)->conval->setval = __SETRNG(l, k);
      }
      (*x)->obj = NIL;
    } else {
      OfrontOPB_BindNodes(10, OfrontOPT_settyp, x, y);
    }
  } else {
    OfrontOPB_err(93);
  }
  (*x)->typ = OfrontOPT_settyp;
}

/*----------------------------------------------------------------------------*/
void OfrontOPB_SetElem (OfrontOPT_Node *x)
{
  LONGINT k;
  if ((INTEGER)(*x)->class == 8 || (INTEGER)(*x)->class == 9) {
    OfrontOPB_err(126);
  } else if (!__IN((*x)->typ->form, 0x4072)) {
    OfrontOPB_err(93);
  } else if ((INTEGER)(*x)->class == 7) {
    k = (*x)->conval->intval;
    if (0 <= k && k <= (LONGINT)OfrontOPM_MaxSet) {
      (*x)->conval->setval = __SETOF(k);
    } else {
      OfrontOPB_err(202);
    }
    (*x)->obj = NIL;
  } else {
    OfrontOPB_BindNodes(11, OfrontOPT_settyp, x, NIL);
    (*x)->subcl = 33;
  }
  (*x)->typ = OfrontOPT_settyp;
}

/*----------------------------------------------------------------------------*/
void OfrontOPB_CheckAssign (OfrontOPT_Struct x, OfrontOPT_Node *ynode)
{
  INTEGER f, g;
  OfrontOPT_Struct y = NIL;
  OfrontOPT_Struct b = NIL;
  y = (*ynode)->typ;
  f = x->form;
  g = y->form;
  if ((INTEGER)(*ynode)->class == 8 || ((INTEGER)(*ynode)->class == 9 && f != 15)) {
    OfrontOPB_err(126);
  }
  switch (f) {
    case 0: case 10: case 18: 
      break;
    case 2: case 9: 
      if (g != f) {
        OfrontOPB_err(113);
      }
      break;
    case 3: case 17: 
      if (!__IN(g, 0x020008) || !OfrontOPT_Includes(f, g)) {
        OfrontOPB_err(113);
      } else if ((INTEGER)(*ynode)->class == 7) {
        OfrontOPB_Convert(ynode, x);
      }
      break;
    case 14: 
      if (__IN(g, 0x4072)) {
        if ((INTEGER)(*ynode)->class == 7) {
          if ((*ynode)->conval->intval < 0 || (*ynode)->conval->intval > 255) {
            OfrontOPB_err(113);
          }
        } else if (g != 14) {
          if (OfrontOPM_Lang == 'C') {
            OfrontOPB_err(113);
          } else {
            OfrontOPB_Convert(ynode, OfrontOPT_ubytetyp);
          }
        }
      } else {
        OfrontOPB_err(113);
      }
      break;
    case 1: 
      if (((__IN(g, 0x4072) && (INTEGER)(*ynode)->class == 7) && -128 <= (*ynode)->conval->intval) && (*ynode)->conval->intval <= 127) {
      } else if (!__IN(g, 0x4002)) {
        OfrontOPB_err(113);
      }
      break;
    case 4: 
      if (((__IN(g, 0x4072) && (INTEGER)(*ynode)->class == 7) && -32768 <= (*ynode)->conval->intval) && (*ynode)->conval->intval <= 32767) {
      } else if (!__IN(g, 0x4012)) {
        OfrontOPB_err(113);
      }
      break;
    case 5: 
      if (((__IN(g, 0x4072) && (INTEGER)(*ynode)->class == 7) && (-2147483647-1) <= (*ynode)->conval->intval) && (*ynode)->conval->intval <= 2147483647) {
      } else if (!__IN(g, 0x4032)) {
        OfrontOPB_err(113);
      }
      break;
    case 6: 
      if (!__IN(g, 0x4072)) {
        OfrontOPB_err(113);
      }
      break;
    case 7: 
      if (((INTEGER)(*ynode)->class == 7 && g == 8) && (OfrontOPM_Lang == 'C' || OfrontOPM_Lang == '3')) {
        if (__ABS((*ynode)->conval->realval) > OfrontOPM_MaxReal32) {
          OfrontOPB_err(203);
          (*ynode)->conval->realval = (REAL)0;
        }
      } else if (OfrontOPM_Lang == '7') {
        if (!__IN(g, 0x0180)) {
          OfrontOPB_err(113);
        }
      } else if (!__IN(g, 0x40f2)) {
        OfrontOPB_err(113);
      }
      break;
    case 8: 
      if (OfrontOPM_Lang == '7') {
        if (!__IN(g, 0x0180)) {
          OfrontOPB_err(113);
        }
      } else if (!__IN(g, 0x41f2)) {
        OfrontOPB_err(113);
      }
      break;
    case 13: 
      b = x->BaseTyp;
      if ((OfrontOPT_Extends(y, x) || g == 11) || (x == OfrontOPT_sysptrtyp && g == 13)) {
      } else if ((INTEGER)b->comp == 3 && (INTEGER)b->sysflag != 0) {
        if ((INTEGER)(*ynode)->class == 7) {
          OfrontOPB_CheckString(*ynode, b, 113);
        } else if (!__IN(y->comp, 0x0c) || !OfrontOPT_EqualType(b->BaseTyp, y->BaseTyp)) {
          OfrontOPB_err(113);
        }
      } else if (((INTEGER)b->sysflag != 0 && (INTEGER)(*ynode)->class == 11) && (INTEGER)(*ynode)->subcl == 31) {
        if ((INTEGER)b->comp == 3 && (INTEGER)(*ynode)->left->class == 7) {
          OfrontOPB_CheckString((*ynode)->left, b, 113);
        } else if (!OfrontOPT_Extends((*ynode)->left->typ, b)) {
          OfrontOPB_err(113);
        }
      } else {
        OfrontOPB_err(113);
      }
      break;
    case 15: 
      if ((INTEGER)(*ynode)->class == 9) {
        OfrontOPB_CheckProc(x, (*ynode)->obj);
      } else if (OfrontOPT_EqualType(x, y) || g == 11) {
      } else {
        OfrontOPB_err(113);
      }
      break;
    case 12: case 11: 
      OfrontOPB_err(113);
      break;
    case 16: 
      x->pvused = 1;
      if ((INTEGER)x->comp == 4) {
        if (OfrontOPM_Lang != 'C') {
          if (x == y) {
          } else if ((INTEGER)y->comp == 4) {
            b = y->BaseTyp;
            while ((b != NIL && b != x) && b != OfrontOPT_undftyp) {
              b = b->BaseTyp;
            }
            if (b == NIL) {
              OfrontOPB_err(113);
            }
          } else {
            OfrontOPB_err(113);
          }
        } else if (!OfrontOPT_EqualType(x, y) || (INTEGER)x->attribute != 0) {
          OfrontOPB_err(113);
        }
      } else if (__IN(g, 0x060408)) {
        if ((INTEGER)x->BaseTyp->form == 17 && g == 10) {
          OfrontOPB_Convert(ynode, OfrontOPT_string16typ);
        } else {
          OfrontOPB_CheckString(*ynode, x, 113);
        }
        if (((INTEGER)x->comp == 2 && (INTEGER)(*ynode)->class == 7) && (*ynode)->conval->intval2 > x->n) {
          OfrontOPB_err(114);
        }
      } else if ((INTEGER)x->comp == 2) {
        if ((INTEGER)(*ynode)->class == 7 && g == 3) {
          OfrontOPB_CharToString8(*ynode);
          y = (*ynode)->typ;
          g = 10;
        } else if ((INTEGER)(*ynode)->class == 7 && g == 17) {
          OfrontOPB_CharToString16(*ynode);
          y = (*ynode)->typ;
          g = 18;
        }
        if (x == y || ((((OfrontOPM_Lang == '7' && g == 16) && (INTEGER)y->comp == 2) && y->n == x->n) && y->BaseTyp == x->BaseTyp)) {
        } else if (((OfrontOPM_Lang == '7' && g == 16) && (INTEGER)y->comp == 3) && ((y->BaseTyp == OfrontOPT_char8typ && x->BaseTyp == OfrontOPT_char8typ) || (y->BaseTyp == OfrontOPT_char16typ && x->BaseTyp == OfrontOPT_char16typ))) {
          OfrontOPB_StrDeref(ynode);
        } else if ((g == 10 && x->BaseTyp == OfrontOPT_char8typ) || (g == 18 && x->BaseTyp == OfrontOPT_char16typ)) {
          if ((*ynode)->conval->intval2 > x->n) {
            OfrontOPB_err(114);
          }
        } else if ((((((g == 16 && (INTEGER)y->comp == 2) && ((y->BaseTyp == OfrontOPT_char8typ && x->BaseTyp == OfrontOPT_char8typ) || (y->BaseTyp == OfrontOPT_char16typ && x->BaseTyp == OfrontOPT_char16typ))) && (*ynode)->left != NIL) && (*ynode)->left->obj != NIL) && (*ynode)->left->obj->conval != NIL) && (*ynode)->left->obj->conval->arr != NIL) {
          if (y->n > x->n) {
            OfrontOPB_err(114);
          }
        } else {
          OfrontOPB_err(113);
        }
      } else {
        OfrontOPB_err(113);
      }
      break;
    default: __CASECHK((CHAR*)"OfrontOPB", 376831);
  }
  if ((((INTEGER)(*ynode)->class == 7 && g < f) && __IN(g, 0xf2)) && __IN(f, 0x01f0)) {
    OfrontOPB_Convert(ynode, x);
  }
}

/*----------------------------------------------------------------------------*/
static void OfrontOPB_AssignString (OfrontOPT_Node *x, OfrontOPT_Node str)
{
  __ASSERT((INTEGER)str->class == 7 && __IN(str->typ->form, 0x040400), 0, (CHAR*)"OfrontOPB", 379206);
  if (__IN((*x)->typ->comp, 0x0c) && str->conval->intval2 == 1) {
    OfrontOPB_Index(x, OfrontOPB_NewIntConst(0));
    str->typ = (*x)->typ;
    str->conval->intval = 0;
    str->obj = NIL;
  }
  OfrontOPB_BindNodes(19, OfrontOPT_notyp, x, str);
  (*x)->subcl = 0;
}

static void OfrontOPB_CheckLeaf (OfrontOPT_Node x, BOOLEAN dynArrToo)
{
}

void OfrontOPB_StPar0 (OfrontOPT_Node *par0, SHORTINT fctno)
{
  INTEGER f;
  OfrontOPT_Struct typ = NIL;
  OfrontOPT_Node x = NIL;
  x = *par0;
  f = x->typ->form;
  switch (fctno) {
    case 0: 
      if (__IN(f, 0x4072) && (INTEGER)x->class == 7) {
        if (0 <= x->conval->intval && x->conval->intval <= 255) {
          OfrontOPB_BindNodes(28, OfrontOPT_notyp, &x, x);
        } else {
          OfrontOPB_err(218);
        }
      } else {
        OfrontOPB_err(69);
      }
      x->typ = OfrontOPT_notyp;
      break;
    case 1: 
      typ = OfrontOPT_notyp;
      if (OfrontOPB_NotVar(x)) {
        OfrontOPB_err(112);
      } else if (f == 13) {
        if (x->readonly) {
          OfrontOPB_err(76);
        }
        f = x->typ->BaseTyp->comp;
        if (__IN(f, 0x1c)) {
          if (f == 3) {
            typ = x->typ->BaseTyp;
          }
          OfrontOPB_BindNodes(19, OfrontOPT_notyp, &x, NIL);
          x->subcl = 1;
        } else {
          OfrontOPB_err(111);
        }
      } else {
        OfrontOPB_err(111);
      }
      x->typ = typ;
      break;
    case 2: 
      OfrontOPB_MOp(23, &x);
      break;
    case 3: 
      OfrontOPB_MOp(24, &x);
      break;
    case 4: 
      if ((INTEGER)x->class == 8 || (INTEGER)x->class == 9) {
        OfrontOPB_err(126);
      } else if (f == 2) {
        if (OfrontOPM_Lang == '3') {
          OfrontOPB_Convert(&x, OfrontOPT_bytetyp);
        } else if (OfrontOPM_Lang == '7') {
          OfrontOPB_Convert(&x, OfrontOPT_inttyp);
        } else {
          OfrontOPB_err(111);
        }
      } else if (f == 3) {
        if (OfrontOPM_Lang == '7' && (INTEGER)OfrontOPM_AdrSize != 2) {
          OfrontOPB_Convert(&x, OfrontOPT_inttyp);
        } else {
          OfrontOPB_Convert(&x, OfrontOPT_sinttyp);
        }
      } else if (f == 17) {
        OfrontOPB_Convert(&x, OfrontOPT_inttyp);
      } else if ((f == 9 && OfrontOPM_Lang != '1') && OfrontOPM_Lang != '2') {
        if (OfrontOPM_Lang != '7' && (INTEGER)OfrontOPM_SetSize == 1) {
          OfrontOPB_Convert(&x, OfrontOPT_bytetyp);
        } else {
          OfrontOPB_Convert(&x, OfrontOPT_inttyp);
        }
      } else {
        OfrontOPB_err(111);
      }
      break;
    case 12: 
      if ((INTEGER)x->class == 8 || (INTEGER)x->class == 9) {
        OfrontOPB_err(126);
      } else if (__IN(f, 0x4072)) {
        OfrontOPB_Convert(&x, OfrontOPT_settyp);
      } else {
        OfrontOPB_err(111);
      }
      break;
    case 5: 
      if ((INTEGER)x->class == 8 || (INTEGER)x->class == 9) {
        OfrontOPB_err(126);
      } else if (__IN(f, 0x0180)) {
        if ((OfrontOPM_Lang == 'C' || OfrontOPM_Lang == '3') && (INTEGER)OfrontOPM_AdrSize != 2) {
          OfrontOPB_Convert(&x, OfrontOPT_linttyp);
        } else {
          OfrontOPB_Convert(&x, OfrontOPT_inttyp);
        }
      } else {
        OfrontOPB_err(111);
        x->typ = OfrontOPT_inttyp;
      }
      break;
    case 13: 
      if ((INTEGER)x->class == 8 || (INTEGER)x->class == 9) {
        OfrontOPB_err(126);
      } else if (__IN(f, 0x4072)) {
        OfrontOPB_Convert(&x, OfrontOPT_realtyp);
      } else {
        OfrontOPB_err(111);
      }
      break;
    case 6: 
      OfrontOPB_MOp(25, &x);
      break;
    case 7: 
      if ((INTEGER)x->class == 8) {
        switch (f) {
          case 2: 
            x = OfrontOPB_NewBoolConst(0);
            break;
          case 3: 
            x = OfrontOPB_NewIntConst(0);
            x->typ = OfrontOPT_char8typ;
            break;
          case 17: 
            x = OfrontOPB_NewIntConst(0);
            x->typ = OfrontOPT_char16typ;
            break;
          case 14: 
            x = OfrontOPB_NewIntConst(0);
            break;
          case 1: 
            x = OfrontOPB_NewIntConst(-128);
            break;
          case 4: 
            x = OfrontOPB_NewIntConst(-32768);
            break;
          case 5: 
            x = OfrontOPB_NewIntConst((-2147483647-1));
            break;
          case 6: 
            x = OfrontOPB_NewIntConst((-9223372036854775807LL-1));
            break;
          case 9: 
            x = OfrontOPB_NewIntConst(0);
            x->typ = OfrontOPT_inttyp;
            break;
          case 7: 
            x = OfrontOPB_NewRealConst(OfrontOPM_MinReal32, OfrontOPT_realtyp);
            break;
          case 8: 
            x = OfrontOPB_NewRealConst(OfrontOPM_MinReal64, OfrontOPT_lrltyp);
            break;
          default: 
            OfrontOPB_err(111);
            break;
        }
        x->hint = 1;
      } else if (OfrontOPM_Lang == 'C' || OfrontOPM_Lang == '3') {
        if (!__IN(f, 0x0241fa)) {
          OfrontOPB_err(111);
        }
      } else {
        OfrontOPB_err(110);
      }
      break;
    case 8: 
      if ((INTEGER)x->class == 8) {
        switch (f) {
          case 2: 
            x = OfrontOPB_NewBoolConst(1);
            break;
          case 3: 
            x = OfrontOPB_NewIntConst(255);
            x->typ = OfrontOPT_char8typ;
            break;
          case 17: 
            x = OfrontOPB_NewIntConst(65535);
            x->typ = OfrontOPT_char16typ;
            break;
          case 14: 
            x = OfrontOPB_NewIntConst(255);
            break;
          case 1: 
            x = OfrontOPB_NewIntConst(127);
            break;
          case 4: 
            x = OfrontOPB_NewIntConst(32767);
            break;
          case 5: 
            x = OfrontOPB_NewIntConst(2147483647);
            break;
          case 6: 
            x = OfrontOPB_NewIntConst(9223372036854775807LL);
            break;
          case 9: 
            x = OfrontOPB_NewIntConst(OfrontOPM_MaxSet);
            x->typ = OfrontOPT_inttyp;
            break;
          case 7: 
            x = OfrontOPB_NewRealConst(OfrontOPM_MaxReal32, OfrontOPT_realtyp);
            break;
          case 8: 
            x = OfrontOPB_NewRealConst(OfrontOPM_MaxReal64, OfrontOPT_lrltyp);
            break;
          default: 
            OfrontOPB_err(111);
            break;
        }
        x->hint = 1;
      } else if (OfrontOPM_Lang == 'C' || OfrontOPM_Lang == '3') {
        if (!__IN(f, 0x0241fa)) {
          OfrontOPB_err(111);
        }
      } else {
        OfrontOPB_err(110);
      }
      break;
    case 9: 
      if ((INTEGER)x->class == 8 || (INTEGER)x->class == 9) {
        OfrontOPB_err(126);
      } else if (__IN(f, 0x4073)) {
        OfrontOPB_Convert(&x, OfrontOPT_char8typ);
      } else {
        OfrontOPB_err(111);
        x->typ = OfrontOPT_char8typ;
      }
      break;
    case 14: 
      if ((INTEGER)x->class == 8 || (INTEGER)x->class == 9) {
        OfrontOPB_err(126);
      } else if (__IN(f, 0x4073)) {
        OfrontOPB_Convert(&x, OfrontOPT_char16typ);
      } else {
        OfrontOPB_err(111);
        x->typ = OfrontOPT_char16typ;
      }
      break;
    case 10: 
      if ((INTEGER)x->class == 8 || (INTEGER)x->class == 9) {
        OfrontOPB_err(126);
      } else {
        if ((OfrontOPM_Lang == 'C' && __IN(x->typ->comp, 0x0c)) && __IN(x->typ->BaseTyp->form, 0x020008)) {
          OfrontOPB_StrDeref(&x);
          f = x->typ->form;
        }
        if (__IN(f, 0x4010)) {
          OfrontOPB_Convert(&x, OfrontOPT_bytetyp);
        } else if (f == 5) {
          OfrontOPB_Convert(&x, OfrontOPT_sinttyp);
        } else if (f == 6) {
          OfrontOPB_Convert(&x, OfrontOPT_inttyp);
        } else if (f == 8) {
          OfrontOPB_Convert(&x, OfrontOPT_realtyp);
        } else if (f == 17) {
          OfrontOPB_Convert(&x, OfrontOPT_char8typ);
        } else if (f == 18) {
          OfrontOPB_Convert(&x, OfrontOPT_string8typ);
        } else {
          OfrontOPB_err(111);
        }
      }
      break;
    case 26: 
      if ((INTEGER)x->class == 8 || (INTEGER)x->class == 9) {
        OfrontOPB_err(126);
      } else {
        if (__IN(f, 0x4072)) {
          OfrontOPB_Convert(&x, OfrontOPT_ubytetyp);
        } else {
          OfrontOPB_err(111);
        }
      }
      break;
    case 11: 
      if ((INTEGER)x->class == 8 || (INTEGER)x->class == 9) {
        OfrontOPB_err(126);
      } else {
        if ((OfrontOPM_Lang == 'C' && __IN(x->typ->comp, 0x0c)) && __IN(x->typ->BaseTyp->form, 0x020008)) {
          OfrontOPB_StrDeref(&x);
          f = x->typ->form;
        }
        if (f == 1) {
          OfrontOPB_Convert(&x, OfrontOPT_sinttyp);
        } else if (__IN(f, 0x4010)) {
          OfrontOPB_Convert(&x, OfrontOPT_inttyp);
        } else if (f == 5) {
          OfrontOPB_Convert(&x, OfrontOPT_linttyp);
        } else if (f == 7) {
          OfrontOPB_Convert(&x, OfrontOPT_lrltyp);
        } else if (f == 3) {
          OfrontOPB_Convert(&x, OfrontOPT_char16typ);
        } else if (f == 10) {
          OfrontOPB_Convert(&x, OfrontOPT_string16typ);
        } else {
          OfrontOPB_err(111);
        }
      }
      break;
    case 19: case 20: 
      if (OfrontOPB_NotVar(x)) {
        OfrontOPB_err(112);
      } else if (!__IN(f, 0x4072)) {
        OfrontOPB_err(111);
      } else if (x->readonly) {
        OfrontOPB_err(76);
      }
      break;
    case 21: case 22: 
      if (OfrontOPB_NotVar(x)) {
        OfrontOPB_err(112);
      } else if (x->typ != OfrontOPT_settyp) {
        OfrontOPB_err(111);
        x->typ = OfrontOPT_settyp;
      } else if (x->readonly) {
        OfrontOPB_err(76);
      }
      break;
    case 23: 
      if ((INTEGER)x->class == 9) {
        OfrontOPB_err(126);
      } else {
        if (OfrontOPM_Lang == 'C' && (INTEGER)x->typ->form == 13) {
          OfrontOPB_DeRef(&x);
        }
        if ((INTEGER)x->class == 7) {
          if ((INTEGER)x->typ->form == 3) {
            OfrontOPB_CharToString8(x);
          } else if ((INTEGER)x->typ->form == 17) {
            OfrontOPB_CharToString16(x);
          }
        }
        if (!__IN(x->typ->comp, 0x0c) && ((OfrontOPM_Lang != 'C' && OfrontOPM_Lang != '3') || !__IN(x->typ->form, 0x040400))) {
          OfrontOPB_err(131);
        }
      }
      break;
    case 24: 
      if ((INTEGER)x->class == 7 && f == 3) {
        OfrontOPB_CharToString8(x);
        f = 10;
      } else if ((INTEGER)x->class == 7 && f == 17) {
        OfrontOPB_CharToString16(x);
        f = 18;
      }
      if ((INTEGER)x->class == 8 || (INTEGER)x->class == 9) {
        OfrontOPB_err(126);
      } else if ((!__IN(x->typ->comp, 0x0c) || !__IN(x->typ->BaseTyp->form, 0x020008)) && !__IN(f, 0x040400)) {
        OfrontOPB_err(111);
      }
      break;
    case 25: case 16: case 17: case 18: 
      if ((INTEGER)x->class == 8 || (INTEGER)x->class == 9) {
        OfrontOPB_err(126);
      } else if (__IN(f, 0x4072)) {
        if (f < 5) {
          OfrontOPB_Convert(&x, OfrontOPT_inttyp);
        }
      } else {
        OfrontOPB_err(111);
        x->typ = OfrontOPT_inttyp;
      }
      break;
    case 27: 
      OfrontOPB_CheckLeaf(x, 0);
      OfrontOPB_MOp(31, &x);
      break;
    case 39: 
      OfrontOPB_CheckLeaf(x, 0);
      if ((INTEGER)x->class == 8) {
        if ((INTEGER)x->typ->form == 13) {
          x = OfrontOPB_NewLeaf(x->typ->BaseTyp->strobj);
        }
        if ((INTEGER)x->typ->comp != 4) {
          OfrontOPB_err(111);
        }
        OfrontOPB_MOp(31, &x);
      } else {
        if ((INTEGER)x->typ->form == 13) {
          OfrontOPB_DeRef(&x);
        }
        if ((INTEGER)x->typ->comp != 4) {
          OfrontOPB_err(111);
        }
        OfrontOPB_MOp(39, &x);
      }
      break;
    case 15: 
      if ((INTEGER)x->class != 8) {
        OfrontOPB_err(110);
        x = OfrontOPB_NewIntConst(1);
      } else if (__IN(f, 0x02e3fe) || __IN(x->typ->comp, 0x14)) {
        (*OfrontOPB_typSize)(x->typ);
        x->typ->pvused = 1;
        x = OfrontOPB_NewIntConst(x->typ->size);
      } else {
        OfrontOPB_err(111);
        x = OfrontOPB_NewIntConst(1);
      }
      break;
    case 40: case 41: 
      if ((INTEGER)x->class == 8 || (INTEGER)x->class == 9) {
        OfrontOPB_err(126);
      } else {
        switch (OfrontOPM_AdrSize) {
          case 2: 
            if (__IN(f, 0x4002)) {
              OfrontOPB_Convert(&x, OfrontOPT_sinttyp);
            } else if (f != 4) {
              OfrontOPB_err(111);
            }
            break;
          case 4: 
            if (__IN(f, 0x4012)) {
              OfrontOPB_Convert(&x, OfrontOPT_inttyp);
            } else if (f != 5) {
              OfrontOPB_err(111);
            }
            break;
          default: 
            if (__IN(f, 0x4032)) {
              OfrontOPB_Convert(&x, OfrontOPT_linttyp);
            } else if (f != 6) {
              OfrontOPB_err(111);
            }
            break;
        }
      }
      break;
    case 28: case 29: 
      if ((INTEGER)x->class == 8 || (INTEGER)x->class == 9) {
        OfrontOPB_err(126);
      } else if (!__IN(f, 0x02427a)) {
        OfrontOPB_err(111);
      }
      break;
    case 30: case 31: case 34: case 37: 
      if ((INTEGER)x->class == 8 || (INTEGER)x->class == 9) {
        OfrontOPB_err(126);
      } else if ((INTEGER)OfrontOPM_AdrSize == 4) {
        if ((INTEGER)x->class == 7 && __IN(f, 0x12)) {
          OfrontOPB_Convert(&x, OfrontOPT_inttyp);
        } else if (!__IN(f, 0x2020)) {
          OfrontOPB_err(111);
          x->typ = OfrontOPT_inttyp;
        }
      } else if ((INTEGER)OfrontOPM_AdrSize == 2) {
        if ((INTEGER)x->class == 7 && f == 1) {
          OfrontOPB_Convert(&x, OfrontOPT_sinttyp);
        } else if (!__IN(f, 0x2010)) {
          OfrontOPB_err(111);
          x->typ = OfrontOPT_sinttyp;
        }
      } else {
        if ((INTEGER)x->class == 7 && __IN(f, 0x32)) {
          OfrontOPB_Convert(&x, OfrontOPT_linttyp);
        } else if (!__IN(f, 0x2040)) {
          OfrontOPB_err(111);
          x->typ = OfrontOPT_linttyp;
        }
      }
      break;
    case 35: 
      if ((INTEGER)x->class != 8) {
        OfrontOPB_err(110);
      } else if (__IN(f, 0x041c01) || (INTEGER)x->typ->comp == 3) {
        OfrontOPB_err(111);
      }
      break;
    case 36: 
      if (OfrontOPB_NotVar(x)) {
        OfrontOPB_err(112);
      } else if (f == 13) {
      } else {
        OfrontOPB_err(111);
      }
      break;
    case 38: 
      if ((INTEGER)x->class == 8 || (INTEGER)x->class == 9) {
        OfrontOPB_err(126);
        x = OfrontOPB_NewBoolConst(0);
      } else if (f != 2) {
        OfrontOPB_err(120);
        x = OfrontOPB_NewBoolConst(0);
      } else {
        OfrontOPB_MOp(35, &x);
      }
      break;
    case 32: case 33: 
      if (OfrontOPB_NotVar(x)) {
        OfrontOPB_err(112);
      } else if (f != 7) {
        OfrontOPB_err(111);
      } else if (x->readonly) {
        OfrontOPB_err(76);
      }
      break;
    default: __CASECHK((CHAR*)"OfrontOPB", 452607);
  }
  *par0 = x;
}

/*----------------------------------------------------------------------------*/
static struct StPar1__70 {
  struct StPar1__70 *lnk;
} *StPar1__70_s;

static OfrontOPT_Node __71 (BYTE class, BYTE subcl, OfrontOPT_Node left, OfrontOPT_Node right);

static OfrontOPT_Node __71 (BYTE class, BYTE subcl, OfrontOPT_Node left, OfrontOPT_Node right)
{
  OfrontOPT_Node node = NIL;
  node = OfrontOPT_NewNode(class);
  node->subcl = subcl;
  node->left = left;
  node->right = right;
  return node;
}

void OfrontOPB_StPar1 (OfrontOPT_Node *par0, OfrontOPT_Node x, BYTE fctno)
{
  OfrontOPT_Struct typ = NIL;
  OfrontOPT_Node p = NIL;
  OfrontOPT_Node t = NIL;
  LONGINT maxInt;
  INTEGER f, L, maxExp;
  struct StPar1__70 _s;
  _s.lnk = StPar1__70_s;
  StPar1__70_s = &_s;
  p = *par0;
  f = x->typ->form;
  switch (fctno) {
    case 19: case 20: 
      if ((INTEGER)x->class == 8 || (INTEGER)x->class == 9) {
        OfrontOPB_err(126);
        p->typ = OfrontOPT_notyp;
      } else {
        if (x->typ != p->typ) {
          if ((INTEGER)x->class == 7 && __IN(f, 0x4072)) {
            OfrontOPB_Convert(&x, p->typ);
          } else if (!__IN(f, 0x4072)) {
            OfrontOPB_err(111);
          } else if (x->typ->size > p->typ->size) {
            OfrontOPB_err(-301);
          }
        }
        p = __71(19, fctno, p, x);
        p->typ = OfrontOPT_notyp;
      }
      break;
    case 21: case 22: 
      if ((INTEGER)x->class == 8 || (INTEGER)x->class == 9) {
        OfrontOPB_err(126);
      } else if (__IN(f, 0x4072)) {
        if ((INTEGER)x->class == 7 && (0 > x->conval->intval || x->conval->intval > (LONGINT)OfrontOPM_MaxSet)) {
          OfrontOPB_err(202);
        }
        p = __71(19, fctno, p, x);
      } else {
        OfrontOPB_err(111);
      }
      p->typ = OfrontOPT_notyp;
      break;
    case 23: 
      if (__IN(f, 0x4072) && (INTEGER)x->class == 7) {
        L = (INTEGER)x->conval->intval;
        typ = p->typ;
        while (L > 0 && __IN(typ->comp, 0x0c)) {
          typ = typ->BaseTyp;
          L -= 1;
        }
        if (L != 0 || !__IN(typ->comp, 0x0c)) {
          OfrontOPB_err(132);
        } else {
          x->obj = NIL;
          if ((INTEGER)typ->comp == 3) {
            while ((INTEGER)p->class == 4) {
              p = p->left;
              x->conval->intval += 1;
            }
            p = __71(12, 21, p, x);
            switch (OfrontOPM_IndexSize) {
              case 2: 
                p->typ = OfrontOPT_sinttyp;
                break;
              case 4: 
                p->typ = OfrontOPT_inttyp;
                break;
              default: 
                p->typ = OfrontOPT_linttyp;
                break;
            }
          } else {
            p = x;
            p->conval->intval = typ->n;
            OfrontOPB_SetIntType(p, 0);
          }
        }
      } else {
        OfrontOPB_err(69);
      }
      break;
    case 24: 
      if (OfrontOPB_NotVar(x)) {
        OfrontOPB_err(112);
      } else if (x->readonly) {
        OfrontOPB_err(76);
      } else if (((INTEGER)x->class == 3 && (INTEGER)x->typ->sysflag != 0) && x->typ->n == 0) {
        OfrontOPB_err(137);
      } else {
        OfrontOPB_CheckString(p, x->typ, 111);
        t = x;
        x = p;
        p = t;
        if ((((INTEGER)x->class == 7 && __IN(x->typ->form, 0x040400)) && (INTEGER)p->typ->comp == 2) && x->conval->intval2 <= p->typ->n) {
          OfrontOPB_AssignString(&p, x);
        } else {
          p = __71(19, 24, p, x);
        }
      }
      p->typ = OfrontOPT_notyp;
      break;
    case 25: 
      if ((INTEGER)x->class == 8 || (INTEGER)x->class == 9) {
        OfrontOPB_err(126);
      } else if (__IN(f, 0x4072)) {
        if ((INTEGER)p->typ->form == 6) {
          maxInt = 9223372036854775807LL;
        } else {
          maxInt = 2147483647;
        }
        maxExp = (INTEGER)OfrontOPB_log(__ASHR(maxInt, 1, LONGINT) + 1);
        maxExp = OfrontOPB_exp;
        if ((INTEGER)x->class == 7 && ((LONGINT)(-maxExp - 1) > x->conval->intval || x->conval->intval > (LONGINT)maxExp)) {
          OfrontOPB_err(208);
        } else if ((INTEGER)p->class == 7 && (INTEGER)x->class == 7) {
          if (x->conval->intval >= 0) {
            if (__ABS(p->conval->intval) <= __DIVFL(maxInt, __ASH(1, (INTEGER)x->conval->intval, LONGINT))) {
              p->conval->intval = __ASH(p->conval->intval, (INTEGER)x->conval->intval, LONGINT);
            } else {
              OfrontOPB_err(208);
              p->conval->intval = 1;
            }
          } else {
            p->conval->intval = __ASH(p->conval->intval, (INTEGER)x->conval->intval, LONGINT);
          }
          p->obj = NIL;
        } else {
          if (f == 6) {
            OfrontOPB_Convert(&x, OfrontOPT_inttyp);
          }
          typ = p->typ;
          p = __71(12, 19, p, x);
          p->typ = typ;
        }
      } else {
        OfrontOPB_err(111);
      }
      break;
    case 16: 
      if ((INTEGER)x->class == 8 || (INTEGER)x->class == 9) {
        OfrontOPB_err(126);
      } else if (__IN(f, 0x4072)) {
        if ((INTEGER)p->typ->form == 6) {
          maxExp = 63;
        } else {
          maxExp = 31;
        }
        if ((INTEGER)x->class == 7 && (x->conval->intval < 0 || x->conval->intval > (LONGINT)maxExp)) {
          OfrontOPB_err(208);
        } else if ((INTEGER)p->class == 7 && (INTEGER)x->class == 7) {
          p->conval->intval = __ASH(p->conval->intval, (INTEGER)(-x->conval->intval), LONGINT);
          p->obj = NIL;
        } else {
          if (f == 6) {
            OfrontOPB_err(113);
            OfrontOPB_Convert(&x, OfrontOPT_inttyp);
          }
          typ = p->typ;
          p = __71(12, 26, p, x);
          p->typ = typ;
        }
      } else {
        OfrontOPB_err(111);
      }
      break;
    case 17: 
      if ((INTEGER)x->class == 8 || (INTEGER)x->class == 9) {
        OfrontOPB_err(126);
      } else if (__IN(f, 0x4072)) {
        if ((INTEGER)p->typ->form == 6) {
          maxExp = 63;
        } else {
          maxExp = 31;
        }
        if ((INTEGER)x->class == 7 && (x->conval->intval < 0 || x->conval->intval > (LONGINT)maxExp)) {
          OfrontOPB_err(210);
        } else if ((INTEGER)p->class == 7 && (INTEGER)x->class == 7) {
          if ((INTEGER)p->typ->form == 6) {
            maxInt = p->conval->intval;
            p->conval->intval = OfrontOPM_Lsl(maxInt, (INTEGER)x->conval->intval);
            if (OfrontOPM_Lsr((INTEGER)p->conval->intval, (INTEGER)x->conval->intval) != maxInt) {
              OfrontOPB_err(-210);
            }
          } else {
            maxExp = (INTEGER)p->conval->intval;
            p->conval->intval = __LSH(maxExp, (INTEGER)x->conval->intval, INTEGER);
            if (__LSH((INTEGER)p->conval->intval, -((INTEGER)x->conval->intval), INTEGER) != maxExp) {
              OfrontOPB_err(-210);
            }
          }
          p->obj = NIL;
        } else {
          if (f == 6) {
            OfrontOPB_err(113);
            OfrontOPB_Convert(&x, OfrontOPT_inttyp);
          }
          typ = p->typ;
          p = __71(12, 27, p, x);
          p->typ = typ;
        }
      } else {
        OfrontOPB_err(111);
      }
      break;
    case 18: 
      if ((INTEGER)x->class == 8 || (INTEGER)x->class == 9) {
        OfrontOPB_err(126);
      } else if (__IN(f, 0x4072)) {
        if ((INTEGER)p->typ->form == 6) {
          maxExp = 63;
        } else {
          maxExp = 31;
        }
        if ((INTEGER)x->class == 7 && (x->conval->intval < 0 || x->conval->intval > (LONGINT)maxExp)) {
          OfrontOPB_err(210);
        } else if ((INTEGER)p->class == 7 && (INTEGER)x->class == 7) {
          maxExp = (INTEGER)x->conval->intval;
          if ((INTEGER)p->typ->form == 6) {
            p->conval->intval = OfrontOPM_Ror(p->conval->intval, maxExp);
          } else {
            p->conval->intval = __ROT((INTEGER)p->conval->intval, -maxExp, INTEGER);
          }
          p->obj = NIL;
        } else {
          if (f == 6) {
            OfrontOPB_err(113);
            OfrontOPB_Convert(&x, OfrontOPT_inttyp);
          }
          typ = p->typ;
          p = __71(12, 28, p, x);
          p->typ = typ;
        }
      } else {
        OfrontOPB_err(111);
      }
      break;
    case 7: 
      if ((OfrontOPM_Lang == 'C' || OfrontOPM_Lang == '3') && (INTEGER)p->class != 8) {
        OfrontOPB_Op(36, &p, x);
      } else {
        OfrontOPB_err(64);
      }
      break;
    case 8: 
      if ((OfrontOPM_Lang == 'C' || OfrontOPM_Lang == '3') && (INTEGER)p->class != 8) {
        OfrontOPB_Op(37, &p, x);
      } else {
        OfrontOPB_err(64);
      }
      break;
    case 1: 
      if ((INTEGER)x->class == 8 || (INTEGER)x->class == 9) {
        OfrontOPB_err(126);
      } else if ((INTEGER)p->typ->comp == 3) {
        if (__IN(f, 0x4072)) {
          if ((INTEGER)x->class == 7 && (x->conval->intval <= 0 || x->conval->intval > OfrontOPM_MaxIndex)) {
            OfrontOPB_err(63);
          }
        } else {
          OfrontOPB_err(111);
        }
        p->right = x;
        p->typ = p->typ->BaseTyp;
      } else {
        OfrontOPB_err(64);
      }
      break;
    case 40: case 41: 
      if ((INTEGER)x->class == 8 || (INTEGER)x->class == 9) {
        OfrontOPB_err(126);
      } else {
        switch (OfrontOPM_AdrSize) {
          case 2: 
            if (__IN(f, 0x4002)) {
              OfrontOPB_Convert(&x, OfrontOPT_sinttyp);
            } else if (f != 4) {
              OfrontOPB_err(111);
            }
            break;
          case 4: 
            if (__IN(f, 0x4012)) {
              OfrontOPB_Convert(&x, OfrontOPT_inttyp);
            } else if (f != 5) {
              OfrontOPB_err(111);
            }
            break;
          default: 
            if (__IN(f, 0x4032)) {
              OfrontOPB_Convert(&x, OfrontOPT_linttyp);
            } else if (f != 6) {
              OfrontOPB_err(111);
            }
            break;
        }
        p = __71(12, fctno, p, x);
        p->typ = OfrontOPT_undftyp;
      }
      break;
    case 28: case 29: 
      if ((INTEGER)x->class == 8 || (INTEGER)x->class == 9) {
        OfrontOPB_err(126);
      } else if (!__IN(f, 0x4072)) {
        OfrontOPB_err(111);
      } else {
        if ((INTEGER)fctno == 28) {
          p = __71(12, 29, p, x);
        } else {
          p = __71(12, 30, p, x);
        }
        p->typ = p->left->typ;
      }
      break;
    case 30: case 31: 
      if ((INTEGER)x->class == 8 || (INTEGER)x->class == 9) {
        OfrontOPB_err(126);
      } else if (__IN(f, 0x02ebff)) {
        if ((INTEGER)fctno == 30) {
          if (OfrontOPB_NotVar(x)) {
            OfrontOPB_err(112);
          }
          t = x;
          x = p;
          p = t;
        }
        p = __71(19, fctno, p, x);
      } else {
        OfrontOPB_err(111);
      }
      p->typ = OfrontOPT_notyp;
      break;
    case 34: 
      if ((INTEGER)x->class == 8 || (INTEGER)x->class == 9) {
        OfrontOPB_err(126);
      } else if (__IN(f, 0x4072)) {
        p = __71(12, 33, p, x);
      } else {
        OfrontOPB_err(111);
      }
      p->typ = OfrontOPT_booltyp;
      break;
    case 35: 
      if ((((INTEGER)x->class == 8 || (INTEGER)x->class == 9) || __IN(f, 0x041401)) || ((INTEGER)x->typ->comp == 3 && (INTEGER)x->typ->sysflag == 0)) {
        OfrontOPB_err(126);
      }
      (*OfrontOPT_typSize)(x->typ);
      (*OfrontOPT_typSize)(p->typ);
      if ((INTEGER)x->class != 7 && x->typ->size < p->typ->size) {
        OfrontOPB_err(-308);
      }
      if (((INTEGER)x->class == 7 && __IN(x->typ->form, 0x4072)) && __IN(p->typ->form, 0x4072)) {
        if ((p->typ->size == 4 && x->conval->intval >= 2147483648LL) && x->conval->intval <= 4294967295LL) {
          x->conval->intval -= 4294967296LL;
        } else if ((p->typ->size == 2 && x->conval->intval >= 32768) && x->conval->intval <= 65535) {
          x->conval->intval -= 65536;
        } else if ((p->typ->size == 1 && x->conval->intval >= 128) && x->conval->intval <= 255) {
          x->conval->intval -= 256;
        }
        OfrontOPB_Convert(&x, p->typ);
      } else {
        t = OfrontOPT_NewNode(11);
        t->subcl = 34;
        t->left = x;
        x = t;
        x->typ = p->typ;
      }
      p = x;
      break;
    case 36: 
      if ((INTEGER)x->class == 8 || (INTEGER)x->class == 9) {
        OfrontOPB_err(126);
      } else if (__IN(f, 0x4072)) {
        p = __71(19, 36, p, x);
      } else {
        OfrontOPB_err(111);
      }
      p->typ = OfrontOPT_notyp;
      break;
    case 37: 
      if ((INTEGER)x->class == 8 || (INTEGER)x->class == 9) {
        OfrontOPB_err(126);
      } else if ((INTEGER)OfrontOPM_AdrSize == 4) {
        if ((INTEGER)x->class == 7 && __IN(f, 0x12)) {
          OfrontOPB_Convert(&x, OfrontOPT_inttyp);
        } else if (!__IN(f, 0x2020)) {
          OfrontOPB_err(111);
          x->typ = OfrontOPT_inttyp;
        }
      } else if ((INTEGER)OfrontOPM_AdrSize == 2) {
        if ((INTEGER)x->class == 7 && f == 1) {
          OfrontOPB_Convert(&x, OfrontOPT_sinttyp);
        } else if (!__IN(f, 0x2010)) {
          OfrontOPB_err(111);
          x->typ = OfrontOPT_sinttyp;
        }
      } else {
        if ((INTEGER)x->class == 7 && __IN(f, 0x32)) {
          OfrontOPB_Convert(&x, OfrontOPT_linttyp);
        } else if (!__IN(f, 0x2040)) {
          OfrontOPB_err(111);
          x->typ = OfrontOPT_linttyp;
        }
      }
      p->link = x;
      break;
    case 38: 
      if (__IN(f, 0x4072) && (INTEGER)x->class == 7) {
        if (0 <= x->conval->intval && x->conval->intval <= 255) {
          OfrontOPB_BindNodes(28, OfrontOPT_notyp, &x, x);
          x->conval = OfrontOPT_NewConst();
          x->conval->intval = OfrontOPM_errpos;
          OfrontOPB_Construct(15, &p, x);
          p->conval = OfrontOPT_NewConst();
          p->conval->intval = OfrontOPM_errpos;
          OfrontOPB_Construct(20, &p, NIL);
          OfrontOPB_OptIf(&p);
          if (p == NIL) {
          } else if ((INTEGER)p->class == 28 && OfrontOPM_Lang != '7') {
            OfrontOPB_err(99);
          } else {
            p->subcl = 38;
          }
        } else {
          OfrontOPB_err(218);
        }
      } else {
        OfrontOPB_err(69);
      }
      break;
    case 32: 
      if ((INTEGER)x->class == 8 || (INTEGER)x->class == 9) {
        OfrontOPB_err(126);
      } else if (__IN(f, 0x4072)) {
        p = __71(19, 32, p, x);
      } else {
        OfrontOPB_err(111);
      }
      p->typ = OfrontOPT_notyp;
      break;
    case 33: 
      if (OfrontOPB_NotVar(x)) {
        OfrontOPB_err(112);
      } else if (x->readonly) {
        OfrontOPB_err(76);
      } else if (__IN(f, 0x4072)) {
        p = __71(19, 33, p, x);
      } else {
        OfrontOPB_err(111);
      }
      p->typ = OfrontOPT_notyp;
      break;
    default: 
      OfrontOPB_err(64);
      break;
  }
  *par0 = p;
  StPar1__70_s = _s.lnk;
}

/*----------------------------------------------------------------------------*/
void OfrontOPB_StParN (OfrontOPT_Node *par0, OfrontOPT_Node x, SHORTINT fctno, SHORTINT n)
{
  OfrontOPT_Node node = NIL;
  SHORTINT f;
  OfrontOPT_Node p = NIL;
  p = *par0;
  f = x->typ->form;
  if ((INTEGER)fctno == 1) {
    if ((INTEGER)x->class == 8 || (INTEGER)x->class == 9) {
      OfrontOPB_err(126);
    } else if ((INTEGER)p->typ->comp != 3) {
      OfrontOPB_err(64);
    } else if (__IN(f, 0x4072)) {
      if ((INTEGER)x->class == 7 && (x->conval->intval <= 0 || x->conval->intval > OfrontOPM_MaxIndex)) {
        OfrontOPB_err(63);
      }
      node = p->right;
      while (node->link != NIL) {
        node = node->link;
      }
      node->link = x;
      p->typ = p->typ->BaseTyp;
    } else {
      OfrontOPB_err(111);
    }
  } else if ((INTEGER)fctno == 37 && (INTEGER)n == 2) {
    if ((INTEGER)x->class == 8 || (INTEGER)x->class == 9) {
      OfrontOPB_err(126);
    } else if (__IN(f, 0x4072)) {
      node = OfrontOPT_NewNode(19);
      node->subcl = 37;
      node->right = p;
      node->left = p->link;
      p->link = x;
      p = node;
    } else {
      OfrontOPB_err(111);
    }
    p->typ = OfrontOPT_notyp;
  } else {
    OfrontOPB_err(64);
  }
  *par0 = p;
}

/*----------------------------------------------------------------------------*/
void OfrontOPB_StFct (OfrontOPT_Node *par0, BYTE fctno, SHORTINT parno)
{
  SHORTINT dim;
  OfrontOPT_Node x = NIL;
  OfrontOPT_Node p = NIL;
  p = *par0;
  if ((INTEGER)fctno <= 25) {
    if ((INTEGER)fctno == 1 && p->typ != OfrontOPT_notyp) {
      if ((INTEGER)p->typ->comp == 3) {
        OfrontOPB_err(65);
      }
      p->typ = OfrontOPT_notyp;
    } else if ((INTEGER)fctno == 7 || (INTEGER)fctno == 8) {
      if ((INTEGER)parno < 1 || ((INTEGER)parno == 1 && (INTEGER)p->hint != 1)) {
        OfrontOPB_err(65);
      } else if ((INTEGER)p->hint == 1 && (INTEGER)parno > 1) {
        OfrontOPB_err(64);
      }
      p->hint = 0;
    } else if ((INTEGER)fctno <= 15) {
      if ((INTEGER)parno < 1) {
        OfrontOPB_err(65);
      }
    } else {
      if (((INTEGER)fctno == 19 || (INTEGER)fctno == 20) && (INTEGER)parno == 1) {
        OfrontOPB_BindNodes(19, OfrontOPT_notyp, &p, OfrontOPB_NewIntConst(1));
        p->subcl = fctno;
        p->right->typ = p->left->typ;
      } else if ((INTEGER)fctno == 23 && (INTEGER)parno == 1) {
        if (__IN(p->typ->form, 0x040400)) {
          if ((INTEGER)p->class == 7) {
            p = OfrontOPB_NewIntConst(p->conval->intval2 - 1);
          } else if ((INTEGER)p->class == 12 && (INTEGER)p->subcl == 8) {
            OfrontOPB_StFct(&p->left, 23, 1);
            OfrontOPB_StFct(&p->right, 23, 1);
            switch (OfrontOPM_IndexSize) {
              case 2: 
                p->typ = OfrontOPT_sinttyp;
                break;
              case 4: 
                p->typ = OfrontOPT_inttyp;
                break;
              default: 
                p->typ = OfrontOPT_linttyp;
                break;
            }
          } else {
            while ((INTEGER)p->class == 11 && (INTEGER)p->subcl == 22) {
              p = p->left;
            }
            if (OfrontOPM_noerr) {
              __ASSERT((INTEGER)p->class == 3, 0, (CHAR*)"OfrontOPB", 538418);
            }
            switch (OfrontOPM_IndexSize) {
              case 2: 
                OfrontOPB_BindNodes(12, OfrontOPT_sinttyp, &p, OfrontOPB_NewIntConst(0));
                break;
              case 4: 
                OfrontOPB_BindNodes(12, OfrontOPT_inttyp, &p, OfrontOPB_NewIntConst(0));
                break;
              default: 
                OfrontOPB_BindNodes(12, OfrontOPT_linttyp, &p, OfrontOPB_NewIntConst(0));
                break;
            }
            p->subcl = 21;
          }
        } else if ((INTEGER)p->typ->comp == 3) {
          dim = 0;
          while ((INTEGER)p->class == 4) {
            p = p->left;
            dim += 1;
          }
          switch (OfrontOPM_IndexSize) {
            case 2: 
              OfrontOPB_BindNodes(12, OfrontOPT_sinttyp, &p, OfrontOPB_NewIntConst(dim));
              break;
            case 4: 
              OfrontOPB_BindNodes(12, OfrontOPT_inttyp, &p, OfrontOPB_NewIntConst(dim));
              break;
            default: 
              OfrontOPB_BindNodes(12, OfrontOPT_linttyp, &p, OfrontOPB_NewIntConst(dim));
              break;
          }
          p->subcl = 21;
        } else {
          p = OfrontOPB_NewIntConst(p->typ->n);
        }
      } else if ((INTEGER)parno < 2) {
        OfrontOPB_err(65);
      }
    }
  } else if ((INTEGER)fctno == 38) {
    if ((INTEGER)parno == 1) {
      x = NIL;
      OfrontOPB_BindNodes(28, OfrontOPT_notyp, &x, OfrontOPB_NewIntConst(0));
      x->conval = OfrontOPT_NewConst();
      x->conval->intval = OfrontOPM_errpos;
      OfrontOPB_Construct(15, &p, x);
      p->conval = OfrontOPT_NewConst();
      p->conval->intval = OfrontOPM_errpos;
      OfrontOPB_Construct(20, &p, NIL);
      OfrontOPB_OptIf(&p);
      if (p == NIL) {
      } else if ((INTEGER)p->class == 28 && OfrontOPM_Lang != '7') {
        OfrontOPB_err(99);
      } else {
        p->subcl = 38;
      }
    } else if ((INTEGER)parno < 1) {
      OfrontOPB_err(65);
    }
  } else {
    if ((INTEGER)fctno == 39) {
      if ((INTEGER)parno < 1) {
        OfrontOPB_err(65);
      }
    } else if ((INTEGER)fctno == 40 || (INTEGER)fctno == 41) {
      if ((INTEGER)parno < 2) {
        OfrontOPB_err(65);
      }
    } else if (((INTEGER)parno < 1 || ((INTEGER)fctno > 27 && (INTEGER)parno < 2)) || ((INTEGER)fctno == 37 && (INTEGER)parno < 3)) {
      OfrontOPB_err(65);
    }
  }
  *par0 = p;
}

/*----------------------------------------------------------------------------*/
static void OfrontOPB_DynArrParCheck (OfrontOPT_Struct ftyp, OfrontOPT_Node *ap, BOOLEAN fvarpar)
{
  OfrontOPT_Struct atyp = NIL;
  atyp = (*ap)->typ;
  if ((!__ODD(ftyp->sysflag) && __ODD(atyp->sysflag)) && (INTEGER)atyp->comp != 2) {
    OfrontOPB_err(137);
  } else if (fvarpar && ftyp == OfrontOPT_ubytetyp) {
    if (!__IN(atyp->comp, 0x0c) || !__IN(atyp->form, 0x400e)) {
      if (OfrontOPM_Lang > '2') {
        OfrontOPB_err(67);
      } else {
        OfrontOPB_err(-301);
      }
    } else if (!OfrontOPT_EqualType(ftyp, atyp)) {
      if (OfrontOPM_Lang > '2') {
        OfrontOPB_err(66);
      } else {
        OfrontOPB_err(-301);
      }
    }
  } else if (__IN(atyp->form, 0x060408)) {
    if ((!fvarpar && (INTEGER)ftyp->BaseTyp->form == 17) && (INTEGER)atyp->form == 10) {
      OfrontOPB_Convert(ap, OfrontOPT_string16typ);
    } else {
      OfrontOPB_CheckString(*ap, ftyp, 66);
    }
  } else {
    while ((INTEGER)ftyp->comp == 3 && (__IN(atyp->comp, 0x0c) || __IN(atyp->form, 0x040400))) {
      ftyp = ftyp->BaseTyp;
      atyp = atyp->BaseTyp;
    }
    if ((INTEGER)ftyp->comp == 3) {
      OfrontOPB_err(67);
    } else if ((!fvarpar && (INTEGER)ftyp->form == 13) && OfrontOPT_Extends(atyp, ftyp)) {
    } else if (!OfrontOPT_EqualType(ftyp, atyp)) {
      OfrontOPB_err(66);
    }
  }
}

static void OfrontOPB_CheckReceiver (OfrontOPT_Node *x, OfrontOPT_Object fp)
{
  if ((INTEGER)fp->typ->form == 13) {
    if ((INTEGER)(*x)->class == 3) {
      *x = (*x)->left;
    } else {
      OfrontOPB_err(71);
    }
  }
}

void OfrontOPB_PrepCall (OfrontOPT_Node *x, OfrontOPT_Object *fpar)
{
  if ((*x)->obj != NIL && __IN((*x)->obj->mode, 0x22c0)) {
    *fpar = (*x)->obj->link;
    if ((INTEGER)(*x)->obj->mode == 13) {
      OfrontOPB_CheckReceiver(&(*x)->left, *fpar);
      *fpar = (*fpar)->link;
    }
  } else if (((INTEGER)(*x)->class != 8 && (*x)->typ != NIL) && (INTEGER)(*x)->typ->form == 15) {
    *fpar = (*x)->typ->link;
  } else {
    OfrontOPB_err(121);
    *fpar = NIL;
    (*x)->typ = OfrontOPT_undftyp;
  }
}

/*----------------------------------------------------------------------------*/
void OfrontOPB_Param (OfrontOPT_Node *ap, OfrontOPT_Object fp)
{
  OfrontOPT_Struct at = NIL;
  OfrontOPT_Struct ft = NIL;
  at = (*ap)->typ;
  ft = fp->typ;
  if (fp->ptyp != NIL) {
    ft = fp->ptyp;
  }
  if ((INTEGER)ft->form != 0) {
    if ((INTEGER)(*ap)->class == 8 || ((INTEGER)(*ap)->class == 9 && (INTEGER)ft->form != 15)) {
      OfrontOPB_err(126);
    }
    if ((INTEGER)fp->mode == 2) {
      if (__ODD((INTEGER)fp->sysflag) && at == OfrontOPT_niltyp) {
      } else if ((((INTEGER)ft->comp == 4 && (INTEGER)ft->sysflag == 0) && (INTEGER)(*ap)->class == 12) && (INTEGER)(*ap)->subcl == 40) {
      } else if (((((INTEGER)ft->comp == 3 && (INTEGER)ft->sysflag == 0) && ft->n == 0) && (INTEGER)(*ap)->class == 12) && (INTEGER)(*ap)->subcl == 41) {
      } else {
        if ((INTEGER)fp->vis == 3) {
          if (!OfrontOPB_NotVar(*ap)) {
            OfrontOPB_CheckLeaf(*ap, 0);
          }
        } else {
          if (OfrontOPB_NotVar(*ap)) {
            OfrontOPB_err(122);
          } else if ((*ap)->readonly) {
            OfrontOPB_err(76);
          } else {
            OfrontOPB_CheckLeaf(*ap, 0);
          }
        }
        if ((INTEGER)ft->comp == 3) {
          OfrontOPB_DynArrParCheck(ft, ap, (INTEGER)fp->vis != 3);
        } else if (ft == OfrontOPT_sysptrtyp && (INTEGER)at->form == 13) {
        } else if (((INTEGER)fp->vis != 4 && (INTEGER)ft->comp == 4) && OfrontOPT_Extends(at, ft)) {
        } else if ((INTEGER)fp->vis == 3) {
          OfrontOPB_CheckAssign(ft, ap);
        } else if (!OfrontOPT_EqualType(ft, at)) {
          OfrontOPB_err(123);
        }
      }
    } else if ((INTEGER)ft->comp == 3) {
      OfrontOPB_DynArrParCheck(ft, ap, 0);
    } else {
      OfrontOPB_CheckAssign(ft, ap);
    }
  }
}

/*----------------------------------------------------------------------------*/
void OfrontOPB_StaticLink (BYTE dlev)
{
  OfrontOPT_Object scope = NIL;
  scope = OfrontOPT_topScope;
  while ((INTEGER)dlev > 0) {
    dlev -= 1;
    scope->link->conval->setval |= __SETOF(3);
    scope = scope->left;
  }
}

/*----------------------------------------------------------------------------*/
void OfrontOPB_Call (OfrontOPT_Node *x, OfrontOPT_Node apar, OfrontOPT_Object fp)
{
  OfrontOPT_Struct typ = NIL;
  OfrontOPT_Node p = NIL;
  BYTE lev;
  if ((INTEGER)(*x)->class == 9) {
    typ = (*x)->typ;
    lev = (*x)->obj->mnolev;
    if ((INTEGER)lev > 0) {
      OfrontOPB_StaticLink((BYTE)((INTEGER)OfrontOPT_topScope->mnolev - (INTEGER)lev));
    }
    if ((INTEGER)(*x)->obj->mode == 10) {
      OfrontOPB_err(121);
    }
  } else if ((INTEGER)(*x)->class == 2 && (INTEGER)(*x)->obj->mode == 13) {
    typ = (*x)->typ;
    (*x)->class = 9;
    p = (*x)->left;
    (*x)->left = NIL;
    p->link = apar;
    apar = p;
    fp = (*x)->obj->link;
  } else {
    typ = (*x)->typ->BaseTyp;
  }
  OfrontOPB_BindNodes(13, typ, x, apar);
  (*x)->obj = fp;
}

/*----------------------------------------------------------------------------*/
void OfrontOPB_Enter (OfrontOPT_Node *procdec, OfrontOPT_Node stat, OfrontOPT_Object proc)
{
  OfrontOPT_Node x = NIL;
  x = OfrontOPT_NewNode(18);
  x->typ = OfrontOPT_notyp;
  x->obj = proc;
  x->left = *procdec;
  x->right = stat;
  *procdec = x;
}

/*----------------------------------------------------------------------------*/
void OfrontOPB_Return (OfrontOPT_Node *x, OfrontOPT_Object proc)
{
  OfrontOPT_Node node = NIL;
  if (proc == NIL) {
    if (*x != NIL) {
      OfrontOPB_err(124);
    }
  } else {
    if (*x != NIL) {
      OfrontOPB_CheckAssign(proc->typ, x);
    } else if (proc->typ != OfrontOPT_notyp) {
      OfrontOPB_err(124);
    }
  }
  node = OfrontOPT_NewNode(26);
  node->typ = OfrontOPT_notyp;
  node->obj = proc;
  node->left = *x;
  *x = node;
}

/*----------------------------------------------------------------------------*/
void OfrontOPB_Assign (OfrontOPT_Node *x, OfrontOPT_Node y)
{
  OfrontOPT_Node z = NIL;
  if ((INTEGER)(*x)->class >= 7 || __IN((*x)->typ->form, 0x040400)) {
    OfrontOPB_err(56);
  }
  OfrontOPB_CheckAssign((*x)->typ, &y);
  if ((*x)->readonly) {
    OfrontOPB_err(76);
  }
  if (((INTEGER)y->class == 7 && __IN(y->typ->form, 0x040400)) && (INTEGER)(*x)->typ->form != 13) {
    OfrontOPB_AssignString(x, y);
  } else {
    if ((INTEGER)(*x)->typ->comp == 4) {
      if ((INTEGER)(*x)->class == 5) {
        z = (*x)->left;
      } else {
        z = *x;
      }
      if ((INTEGER)z->class == 3 && (INTEGER)z->left->class == 5) {
        z->left = z->left->left;
      }
      if ((*x)->typ->strobj != NIL && ((INTEGER)z->class == 3 || (INTEGER)z->class == 1)) {
        OfrontOPB_BindNodes(6, (*x)->typ, &z, NIL);
        *x = z;
      }
    }
    OfrontOPB_BindNodes(19, OfrontOPT_notyp, x, y);
    (*x)->subcl = 0;
  }
}

/*----------------------------------------------------------------------------*/
void OfrontOPB_Inittd (OfrontOPT_Node *inittd, OfrontOPT_Node *last, OfrontOPT_Struct typ)
{
  OfrontOPT_Node node = NIL;
  node = OfrontOPT_NewNode(14);
  node->typ = typ;
  node->conval = OfrontOPT_NewConst();
  node->conval->intval = typ->txtpos;
  if (*inittd == NIL) {
    *inittd = node;
  } else {
    (*last)->link = node;
  }
  *last = node;
}

/*----------------------------------------------------------------------------*/
static BOOLEAN OfrontOPB_Overlap (OfrontOPT_Node left, OfrontOPT_Node right)
{
  if ((INTEGER)right->class == 7) {
    return 0;
  } else if ((INTEGER)right->class == 12 && (INTEGER)right->subcl == 8) {
    return OfrontOPB_Overlap(left, right->left) || OfrontOPB_Overlap(left, right->right);
  } else {
    while ((INTEGER)right->class == 11) {
      right = right->left;
    }
    if ((INTEGER)right->class == 3) {
      right = right->left;
    }
    if (left->typ->BaseTyp != right->typ->BaseTyp) {
      return 0;
    }
    for (;;) {
      if ((INTEGER)left->class == 1) {
        while (((INTEGER)right->class == 4 || (INTEGER)right->class == 2) || (INTEGER)right->class == 5) {
          right = right->left;
        }
        return (INTEGER)right->class != 0 || (INTEGER)right->obj->mnolev < (INTEGER)left->obj->mnolev;
      } else if ((INTEGER)right->class == 1) {
        while (((INTEGER)left->class == 4 || (INTEGER)left->class == 2) || (INTEGER)left->class == 5) {
          left = left->left;
        }
        return (INTEGER)left->class != 0 || (INTEGER)left->obj->mnolev < (INTEGER)right->obj->mnolev;
      } else if ((INTEGER)left->class == 0 && (INTEGER)right->class == 0) {
        return left->obj == right->obj;
      } else if ((INTEGER)left->class == 3 && (INTEGER)right->class == 3) {
        return 1;
      } else if ((INTEGER)left->class == 4 && (INTEGER)right->class == 4) {
        if (((INTEGER)left->right->class == 7 && (INTEGER)right->right->class == 7) && left->right->conval->intval != right->right->conval->intval) {
          return 0;
        }
        left = left->left;
        right = right->left;
      } else if ((INTEGER)left->class == 2 && (INTEGER)right->class == 2) {
        if (left->obj != right->obj) {
          return 0;
        }
        left = left->left;
        right = right->left;
        while ((INTEGER)left->class == 5) {
          left = left->left;
        }
        while ((INTEGER)right->class == 5) {
          right = right->left;
        }
      } else {
        return 0;
      }
    }
  }
  __RETCHK((CHAR*)"OfrontOPB", 598527);
}

static void OfrontOPB_GetStaticLength (OfrontOPT_Node n, INTEGER *length)
{
  INTEGER x;
  if ((INTEGER)n->class == 7) {
    *length = n->conval->intval2 - 1;
  } else if ((INTEGER)n->class == 12 && (INTEGER)n->subcl == 8) {
    OfrontOPB_GetStaticLength(n->left, length);
    OfrontOPB_GetStaticLength(n->right, &x);
    if (*length >= 0 && x >= 0) {
      *length = *length + x;
    } else {
      *length = -1;
    }
  } else {
    while ((INTEGER)n->class == 11 && (INTEGER)n->subcl == 22) {
      n = n->left;
    }
    if ((INTEGER)n->class == 3 && (INTEGER)n->subcl == 1) {
      n = n->left;
    }
    if ((INTEGER)n->typ->comp == 2) {
      *length = n->typ->n - 1;
    } else if ((INTEGER)n->typ->comp == 3) {
      *length = -1;
    } else {
      *length = 4;
    }
  }
}

static void OfrontOPB_GetMaxLength (OfrontOPT_Node n, OfrontOPT_Node *stat, OfrontOPT_Node *last, OfrontOPT_Node *length)
{
  OfrontOPT_Node x = NIL;
  INTEGER d;
  OfrontOPT_Object obj = NIL;
  *length = NIL;
  if ((INTEGER)n->class == 7) {
    *length = OfrontOPB_NewIntConst(n->conval->intval2 - 1);
  } else if ((INTEGER)n->class == 12 && (INTEGER)n->subcl == 8) {
    OfrontOPB_GetMaxLength(n->left, stat, last, length);
    OfrontOPB_GetMaxLength(n->right, stat, last, &x);
    if ((INTEGER)(*length)->class == 7 && (INTEGER)x->class == 7) {
      OfrontOPB_ConstOp(8, *length, x);
    } else {
      OfrontOPB_BindNodes(12, (*length)->typ, length, x);
      (*length)->subcl = 8;
    }
  } else {
    while ((INTEGER)n->class == 11 && (INTEGER)n->subcl == 22) {
      n = n->left;
    }
    if ((INTEGER)n->class == 3 && (INTEGER)n->subcl == 1) {
      n = n->left;
    }
    if ((INTEGER)n->typ->comp == 2) {
      *length = OfrontOPB_NewIntConst(n->typ->n - 1);
    } else if ((INTEGER)n->typ->comp == 3) {
      d = 0;
      while ((INTEGER)n->class == 4) {
        n = n->left;
        d += 1;
      }
      __ASSERT(((INTEGER)n->class == 3 || (INTEGER)n->class == 0) || (INTEGER)n->class == 1, 0, (CHAR*)"OfrontOPB", 609865);
      if (((INTEGER)n->class == 3 && (INTEGER)n->left->class != 0) && (INTEGER)n->left->class != 1) {
        OfrontOPB_GetTempVar((CHAR*)"@tmp", 5, n->left->typ, &obj);
        x = OfrontOPB_NewLeaf(obj);
        OfrontOPB_Assign(&x, n->left);
        OfrontOPB_Link(stat, last, x);
        n->left = OfrontOPB_NewLeaf(obj);
        n = OfrontOPB_NewLeaf(obj);
        OfrontOPB_DeRef(&n);
      }
      if (((INTEGER)n->typ->sysflag != 0 && (INTEGER)n->typ->comp == 3) && (INTEGER)n->typ->BaseTyp->form == 3) {
        OfrontOPB_StrDeref(&n);
        OfrontOPB_BindNodes(12, OfrontOPT_inttyp, &n, OfrontOPB_NewIntConst(d));
        n->subcl = 21;
        OfrontOPB_BindNodes(12, OfrontOPT_inttyp, &n, OfrontOPB_NewIntConst(1));
        n->subcl = 8;
      } else {
        OfrontOPB_BindNodes(12, OfrontOPT_inttyp, &n, OfrontOPB_NewIntConst(d));
        n->subcl = 21;
      }
      *length = n;
    } else {
      *length = OfrontOPB_NewIntConst(4);
    }
  }
}

void OfrontOPB_CheckBuffering (OfrontOPT_Node *n, OfrontOPT_Node left, OfrontOPT_Object par, OfrontOPT_Node *stat, OfrontOPT_Node *last)
{
  OfrontOPT_Node length = NIL;
  OfrontOPT_Node x = NIL;
  OfrontOPT_Object obj = NIL;
  OfrontOPT_Struct typ = NIL;
  INTEGER len, xlen;
  if (__IN((*n)->typ->form, 0x040400) && (((((INTEGER)(*n)->class == 12 && (INTEGER)(*n)->subcl == 8) && (left == NIL || OfrontOPB_Overlap(left, (*n)->right))) || (((INTEGER)(*n)->class == 11 && (INTEGER)(*n)->subcl == 22) && left == NIL)) || ((par != NIL && (INTEGER)par->vis == 3) && (INTEGER)par->typ->comp == 2))) {
    if (par != NIL && (INTEGER)par->typ->comp == 2) {
      len = par->typ->n - 1;
    } else {
      if (left != NIL) {
        OfrontOPB_GetStaticLength(left, &len);
      } else {
        len = -1;
      }
      OfrontOPB_GetStaticLength(*n, &xlen);
      if (len == -1 || (xlen != -1 && xlen < len)) {
        len = xlen;
      }
    }
    if (len != -1) {
      typ = OfrontOPT_NewStr(16, 2);
      typ->n = len + 1;
      typ->BaseTyp = (*n)->typ->BaseTyp;
      OfrontOPB_GetTempVar((CHAR*)"@str", 5, typ, &obj);
      x = OfrontOPB_NewLeaf(obj);
      OfrontOPB_Assign(&x, *n);
      OfrontOPB_Link(stat, last, x);
      *n = OfrontOPB_NewLeaf(obj);
    } else {
      if (left != NIL) {
        OfrontOPB_GetMaxLength(left, stat, last, &length);
      } else {
        OfrontOPB_GetMaxLength(*n, stat, last, &length);
      }
      typ = OfrontOPT_NewStr(13, 1);
      typ->BaseTyp = OfrontOPT_NewStr(16, 3);
      typ->BaseTyp->BaseTyp = (*n)->typ->BaseTyp;
      OfrontOPB_GetTempVar((CHAR*)"@ptr", 5, typ, &obj);
      x = OfrontOPB_NewLeaf(obj);
      OfrontOPB_Construct(19, &x, length);
      x->subcl = 1;
      OfrontOPB_Link(stat, last, x);
      x = OfrontOPB_NewLeaf(obj);
      OfrontOPB_DeRef(&x);
      OfrontOPB_Assign(&x, *n);
      OfrontOPB_Link(stat, last, x);
      *n = OfrontOPB_NewLeaf(obj);
      OfrontOPB_DeRef(n);
    }
    OfrontOPB_StrDeref(n);
  }
}

/*----------------------------------------------------------------------------*/
void OfrontOPB_CheckVarParBuffering (OfrontOPT_Node *n, OfrontOPT_Node *stat, OfrontOPT_Node *last)
{
  OfrontOPT_Node x = NIL;
  OfrontOPT_Object obj = NIL;
  if ((INTEGER)(*n)->class != 0 || (INTEGER)(*n)->obj->mnolev <= 0) {
    OfrontOPB_GetTempVar((CHAR*)"@ptr", 5, (*n)->typ, &obj);
    x = OfrontOPB_NewLeaf(obj);
    OfrontOPB_Assign(&x, *n);
    OfrontOPB_Link(stat, last, x);
    *n = OfrontOPB_NewLeaf(obj);
  }
}

/*----------------------------------------------------------------------------*/

export void *OfrontOPB__init (void)
{
  __DEFMOD;
  __IMPORT(OfrontOPM__init);
  __IMPORT(OfrontOPS__init);
  __IMPORT(OfrontOPT__init);
  __REGMOD("OfrontOPB", 0);
/* BEGIN */
  __ENDMOD;
}
