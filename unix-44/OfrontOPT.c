/* Ofront+ 1.0 -sC -44 */
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
  __ENUMR(&OfrontOPT_impCtxt, OfrontOPT_ImpCtxt__typ, 21128, 1, P);
}

__TDESC(OfrontOPT_ConstArr__rec__desc, 2, 4) = {__TDFLDS("ConstArr__rec", 16), {0, 4, 8, 12, -20}};
__TDESC(OfrontOPT_ConstDesc__desc, 2, 2) = {__TDFLDS("ConstDesc", 32), {0, 28, -12}};
__TDESC(OfrontOPT_ObjDesc__desc, 1, 10) = {__TDFLDS("ObjDesc", 64), {0, 4, 8, 12, 16, 32, 36, 40, 44, 48, -44}};
__TDESC(OfrontOPT_StrDesc__desc, 2, 3) = {__TDFLDS("StrDesc", 56), {44, 48, 52, -16}};
__TDESC(OfrontOPT_NodeDesc__desc, 2, 6) = {__TDFLDS("NodeDesc", 28), {0, 4, 8, 16, 20, 24, -28}};
__TDESC(OfrontOPT_ImpCtxt__desc, 2, 3508) = {__TDFLDS("ImpCtxt", 21128), {16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60, 64, 68, 72, 76, 
  80, 84, 88, 92, 96, 100, 104, 108, 112, 116, 120, 124, 128, 132, 136, 140, 
  144, 148, 152, 156, 160, 164, 168, 172, 176, 180, 184, 188, 192, 196, 200, 204, 
  208, 212, 216, 220, 224, 228, 232, 236, 240, 244, 248, 252, 256, 260, 264, 268, 
  272, 276, 280, 284, 288, 292, 296, 300, 304, 308, 312, 316, 320, 324, 328, 332, 
  336, 340, 344, 348, 352, 356, 360, 364, 368, 372, 376, 380, 384, 388, 392, 396, 
  400, 404, 408, 412, 416, 420, 424, 428, 432, 436, 440, 444, 448, 452, 456, 460, 
  464, 468, 472, 476, 480, 484, 488, 492, 496, 500, 504, 508, 512, 516, 520, 524, 
  528, 532, 536, 540, 544, 548, 552, 556, 560, 564, 568, 572, 576, 580, 584, 588, 
  592, 596, 600, 604, 608, 612, 616, 620, 624, 628, 632, 636, 640, 644, 648, 652, 
  656, 660, 664, 668, 672, 676, 680, 684, 688, 692, 696, 700, 704, 708, 712, 716, 
  720, 724, 728, 732, 736, 740, 744, 748, 752, 756, 760, 764, 768, 772, 776, 780, 
  784, 788, 792, 796, 800, 804, 808, 812, 816, 820, 824, 828, 832, 836, 840, 844, 
  848, 852, 856, 860, 864, 868, 872, 876, 880, 884, 888, 892, 896, 900, 904, 908, 
  912, 916, 920, 924, 928, 932, 936, 940, 944, 948, 952, 956, 960, 964, 968, 972, 
  976, 980, 984, 988, 992, 996, 1000, 1004, 1008, 1012, 1016, 1020, 1024, 1028, 1032, 1036, 
  1040, 1044, 1048, 1052, 1056, 1060, 1064, 1068, 1072, 1076, 1080, 1084, 1088, 1092, 1096, 1100, 
  1104, 1108, 1112, 1116, 1120, 1124, 1128, 1132, 1136, 1140, 1144, 1148, 1152, 1156, 1160, 1164, 
  1168, 1172, 1176, 1180, 1184, 1188, 1192, 1196, 1200, 1204, 1208, 1212, 1216, 1220, 1224, 1228, 
  1232, 1236, 1240, 1244, 1248, 1252, 1256, 1260, 1264, 1268, 1272, 1276, 1280, 1284, 1288, 1292, 
  1296, 1300, 1304, 1308, 1312, 1316, 1320, 1324, 1328, 1332, 1336, 1340, 1344, 1348, 1352, 1356, 
  1360, 1364, 1368, 1372, 1376, 1380, 1384, 1388, 1392, 1396, 1400, 1404, 1408, 1412, 1416, 1420, 
  1424, 1428, 1432, 1436, 1440, 1444, 1448, 1452, 1456, 1460, 1464, 1468, 1472, 1476, 1480, 1484, 
  1488, 1492, 1496, 1500, 1504, 1508, 1512, 1516, 1520, 1524, 1528, 1532, 1536, 1540, 1544, 1548, 
  1552, 1556, 1560, 1564, 1568, 1572, 1576, 1580, 1584, 1588, 1592, 1596, 1600, 1604, 1608, 1612, 
  1616, 1620, 1624, 1628, 1632, 1636, 1640, 1644, 1648, 1652, 1656, 1660, 1664, 1668, 1672, 1676, 
  1680, 1684, 1688, 1692, 1696, 1700, 1704, 1708, 1712, 1716, 1720, 1724, 1728, 1732, 1736, 1740, 
  1744, 1748, 1752, 1756, 1760, 1764, 1768, 1772, 1776, 1780, 1784, 1788, 1792, 1796, 1800, 1804, 
  1808, 1812, 1816, 1820, 1824, 1828, 1832, 1836, 1840, 1844, 1848, 1852, 1856, 1860, 1864, 1868, 
  1872, 1876, 1880, 1884, 1888, 1892, 1896, 1900, 1904, 1908, 1912, 1916, 1920, 1924, 1928, 1932, 
  1936, 1940, 1944, 1948, 1952, 1956, 1960, 1964, 1968, 1972, 1976, 1980, 1984, 1988, 1992, 1996, 
  2000, 2004, 2008, 2012, 2016, 2020, 2024, 2028, 2032, 2036, 2040, 2044, 2048, 2052, 2056, 2060, 
  2064, 2068, 2072, 2076, 2080, 2084, 2088, 2092, 2096, 2100, 2104, 2108, 2112, 2116, 2120, 2124, 
  2128, 2132, 2136, 2140, 2144, 2148, 2152, 2156, 2160, 2164, 2168, 2172, 2176, 2180, 2184, 2188, 
  2192, 2196, 2200, 2204, 2208, 2212, 2216, 2220, 2224, 2228, 2232, 2236, 2240, 2244, 2248, 2252, 
  2256, 2260, 2264, 2268, 2272, 2276, 2280, 2284, 2288, 2292, 2296, 2300, 2304, 2308, 2312, 2316, 
  2320, 2324, 2328, 2332, 2336, 2340, 2344, 2348, 2352, 2356, 2360, 2364, 2368, 2372, 2376, 2380, 
  2384, 2388, 2392, 2396, 2400, 2404, 2408, 2412, 2416, 2420, 2424, 2428, 2432, 2436, 2440, 2444, 
  2448, 2452, 2456, 2460, 2464, 2468, 2472, 2476, 2480, 2484, 2488, 2492, 2496, 2500, 2504, 2508, 
  2512, 2516, 2520, 2524, 2528, 2532, 2536, 2540, 2544, 2548, 2552, 2556, 2560, 2564, 2568, 2572, 
  2576, 2580, 2584, 2588, 2592, 2596, 2600, 2604, 2608, 2612, 2616, 2620, 2624, 2628, 2632, 2636, 
  2640, 2644, 2648, 2652, 2656, 2660, 2664, 2668, 2672, 2676, 2680, 2684, 2688, 2692, 2696, 2700, 
  2704, 2708, 2712, 2716, 2720, 2724, 2728, 2732, 2736, 2740, 2744, 2748, 2752, 2756, 2760, 2764, 
  2768, 2772, 2776, 2780, 2784, 2788, 2792, 2796, 2800, 2804, 2808, 2812, 2816, 2820, 2824, 2828, 
  2832, 2836, 2840, 2844, 2848, 2852, 2856, 2860, 2864, 2868, 2872, 2876, 2880, 2884, 2888, 2892, 
  2896, 2900, 2904, 2908, 2912, 2916, 2920, 2924, 2928, 2932, 2936, 2940, 2944, 2948, 2952, 2956, 
  2960, 2964, 2968, 2972, 2976, 2980, 2984, 2988, 2992, 2996, 3000, 3004, 3008, 3012, 3016, 3020, 
  3024, 3028, 3032, 3036, 3040, 3044, 3048, 3052, 3056, 3060, 3064, 3068, 3072, 3076, 3080, 3084, 
  3088, 3092, 3096, 3100, 3104, 3108, 3112, 3116, 3120, 3124, 3128, 3132, 3136, 3140, 3144, 3148, 
  3152, 3156, 3160, 3164, 3168, 3172, 3176, 3180, 3184, 3188, 3192, 3196, 3200, 3204, 3208, 3212, 
  3216, 3220, 3224, 3228, 3232, 3236, 3240, 3244, 3248, 3252, 3256, 3260, 3264, 3268, 3272, 3276, 
  3280, 3284, 3288, 3292, 3296, 3300, 3304, 3308, 3312, 3316, 3320, 3324, 3328, 3332, 3336, 3340, 
  3344, 3348, 3352, 3356, 3360, 3364, 3368, 3372, 3376, 3380, 3384, 3388, 3392, 3396, 3400, 3404, 
  3408, 3412, 3416, 3420, 3424, 3428, 3432, 3436, 3440, 3444, 3448, 3452, 3456, 3460, 3464, 3468, 
  3472, 3476, 3480, 3484, 3488, 3492, 3496, 3500, 3504, 3508, 3512, 3516, 3520, 3524, 3528, 3532, 
  3536, 3540, 3544, 3548, 3552, 3556, 3560, 3564, 3568, 3572, 3576, 3580, 3584, 3588, 3592, 3596, 
  3600, 3604, 3608, 3612, 3616, 3620, 3624, 3628, 3632, 3636, 3640, 3644, 3648, 3652, 3656, 3660, 
  3664, 3668, 3672, 3676, 3680, 3684, 3688, 3692, 3696, 3700, 3704, 3708, 3712, 3716, 3720, 3724, 
  3728, 3732, 3736, 3740, 3744, 3748, 3752, 3756, 3760, 3764, 3768, 3772, 3776, 3780, 3784, 3788, 
  3792, 3796, 3800, 3804, 3808, 3812, 3816, 3820, 3824, 3828, 3832, 3836, 3840, 3844, 3848, 3852, 
  3856, 3860, 3864, 3868, 3872, 3876, 3880, 3884, 3888, 3892, 3896, 3900, 3904, 3908, 3912, 3916, 
  3920, 3924, 3928, 3932, 3936, 3940, 3944, 3948, 3952, 3956, 3960, 3964, 3968, 3972, 3976, 3980, 
  3984, 3988, 3992, 3996, 4000, 4004, 4008, 4012, 4016, 4020, 4024, 4028, 4032, 4036, 4040, 4044, 
  4048, 4052, 4056, 4060, 4064, 4068, 4072, 4076, 4080, 4084, 4088, 4092, 4096, 4100, 4104, 4108, 
  4112, 4116, 4120, 4124, 4128, 4132, 4136, 4140, 4144, 4148, 4152, 4156, 4160, 4164, 4168, 4172, 
  4176, 4180, 4184, 4188, 4192, 4196, 4200, 4204, 4208, 4212, 4216, 4220, 4224, 4228, 4232, 4236, 
  4240, 4244, 4248, 4252, 4256, 4260, 4264, 4268, 4272, 4276, 4280, 4284, 4288, 4292, 4296, 4300, 
  4304, 4308, 4312, 4316, 4320, 4324, 4328, 4332, 4336, 4340, 4344, 4348, 4352, 4356, 4360, 4364, 
  4368, 4372, 4376, 4380, 4384, 4388, 4392, 4396, 4400, 4404, 4408, 4412, 4416, 4420, 4424, 4428, 
  4432, 4436, 4440, 4444, 4448, 4452, 4456, 4460, 4464, 4468, 4472, 4476, 4480, 4484, 4488, 4492, 
  4496, 4500, 4504, 4508, 4512, 4516, 4520, 4524, 4528, 4532, 4536, 4540, 4544, 4548, 4552, 4556, 
  4560, 4564, 4568, 4572, 4576, 4580, 4584, 4588, 4592, 4596, 4600, 4604, 4608, 4612, 4616, 4620, 
  4624, 4628, 4632, 4636, 4640, 4644, 4648, 4652, 4656, 4660, 4664, 4668, 4672, 4676, 4680, 4684, 
  4688, 4692, 4696, 4700, 4704, 4708, 4712, 4716, 4720, 4724, 4728, 4732, 4736, 4740, 4744, 4748, 
  4752, 4756, 4760, 4764, 4768, 4772, 4776, 4780, 4784, 4788, 4792, 4796, 4800, 4804, 4808, 4812, 
  4816, 4820, 4824, 4828, 4832, 4836, 4840, 4844, 4848, 4852, 4856, 4860, 4864, 4868, 4872, 4876, 
  4880, 4884, 4888, 4892, 4896, 4900, 4904, 4908, 4912, 4916, 4920, 4924, 4928, 4932, 4936, 4940, 
  4944, 4948, 4952, 4956, 4960, 4964, 4968, 4972, 4976, 4980, 4984, 4988, 4992, 4996, 5000, 5004, 
  5008, 5012, 5016, 5020, 5024, 5028, 5032, 5036, 5040, 5044, 5048, 5052, 5056, 5060, 5064, 5068, 
  5072, 5076, 5080, 5084, 5088, 5092, 5096, 5100, 5104, 5108, 5112, 5116, 5120, 5124, 5128, 5132, 
  5136, 5140, 5144, 5148, 5152, 5156, 5160, 5164, 5168, 5172, 5176, 5180, 5184, 5188, 5192, 5196, 
  5200, 5204, 5208, 5212, 5216, 5220, 5224, 5228, 5232, 5236, 5240, 5244, 5248, 5252, 5256, 5260, 
  5264, 5268, 5272, 5276, 5280, 5284, 5288, 5292, 5296, 5300, 5304, 5308, 5312, 5316, 5320, 5324, 
  5328, 5332, 5336, 5340, 5344, 5348, 5352, 5356, 5360, 5364, 5368, 5372, 5376, 5380, 5384, 5388, 
  5392, 5396, 5400, 5404, 5408, 5412, 5416, 5420, 5424, 5428, 5432, 5436, 5440, 5444, 5448, 5452, 
  5456, 5460, 5464, 5468, 5472, 5476, 5480, 5484, 5488, 5492, 5496, 5500, 5504, 5508, 5512, 5516, 
  5520, 5524, 5528, 5532, 5536, 5540, 5544, 5548, 5552, 5556, 5560, 5564, 5568, 5572, 5576, 5580, 
  5584, 5588, 5592, 5596, 5600, 5604, 5608, 5612, 5616, 5620, 5624, 5628, 5632, 5636, 5640, 5644, 
  5648, 5652, 5656, 5660, 5664, 5668, 5672, 5676, 5680, 5684, 5688, 5692, 5696, 5700, 5704, 5708, 
  5712, 5716, 5720, 5724, 5728, 5732, 5736, 5740, 5744, 5748, 5752, 5756, 5760, 5764, 5768, 5772, 
  5776, 5780, 5784, 5788, 5792, 5796, 5800, 5804, 5808, 5812, 5816, 5820, 5824, 5828, 5832, 5836, 
  5840, 5844, 5848, 5852, 5856, 5860, 5864, 5868, 5872, 5876, 5880, 5884, 5888, 5892, 5896, 5900, 
  5904, 5908, 5912, 5916, 5920, 5924, 5928, 5932, 5936, 5940, 5944, 5948, 5952, 5956, 5960, 5964, 
  5968, 5972, 5976, 5980, 5984, 5988, 5992, 5996, 6000, 6004, 6008, 6012, 6016, 6020, 6024, 6028, 
  6032, 6036, 6040, 6044, 6048, 6052, 6056, 6060, 6064, 6068, 6072, 6076, 6080, 6084, 6088, 6092, 
  6096, 6100, 6104, 6108, 6112, 6116, 6120, 6124, 6128, 6132, 6136, 6140, 6144, 6148, 6152, 6156, 
  6160, 6164, 6168, 6172, 6176, 6180, 6184, 6188, 6192, 6196, 6200, 6204, 6208, 6212, 6216, 6220, 
  6224, 6228, 6232, 6236, 6240, 6244, 6248, 6252, 6256, 6260, 6264, 6268, 6272, 6276, 6280, 6284, 
  6288, 6292, 6296, 6300, 6304, 6308, 6312, 6316, 6320, 6324, 6328, 6332, 6336, 6340, 6344, 6348, 
  6352, 6356, 6360, 6364, 6368, 6372, 6376, 6380, 6384, 6388, 6392, 6396, 6400, 6404, 6408, 6412, 
  6416, 6420, 6424, 6428, 6432, 6436, 6440, 6444, 6448, 6452, 6456, 6460, 6464, 6468, 6472, 6476, 
  6480, 6484, 6488, 6492, 6496, 6500, 6504, 6508, 6512, 6516, 6520, 6524, 6528, 6532, 6536, 6540, 
  6544, 6548, 6552, 6556, 6560, 6564, 6568, 6572, 6576, 6580, 6584, 6588, 6592, 6596, 6600, 6604, 
  6608, 6612, 6616, 6620, 6624, 6628, 6632, 6636, 6640, 6644, 6648, 6652, 6656, 6660, 6664, 6668, 
  6672, 6676, 6680, 6684, 6688, 6692, 6696, 6700, 6704, 6708, 6712, 6716, 6720, 6724, 6728, 6732, 
  6736, 6740, 6744, 6748, 6752, 6756, 6760, 6764, 6768, 6772, 6776, 6780, 6784, 6788, 6792, 6796, 
  6800, 6804, 6808, 6812, 6816, 6820, 6824, 6828, 6832, 6836, 6840, 6844, 6848, 6852, 6856, 6860, 
  6864, 6868, 6872, 6876, 6880, 6884, 6888, 6892, 6896, 6900, 6904, 6908, 6912, 6916, 6920, 6924, 
  6928, 6932, 6936, 6940, 6944, 6948, 6952, 6956, 6960, 6964, 6968, 6972, 6976, 6980, 6984, 6988, 
  6992, 6996, 7000, 7004, 7008, 7012, 7016, 7020, 7024, 7028, 7032, 7036, 7040, 7044, 7048, 7052, 
  7056, 7060, 7064, 7068, 7072, 7076, 7080, 7084, 7088, 7092, 7096, 7100, 7104, 7108, 7112, 7116, 
  7120, 7124, 7128, 7132, 7136, 7140, 7144, 7148, 7152, 7156, 7160, 7164, 7168, 7172, 7176, 7180, 
  7184, 7188, 7192, 7196, 7200, 7204, 7208, 7212, 7216, 7220, 7224, 7228, 7232, 7236, 7240, 7244, 
  7248, 7252, 7256, 7260, 7264, 7268, 7272, 7276, 7280, 7284, 7288, 7292, 7296, 7300, 7304, 7308, 
  7312, 7316, 7320, 7324, 7328, 7332, 7336, 7340, 7344, 7348, 7352, 7356, 7360, 7364, 7368, 7372, 
  7376, 7380, 7384, 7388, 7392, 7396, 7400, 7404, 7408, 7412, 7416, 7420, 7424, 7428, 7432, 7436, 
  7440, 7444, 7448, 7452, 7456, 7460, 7464, 7468, 7472, 7476, 7480, 7484, 7488, 7492, 7496, 7500, 
  7504, 7508, 7512, 7516, 7520, 7524, 7528, 7532, 7536, 7540, 7544, 7548, 7552, 7556, 7560, 7564, 
  7568, 7572, 7576, 7580, 7584, 7588, 7592, 7596, 7600, 7604, 7608, 7612, 7616, 7620, 7624, 7628, 
  7632, 7636, 7640, 7644, 7648, 7652, 7656, 7660, 7664, 7668, 7672, 7676, 7680, 7684, 7688, 7692, 
  7696, 7700, 7704, 7708, 7712, 7716, 7720, 7724, 7728, 7732, 7736, 7740, 7744, 7748, 7752, 7756, 
  7760, 7764, 7768, 7772, 7776, 7780, 7784, 7788, 7792, 7796, 7800, 7804, 7808, 7812, 7816, 7820, 
  7824, 7828, 7832, 7836, 7840, 7844, 7848, 7852, 7856, 7860, 7864, 7868, 7872, 7876, 7880, 7884, 
  7888, 7892, 7896, 7900, 7904, 7908, 7912, 7916, 7920, 7924, 7928, 7932, 7936, 7940, 7944, 7948, 
  7952, 7956, 7960, 7964, 7968, 7972, 7976, 7980, 7984, 7988, 7992, 7996, 8000, 8004, 8008, 8012, 
  8016, 8020, 8024, 8028, 8032, 8036, 8040, 8044, 8048, 8052, 8056, 8060, 8064, 8068, 8072, 8076, 
  8080, 8084, 8088, 8092, 8096, 8100, 8104, 8108, 8112, 8116, 8120, 8124, 8128, 8132, 8136, 8140, 
  8144, 8148, 8152, 8156, 8160, 8164, 8168, 8172, 8176, 8180, 8184, 8188, 8192, 8196, 8200, 8204, 
  8208, 8212, 8216, 8220, 8224, 8228, 8232, 8236, 8240, 8244, 8248, 8252, 8256, 8260, 8264, 8268, 
  8272, 8276, 8280, 8284, 8288, 8292, 8296, 8300, 8304, 8308, 8312, 8316, 8320, 8324, 8328, 8332, 
  8336, 8340, 8344, 8348, 8352, 8356, 8360, 8364, 8368, 8372, 8376, 8380, 8384, 8388, 8392, 8396, 
  8400, 8404, 8408, 8412, 8416, 8420, 8424, 8428, 8432, 8436, 8440, 8444, 8448, 8452, 8456, 8460, 
  8464, 8468, 8472, 8476, 8480, 8484, 8488, 8492, 8496, 8500, 8504, 8508, 8512, 8516, 8520, 8524, 
  8528, 8532, 8536, 8540, 8544, 8548, 8552, 8556, 8560, 8564, 8568, 8572, 8576, 8580, 8584, 8588, 
  8592, 8596, 8600, 8604, 8608, 8612, 8616, 8620, 8624, 8628, 8632, 8636, 8640, 8644, 8648, 8652, 
  8656, 8660, 8664, 8668, 8672, 8676, 8680, 8684, 8688, 8692, 8696, 8700, 8704, 8708, 8712, 8716, 
  8720, 8724, 8728, 8732, 8736, 8740, 8744, 8748, 8752, 8756, 8760, 8764, 8768, 8772, 8776, 8780, 
  8784, 8788, 8792, 8796, 8800, 8804, 8808, 8812, 8816, 8820, 8824, 8828, 8832, 8836, 8840, 8844, 
  8848, 8852, 8856, 8860, 8864, 8868, 8872, 8876, 8880, 8884, 8888, 8892, 8896, 8900, 8904, 8908, 
  8912, 8916, 8920, 8924, 8928, 8932, 8936, 8940, 8944, 8948, 8952, 8956, 8960, 8964, 8968, 8972, 
  8976, 8980, 8984, 8988, 8992, 8996, 9000, 9004, 9008, 9012, 9016, 9020, 9024, 9028, 9032, 9036, 
  9040, 9044, 9048, 9052, 9056, 9060, 9064, 9068, 9072, 9076, 9080, 9084, 9088, 9092, 9096, 9100, 
  9104, 9108, 9112, 9116, 9120, 9124, 9128, 9132, 9136, 9140, 9144, 9148, 9152, 9156, 9160, 9164, 
  9168, 9172, 9176, 9180, 9184, 9188, 9192, 9196, 9200, 9204, 9208, 9212, 9216, 9220, 9224, 9228, 
  9232, 9236, 9240, 9244, 9248, 9252, 9256, 9260, 9264, 9268, 9272, 9276, 9280, 9284, 9288, 9292, 
  9296, 9300, 9304, 9308, 9312, 9316, 9320, 9324, 9328, 9332, 9336, 9340, 9344, 9348, 9352, 9356, 
  9360, 9364, 9368, 9372, 9376, 9380, 9384, 9388, 9392, 9396, 9400, 9404, 9408, 9412, 9416, 9420, 
  9424, 9428, 9432, 9436, 9440, 9444, 9448, 9452, 9456, 9460, 9464, 9468, 9472, 9476, 9480, 9484, 
  9488, 9492, 9496, 9500, 9504, 9508, 9512, 9516, 9520, 9524, 9528, 9532, 9536, 9540, 9544, 9548, 
  9552, 9556, 9560, 9564, 9568, 9572, 9576, 9580, 9584, 9588, 9592, 9596, 9600, 9604, 9608, 9612, 
  9616, 9620, 9624, 9628, 9632, 9636, 9640, 9644, 9648, 9652, 9656, 9660, 9664, 9668, 9672, 9676, 
  9680, 9684, 9688, 9692, 9696, 9700, 9704, 9708, 9712, 9716, 9720, 9724, 9728, 9732, 9736, 9740, 
  9744, 9748, 9752, 9756, 9760, 9764, 9768, 9772, 9776, 9780, 9784, 9788, 9792, 9796, 9800, 9804, 
  9808, 9812, 9816, 9820, 9824, 9828, 9832, 9836, 9840, 9844, 9848, 9852, 9856, 9860, 9864, 9868, 
  9872, 9876, 9880, 9884, 9888, 9892, 9896, 9900, 9904, 9908, 9912, 9916, 9920, 9924, 9928, 9932, 
  9936, 9940, 9944, 9948, 9952, 9956, 9960, 9964, 9968, 9972, 9976, 9980, 9984, 9988, 9992, 9996, 
  10000, 10004, 10008, 10012, 10016, 10020, 10024, 10028, 10032, 10036, 10040, 10044, 10048, 10052, 10056, 10060, 
  10064, 10068, 10072, 10076, 10080, 10084, 10088, 10092, 10096, 10100, 10104, 10108, 10112, 10116, 10120, 10124, 
  10128, 10132, 10136, 10140, 10144, 10148, 10152, 10156, 10160, 10164, 10168, 10172, 10176, 10180, 10184, 10188, 
  10192, 10196, 10200, 10204, 10208, 10212, 10216, 10220, 10224, 10228, 10232, 10236, 10240, 10244, 10248, 10252, 
  10256, 10260, 10264, 10268, 10272, 10276, 10280, 10284, 10288, 10292, 10296, 10300, 10304, 10308, 10312, 10316, 
  10320, 10324, 10328, 10332, 10336, 10340, 10344, 10348, 10352, 10356, 10360, 10364, 10368, 10372, 10376, 10380, 
  10384, 10388, 10392, 10396, 10400, 10404, 10408, 10412, 10416, 10420, 10424, 10428, 10432, 10436, 10440, 10444, 
  10448, 10452, 10456, 10460, 10464, 10468, 10472, 10476, 10480, 10484, 10488, 10492, 10496, 10500, 10504, 10508, 
  10512, 10516, 10520, 10524, 10528, 10532, 10536, 10540, 10544, 10548, 10552, 10556, 10560, 10564, 10568, 10572, 
  10576, 10580, 10584, 10588, 10592, 10596, 10600, 10604, 10608, 10612, 10616, 10620, 10624, 10628, 10632, 10636, 
  10640, 10644, 10648, 10652, 10656, 10660, 10664, 10668, 10672, 10676, 10680, 10684, 10688, 10692, 10696, 10700, 
  10704, 10708, 10712, 10716, 10720, 10724, 10728, 10732, 10736, 10740, 10744, 10748, 10752, 10756, 10760, 10764, 
  10768, 10772, 10776, 10780, 10784, 10788, 10792, 10796, 10800, 10804, 10808, 10812, 10816, 10820, 10824, 10828, 
  10832, 10836, 10840, 10844, 10848, 10852, 10856, 10860, 10864, 10868, 10872, 10876, 10880, 10884, 10888, 10892, 
  10896, 10900, 10904, 10908, 10912, 10916, 10920, 10924, 10928, 10932, 10936, 10940, 10944, 10948, 10952, 10956, 
  10960, 10964, 10968, 10972, 10976, 10980, 10984, 10988, 10992, 10996, 11000, 11004, 11008, 11012, 11016, 11020, 
  11024, 11028, 11032, 11036, 11040, 11044, 11048, 11052, 11056, 11060, 11064, 11068, 11072, 11076, 11080, 11084, 
  11088, 11092, 11096, 11100, 11104, 11108, 11112, 11116, 11120, 11124, 11128, 11132, 11136, 11140, 11144, 11148, 
  11152, 11156, 11160, 11164, 11168, 11172, 11176, 11180, 11184, 11188, 11192, 11196, 11200, 11204, 11208, 11212, 
  11216, 11220, 11224, 11228, 11232, 11236, 11240, 11244, 11248, 11252, 11256, 11260, 11264, 11268, 11272, 11276, 
  11280, 11284, 11288, 11292, 11296, 11300, 11304, 11308, 11312, 11316, 11320, 11324, 11328, 11332, 11336, 11340, 
  11344, 11348, 11352, 11356, 11360, 11364, 11368, 11372, 11376, 11380, 11384, 11388, 11392, 11396, 11400, 11404, 
  11408, 11412, 11416, 11420, 11424, 11428, 11432, 11436, 11440, 11444, 11448, 11452, 11456, 11460, 11464, 11468, 
  11472, 11476, 11480, 11484, 11488, 11492, 11496, 11500, 11504, 11508, 11512, 11516, 11520, 11524, 11528, 11532, 
  11536, 11540, 11544, 11548, 11552, 11556, 11560, 11564, 11568, 11572, 11576, 11580, 11584, 11588, 11592, 11596, 
  11600, 11604, 11608, 11612, 11616, 11620, 11624, 11628, 11632, 11636, 11640, 11644, 11648, 11652, 11656, 11660, 
  11664, 11668, 11672, 11676, 11680, 11684, 11688, 11692, 11696, 11700, 11704, 11708, 11712, 11716, 11720, 11724, 
  11728, 11732, 11736, 11740, 11744, 11748, 11752, 11756, 11760, 11764, 11768, 11772, 11776, 11780, 11784, 11788, 
  11792, 11796, 11800, 11804, 11808, 11812, 11816, 11820, 11824, 11828, 11832, 11836, 11840, 11844, 11848, 11852, 
  11856, 11860, 11864, 11868, 11872, 11876, 11880, 11884, 11888, 11892, 11896, 11900, 11904, 11908, 11912, 11916, 
  11920, 11924, 11928, 11932, 11936, 11940, 11944, 11948, 11952, 11956, 11960, 11964, 11968, 11972, 11976, 11980, 
  11984, 11988, 11992, 11996, 12000, 12004, 12008, 12012, 12016, 12020, 12024, 12028, 12032, 12036, 12040, 12044, 
  12048, 12052, 12056, 12060, 12064, 12068, 12072, 12076, 12080, 12084, 12088, 12092, 12096, 12100, 12104, 12108, 
  12112, 12116, 12120, 12124, 12128, 12132, 12136, 12140, 12144, 12148, 12152, 12156, 12160, 12164, 12168, 12172, 
  12176, 12180, 12184, 12188, 12192, 12196, 12200, 12204, 12208, 12212, 12216, 12220, 12224, 12228, 12232, 12236, 
  12240, 12244, 12248, 12252, 12256, 12260, 12264, 12268, 12272, 12276, 12280, 12284, 12288, 12292, 12296, 12300, 
  12304, 12308, 12312, 12316, 12320, 12324, 12328, 12332, 12336, 12340, 12344, 12348, 12352, 12356, 12360, 12364, 
  12368, 12372, 12376, 12380, 12384, 12388, 12392, 12396, 12400, 12404, 12408, 12412, 12416, 12420, 12424, 12428, 
  12432, 12436, 12440, 12444, 12448, 12452, 12456, 12460, 12464, 12468, 12472, 12476, 12480, 12484, 12488, 12492, 
  12496, 12500, 12504, 12508, 12512, 12516, 12520, 12524, 12528, 12532, 12536, 12540, 12544, 12548, 12552, 12556, 
  12560, 12564, 12568, 12572, 12576, 12580, 12584, 12588, 12592, 12596, 12600, 12604, 12608, 12612, 12616, 12620, 
  12624, 12628, 12632, 12636, 12640, 12644, 12648, 12652, 12656, 12660, 12664, 12668, 12672, 12676, 12680, 12684, 
  12688, 12692, 12696, 12700, 12704, 12708, 12712, 12716, 12720, 12724, 12728, 12732, 12736, 12740, 12744, 12748, 
  12752, 12756, 12760, 12764, 12768, 12772, 12776, 12780, 12784, 12788, 12792, 12796, 12800, 12804, 12808, 12812, 
  12816, 12820, 12824, 12828, 12832, 12836, 12840, 12844, 12848, 12852, 12856, 12860, 12864, 12868, 12872, 12876, 
  12880, 12884, 12888, 12892, 12896, 12900, 12904, 12908, 12912, 12916, 12920, 12924, 12928, 12932, 12936, 12940, 
  12944, 12948, 12952, 12956, 12960, 12964, 12968, 12972, 12976, 12980, 12984, 12988, 12992, 12996, 13000, 13004, 
  13008, 13012, 13016, 13020, 13024, 13028, 13032, 13036, 13040, 13044, 13048, 13052, 13056, 13060, 13064, 13068, 
  13072, 13076, 13080, 13084, 13088, 13092, 13096, 13100, 13104, 13108, 13112, 13116, 13120, 13124, 13128, 13132, 
  13136, 13140, 13144, 13148, 13152, 13156, 13160, 13164, 13168, 13172, 13176, 13180, 13184, 13188, 13192, 13196, 
  13200, 13204, 13208, 13212, 13216, 13220, 13224, 13228, 13232, 13236, 13240, 13244, 13248, 13252, 13256, 13260, 
  13264, 13268, 13272, 13276, 13280, 13284, 13288, 13292, 13296, 13300, 13304, 13308, 13312, 13316, 13320, 13324, 
  13328, 13332, 13336, 13340, 13344, 13348, 13352, 13356, 13360, 13364, 13368, 13372, 13376, 13380, 13384, 13388, 
  13392, 13396, 13400, 13404, 13408, 13412, 13416, 13420, 13424, 13428, 13432, 13436, 13440, 13444, 13448, 13452, 
  13456, 13460, 13464, 13468, 13472, 13476, 13480, 13484, 13488, 13492, 13496, 13500, 13504, 13508, 13512, 13516, 
  13520, 13524, 13528, 13532, 13536, 13540, 13544, 13548, 13552, 13556, 13560, 13564, 13568, 13572, 13576, 13580, 
  13584, 13588, 13592, 13596, 13600, 13604, 13608, 13612, 13616, 13620, 13624, 13628, 13632, 13636, 13640, 13644, 
  13648, 13652, 13656, 13660, 13664, 13668, 13672, 13676, 13680, 13684, 13688, 13692, 13696, 13700, 13704, 13708, 
  13712, 13716, 13720, 13724, 13728, 13732, 13736, 13740, 13744, 13748, 13752, 13756, 13760, 13764, 13768, 13772, 
  13776, 13780, 13784, 13788, 13792, 13796, 13800, 13804, 13808, 13812, 13816, 13820, 13824, 13828, 13832, 13836, 
  13840, 13844, 13848, 13852, 13856, 13860, 13864, 13868, 13872, 13876, 13880, 13884, 13888, 13892, 13896, 13900, 
  13904, 13908, 13912, 13916, 13920, 13924, 13928, 13932, 13936, 13940, 13944, 13948, 13952, 13956, 13960, 13964, 
  13968, 13972, 13976, 13980, 13984, 13988, 13992, 13996, 14000, 14004, 14008, 14012, 14016, 14020, 14024, 14028, 
  14032, 14036, 14040, 14044, -14036}};
__TDESC(OfrontOPT_ExpCtxt__desc, 1, 0) = {__TDFLDS("ExpCtxt", 72), {-4}};

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
