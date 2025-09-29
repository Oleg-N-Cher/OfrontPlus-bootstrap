/* Ofront+ 1.0 -sC -88 */
#include "SYSTEM.oh"
#include "OfrontOPS.oh"
#include "OfrontOPM.oh"

typedef
  struct OfrontOPT_ConstDesc *OfrontOPT_Const;

typedef
  struct OfrontOPT_ConstArr__rec *OfrontOPT_ConstArr;

typedef
  struct OfrontOPT_ConstArr__rec {
    struct INT8_ARRAY *val1;
    struct INT16_ARRAY *val2;
    struct INT32_ARRAY *val4;
    struct INT64_ARRAY *val8;
  } OfrontOPT_ConstArr__rec;

typedef
  struct OfrontOPT_ConstDesc {
    OfrontOPS_String ext;
    LONGINT intval;
    INTEGER intval2;
    SET setval;
    REAL realval;
    OfrontOPT_ConstArr arr;
  } OfrontOPT_ConstDesc;

typedef
  struct OfrontOPT_ExpCtxt {
    INTEGER reffp;
    SHORTINT ref;
    BYTE nofm;
    BYTE locmno[64];
  } OfrontOPT_ExpCtxt;

typedef
  struct OfrontOPT_StrDesc *OfrontOPT_Struct;

typedef
  struct OfrontOPT_ObjDesc *OfrontOPT_Object;

typedef
  struct OfrontOPT_ImpCtxt {
    INTEGER nextTag, reffp;
    SHORTINT nofr, minr, nofm;
    BOOLEAN self;
    OfrontOPT_Struct ref[1754];
    OfrontOPT_Object old[1754];
    INTEGER pvfp[1754];
    BYTE glbmno[64];
  } OfrontOPT_ImpCtxt;

typedef
  struct OfrontOPT_NodeDesc *OfrontOPT_Node;

typedef
  struct OfrontOPT_NodeDesc {
    OfrontOPT_Node left, right, link;
    BYTE class, subcl, hint;
    BOOLEAN readonly;
    OfrontOPT_Struct typ;
    OfrontOPT_Object obj;
    OfrontOPT_Const conval;
  } OfrontOPT_NodeDesc;

typedef
  struct OfrontOPT_ObjDesc {
    OfrontOPT_Object left, right, link, scope;
    OfrontOPS_String name;
    BOOLEAN leaf;
    BYTE sysflag, mode, mnolev, vis, history;
    BOOLEAN used, fpdone;
    INTEGER fprint;
    OfrontOPT_Struct typ, ptyp;
    OfrontOPT_Const conval;
    OfrontOPT_Object nlink;
    OfrontOPS_String entry;
    INTEGER adr, linkadr;
    SHORTINT x;
  } OfrontOPT_ObjDesc;

typedef
  struct OfrontOPT_StrDesc {
    BYTE form, comp, mno, extlev;
    SHORTINT ref, sysflag;
    INTEGER n, size, align, txtpos;
    BOOLEAN allocated, pbused, pvused, exp, fpdone, idfpdone;
    BYTE attribute;
    INTEGER idfp, pbfp, pvfp;
    OfrontOPT_Struct BaseTyp;
    OfrontOPT_Object link, strobj;
  } OfrontOPT_StrDesc;


#ifndef INT8_ARRAY_DEF
#define INT8_ARRAY_DEF
typedef struct INT8_ARRAY {
  INTEGER len[1];
  BYTE data[1];
} INT8_ARRAY;
#endif 

#ifndef INT16_ARRAY_DEF
#define INT16_ARRAY_DEF
typedef struct INT16_ARRAY {
  INTEGER len[1];
  SHORTINT data[1];
} INT16_ARRAY;
#endif 

#ifndef INT32_ARRAY_DEF
#define INT32_ARRAY_DEF
typedef struct INT32_ARRAY {
  INTEGER len[1];
  INTEGER data[1];
} INT32_ARRAY;
#endif 

#ifndef INT64_ARRAY_DEF
#define INT64_ARRAY_DEF
typedef struct INT64_ARRAY {
  INTEGER len[1];
  LONGINT data[1];
} INT64_ARRAY;
#endif 

export void (*OfrontOPT_typSize)(OfrontOPT_Struct);
export OfrontOPT_Object OfrontOPT_topScope;
export OfrontOPT_Struct OfrontOPT_undftyp, OfrontOPT_bytetyp, OfrontOPT_booltyp, OfrontOPT_char8typ, OfrontOPT_sinttyp, OfrontOPT_inttyp, OfrontOPT_linttyp, OfrontOPT_realtyp, OfrontOPT_lrltyp, OfrontOPT_settyp, OfrontOPT_string8typ, OfrontOPT_niltyp, OfrontOPT_notyp, OfrontOPT_sysptrtyp, OfrontOPT_ubytetyp, OfrontOPT_anytyp, OfrontOPT_anyptrtyp, OfrontOPT_char16typ, OfrontOPT_string16typ;
static OfrontOPT_Object OfrontOPT_char8, OfrontOPT_int8, OfrontOPT_int16, OfrontOPT_int32, OfrontOPT_int64, OfrontOPT_adrint, OfrontOPT_byte, OfrontOPT_ubyte, OfrontOPT_real32, OfrontOPT_real64, OfrontOPT_char16;
export BYTE OfrontOPT_nofGmod;
export OfrontOPT_Object OfrontOPT_GlbMod[64];
export OfrontOPS_Name OfrontOPT_SelfName;
export BOOLEAN OfrontOPT_SYSimported;
export OfrontOPS_String OfrontOPT_null;
static OfrontOPT_Object OfrontOPT_universe, OfrontOPT_syslink, OfrontOPT_infinity;
static OfrontOPT_ImpCtxt OfrontOPT_impCtxt;
static OfrontOPT_ExpCtxt OfrontOPT_expCtxt;
static INTEGER OfrontOPT_nofhdfld;
static BOOLEAN OfrontOPT_newsf, OfrontOPT_findpc, OfrontOPT_extsf, OfrontOPT_sfpresent, OfrontOPT_symExtended, OfrontOPT_symNew;
static INTEGER OfrontOPT_depth;

export void **OfrontOPT_ConstArr__rec__typ;
export void **OfrontOPT_ConstDesc__typ;
export void **OfrontOPT_ObjDesc__typ;
export void **OfrontOPT_StrDesc__typ;
export void **OfrontOPT_NodeDesc__typ;
export void **OfrontOPT_ImpCtxt__typ;
export void **OfrontOPT_ExpCtxt__typ;

export void OfrontOPT_Close (void);
export void OfrontOPT_CloseScope (void);
export BOOLEAN OfrontOPT_ContainsRealType (OfrontOPT_Struct typ);
static void OfrontOPT_EnterAttr (CHAR *name, INTEGER name__len, CHAR *lowcase, INTEGER lowcase__len, SHORTINT num);
static void OfrontOPT_EnterBoolConst (CHAR *name, INTEGER name__len, CHAR *lowcase, INTEGER lowcase__len, INTEGER value);
static void OfrontOPT_EnterProc (CHAR *name, INTEGER name__len, CHAR *lowcase, INTEGER lowcase__len, SHORTINT num);
static void OfrontOPT_EnterRealConst (CHAR *name, INTEGER name__len, CHAR *lowcase, INTEGER lowcase__len, REAL val, OfrontOPT_Object *obj);
static void OfrontOPT_EnterTProc (OfrontOPT_Struct ptr, OfrontOPT_Struct rec, CHAR *name, INTEGER name__len, CHAR *lowcase, INTEGER lowcase__len, SHORTINT typ);
static void OfrontOPT_EnterTyp (CHAR *name, INTEGER name__len, CHAR *lowcase, INTEGER lowcase__len, BYTE form, SHORTINT size, OfrontOPT_Struct *res);
static void OfrontOPT_EnterTypeAlias (CHAR *name, INTEGER name__len, CHAR *lowcase, INTEGER lowcase__len, OfrontOPT_Object *res, OfrontOPT_Struct typ);
export BOOLEAN OfrontOPT_EqualType (OfrontOPT_Struct x, OfrontOPT_Struct y);
export void OfrontOPT_Export (BOOLEAN *ext, BOOLEAN *new);
export BOOLEAN OfrontOPT_Extends (OfrontOPT_Struct x, OfrontOPT_Struct y);
static void OfrontOPT_FPrintErr (OfrontOPT_Object obj, SHORTINT errno);
static void OfrontOPT_FPrintName (INTEGER *fp, CHAR *name, INTEGER name__len);
static void OfrontOPT_FPrintObj (OfrontOPT_Object obj);
static void OfrontOPT_FPrintSign (INTEGER *fp, OfrontOPT_Struct result, OfrontOPT_Object par);
static void OfrontOPT_FPrintStr (OfrontOPT_Struct typ);
export void OfrontOPT_Find (CHAR *name, INTEGER name__len, OfrontOPT_Object *res);
export void OfrontOPT_FindBaseField (CHAR *name, INTEGER name__len, OfrontOPT_Struct typ, OfrontOPT_Object *res);
export void OfrontOPT_FindField (CHAR *name, INTEGER name__len, OfrontOPT_Struct typ, OfrontOPT_Object *res);
static void OfrontOPT_FindFld (CHAR *name, INTEGER name__len, OfrontOPT_Struct typ, OfrontOPT_Object *res);
export void OfrontOPT_FindImport (OfrontOPT_Object mod, OfrontOPT_Object *res);
static void OfrontOPT_IdFPrint (OfrontOPT_Struct typ);
export void OfrontOPT_Import (CHAR *aliasName, INTEGER aliasName__len, CHAR *name, INTEGER name__len, BOOLEAN *done);
static void OfrontOPT_InConstant (INTEGER f, OfrontOPT_Const conval);
static OfrontOPT_Object OfrontOPT_InFld (void);
static void OfrontOPT_InMod (BYTE *mno);
static void OfrontOPT_InName (OfrontOPS_String *name);
static OfrontOPT_Object OfrontOPT_InObj (BYTE mno);
static void OfrontOPT_InSign (BYTE mno, OfrontOPT_Struct *res, OfrontOPT_Object *par);
static void OfrontOPT_InStruct (OfrontOPT_Struct *typ);
static OfrontOPT_Object OfrontOPT_InTProc (BYTE mno);
export BOOLEAN OfrontOPT_Includes (INTEGER xform, INTEGER yform);
export void OfrontOPT_Init (CHAR *name, INTEGER name__len, CHAR lang, SET opt);
static void OfrontOPT_InitScope (CHAR lang);
static void OfrontOPT_InitStruct (OfrontOPT_Struct *typ, BYTE form);
export void OfrontOPT_Insert (CHAR *name, INTEGER name__len, OfrontOPT_Object *obj);
static void OfrontOPT_Insert2 (CHAR *name, INTEGER name__len, CHAR *lowcase, INTEGER lowcase__len, OfrontOPT_Object *obj);
static void OfrontOPT_InsertField (CHAR *name, INTEGER name__len, CHAR *lowcase, INTEGER lowcase__len, OfrontOPT_Struct typ, OfrontOPT_Object *obj);
export void OfrontOPT_InsertImport (OfrontOPT_Object obj, OfrontOPT_Object *root, OfrontOPT_Object *old);
static void OfrontOPT_InsertThisField (OfrontOPT_Object obj, OfrontOPT_Struct typ, OfrontOPT_Object *old);
export OfrontOPT_Const OfrontOPT_NewConst (void);
export OfrontOPS_String OfrontOPT_NewName (CHAR *name, INTEGER name__len);
export OfrontOPT_Node OfrontOPT_NewNode (BYTE class);
export OfrontOPT_Object OfrontOPT_NewObj (void);
export OfrontOPT_Struct OfrontOPT_NewStr (BYTE form, BYTE comp);
export void OfrontOPT_OpenScope (BYTE level, OfrontOPT_Object owner);
static void OfrontOPT_OutConstant (OfrontOPT_Object obj);
static void OfrontOPT_OutFlds (OfrontOPT_Object fld, INTEGER adr, BOOLEAN visible);
static void OfrontOPT_OutHdFld (OfrontOPT_Struct typ, OfrontOPT_Object fld, INTEGER adr);
static void OfrontOPT_OutMod (SHORTINT mno);
static void OfrontOPT_OutName (CHAR *name, INTEGER name__len);
static void OfrontOPT_OutObj (OfrontOPT_Object obj);
static void OfrontOPT_OutSign (OfrontOPT_Struct result, OfrontOPT_Object par);
static void OfrontOPT_OutStr (OfrontOPT_Struct typ);
static void OfrontOPT_OutTProcs (OfrontOPT_Struct typ, OfrontOPT_Object obj);
export BOOLEAN OfrontOPT_SameType (OfrontOPT_Struct x, OfrontOPT_Struct y);
static void OfrontOPT_err (SHORTINT n);


/*============================================================================*/

static void OfrontOPT_err (SHORTINT n)
{
  OfrontOPM_err(n);
}

OfrontOPT_Const OfrontOPT_NewConst (void)
{
  OfrontOPT_Const const_ = NIL;
  __NEW(const_, OfrontOPT_ConstDesc);
  return const_;
}

/*----------------------------------------------------------------------------*/
OfrontOPT_Object OfrontOPT_NewObj (void)
{
  OfrontOPT_Object obj = NIL;
  __NEW(obj, OfrontOPT_ObjDesc);
  obj->name = OfrontOPT_null;
  return obj;
}

/*----------------------------------------------------------------------------*/
OfrontOPT_Struct OfrontOPT_NewStr (BYTE form, BYTE comp)
{
  OfrontOPT_Struct typ = NIL;
  __NEW(typ, OfrontOPT_StrDesc);
  typ->form = form;
  typ->comp = comp;
  typ->ref = 1754;
  if ((INTEGER)form != 0) {
    typ->txtpos = OfrontOPM_errpos;
  }
  typ->size = -1;
  typ->BaseTyp = OfrontOPT_undftyp;
  return typ;
}

/*----------------------------------------------------------------------------*/
OfrontOPT_Node OfrontOPT_NewNode (BYTE class)
{
  OfrontOPT_Node node = NIL;
  __NEW(node, OfrontOPT_NodeDesc);
  node->class = class;
  return node;
}

/*----------------------------------------------------------------------------*/
OfrontOPS_String OfrontOPT_NewName (CHAR *name, INTEGER name__len)
{
  INTEGER i;
  OfrontOPS_String p = NIL;
  i = __STRLEN(name, name__len, (CHAR*)"OfrontOPT", 50193);
  if (i > 0) {
    p = __NEWARR(NIL, 1, 1, 1, 1, (SYSTEM_ARRLEN)(i + 1));
    __STRCOPYCC(name, p->data, __MIN(p->len[0], name__len), (CHAR*)"OfrontOPT", 50474);
    return p;
  } else {
    return OfrontOPT_null;
  }
  __RETCHK((CHAR*)"OfrontOPT", 50943);
}

/*----------------------------------------------------------------------------*/
void OfrontOPT_OpenScope (BYTE level, OfrontOPT_Object owner)
{
  OfrontOPT_Object head = NIL;
  head = OfrontOPT_NewObj();
  head->mode = 12;
  head->mnolev = level;
  head->link = owner;
  if (owner != NIL) {
    owner->scope = head;
  }
  head->left = OfrontOPT_topScope;
  head->right = NIL;
  head->scope = NIL;
  OfrontOPT_topScope = head;
}

/*----------------------------------------------------------------------------*/
void OfrontOPT_CloseScope (void)
{
  if (OfrontOPT_topScope != NIL) {
    OfrontOPT_topScope = OfrontOPT_topScope->left;
  }
}

/*----------------------------------------------------------------------------*/
void OfrontOPT_Close (void)
{
  SHORTINT i;
  OfrontOPT_CloseScope();
  i = 0;
  while ((INTEGER)i < 64) {
    OfrontOPT_GlbMod[__X(i, 64, (CHAR*)"OfrontOPT", 55855)] = NIL;
    i += 1;
  }
  i = 32;
  while ((INTEGER)i < 1754) {
    OfrontOPT_impCtxt.ref[__X(i, 1754, (CHAR*)"OfrontOPT", 56125)] = NIL;
    OfrontOPT_impCtxt.old[__X(i, 1754, (CHAR*)"OfrontOPT", 56148)] = NIL;
    i += 1;
  }
}

/*----------------------------------------------------------------------------*/
BOOLEAN OfrontOPT_SameType (OfrontOPT_Struct x, OfrontOPT_Struct y)
{
  return ((x == y || ((INTEGER)x->form == (INTEGER)y->form && !__IN(x->form, 0x01a000))) || x == OfrontOPT_undftyp) || y == OfrontOPT_undftyp;
}

/*----------------------------------------------------------------------------*/
BOOLEAN OfrontOPT_EqualType (OfrontOPT_Struct x, OfrontOPT_Struct y)
{
  OfrontOPT_Object xp = NIL;
  OfrontOPT_Object yp = NIL;
  INTEGER n;
  n = 0;
  while ((n < 100 && x != y) && (((((INTEGER)x->comp == 3 && (INTEGER)y->comp == 3) && (INTEGER)x->sysflag == (INTEGER)y->sysflag) || ((INTEGER)x->form == 13 && (INTEGER)y->form == 13)) || ((INTEGER)x->form == 15 && (INTEGER)y->form == 15))) {
    if ((INTEGER)x->form == 15) {
      if ((INTEGER)x->sysflag != (INTEGER)y->sysflag) {
        return 0;
      }
      xp = x->link;
      yp = y->link;
      OfrontOPT_depth += 1;
      while ((((((xp != NIL && yp != NIL) && (INTEGER)xp->mode == (INTEGER)yp->mode) && (INTEGER)xp->sysflag == (INTEGER)yp->sysflag) && (INTEGER)xp->vis == (INTEGER)yp->vis) && OfrontOPT_depth < 100) && OfrontOPT_EqualType(xp->typ, yp->typ)) {
        xp = xp->link;
        yp = yp->link;
      }
      OfrontOPT_depth -= 1;
      if (xp != NIL || yp != NIL) {
        return 0;
      }
    }
    x = x->BaseTyp;
    y = y->BaseTyp;
    n += 1;
  }
  return OfrontOPT_SameType(x, y);
}

/*----------------------------------------------------------------------------*/
BOOLEAN OfrontOPT_Extends (OfrontOPT_Struct x, OfrontOPT_Struct y)
{
  if ((INTEGER)x->form == 13 && (INTEGER)y->form == 13) {
    x = x->BaseTyp;
    y = y->BaseTyp;
  }
  if ((INTEGER)x->comp == 4 && (INTEGER)y->comp == 4) {
    if (y == OfrontOPT_anytyp && (INTEGER)x->sysflag == 0) {
      return 1;
    }
    while ((x != NIL && x != OfrontOPT_undftyp) && x != y) {
      x = x->BaseTyp;
    }
  }
  return x != NIL && OfrontOPT_EqualType(x, y);
}

/*----------------------------------------------------------------------------*/
BOOLEAN OfrontOPT_Includes (INTEGER xform, INTEGER yform)
{
  switch (xform) {
    case 17: 
      return __IN(yform, 0x02000a);
      break;
    case 4: 
      return __IN(yform, 0x1a);
      break;
    case 5: 
      return __IN(yform, 0x02003a);
      break;
    case 6: 
      return __IN(yform, 0x02007a);
      break;
    case 7: 
      return __IN(yform, 0x0200fa);
      break;
    case 8: 
      return __IN(yform, 0x0201fa);
      break;
    case 18: 
      return __IN(yform, 0x040400);
      break;
    default: 
      return xform == yform;
      break;
  }
  __RETCHK((CHAR*)"OfrontOPT", 69631);
}

/*----------------------------------------------------------------------------*/
void OfrontOPT_FindImport (OfrontOPT_Object mod, OfrontOPT_Object *res)
{
  OfrontOPT_Object obj = NIL;
  obj = mod->scope;
  for (;;) {
    if (obj == NIL) {
      break;
    }
    if (__STRCMPCC(OfrontOPS_name, obj->name->data, obj->name->len[0], (CHAR*)"OfrontOPT", 73727) < 0) {
      obj = obj->left;
    } else if (__STRCMPCC(OfrontOPS_name, obj->name->data, obj->name->len[0], (CHAR*)"OfrontOPT", 71935) > 0) {
      obj = obj->right;
    } else {
      if ((INTEGER)obj->mode == 5 && (INTEGER)obj->vis == 0) {
        obj = NIL;
      } else {
        obj->used = 1;
      }
      break;
    }
  }
  *res = obj;
}

/*----------------------------------------------------------------------------*/
void OfrontOPT_Find (CHAR *name, INTEGER name__len, OfrontOPT_Object *res)
{
  OfrontOPT_Object obj = NIL;
  OfrontOPT_Object head = NIL;
  head = OfrontOPT_topScope;
  for (;;) {
    obj = head->right;
    for (;;) {
      if (obj == NIL) {
        break;
      }
      if (__STRCMPCC(name, obj->name->data, obj->name->len[0], (CHAR*)"OfrontOPT", 77311) < 0) {
        obj = obj->left;
      } else if (__STRCMPCC(name, obj->name->data, obj->name->len[0], (CHAR*)"OfrontOPT", 76543) > 0) {
        obj = obj->right;
      } else {
        break;
      }
    }
    if (obj != NIL) {
      break;
    }
    head = head->left;
    if (head == NIL) {
      break;
    }
  }
  *res = obj;
}

/*----------------------------------------------------------------------------*/
static void OfrontOPT_FindFld (CHAR *name, INTEGER name__len, OfrontOPT_Struct typ, OfrontOPT_Object *res)
{
  OfrontOPT_Object obj = NIL;
  while (typ != NIL && typ != OfrontOPT_undftyp) {
    obj = typ->link;
    while (obj != NIL) {
      if (__STRCMPCC(name, obj->name->data, obj->name->len[0], (CHAR*)"OfrontOPT", 81663) < 0) {
        obj = obj->left;
      } else if (__STRCMPCC(name, obj->name->data, obj->name->len[0], (CHAR*)"OfrontOPT", 80895) > 0) {
        obj = obj->right;
      } else {
        *res = obj;
        return;
      }
    }
    typ = typ->BaseTyp;
  }
  *res = NIL;
}

void OfrontOPT_FindField (CHAR *name, INTEGER name__len, OfrontOPT_Struct typ, OfrontOPT_Object *res)
{
  OfrontOPT_FindFld((void*)name, name__len, typ, res);
  if (*res == NIL && (INTEGER)typ->sysflag == 0) {
    OfrontOPT_FindFld((void*)name, name__len, OfrontOPT_anytyp, res);
  }
}

/*----------------------------------------------------------------------------*/
void OfrontOPT_FindBaseField (CHAR *name, INTEGER name__len, OfrontOPT_Struct typ, OfrontOPT_Object *res)
{
  OfrontOPT_FindFld((void*)name, name__len, typ->BaseTyp, res);
  if (*res == NIL && (INTEGER)typ->sysflag == 0) {
    OfrontOPT_FindFld((void*)name, name__len, OfrontOPT_anytyp, res);
  }
}

/*----------------------------------------------------------------------------*/
void OfrontOPT_Insert (CHAR *name, INTEGER name__len, OfrontOPT_Object *obj)
{
  OfrontOPT_Object ob0 = NIL;
  OfrontOPT_Object ob1 = NIL;
  BOOLEAN left;
  BYTE mnolev;
  ob0 = OfrontOPT_topScope;
  ob1 = ob0->right;
  left = 0;
  for (;;) {
    if (ob1 != NIL) {
      if (__STRCMPCC(name, ob1->name->data, ob1->name->len[0], (CHAR*)"OfrontOPT", 88575) < 0) {
        ob0 = ob1;
        ob1 = ob0->left;
        left = 1;
      } else if (__STRCMPCC(name, ob1->name->data, ob1->name->len[0], (CHAR*)"OfrontOPT", 87807) > 0) {
        ob0 = ob1;
        ob1 = ob0->right;
        left = 0;
      } else {
        OfrontOPT_err(1);
        ob0 = ob1;
        ob1 = ob0->right;
      }
    } else {
      ob1 = OfrontOPT_NewObj();
      ob1->leaf = 1;
      if (left) {
        ob0->left = ob1;
      } else {
        ob0->right = ob1;
      }
      ob1->left = NIL;
      ob1->right = NIL;
      ob1->name = OfrontOPT_NewName((void*)name, name__len);
      mnolev = OfrontOPT_topScope->mnolev;
      ob1->mnolev = mnolev;
      break;
    }
  }
  *obj = ob1;
}

/*----------------------------------------------------------------------------*/
static void OfrontOPT_Insert2 (CHAR *name, INTEGER name__len, CHAR *lowcase, INTEGER lowcase__len, OfrontOPT_Object *obj)
{
  if (OfrontOPS_lowcase) {
    OfrontOPT_Insert((void*)lowcase, lowcase__len, obj);
  } else {
    OfrontOPT_Insert((void*)name, name__len, obj);
  }
}

static void OfrontOPT_InsertThisField (OfrontOPT_Object obj, OfrontOPT_Struct typ, OfrontOPT_Object *old)
{
  OfrontOPT_Object ob0 = NIL;
  OfrontOPT_Object ob1 = NIL;
  BOOLEAN left;
  OfrontOPS_String name = NIL;
  if (typ->link == NIL) {
    typ->link = obj;
  } else {
    ob1 = typ->link;
    name = obj->name;
    do {
      if (__STRCMPCC(name->data, ob1->name->data, ob1->name->len[0], (CHAR*)"OfrontOPT", 95231) < 0) {
        ob0 = ob1;
        ob1 = ob1->left;
        left = 1;
      } else if (__STRCMPCC(name->data, ob1->name->data, ob1->name->len[0], (CHAR*)"OfrontOPT", 94463) > 0) {
        ob0 = ob1;
        ob1 = ob1->right;
        left = 0;
      } else {
        *old = ob1;
        return;
      }
    } while (!(ob1 == NIL));
    if (left) {
      ob0->left = obj;
    } else {
      ob0->right = obj;
    }
  }
}

static void OfrontOPT_InsertField (CHAR *name, INTEGER name__len, CHAR *lowcase, INTEGER lowcase__len, OfrontOPT_Struct typ, OfrontOPT_Object *obj)
{
  OfrontOPT_Object old = NIL;
  *obj = OfrontOPT_NewObj();
  (*obj)->leaf = 1;
  if (OfrontOPS_lowcase) {
    (*obj)->name = OfrontOPT_NewName((void*)lowcase, lowcase__len);
  } else {
    (*obj)->name = OfrontOPT_NewName((void*)name, name__len);
  }
  OfrontOPT_InsertThisField(*obj, typ, &old);
  if (old != NIL) {
    OfrontOPT_err(1);
  }
}

static void OfrontOPT_FPrintName (INTEGER *fp, CHAR *name, INTEGER name__len)
{
  INTEGER i;
  CHAR ch;
  i = 0;
  do {
    ch = name[__X(i, name__len, (CHAR*)"OfrontOPT", 100118)];
    OfrontOPM_FPrint(fp, (SHORTINT)ch);
    i += 1;
  } while (!(ch == 0x00));
}

static void OfrontOPT_FPrintSign (INTEGER *fp, OfrontOPT_Struct result, OfrontOPT_Object par)
{
  OfrontOPT_IdFPrint(result);
  OfrontOPM_FPrint(fp, result->idfp);
  while (par != NIL) {
    OfrontOPM_FPrint(fp, par->mode);
    OfrontOPT_IdFPrint(par->typ);
    OfrontOPM_FPrint(fp, par->typ->idfp);
    if ((INTEGER)par->mode == 2 && (INTEGER)par->vis != 0) {
      OfrontOPM_FPrint(fp, par->vis);
    }
    if ((INTEGER)par->sysflag != 0) {
      OfrontOPM_FPrint(fp, par->sysflag);
    }
    par = par->link;
  }
}

static void OfrontOPT_IdFPrint (OfrontOPT_Struct typ)
{
  OfrontOPT_Struct btyp = NIL;
  OfrontOPT_Object strobj = NIL;
  INTEGER idfp;
  SHORTINT f, c;
  OfrontOPS_String _ptr__36 = NIL;
  OfrontOPS_String _ptr__35 = NIL;
  if (!typ->idfpdone) {
    typ->idfpdone = 1;
    idfp = 0;
    f = typ->form;
    c = typ->comp;
    OfrontOPM_FPrint(&idfp, f);
    OfrontOPM_FPrint(&idfp, c);
    btyp = typ->BaseTyp;
    strobj = typ->strobj;
    if (strobj != NIL && strobj->name != OfrontOPT_null) {
      _ptr__36 = OfrontOPT_GlbMod[__X(typ->mno, 64, (CHAR*)"OfrontOPT", 106797)]->name;
      OfrontOPT_FPrintName(&idfp, (void*)_ptr__36->data, _ptr__36->len[0]);
      _ptr__35 = strobj->name;
      OfrontOPT_FPrintName(&idfp, (void*)_ptr__35->data, _ptr__35->len[0]);
    }
    if (((INTEGER)f == 13 || ((INTEGER)c == 4 && btyp != NIL)) || (INTEGER)c == 3) {
      OfrontOPT_IdFPrint(btyp);
      OfrontOPM_FPrint(&idfp, btyp->idfp);
    } else if ((INTEGER)c == 2) {
      OfrontOPT_IdFPrint(btyp);
      OfrontOPM_FPrint(&idfp, btyp->idfp);
      OfrontOPM_FPrint(&idfp, typ->n);
    } else if ((INTEGER)f == 15) {
      OfrontOPT_FPrintSign(&idfp, btyp, typ->link);
    }
    if ((INTEGER)typ->sysflag != 0) {
      OfrontOPM_FPrint(&idfp, typ->sysflag);
    }
    typ->idfp = idfp;
  }
}

static struct FPrintStr__20 {
  INTEGER *pbfp, *pvfp;
  struct FPrintStr__20 *lnk;
} *FPrintStr__20_s;

static void __21 (OfrontOPT_Object fld, INTEGER adr, BOOLEAN visible);
static void __24 (OfrontOPT_Struct typ, OfrontOPT_Object fld, INTEGER adr);
static void __26 (OfrontOPT_Object obj);

static void __24 (OfrontOPT_Struct typ, OfrontOPT_Object fld, INTEGER adr)
{
  INTEGER i, j, n;
  OfrontOPT_Struct btyp = NIL;
  if ((INTEGER)typ->comp == 4) {
    __21(typ->link, adr, 0);
  } else if ((INTEGER)typ->comp == 2) {
    btyp = typ->BaseTyp;
    n = typ->n;
    while ((INTEGER)btyp->comp == 2) {
      n = btyp->n * n;
      btyp = btyp->BaseTyp;
    }
    if ((INTEGER)btyp->form == 13 || (INTEGER)btyp->comp == 4) {
      j = OfrontOPT_nofhdfld;
      __24(btyp, fld, adr);
      if (j != OfrontOPT_nofhdfld) {
        i = 1;
        while (i < n && OfrontOPT_nofhdfld <= 512) {
          adr += btyp->size;
          __24(btyp, fld, adr);
          i += 1;
        }
      }
    }
  } else if ((INTEGER)typ->form == 13 || __STRCMPCC(fld->name->data, (CHAR*)"@ptr", 5, (CHAR*)"OfrontOPT", 113919) == 0) {
    OfrontOPM_FPrint(&(*FPrintStr__20_s->pvfp), 13);
    OfrontOPM_FPrint(&(*FPrintStr__20_s->pvfp), adr);
    OfrontOPT_nofhdfld += 1;
  }
}

static void __21 (OfrontOPT_Object fld, INTEGER adr, BOOLEAN visible)
{
  OfrontOPS_String _ptr__23 = NIL;
  while (fld != NIL && (INTEGER)fld->mode == 4) {
    if ((INTEGER)fld->vis != 0 && visible) {
      OfrontOPM_FPrint(&(*FPrintStr__20_s->pbfp), fld->vis);
      _ptr__23 = fld->name;
      OfrontOPT_FPrintName(&(*FPrintStr__20_s->pbfp), (void*)_ptr__23->data, _ptr__23->len[0]);
      OfrontOPM_FPrint(&(*FPrintStr__20_s->pbfp), fld->adr);
      OfrontOPT_FPrintStr(fld->typ);
      OfrontOPM_FPrint(&(*FPrintStr__20_s->pbfp), fld->typ->pbfp);
      OfrontOPM_FPrint(&(*FPrintStr__20_s->pvfp), fld->typ->pvfp);
    } else {
      __24(fld->typ, fld, fld->adr + adr);
    }
    fld = fld->link;
  }
}

static void __26 (OfrontOPT_Object obj)
{
  INTEGER fp;
  OfrontOPS_String _ptr__28 = NIL;
  if (obj != NIL) {
    __26(obj->left);
    if ((INTEGER)obj->mode == 13) {
      if ((INTEGER)obj->vis != 0) {
        fp = 0;
        if ((INTEGER)obj->vis == 2) {
          OfrontOPM_FPrint(&fp, 2);
        }
        if (__IN(18, obj->conval->setval)) {
          OfrontOPM_FPrint(&fp, 18);
        } else if (__IN(17, obj->conval->setval)) {
          OfrontOPM_FPrint(&fp, 17);
        } else if (__IN(19, obj->conval->setval)) {
          OfrontOPM_FPrint(&fp, 19);
        } else if (__IN(20, obj->conval->setval)) {
          OfrontOPM_FPrint(&fp, 20);
        }
        OfrontOPM_FPrint(&fp, 13);
        OfrontOPM_FPrint(&fp, __ASHR(obj->adr, 16, INTEGER));
        OfrontOPT_FPrintSign(&fp, obj->typ, obj->link);
        _ptr__28 = obj->name;
        OfrontOPT_FPrintName(&fp, (void*)_ptr__28->data, _ptr__28->len[0]);
        OfrontOPM_FPrint(&(*FPrintStr__20_s->pvfp), fp);
        OfrontOPM_FPrint(&(*FPrintStr__20_s->pbfp), fp);
      }
    }
    __26(obj->right);
  }
}

static void OfrontOPT_FPrintStr (OfrontOPT_Struct typ)
{
  SHORTINT f, c;
  OfrontOPT_Struct btyp = NIL;
  OfrontOPT_Object strobj = NIL;
  OfrontOPT_Object bstrobj = NIL;
  INTEGER pbfp, pvfp;
  struct FPrintStr__20 _s;
  _s.pbfp = &pbfp;
  _s.pvfp = &pvfp;
  _s.lnk = FPrintStr__20_s;
  FPrintStr__20_s = &_s;
  if (!typ->fpdone) {
    OfrontOPT_IdFPrint(typ);
    pbfp = typ->idfp;
    pvfp = pbfp;
    typ->pbfp = pbfp;
    typ->pvfp = pvfp;
    typ->fpdone = 1;
    f = typ->form;
    c = typ->comp;
    btyp = typ->BaseTyp;
    if ((INTEGER)f == 13) {
      strobj = typ->strobj;
      bstrobj = btyp->strobj;
      if (((strobj == NIL || strobj->name == OfrontOPT_null) || bstrobj == NIL) || bstrobj->name == OfrontOPT_null) {
        OfrontOPT_FPrintStr(btyp);
        OfrontOPM_FPrint(&pbfp, btyp->pbfp + 12345);
        pvfp = pbfp;
      }
    } else if ((INTEGER)f == 15) {
    } else if (__IN(c, 0x0c)) {
      OfrontOPT_FPrintStr(btyp);
      OfrontOPM_FPrint(&pbfp, btyp->pvfp);
      pvfp = pbfp;
    } else {
      if (btyp != NIL) {
        OfrontOPT_FPrintStr(btyp);
        OfrontOPM_FPrint(&pbfp, btyp->pbfp);
        OfrontOPM_FPrint(&pvfp, btyp->pvfp);
      }
      OfrontOPM_FPrint(&pvfp, typ->size);
      OfrontOPM_FPrint(&pvfp, typ->align);
      OfrontOPM_FPrint(&pvfp, typ->n);
      OfrontOPT_nofhdfld = 0;
      __21(typ->link, 0, 1);
      if (OfrontOPT_nofhdfld > 512) {
        OfrontOPM_Mark(225, typ->txtpos);
      }
      __26(typ->link);
      OfrontOPM_FPrint(&pvfp, pbfp);
      strobj = typ->strobj;
      if (strobj == NIL || strobj->name == OfrontOPT_null) {
        pbfp = pvfp;
      }
    }
    typ->pbfp = pbfp;
    typ->pvfp = pvfp;
  }
  FPrintStr__20_s = _s.lnk;
}

static void OfrontOPT_FPrintObj (OfrontOPT_Object obj)
{
  INTEGER fprint, f, m;
  SHORTREAL rval;
  OfrontOPS_String ext = NIL;
  OfrontOPS_String _ptr__18 = NIL;
  OfrontOPS_String _ptr__17 = NIL;
  if (!obj->fpdone) {
    fprint = 0;
    obj->fpdone = 1;
    if ((INTEGER)obj->mode == 2) {
      OfrontOPM_FPrint(&fprint, 1);
    } else {
      OfrontOPM_FPrint(&fprint, obj->mode);
    }
    if ((INTEGER)obj->mode == 3) {
      f = obj->typ->form;
      OfrontOPM_FPrint(&fprint, f);
      switch (f) {
        case 1: case 2: case 3: case 17: case 4: 
        case 5: 
          OfrontOPM_FPrint(&fprint, (INTEGER)obj->conval->intval);
          break;
        case 6: 
          OfrontOPM_FPrint(&fprint, (INTEGER)obj->conval->intval);
          OfrontOPM_FPrint(&fprint, (INTEGER)__ASHR(obj->conval->intval, 32, LONGINT));
          break;
        case 9: 
          OfrontOPM_FPrintSet(&fprint, obj->conval->setval);
          break;
        case 7: 
          rval = (SHORTREAL)obj->conval->realval;
          OfrontOPM_FPrintReal(&fprint, rval);
          break;
        case 8: 
          OfrontOPM_FPrintLReal(&fprint, obj->conval->realval);
          break;
        case 10: case 18: 
          _ptr__18 = obj->conval->ext;
          OfrontOPT_FPrintName(&fprint, (void*)_ptr__18->data, _ptr__18->len[0]);
          break;
        case 11: 
          break;
        default: 
          OfrontOPT_err(127);
          break;
      }
    } else if (__IN(obj->mode, 0x06)) {
      OfrontOPM_FPrint(&fprint, obj->vis);
      OfrontOPT_FPrintStr(obj->typ);
      OfrontOPM_FPrint(&fprint, obj->typ->pbfp);
    } else if (__IN(obj->mode, 0x0480)) {
      OfrontOPT_FPrintSign(&fprint, obj->typ, obj->link);
    } else if ((INTEGER)obj->mode == 9) {
      OfrontOPT_FPrintSign(&fprint, obj->typ, obj->link);
      ext = obj->conval->ext;
      if (ext != NIL) {
        m = ext->len[0];
        f = 0;
        OfrontOPM_FPrint(&fprint, m);
        while (f < m) {
          OfrontOPM_FPrint(&fprint, (SHORTINT)(ext->data)[__X(f, ext->len[0], (CHAR*)"OfrontOPT", 141364)]);
          f += 1;
        }
      } else {
        OfrontOPM_FPrint(&fprint, 0);
      }
    } else if ((INTEGER)obj->mode == 5) {
      OfrontOPT_FPrintStr(obj->typ);
      OfrontOPM_FPrint(&fprint, obj->typ->pbfp);
    }
    if ((INTEGER)obj->sysflag != 0) {
      OfrontOPM_FPrint(&fprint, obj->sysflag);
    }
    if (__IN(obj->mode, 0xc2) && obj->entry != NIL) {
      _ptr__17 = obj->entry;
      OfrontOPT_FPrintName(&fprint, (void*)_ptr__17->data, _ptr__17->len[0]);
    }
    obj->fprint = fprint;
  }
}

static void OfrontOPT_FPrintErr (OfrontOPT_Object obj, SHORTINT errno)
{
  SHORTINT i, j;
  CHAR ch;
  if ((INTEGER)obj->mnolev != 0) {
    __STRCOPYCC(OfrontOPT_GlbMod[__X(-((INTEGER)obj->mnolev), 64, (CHAR*)"OfrontOPT", 145454)]->name->data, OfrontOPM_objname, __MIN(64, OfrontOPT_GlbMod[__X(-((INTEGER)obj->mnolev), 64, (CHAR*)"OfrontOPT", 145454)]->name->len[0]), (CHAR*)"OfrontOPT", 145454);
    i = 0;
    while (OfrontOPM_objname[__X(i, 64, (CHAR*)"OfrontOPT", 145692)] != 0x00) {
      i += 1;
    }
    OfrontOPM_objname[__X(i, 64, (CHAR*)"OfrontOPT", 145944)] = '.';
    j = 0;
    i += 1;
    do {
      ch = (obj->name->data)[__X(j, obj->name->len[0], (CHAR*)"OfrontOPT", 146204)];
      OfrontOPM_objname[__X(i, 64, (CHAR*)"OfrontOPT", 146226)] = ch;
      j += 1;
      i += 1;
    } while (!(ch == 0x00));
  } else {
    __STRCOPYCC(obj->name->data, OfrontOPM_objname, __MIN(64, obj->name->len[0]), (CHAR*)"OfrontOPT", 146943);
  }
  if ((INTEGER)errno == 249) {
    if (OfrontOPM_noerr) {
      OfrontOPT_err(errno);
    }
  } else if ((INTEGER)errno == 253) {
    if ((!OfrontOPT_symNew && !OfrontOPT_symExtended) && !OfrontOPT_extsf) {
      OfrontOPT_err(errno);
    }
    OfrontOPT_symExtended = 1;
  } else {
    if (!OfrontOPT_symNew && !OfrontOPT_newsf) {
      OfrontOPT_err(errno);
    }
    OfrontOPT_symNew = 1;
  }
}

void OfrontOPT_InsertImport (OfrontOPT_Object obj, OfrontOPT_Object *root, OfrontOPT_Object *old)
{
  OfrontOPT_Object ob0 = NIL;
  OfrontOPT_Object ob1 = NIL;
  BOOLEAN left;
  if (*root == NIL) {
    *root = obj;
    *old = NIL;
  } else {
    ob0 = *root;
    ob1 = ob0->right;
    left = 0;
    if (__STRCMPCC(obj->name->data, ob0->name->data, ob0->name->len[0], (CHAR*)"OfrontOPT", 152838) < 0) {
      ob1 = ob0->left;
      left = 1;
    } else if (__STRCMPCC(obj->name->data, ob0->name->data, ob0->name->len[0], (CHAR*)"OfrontOPT", 152319) > 0) {
      ob1 = ob0->right;
      left = 0;
    } else {
      *old = ob0;
      return;
    }
    for (;;) {
      if (ob1 != NIL) {
        if (__STRCMPCC(obj->name->data, ob1->name->data, ob1->name->len[0], (CHAR*)"OfrontOPT", 154623) < 0) {
          ob0 = ob1;
          ob1 = ob1->left;
          left = 1;
        } else if (__STRCMPCC(obj->name->data, ob1->name->data, ob1->name->len[0], (CHAR*)"OfrontOPT", 153855) > 0) {
          ob0 = ob1;
          ob1 = ob1->right;
          left = 0;
        } else {
          *old = ob1;
          break;
        }
      } else {
        ob1 = obj;
        if (left) {
          ob0->left = ob1;
        } else {
          ob0->right = ob1;
        }
        ob1->left = NIL;
        ob1->right = NIL;
        *old = NIL;
        break;
      }
    }
  }
}

/*----------------------------------------------------------------------------*/
static void OfrontOPT_InName (OfrontOPS_String *name)
{
  SHORTINT i;
  CHAR ch;
  OfrontOPS_Name n;
  *name = NIL;
  i = 0;
  do {
    OfrontOPM_SymRCh(&ch);
    n[__X(i, 48, (CHAR*)"OfrontOPT", 157725)] = ch;
    i += 1;
  } while (!(ch == 0x00));
  if ((INTEGER)i > 1) {
    *name = __NEWARR(NIL, 1, 1, 1, 1, (SYSTEM_ARRLEN)i);
    __STRCOPYCC(n, (*name)->data, __MIN((*name)->len[0], 48), (CHAR*)"OfrontOPT", 158249);
  } else {
    *name = OfrontOPT_null;
  }
}

static void OfrontOPT_InMod (BYTE *mno)
{
  OfrontOPT_Object head = NIL;
  OfrontOPS_String name = NIL;
  INTEGER mn;
  BYTE i, sysflag;
  mn = (INTEGER)OfrontOPM_SymRInt();
  if (mn == 0) {
    *mno = OfrontOPT_impCtxt.glbmno[0];
  } else {
    if (mn == 35) {
      sysflag = (BYTE)OfrontOPM_SymRInt();
      if (__ODD(__ASHR((INTEGER)sysflag, 1, INTEGER)) && !OfrontOPT_impCtxt.self) {
        OfrontOPM_opt |= __SETOF(19);
      }
      mn = (INTEGER)OfrontOPM_SymRInt();
    } else {
      sysflag = 0;
    }
    if (mn == 16) {
      OfrontOPT_InName(&name);
      if (__STRCMPCC(name->data, OfrontOPT_SelfName, 48, (CHAR*)"OfrontOPT", 162875) == 0 && !OfrontOPT_impCtxt.self) {
        OfrontOPT_err(154);
      }
      i = 0;
      while ((INTEGER)i < (INTEGER)OfrontOPT_nofGmod && __STRCMPCC(name->data, OfrontOPT_GlbMod[__X(i, 64, (CHAR*)"OfrontOPT", 163379)]->name->data, OfrontOPT_GlbMod[__X(i, 64, (CHAR*)"OfrontOPT", 163379)]->name->len[0], (CHAR*)"OfrontOPT", 163379) != 0) {
        i += 1;
      }
      if ((INTEGER)i < (INTEGER)OfrontOPT_nofGmod) {
        *mno = i;
      } else {
        head = OfrontOPT_NewObj();
        head->mode = 12;
        head->name = name;
        head->sysflag = sysflag;
        *mno = OfrontOPT_nofGmod;
        head->mnolev = (BYTE)(-((INTEGER)*mno));
        if ((INTEGER)OfrontOPT_nofGmod < 64) {
          OfrontOPT_GlbMod[__X(*mno, 64, (CHAR*)"OfrontOPT", 165145)] = head;
          OfrontOPT_nofGmod += 1;
        } else {
          OfrontOPT_err(227);
        }
      }
      OfrontOPT_impCtxt.glbmno[__X(OfrontOPT_impCtxt.nofm, 64, (CHAR*)"OfrontOPT", 166183)] = *mno;
      OfrontOPT_impCtxt.nofm += 1;
    } else {
      *mno = OfrontOPT_impCtxt.glbmno[__X(-mn, 64, (CHAR*)"OfrontOPT", 166911)];
    }
  }
}

static void OfrontOPT_InConstant (INTEGER f, OfrontOPT_Const conval)
{
  CHAR ch;
  INTEGER i, x, y;
  OfrontOPS_String ext = NIL;
  OfrontOPS_String t = NIL;
  SHORTREAL rval;
  OfrontOPS_Name str;
  switch (f) {
    case 3: case 2: 
      OfrontOPM_SymRCh(&ch);
      conval->intval = (SHORTINT)ch;
      break;
    case 1: case 4: case 5: case 6: 
      conval->intval = OfrontOPM_SymRInt();
      break;
    case 17: 
      OfrontOPM_SymRCh(&ch);
      conval->intval = (SHORTINT)ch;
      OfrontOPM_SymRCh(&ch);
      conval->intval = conval->intval + (LONGINT)__ASHL((INTEGER)ch, 8, INTEGER);
      break;
    case 9: 
      OfrontOPM_SymRSet(&conval->setval);
      break;
    case 7: 
      OfrontOPM_SymRReal(&rval);
      conval->realval = rval;
      conval->intval = -1;
      break;
    case 8: 
      OfrontOPM_SymRLReal(&conval->realval);
      conval->intval = -1;
      break;
    case 10: case 18: 
      i = 0;
      do {
        OfrontOPM_SymRCh(&ch);
        if (i < 47) {
          str[__X(i, 48, (CHAR*)"OfrontOPT", 174079)] = ch;
        } else if (i == 47) {
          str[__X(i, 48, (CHAR*)"OfrontOPT", 174124)] = 0x00;
          ext = __NEWARR(NIL, 1, 1, 1, 1, (SYSTEM_ARRLEN)96);
          __STRCOPYCC(str, ext->data, __MIN(ext->len[0], 48), (CHAR*)"OfrontOPT", 174162);
          (ext->data)[__X(i, ext->len[0], (CHAR*)"OfrontOPT", 174335)] = ch;
        } else if (i < ext->len[0] - 1) {
          (ext->data)[__X(i, ext->len[0], (CHAR*)"OfrontOPT", 174591)] = ch;
        } else {
          t = ext;
          (t->data)[__X(i, t->len[0], (CHAR*)"OfrontOPT", 174621)] = 0x00;
          ext = __NEWARR(NIL, 1, 1, 1, 1, (SYSTEM_ARRLEN)(__ASHL(t->len[0], 1, INTEGER)));
          __STRCOPYCC(t->data, ext->data, __MIN(ext->len[0], t->len[0]), (CHAR*)"OfrontOPT", 174657);
          (ext->data)[__X(i, ext->len[0], (CHAR*)"OfrontOPT", 174847)] = ch;
        }
        i += 1;
      } while (!(ch == 0x00));
      if (i < 48) {
        ext = __NEWARR(NIL, 1, 1, 1, 1, (SYSTEM_ARRLEN)i);
        __STRCOPYCC(str, ext->data, __MIN(ext->len[0], 48), (CHAR*)"OfrontOPT", 175665);
      }
      conval->ext = ext;
      conval->intval = -1;
      if (f == 10) {
        conval->intval2 = i;
      } else {
        i = 0;
        y = 0;
        do {
          OfrontOPM_GetUtf8((void*)ext->data, ext->len[0], &x, &i);
          y += 1;
        } while (!(x == 0));
        conval->intval2 = y;
      }
      break;
    case 11: 
      conval->intval = 0;
      break;
    default: __CASECHK((CHAR*)"OfrontOPT", 178175);
  }
}

static void OfrontOPT_InSign (BYTE mno, OfrontOPT_Struct *res, OfrontOPT_Object *par)
{
  OfrontOPT_Object last = NIL;
  OfrontOPT_Object new = NIL;
  INTEGER tag;
  OfrontOPT_InStruct(res);
  tag = (INTEGER)OfrontOPM_SymRInt();
  last = NIL;
  while (tag != 18) {
    new = OfrontOPT_NewObj();
    new->mnolev = (BYTE)(-((INTEGER)mno));
    if (last == NIL) {
      *par = new;
    } else {
      last->link = new;
    }
    if (tag == 35) {
      new->sysflag = (BYTE)OfrontOPM_SymRInt();
      tag = (INTEGER)OfrontOPM_SymRInt();
      if (__ODD(__ASHR((INTEGER)new->sysflag, 1, INTEGER))) {
        new->vis = 3;
      } else if (__ODD(__ASHR((INTEGER)new->sysflag, 2, INTEGER))) {
        new->vis = 4;
      }
    }
    if (tag == 23) {
      new->mode = 1;
    } else {
      new->mode = 2;
      if (tag == 25) {
        new->vis = 3;
      } else if (tag == 26) {
        new->vis = 4;
      }
    }
    OfrontOPT_InStruct(&new->typ);
    new->adr = (INTEGER)OfrontOPM_SymRInt();
    OfrontOPT_InName(&new->name);
    last = new;
    tag = (INTEGER)OfrontOPM_SymRInt();
  }
}

static OfrontOPT_Object OfrontOPT_InFld (void)
{
  INTEGER tag;
  OfrontOPT_Object obj = NIL;
  tag = OfrontOPT_impCtxt.nextTag;
  obj = OfrontOPT_NewObj();
  if (tag <= 26) {
    obj->mode = 4;
    switch (tag) {
      case 25: 
        obj->vis = 1;
        break;
      case 26: 
        obj->vis = 2;
        break;
      default: 
        obj->vis = 0;
        break;
    }
    OfrontOPT_InStruct(&obj->typ);
    OfrontOPT_InName(&obj->name);
    obj->adr = (INTEGER)OfrontOPM_SymRInt();
  } else {
    obj->mode = 4;
    if (tag == 27) {
      obj->name = OfrontOPT_NewName((CHAR*)"@ptr", 5);
    } else {
      obj->name = OfrontOPT_NewName((CHAR*)"@proc", 6);
    }
    obj->typ = OfrontOPT_undftyp;
    obj->vis = 0;
    obj->adr = (INTEGER)OfrontOPM_SymRInt();
  }
  return obj;
}

static OfrontOPT_Object OfrontOPT_InTProc (BYTE mno)
{
  INTEGER tag;
  OfrontOPT_Object obj = NIL;
  tag = OfrontOPT_impCtxt.nextTag;
  obj = OfrontOPT_NewObj();
  obj->mnolev = (BYTE)(-((INTEGER)mno));
  if (tag == 30) {
    obj->mode = 13;
    obj->name = OfrontOPT_NewName((CHAR*)"@tproc", 7);
    obj->link = OfrontOPT_NewObj();
    obj->typ = OfrontOPT_undftyp;
    obj->vis = 0;
    obj->adr = __ASHL((INTEGER)OfrontOPM_SymRInt(), 16, INTEGER);
  } else {
    obj->vis = 1;
    if (tag == 22) {
      obj->vis = 2;
      tag = (INTEGER)OfrontOPM_SymRInt();
    }
    obj->mode = 13;
    obj->conval = OfrontOPT_NewConst();
    obj->conval->intval = -1;
    OfrontOPT_InSign(mno, &obj->typ, &obj->link);
    OfrontOPT_InName(&obj->name);
    obj->adr = __ASHL((INTEGER)OfrontOPM_SymRInt(), 16, INTEGER);
    if (tag == 31) {
      obj->conval->setval |= __SETOF(18);
    } else if (tag == 32) {
      obj->conval->setval |= __SETOF(17);
    } else if (tag == 33) {
      obj->conval->setval |= __SETOF(19);
    } else if (tag == 34) {
      obj->conval->setval |= __SETOF(20);
    }
  }
  return obj;
}

static void OfrontOPT_InStruct (OfrontOPT_Struct *typ)
{
  BYTE mno;
  SHORTINT ref;
  INTEGER tag;
  OfrontOPS_String name = NIL;
  OfrontOPT_Struct t = NIL;
  OfrontOPT_Object obj = NIL;
  OfrontOPT_Object last = NIL;
  OfrontOPT_Object fld = NIL;
  OfrontOPT_Object old = NIL;
  OfrontOPT_Object dummy = NIL;
  tag = (INTEGER)OfrontOPM_SymRInt();
  if (tag != 34) {
    *typ = OfrontOPT_impCtxt.ref[__X(-tag, 1754, (CHAR*)"OfrontOPT", 198399)];
  } else {
    ref = OfrontOPT_impCtxt.nofr;
    OfrontOPT_impCtxt.nofr += 1;
    if ((INTEGER)ref < (INTEGER)OfrontOPT_impCtxt.minr) {
      OfrontOPT_impCtxt.minr = ref;
    }
    OfrontOPT_InMod(&mno);
    OfrontOPT_InName(&name);
    obj = OfrontOPT_NewObj();
    if (name == OfrontOPT_null) {
      if (OfrontOPT_impCtxt.self) {
        old = NIL;
      } else {
        obj->name = OfrontOPT_NewName((CHAR*)"@", 2);
        OfrontOPT_InsertImport(obj, &OfrontOPT_GlbMod[__X(mno, 64, (CHAR*)"OfrontOPT", 200021)]->right, &old);
        obj->name = OfrontOPT_null;
      }
      *typ = OfrontOPT_NewStr(0, 1);
    } else {
      obj->name = name;
      OfrontOPT_InsertImport(obj, &OfrontOPT_GlbMod[__X(mno, 64, (CHAR*)"OfrontOPT", 200772)]->right, &old);
      if (old != NIL) {
        OfrontOPT_FPrintObj(old);
        OfrontOPT_impCtxt.pvfp[__X(ref, 1754, (CHAR*)"OfrontOPT", 201272)] = old->typ->pvfp;
        if (OfrontOPT_impCtxt.self) {
          *typ = OfrontOPT_NewStr(0, 1);
        } else {
          *typ = old->typ;
          (*typ)->link = NIL;
          (*typ)->sysflag = 0;
          (*typ)->fpdone = 0;
          (*typ)->idfpdone = 0;
        }
      } else {
        *typ = OfrontOPT_NewStr(0, 1);
      }
    }
    OfrontOPT_impCtxt.ref[__X(ref, 1754, (CHAR*)"OfrontOPT", 203802)] = *typ;
    OfrontOPT_impCtxt.old[__X(ref, 1754, (CHAR*)"OfrontOPT", 203827)] = old;
    (*typ)->ref = (SHORTINT)((INTEGER)ref + 1754);
    (*typ)->mno = mno;
    (*typ)->allocated = 1;
    (*typ)->strobj = obj;
    obj->mode = 5;
    obj->typ = *typ;
    obj->mnolev = (BYTE)(-((INTEGER)mno));
    obj->vis = 0;
    tag = (INTEGER)OfrontOPM_SymRInt();
    if (tag == 35) {
      (*typ)->sysflag = (SHORTINT)OfrontOPM_SymRInt();
      tag = (INTEGER)OfrontOPM_SymRInt();
    }
    switch (tag) {
      case 36: 
        (*typ)->form = 13;
        (*typ)->size = OfrontOPM_AdrSize;
        (*typ)->n = 0;
        OfrontOPT_InStruct(&(*typ)->BaseTyp);
        break;
      case 37: 
        (*typ)->form = 16;
        (*typ)->comp = 2;
        OfrontOPT_InStruct(&(*typ)->BaseTyp);
        (*typ)->n = (INTEGER)OfrontOPM_SymRInt();
        (*OfrontOPT_typSize)(*typ);
        break;
      case 38: 
        (*typ)->form = 16;
        (*typ)->comp = 3;
        OfrontOPT_InStruct(&(*typ)->BaseTyp);
        if ((INTEGER)(*typ)->BaseTyp->comp == 3) {
          (*typ)->n = (*typ)->BaseTyp->n + 1;
        } else {
          (*typ)->n = 0;
        }
        (*OfrontOPT_typSize)(*typ);
        break;
      case 39: case 26: case 25: case 27: 
        (*typ)->form = 16;
        (*typ)->comp = 4;
        OfrontOPT_InStruct(&(*typ)->BaseTyp);
        if ((*typ)->BaseTyp == OfrontOPT_notyp) {
          (*typ)->BaseTyp = NIL;
        }
        (*typ)->extlev = 0;
        t = (*typ)->BaseTyp;
        while (t != NIL && (INTEGER)t->comp == 4) {
          (*typ)->extlev += 1;
          t = t->BaseTyp;
        }
        (*typ)->size = (INTEGER)OfrontOPM_SymRInt();
        (*typ)->align = (INTEGER)OfrontOPM_SymRInt();
        (*typ)->n = (INTEGER)OfrontOPM_SymRInt();
        if (tag == 26) {
          (*typ)->attribute = 17;
        } else if (tag == 25) {
          (*typ)->attribute = 18;
        } else if (tag == 27) {
          (*typ)->attribute = 20;
        }
        OfrontOPT_impCtxt.nextTag = (INTEGER)OfrontOPM_SymRInt();
        last = NIL;
        while (((OfrontOPT_impCtxt.nextTag >= 25 && OfrontOPT_impCtxt.nextTag <= 28) || OfrontOPT_impCtxt.nextTag == 17) || OfrontOPT_impCtxt.nextTag == 35) {
          fld = OfrontOPT_InFld();
          fld->mnolev = (BYTE)(-((INTEGER)mno));
          if (last != NIL) {
            last->link = fld;
          }
          last = fld;
          OfrontOPT_InsertImport(fld, &(*typ)->link, &dummy);
          OfrontOPT_impCtxt.nextTag = (INTEGER)OfrontOPM_SymRInt();
        }
        while (OfrontOPT_impCtxt.nextTag != 18) {
          fld = OfrontOPT_InTProc(mno);
          OfrontOPT_InsertImport(fld, &(*typ)->link, &dummy);
          OfrontOPT_impCtxt.nextTag = (INTEGER)OfrontOPM_SymRInt();
        }
        break;
      case 40: 
        (*typ)->form = 15;
        (*typ)->size = OfrontOPM_AdrSize;
        OfrontOPT_InSign(mno, &(*typ)->BaseTyp, &(*typ)->link);
        break;
      case 20: 
        OfrontOPT_InStruct(&t);
        (*typ)->form = t->form;
        (*typ)->comp = 1;
        (*typ)->size = t->size;
        (*typ)->pbfp = t->pbfp;
        (*typ)->pvfp = t->pvfp;
        (*typ)->fpdone = 1;
        (*typ)->idfp = t->idfp;
        (*typ)->idfpdone = 1;
        (*typ)->BaseTyp = t;
        break;
      default: __CASECHK((CHAR*)"OfrontOPT", 217343);
    }
    if ((INTEGER)ref == (INTEGER)OfrontOPT_impCtxt.minr) {
      while ((INTEGER)ref < (INTEGER)OfrontOPT_impCtxt.nofr) {
        t = OfrontOPT_impCtxt.ref[__X(ref, 1754, (CHAR*)"OfrontOPT", 218138)];
        OfrontOPT_FPrintStr(t);
        obj = t->strobj;
        if (obj->name != OfrontOPT_null) {
          OfrontOPT_FPrintObj(obj);
        }
        old = OfrontOPT_impCtxt.old[__X(ref, 1754, (CHAR*)"OfrontOPT", 218908)];
        if (old != NIL) {
          t->strobj = old;
          if (OfrontOPT_impCtxt.self) {
            if ((INTEGER)old->mnolev < 0) {
              if ((INTEGER)old->history != 5) {
                if (old->fprint != obj->fprint) {
                  old->history = 2;
                } else if (OfrontOPT_impCtxt.pvfp[__X(ref, 1754, (CHAR*)"OfrontOPT", 220415)] != t->pvfp) {
                  old->history = 3;
                }
              }
            } else if (old->fprint != obj->fprint) {
              old->history = 2;
            } else if (OfrontOPT_impCtxt.pvfp[__X(ref, 1754, (CHAR*)"OfrontOPT", 221695)] != t->pvfp) {
              old->history = 3;
            } else if ((INTEGER)old->vis == 0) {
              old->history = 1;
            } else {
              old->history = 0;
            }
          } else {
            if (OfrontOPT_impCtxt.pvfp[__X(ref, 1754, (CHAR*)"OfrontOPT", 223307)] != t->pvfp) {
              old->history = 5;
            }
            if (old->fprint != obj->fprint) {
              OfrontOPT_FPrintErr(old, 249);
            }
          }
        } else if (OfrontOPT_impCtxt.self) {
          obj->history = 4;
        } else {
          obj->history = 1;
        }
        ref += 1;
      }
      OfrontOPT_impCtxt.minr = 1754;
    }
  }
}

static OfrontOPT_Object OfrontOPT_InObj (BYTE mno)
{
  CHAR ch;
  OfrontOPT_Object obj = NIL;
  OfrontOPT_Object old = NIL;
  OfrontOPT_Struct typ = NIL;
  INTEGER i, s, tag;
  OfrontOPS_String ext = NIL;
  tag = OfrontOPT_impCtxt.nextTag;
  if (tag == 19) {
    OfrontOPT_InStruct(&typ);
    obj = typ->strobj;
    if (!OfrontOPT_impCtxt.self) {
      obj->vis = 1;
    }
  } else {
    obj = OfrontOPT_NewObj();
    obj->mnolev = (BYTE)(-((INTEGER)mno));
    obj->vis = 1;
    if (tag == 35) {
      obj->sysflag = (BYTE)OfrontOPM_SymRInt();
      tag = (INTEGER)OfrontOPM_SymRInt();
    }
    if (tag == 43) {
      OfrontOPT_InName(&obj->entry);
      tag = (INTEGER)OfrontOPM_SymRInt();
    }
    if ((tag <= 14 || tag == 17) || tag == 18) {
      obj->mode = 3;
      obj->typ = OfrontOPT_impCtxt.ref[__X(tag, 1754, (CHAR*)"OfrontOPT", 230962)];
      obj->conval = OfrontOPT_NewConst();
      OfrontOPT_InConstant(tag, obj->conval);
    } else if (tag >= 31) {
      obj->conval = OfrontOPT_NewConst();
      obj->conval->intval = -1;
      OfrontOPT_InSign(mno, &obj->typ, &obj->link);
      switch (tag) {
        case 31: 
          obj->mode = 7;
          break;
        case 32: 
          obj->mode = 10;
          break;
        case 33: 
          obj->mode = 9;
          s = (INTEGER)OfrontOPM_SymRInt();
          if (s > 0) {
            ext = __NEWARR(NIL, 1, 1, 1, 1, (SYSTEM_ARRLEN)s);
            i = 0;
            while (i < s) {
              OfrontOPM_SymRCh(&(ext->data)[__X(i, ext->len[0], (CHAR*)"OfrontOPT", 233768)]);
              i += 1;
            }
          } else {
            ext = NIL;
          }
          obj->conval->ext = ext;
          break;
        default: __CASECHK((CHAR*)"OfrontOPT", 234751);
      }
    } else if (tag == 20) {
      obj->mode = 5;
      OfrontOPT_InStruct(&obj->typ);
    } else {
      obj->mode = 1;
      if (tag == 22) {
        obj->vis = 2;
      }
      OfrontOPT_InStruct(&obj->typ);
    }
    OfrontOPT_InName(&obj->name);
  }
  OfrontOPT_FPrintObj(obj);
  if ((INTEGER)obj->mode == 1 && (obj->typ->strobj == NIL || obj->typ->strobj->name == OfrontOPT_null)) {
    OfrontOPM_FPrint(&OfrontOPT_impCtxt.reffp, (INTEGER)obj->typ->ref - 1754);
  }
  if (tag != 19) {
    OfrontOPT_InsertImport(obj, &OfrontOPT_GlbMod[__X(mno, 64, (CHAR*)"OfrontOPT", 238892)]->right, &old);
    if (OfrontOPT_impCtxt.self) {
      if (old != NIL) {
        if ((INTEGER)old->vis == 0) {
          old->history = 4;
        } else {
          OfrontOPT_FPrintObj(old);
          OfrontOPT_FPrintStr(old->typ);
          if (obj->fprint != old->fprint) {
            old->history = 2;
          } else if (obj->typ->pvfp != old->typ->pvfp) {
            old->history = 3;
          } else {
            old->history = 1;
          }
        }
      } else {
        obj->history = 4;
      }
    }
  } else {
    if (OfrontOPT_impCtxt.self) {
      if ((INTEGER)obj->vis == 0) {
        obj->history = 4;
      } else if ((INTEGER)obj->history == 0) {
        obj->history = 1;
      }
    }
  }
  return obj;
}

void OfrontOPT_Import (CHAR *aliasName, INTEGER aliasName__len, CHAR *name, INTEGER name__len, BOOLEAN *done)
{
  OfrontOPT_Object obj = NIL;
  BYTE mno;
  if (__STRCMPCC(name, (CHAR*)"SYSTEM", 7, (CHAR*)"OfrontOPT", 252159) == 0) {
    OfrontOPT_SYSimported = 1;
    OfrontOPT_Insert((void*)aliasName, aliasName__len, &obj);
    obj->mode = 11;
    obj->mnolev = 0;
    obj->scope = OfrontOPT_syslink;
    obj->typ = OfrontOPT_notyp;
  } else {
    OfrontOPT_impCtxt.nofr = 32;
    OfrontOPT_impCtxt.minr = 1754;
    OfrontOPT_impCtxt.nofm = 0;
    OfrontOPT_impCtxt.self = __STRCMPCC(aliasName, (CHAR*)"@self", 6, (CHAR*)"OfrontOPT", 247334) == 0;
    OfrontOPT_impCtxt.reffp = 0;
    OfrontOPM_OldSym((void*)name, name__len, done);
    if (*done) {
      OfrontOPM_checksum = 0;
      OfrontOPT_InMod(&mno);
      OfrontOPT_impCtxt.nextTag = (INTEGER)OfrontOPM_SymRInt();
      while (!OfrontOPM_eofSF()) {
        obj = OfrontOPT_InObj(mno);
        OfrontOPT_impCtxt.nextTag = (INTEGER)OfrontOPM_SymRInt();
      }
      OfrontOPT_Insert((void*)aliasName, aliasName__len, &obj);
      obj->mode = 11;
      obj->scope = OfrontOPT_GlbMod[__X(mno, 64, (CHAR*)"OfrontOPT", 249909)]->right;
      OfrontOPT_GlbMod[__X(mno, 64, (CHAR*)"OfrontOPT", 250139)]->link = obj;
      obj->mnolev = (BYTE)(-((INTEGER)mno));
      obj->typ = OfrontOPT_notyp;
      OfrontOPM_CloseOldSym();
    } else if (OfrontOPT_impCtxt.self) {
      OfrontOPT_newsf = 1;
      OfrontOPT_extsf = 1;
      OfrontOPT_sfpresent = 0;
    } else {
      OfrontOPT_err(152);
    }
  }
}

/*----------------------------------------------------------------------------*/
static void OfrontOPT_OutName (CHAR *name, INTEGER name__len)
{
  INTEGER i;
  CHAR ch;
  i = 0;
  do {
    ch = name[__X(i, name__len, (CHAR*)"OfrontOPT", 253974)];
    OfrontOPM_SymWCh(ch);
    i += 1;
  } while (!(ch == 0x00));
}

static void OfrontOPT_OutMod (SHORTINT mno)
{
  OfrontOPS_String _ptr__68 = NIL;
  if ((INTEGER)OfrontOPT_expCtxt.locmno[__X(mno, 64, (CHAR*)"OfrontOPT", 257023)] < 0) {
    if ((INTEGER)OfrontOPT_GlbMod[__X(mno, 64, (CHAR*)"OfrontOPT", 255578)]->sysflag != 0) {
      OfrontOPM_SymWInt(35);
      OfrontOPM_SymWInt(OfrontOPT_GlbMod[__X(mno, 64, (CHAR*)"OfrontOPT", 255574)]->sysflag);
    }
    OfrontOPM_SymWInt(16);
    OfrontOPT_expCtxt.locmno[__X(mno, 64, (CHAR*)"OfrontOPT", 256038)] = OfrontOPT_expCtxt.nofm;
    OfrontOPT_expCtxt.nofm += 1;
    _ptr__68 = OfrontOPT_GlbMod[__X(mno, 64, (CHAR*)"OfrontOPT", 256511)]->name;
    OfrontOPT_OutName((void*)_ptr__68->data, _ptr__68->len[0]);
  } else {
    OfrontOPM_SymWInt(-((INTEGER)OfrontOPT_expCtxt.locmno[__X(mno, 64, (CHAR*)"OfrontOPT", 256767)]));
  }
}

static void OfrontOPT_OutHdFld (OfrontOPT_Struct typ, OfrontOPT_Object fld, INTEGER adr)
{
  INTEGER i, j, n;
  OfrontOPT_Struct btyp = NIL;
  if ((INTEGER)typ->comp == 4) {
    OfrontOPT_OutFlds(typ->link, adr, 0);
  } else if ((INTEGER)typ->comp == 2) {
    btyp = typ->BaseTyp;
    n = typ->n;
    while ((INTEGER)btyp->comp == 2) {
      n = btyp->n * n;
      btyp = btyp->BaseTyp;
    }
    if ((INTEGER)btyp->form == 13 || (INTEGER)btyp->comp == 4) {
      j = OfrontOPT_nofhdfld;
      OfrontOPT_OutHdFld(btyp, fld, adr);
      if (j != OfrontOPT_nofhdfld) {
        i = 1;
        while (i < n && OfrontOPT_nofhdfld <= 512) {
          adr += btyp->size;
          OfrontOPT_OutHdFld(btyp, fld, adr);
          i += 1;
        }
      }
    }
  } else if ((INTEGER)typ->form == 13 || __STRCMPCC(fld->name->data, (CHAR*)"@ptr", 5, (CHAR*)"OfrontOPT", 261119) == 0) {
    OfrontOPM_SymWInt(27);
    OfrontOPM_SymWInt(adr);
    OfrontOPT_nofhdfld += 1;
  }
}

BOOLEAN OfrontOPT_ContainsRealType (OfrontOPT_Struct typ)
{
  OfrontOPT_Object fld = NIL;
  if (typ == NIL) {
    return 0;
  }
  if (__IN(typ->form, 0x0180)) {
    return 1;
  }
  switch (typ->comp) {
    case 2: 
      return OfrontOPT_ContainsRealType(typ->BaseTyp);
      break;
    case 4: 
      if (OfrontOPT_ContainsRealType(typ->BaseTyp)) {
        return 1;
      }
      fld = typ->link;
      while (fld != NIL && (INTEGER)fld->mode == 4) {
        if (OfrontOPT_ContainsRealType(fld->typ)) {
          return 1;
        }
        fld = fld->link;
      }
      break;
    default: 
      break;
  }
  return 0;
}

/*----------------------------------------------------------------------------*/
static void OfrontOPT_OutFlds (OfrontOPT_Object fld, INTEGER adr, BOOLEAN visible)
{
  OfrontOPS_String _ptr__65 = NIL;
  OfrontOPS_String _ptr__64 = NIL;
  while (fld != NIL && (INTEGER)fld->mode == 4) {
    if ((INTEGER)fld->vis != 0 && visible) {
      if ((INTEGER)fld->vis == 2) {
        OfrontOPM_SymWInt(26);
      } else {
        OfrontOPM_SymWInt(25);
      }
      OfrontOPT_OutStr(fld->typ);
      _ptr__65 = fld->name;
      OfrontOPT_OutName((void*)_ptr__65->data, _ptr__65->len[0]);
      OfrontOPM_SymWInt(fld->adr);
    } else if (OfrontOPT_ContainsRealType(fld->typ)) {
      OfrontOPM_SymWInt(17);
      OfrontOPT_OutStr(fld->typ);
      _ptr__64 = fld->name;
      OfrontOPT_OutName((void*)_ptr__64->data, _ptr__64->len[0]);
      OfrontOPM_SymWInt(fld->adr);
    } else {
      OfrontOPT_OutHdFld(fld->typ, fld, fld->adr + adr);
    }
    fld = fld->link;
  }
}

static void OfrontOPT_OutSign (OfrontOPT_Struct result, OfrontOPT_Object par)
{
  OfrontOPS_String _ptr__79 = NIL;
  OfrontOPT_OutStr(result);
  while (par != NIL) {
    if ((INTEGER)par->sysflag != 0) {
      OfrontOPM_SymWInt(35);
      OfrontOPM_SymWInt(par->sysflag);
    }
    if ((INTEGER)par->mode == 1) {
      OfrontOPM_SymWInt(23);
    } else if ((INTEGER)par->vis == 3) {
      OfrontOPM_SymWInt(25);
    } else if ((INTEGER)par->vis == 4) {
      OfrontOPM_SymWInt(26);
    } else {
      OfrontOPM_SymWInt(24);
    }
    OfrontOPT_OutStr(par->typ);
    OfrontOPM_SymWInt(par->adr);
    _ptr__79 = par->name;
    OfrontOPT_OutName((void*)_ptr__79->data, _ptr__79->len[0]);
    par = par->link;
  }
  OfrontOPM_SymWInt(18);
}

static void OfrontOPT_OutTProcs (OfrontOPT_Struct typ, OfrontOPT_Object obj)
{
  OfrontOPS_String _ptr__83 = NIL;
  if (obj != NIL) {
    if ((INTEGER)obj->mode == 13) {
      if ((INTEGER)obj->vis != 0) {
        if ((INTEGER)obj->vis == 2) {
          OfrontOPM_SymWInt(22);
        }
        if (__IN(18, obj->conval->setval)) {
          OfrontOPM_SymWInt(31);
        } else if (__IN(17, obj->conval->setval)) {
          OfrontOPM_SymWInt(32);
        } else if (__IN(19, obj->conval->setval)) {
          OfrontOPM_SymWInt(33);
        } else if (__IN(20, obj->conval->setval)) {
          OfrontOPM_SymWInt(34);
        } else {
          OfrontOPM_SymWInt(29);
        }
        OfrontOPT_OutSign(obj->typ, obj->link);
        _ptr__83 = obj->name;
        OfrontOPT_OutName((void*)_ptr__83->data, _ptr__83->len[0]);
        OfrontOPM_SymWInt(__ASHR(obj->adr, 16, INTEGER));
      }
    }
    OfrontOPT_OutTProcs(typ, obj->left);
    OfrontOPT_OutTProcs(typ, obj->right);
  }
}

static void OfrontOPT_OutStr (OfrontOPT_Struct typ)
{
  OfrontOPT_Object strobj = NIL;
  OfrontOPS_String _ptr__81 = NIL;
  if ((INTEGER)typ->ref < (INTEGER)OfrontOPT_expCtxt.ref) {
    OfrontOPM_SymWInt(-((INTEGER)typ->ref));
  } else {
    OfrontOPM_SymWInt(34);
    typ->ref = OfrontOPT_expCtxt.ref;
    OfrontOPT_expCtxt.ref += 1;
    if ((INTEGER)OfrontOPT_expCtxt.ref >= 1754) {
      OfrontOPT_err(228);
    }
    OfrontOPT_OutMod(typ->mno);
    strobj = typ->strobj;
    if (strobj != NIL && strobj->name != OfrontOPT_null) {
      _ptr__81 = strobj->name;
      OfrontOPT_OutName((void*)_ptr__81->data, _ptr__81->len[0]);
      switch (strobj->history) {
        case 2: 
          OfrontOPT_FPrintErr(strobj, 252);
          break;
        case 3: 
          OfrontOPT_FPrintErr(strobj, 251);
          break;
        case 5: 
          OfrontOPT_FPrintErr(strobj, 249);
          break;
        default: 
          break;
      }
    } else {
      OfrontOPM_SymWCh(0x00);
    }
    if ((INTEGER)typ->sysflag != 0) {
      OfrontOPM_SymWInt(35);
      OfrontOPM_SymWInt(typ->sysflag);
    }
    switch (typ->form) {
      case 13: 
        OfrontOPM_SymWInt(36);
        OfrontOPT_OutStr(typ->BaseTyp);
        break;
      case 15: 
        OfrontOPM_SymWInt(40);
        OfrontOPT_OutSign(typ->BaseTyp, typ->link);
        break;
      case 16: 
        switch (typ->comp) {
          case 2: 
            OfrontOPM_SymWInt(37);
            OfrontOPT_OutStr(typ->BaseTyp);
            OfrontOPM_SymWInt(typ->n);
            break;
          case 3: 
            OfrontOPM_SymWInt(38);
            OfrontOPT_OutStr(typ->BaseTyp);
            break;
          case 4: 
            if ((INTEGER)typ->attribute == 18) {
              OfrontOPM_SymWInt(25);
            } else if ((INTEGER)typ->attribute == 17) {
              OfrontOPM_SymWInt(26);
            } else if ((INTEGER)typ->attribute == 20) {
              OfrontOPM_SymWInt(27);
            } else {
              OfrontOPM_SymWInt(39);
            }
            if (typ->BaseTyp == NIL) {
              OfrontOPT_OutStr(OfrontOPT_notyp);
            } else {
              OfrontOPT_OutStr(typ->BaseTyp);
            }
            OfrontOPM_SymWInt(typ->size);
            OfrontOPM_SymWInt(typ->align);
            OfrontOPM_SymWInt(typ->n);
            OfrontOPT_nofhdfld = 0;
            OfrontOPT_OutFlds(typ->link, 0, 1);
            if (OfrontOPT_nofhdfld > 512) {
              OfrontOPM_Mark(223, typ->txtpos);
            }
            OfrontOPT_OutTProcs(typ, typ->link);
            OfrontOPM_SymWInt(18);
            break;
          default: __CASECHK((CHAR*)"OfrontOPT", 293631);
        }
        break;
      default: 
        OfrontOPM_SymWInt(20);
        OfrontOPT_OutStr(typ->BaseTyp);
        break;
    }
  }
}

static void OfrontOPT_OutConstant (OfrontOPT_Object obj)
{
  SHORTINT f;
  SHORTREAL rval;
  OfrontOPS_String _ptr__62 = NIL;
  f = obj->typ->form;
  OfrontOPM_SymWInt(f);
  switch (f) {
    case 2: case 3: 
      OfrontOPM_SymWCh((CHAR)obj->conval->intval);
      break;
    case 17: 
      OfrontOPM_SymWCh((CHAR)__MASK(obj->conval->intval, -256));
      OfrontOPM_SymWCh((CHAR)__ASHR(obj->conval->intval, 8, LONGINT));
      break;
    case 1: case 4: case 5: case 6: 
      OfrontOPM_SymWInt(obj->conval->intval);
      break;
    case 9: 
      OfrontOPM_SymWSet(obj->conval->setval);
      break;
    case 7: 
      rval = (SHORTREAL)obj->conval->realval;
      OfrontOPM_SymWReal(rval);
      break;
    case 8: 
      OfrontOPM_SymWLReal(obj->conval->realval);
      break;
    case 10: case 18: 
      _ptr__62 = obj->conval->ext;
      OfrontOPT_OutName((void*)_ptr__62->data, _ptr__62->len[0]);
      break;
    case 11: 
      break;
    default: 
      OfrontOPT_err(127);
      break;
  }
}

static void OfrontOPT_OutObj (OfrontOPT_Object obj)
{
  INTEGER i, j;
  OfrontOPS_String ext = NIL;
  OfrontOPS_String _ptr__77 = NIL;
  OfrontOPS_String _ptr__76 = NIL;
  OfrontOPS_String _ptr__75 = NIL;
  OfrontOPS_String _ptr__74 = NIL;
  OfrontOPS_String _ptr__73 = NIL;
  OfrontOPS_String _ptr__72 = NIL;
  OfrontOPS_String _ptr__71 = NIL;
  if (obj != NIL) {
    OfrontOPT_OutObj(obj->left);
    if (__IN(obj->mode, 0x06ee)) {
      if ((INTEGER)obj->history == 4) {
        OfrontOPT_FPrintErr(obj, 250);
      } else if (__IN(obj->vis, 0x06)) {
        switch (obj->history) {
          case 0: 
            OfrontOPT_FPrintErr(obj, 253);
            break;
          case 1: 
            break;
          case 2: 
            OfrontOPT_FPrintErr(obj, 252);
            break;
          case 3: 
            OfrontOPT_FPrintErr(obj, 251);
            break;
          default: __CASECHK((CHAR*)"OfrontOPT", 305151);
        }
        if ((INTEGER)obj->sysflag != 0) {
          OfrontOPM_SymWInt(35);
          OfrontOPM_SymWInt(obj->sysflag);
        }
        if (__IN(obj->mode, 0xc2)) {
          if (obj->entry != NIL) {
            OfrontOPM_SymWInt(43);
            _ptr__77 = obj->entry;
            OfrontOPT_OutName((void*)_ptr__77->data, _ptr__77->len[0]);
          }
        }
        switch (obj->mode) {
          case 3: 
            OfrontOPT_OutConstant(obj);
            _ptr__76 = obj->name;
            OfrontOPT_OutName((void*)_ptr__76->data, _ptr__76->len[0]);
            break;
          case 5: 
            if (obj->typ->strobj == obj) {
              OfrontOPM_SymWInt(19);
              OfrontOPT_OutStr(obj->typ);
            } else {
              OfrontOPM_SymWInt(20);
              OfrontOPT_OutStr(obj->typ);
              _ptr__75 = obj->name;
              OfrontOPT_OutName((void*)_ptr__75->data, _ptr__75->len[0]);
            }
            break;
          case 1: case 2: 
            if ((INTEGER)obj->vis == 2) {
              OfrontOPM_SymWInt(22);
            } else {
              OfrontOPM_SymWInt(21);
            }
            OfrontOPT_OutStr(obj->typ);
            _ptr__74 = obj->name;
            OfrontOPT_OutName((void*)_ptr__74->data, _ptr__74->len[0]);
            if (obj->typ->strobj == NIL || obj->typ->strobj->name == OfrontOPT_null) {
              OfrontOPM_FPrint(&OfrontOPT_expCtxt.reffp, obj->typ->ref);
            }
            break;
          case 7: 
            OfrontOPM_SymWInt(31);
            OfrontOPT_OutSign(obj->typ, obj->link);
            _ptr__73 = obj->name;
            OfrontOPT_OutName((void*)_ptr__73->data, _ptr__73->len[0]);
            break;
          case 10: 
            OfrontOPM_SymWInt(32);
            OfrontOPT_OutSign(obj->typ, obj->link);
            _ptr__72 = obj->name;
            OfrontOPT_OutName((void*)_ptr__72->data, _ptr__72->len[0]);
            break;
          case 9: 
            OfrontOPM_SymWInt(33);
            OfrontOPT_OutSign(obj->typ, obj->link);
            ext = obj->conval->ext;
            i = 0;
            if (ext != NIL) {
              j = ext->len[0];
            } else {
              j = 0;
            }
            OfrontOPM_SymWInt(j);
            while (i < j) {
              OfrontOPM_SymWCh((ext->data)[__X(i, ext->len[0], (CHAR*)"OfrontOPT", 311848)]);
              i += 1;
            }
            _ptr__71 = obj->name;
            OfrontOPT_OutName((void*)_ptr__71->data, _ptr__71->len[0]);
            break;
          default: __CASECHK((CHAR*)"OfrontOPT", 311825);
        }
      }
    }
    OfrontOPT_OutObj(obj->right);
  }
}

void OfrontOPT_Export (BOOLEAN *ext, BOOLEAN *new)
{
  SHORTINT i;
  BYTE nofmod;
  BOOLEAN done;
  INTEGER oldCSum;
  OfrontOPT_symExtended = 0;
  OfrontOPT_symNew = 0;
  nofmod = OfrontOPT_nofGmod;
  OfrontOPT_Import((CHAR*)"@self", 6, (void*)OfrontOPT_SelfName, 48, &done);
  OfrontOPT_nofGmod = nofmod;
  oldCSum = OfrontOPM_checksum;
  if (OfrontOPM_noerr) {
    OfrontOPM_NewSym((void*)OfrontOPT_SelfName, 48);
    if (OfrontOPM_noerr) {
      OfrontOPM_checksum = 0;
      if ((0xc000 & OfrontOPM_opt) != 0x0) {
        OfrontOPM_SymWInt(35);
        OfrontOPM_SymWInt(1);
      } else if (__IN(19, OfrontOPM_opt)) {
        OfrontOPM_SymWInt(35);
        OfrontOPM_SymWInt(2);
      }
      OfrontOPM_SymWInt(16);
      OfrontOPT_OutName((void*)OfrontOPT_SelfName, 48);
      OfrontOPT_expCtxt.reffp = 0;
      OfrontOPT_expCtxt.ref = 32;
      OfrontOPT_expCtxt.nofm = 1;
      OfrontOPT_expCtxt.locmno[0] = 0;
      i = 1;
      while ((INTEGER)i < 64) {
        OfrontOPT_expCtxt.locmno[__X(i, 64, (CHAR*)"OfrontOPT", 318776)] = -1;
        i += 1;
      }
      OfrontOPT_OutObj(OfrontOPT_topScope->right);
      *ext = OfrontOPT_sfpresent && OfrontOPT_symExtended;
      *new = (!OfrontOPT_sfpresent || OfrontOPT_symNew) || OfrontOPM_checksum != oldCSum;
      if ((OfrontOPM_noerr && OfrontOPT_sfpresent) && OfrontOPT_impCtxt.reffp != OfrontOPT_expCtxt.reffp) {
        *new = 1;
        if (!OfrontOPT_extsf) {
          OfrontOPT_err(155);
        }
      }
      OfrontOPT_newsf = 0;
      OfrontOPT_symNew = 0;
      if (!OfrontOPM_noerr || OfrontOPT_findpc) {
        OfrontOPM_DeleteNewSym();
      }
    }
  }
}

/*----------------------------------------------------------------------------*/
static void OfrontOPT_InitStruct (OfrontOPT_Struct *typ, BYTE form)
{
  *typ = OfrontOPT_NewStr(form, 1);
  (*typ)->ref = form;
  (*typ)->size = 1;
  (*typ)->allocated = 1;
  (*typ)->strobj = OfrontOPT_NewObj();
  (*typ)->pbfp = form;
  (*typ)->pvfp = form;
  (*typ)->fpdone = 1;
  (*typ)->idfp = form;
  (*typ)->idfpdone = 1;
}

static void OfrontOPT_EnterBoolConst (CHAR *name, INTEGER name__len, CHAR *lowcase, INTEGER lowcase__len, INTEGER value)
{
  OfrontOPT_Object obj = NIL;
  OfrontOPT_Insert2((void*)name, name__len, (void*)lowcase, lowcase__len, &obj);
  obj->conval = OfrontOPT_NewConst();
  obj->mode = 3;
  obj->typ = OfrontOPT_booltyp;
  obj->conval->intval = value;
}

static void OfrontOPT_EnterRealConst (CHAR *name, INTEGER name__len, CHAR *lowcase, INTEGER lowcase__len, REAL val, OfrontOPT_Object *obj)
{
  OfrontOPT_Insert2((void*)name, name__len, (void*)lowcase, lowcase__len, obj);
  (*obj)->conval = OfrontOPT_NewConst();
  (*obj)->mode = 3;
  (*obj)->typ = OfrontOPT_realtyp;
  (*obj)->conval->realval = val;
}

static void OfrontOPT_EnterTyp (CHAR *name, INTEGER name__len, CHAR *lowcase, INTEGER lowcase__len, BYTE form, SHORTINT size, OfrontOPT_Struct *res)
{
  OfrontOPT_Object obj = NIL;
  OfrontOPT_Struct typ = NIL;
  OfrontOPT_Insert2((void*)name, name__len, (void*)lowcase, lowcase__len, &obj);
  typ = OfrontOPT_NewStr(form, 1);
  obj->mode = 5;
  obj->typ = typ;
  obj->vis = 1;
  typ->strobj = obj;
  typ->size = size;
  typ->ref = form;
  typ->allocated = 1;
  typ->pbfp = form;
  typ->pvfp = form;
  typ->fpdone = 1;
  typ->idfp = form;
  typ->idfpdone = 1;
  *res = typ;
}

static void OfrontOPT_EnterTypeAlias (CHAR *name, INTEGER name__len, CHAR *lowcase, INTEGER lowcase__len, OfrontOPT_Object *res, OfrontOPT_Struct typ)
{
  OfrontOPT_Object obj = NIL;
  OfrontOPT_Insert2((void*)name, name__len, (void*)lowcase, lowcase__len, &obj);
  obj->mode = 5;
  obj->typ = typ;
  obj->vis = 1;
  *res = obj;
}

static void OfrontOPT_EnterProc (CHAR *name, INTEGER name__len, CHAR *lowcase, INTEGER lowcase__len, SHORTINT num)
{
  OfrontOPT_Object obj = NIL;
  OfrontOPT_Insert2((void*)name, name__len, (void*)lowcase, lowcase__len, &obj);
  obj->mode = 8;
  obj->typ = OfrontOPT_notyp;
  obj->adr = num;
}

static void OfrontOPT_EnterAttr (CHAR *name, INTEGER name__len, CHAR *lowcase, INTEGER lowcase__len, SHORTINT num)
{
  OfrontOPT_Object obj = NIL;
  OfrontOPT_Insert2((void*)name, name__len, (void*)lowcase, lowcase__len, &obj);
  obj->mode = 20;
  obj->adr = num;
}

static void OfrontOPT_EnterTProc (OfrontOPT_Struct ptr, OfrontOPT_Struct rec, CHAR *name, INTEGER name__len, CHAR *lowcase, INTEGER lowcase__len, SHORTINT typ)
{
  OfrontOPT_Object obj = NIL;
  OfrontOPT_Object par = NIL;
  OfrontOPT_InsertField((void*)name, name__len, (void*)lowcase, lowcase__len, rec, &obj);
  obj->mnolev = -128;
  obj->mode = 13;
  obj->conval = OfrontOPT_NewConst();
  obj->conval->setval = obj->conval->setval | 0x010000;
  obj->typ = OfrontOPT_notyp;
  obj->vis = 2;
  obj->conval->setval |= __SETOF(19);
  par = OfrontOPT_NewObj();
  par->name = OfrontOPT_NewName((CHAR*)"this", 5);
  par->mode = 1;
  par->adr = 8;
  par->typ = ptr;
  par->link = obj->link;
  obj->link = par;
}

static void OfrontOPT_InitScope (CHAR lang)
{
  OfrontOPT_topScope = NIL;
  OfrontOPT_OpenScope(0, NIL);
  OfrontOPM_errpos = 0;
  OfrontOPT_InitStruct(&OfrontOPT_undftyp, 0);
  OfrontOPT_InitStruct(&OfrontOPT_notyp, 12);
  OfrontOPT_InitStruct(&OfrontOPT_string8typ, 10);
  OfrontOPT_InitStruct(&OfrontOPT_niltyp, 11);
  OfrontOPT_niltyp->size = OfrontOPM_AdrSize;
  OfrontOPT_InitStruct(&OfrontOPT_string16typ, 18);
  OfrontOPT_undftyp->BaseTyp = OfrontOPT_undftyp;
  OfrontOPT_EnterTyp((CHAR*)"PTR", 4, (CHAR*)"ptr", 4, 13, OfrontOPM_AdrSize, &OfrontOPT_sysptrtyp);
  if (lang <= '3') {
    OfrontOPT_EnterTyp((CHAR*)"BYTE", 5, (CHAR*)"byte", 5, 14, 1, &OfrontOPT_ubytetyp);
  }
  OfrontOPT_EnterTyp((CHAR*)"CHAR8", 6, (CHAR*)"char8", 6, 3, 1, &OfrontOPT_char8typ);
  OfrontOPT_EnterTyp((CHAR*)"CHAR16", 7, (CHAR*)"char16", 7, 17, 2, &OfrontOPT_char16typ);
  OfrontOPT_EnterTyp((CHAR*)"REAL32", 7, (CHAR*)"real32", 7, 7, 4, &OfrontOPT_realtyp);
  OfrontOPT_EnterTyp((CHAR*)"REAL64", 7, (CHAR*)"real64", 7, 8, 8, &OfrontOPT_lrltyp);
  if (lang != '3') {
    OfrontOPT_EnterTyp((CHAR*)"INT8", 5, (CHAR*)"int8", 5, 1, 1, &OfrontOPT_bytetyp);
    OfrontOPT_EnterTyp((CHAR*)"INT16", 6, (CHAR*)"int16", 6, 4, 2, &OfrontOPT_sinttyp);
    OfrontOPT_EnterTyp((CHAR*)"INT32", 6, (CHAR*)"int32", 6, 5, 4, &OfrontOPT_inttyp);
    OfrontOPT_EnterTyp((CHAR*)"INT64", 6, (CHAR*)"int64", 6, 6, 8, &OfrontOPT_linttyp);
    switch (OfrontOPM_AdrSize) {
      case 2: 
        OfrontOPT_EnterTypeAlias((CHAR*)"ADRINT", 7, (CHAR*)"adrint", 7, &OfrontOPT_adrint, OfrontOPT_sinttyp);
        break;
      case 4: 
        OfrontOPT_EnterTypeAlias((CHAR*)"ADRINT", 7, (CHAR*)"adrint", 7, &OfrontOPT_adrint, OfrontOPT_inttyp);
        break;
      default: 
        OfrontOPT_EnterTypeAlias((CHAR*)"ADRINT", 7, (CHAR*)"adrint", 7, &OfrontOPT_adrint, OfrontOPT_linttyp);
        break;
    }
  }
  OfrontOPT_EnterProc((CHAR*)"ADR", 4, (CHAR*)"adr", 4, 27);
  OfrontOPT_EnterProc((CHAR*)"TYP", 4, (CHAR*)"typ", 4, 39);
  OfrontOPT_EnterProc((CHAR*)"LSH", 4, (CHAR*)"lsh", 4, 28);
  OfrontOPT_EnterProc((CHAR*)"ROT", 4, (CHAR*)"rot", 4, 29);
  OfrontOPT_EnterProc((CHAR*)"GET", 4, (CHAR*)"get", 4, 30);
  OfrontOPT_EnterProc((CHAR*)"PUT", 4, (CHAR*)"put", 4, 31);
  OfrontOPT_EnterProc((CHAR*)"BIT", 4, (CHAR*)"bit", 4, 34);
  OfrontOPT_EnterProc((CHAR*)"VAL", 4, (CHAR*)"val", 4, 35);
  OfrontOPT_EnterProc((CHAR*)"NEW", 4, (CHAR*)"new", 4, 36);
  OfrontOPT_EnterProc((CHAR*)"MOVE", 5, (CHAR*)"move", 5, 37);
  OfrontOPT_EnterProc((CHAR*)"THISREC", 8, (CHAR*)"thisrec", 8, 40);
  OfrontOPT_EnterProc((CHAR*)"THISARR", 8, (CHAR*)"thisarr", 8, 41);
  if (lang > '2') {
    OfrontOPT_EnterProc((CHAR*)"COPY", 5, (CHAR*)"copy", 5, 24);
  } else {
    OfrontOPT_EnterProc((CHAR*)"LCHR", 5, (CHAR*)"lchr", 5, 14);
  }
  if (lang == '7') {
    OfrontOPT_EnterProc((CHAR*)"SIZE", 5, (CHAR*)"size", 5, 15);
    OfrontOPT_EnterProc((CHAR*)"SHORT", 6, (CHAR*)"short", 6, 10);
    OfrontOPT_EnterProc((CHAR*)"LONG", 5, (CHAR*)"long", 5, 11);
  } else {
    OfrontOPT_EnterProc((CHAR*)"PACK", 5, (CHAR*)"pack", 5, 32);
    OfrontOPT_EnterProc((CHAR*)"UNPK", 5, (CHAR*)"unpk", 5, 33);
  }
  OfrontOPT_syslink = OfrontOPT_topScope->right;
  OfrontOPT_universe = OfrontOPT_topScope;
  OfrontOPT_topScope->right = NIL;
  if (lang == 'C') {
    OfrontOPT_EnterTyp((CHAR*)"ANYREC", 7, (CHAR*)"anyrec", 7, 16, 0, &OfrontOPT_anytyp);
  } else {
    OfrontOPT_EnterTyp((CHAR*)"ANYREC@", 8, (CHAR*)"anyrec@", 8, 16, 0, &OfrontOPT_anytyp);
  }
  OfrontOPT_anytyp->form = 16;
  OfrontOPT_anytyp->comp = 4;
  OfrontOPT_anytyp->n = 1;
  OfrontOPT_anytyp->BaseTyp = NIL;
  OfrontOPT_anytyp->extlev = -1;
  OfrontOPT_anytyp->attribute = 17;
  if (lang == 'C') {
    OfrontOPT_EnterTyp((CHAR*)"ANYPTR", 7, (CHAR*)"anyptr", 7, 15, OfrontOPM_AdrSize, &OfrontOPT_anyptrtyp);
  } else {
    OfrontOPT_EnterTyp((CHAR*)"ANYPTR@", 8, (CHAR*)"anyptr@", 8, 15, OfrontOPM_AdrSize, &OfrontOPT_anyptrtyp);
  }
  OfrontOPT_anyptrtyp->form = 13;
  OfrontOPT_anyptrtyp->BaseTyp = OfrontOPT_anytyp;
  OfrontOPT_EnterTProc(OfrontOPT_anyptrtyp, OfrontOPT_anytyp, (CHAR*)"FINALIZE", 9, (CHAR*)"finalize", 9, 0);
  OfrontOPT_EnterTyp((CHAR*)"BOOLEAN", 8, (CHAR*)"boolean", 8, 2, 1, &OfrontOPT_booltyp);
  OfrontOPT_EnterTyp((CHAR*)"SET", 4, (CHAR*)"set", 4, 9, OfrontOPM_SetSize, &OfrontOPT_settyp);
  if (lang == 'C') {
    OfrontOPT_EnterTypeAlias((CHAR*)"SHORTCHAR", 10, (CHAR*)"shortchar", 10, &OfrontOPT_char8, OfrontOPT_char8typ);
    OfrontOPT_EnterTypeAlias((CHAR*)"CHAR", 5, (CHAR*)"char", 5, &OfrontOPT_char16, OfrontOPT_char16typ);
    OfrontOPT_EnterTypeAlias((CHAR*)"BYTE", 5, (CHAR*)"byte", 5, &OfrontOPT_int8, OfrontOPT_bytetyp);
    OfrontOPT_EnterTypeAlias((CHAR*)"SHORTINT", 9, (CHAR*)"shortint", 9, &OfrontOPT_int16, OfrontOPT_sinttyp);
    OfrontOPT_EnterTypeAlias((CHAR*)"INTEGER", 8, (CHAR*)"integer", 8, &OfrontOPT_int32, OfrontOPT_inttyp);
    OfrontOPT_EnterTypeAlias((CHAR*)"LONGINT", 8, (CHAR*)"longint", 8, &OfrontOPT_int64, OfrontOPT_linttyp);
    OfrontOPT_EnterTypeAlias((CHAR*)"SHORTREAL", 10, (CHAR*)"shortreal", 10, &OfrontOPT_real32, OfrontOPT_realtyp);
    OfrontOPT_EnterTypeAlias((CHAR*)"REAL", 5, (CHAR*)"real", 5, &OfrontOPT_real64, OfrontOPT_lrltyp);
    OfrontOPT_EnterTyp((CHAR*)"UBYTE", 6, (CHAR*)"ubyte", 6, 14, 1, &OfrontOPT_ubytetyp);
  } else if (lang == '3') {
    OfrontOPT_EnterTyp((CHAR*)"CHAR", 5, (CHAR*)"char", 5, 3, 1, &OfrontOPT_char8typ);
    OfrontOPT_EnterTypeAlias((CHAR*)"LONGCHAR", 9, (CHAR*)"longchar", 9, &OfrontOPT_char16, OfrontOPT_char16typ);
    OfrontOPT_EnterTyp((CHAR*)"INT8", 5, (CHAR*)"int8", 5, 1, 1, &OfrontOPT_bytetyp);
    OfrontOPT_EnterTyp((CHAR*)"INT16", 6, (CHAR*)"int16", 6, 4, 2, &OfrontOPT_sinttyp);
    OfrontOPT_EnterTyp((CHAR*)"INT32", 6, (CHAR*)"int32", 6, 5, 4, &OfrontOPT_inttyp);
    OfrontOPT_EnterTyp((CHAR*)"INT64", 6, (CHAR*)"int64", 6, 6, 8, &OfrontOPT_linttyp);
    OfrontOPT_EnterTypeAlias((CHAR*)"REAL", 5, (CHAR*)"real", 5, &OfrontOPT_real32, OfrontOPT_realtyp);
    if ((INTEGER)OfrontOPM_AdrSize == 2) {
      OfrontOPT_EnterTypeAlias((CHAR*)"INTEGER", 8, (CHAR*)"integer", 8, &OfrontOPT_int16, OfrontOPT_sinttyp);
    } else {
      OfrontOPT_EnterTypeAlias((CHAR*)"INTEGER", 8, (CHAR*)"integer", 8, &OfrontOPT_int32, OfrontOPT_inttyp);
    }
    switch (OfrontOPM_AdrSize) {
      case 2: 
        OfrontOPT_EnterTypeAlias((CHAR*)"ADRINT", 7, (CHAR*)"adrint", 7, &OfrontOPT_adrint, OfrontOPT_sinttyp);
        break;
      case 4: 
        OfrontOPT_EnterTypeAlias((CHAR*)"ADRINT", 7, (CHAR*)"adrint", 7, &OfrontOPT_adrint, OfrontOPT_inttyp);
        break;
      default: 
        OfrontOPT_EnterTypeAlias((CHAR*)"ADRINT", 7, (CHAR*)"adrint", 7, &OfrontOPT_adrint, OfrontOPT_linttyp);
        break;
    }
  } else if (lang <= '2') {
    OfrontOPT_EnterTypeAlias((CHAR*)"CHAR", 5, (CHAR*)"char", 5, &OfrontOPT_char8, OfrontOPT_char8typ);
    OfrontOPT_EnterTypeAlias((CHAR*)"SHORTINT", 9, (CHAR*)"shortint", 9, &OfrontOPT_int8, OfrontOPT_bytetyp);
    OfrontOPT_EnterTypeAlias((CHAR*)"INTEGER", 8, (CHAR*)"integer", 8, &OfrontOPT_int16, OfrontOPT_sinttyp);
    OfrontOPT_EnterTypeAlias((CHAR*)"LONGINT", 8, (CHAR*)"longint", 8, &OfrontOPT_int32, OfrontOPT_inttyp);
    OfrontOPT_EnterTypeAlias((CHAR*)"HUGEINT", 8, (CHAR*)"hugeint", 8, &OfrontOPT_int64, OfrontOPT_linttyp);
    OfrontOPT_EnterTypeAlias((CHAR*)"REAL", 5, (CHAR*)"real", 5, &OfrontOPT_real32, OfrontOPT_realtyp);
    OfrontOPT_EnterTypeAlias((CHAR*)"LONGREAL", 9, (CHAR*)"longreal", 9, &OfrontOPT_real64, OfrontOPT_lrltyp);
  } else {
    OfrontOPT_EnterTyp((CHAR*)"BYTE", 5, (CHAR*)"byte", 5, 14, 1, &OfrontOPT_ubytetyp);
    if (__IN(18, OfrontOPM_opt)) {
      OfrontOPT_EnterTypeAlias((CHAR*)"CHAR", 5, (CHAR*)"char", 5, &OfrontOPT_char16, OfrontOPT_char16typ);
    } else {
      OfrontOPT_EnterTypeAlias((CHAR*)"CHAR", 5, (CHAR*)"char", 5, &OfrontOPT_char8, OfrontOPT_char8typ);
    }
    if ((INTEGER)OfrontOPM_AdrSize == 2) {
      OfrontOPT_EnterTypeAlias((CHAR*)"INTEGER", 8, (CHAR*)"integer", 8, &OfrontOPT_int16, OfrontOPT_sinttyp);
      OfrontOPT_EnterTypeAlias((CHAR*)"LONGINT", 8, (CHAR*)"longint", 8, &OfrontOPT_int16, OfrontOPT_sinttyp);
    } else {
      OfrontOPT_EnterTypeAlias((CHAR*)"INTEGER", 8, (CHAR*)"integer", 8, &OfrontOPT_int32, OfrontOPT_inttyp);
      OfrontOPT_EnterTypeAlias((CHAR*)"LONGINT", 8, (CHAR*)"longint", 8, &OfrontOPT_int32, OfrontOPT_inttyp);
    }
    OfrontOPT_EnterTypeAlias((CHAR*)"REAL", 5, (CHAR*)"real", 5, &OfrontOPT_real32, OfrontOPT_realtyp);
  }
  OfrontOPT_string8typ->BaseTyp = OfrontOPT_char8typ;
  OfrontOPT_string16typ->BaseTyp = OfrontOPT_char16typ;
  OfrontOPT_EnterBoolConst((CHAR*)"FALSE", 6, (CHAR*)"false", 6, 0);
  OfrontOPT_EnterBoolConst((CHAR*)"TRUE", 5, (CHAR*)"true", 5, 1);
  if (lang == 'C') {
    OfrontOPT_EnterRealConst((CHAR*)"INF", 4, (CHAR*)"inf", 4, OfrontOPM_InfReal, &OfrontOPT_infinity);
  } else {
    OfrontOPT_EnterRealConst((CHAR*)"INF@", 5, (CHAR*)"inf@", 5, OfrontOPM_InfReal, &OfrontOPT_infinity);
  }
  OfrontOPT_EnterProc((CHAR*)"HALT", 5, (CHAR*)"halt", 5, 0);
  OfrontOPT_EnterProc((CHAR*)"NEW", 4, (CHAR*)"new", 4, 1);
  OfrontOPT_EnterProc((CHAR*)"ABS", 4, (CHAR*)"abs", 4, 2);
  OfrontOPT_EnterProc((CHAR*)"CAP", 4, (CHAR*)"cap", 4, 3);
  OfrontOPT_EnterProc((CHAR*)"ORD", 4, (CHAR*)"ord", 4, 4);
  if (lang == '7') {
    OfrontOPT_EnterProc((CHAR*)"ASR", 4, (CHAR*)"asr", 4, 16);
    OfrontOPT_EnterProc((CHAR*)"LSL", 4, (CHAR*)"lsl", 4, 17);
    OfrontOPT_EnterProc((CHAR*)"ROR", 4, (CHAR*)"ror", 4, 18);
    OfrontOPT_EnterProc((CHAR*)"FLOOR", 6, (CHAR*)"floor", 6, 5);
    OfrontOPT_EnterProc((CHAR*)"FLT", 4, (CHAR*)"flt", 4, 13);
    OfrontOPT_EnterProc((CHAR*)"PACK", 5, (CHAR*)"pack", 5, 32);
    OfrontOPT_EnterProc((CHAR*)"UNPK", 5, (CHAR*)"unpk", 5, 33);
    if (__IN(18, OfrontOPM_opt)) {
      OfrontOPT_EnterProc((CHAR*)"CHR", 4, (CHAR*)"chr", 4, 14);
    } else {
      OfrontOPT_EnterProc((CHAR*)"CHR", 4, (CHAR*)"chr", 4, 9);
    }
  } else {
    OfrontOPT_EnterProc((CHAR*)"ASH", 4, (CHAR*)"ash", 4, 25);
    OfrontOPT_EnterProc((CHAR*)"ENTIER", 7, (CHAR*)"entier", 7, 5);
    OfrontOPT_EnterProc((CHAR*)"MIN", 4, (CHAR*)"min", 4, 7);
    OfrontOPT_EnterProc((CHAR*)"MAX", 4, (CHAR*)"max", 4, 8);
    OfrontOPT_EnterProc((CHAR*)"SHORT", 6, (CHAR*)"short", 6, 10);
    OfrontOPT_EnterProc((CHAR*)"LONG", 5, (CHAR*)"long", 5, 11);
    OfrontOPT_EnterProc((CHAR*)"SIZE", 5, (CHAR*)"size", 5, 15);
    if (lang == 'C') {
      OfrontOPT_EnterProc((CHAR*)"CHR", 4, (CHAR*)"chr", 4, 14);
    } else {
      OfrontOPT_EnterProc((CHAR*)"CHR", 4, (CHAR*)"chr", 4, 9);
      if (lang == '3') {
        OfrontOPT_EnterProc((CHAR*)"LCHR", 5, (CHAR*)"lchr", 5, 14);
      }
    }
  }
  OfrontOPT_EnterProc((CHAR*)"ODD", 4, (CHAR*)"odd", 4, 6);
  OfrontOPT_EnterProc((CHAR*)"INC", 4, (CHAR*)"inc", 4, 19);
  OfrontOPT_EnterProc((CHAR*)"DEC", 4, (CHAR*)"dec", 4, 20);
  OfrontOPT_EnterProc((CHAR*)"INCL", 5, (CHAR*)"incl", 5, 21);
  OfrontOPT_EnterProc((CHAR*)"EXCL", 5, (CHAR*)"excl", 5, 22);
  OfrontOPT_EnterProc((CHAR*)"LEN", 4, (CHAR*)"len", 4, 23);
  if (lang <= '2') {
    OfrontOPT_EnterProc((CHAR*)"COPY", 5, (CHAR*)"copy", 5, 24);
  }
  OfrontOPT_EnterProc((CHAR*)"ASSERT", 7, (CHAR*)"assert", 7, 38);
  if (lang == 'C' || lang == '3') {
    OfrontOPT_EnterProc((CHAR*)"BITS", 5, (CHAR*)"bits", 5, 12);
    OfrontOPT_EnterProc((CHAR*)"USHORT", 7, (CHAR*)"ushort", 7, 26);
  }
  OfrontOPT_EnterAttr((CHAR*)"ABSTRACT", 9, (CHAR*)"abstract", 9, 17);
  OfrontOPT_EnterAttr((CHAR*)"LIMITED", 8, (CHAR*)"limited", 8, 18);
  OfrontOPT_EnterAttr((CHAR*)"EMPTY", 6, (CHAR*)"empty", 6, 19);
  OfrontOPT_EnterAttr((CHAR*)"EXTENSIBLE", 11, (CHAR*)"extensible", 11, 20);
  OfrontOPT_impCtxt.ref[0] = OfrontOPT_undftyp;
  OfrontOPT_impCtxt.ref[1] = OfrontOPT_bytetyp;
  OfrontOPT_impCtxt.ref[2] = OfrontOPT_booltyp;
  OfrontOPT_impCtxt.ref[3] = OfrontOPT_char8typ;
  OfrontOPT_impCtxt.ref[4] = OfrontOPT_sinttyp;
  OfrontOPT_impCtxt.ref[5] = OfrontOPT_inttyp;
  OfrontOPT_impCtxt.ref[6] = OfrontOPT_linttyp;
  OfrontOPT_impCtxt.ref[7] = OfrontOPT_realtyp;
  OfrontOPT_impCtxt.ref[8] = OfrontOPT_lrltyp;
  OfrontOPT_impCtxt.ref[9] = OfrontOPT_settyp;
  OfrontOPT_impCtxt.ref[10] = OfrontOPT_string8typ;
  OfrontOPT_impCtxt.ref[11] = OfrontOPT_niltyp;
  OfrontOPT_impCtxt.ref[12] = OfrontOPT_notyp;
  OfrontOPT_impCtxt.ref[13] = OfrontOPT_sysptrtyp;
  OfrontOPT_impCtxt.ref[15] = OfrontOPT_anyptrtyp;
  OfrontOPT_impCtxt.ref[16] = OfrontOPT_anytyp;
  OfrontOPT_impCtxt.ref[17] = OfrontOPT_char16typ;
  OfrontOPT_impCtxt.ref[18] = OfrontOPT_string16typ;
  OfrontOPT_impCtxt.ref[14] = OfrontOPT_ubytetyp;
}

void OfrontOPT_Init (CHAR *name, INTEGER name__len, CHAR lang, SET opt)
{
  OfrontOPT_InitScope(lang);
  OfrontOPT_topScope = OfrontOPT_universe;
  OfrontOPT_OpenScope(0, NIL);
  OfrontOPT_SYSimported = 0;
  __STRCOPYCC(name, OfrontOPT_SelfName, __MIN(48, name__len), (CHAR*)"OfrontOPT", 390419);
  OfrontOPT_topScope->name = OfrontOPT_NewName((void*)name, name__len);
  OfrontOPT_GlbMod[0] = OfrontOPT_topScope;
  OfrontOPT_nofGmod = 1;
  OfrontOPT_newsf = __IN(4, opt);
  OfrontOPT_findpc = __IN(8, opt);
  OfrontOPT_extsf = OfrontOPT_newsf || __IN(9, opt);
  OfrontOPT_sfpresent = 1;
  OfrontOPT_infinity->conval->intval = -1;
  OfrontOPT_depth = 0;
}

/*----------------------------------------------------------------------------*/
static void EnumPtrs(void (*P)(void*))
{
  P(OfrontOPT_topScope);
  P(OfrontOPT_undftyp);
  P(OfrontOPT_bytetyp);
  P(OfrontOPT_booltyp);
  P(OfrontOPT_char8typ);
  P(OfrontOPT_sinttyp);
  P(OfrontOPT_inttyp);
  P(OfrontOPT_linttyp);
  P(OfrontOPT_realtyp);
  P(OfrontOPT_lrltyp);
  P(OfrontOPT_settyp);
  P(OfrontOPT_string8typ);
  P(OfrontOPT_niltyp);
  P(OfrontOPT_notyp);
  P(OfrontOPT_sysptrtyp);
  P(OfrontOPT_ubytetyp);
  P(OfrontOPT_anytyp);
  P(OfrontOPT_anyptrtyp);
  P(OfrontOPT_char16typ);
  P(OfrontOPT_string16typ);
  P(OfrontOPT_char8);
  P(OfrontOPT_int8);
  P(OfrontOPT_int16);
  P(OfrontOPT_int32);
  P(OfrontOPT_int64);
  P(OfrontOPT_adrint);
  P(OfrontOPT_byte);
  P(OfrontOPT_ubyte);
  P(OfrontOPT_real32);
  P(OfrontOPT_real64);
  P(OfrontOPT_char16);
  __ENUMP(OfrontOPT_GlbMod, 64, P);
  P(OfrontOPT_null);
  P(OfrontOPT_universe);
  P(OfrontOPT_syslink);
  P(OfrontOPT_infinity);
  __ENUMR(&OfrontOPT_impCtxt, OfrontOPT_ImpCtxt__typ, 35160, 1, P);
}

__TDESC(OfrontOPT_ConstArr__rec__desc, 2, 4) = {__TDFLDS("ConstArr__rec", 32), {0, 8, 16, 24, -40}};
__TDESC(OfrontOPT_ConstDesc__desc, 2, 2) = {__TDFLDS("ConstDesc", 40), {0, 32, -24}};
__TDESC(OfrontOPT_ObjDesc__desc, 1, 10) = {__TDFLDS("ObjDesc", 112), {0, 8, 16, 24, 32, 56, 64, 72, 80, 88, -88}};
__TDESC(OfrontOPT_StrDesc__desc, 2, 3) = {__TDFLDS("StrDesc", 72), {48, 56, 64, -32}};
__TDESC(OfrontOPT_NodeDesc__desc, 2, 6) = {__TDFLDS("NodeDesc", 56), {0, 8, 16, 32, 40, 48, -56}};
__TDESC(OfrontOPT_ImpCtxt__desc, 2, 3508) = {__TDFLDS("ImpCtxt", 35160), {16, 24, 32, 40, 48, 56, 64, 72, 80, 88, 96, 104, 112, 120, 128, 136, 
  144, 152, 160, 168, 176, 184, 192, 200, 208, 216, 224, 232, 240, 248, 256, 264, 
  272, 280, 288, 296, 304, 312, 320, 328, 336, 344, 352, 360, 368, 376, 384, 392, 
  400, 408, 416, 424, 432, 440, 448, 456, 464, 472, 480, 488, 496, 504, 512, 520, 
  528, 536, 544, 552, 560, 568, 576, 584, 592, 600, 608, 616, 624, 632, 640, 648, 
  656, 664, 672, 680, 688, 696, 704, 712, 720, 728, 736, 744, 752, 760, 768, 776, 
  784, 792, 800, 808, 816, 824, 832, 840, 848, 856, 864, 872, 880, 888, 896, 904, 
  912, 920, 928, 936, 944, 952, 960, 968, 976, 984, 992, 1000, 1008, 1016, 1024, 1032, 
  1040, 1048, 1056, 1064, 1072, 1080, 1088, 1096, 1104, 1112, 1120, 1128, 1136, 1144, 1152, 1160, 
  1168, 1176, 1184, 1192, 1200, 1208, 1216, 1224, 1232, 1240, 1248, 1256, 1264, 1272, 1280, 1288, 
  1296, 1304, 1312, 1320, 1328, 1336, 1344, 1352, 1360, 1368, 1376, 1384, 1392, 1400, 1408, 1416, 
  1424, 1432, 1440, 1448, 1456, 1464, 1472, 1480, 1488, 1496, 1504, 1512, 1520, 1528, 1536, 1544, 
  1552, 1560, 1568, 1576, 1584, 1592, 1600, 1608, 1616, 1624, 1632, 1640, 1648, 1656, 1664, 1672, 
  1680, 1688, 1696, 1704, 1712, 1720, 1728, 1736, 1744, 1752, 1760, 1768, 1776, 1784, 1792, 1800, 
  1808, 1816, 1824, 1832, 1840, 1848, 1856, 1864, 1872, 1880, 1888, 1896, 1904, 1912, 1920, 1928, 
  1936, 1944, 1952, 1960, 1968, 1976, 1984, 1992, 2000, 2008, 2016, 2024, 2032, 2040, 2048, 2056, 
  2064, 2072, 2080, 2088, 2096, 2104, 2112, 2120, 2128, 2136, 2144, 2152, 2160, 2168, 2176, 2184, 
  2192, 2200, 2208, 2216, 2224, 2232, 2240, 2248, 2256, 2264, 2272, 2280, 2288, 2296, 2304, 2312, 
  2320, 2328, 2336, 2344, 2352, 2360, 2368, 2376, 2384, 2392, 2400, 2408, 2416, 2424, 2432, 2440, 
  2448, 2456, 2464, 2472, 2480, 2488, 2496, 2504, 2512, 2520, 2528, 2536, 2544, 2552, 2560, 2568, 
  2576, 2584, 2592, 2600, 2608, 2616, 2624, 2632, 2640, 2648, 2656, 2664, 2672, 2680, 2688, 2696, 
  2704, 2712, 2720, 2728, 2736, 2744, 2752, 2760, 2768, 2776, 2784, 2792, 2800, 2808, 2816, 2824, 
  2832, 2840, 2848, 2856, 2864, 2872, 2880, 2888, 2896, 2904, 2912, 2920, 2928, 2936, 2944, 2952, 
  2960, 2968, 2976, 2984, 2992, 3000, 3008, 3016, 3024, 3032, 3040, 3048, 3056, 3064, 3072, 3080, 
  3088, 3096, 3104, 3112, 3120, 3128, 3136, 3144, 3152, 3160, 3168, 3176, 3184, 3192, 3200, 3208, 
  3216, 3224, 3232, 3240, 3248, 3256, 3264, 3272, 3280, 3288, 3296, 3304, 3312, 3320, 3328, 3336, 
  3344, 3352, 3360, 3368, 3376, 3384, 3392, 3400, 3408, 3416, 3424, 3432, 3440, 3448, 3456, 3464, 
  3472, 3480, 3488, 3496, 3504, 3512, 3520, 3528, 3536, 3544, 3552, 3560, 3568, 3576, 3584, 3592, 
  3600, 3608, 3616, 3624, 3632, 3640, 3648, 3656, 3664, 3672, 3680, 3688, 3696, 3704, 3712, 3720, 
  3728, 3736, 3744, 3752, 3760, 3768, 3776, 3784, 3792, 3800, 3808, 3816, 3824, 3832, 3840, 3848, 
  3856, 3864, 3872, 3880, 3888, 3896, 3904, 3912, 3920, 3928, 3936, 3944, 3952, 3960, 3968, 3976, 
  3984, 3992, 4000, 4008, 4016, 4024, 4032, 4040, 4048, 4056, 4064, 4072, 4080, 4088, 4096, 4104, 
  4112, 4120, 4128, 4136, 4144, 4152, 4160, 4168, 4176, 4184, 4192, 4200, 4208, 4216, 4224, 4232, 
  4240, 4248, 4256, 4264, 4272, 4280, 4288, 4296, 4304, 4312, 4320, 4328, 4336, 4344, 4352, 4360, 
  4368, 4376, 4384, 4392, 4400, 4408, 4416, 4424, 4432, 4440, 4448, 4456, 4464, 4472, 4480, 4488, 
  4496, 4504, 4512, 4520, 4528, 4536, 4544, 4552, 4560, 4568, 4576, 4584, 4592, 4600, 4608, 4616, 
  4624, 4632, 4640, 4648, 4656, 4664, 4672, 4680, 4688, 4696, 4704, 4712, 4720, 4728, 4736, 4744, 
  4752, 4760, 4768, 4776, 4784, 4792, 4800, 4808, 4816, 4824, 4832, 4840, 4848, 4856, 4864, 4872, 
  4880, 4888, 4896, 4904, 4912, 4920, 4928, 4936, 4944, 4952, 4960, 4968, 4976, 4984, 4992, 5000, 
  5008, 5016, 5024, 5032, 5040, 5048, 5056, 5064, 5072, 5080, 5088, 5096, 5104, 5112, 5120, 5128, 
  5136, 5144, 5152, 5160, 5168, 5176, 5184, 5192, 5200, 5208, 5216, 5224, 5232, 5240, 5248, 5256, 
  5264, 5272, 5280, 5288, 5296, 5304, 5312, 5320, 5328, 5336, 5344, 5352, 5360, 5368, 5376, 5384, 
  5392, 5400, 5408, 5416, 5424, 5432, 5440, 5448, 5456, 5464, 5472, 5480, 5488, 5496, 5504, 5512, 
  5520, 5528, 5536, 5544, 5552, 5560, 5568, 5576, 5584, 5592, 5600, 5608, 5616, 5624, 5632, 5640, 
  5648, 5656, 5664, 5672, 5680, 5688, 5696, 5704, 5712, 5720, 5728, 5736, 5744, 5752, 5760, 5768, 
  5776, 5784, 5792, 5800, 5808, 5816, 5824, 5832, 5840, 5848, 5856, 5864, 5872, 5880, 5888, 5896, 
  5904, 5912, 5920, 5928, 5936, 5944, 5952, 5960, 5968, 5976, 5984, 5992, 6000, 6008, 6016, 6024, 
  6032, 6040, 6048, 6056, 6064, 6072, 6080, 6088, 6096, 6104, 6112, 6120, 6128, 6136, 6144, 6152, 
  6160, 6168, 6176, 6184, 6192, 6200, 6208, 6216, 6224, 6232, 6240, 6248, 6256, 6264, 6272, 6280, 
  6288, 6296, 6304, 6312, 6320, 6328, 6336, 6344, 6352, 6360, 6368, 6376, 6384, 6392, 6400, 6408, 
  6416, 6424, 6432, 6440, 6448, 6456, 6464, 6472, 6480, 6488, 6496, 6504, 6512, 6520, 6528, 6536, 
  6544, 6552, 6560, 6568, 6576, 6584, 6592, 6600, 6608, 6616, 6624, 6632, 6640, 6648, 6656, 6664, 
  6672, 6680, 6688, 6696, 6704, 6712, 6720, 6728, 6736, 6744, 6752, 6760, 6768, 6776, 6784, 6792, 
  6800, 6808, 6816, 6824, 6832, 6840, 6848, 6856, 6864, 6872, 6880, 6888, 6896, 6904, 6912, 6920, 
  6928, 6936, 6944, 6952, 6960, 6968, 6976, 6984, 6992, 7000, 7008, 7016, 7024, 7032, 7040, 7048, 
  7056, 7064, 7072, 7080, 7088, 7096, 7104, 7112, 7120, 7128, 7136, 7144, 7152, 7160, 7168, 7176, 
  7184, 7192, 7200, 7208, 7216, 7224, 7232, 7240, 7248, 7256, 7264, 7272, 7280, 7288, 7296, 7304, 
  7312, 7320, 7328, 7336, 7344, 7352, 7360, 7368, 7376, 7384, 7392, 7400, 7408, 7416, 7424, 7432, 
  7440, 7448, 7456, 7464, 7472, 7480, 7488, 7496, 7504, 7512, 7520, 7528, 7536, 7544, 7552, 7560, 
  7568, 7576, 7584, 7592, 7600, 7608, 7616, 7624, 7632, 7640, 7648, 7656, 7664, 7672, 7680, 7688, 
  7696, 7704, 7712, 7720, 7728, 7736, 7744, 7752, 7760, 7768, 7776, 7784, 7792, 7800, 7808, 7816, 
  7824, 7832, 7840, 7848, 7856, 7864, 7872, 7880, 7888, 7896, 7904, 7912, 7920, 7928, 7936, 7944, 
  7952, 7960, 7968, 7976, 7984, 7992, 8000, 8008, 8016, 8024, 8032, 8040, 8048, 8056, 8064, 8072, 
  8080, 8088, 8096, 8104, 8112, 8120, 8128, 8136, 8144, 8152, 8160, 8168, 8176, 8184, 8192, 8200, 
  8208, 8216, 8224, 8232, 8240, 8248, 8256, 8264, 8272, 8280, 8288, 8296, 8304, 8312, 8320, 8328, 
  8336, 8344, 8352, 8360, 8368, 8376, 8384, 8392, 8400, 8408, 8416, 8424, 8432, 8440, 8448, 8456, 
  8464, 8472, 8480, 8488, 8496, 8504, 8512, 8520, 8528, 8536, 8544, 8552, 8560, 8568, 8576, 8584, 
  8592, 8600, 8608, 8616, 8624, 8632, 8640, 8648, 8656, 8664, 8672, 8680, 8688, 8696, 8704, 8712, 
  8720, 8728, 8736, 8744, 8752, 8760, 8768, 8776, 8784, 8792, 8800, 8808, 8816, 8824, 8832, 8840, 
  8848, 8856, 8864, 8872, 8880, 8888, 8896, 8904, 8912, 8920, 8928, 8936, 8944, 8952, 8960, 8968, 
  8976, 8984, 8992, 9000, 9008, 9016, 9024, 9032, 9040, 9048, 9056, 9064, 9072, 9080, 9088, 9096, 
  9104, 9112, 9120, 9128, 9136, 9144, 9152, 9160, 9168, 9176, 9184, 9192, 9200, 9208, 9216, 9224, 
  9232, 9240, 9248, 9256, 9264, 9272, 9280, 9288, 9296, 9304, 9312, 9320, 9328, 9336, 9344, 9352, 
  9360, 9368, 9376, 9384, 9392, 9400, 9408, 9416, 9424, 9432, 9440, 9448, 9456, 9464, 9472, 9480, 
  9488, 9496, 9504, 9512, 9520, 9528, 9536, 9544, 9552, 9560, 9568, 9576, 9584, 9592, 9600, 9608, 
  9616, 9624, 9632, 9640, 9648, 9656, 9664, 9672, 9680, 9688, 9696, 9704, 9712, 9720, 9728, 9736, 
  9744, 9752, 9760, 9768, 9776, 9784, 9792, 9800, 9808, 9816, 9824, 9832, 9840, 9848, 9856, 9864, 
  9872, 9880, 9888, 9896, 9904, 9912, 9920, 9928, 9936, 9944, 9952, 9960, 9968, 9976, 9984, 9992, 
  10000, 10008, 10016, 10024, 10032, 10040, 10048, 10056, 10064, 10072, 10080, 10088, 10096, 10104, 10112, 10120, 
  10128, 10136, 10144, 10152, 10160, 10168, 10176, 10184, 10192, 10200, 10208, 10216, 10224, 10232, 10240, 10248, 
  10256, 10264, 10272, 10280, 10288, 10296, 10304, 10312, 10320, 10328, 10336, 10344, 10352, 10360, 10368, 10376, 
  10384, 10392, 10400, 10408, 10416, 10424, 10432, 10440, 10448, 10456, 10464, 10472, 10480, 10488, 10496, 10504, 
  10512, 10520, 10528, 10536, 10544, 10552, 10560, 10568, 10576, 10584, 10592, 10600, 10608, 10616, 10624, 10632, 
  10640, 10648, 10656, 10664, 10672, 10680, 10688, 10696, 10704, 10712, 10720, 10728, 10736, 10744, 10752, 10760, 
  10768, 10776, 10784, 10792, 10800, 10808, 10816, 10824, 10832, 10840, 10848, 10856, 10864, 10872, 10880, 10888, 
  10896, 10904, 10912, 10920, 10928, 10936, 10944, 10952, 10960, 10968, 10976, 10984, 10992, 11000, 11008, 11016, 
  11024, 11032, 11040, 11048, 11056, 11064, 11072, 11080, 11088, 11096, 11104, 11112, 11120, 11128, 11136, 11144, 
  11152, 11160, 11168, 11176, 11184, 11192, 11200, 11208, 11216, 11224, 11232, 11240, 11248, 11256, 11264, 11272, 
  11280, 11288, 11296, 11304, 11312, 11320, 11328, 11336, 11344, 11352, 11360, 11368, 11376, 11384, 11392, 11400, 
  11408, 11416, 11424, 11432, 11440, 11448, 11456, 11464, 11472, 11480, 11488, 11496, 11504, 11512, 11520, 11528, 
  11536, 11544, 11552, 11560, 11568, 11576, 11584, 11592, 11600, 11608, 11616, 11624, 11632, 11640, 11648, 11656, 
  11664, 11672, 11680, 11688, 11696, 11704, 11712, 11720, 11728, 11736, 11744, 11752, 11760, 11768, 11776, 11784, 
  11792, 11800, 11808, 11816, 11824, 11832, 11840, 11848, 11856, 11864, 11872, 11880, 11888, 11896, 11904, 11912, 
  11920, 11928, 11936, 11944, 11952, 11960, 11968, 11976, 11984, 11992, 12000, 12008, 12016, 12024, 12032, 12040, 
  12048, 12056, 12064, 12072, 12080, 12088, 12096, 12104, 12112, 12120, 12128, 12136, 12144, 12152, 12160, 12168, 
  12176, 12184, 12192, 12200, 12208, 12216, 12224, 12232, 12240, 12248, 12256, 12264, 12272, 12280, 12288, 12296, 
  12304, 12312, 12320, 12328, 12336, 12344, 12352, 12360, 12368, 12376, 12384, 12392, 12400, 12408, 12416, 12424, 
  12432, 12440, 12448, 12456, 12464, 12472, 12480, 12488, 12496, 12504, 12512, 12520, 12528, 12536, 12544, 12552, 
  12560, 12568, 12576, 12584, 12592, 12600, 12608, 12616, 12624, 12632, 12640, 12648, 12656, 12664, 12672, 12680, 
  12688, 12696, 12704, 12712, 12720, 12728, 12736, 12744, 12752, 12760, 12768, 12776, 12784, 12792, 12800, 12808, 
  12816, 12824, 12832, 12840, 12848, 12856, 12864, 12872, 12880, 12888, 12896, 12904, 12912, 12920, 12928, 12936, 
  12944, 12952, 12960, 12968, 12976, 12984, 12992, 13000, 13008, 13016, 13024, 13032, 13040, 13048, 13056, 13064, 
  13072, 13080, 13088, 13096, 13104, 13112, 13120, 13128, 13136, 13144, 13152, 13160, 13168, 13176, 13184, 13192, 
  13200, 13208, 13216, 13224, 13232, 13240, 13248, 13256, 13264, 13272, 13280, 13288, 13296, 13304, 13312, 13320, 
  13328, 13336, 13344, 13352, 13360, 13368, 13376, 13384, 13392, 13400, 13408, 13416, 13424, 13432, 13440, 13448, 
  13456, 13464, 13472, 13480, 13488, 13496, 13504, 13512, 13520, 13528, 13536, 13544, 13552, 13560, 13568, 13576, 
  13584, 13592, 13600, 13608, 13616, 13624, 13632, 13640, 13648, 13656, 13664, 13672, 13680, 13688, 13696, 13704, 
  13712, 13720, 13728, 13736, 13744, 13752, 13760, 13768, 13776, 13784, 13792, 13800, 13808, 13816, 13824, 13832, 
  13840, 13848, 13856, 13864, 13872, 13880, 13888, 13896, 13904, 13912, 13920, 13928, 13936, 13944, 13952, 13960, 
  13968, 13976, 13984, 13992, 14000, 14008, 14016, 14024, 14032, 14040, 14048, 14056, 14064, 14072, 14080, 14088, 
  14096, 14104, 14112, 14120, 14128, 14136, 14144, 14152, 14160, 14168, 14176, 14184, 14192, 14200, 14208, 14216, 
  14224, 14232, 14240, 14248, 14256, 14264, 14272, 14280, 14288, 14296, 14304, 14312, 14320, 14328, 14336, 14344, 
  14352, 14360, 14368, 14376, 14384, 14392, 14400, 14408, 14416, 14424, 14432, 14440, 14448, 14456, 14464, 14472, 
  14480, 14488, 14496, 14504, 14512, 14520, 14528, 14536, 14544, 14552, 14560, 14568, 14576, 14584, 14592, 14600, 
  14608, 14616, 14624, 14632, 14640, 14648, 14656, 14664, 14672, 14680, 14688, 14696, 14704, 14712, 14720, 14728, 
  14736, 14744, 14752, 14760, 14768, 14776, 14784, 14792, 14800, 14808, 14816, 14824, 14832, 14840, 14848, 14856, 
  14864, 14872, 14880, 14888, 14896, 14904, 14912, 14920, 14928, 14936, 14944, 14952, 14960, 14968, 14976, 14984, 
  14992, 15000, 15008, 15016, 15024, 15032, 15040, 15048, 15056, 15064, 15072, 15080, 15088, 15096, 15104, 15112, 
  15120, 15128, 15136, 15144, 15152, 15160, 15168, 15176, 15184, 15192, 15200, 15208, 15216, 15224, 15232, 15240, 
  15248, 15256, 15264, 15272, 15280, 15288, 15296, 15304, 15312, 15320, 15328, 15336, 15344, 15352, 15360, 15368, 
  15376, 15384, 15392, 15400, 15408, 15416, 15424, 15432, 15440, 15448, 15456, 15464, 15472, 15480, 15488, 15496, 
  15504, 15512, 15520, 15528, 15536, 15544, 15552, 15560, 15568, 15576, 15584, 15592, 15600, 15608, 15616, 15624, 
  15632, 15640, 15648, 15656, 15664, 15672, 15680, 15688, 15696, 15704, 15712, 15720, 15728, 15736, 15744, 15752, 
  15760, 15768, 15776, 15784, 15792, 15800, 15808, 15816, 15824, 15832, 15840, 15848, 15856, 15864, 15872, 15880, 
  15888, 15896, 15904, 15912, 15920, 15928, 15936, 15944, 15952, 15960, 15968, 15976, 15984, 15992, 16000, 16008, 
  16016, 16024, 16032, 16040, 16048, 16056, 16064, 16072, 16080, 16088, 16096, 16104, 16112, 16120, 16128, 16136, 
  16144, 16152, 16160, 16168, 16176, 16184, 16192, 16200, 16208, 16216, 16224, 16232, 16240, 16248, 16256, 16264, 
  16272, 16280, 16288, 16296, 16304, 16312, 16320, 16328, 16336, 16344, 16352, 16360, 16368, 16376, 16384, 16392, 
  16400, 16408, 16416, 16424, 16432, 16440, 16448, 16456, 16464, 16472, 16480, 16488, 16496, 16504, 16512, 16520, 
  16528, 16536, 16544, 16552, 16560, 16568, 16576, 16584, 16592, 16600, 16608, 16616, 16624, 16632, 16640, 16648, 
  16656, 16664, 16672, 16680, 16688, 16696, 16704, 16712, 16720, 16728, 16736, 16744, 16752, 16760, 16768, 16776, 
  16784, 16792, 16800, 16808, 16816, 16824, 16832, 16840, 16848, 16856, 16864, 16872, 16880, 16888, 16896, 16904, 
  16912, 16920, 16928, 16936, 16944, 16952, 16960, 16968, 16976, 16984, 16992, 17000, 17008, 17016, 17024, 17032, 
  17040, 17048, 17056, 17064, 17072, 17080, 17088, 17096, 17104, 17112, 17120, 17128, 17136, 17144, 17152, 17160, 
  17168, 17176, 17184, 17192, 17200, 17208, 17216, 17224, 17232, 17240, 17248, 17256, 17264, 17272, 17280, 17288, 
  17296, 17304, 17312, 17320, 17328, 17336, 17344, 17352, 17360, 17368, 17376, 17384, 17392, 17400, 17408, 17416, 
  17424, 17432, 17440, 17448, 17456, 17464, 17472, 17480, 17488, 17496, 17504, 17512, 17520, 17528, 17536, 17544, 
  17552, 17560, 17568, 17576, 17584, 17592, 17600, 17608, 17616, 17624, 17632, 17640, 17648, 17656, 17664, 17672, 
  17680, 17688, 17696, 17704, 17712, 17720, 17728, 17736, 17744, 17752, 17760, 17768, 17776, 17784, 17792, 17800, 
  17808, 17816, 17824, 17832, 17840, 17848, 17856, 17864, 17872, 17880, 17888, 17896, 17904, 17912, 17920, 17928, 
  17936, 17944, 17952, 17960, 17968, 17976, 17984, 17992, 18000, 18008, 18016, 18024, 18032, 18040, 18048, 18056, 
  18064, 18072, 18080, 18088, 18096, 18104, 18112, 18120, 18128, 18136, 18144, 18152, 18160, 18168, 18176, 18184, 
  18192, 18200, 18208, 18216, 18224, 18232, 18240, 18248, 18256, 18264, 18272, 18280, 18288, 18296, 18304, 18312, 
  18320, 18328, 18336, 18344, 18352, 18360, 18368, 18376, 18384, 18392, 18400, 18408, 18416, 18424, 18432, 18440, 
  18448, 18456, 18464, 18472, 18480, 18488, 18496, 18504, 18512, 18520, 18528, 18536, 18544, 18552, 18560, 18568, 
  18576, 18584, 18592, 18600, 18608, 18616, 18624, 18632, 18640, 18648, 18656, 18664, 18672, 18680, 18688, 18696, 
  18704, 18712, 18720, 18728, 18736, 18744, 18752, 18760, 18768, 18776, 18784, 18792, 18800, 18808, 18816, 18824, 
  18832, 18840, 18848, 18856, 18864, 18872, 18880, 18888, 18896, 18904, 18912, 18920, 18928, 18936, 18944, 18952, 
  18960, 18968, 18976, 18984, 18992, 19000, 19008, 19016, 19024, 19032, 19040, 19048, 19056, 19064, 19072, 19080, 
  19088, 19096, 19104, 19112, 19120, 19128, 19136, 19144, 19152, 19160, 19168, 19176, 19184, 19192, 19200, 19208, 
  19216, 19224, 19232, 19240, 19248, 19256, 19264, 19272, 19280, 19288, 19296, 19304, 19312, 19320, 19328, 19336, 
  19344, 19352, 19360, 19368, 19376, 19384, 19392, 19400, 19408, 19416, 19424, 19432, 19440, 19448, 19456, 19464, 
  19472, 19480, 19488, 19496, 19504, 19512, 19520, 19528, 19536, 19544, 19552, 19560, 19568, 19576, 19584, 19592, 
  19600, 19608, 19616, 19624, 19632, 19640, 19648, 19656, 19664, 19672, 19680, 19688, 19696, 19704, 19712, 19720, 
  19728, 19736, 19744, 19752, 19760, 19768, 19776, 19784, 19792, 19800, 19808, 19816, 19824, 19832, 19840, 19848, 
  19856, 19864, 19872, 19880, 19888, 19896, 19904, 19912, 19920, 19928, 19936, 19944, 19952, 19960, 19968, 19976, 
  19984, 19992, 20000, 20008, 20016, 20024, 20032, 20040, 20048, 20056, 20064, 20072, 20080, 20088, 20096, 20104, 
  20112, 20120, 20128, 20136, 20144, 20152, 20160, 20168, 20176, 20184, 20192, 20200, 20208, 20216, 20224, 20232, 
  20240, 20248, 20256, 20264, 20272, 20280, 20288, 20296, 20304, 20312, 20320, 20328, 20336, 20344, 20352, 20360, 
  20368, 20376, 20384, 20392, 20400, 20408, 20416, 20424, 20432, 20440, 20448, 20456, 20464, 20472, 20480, 20488, 
  20496, 20504, 20512, 20520, 20528, 20536, 20544, 20552, 20560, 20568, 20576, 20584, 20592, 20600, 20608, 20616, 
  20624, 20632, 20640, 20648, 20656, 20664, 20672, 20680, 20688, 20696, 20704, 20712, 20720, 20728, 20736, 20744, 
  20752, 20760, 20768, 20776, 20784, 20792, 20800, 20808, 20816, 20824, 20832, 20840, 20848, 20856, 20864, 20872, 
  20880, 20888, 20896, 20904, 20912, 20920, 20928, 20936, 20944, 20952, 20960, 20968, 20976, 20984, 20992, 21000, 
  21008, 21016, 21024, 21032, 21040, 21048, 21056, 21064, 21072, 21080, 21088, 21096, 21104, 21112, 21120, 21128, 
  21136, 21144, 21152, 21160, 21168, 21176, 21184, 21192, 21200, 21208, 21216, 21224, 21232, 21240, 21248, 21256, 
  21264, 21272, 21280, 21288, 21296, 21304, 21312, 21320, 21328, 21336, 21344, 21352, 21360, 21368, 21376, 21384, 
  21392, 21400, 21408, 21416, 21424, 21432, 21440, 21448, 21456, 21464, 21472, 21480, 21488, 21496, 21504, 21512, 
  21520, 21528, 21536, 21544, 21552, 21560, 21568, 21576, 21584, 21592, 21600, 21608, 21616, 21624, 21632, 21640, 
  21648, 21656, 21664, 21672, 21680, 21688, 21696, 21704, 21712, 21720, 21728, 21736, 21744, 21752, 21760, 21768, 
  21776, 21784, 21792, 21800, 21808, 21816, 21824, 21832, 21840, 21848, 21856, 21864, 21872, 21880, 21888, 21896, 
  21904, 21912, 21920, 21928, 21936, 21944, 21952, 21960, 21968, 21976, 21984, 21992, 22000, 22008, 22016, 22024, 
  22032, 22040, 22048, 22056, 22064, 22072, 22080, 22088, 22096, 22104, 22112, 22120, 22128, 22136, 22144, 22152, 
  22160, 22168, 22176, 22184, 22192, 22200, 22208, 22216, 22224, 22232, 22240, 22248, 22256, 22264, 22272, 22280, 
  22288, 22296, 22304, 22312, 22320, 22328, 22336, 22344, 22352, 22360, 22368, 22376, 22384, 22392, 22400, 22408, 
  22416, 22424, 22432, 22440, 22448, 22456, 22464, 22472, 22480, 22488, 22496, 22504, 22512, 22520, 22528, 22536, 
  22544, 22552, 22560, 22568, 22576, 22584, 22592, 22600, 22608, 22616, 22624, 22632, 22640, 22648, 22656, 22664, 
  22672, 22680, 22688, 22696, 22704, 22712, 22720, 22728, 22736, 22744, 22752, 22760, 22768, 22776, 22784, 22792, 
  22800, 22808, 22816, 22824, 22832, 22840, 22848, 22856, 22864, 22872, 22880, 22888, 22896, 22904, 22912, 22920, 
  22928, 22936, 22944, 22952, 22960, 22968, 22976, 22984, 22992, 23000, 23008, 23016, 23024, 23032, 23040, 23048, 
  23056, 23064, 23072, 23080, 23088, 23096, 23104, 23112, 23120, 23128, 23136, 23144, 23152, 23160, 23168, 23176, 
  23184, 23192, 23200, 23208, 23216, 23224, 23232, 23240, 23248, 23256, 23264, 23272, 23280, 23288, 23296, 23304, 
  23312, 23320, 23328, 23336, 23344, 23352, 23360, 23368, 23376, 23384, 23392, 23400, 23408, 23416, 23424, 23432, 
  23440, 23448, 23456, 23464, 23472, 23480, 23488, 23496, 23504, 23512, 23520, 23528, 23536, 23544, 23552, 23560, 
  23568, 23576, 23584, 23592, 23600, 23608, 23616, 23624, 23632, 23640, 23648, 23656, 23664, 23672, 23680, 23688, 
  23696, 23704, 23712, 23720, 23728, 23736, 23744, 23752, 23760, 23768, 23776, 23784, 23792, 23800, 23808, 23816, 
  23824, 23832, 23840, 23848, 23856, 23864, 23872, 23880, 23888, 23896, 23904, 23912, 23920, 23928, 23936, 23944, 
  23952, 23960, 23968, 23976, 23984, 23992, 24000, 24008, 24016, 24024, 24032, 24040, 24048, 24056, 24064, 24072, 
  24080, 24088, 24096, 24104, 24112, 24120, 24128, 24136, 24144, 24152, 24160, 24168, 24176, 24184, 24192, 24200, 
  24208, 24216, 24224, 24232, 24240, 24248, 24256, 24264, 24272, 24280, 24288, 24296, 24304, 24312, 24320, 24328, 
  24336, 24344, 24352, 24360, 24368, 24376, 24384, 24392, 24400, 24408, 24416, 24424, 24432, 24440, 24448, 24456, 
  24464, 24472, 24480, 24488, 24496, 24504, 24512, 24520, 24528, 24536, 24544, 24552, 24560, 24568, 24576, 24584, 
  24592, 24600, 24608, 24616, 24624, 24632, 24640, 24648, 24656, 24664, 24672, 24680, 24688, 24696, 24704, 24712, 
  24720, 24728, 24736, 24744, 24752, 24760, 24768, 24776, 24784, 24792, 24800, 24808, 24816, 24824, 24832, 24840, 
  24848, 24856, 24864, 24872, 24880, 24888, 24896, 24904, 24912, 24920, 24928, 24936, 24944, 24952, 24960, 24968, 
  24976, 24984, 24992, 25000, 25008, 25016, 25024, 25032, 25040, 25048, 25056, 25064, 25072, 25080, 25088, 25096, 
  25104, 25112, 25120, 25128, 25136, 25144, 25152, 25160, 25168, 25176, 25184, 25192, 25200, 25208, 25216, 25224, 
  25232, 25240, 25248, 25256, 25264, 25272, 25280, 25288, 25296, 25304, 25312, 25320, 25328, 25336, 25344, 25352, 
  25360, 25368, 25376, 25384, 25392, 25400, 25408, 25416, 25424, 25432, 25440, 25448, 25456, 25464, 25472, 25480, 
  25488, 25496, 25504, 25512, 25520, 25528, 25536, 25544, 25552, 25560, 25568, 25576, 25584, 25592, 25600, 25608, 
  25616, 25624, 25632, 25640, 25648, 25656, 25664, 25672, 25680, 25688, 25696, 25704, 25712, 25720, 25728, 25736, 
  25744, 25752, 25760, 25768, 25776, 25784, 25792, 25800, 25808, 25816, 25824, 25832, 25840, 25848, 25856, 25864, 
  25872, 25880, 25888, 25896, 25904, 25912, 25920, 25928, 25936, 25944, 25952, 25960, 25968, 25976, 25984, 25992, 
  26000, 26008, 26016, 26024, 26032, 26040, 26048, 26056, 26064, 26072, 26080, 26088, 26096, 26104, 26112, 26120, 
  26128, 26136, 26144, 26152, 26160, 26168, 26176, 26184, 26192, 26200, 26208, 26216, 26224, 26232, 26240, 26248, 
  26256, 26264, 26272, 26280, 26288, 26296, 26304, 26312, 26320, 26328, 26336, 26344, 26352, 26360, 26368, 26376, 
  26384, 26392, 26400, 26408, 26416, 26424, 26432, 26440, 26448, 26456, 26464, 26472, 26480, 26488, 26496, 26504, 
  26512, 26520, 26528, 26536, 26544, 26552, 26560, 26568, 26576, 26584, 26592, 26600, 26608, 26616, 26624, 26632, 
  26640, 26648, 26656, 26664, 26672, 26680, 26688, 26696, 26704, 26712, 26720, 26728, 26736, 26744, 26752, 26760, 
  26768, 26776, 26784, 26792, 26800, 26808, 26816, 26824, 26832, 26840, 26848, 26856, 26864, 26872, 26880, 26888, 
  26896, 26904, 26912, 26920, 26928, 26936, 26944, 26952, 26960, 26968, 26976, 26984, 26992, 27000, 27008, 27016, 
  27024, 27032, 27040, 27048, 27056, 27064, 27072, 27080, 27088, 27096, 27104, 27112, 27120, 27128, 27136, 27144, 
  27152, 27160, 27168, 27176, 27184, 27192, 27200, 27208, 27216, 27224, 27232, 27240, 27248, 27256, 27264, 27272, 
  27280, 27288, 27296, 27304, 27312, 27320, 27328, 27336, 27344, 27352, 27360, 27368, 27376, 27384, 27392, 27400, 
  27408, 27416, 27424, 27432, 27440, 27448, 27456, 27464, 27472, 27480, 27488, 27496, 27504, 27512, 27520, 27528, 
  27536, 27544, 27552, 27560, 27568, 27576, 27584, 27592, 27600, 27608, 27616, 27624, 27632, 27640, 27648, 27656, 
  27664, 27672, 27680, 27688, 27696, 27704, 27712, 27720, 27728, 27736, 27744, 27752, 27760, 27768, 27776, 27784, 
  27792, 27800, 27808, 27816, 27824, 27832, 27840, 27848, 27856, 27864, 27872, 27880, 27888, 27896, 27904, 27912, 
  27920, 27928, 27936, 27944, 27952, 27960, 27968, 27976, 27984, 27992, 28000, 28008, 28016, 28024, 28032, 28040, 
  28048, 28056, 28064, 28072, -28072}};
__TDESC(OfrontOPT_ExpCtxt__desc, 1, 0) = {__TDFLDS("ExpCtxt", 72), {-8}};

export void *OfrontOPT__init (void)
{
  __DEFMOD;
  __IMPORT(OfrontOPM__init);
  __IMPORT(OfrontOPS__init);
  __REGMOD("OfrontOPT", EnumPtrs);
  __REGCMD("Close", OfrontOPT_Close);
  __REGCMD("CloseScope", OfrontOPT_CloseScope);
  __INITYP(OfrontOPT_ConstArr__rec, OfrontOPT_ConstArr__rec, 0);
  __INITYP(OfrontOPT_ConstDesc, OfrontOPT_ConstDesc, 0);
  __INITYP(OfrontOPT_ObjDesc, OfrontOPT_ObjDesc, 0);
  __INITYP(OfrontOPT_StrDesc, OfrontOPT_StrDesc, 0);
  __INITYP(OfrontOPT_NodeDesc, OfrontOPT_NodeDesc, 0);
  __INITYP(OfrontOPT_ImpCtxt, OfrontOPT_ImpCtxt, 0);
  __INITYP(OfrontOPT_ExpCtxt, OfrontOPT_ExpCtxt, 0);
/* BEGIN */
  OfrontOPT_null = __NEWARR(NIL, 1, 1, 1, 1, (SYSTEM_ARRLEN)1);
  (OfrontOPT_null->data)[0] = 0x00;
  __ENDMOD;
}
