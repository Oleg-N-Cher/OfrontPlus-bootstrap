/* Ofront+ 1.0 -sC -88 */
#include "SYSTEM.oh"
#include "OfrontOPT.oh"
#include "OfrontOPS.oh"
#include "OfrontOPC.oh"
#include "OfrontOPM.oh"

typedef
  struct OfrontOPV_ExitInfo {
    SHORTINT level, label;
  } OfrontOPV_ExitInfo;


static BOOLEAN OfrontOPV_assert, OfrontOPV_inxchk, OfrontOPV_mainprog, OfrontOPV_ansi, OfrontOPV_oldc;
static SHORTINT OfrontOPV_stamp, OfrontOPV_recno;
static OfrontOPV_ExitInfo OfrontOPV_exit;
static SHORTINT OfrontOPV_nofExitLabels;

export void **OfrontOPV_ExitInfo__typ;

static void OfrontOPV_ActualPar (OfrontOPT_Node n, OfrontOPT_Object fp);
static void OfrontOPV_AddCopy (OfrontOPT_Node left, OfrontOPT_Node right, BOOLEAN first);
static void OfrontOPV_Adr (OfrontOPT_Node n, SHORTINT prec, BOOLEAN cast_adr);
export void OfrontOPV_AdrAndSize (OfrontOPT_Object topScope);
static void OfrontOPV_CaseStat (OfrontOPT_Node n, OfrontOPT_Object outerProc);
static void OfrontOPV_Convert (OfrontOPT_Node n, SHORTINT form, SHORTINT prec);
static void OfrontOPV_CountTProcs (OfrontOPT_Struct rec);
static void OfrontOPV_DefineTDescs (OfrontOPT_Node n);
static void OfrontOPV_Entier (OfrontOPT_Node n, SHORTINT prec);
static void OfrontOPV_IfStat (OfrontOPT_Node n, BOOLEAN withtrap, OfrontOPT_Object outerProc);
static BOOLEAN OfrontOPV_ImplicitReturn (OfrontOPT_Node n);
static void OfrontOPV_Index (OfrontOPT_Node n, OfrontOPT_Node d, SHORTINT prec, SHORTINT dim);
export void OfrontOPV_Init (void);
static void OfrontOPV_InitTDescs (OfrontOPT_Node n);
static void OfrontOPV_LEntier (OfrontOPT_Node n, SHORTINT prec);
static void OfrontOPV_Len (OfrontOPT_Node n, INTEGER dim, BOOLEAN incl0x);
static void OfrontOPV_MaxLen (OfrontOPT_Node left, OfrontOPT_Node right);
export void OfrontOPV_Module (OfrontOPT_Node prog);
static void OfrontOPV_NewArr (OfrontOPT_Node d, OfrontOPT_Node x);
static BOOLEAN OfrontOPV_OpParentheses (SHORTINT ePrec, SHORTINT prec);
static SHORTINT OfrontOPV_Precedence (SHORTINT class, SHORTINT subclass, SHORTINT form, SHORTINT comp);
static BOOLEAN OfrontOPV_SameExp (OfrontOPT_Node n1, OfrontOPT_Node n2);
static BOOLEAN OfrontOPV_SideEffects (OfrontOPT_Node n);
static void OfrontOPV_Stamp (OfrontOPS_String *s);
static void OfrontOPV_StringCopy (OfrontOPT_Node left, OfrontOPT_Node right, BOOLEAN exp);
static void OfrontOPV_StringModifier (OfrontOPT_Node n);
static OfrontOPT_Object OfrontOPV_SuperProc (OfrontOPT_Node n);
static void OfrontOPV_Traverse (OfrontOPT_Object obj, OfrontOPT_Object outerScope, BOOLEAN exported);
static void OfrontOPV_TraverseType (OfrontOPT_Struct typ);
export void OfrontOPV_TypSize (OfrontOPT_Struct typ);
static void OfrontOPV_TypeOf (OfrontOPT_Node n);
static void OfrontOPV_compStat (OfrontOPT_Node n, BOOLEAN exp);
static void OfrontOPV_design (OfrontOPT_Node n, SHORTINT prec);
static void OfrontOPV_design_adr (OfrontOPT_Node n, SHORTINT prec, BOOLEAN adr);
static void OfrontOPV_expr (OfrontOPT_Node n, SHORTINT prec);
static void OfrontOPV_expr_val (OfrontOPT_Node n, SHORTINT prec, BOOLEAN lvalue);
static void OfrontOPV_stat (OfrontOPT_Node n, OfrontOPT_Object outerProc);


/*============================================================================*/

void OfrontOPV_Init (void)
{
  OfrontOPC_Init();
  OfrontOPV_stamp = 0;
  OfrontOPV_recno = 0;
  OfrontOPV_nofExitLabels = 0;
  OfrontOPV_assert = __IN(7, OfrontOPM_opt);
  OfrontOPV_inxchk = __IN(0, OfrontOPM_opt);
  OfrontOPV_mainprog = __IN(10, OfrontOPM_opt);
  OfrontOPV_ansi = __IN(6, OfrontOPM_opt);
  OfrontOPV_oldc = __IN(13, OfrontOPM_opt);
}

/*----------------------------------------------------------------------------*/
void OfrontOPV_TypSize (OfrontOPT_Struct typ)
{
  SHORTINT f, c;
  INTEGER offset, size, base, fbase, off0;
  OfrontOPT_Object fld = NIL;
  OfrontOPT_Struct btyp = NIL;
  if (typ == OfrontOPT_undftyp) {
    OfrontOPM_err(58);
  } else if (typ->size == -1) {
    f = typ->form;
    c = typ->comp;
    if ((INTEGER)c == 4) {
      btyp = typ->BaseTyp;
      if (btyp == NIL) {
        offset = 0;
        base = 1;
      } else {
        OfrontOPV_TypSize(btyp);
        offset = btyp->size - __ASHR((INTEGER)btyp->sysflag, 8, INTEGER);
        base = btyp->align;
      }
      fld = typ->link;
      while (fld != NIL && (INTEGER)fld->mode == 4) {
        btyp = fld->typ;
        OfrontOPV_TypSize(btyp);
        size = btyp->size;
        fbase = OfrontOPC_BaseAlignment(btyp, typ->sysflag);
        if ((INTEGER)typ->sysflag == 7) {
          fld->adr = 0;
          if (size > offset) {
            offset = size;
          }
        } else {
          OfrontOPC_Align(&offset, fbase);
          fld->adr = offset;
          offset += size;
        }
        if (fbase > base) {
          base = fbase;
        }
        fld = fld->link;
      }
      off0 = offset;
      if (offset == 0) {
        offset = 1;
      }
      OfrontOPC_Align(&offset, base);
      if (typ->strobj == NIL && __MASK(typ->align, -65536) == 0) {
        OfrontOPV_recno += 1;
        base += __ASHL((INTEGER)OfrontOPV_recno, 16, INTEGER);
      }
      typ->size = offset;
      typ->align = base;
      typ->sysflag = (SHORTINT)(__MASK((INTEGER)typ->sysflag, -256) + (INTEGER)((SHORTINT)__ASHL(offset - off0, 8, INTEGER)));
      typ->n = -1;
    } else if ((INTEGER)c == 2) {
      OfrontOPV_TypSize(typ->BaseTyp);
      if ((typ->strobj == NIL && typ == typ->BaseTyp->BaseTyp) && __MASK(typ->align, -65536) == 0) {
        OfrontOPV_recno += 1;
        typ->align += __ASHL((INTEGER)OfrontOPV_recno, 16, INTEGER);
      }
      typ->size = typ->n * typ->BaseTyp->size;
    } else if ((INTEGER)f == 13) {
      typ->size = OfrontOPM_AdrSize;
      if (typ->BaseTyp == OfrontOPT_undftyp) {
        OfrontOPM_Mark(128, typ->n);
      } else {
        OfrontOPV_TypSize(typ->BaseTyp);
      }
      if (typ->BaseTyp == OfrontOPT_anytyp && typ->strobj == NIL) {
        typ->strobj = OfrontOPT_anyptrtyp->strobj;
      }
    } else if ((INTEGER)f == 15) {
      typ->size = OfrontOPM_AdrSize;
    } else if ((INTEGER)c == 3) {
      btyp = typ->BaseTyp;
      OfrontOPV_TypSize(btyp);
      if (((typ->strobj == NIL && btyp->BaseTyp != NIL) && btyp == btyp->BaseTyp->BaseTyp) && __MASK(typ->align, -65536) == 0) {
        OfrontOPV_recno += 1;
        typ->align += __ASHL((INTEGER)OfrontOPV_recno, 16, INTEGER);
      }
      if (__ODD(typ->sysflag)) {
        typ->size = 4;
      } else if ((INTEGER)btyp->comp == 3) {
        typ->size = btyp->size + 4;
      } else {
        typ->size = 8;
      }
    }
  }
}

/*----------------------------------------------------------------------------*/
static struct CountTProcs__7 {
  OfrontOPT_Struct *rec;
  struct CountTProcs__7 *lnk;
} *CountTProcs__7_s;

static void __8 (OfrontOPT_Object obj);

static void __8 (OfrontOPT_Object obj)
{
  OfrontOPT_Object redef = NIL;
  OfrontOPS_String _ptr__10 = NIL;
  if (obj != NIL) {
    __8(obj->left);
    if ((INTEGER)obj->mode == 13) {
      _ptr__10 = obj->name;
      OfrontOPT_FindBaseField((void*)_ptr__10->data, _ptr__10->len[0], (*CountTProcs__7_s->rec), &redef);
      if (redef != NIL) {
        obj->adr = redef->adr;
        if (!__IN(2, obj->conval->setval) || (redef->conval->setval & 0x1a0000) == 0x0) {
          OfrontOPM_Mark(119, ((*CountTProcs__7_s->rec))->txtpos);
        }
      } else {
        obj->adr = __ASHL(((*CountTProcs__7_s->rec))->n, 16, INTEGER);
        ((*CountTProcs__7_s->rec))->n += 1;
      }
      if ((obj->conval->setval & 0x0a0002) == 0x0) {
        OfrontOPM_Mark(129, obj->adr);
      }
    }
    __8(obj->right);
  }
}

static void OfrontOPV_CountTProcs (OfrontOPT_Struct rec)
{
  OfrontOPT_Struct btyp = NIL;
  struct CountTProcs__7 _s;
  _s.rec = &rec;
  _s.lnk = CountTProcs__7_s;
  CountTProcs__7_s = &_s;
  if (rec->n == -1) {
    if ((INTEGER)rec->sysflag != 0) {
      rec->n = 0;
    } else {
      rec->n = OfrontOPT_anytyp->n;
    }
    btyp = rec->BaseTyp;
    if (btyp != NIL) {
      OfrontOPV_CountTProcs(btyp);
      rec->n = btyp->n;
    }
    __8(rec->link);
  }
  CountTProcs__7_s = _s.lnk;
}

static void OfrontOPV_TraverseType (OfrontOPT_Struct typ)
{
  OfrontOPT_Object p = NIL;
  if (!typ->allocated) {
    typ->allocated = 1;
    OfrontOPV_TypSize(typ);
    if ((INTEGER)typ->comp == 4) {
      OfrontOPV_CountTProcs(typ);
      if ((INTEGER)typ->extlev > 14) {
        OfrontOPM_Mark(233, typ->txtpos);
      }
      if (typ->BaseTyp != NIL) {
        OfrontOPV_TraverseType(typ->BaseTyp);
      }
      OfrontOPV_Traverse(typ->link, typ->strobj, 0);
    } else if ((INTEGER)typ->form == 13) {
      if (typ->BaseTyp == OfrontOPT_undftyp) {
        OfrontOPM_Mark(128, typ->txtpos);
      }
      OfrontOPV_TraverseType(typ->BaseTyp);
      if (OfrontOPC_ArrayType(typ->BaseTyp)) {
        OfrontOPC_InsertArrayType(typ->BaseTyp);
      }
    } else if ((INTEGER)typ->form == 15) {
      OfrontOPV_TraverseType(typ->BaseTyp);
      p = typ->link;
      while (p != NIL) {
        OfrontOPV_TraverseType(p->typ);
        p = p->link;
      }
    } else {
      OfrontOPV_TraverseType(typ->BaseTyp);
    }
  }
}

static void OfrontOPV_Stamp (OfrontOPS_String *s)
{
  SHORTINT i, j, k;
  CHAR n[10];
  OfrontOPS_Name res;
  OfrontOPV_stamp += 1;
  i = 0;
  j = OfrontOPV_stamp;
  while (((*s)->data)[__X(i, (*s)->len[0], (CHAR*)"OfrontOPV", 63505)] != 0x00) {
    res[__X(i, 48, (CHAR*)"OfrontOPV", 63523)] = ((*s)->data)[__X(i, (*s)->len[0], (CHAR*)"OfrontOPV", 63523)];
    i += 1;
  }
  if ((INTEGER)i > 25) {
    i = 25;
  }
  res[__X(i, 48, (CHAR*)"OfrontOPV", 64015)] = '_';
  res[__X((INTEGER)i + 1, 48, (CHAR*)"OfrontOPV", 64032)] = '_';
  i += 2;
  k = 0;
  do {
    n[__X(k, 10, (CHAR*)"OfrontOPV", 64306)] = (CHAR)(__MOD((INTEGER)j, 10) + 48);
    j = (SHORTINT)__DIV((INTEGER)j, 10);
    k += 1;
  } while (!((INTEGER)j == 0));
  do {
    k -= 1;
    res[__X(i, 48, (CHAR*)"OfrontOPV", 64543)] = n[__X(k, 10, (CHAR*)"OfrontOPV", 64543)];
    i += 1;
  } while (!((INTEGER)k == 0));
  res[__X(i, 48, (CHAR*)"OfrontOPV", 64782)] = 0x00;
  if ((*s)->len[0] <= (INTEGER)i) {
    *s = __NEWARR(NIL, 1, 1, 1, 1, (SYSTEM_ARRLEN)((INTEGER)i + 1));
  }
  __STRCOPYCC(res, (*s)->data, __MIN((*s)->len[0], 48), (CHAR*)"OfrontOPV", 65279);
}

static void OfrontOPV_Traverse (OfrontOPT_Object obj, OfrontOPT_Object outerScope, BOOLEAN exported)
{
  SHORTINT mode;
  OfrontOPT_Object scope = NIL;
  OfrontOPT_Object p = NIL;
  if (obj != NIL) {
    OfrontOPV_Traverse(obj->left, outerScope, exported);
    if ((obj->name->data)[0] == '@') {
      (obj->name->data)[0] = '_';
      OfrontOPV_Stamp(&obj->name);
    }
    obj->linkadr = 0;
    mode = obj->mode;
    if ((INTEGER)mode == 5 && ((INTEGER)obj->vis != 0) == exported) {
      OfrontOPV_TraverseType(obj->typ);
    } else if (__IN(mode, 0x16)) {
      OfrontOPV_TraverseType(obj->typ);
    }
    if (!exported) {
      if (__IN(mode, 0x60) && (INTEGER)obj->mnolev > 0) {
        obj->entry = obj->name;
        obj->name = __NEWARR(NIL, 1, 1, 1, 1, (SYSTEM_ARRLEN)(__STRLEN(obj->name->data, obj->name->len[0], (CHAR*)"OfrontOPV", 69182) + 12));
        OfrontOPV_Stamp(&obj->name);
      }
      if (__IN(mode, 0x26)) {
        obj->scope = outerScope;
      } else if (__IN(mode, 0x26c0)) {
        OfrontOPV_TraverseType(obj->typ);
        p = obj->link;
        while (p != NIL) {
          OfrontOPV_TraverseType(p->typ);
          p = p->link;
        }
        scope = obj->scope;
        scope->leaf = 1;
        scope->name = __NEWARR(NIL, 1, 1, 1, 1, (SYSTEM_ARRLEN)(__STRLEN(obj->name->data, obj->name->len[0], (CHAR*)"OfrontOPV", 71721) + 12));
        __STRCOPYCC(obj->name->data, scope->name->data, __MIN(scope->name->len[0], obj->name->len[0]), (CHAR*)"OfrontOPV", 71747);
        OfrontOPV_Stamp(&scope->name);
        if ((INTEGER)mode == 9) {
          obj->adr = 1;
        }
        if ((INTEGER)scope->mnolev > 1) {
          outerScope->leaf = 0;
        }
        OfrontOPV_Traverse(obj->scope->right, obj->scope, 0);
        if ((obj->conval->setval & 0x0a0002) == 0x0) {
          OfrontOPM_Mark(129, obj->adr);
        }
      }
    }
    OfrontOPV_Traverse(obj->right, outerScope, exported);
  }
}

void OfrontOPV_AdrAndSize (OfrontOPT_Object topScope)
{
  OfrontOPM_errpos = topScope->adr;
  topScope->leaf = 1;
  OfrontOPV_Traverse(topScope->right, topScope, 1);
  OfrontOPV_Traverse(topScope->right, topScope, 0);
  OfrontOPT_char8typ->strobj->linkadr = 2;
  OfrontOPT_char16typ->strobj->linkadr = 2;
  OfrontOPT_settyp->strobj->linkadr = 2;
  OfrontOPT_realtyp->strobj->linkadr = 2;
  OfrontOPT_inttyp->strobj->linkadr = 2;
  OfrontOPT_linttyp->strobj->linkadr = 2;
  OfrontOPT_lrltyp->strobj->linkadr = 2;
  OfrontOPT_sinttyp->strobj->linkadr = 2;
  OfrontOPT_booltyp->strobj->linkadr = 2;
  OfrontOPT_bytetyp->strobj->linkadr = 2;
  OfrontOPT_ubytetyp->strobj->linkadr = 2;
  OfrontOPT_sysptrtyp->strobj->linkadr = 2;
  OfrontOPT_anyptrtyp->strobj->linkadr = 2;
  OfrontOPT_anytyp->strobj->linkadr = 2;
}

/*----------------------------------------------------------------------------*/
static SHORTINT OfrontOPV_Precedence (SHORTINT class, SHORTINT subclass, SHORTINT form, SHORTINT comp)
{
  switch (class) {
    case 7: case 0: case 2: case 4: case 9: 
    case 13: 
      return 10;
      break;
    case 5: 
      if (__IN(3, OfrontOPM_opt)) {
        return 10;
      } else {
        return 9;
      }
      break;
    case 1: 
      if (__IN(comp, 0x0c)) {
        return 10;
      } else {
        return 9;
      }
      break;
    case 3: 
      return 9;
      break;
    case 11: 
      switch (subclass) {
        case 35: case 9: case 31: case 39: case 34: 
        case 22: case 40: 
          return 9;
          break;
        case 18: case 23: case 24: case 25: case 33: 
          return 10;
          break;
        default: __CASECHK((CHAR*)"OfrontOPV", 84991);
      }
      break;
    case 12: 
      switch (subclass) {
        case 1: 
          if ((INTEGER)form == 9) {
            return 4;
          } else {
            return 8;
          }
          break;
        case 2: 
          if ((INTEGER)form == 9) {
            return 3;
          } else {
            return 8;
          }
          break;
        case 3: case 4: 
          return 10;
          break;
        case 5: case 6: 
          return 8;
          break;
        case 8: 
          if ((INTEGER)form == 9) {
            return 2;
          } else {
            return 7;
          }
          break;
        case 9: 
          if ((INTEGER)form == 9) {
            return 4;
          } else {
            return 7;
          }
          break;
        case 13: case 14: case 15: case 16: 
          return 6;
          break;
        case 11: case 12: 
          return 5;
          break;
        case 7: 
          return 1;
          break;
        case 10: 
          return 0;
          break;
        case 21: case 17: case 19: case 20: case 33: 
        case 29: case 30: case 26: case 27: case 28: 
        case 36: case 37: 
          return 10;
          break;
        default: __CASECHK((CHAR*)"OfrontOPV", 91391);
      }
      break;
    case 10: 
      return 10;
      break;
    case 8: case 6: 
      return 12;
      break;
    case 29: 
      return 10;
      break;
    default: __CASECHK((CHAR*)"OfrontOPV", 93183);
  }
  __RETCHK((CHAR*)"OfrontOPV", 93183);
}

static void OfrontOPV_Len (OfrontOPT_Node n, INTEGER dim, BOOLEAN incl0x)
{
  INTEGER d;
  OfrontOPT_Struct array = NIL;
  while ((INTEGER)n->class == 4 && (INTEGER)n->typ->comp == 3) {
    dim += 1;
    n = n->left;
  }
  if (__IN(n->typ->form, 0x040400)) {
    if ((INTEGER)n->class == 7) {
      OfrontOPM_WriteInt(n->conval->intval2);
    } else if ((INTEGER)n->class == 3 && (INTEGER)n->left->typ->sysflag == 0) {
      OfrontOPM_WriteString((CHAR*)"__STRLEN", 9);
      if ((INTEGER)n->typ->form == 18) {
        OfrontOPM_Write('L');
      }
      OfrontOPM_Write('(');
      OfrontOPV_expr(n, -1);
      OfrontOPM_WriteString((CHAR*)", ", 3);
      OfrontOPV_Len(n->left, dim, 0);
      OfrontOPM_WriteString((CHAR*)", ", 3);
      OfrontOPM_WriteModPos();
      OfrontOPM_Write(')');
      if (incl0x) {
        OfrontOPM_WriteString((CHAR*)" + 1", 5);
      }
    } else {
      OfrontOPM_WriteString((CHAR*)"__CSTRLEN", 10);
      if ((INTEGER)n->typ->form == 18) {
        OfrontOPM_Write('L');
      }
      OfrontOPM_Write('(');
      OfrontOPV_expr(n, -1);
      OfrontOPM_Write(')');
      if (incl0x) {
        OfrontOPM_WriteString((CHAR*)" + 1", 5);
      }
    }
  } else if ((INTEGER)n->class == 3 && (INTEGER)n->typ->comp == 3) {
    d = dim;
    array = n->typ;
    while (d > 0) {
      array = array->BaseTyp;
      d -= 1;
    }
    if ((INTEGER)array->comp == 3) {
      OfrontOPV_design(n->left, 10);
      OfrontOPM_WriteString((CHAR*)"->len[", 7);
      OfrontOPM_WriteInt(dim);
      OfrontOPM_Write(']');
    } else {
      OfrontOPM_WriteInt(array->n);
      OfrontOPM_PromoteIntConstToLInt();
    }
  } else {
    OfrontOPC_Len(n->obj, n->typ, dim);
  }
}

static BOOLEAN OfrontOPV_SameExp (OfrontOPT_Node n1, OfrontOPT_Node n2)
{
  if ((INTEGER)n2->class == 3 && __IN(n2->typ->form, 0x040400)) {
    n2 = n2->left;
  }
  while ((INTEGER)n1->class == (INTEGER)n2->class && n1->typ == n2->typ) {
    switch (n1->class) {
      case 0: case 1: case 9: 
        return n1->obj == n2->obj;
        break;
      case 7: 
        return __IN(n1->typ->form, 0x72) && n1->conval->intval == n2->conval->intval;
        break;
      case 2: 
        if (n1->obj != n2->obj) {
          return 0;
        }
        break;
      case 3: case 5: 
        break;
      case 4: 
        if (!OfrontOPV_SameExp(n1->right, n2->right)) {
          return 0;
        }
        break;
      case 11: 
        if ((INTEGER)n1->subcl != (INTEGER)n2->subcl || (INTEGER)n1->subcl == 18) {
          return 0;
        }
        break;
      case 12: 
        if ((INTEGER)n1->subcl != (INTEGER)n2->subcl || !OfrontOPV_SameExp(n1->right, n2->right)) {
          return 0;
        }
        break;
      default: 
        return 0;
        break;
    }
    n1 = n1->left;
    n2 = n2->left;
  }
  return 0;
}

static void OfrontOPV_MaxLen (OfrontOPT_Node left, OfrontOPT_Node right)
{
  if (((INTEGER)right->class == 3 && (INTEGER)right->typ->comp != 3) && (INTEGER)right->left->typ->sysflag == 0) {
    right = right->left;
  }
  if (__IN(left->typ->form, 0x040400) || (INTEGER)left->typ->sysflag != 0) {
    OfrontOPV_Len(right, 0, 1);
  } else if ((INTEGER)left->typ->comp == 2 && (INTEGER)right->typ->comp == 2) {
    OfrontOPM_WriteInt(__MIN(left->typ->n, right->typ->n));
  } else if (__IN(right->typ->form, 0x040400) || OfrontOPV_SameExp(left, right)) {
    OfrontOPV_Len(left, 0, 1);
  } else {
    OfrontOPM_WriteString((CHAR*)"__MIN(", 7);
    OfrontOPV_Len(left, 0, 1);
    OfrontOPM_WriteString((CHAR*)", ", 3);
    OfrontOPV_Len(right, 0, 1);
    OfrontOPM_Write(')');
  }
}

static BOOLEAN OfrontOPV_SideEffects (OfrontOPT_Node n)
{
  if (n != NIL) {
    return ((INTEGER)n->class == 13 || OfrontOPV_SideEffects(n->left)) || OfrontOPV_SideEffects(n->right);
  } else {
    return 0;
  }
  __RETCHK((CHAR*)"OfrontOPV", 113151);
}

static void OfrontOPV_Entier (OfrontOPT_Node n, SHORTINT prec)
{
  if (__IN(n->typ->form, 0x0180)) {
    OfrontOPM_WriteString((CHAR*)"__ENTIER(", 10);
    OfrontOPV_expr(n, -1);
    OfrontOPM_Write(')');
  } else {
    OfrontOPV_expr(n, prec);
  }
}

static void OfrontOPV_LEntier (OfrontOPT_Node n, SHORTINT prec)
{
  if (__IN(n->typ->form, 0x0180)) {
    OfrontOPM_WriteString((CHAR*)"__ENTIERL(", 11);
    OfrontOPV_expr(n, -1);
    OfrontOPM_Write(')');
  } else {
    OfrontOPV_expr(n, prec);
  }
}

static void OfrontOPV_Convert (OfrontOPT_Node n, SHORTINT form, SHORTINT prec)
{
  SHORTINT from;
  from = n->typ->form;
  switch (form) {
    case 1: 
      if ((INTEGER)from == 2) {
        OfrontOPM_WriteString((CHAR*)"(BYTE)", 7);
        OfrontOPV_expr(n, 9);
      } else {
        if (__IN(2, OfrontOPM_opt)) {
          OfrontOPM_WriteString((CHAR*)"__SHORT", 8);
          if (OfrontOPV_SideEffects(n)) {
            OfrontOPM_Write('F');
          }
          OfrontOPM_Write('(');
          OfrontOPV_Entier(n, -1);
          OfrontOPM_WriteString((CHAR*)", ", 3);
          OfrontOPM_WriteInt(128);
          OfrontOPM_WriteString((CHAR*)", ", 3);
          OfrontOPM_WriteModPos();
          OfrontOPM_Write(')');
        } else {
          OfrontOPM_WriteString((CHAR*)"(BYTE)", 7);
          OfrontOPV_Entier(n, 9);
        }
      }
      break;
    case 4: 
      if (__IN(2, OfrontOPM_opt)) {
        OfrontOPM_WriteString((CHAR*)"__SHORT", 8);
        if (OfrontOPV_SideEffects(n)) {
          OfrontOPM_Write('F');
        }
        OfrontOPM_Write('(');
        OfrontOPV_Entier(n, -1);
        OfrontOPM_WriteString((CHAR*)", ", 3);
        OfrontOPM_WriteInt(32768);
        OfrontOPM_WriteString((CHAR*)", ", 3);
        OfrontOPM_WriteModPos();
        OfrontOPM_Write(')');
      } else {
        OfrontOPM_WriteString((CHAR*)"(SHORTINT)", 11);
        OfrontOPV_Entier(n, 9);
      }
      break;
    case 5: 
      if ((INTEGER)from < 5 || (INTEGER)from == 9) {
        OfrontOPM_WriteString((CHAR*)"(INTEGER)", 10);
        OfrontOPV_expr(n, 9);
      } else {
        if (__IN(2, OfrontOPM_opt)) {
          OfrontOPM_WriteString((CHAR*)"__SHORT", 8);
          if (OfrontOPV_SideEffects(n)) {
            OfrontOPM_Write('F');
          }
          OfrontOPM_Write('(');
          OfrontOPV_Entier(n, -1);
          OfrontOPM_WriteString((CHAR*)", ", 3);
          OfrontOPM_WriteInt(2147483648LL);
          OfrontOPM_WriteString((CHAR*)", ", 3);
          OfrontOPM_WriteModPos();
          OfrontOPM_Write(')');
        } else {
          OfrontOPM_WriteString((CHAR*)"(INTEGER)", 10);
          OfrontOPV_Entier(n, 9);
        }
      }
      break;
    case 6: 
      if ((INTEGER)from < 6) {
        OfrontOPM_WriteString((CHAR*)"(LONGINT)", 10);
      }
      OfrontOPV_LEntier(n, 9);
      break;
    case 3: case 14: 
      if (__IN(2, OfrontOPM_opt)) {
        OfrontOPM_WriteString((CHAR*)"__CHR", 6);
        if (OfrontOPV_SideEffects(n)) {
          OfrontOPM_Write('F');
        }
        OfrontOPM_Write('(');
        OfrontOPV_Entier(n, -1);
        OfrontOPM_WriteString((CHAR*)", ", 3);
        OfrontOPM_WriteModPos();
        OfrontOPM_Write(')');
      } else {
        OfrontOPM_WriteString((CHAR*)"(CHAR)", 7);
        OfrontOPV_Entier(n, 9);
      }
      break;
    case 17: 
      if (__IN(2, OfrontOPM_opt)) {
        OfrontOPM_WriteString((CHAR*)"__CHR", 6);
        if (OfrontOPV_SideEffects(n)) {
          OfrontOPM_Write('F');
        }
        OfrontOPM_WriteString((CHAR*)"L(", 3);
        OfrontOPV_Entier(n, -1);
        OfrontOPM_WriteString((CHAR*)", ", 3);
        OfrontOPM_WriteModPos();
        OfrontOPM_Write(')');
      } else {
        OfrontOPM_WriteString((CHAR*)"(LONGCHAR)", 11);
        OfrontOPV_Entier(n, 9);
      }
      break;
    case 9: 
      OfrontOPM_WriteString((CHAR*)"(SET)", 6);
      OfrontOPV_Entier(n, 9);
      break;
    case 7: 
      OfrontOPM_WriteString((CHAR*)"(SHORTREAL)", 12);
      OfrontOPV_expr(n, prec);
      break;
    case 8: 
      OfrontOPM_WriteString((CHAR*)"(REAL)", 7);
      OfrontOPV_expr(n, prec);
      break;
    default: 
      OfrontOPV_expr(n, prec);
      break;
  }
}

static void OfrontOPV_TypeOf (OfrontOPT_Node n)
{
  if ((INTEGER)n->typ->form == 13) {
    OfrontOPM_WriteString((CHAR*)"__TYPEOF(", 10);
    OfrontOPV_expr(n, -1);
    OfrontOPM_Write(')');
  } else if (__IN(n->class, 0x15)) {
    OfrontOPC_Andent(n->typ);
    OfrontOPM_WriteString((CHAR*)"__typ", 6);
  } else if ((INTEGER)n->class == 3) {
    OfrontOPM_WriteString((CHAR*)"__TYPEOF(", 10);
    OfrontOPV_expr(n->left, -1);
    OfrontOPM_Write(')');
  } else if ((INTEGER)n->class == 5) {
    OfrontOPV_TypeOf(n->left);
  } else if ((INTEGER)n->class == 11 && (INTEGER)n->subcl == 34) {
    OfrontOPC_TypeOf(n->left->obj);
  } else if ((INTEGER)n->typ->form == 11) {
    OfrontOPM_WriteString((CHAR*)"NIL", 4);
  } else {
    OfrontOPC_TypeOf(n->obj);
  }
}

static void OfrontOPV_Index (OfrontOPT_Node n, OfrontOPT_Node d, SHORTINT prec, SHORTINT dim)
{
  if ((!OfrontOPV_inxchk || ((INTEGER)n->right->class == 7 && (n->right->conval->intval == 0 || (INTEGER)n->left->typ->comp != 3))) || ((INTEGER)n->left->typ->comp == 3 && __ODD(n->left->typ->sysflag))) {
    OfrontOPV_expr(n->right, prec);
  } else {
    if (OfrontOPV_SideEffects(n->right)) {
      OfrontOPM_WriteString((CHAR*)"__XF(", 6);
    } else {
      OfrontOPM_WriteString((CHAR*)"__X(", 5);
    }
    OfrontOPV_expr(n->right, -1);
    OfrontOPM_WriteString((CHAR*)", ", 3);
    OfrontOPV_Len(d, dim, 0);
    OfrontOPM_WriteString((CHAR*)", ", 3);
    OfrontOPM_WriteModPos();
    OfrontOPM_Write(')');
  }
}

static void OfrontOPV_Adr (OfrontOPT_Node n, SHORTINT prec, BOOLEAN cast_adr)
{
  if (__IN(n->typ->form, 0x040400)) {
    OfrontOPV_expr(n, prec);
  } else if (((INTEGER)n->class == 3 && (INTEGER)n->subcl == 0) && !__IN(n->typ->comp, 0x0c)) {
    OfrontOPV_expr(n->left, prec);
  } else if ((INTEGER)n->class == 1 && !__IN(n->typ->comp, 0x0c)) {
    OfrontOPC_CompleteIdent(n->obj);
  } else if (cast_adr) {
    OfrontOPV_design_adr(n, prec, 1);
  } else {
    OfrontOPM_Write('&');
    OfrontOPV_expr(n, prec);
  }
}

static void OfrontOPV_design_adr (OfrontOPT_Node n, SHORTINT prec, BOOLEAN adr)
{
  OfrontOPT_Object obj = NIL;
  OfrontOPT_Struct typ = NIL;
  SHORTINT class, designPrec, comp;
  OfrontOPT_Node d = NIL;
  OfrontOPT_Node x = NIL;
  SHORTINT dims, i, _for__41;
  OfrontOPS_String _ptr__40 = NIL;
  comp = n->typ->comp;
  obj = n->obj;
  class = n->class;
  if (adr && (INTEGER)class != 0) {
    OfrontOPM_Write('&');
  }
  designPrec = OfrontOPV_Precedence(class, n->subcl, n->typ->form, comp);
  if ((((INTEGER)class == 0 && (INTEGER)obj->mnolev > 0) && (INTEGER)obj->mnolev != OfrontOPM_level) && (INTEGER)prec == 10) {
    designPrec = 9;
  }
  if ((INTEGER)prec > (INTEGER)designPrec) {
    OfrontOPM_Write('(');
  }
  if ((INTEGER)prec == 11) {
    OfrontOPM_Write('*');
  }
  switch (class) {
    case 9: 
      OfrontOPC_Ident(n->obj);
      break;
    case 0: 
      if (adr) {
        OfrontOPC_CompleteIdentAdr(n->obj);
      } else {
        OfrontOPC_CompleteIdent(n->obj);
      }
      break;
    case 1: 
      if (!__IN(comp, 0x0c)) {
        OfrontOPM_Write('*');
      }
      OfrontOPC_CompleteIdent(n->obj);
      break;
    case 2: 
      if ((INTEGER)n->left->class == 3) {
        OfrontOPV_expr(n->left->left, designPrec);
        OfrontOPM_WriteString((CHAR*)"->", 3);
      } else {
        OfrontOPV_design(n->left, designPrec);
        OfrontOPM_Write('.');
      }
      OfrontOPC_Ident(n->obj);
      break;
    case 3: 
      if ((INTEGER)n->subcl != 0) {
        OfrontOPV_expr(n->left, designPrec);
      } else {
        if ((INTEGER)n->typ->comp == 3 || (((INTEGER)n->typ->comp == 2 && n->typ->strobj != NIL) && n->typ->strobj->linkadr == 5)) {
          if ((INTEGER)n->typ->sysflag != 0) {
            OfrontOPV_design(n->left, designPrec);
          } else {
            OfrontOPV_design(n->left, 10);
            OfrontOPM_WriteString((CHAR*)"->data", 7);
          }
        } else {
          OfrontOPM_Write('*');
          OfrontOPV_expr(n->left, designPrec);
        }
      }
      break;
    case 4: 
      d = n->left;
      if ((INTEGER)d->typ->comp == 3) {
        dims = 0;
        while ((INTEGER)d->class == 4) {
          d = d->left;
          dims += 1;
        }
        if ((INTEGER)n->typ->comp == 3) {
          OfrontOPV_Adr(d, designPrec, 0);
        } else {
          OfrontOPV_design(d, designPrec);
        }
        OfrontOPM_Write('[');
        if ((INTEGER)n->typ->comp == 3) {
          OfrontOPM_Write('(');
        }
        i = dims;
        x = n;
        while (x != d) {
          if (x->left != d) {
            OfrontOPV_Index(x, d, 7, i);
            OfrontOPM_WriteString((CHAR*)" + ", 4);
            OfrontOPV_Len(d, i, 0);
            OfrontOPM_WriteString((CHAR*)" * (", 5);
            i -= 1;
          } else {
            OfrontOPV_Index(x, d, -1, i);
          }
          x = x->left;
        }
        _for__41 = dims;
        i = 1;
        while ((INTEGER)i <= (INTEGER)_for__41) {
          OfrontOPM_Write(')');
          i += 1;
        }
        if ((INTEGER)n->typ->comp == 3) {
          OfrontOPM_Write(')');
          while ((INTEGER)i <= d->typ->n) {
            OfrontOPM_WriteString((CHAR*)" * ", 4);
            OfrontOPV_Len(d, i, 0);
            i += 1;
          }
        }
        OfrontOPM_Write(']');
      } else {
        OfrontOPV_design(n->left, designPrec);
        OfrontOPM_Write('[');
        OfrontOPV_Index(n, n->left, -1, 0);
        OfrontOPM_Write(']');
      }
      break;
    case 5: 
      typ = n->typ;
      obj = n->left->obj;
      if (__IN(3, OfrontOPM_opt)) {
        if ((INTEGER)typ->comp == 4) {
          OfrontOPM_WriteString((CHAR*)"__GUARDR(", 10);
          if ((INTEGER)obj->mnolev != OfrontOPM_level) {
            _ptr__40 = obj->scope->name;
            OfrontOPM_WriteString((void*)_ptr__40->data, _ptr__40->len[0]);
            OfrontOPM_WriteString((CHAR*)"__curr->", 9);
            OfrontOPC_Ident(obj);
          } else {
            OfrontOPC_Ident(obj);
          }
        } else {
          if (typ->BaseTyp->strobj == NIL) {
            OfrontOPM_WriteString((CHAR*)"__GUARDA(", 10);
          } else {
            OfrontOPM_WriteString((CHAR*)"__GUARDP(", 10);
          }
          OfrontOPV_expr(n->left, -1);
          typ = typ->BaseTyp;
        }
        OfrontOPM_WriteString((CHAR*)", ", 3);
        OfrontOPC_Andent(typ);
        OfrontOPM_WriteString((CHAR*)", ", 3);
        OfrontOPM_WriteInt(typ->extlev);
        OfrontOPM_Write(')');
      } else {
        if ((INTEGER)typ->comp == 4) {
          OfrontOPM_WriteString((CHAR*)"*(", 3);
          OfrontOPC_Ident(typ->strobj);
          OfrontOPM_WriteString((CHAR*)"*)", 3);
          OfrontOPC_CompleteIdent(obj);
        } else {
          OfrontOPM_Write('(');
          OfrontOPC_Ident(typ->strobj);
          OfrontOPM_Write(')');
          OfrontOPV_expr(n->left, designPrec);
        }
      }
      break;
    case 6: 
      if (__IN(3, OfrontOPM_opt)) {
        if ((INTEGER)n->left->class == 1) {
          OfrontOPM_WriteString((CHAR*)"__GUARDEQR(", 12);
          OfrontOPC_CompleteIdent(n->left->obj);
          OfrontOPM_WriteString((CHAR*)", ", 3);
          OfrontOPV_TypeOf(n->left);
        } else {
          OfrontOPM_WriteString((CHAR*)"__GUARDEQP(", 12);
          OfrontOPV_expr(n->left->left, -1);
        }
        OfrontOPM_WriteString((CHAR*)", ", 3);
        OfrontOPC_Ident(n->left->typ->strobj);
        OfrontOPM_Write(')');
      } else {
        OfrontOPV_expr(n->left, -1);
      }
      break;
    case 11: 
      if ((INTEGER)n->subcl == 34) {
        OfrontOPV_design(n->left, prec);
      }
      break;
    case 13: 
      OfrontOPV_expr(n, -1);
      break;
    default: __CASECHK((CHAR*)"OfrontOPV", 169471);
  }
  if ((INTEGER)prec > (INTEGER)designPrec) {
    OfrontOPM_Write(')');
  }
}

static void OfrontOPV_design (OfrontOPT_Node n, SHORTINT prec)
{
  OfrontOPV_design_adr(n, prec, 0);
}

static void OfrontOPV_ActualPar (OfrontOPT_Node n, OfrontOPT_Object fp)
{
  OfrontOPT_Struct typ = NIL;
  OfrontOPT_Struct aptyp = NIL;
  SHORTINT comp, form, mode, prec, dim;
  BOOLEAN useAdr;
  OfrontOPT_Node n1 = NIL;
  OfrontOPM_Write('(');
  while (n != NIL) {
    typ = fp->typ;
    if ((INTEGER)typ->form == (INTEGER)n->typ->form && __IN(typ->form, 0x0243fe)) {
      typ = n->typ;
    }
    comp = typ->comp;
    form = typ->form;
    mode = fp->mode;
    prec = -1;
    if ((INTEGER)mode == 2 && n->typ == OfrontOPT_niltyp) {
      OfrontOPM_WriteString((CHAR*)"NIL", 4);
    } else if ((INTEGER)mode == 2 && ((INTEGER)n->subcl == 41 || (INTEGER)n->subcl == 40)) {
      OfrontOPM_WriteString((CHAR*)"(void*)", 8);
      OfrontOPV_expr(n->left, -1);
      OfrontOPM_WriteString((CHAR*)", ", 3);
      if ((INTEGER)n->subcl == 40) {
        OfrontOPM_WriteString((CHAR*)"(void*)", 8);
      }
      OfrontOPV_expr(n->right, -1);
    } else {
      useAdr = 0;
      if (((INTEGER)mode == 2 && (INTEGER)n->class == 11) && (INTEGER)n->subcl == 34) {
        OfrontOPM_Write('(');
        OfrontOPC_Ident(n->typ->strobj);
        OfrontOPM_WriteString((CHAR*)"*)", 3);
        prec = 10;
      }
      if (!__IN(n->typ->comp, 0x0c)) {
        if ((INTEGER)mode == 2) {
          if ((OfrontOPV_ansi && typ != n->typ) && (INTEGER)n->class != 7) {
            OfrontOPM_WriteString((CHAR*)"(void*)", 8);
          }
          useAdr = 1;
          prec = 9;
        } else if (OfrontOPV_ansi) {
          if ((((INTEGER)form == 13 && typ != n->typ) && n->typ != OfrontOPT_niltyp) && (INTEGER)n->class != 7) {
            OfrontOPM_WriteString((CHAR*)"(void*)", 8);
          } else if ((INTEGER)comp == 4 && n->typ != typ) {
            OfrontOPM_WriteString((CHAR*)"*(", 3);
            OfrontOPC_Andent(typ);
            OfrontOPM_WriteString((CHAR*)"*)&", 4);
            prec = 9;
          }
        } else {
          if (__IN(form, 0x0180) && __IN(n->typ->form, 0x4072)) {
            OfrontOPM_WriteString((CHAR*)"(REAL)", 7);
            prec = 9;
          } else if ((INTEGER)form == 6 && (INTEGER)n->typ->form < 6) {
            OfrontOPM_WriteString((CHAR*)"(LONGINT)", 10);
            prec = 9;
          }
        }
      } else if (OfrontOPV_ansi) {
        if ((((INTEGER)mode == 2 || (INTEGER)typ->BaseTyp->form == 16) && typ != n->typ) && (INTEGER)prec == -1) {
          OfrontOPM_WriteString((CHAR*)"(void*)", 8);
        }
      }
      n1 = n;
      if (((INTEGER)mode == 2 && (INTEGER)n->class == 11) && (INTEGER)n->subcl == 34) {
        n1 = n->left;
      }
      if (useAdr) {
        OfrontOPV_Adr(n1, prec, 1);
      } else {
        OfrontOPV_expr(n1, prec);
      }
      if ((((INTEGER)form == 6 && (INTEGER)n->class == 7) && n->conval->intval <= 2147483647) && n->conval->intval >= (-2147483647-1)) {
        OfrontOPM_PromoteIntConstToLInt();
      } else if ((INTEGER)comp == 4 && (INTEGER)mode == 2) {
        if (__MASK((INTEGER)typ->sysflag, -256) == 0) {
          OfrontOPM_WriteString((CHAR*)", ", 3);
          OfrontOPV_TypeOf(n);
        }
      } else if ((INTEGER)comp == 3 && !__ODD(typ->sysflag)) {
        if (__ODD(n->typ->sysflag) && (INTEGER)n->typ->comp != 2) {
          OfrontOPM_err(137);
        }
        if ((INTEGER)n->class == 7) {
          OfrontOPM_WriteString((CHAR*)", ", 3);
          if ((INTEGER)OfrontOPM_IndexSize > 4) {
            OfrontOPM_WriteString((CHAR*)"(LONGINT)", 10);
          }
          OfrontOPM_WriteInt(n->conval->intval2);
        } else {
          aptyp = n->typ;
          dim = 0;
          while ((INTEGER)typ->comp == 3 && (INTEGER)typ->BaseTyp->form != 1) {
            OfrontOPM_WriteString((CHAR*)", ", 3);
            OfrontOPV_Len(n, dim, 1);
            typ = typ->BaseTyp;
            aptyp = aptyp->BaseTyp;
            dim += 1;
          }
          if ((INTEGER)typ->comp == 3 && (INTEGER)typ->BaseTyp->form == 1) {
            OfrontOPM_WriteString((CHAR*)", ", 3);
            while ((INTEGER)aptyp->comp == 3) {
              OfrontOPV_Len(n, dim, 0);
              OfrontOPM_WriteString((CHAR*)" * ", 4);
              dim += 1;
              aptyp = aptyp->BaseTyp;
            }
            OfrontOPM_WriteInt(aptyp->size);
            OfrontOPM_PromoteIntConstToLInt();
          }
        }
      }
    }
    n = n->link;
    fp = fp->link;
    if (n != NIL) {
      OfrontOPM_WriteString((CHAR*)", ", 3);
    }
  }
  OfrontOPM_Write(')');
}

static OfrontOPT_Object OfrontOPV_SuperProc (OfrontOPT_Node n)
{
  OfrontOPT_Object obj = NIL;
  OfrontOPT_Struct typ = NIL;
  OfrontOPS_String _ptr__32 = NIL;
  typ = n->right->typ;
  if ((INTEGER)typ->form == 13) {
    typ = typ->BaseTyp;
  }
  _ptr__32 = n->left->obj->name;
  OfrontOPT_FindBaseField((void*)_ptr__32->data, _ptr__32->len[0], typ, &obj);
  return obj;
}

static void OfrontOPV_StringModifier (OfrontOPT_Node n)
{
  BOOLEAN trunc;
  trunc = 0;
  while ((INTEGER)n->class == 11 && (INTEGER)n->subcl == 22) {
    if ((INTEGER)n->typ->form == 10) {
      trunc = 1;
    }
    n = n->left;
  }
  if ((INTEGER)n->typ->form == 10 || ((INTEGER)n->typ->form == 16 && (INTEGER)n->typ->BaseTyp->form == 3)) {
    OfrontOPM_Write('C');
  } else if (trunc) {
    OfrontOPM_Write('T');
  } else {
    OfrontOPM_Write('L');
  }
}

static BOOLEAN OfrontOPV_OpParentheses (SHORTINT ePrec, SHORTINT prec)
{
  return ((INTEGER)ePrec == 4 && (INTEGER)prec == 2) || ((INTEGER)ePrec == 1 && (INTEGER)prec == 0);
}

static void OfrontOPV_expr_val (OfrontOPT_Node n, SHORTINT prec, BOOLEAN lvalue)
{
  SHORTINT class, subclass, form, exprPrec;
  OfrontOPT_Struct typ = NIL;
  OfrontOPT_Node l = NIL;
  OfrontOPT_Node r = NIL;
  OfrontOPT_Object proc = NIL;
  class = n->class;
  subclass = n->subcl;
  form = n->typ->form;
  l = n->left;
  r = n->right;
  exprPrec = OfrontOPV_Precedence(class, subclass, form, n->typ->comp);
  if (((INTEGER)exprPrec <= (INTEGER)prec || OfrontOPV_OpParentheses(exprPrec, prec)) && __IN(class, 0x3ce0)) {
    OfrontOPM_Write('(');
  }
  switch (class) {
    case 7: 
      OfrontOPC_Constant(n->conval, form);
      break;
    case 10: 
      OfrontOPM_WriteString((CHAR*)"__SETRNG(", 10);
      OfrontOPV_expr(l, -1);
      OfrontOPM_WriteString((CHAR*)", ", 3);
      OfrontOPV_expr(r, -1);
      OfrontOPM_Write(')');
      break;
    case 11: 
      switch (subclass) {
        case 35: 
          OfrontOPM_Write('!');
          OfrontOPV_expr(l, exprPrec);
          break;
        case 9: 
          if ((INTEGER)form == 9) {
            OfrontOPM_Write('~');
          } else {
            OfrontOPM_Write('-');
          }
          OfrontOPV_expr(l, exprPrec);
          break;
        case 18: 
          typ = n->obj->typ;
          if ((INTEGER)l->typ->comp == 4) {
            OfrontOPM_WriteString((CHAR*)"__IS(", 6);
            OfrontOPC_TypeOf(l->obj);
          } else {
            OfrontOPM_WriteString((CHAR*)"__ISP(", 7);
            OfrontOPV_expr(l, -1);
            typ = typ->BaseTyp;
          }
          OfrontOPM_WriteString((CHAR*)", ", 3);
          OfrontOPC_Andent(typ);
          OfrontOPM_WriteString((CHAR*)", ", 3);
          OfrontOPM_WriteInt(typ->extlev);
          OfrontOPM_Write(')');
          break;
        case 22: 
          if (__IN(form, 0x040400)) {
            OfrontOPV_expr(l, exprPrec);
          } else {
            OfrontOPV_Convert(l, form, exprPrec);
          }
          break;
        case 23: 
          if (OfrontOPV_SideEffects(l)) {
            if ((INTEGER)l->typ->form == 8) {
              OfrontOPM_WriteString((CHAR*)"__ABSFD(", 9);
            } else if ((INTEGER)l->typ->form == 7) {
              OfrontOPM_WriteString((CHAR*)"__ABSFF(", 9);
            } else if ((INTEGER)l->typ->form == 6) {
              OfrontOPM_WriteString((CHAR*)"__ABSFL(", 9);
            } else if ((INTEGER)l->typ->form < 5 && (INTEGER)OfrontOPM_AdrSize == 2) {
              OfrontOPM_WriteString((CHAR*)"__ABSFS(", 9);
            } else {
              OfrontOPM_WriteString((CHAR*)"__ABSF(", 8);
            }
          } else {
            OfrontOPM_WriteString((CHAR*)"__ABS(", 7);
          }
          OfrontOPV_expr(l, -1);
          OfrontOPM_Write(')');
          break;
        case 24: 
          OfrontOPM_WriteString((CHAR*)"__CAP(", 7);
          OfrontOPV_expr(l, -1);
          OfrontOPM_Write(')');
          break;
        case 25: 
          OfrontOPM_WriteString((CHAR*)"__ODD(", 7);
          OfrontOPV_expr(l, -1);
          OfrontOPM_Write(')');
          break;
        case 39: 
          OfrontOPM_WriteString((CHAR*)"(void*)", 8);
          OfrontOPV_TypeOf(l);
          break;
        case 31: 
          if (!OfrontOPV_oldc) {
            OfrontOPM_WriteString((CHAR*)"(SYSTEM_ADRINT)", 16);
          }
          if ((INTEGER)l->class == 8) {
            OfrontOPV_TypeOf(l);
          } else if ((INTEGER)l->class == 1) {
            OfrontOPC_CompleteIdent(l->obj);
          } else {
            if (!__IN(l->typ->form, 0x040400) && !__IN(l->typ->comp, 0x0c)) {
              OfrontOPV_Adr(l, exprPrec, 1);
            } else {
              OfrontOPV_expr(l, exprPrec);
            }
          }
          break;
        case 34: 
          if ((!lvalue && !__IN(n->typ->form, 0x010180)) && !__IN(l->typ->form, 0x010180)) {
            OfrontOPM_Write('(');
            OfrontOPC_Ident(n->typ->strobj);
            OfrontOPM_Write(')');
            OfrontOPV_expr(l, exprPrec);
          } else if (__IN(l->class, 0x17)) {
            OfrontOPM_WriteString((CHAR*)"__VAL(", 7);
            OfrontOPC_Ident(n->typ->strobj);
            OfrontOPM_WriteString((CHAR*)", ", 3);
            OfrontOPV_expr(l, -1);
            OfrontOPM_Write(')');
          } else {
            if ((INTEGER)n->typ->form == 7) {
              OfrontOPM_WriteString((CHAR*)"__VALSR((INTEGER)", 18);
            } else if ((INTEGER)n->typ->form == 8) {
              OfrontOPM_WriteString((CHAR*)"__VALR((LONGINT)", 17);
            } else {
              OfrontOPM_Write('(');
              OfrontOPC_Ident(n->typ->strobj);
              OfrontOPM_Write(')');
            }
            if ((INTEGER)l->typ->form == 7) {
              OfrontOPM_WriteString((CHAR*)"__VALI(", 8);
              OfrontOPV_expr(l, -1);
              OfrontOPM_Write(')');
            } else if ((INTEGER)l->typ->form == 8) {
              OfrontOPM_WriteString((CHAR*)"__VALL(", 8);
              OfrontOPV_expr(l, -1);
              OfrontOPM_Write(')');
            } else {
              OfrontOPV_expr(l, exprPrec);
            }
            if (__IN(n->typ->form, 0x0180)) {
              OfrontOPM_Write(')');
            }
          }
          break;
        case 33: 
          OfrontOPM_WriteString((CHAR*)"__SETOF(", 9);
          OfrontOPV_expr(l, -1);
          OfrontOPM_Write(')');
          break;
        case 40: 
          switch (form) {
            case 1: 
              OfrontOPM_WriteString((CHAR*)"(__U_BYTE)", 11);
              break;
            case 4: 
              OfrontOPM_WriteString((CHAR*)"(__U_SHORTINT)", 15);
              break;
            case 5: 
              OfrontOPM_WriteString((CHAR*)"(__U_INTEGER)", 14);
              break;
            default: 
              OfrontOPM_WriteString((CHAR*)"(__U_LONGINT)", 14);
              break;
          }
          OfrontOPM_Write('(');
          OfrontOPV_expr(l, -1);
          OfrontOPM_Write(')');
          break;
        default: 
          OfrontOPM_err(200);
          break;
      }
      break;
    case 12: 
      switch (subclass) {
        case 21: 
          OfrontOPV_Len(l, (INTEGER)r->conval->intval, 0);
          break;
        case 17: case 19: case 20: case 33: case 29: 
        case 30: case 3: case 4: case 26: case 27: 
        case 28: case 36: case 37: 
          switch (subclass) {
            case 17: 
              OfrontOPM_WriteString((CHAR*)"__IN(", 6);
              break;
            case 19: 
              if ((INTEGER)r->class == 7) {
                if (r->conval->intval >= 0) {
                  OfrontOPM_WriteString((CHAR*)"__ASHL(", 8);
                } else {
                  OfrontOPM_WriteString((CHAR*)"__ASHR(", 8);
                }
              } else if (!OfrontOPV_SideEffects(r)) {
                OfrontOPM_WriteString((CHAR*)"__ASH(", 7);
              } else if ((INTEGER)form == 6) {
                OfrontOPM_WriteString((CHAR*)"__ASHFL(", 9);
              } else {
                OfrontOPM_WriteString((CHAR*)"__ASHF(", 8);
              }
              break;
            case 26: 
              OfrontOPM_WriteString((CHAR*)"__ASHR(", 8);
              break;
            case 27: 
              OfrontOPM_WriteString((CHAR*)"__LSHL(", 8);
              break;
            case 28: 
              OfrontOPM_WriteString((CHAR*)"__ROTR(", 8);
              break;
            case 20: 
              OfrontOPM_WriteString((CHAR*)"__MASK(", 8);
              break;
            case 33: 
              OfrontOPM_WriteString((CHAR*)"__BIT(", 7);
              break;
            case 29: 
              if ((INTEGER)r->class == 7) {
                if (r->conval->intval >= 0) {
                  OfrontOPM_WriteString((CHAR*)"__LSHL(", 8);
                } else {
                  OfrontOPM_WriteString((CHAR*)"__LSHR(", 8);
                }
              } else {
                OfrontOPM_WriteString((CHAR*)"__LSH(", 7);
              }
              break;
            case 30: 
              if ((INTEGER)r->class == 7) {
                if (r->conval->intval >= 0) {
                  OfrontOPM_WriteString((CHAR*)"__ROTL(", 8);
                } else {
                  OfrontOPM_WriteString((CHAR*)"__ROTR(", 8);
                }
              } else {
                OfrontOPM_WriteString((CHAR*)"__ROT(", 7);
              }
              break;
            case 3: 
              if ((!OfrontOPV_SideEffects(n) && (INTEGER)r->class == 7) && r->conval->intval > 0) {
                OfrontOPM_WriteString((CHAR*)"__DIV(", 7);
              } else if ((INTEGER)form < 5 && (INTEGER)OfrontOPM_AdrSize == 2) {
                OfrontOPM_WriteString((CHAR*)"__DIVFS(", 9);
              } else if ((INTEGER)form == 6) {
                OfrontOPM_WriteString((CHAR*)"__DIVFL(", 9);
              } else {
                OfrontOPM_WriteString((CHAR*)"__DIVF(", 8);
              }
              break;
            case 4: 
              if ((!OfrontOPV_SideEffects(n) && (INTEGER)r->class == 7) && r->conval->intval > 0) {
                OfrontOPM_WriteString((CHAR*)"__MOD(", 7);
              } else if ((INTEGER)form < 5 && (INTEGER)OfrontOPM_AdrSize == 2) {
                OfrontOPM_WriteString((CHAR*)"__MODFS(", 9);
              } else if ((INTEGER)form == 6) {
                OfrontOPM_WriteString((CHAR*)"__MODFL(", 9);
              } else {
                OfrontOPM_WriteString((CHAR*)"__MODF(", 8);
              }
              break;
            case 36: 
              if (!OfrontOPV_SideEffects(n)) {
                OfrontOPM_WriteString((CHAR*)"__MIN(", 7);
              } else if ((INTEGER)form == 7) {
                OfrontOPM_WriteString((CHAR*)"__MINFF(", 9);
              } else if ((INTEGER)form == 8) {
                OfrontOPM_WriteString((CHAR*)"__MINFD(", 9);
              } else if ((INTEGER)form == 6) {
                OfrontOPM_WriteString((CHAR*)"__MINFL(", 9);
              } else if ((INTEGER)form < 5 && (INTEGER)OfrontOPM_AdrSize == 2) {
                OfrontOPM_WriteString((CHAR*)"__MINFS(", 9);
              } else {
                OfrontOPM_WriteString((CHAR*)"__MINF(", 8);
              }
              break;
            case 37: 
              if (!OfrontOPV_SideEffects(n)) {
                OfrontOPM_WriteString((CHAR*)"__MAX(", 7);
              } else if ((INTEGER)form == 7) {
                OfrontOPM_WriteString((CHAR*)"__MAXFF(", 9);
              } else if ((INTEGER)form == 8) {
                OfrontOPM_WriteString((CHAR*)"__MAXFD(", 9);
              } else if ((INTEGER)form == 6) {
                OfrontOPM_WriteString((CHAR*)"__MAXFL(", 9);
              } else if ((INTEGER)form < 5 && (INTEGER)OfrontOPM_AdrSize == 2) {
                OfrontOPM_WriteString((CHAR*)"__MAXFS(", 9);
              } else {
                OfrontOPM_WriteString((CHAR*)"__MAXF(", 8);
              }
              break;
            default: __CASECHK((CHAR*)"OfrontOPV", 243711);
          }
          OfrontOPV_expr(l, -1);
          OfrontOPM_WriteString((CHAR*)", ", 3);
          if ((__IN(subclass, 0x60080000) && (INTEGER)r->class == 7) && r->conval->intval < 0) {
            OfrontOPM_WriteInt(-r->conval->intval);
          } else {
            OfrontOPV_expr(r, -1);
          }
          if (__IN(subclass, 0x7c080000)) {
            OfrontOPM_WriteString((CHAR*)", ", 3);
            OfrontOPC_Ident(l->typ->strobj);
          }
          OfrontOPM_Write(')');
          break;
        case 11: case 12: case 13: case 14: case 15: 
        case 16: 
          if (__IN(l->typ->form, 0x050400)) {
            OfrontOPM_WriteString((CHAR*)"__STRCMP", 9);
            if ((INTEGER)r->class == 11 && (INTEGER)r->subcl == 22) {
              OfrontOPV_StringModifier(r);
              OfrontOPV_StringModifier(l);
              OfrontOPM_Write('(');
              OfrontOPV_expr(r, -1);
              OfrontOPM_WriteString((CHAR*)", ", 3);
              OfrontOPV_expr(l, -1);
              if ((INTEGER)subclass >= 13) {
                subclass = (SHORTINT)(__MASK((INTEGER)subclass - 15, -4) + 13);
              }
            } else {
              OfrontOPV_StringModifier(l);
              OfrontOPV_StringModifier(r);
              OfrontOPM_Write('(');
              OfrontOPV_expr(l, -1);
              OfrontOPM_WriteString((CHAR*)", ", 3);
              OfrontOPV_expr(r, -1);
            }
            OfrontOPM_WriteString((CHAR*)", ", 3);
            OfrontOPV_MaxLen(l, r);
            OfrontOPM_WriteString((CHAR*)", ", 3);
            OfrontOPM_WriteModPos();
            OfrontOPM_Write(')');
            OfrontOPC_Cmp(subclass);
            OfrontOPM_Write('0');
          } else {
            OfrontOPV_expr(l, exprPrec);
            OfrontOPC_Cmp(subclass);
            typ = l->typ;
            if ((((INTEGER)typ->form == 13 && (INTEGER)r->typ->form != 11) && r->typ != typ) && r->typ != OfrontOPT_sysptrtyp) {
              OfrontOPM_WriteString((CHAR*)"(void *) ", 10);
            }
            OfrontOPV_expr(r, exprPrec);
          }
          break;
        default: 
          OfrontOPV_expr(l, exprPrec);
          switch (subclass) {
            case 1: 
              if ((INTEGER)form == 9) {
                OfrontOPM_WriteString((CHAR*)" & ", 4);
              } else {
                OfrontOPM_WriteString((CHAR*)" * ", 4);
              }
              break;
            case 2: 
              if ((INTEGER)form == 9) {
                OfrontOPM_WriteString((CHAR*)" ^ ", 4);
              } else {
                OfrontOPM_WriteString((CHAR*)" / ", 4);
                if (r->obj == NIL || __IN(r->obj->typ->form, 0x4072)) {
                  OfrontOPM_Write('(');
                  OfrontOPC_Ident(n->typ->strobj);
                  OfrontOPM_Write(')');
                }
              }
              break;
            case 7: 
              OfrontOPM_WriteString((CHAR*)" && ", 5);
              break;
            case 8: 
              if (__IN(form, 0x040400)) {
                OfrontOPM_err(265);
              } else if ((INTEGER)form == 9) {
                OfrontOPM_WriteString((CHAR*)" | ", 4);
              } else {
                OfrontOPM_WriteString((CHAR*)" + ", 4);
              }
              break;
            case 9: 
              if ((INTEGER)form == 9) {
                OfrontOPM_WriteString((CHAR*)" & ~", 5);
              } else {
                OfrontOPM_WriteString((CHAR*)" - ", 4);
              }
              break;
            case 5: 
              OfrontOPM_WriteString((CHAR*)" / ", 4);
              break;
            case 6: 
              OfrontOPM_WriteString((CHAR*)" % ", 4);
              break;
            case 10: 
              OfrontOPM_WriteString((CHAR*)" || ", 5);
              break;
            default: __CASECHK((CHAR*)"OfrontOPV", 260095);
          }
          OfrontOPV_expr(r, exprPrec);
          break;
      }
      break;
    case 13: 
      if (l->obj != NIL && (INTEGER)l->obj->mode == 13) {
        if ((INTEGER)l->subcl == 1) {
          proc = OfrontOPV_SuperProc(n);
        } else {
          OfrontOPM_WriteString((CHAR*)"__", 3);
          proc = OfrontOPC_BaseTProc(l->obj);
        }
        OfrontOPC_Ident(proc);
        n->obj = proc->link;
      } else if ((INTEGER)l->class == 9) {
        OfrontOPV_design(l, 10);
      } else {
        OfrontOPV_design(l, 11);
      }
      OfrontOPV_ActualPar(r, n->obj);
      break;
    case 29: 
      OfrontOPM_Write('(');
      OfrontOPV_compStat(l, 1);
      OfrontOPV_expr(r, -1);
      OfrontOPM_Write(')');
      break;
    default: 
      OfrontOPV_design(n, prec);
      break;
  }
  if (((INTEGER)exprPrec <= (INTEGER)prec || OfrontOPV_OpParentheses(exprPrec, prec)) && __IN(class, 0x3ca0)) {
    OfrontOPM_Write(')');
  }
}

static void OfrontOPV_expr (OfrontOPT_Node n, SHORTINT prec)
{
  OfrontOPV_expr_val(n, prec, 0);
}

static void OfrontOPV_IfStat (OfrontOPT_Node n, BOOLEAN withtrap, OfrontOPT_Object outerProc)
{
  OfrontOPT_Node if_ = NIL;
  OfrontOPT_Object obj = NIL;
  OfrontOPT_Struct typ = NIL;
  INTEGER adr;
  OfrontOPS_String _ptr__14 = NIL;
  if_ = n->left;
  while (if_ != NIL) {
    OfrontOPM_WriteString((CHAR*)"if ", 4);
    OfrontOPV_expr(if_->left, 12);
    OfrontOPM_Write(' ');
    OfrontOPC_BegBlk();
    if ((INTEGER)n->class == 27 && if_->left->left != NIL) {
      obj = if_->left->left->obj;
      typ = obj->typ;
      adr = obj->adr;
      if ((INTEGER)typ->comp == 4) {
        OfrontOPC_BegStat();
        OfrontOPC_Ident(if_->left->obj->typ->strobj);
        OfrontOPM_WriteString((CHAR*)" *", 3);
        _ptr__14 = obj->name;
        OfrontOPM_WriteString((void*)_ptr__14->data, _ptr__14->len[0]);
        OfrontOPM_WriteString((CHAR*)"__ = (void*)", 13);
        obj->adr = 0;
        OfrontOPC_CompleteIdent(obj);
        OfrontOPC_EndStat();
      }
      obj->adr = 1;
      obj->typ = if_->left->obj->typ;
      OfrontOPV_stat(if_->right, outerProc);
      obj->typ = typ;
      obj->adr = adr;
    } else {
      OfrontOPV_stat(if_->right, outerProc);
    }
    if_ = if_->link;
    if ((if_ != NIL || n->right != NIL) || withtrap) {
      OfrontOPC_EndBlk0();
      OfrontOPM_WriteString((CHAR*)" else ", 7);
    } else {
      OfrontOPC_EndBlk();
    }
  }
  if (withtrap) {
    OfrontOPM_WriteString((CHAR*)"__WITHCHK(", 11);
    OfrontOPM_WriteModPos();
    OfrontOPM_Write(')');
    OfrontOPC_EndStat();
  } else if (n->right != NIL) {
    OfrontOPC_BegBlk();
    OfrontOPV_stat(n->right, outerProc);
    OfrontOPC_EndBlk();
  }
}

static void OfrontOPV_CaseStat (OfrontOPT_Node n, OfrontOPT_Object outerProc)
{
  OfrontOPT_Node switchCase = NIL;
  OfrontOPT_Node label = NIL;
  INTEGER low, high;
  SHORTINT form, i;
  OfrontOPM_WriteString((CHAR*)"switch ", 8);
  OfrontOPV_expr(n->left, 12);
  OfrontOPM_Write(' ');
  OfrontOPC_BegBlk();
  form = n->left->typ->form;
  switchCase = n->right->left;
  while (switchCase != NIL) {
    label = switchCase->left;
    i = 0;
    while (label != NIL) {
      low = (INTEGER)label->conval->intval;
      high = label->conval->intval2;
      while (low <= high) {
        if ((INTEGER)i == 0) {
          OfrontOPC_BegStat();
        }
        OfrontOPC_Case(low, form);
        low += 1;
        i += 1;
        if ((INTEGER)i == 5) {
          OfrontOPM_WriteLn();
          i = 0;
        }
      }
      label = label->link;
    }
    if ((INTEGER)i > 0) {
      OfrontOPM_WriteLn();
    }
    OfrontOPC_Indent(1);
    OfrontOPV_stat(switchCase->right, outerProc);
    OfrontOPC_BegStat();
    OfrontOPM_WriteString((CHAR*)"break", 6);
    OfrontOPC_EndStat();
    OfrontOPC_Indent(-1);
    switchCase = switchCase->link;
  }
  if (OfrontOPM_Lang != '7') {
    OfrontOPC_BegStat();
    OfrontOPM_WriteString((CHAR*)"default: ", 10);
    if (n->right->conval->setval != 0x0) {
      OfrontOPC_Indent(1);
      OfrontOPM_WriteLn();
      OfrontOPV_stat(n->right->right, outerProc);
      OfrontOPC_BegStat();
      OfrontOPM_WriteString((CHAR*)"break", 6);
      OfrontOPC_Indent(-1);
    } else {
      OfrontOPM_WriteString((CHAR*)"__CASECHK(", 11);
      OfrontOPM_WriteModPos();
      OfrontOPM_Write(')');
    }
    OfrontOPC_EndStat();
  }
  OfrontOPC_EndBlk();
}

static BOOLEAN OfrontOPV_ImplicitReturn (OfrontOPT_Node n)
{
  while (n != NIL && (INTEGER)n->class != 26) {
    n = n->link;
  }
  return n == NIL;
}

static void OfrontOPV_NewArr (OfrontOPT_Node d, OfrontOPT_Node x)
{
  OfrontOPT_Struct typ = NIL;
  OfrontOPT_Struct base = NIL;
  SHORTINT nofdim, nofdyn;
  typ = d->typ->BaseTyp;
  base = typ;
  nofdim = 0;
  nofdyn = 0;
  while ((INTEGER)base->comp == 3) {
    nofdim += 1;
    nofdyn += 1;
    base = base->BaseTyp;
  }
  OfrontOPV_design(d, -1);
  OfrontOPM_WriteString((CHAR*)" = __NEWARR(", 13);
  while ((INTEGER)base->comp == 2) {
    nofdim += 1;
    base = base->BaseTyp;
  }
  if ((INTEGER)base->comp == 4 && OfrontOPC_NofPtrs(base) != 0) {
    if (__MASK((INTEGER)base->sysflag, -256) != 0) {
      OfrontOPM_err(138);
    }
    OfrontOPC_Andent(base);
    OfrontOPM_WriteString((CHAR*)"__typ", 6);
  } else if ((INTEGER)base->form == 13) {
    OfrontOPM_WriteString((CHAR*)"POINTER__typ", 13);
  } else {
    OfrontOPM_WriteString((CHAR*)"NIL", 4);
  }
  OfrontOPM_WriteString((CHAR*)", ", 3);
  OfrontOPM_WriteInt(base->size);
  OfrontOPM_PromoteIntConstToLInt();
  OfrontOPM_WriteString((CHAR*)", ", 3);
  OfrontOPM_WriteInt(OfrontOPC_BaseAlignment(base, base->sysflag));
  OfrontOPM_WriteString((CHAR*)", ", 3);
  OfrontOPM_WriteInt(nofdim);
  OfrontOPM_WriteString((CHAR*)", ", 3);
  OfrontOPM_WriteInt(nofdyn);
  while (typ != base) {
    OfrontOPM_WriteString((CHAR*)", (SYSTEM_ARRLEN)", 18);
    if ((INTEGER)typ->comp == 3) {
      if ((INTEGER)x->class == 7) {
        OfrontOPV_expr(x, -1);
      } else {
        OfrontOPV_expr(x, 10);
      }
      x = x->link;
    } else {
      OfrontOPM_WriteInt(typ->n);
    }
    typ = typ->BaseTyp;
  }
  OfrontOPM_Write(')');
}

static void OfrontOPV_DefineTDescs (OfrontOPT_Node n)
{
  while (n != NIL && (INTEGER)n->class == 14) {
    OfrontOPC_TDescDecl(n->typ);
    n = n->link;
  }
}

static void OfrontOPV_InitTDescs (OfrontOPT_Node n)
{
  while (n != NIL && (INTEGER)n->class == 14) {
    OfrontOPC_InitTDesc(n->typ);
    n = n->link;
  }
}

static void OfrontOPV_AddCopy (OfrontOPT_Node left, OfrontOPT_Node right, BOOLEAN first)
{
  if (first) {
    OfrontOPM_WriteString((CHAR*)"__STRCOPY", 10);
  } else {
    OfrontOPM_WriteString((CHAR*)"__STRAPND", 10);
  }
  OfrontOPV_StringModifier(right);
  OfrontOPV_StringModifier(left);
  OfrontOPM_Write('(');
  OfrontOPV_expr(right, -1);
  OfrontOPM_WriteString((CHAR*)", ", 3);
  if (!first) {
    if (((INTEGER)right->typ->form == 18 && (INTEGER)right->class == 11) && (INTEGER)right->subcl == 22) {
      right = right->left;
    }
    if ((INTEGER)right->class == 3) {
      right = right->left;
    }
    if ((INTEGER)right->typ->sysflag != 0) {
      OfrontOPM_WriteString((CHAR*)"-1", 3);
    } else {
      OfrontOPV_Len(right, 0, 0);
    }
    OfrontOPM_WriteString((CHAR*)", ", 3);
  }
  OfrontOPV_expr(left, -1);
  OfrontOPM_WriteString((CHAR*)", ", 3);
  if (first) {
    OfrontOPV_MaxLen(left, right);
  } else if ((INTEGER)left->typ->sysflag != 0) {
    OfrontOPM_WriteString((CHAR*)"-1", 3);
  } else {
    OfrontOPV_Len(left, 0, 0);
  }
  OfrontOPM_WriteString((CHAR*)", ", 3);
  OfrontOPM_WriteModPos();
  OfrontOPM_Write(')');
}

static void OfrontOPV_StringCopy (OfrontOPT_Node left, OfrontOPT_Node right, BOOLEAN exp)
{
  __ASSERT((INTEGER)right->class != 7, 0, (CHAR*)"OfrontOPV", 305182);
  if ((INTEGER)right->class == 12) {
    __ASSERT((INTEGER)right->subcl == 8, 0, (CHAR*)"OfrontOPV", 305693);
    if (!OfrontOPV_SameExp(left, right->left)) {
      OfrontOPV_AddCopy(left, right->left, 1);
      if (exp) {
        OfrontOPM_WriteString((CHAR*)", ", 3);
      } else {
        OfrontOPC_EndStat();
        OfrontOPC_BegStat();
      }
    }
    right = right->right;
    while ((INTEGER)right->class == 12) {
      __ASSERT((INTEGER)right->subcl == 8, 0, (CHAR*)"OfrontOPV", 307486);
      OfrontOPV_AddCopy(left, right->left, 0);
      if (exp) {
        OfrontOPM_WriteString((CHAR*)", ", 3);
      } else {
        OfrontOPC_EndStat();
        OfrontOPC_BegStat();
      }
      right = right->right;
    }
    OfrontOPV_AddCopy(left, right, 0);
  } else {
    OfrontOPV_AddCopy(left, right, 1);
  }
}

static void OfrontOPV_compStat (OfrontOPT_Node n, BOOLEAN exp)
{
  OfrontOPT_Node l = NIL;
  OfrontOPT_Node r = NIL;
  while (n != NIL && OfrontOPM_noerr) {
    if (!exp) {
      OfrontOPC_BegStat();
    }
    __ASSERT((INTEGER)n->class == 19, 0, (CHAR*)"OfrontOPV", 311580);
    l = n->left;
    r = n->right;
    if ((INTEGER)n->subcl == 0) {
      if (__IN(r->typ->form, 0x040400)) {
        if ((INTEGER)r->class != 7) {
          OfrontOPV_StringCopy(l, r, exp);
        } else {
          OfrontOPM_WriteString((CHAR*)"__MOVE(", 8);
          OfrontOPV_expr(r, -1);
          OfrontOPM_WriteString((CHAR*)", ", 3);
          OfrontOPV_expr(l, -1);
          OfrontOPM_WriteString((CHAR*)", ", 3);
          OfrontOPM_WriteInt(r->conval->intval2 * r->typ->BaseTyp->size);
          OfrontOPM_Write(')');
        }
      } else {
        __ASSERT(__IN(l->typ->form, 0x022008), 0, (CHAR*)"OfrontOPV", 314425);
        OfrontOPV_design(l, -1);
        OfrontOPM_WriteString((CHAR*)" = ", 4);
        OfrontOPV_expr(r, -1);
      }
    } else {
      __ASSERT((INTEGER)n->subcl == 1, 0, (CHAR*)"OfrontOPV", 315167);
      __ASSERT((INTEGER)l->typ->BaseTyp->comp == 3, 0, (CHAR*)"OfrontOPV", 315431);
      OfrontOPV_NewArr(l, r);
    }
    if (exp) {
      OfrontOPM_WriteString((CHAR*)", ", 3);
      OfrontOPM_WriteLn();
      OfrontOPC_BegStat();
      OfrontOPM_WriteTab();
    } else {
      OfrontOPC_EndStat();
    }
    n = n->link;
  }
}

static struct stat__44 {
  struct stat__44 *lnk;
} *stat__44_s;

static void __45 (OfrontOPT_Node id, SHORTINT cond, OfrontOPT_Node z);

static void __45 (OfrontOPT_Node id, SHORTINT cond, OfrontOPT_Node z)
{
  LONGINT step;
  step = z->conval->intval;
  if ((INTEGER)cond == 12) {
    OfrontOPM_WriteString((CHAR*)"!", 2);
  }
  if (step == 1) {
    OfrontOPM_WriteString((CHAR*)"++", 3);
    OfrontOPC_CompleteIdent(id->obj);
  } else if (step == -1) {
    OfrontOPM_WriteString((CHAR*)"--", 3);
    OfrontOPC_CompleteIdent(id->obj);
  } else if (step == 0) {
    OfrontOPC_CompleteIdent(id->obj);
  } else {
    if ((INTEGER)cond != 11) {
      OfrontOPM_WriteString((CHAR*)"(", 2);
    }
    OfrontOPC_CompleteIdent(id->obj);
    OfrontOPM_WriteString((CHAR*)"+=", 3);
    OfrontOPV_expr(z, -1);
    if ((INTEGER)cond != 11) {
      OfrontOPM_WriteString((CHAR*)")", 2);
    }
  }
  switch (cond) {
    case 11: case 12: 
      break;
    case 13: 
      OfrontOPM_WriteString((CHAR*)" >= 0", 6);
      break;
    case 14: 
      OfrontOPM_WriteString((CHAR*)" > 0", 5);
      break;
    case 15: 
      OfrontOPM_WriteString((CHAR*)" <= 0", 6);
      break;
    case 16: 
      OfrontOPM_WriteString((CHAR*)" < 0", 5);
      break;
    default: __CASECHK((CHAR*)"OfrontOPV", 323362);
  }
}

static void OfrontOPV_stat (OfrontOPT_Node n, OfrontOPT_Object outerProc)
{
  OfrontOPT_Object proc = NIL;
  OfrontOPV_ExitInfo saved;
  OfrontOPT_Node l = NIL;
  OfrontOPT_Node r = NIL;
  INTEGER i;
  CHAR ch;
  struct stat__44 _s;
  _s.lnk = stat__44_s;
  stat__44_s = &_s;
  while (n != NIL && OfrontOPM_noerr) {
    OfrontOPM_errpos = (INTEGER)n->conval->intval;
    if (!__IN(n->class, 0x60004000)) {
      OfrontOPC_BegStat();
    }
    switch (n->class) {
      case 18: 
        __ASSERT(n->obj != NIL, 0, (CHAR*)"OfrontOPV", 325914);
        proc = n->obj;
        OfrontOPC_TypeDefs(proc->scope->right);
        if (!proc->scope->leaf) {
          OfrontOPC_DefineInter(proc);
        }
        OfrontOPM_level += 1;
        OfrontOPV_stat(n->left, proc);
        OfrontOPM_level -= 1;
        OfrontOPC_EnterProc(proc);
        OfrontOPV_stat(n->right, proc);
        OfrontOPC_ExitProc(proc, 1, OfrontOPV_ImplicitReturn(n->right));
        if ((INTEGER)proc->sysflag == 3 && (INTEGER)proc->vis != 0) {
          i = OfrontOPM_currFile;
          OfrontOPM_currFile = 0;
          OfrontOPC_EnterProc(proc);
          OfrontOPV_stat(n->right, proc);
          OfrontOPC_ExitProc(proc, 1, OfrontOPV_ImplicitReturn(n->right));
          OfrontOPM_currFile = i;
        }
        break;
      case 14: 
        break;
      case 19: 
        switch (n->subcl) {
          case 0: 
            l = n->left;
            r = n->right;
            if (__IN(l->typ->comp, 0x0c)) {
              if (__IN(r->typ->form, 0x040400) && (INTEGER)r->class != 7) {
                OfrontOPV_StringCopy(l, r, 0);
              } else if ((__IN(r->typ->form, 0x040400) && (INTEGER)l->typ->sysflag == 0) && !((INTEGER)l->typ->comp == 2 && r->conval->intval2 <= l->typ->n)) {
                OfrontOPV_AddCopy(l, r, 1);
              } else {
                OfrontOPM_WriteString((CHAR*)"__MOVE(", 8);
                OfrontOPV_expr(r, -1);
                OfrontOPM_WriteString((CHAR*)", ", 3);
                OfrontOPV_expr(l, -1);
                OfrontOPM_WriteString((CHAR*)", ", 3);
                if (r->typ == OfrontOPT_string8typ) {
                  OfrontOPM_WriteInt(r->conval->intval2);
                } else if (r->typ == OfrontOPT_string16typ) {
                  OfrontOPM_WriteInt(r->conval->intval2 * OfrontOPT_char16typ->size);
                } else {
                  OfrontOPM_WriteInt(r->typ->size);
                }
                OfrontOPM_Write(')');
              }
            } else {
              if ((((INTEGER)l->typ->form == 13 && l->obj != NIL) && l->obj->adr == 1) && (INTEGER)l->obj->mode == 1) {
                l->obj->adr = 0;
                OfrontOPV_design(l, -1);
                l->obj->adr = 1;
                if ((INTEGER)r->typ->form != 11) {
                  OfrontOPM_WriteString((CHAR*)" = (void*)", 11);
                } else {
                  OfrontOPM_WriteString((CHAR*)" = ", 4);
                }
              } else {
                OfrontOPV_design(l, -1);
                OfrontOPM_WriteString((CHAR*)" = ", 4);
              }
              if (l->typ == r->typ) {
                OfrontOPV_expr(r, -1);
              } else if ((INTEGER)l->typ->form == 13 && (INTEGER)r->typ->form != 11) {
                if (l->typ->strobj != NIL) {
                  OfrontOPM_Write('(');
                  OfrontOPC_Ident(l->typ->strobj);
                  OfrontOPM_Write(')');
                } else if ((l->typ->BaseTyp != NIL && l->typ->BaseTyp->strobj != NIL) && l->typ->BaseTyp != r->typ->BaseTyp) {
                  OfrontOPM_Write('(');
                  OfrontOPC_Ident(l->typ->BaseTyp->strobj);
                  OfrontOPM_WriteString((CHAR*)"*)", 3);
                }
                OfrontOPV_expr(r, -1);
              } else if ((INTEGER)l->typ->comp == 4) {
                OfrontOPM_WriteString((CHAR*)"*(", 3);
                OfrontOPC_Andent(l->typ);
                OfrontOPM_WriteString((CHAR*)"*)", 3);
                OfrontOPV_Adr(r, 9, 0);
              } else {
                OfrontOPV_expr(r, -1);
              }
            }
            break;
          case 1: 
            if ((INTEGER)n->left->typ->BaseTyp->comp == 4) {
              OfrontOPM_WriteString((CHAR*)"__NEW(", 7);
              OfrontOPV_design(n->left, -1);
              OfrontOPM_WriteString((CHAR*)", ", 3);
              OfrontOPC_Andent(n->left->typ->BaseTyp);
              OfrontOPM_WriteString((CHAR*)")", 2);
            } else if (__IN(n->left->typ->BaseTyp->comp, 0x0c)) {
              OfrontOPV_NewArr(n->left, n->right);
            }
            break;
          case 19: case 20: 
            OfrontOPV_expr_val(n->left, -1, 1);
            OfrontOPC_Increment((INTEGER)n->subcl == 20);
            OfrontOPV_expr(n->right, -1);
            break;
          case 21: case 22: 
            OfrontOPV_expr_val(n->left, -1, 1);
            OfrontOPC_SetInclude((INTEGER)n->subcl == 22);
            OfrontOPM_WriteString((CHAR*)"__SETOF(", 9);
            OfrontOPV_expr(n->right, -1);
            OfrontOPM_Write(')');
            break;
          case 24: 
            OfrontOPM_WriteString((CHAR*)"__COPY(", 8);
            OfrontOPV_expr(n->right, -1);
            OfrontOPM_WriteString((CHAR*)", ", 3);
            OfrontOPV_expr(n->left, -1);
            OfrontOPM_WriteString((CHAR*)", ", 3);
            OfrontOPV_MaxLen(n->left, n->right);
            OfrontOPM_Write(')');
            break;
          case 32: 
            OfrontOPM_WriteString((CHAR*)"__PACK(&", 9);
            OfrontOPV_expr(n->left, -1);
            OfrontOPM_WriteString((CHAR*)", ", 3);
            OfrontOPV_expr(n->right, -1);
            OfrontOPM_Write(')');
            break;
          case 33: 
            OfrontOPM_WriteString((CHAR*)"__UNPK(&", 9);
            OfrontOPV_expr(n->left, -1);
            OfrontOPM_WriteString((CHAR*)", &", 4);
            OfrontOPV_expr(n->right, -1);
            OfrontOPM_Write(')');
            break;
          case 37: 
            OfrontOPM_WriteString((CHAR*)"__MOVE(", 8);
            OfrontOPV_expr(n->right, -1);
            OfrontOPM_WriteString((CHAR*)", ", 3);
            OfrontOPV_expr(n->left, -1);
            OfrontOPM_WriteString((CHAR*)", ", 3);
            OfrontOPV_expr(n->right->link, -1);
            OfrontOPM_Write(')');
            break;
          case 30: 
            OfrontOPM_WriteString((CHAR*)"__GET(", 7);
            OfrontOPV_expr(n->right, -1);
            OfrontOPM_WriteString((CHAR*)", ", 3);
            OfrontOPV_expr(n->left, -1);
            OfrontOPM_WriteString((CHAR*)", ", 3);
            OfrontOPC_Ident(n->left->typ->strobj);
            OfrontOPM_Write(')');
            break;
          case 31: 
            OfrontOPM_WriteString((CHAR*)"__PUT(", 7);
            OfrontOPV_expr(n->left, -1);
            OfrontOPM_WriteString((CHAR*)", ", 3);
            OfrontOPV_expr(n->right, -1);
            OfrontOPM_WriteString((CHAR*)", ", 3);
            OfrontOPC_Ident(n->right->typ->strobj);
            OfrontOPM_Write(')');
            break;
          case 36: 
            OfrontOPM_WriteString((CHAR*)"__SYSNEW(", 10);
            OfrontOPV_design(n->left, -1);
            OfrontOPM_WriteString((CHAR*)", ", 3);
            OfrontOPV_expr(n->right, -1);
            OfrontOPM_Write(')');
            break;
          default: __CASECHK((CHAR*)"OfrontOPV", 350207);
        }
        break;
      case 13: 
        if (n->left->obj != NIL && (INTEGER)n->left->obj->mode == 13) {
          if ((INTEGER)n->left->subcl == 1) {
            proc = OfrontOPV_SuperProc(n);
          } else {
            OfrontOPM_WriteString((CHAR*)"__", 3);
            proc = OfrontOPC_BaseTProc(n->left->obj);
          }
          OfrontOPC_Ident(proc);
          n->obj = proc->link;
        } else if ((INTEGER)n->left->class == 9) {
          OfrontOPV_design(n->left, 10);
        } else {
          OfrontOPV_expr(n->left, 11);
        }
        OfrontOPV_ActualPar(n->right, n->obj);
        break;
      case 20: 
        if ((INTEGER)n->subcl != 38) {
          OfrontOPV_IfStat(n, 0, outerProc);
        } else if (OfrontOPV_assert) {
          OfrontOPM_WriteString((CHAR*)"__ASSERT(", 10);
          OfrontOPV_expr(n->left->left->left, -1);
          OfrontOPM_WriteString((CHAR*)", ", 3);
          OfrontOPM_WriteInt(n->left->right->right->conval->intval);
          OfrontOPM_WriteString((CHAR*)", ", 3);
          OfrontOPM_WriteModPos();
          OfrontOPM_Write(')');
          OfrontOPC_EndStat();
        }
        break;
      case 21: 
        OfrontOPV_exit.level += 1;
        OfrontOPV_CaseStat(n, outerProc);
        OfrontOPV_exit.level -= 1;
        break;
      case 22: 
        OfrontOPV_exit.level += 1;
        OfrontOPM_WriteString((CHAR*)"while ", 7);
        OfrontOPV_expr(n->left, 12);
        OfrontOPM_Write(' ');
        OfrontOPC_BegBlk();
        OfrontOPV_stat(n->right, outerProc);
        OfrontOPC_EndBlk();
        OfrontOPV_exit.level -= 1;
        break;
      case 11: 
        OfrontOPV_exit.level += 1;
        OfrontOPM_WriteString((CHAR*)"for (;;) ", 10);
        OfrontOPC_BegBlk();
        break;
      case 12: 
        OfrontOPV_exit.level -= 1;
        OfrontOPM_WriteString((CHAR*)"else break", 11);
        OfrontOPC_EndStat();
        OfrontOPC_EndBlk();
        break;
      case 23: 
        OfrontOPV_exit.level += 1;
        OfrontOPM_WriteString((CHAR*)"do ", 4);
        OfrontOPC_BegBlk();
        OfrontOPV_stat(n->left, outerProc);
        OfrontOPC_EndBlk0();
        if ((INTEGER)n->right->class == 19) {
          OfrontOPM_WriteString((CHAR*)" while (", 9);
          __45(n->right->left, n->right->subcl, n->right->right);
          OfrontOPM_Write(')');
        } else {
          OfrontOPM_WriteString((CHAR*)" while (!", 10);
          OfrontOPV_expr(n->right, 9);
          OfrontOPM_Write(')');
        }
        OfrontOPV_exit.level -= 1;
        break;
      case 24: 
        saved = OfrontOPV_exit;
        OfrontOPV_exit.level = 0;
        OfrontOPV_exit.label = -1;
        OfrontOPM_WriteString((CHAR*)"for (;;) ", 10);
        OfrontOPC_BegBlk();
        OfrontOPV_stat(n->left, outerProc);
        OfrontOPC_EndBlk();
        if ((INTEGER)OfrontOPV_exit.label != -1) {
          OfrontOPC_BegStat();
          OfrontOPM_WriteString((CHAR*)"exit__", 7);
          OfrontOPM_WriteInt(OfrontOPV_exit.label);
          OfrontOPM_Write(':');
          OfrontOPC_EndStat();
        }
        OfrontOPV_exit = saved;
        break;
      case 25: 
        if ((INTEGER)OfrontOPV_exit.level == 0) {
          OfrontOPM_WriteString((CHAR*)"break", 6);
        } else {
          if ((INTEGER)OfrontOPV_exit.label == -1) {
            OfrontOPV_exit.label = OfrontOPV_nofExitLabels;
            OfrontOPV_nofExitLabels += 1;
          }
          OfrontOPM_WriteString((CHAR*)"goto exit__", 12);
          OfrontOPM_WriteInt(OfrontOPV_exit.label);
        }
        break;
      case 26: 
        if (OfrontOPM_level == 0) {
          OfrontOPC_retmain = 1;
          OfrontOPM_WriteString((CHAR*)"goto return__", 14);
        } else if (OfrontOPC_NeedsRetval(outerProc)) {
          OfrontOPM_WriteString((CHAR*)"__retval = ", 12);
          if ((INTEGER)n->left->typ->form == 13 && n->obj->typ != n->left->typ) {
            OfrontOPM_WriteString((CHAR*)"(void*)", 8);
            OfrontOPV_expr(n->left, 10);
          } else {
            OfrontOPV_expr(n->left, -1);
          }
          OfrontOPC_EndStat();
          OfrontOPC_BegStat();
          OfrontOPC_ExitProc(outerProc, 0, 0);
          OfrontOPC_EndStat();
          OfrontOPC_BegStat();
          OfrontOPM_WriteString((CHAR*)"return __retval", 16);
        } else {
          OfrontOPC_ExitProc(outerProc, 0, 0);
          OfrontOPM_WriteString((CHAR*)"return", 7);
          if (n->left != NIL) {
            OfrontOPM_Write(' ');
            if ((INTEGER)n->left->typ->form == 13 && n->obj->typ != n->left->typ) {
              OfrontOPM_WriteString((CHAR*)"(void*)", 8);
              OfrontOPV_expr(n->left, 10);
            } else {
              OfrontOPV_expr(n->left, -1);
            }
          }
        }
        break;
      case 27: 
        OfrontOPV_IfStat(n, (INTEGER)n->subcl == 0, outerProc);
        break;
      case 28: 
        OfrontOPC_Halt((INTEGER)n->right->conval->intval);
        break;
      case 29: 
        OfrontOPV_compStat(n->left, 0);
        OfrontOPV_stat(n->right, outerProc);
        break;
      case 30: 
        if (OfrontOPT_SYSimported) {
          i = 0;
          ch = (n->left->conval->ext->data)[0];
          while (ch != 0x00) {
            if (ch == 0x0d) {
              OfrontOPM_WriteLn();
            } else {
              OfrontOPM_Write(ch);
            }
            i += 1;
            ch = (n->left->conval->ext->data)[__X(i, n->left->conval->ext->len[0], (CHAR*)"OfrontOPV", 371967)];
          }
          OfrontOPM_WriteLn();
        }
        break;
      default: __CASECHK((CHAR*)"OfrontOPV", 372479);
    }
    if (!__IN(n->class, 0x69745800)) {
      OfrontOPC_EndStat();
    }
    n = n->link;
  }
  stat__44_s = _s.lnk;
}

void OfrontOPV_Module (OfrontOPT_Node prog)
{
  OfrontOPM_level = 0;
  if (!OfrontOPV_mainprog) {
    OfrontOPC_GenHdr(prog->right);
    OfrontOPC_GenHdrIncludes();
  }
  OfrontOPC_GenBdy(prog->right);
  OfrontOPM_level += 1;
  OfrontOPV_stat(prog->left, NIL);
  OfrontOPM_level -= 1;
  if (!__IN(15, OfrontOPM_opt)) {
    OfrontOPC_GenEnumPtrs(OfrontOPT_topScope->scope);
    OfrontOPV_DefineTDescs(prog->right);
    OfrontOPC_EnterBody();
    OfrontOPV_InitTDescs(prog->right);
    OfrontOPM_WriteString((CHAR*)"/* BEGIN */", 12);
    OfrontOPM_WriteLn();
    OfrontOPV_stat(prog->right, NIL);
    OfrontOPC_ExitBody();
    if (prog->link != NIL || __IN(19, OfrontOPM_opt)) {
      OfrontOPC_EnterClose();
      OfrontOPV_stat(prog->link, NIL);
      OfrontOPC_ExitClose();
    }
    if (OfrontOPV_mainprog && __IN(11, OfrontOPM_opt)) {
      OfrontOPC_DllMainBody(prog->link != NIL);
    }
  }
  OfrontOPM_currFile = 0;
  OfrontOPM_WriteString((CHAR*)"#endif", 7);
  OfrontOPM_WriteLn();
  OfrontOPC_CleanupArrays();
}

/*----------------------------------------------------------------------------*/
__TDESC(OfrontOPV_ExitInfo__desc, 2, 0) = {__TDFLDS("ExitInfo", 4), {-8}};

export void *OfrontOPV__init (void)
{
  __DEFMOD;
  __IMPORT(OfrontOPC__init);
  __IMPORT(OfrontOPM__init);
  __IMPORT(OfrontOPS__init);
  __IMPORT(OfrontOPT__init);
  __REGMOD("OfrontOPV", 0);
  __REGCMD("Init", OfrontOPV_Init);
  __INITYP(OfrontOPV_ExitInfo, OfrontOPV_ExitInfo, 0);
/* BEGIN */
  __ENDMOD;
}
