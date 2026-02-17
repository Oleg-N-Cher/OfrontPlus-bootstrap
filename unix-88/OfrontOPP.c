/* Ofront+ 1.0 -sC -88 */
#include "SYSTEM.oh"
#include "OfrontOPB.oh"
#include "OfrontOPT.oh"
#include "OfrontOPS.oh"
#include "OfrontOPM.oh"

struct OfrontOPP__1 {
  INTEGER low, high;
};

typedef
  struct OfrontOPP__1 OfrontOPP_CaseTable[256];

typedef
  struct OfrontOPP_Elem__rec *OfrontOPP_Elem;

typedef
  struct OfrontOPP_Elem__rec {
    OfrontOPP_Elem next;
    OfrontOPT_Struct struct_;
    OfrontOPT_Object obj, base;
    INTEGER pos;
    OfrontOPS_String name;
  } OfrontOPP_Elem__rec;


static BYTE OfrontOPP_sym, OfrontOPP_level;
static SHORTINT OfrontOPP_LoopLevel, OfrontOPP_ReturnLevel;
static OfrontOPT_Node OfrontOPP_TDinit, OfrontOPP_lastTDinit;
static OfrontOPP_Elem OfrontOPP_userList, OfrontOPP_recList;
static BOOLEAN OfrontOPP_hasReturn;

export void **OfrontOPP_Elem__rec__typ;
export void **OfrontOPP__1__typ;

static void OfrontOPP_ActualParameters (OfrontOPT_Node *aparlist, OfrontOPT_Object fpar, OfrontOPT_Node *pre, OfrontOPT_Node *lastp);
static void OfrontOPP_ArrayType (OfrontOPT_Struct *typ);
static void OfrontOPP_Block (OfrontOPT_Node *procdec, OfrontOPT_Node *statseq);
static void OfrontOPP_CaseLabelList (OfrontOPT_Node *lab, SHORTINT LabelForm, SHORTINT *n, OfrontOPP_CaseTable tab);
static void OfrontOPP_CheckAlloc (OfrontOPT_Struct *typ, BOOLEAN dynAllowed, INTEGER pos);
static void OfrontOPP_CheckForwardTypes (void);
static void OfrontOPP_CheckMark (OfrontOPT_Object obj);
static void OfrontOPP_CheckOverwrite (OfrontOPT_Object proc, OfrontOPT_Object base, OfrontOPT_Struct rec);
static void OfrontOPP_CheckRecords (OfrontOPP_Elem rec);
static void OfrontOPP_CheckRecursiveType (OfrontOPT_Struct outer, OfrontOPT_Struct inner, INTEGER pos);
static void OfrontOPP_CheckSym (SHORTINT s);
static void OfrontOPP_CheckSysFlag (SHORTINT *sysflag, SHORTINT default_, BOOLEAN record);
static void OfrontOPP_CheckSysFlagProc (SHORTINT *sysflag, BOOLEAN checkinline);
static void OfrontOPP_CheckSysFlagVarPar (SHORTINT *sysflag);
static void OfrontOPP_CheckUnimpl (OfrontOPT_Object m, OfrontOPT_Struct typ, INTEGER pos);
static void OfrontOPP_ConstArray (OfrontOPT_Node *x, OfrontOPT_Struct typ);
static void OfrontOPP_ConstExpression (OfrontOPT_Node *x);
static void OfrontOPP_Element (OfrontOPT_Node *x);
static void OfrontOPP_Expression (OfrontOPT_Node *x);
static void OfrontOPP_Factor (OfrontOPT_Node *x);
static void OfrontOPP_FixType (OfrontOPT_Struct struct_, OfrontOPT_Object obj, OfrontOPT_Struct typ, INTEGER pos);
static void OfrontOPP_FormalParameters (OfrontOPT_Object *firstPar, OfrontOPT_Struct *resTyp, OfrontOPS_String *name);
static void OfrontOPP_GetAttributes (OfrontOPT_Object proc, OfrontOPT_Object base, OfrontOPT_Struct owner);
static BOOLEAN OfrontOPP_IncompleteType (OfrontOPT_Struct typ);
export void OfrontOPP_Module (OfrontOPT_Node *prog, SET opt);
static void OfrontOPP_PointerType (OfrontOPT_Struct *typ);
static void OfrontOPP_ProcedureDeclaration (OfrontOPT_Node *x);
static void OfrontOPP_Receiver (BYTE *mode, BYTE *vis, OfrontOPS_Name name, OfrontOPT_Struct *typ, OfrontOPT_Struct *rec);
static void OfrontOPP_RecordType (OfrontOPT_Struct *typ, OfrontOPT_Object attr);
static void OfrontOPP_SetType (OfrontOPT_Struct struct_, OfrontOPT_Object obj, OfrontOPT_Struct typ, OfrontOPS_String name);
static void OfrontOPP_Sets (OfrontOPT_Node *x);
static INTEGER OfrontOPP_Sign (LONGINT n);
static void OfrontOPP_SimpleExpression (OfrontOPT_Node *x);
static void OfrontOPP_StandProcCall (OfrontOPT_Node *x);
static void OfrontOPP_StatSeq (OfrontOPT_Node *stat);
static void OfrontOPP_String2Chars (OfrontOPT_Node a, OfrontOPT_Node *x);
static void OfrontOPP_Term (OfrontOPT_Node *x);
static void OfrontOPP_Type (OfrontOPT_Struct *typ, OfrontOPS_String *name);
static void OfrontOPP_err (SHORTINT n);
static void OfrontOPP_qualident (OfrontOPT_Object *id);
static void OfrontOPP_selector (OfrontOPT_Node *x);


/*============================================================================*/

static BOOLEAN OfrontOPP_IncompleteType (OfrontOPT_Struct typ)
{
  if ((INTEGER)typ->form == 13) {
    if (typ == OfrontOPT_sysptrtyp) {
      return 0;
    }
    typ = typ->BaseTyp;
  }
  return typ == OfrontOPT_undftyp || ((INTEGER)typ->comp == 4 && typ->BaseTyp == OfrontOPT_undftyp);
}

static void OfrontOPP_SetType (OfrontOPT_Struct struct_, OfrontOPT_Object obj, OfrontOPT_Struct typ, OfrontOPS_String name)
{
  OfrontOPP_Elem u = NIL;
  if (obj != NIL) {
    obj->typ = typ;
  } else {
    struct_->BaseTyp = typ;
  }
  if (name != NIL) {
    __NEW(u, OfrontOPP_Elem__rec);
    u->struct_ = struct_;
    u->obj = obj;
    u->pos = OfrontOPM_errpos;
    u->name = name;
    u->next = OfrontOPP_userList;
    OfrontOPP_userList = u;
  }
}

static void OfrontOPP_CheckAlloc (OfrontOPT_Struct *typ, BOOLEAN dynAllowed, INTEGER pos)
{
  (*typ)->pvused = 1;
  if ((INTEGER)(*typ)->comp == 3) {
    if (!dynAllowed) {
      OfrontOPM_Mark(88, pos);
      *typ = OfrontOPT_undftyp;
    }
  } else if ((INTEGER)(*typ)->comp == 4) {
    if ((INTEGER)(*typ)->attribute == 17 || ((INTEGER)(*typ)->attribute == 18 && (INTEGER)(*typ)->mno != 0)) {
      OfrontOPM_Mark(193, pos);
      *typ = OfrontOPT_undftyp;
    }
  }
}

static void OfrontOPP_CheckRecursiveType (OfrontOPT_Struct outer, OfrontOPT_Struct inner, INTEGER pos)
{
  OfrontOPT_Object fld = NIL;
  if (outer == inner) {
    OfrontOPM_Mark(58, pos);
  } else if (__IN(inner->comp, 0x0c)) {
    OfrontOPP_CheckRecursiveType(outer, inner->BaseTyp, pos);
  } else if ((INTEGER)inner->comp == 4) {
    fld = inner->link;
    while (fld != NIL && (INTEGER)fld->mode == 4) {
      OfrontOPP_CheckRecursiveType(outer, fld->typ, pos);
      fld = fld->link;
    }
    if (inner->BaseTyp != NIL) {
      OfrontOPP_CheckRecursiveType(outer, inner->BaseTyp, pos);
    }
  }
}

static void OfrontOPP_FixType (OfrontOPT_Struct struct_, OfrontOPT_Object obj, OfrontOPT_Struct typ, INTEGER pos)
{
  OfrontOPT_Struct t = NIL;
  OfrontOPT_Object f = NIL;
  OfrontOPT_Object bf = NIL;
  SHORTINT i;
  OfrontOPS_String _ptr__28 = NIL;
  if (obj != NIL) {
    if ((INTEGER)obj->mode == 1) {
      if (struct_ != NIL) {
        if ((INTEGER)typ->form != 13 || typ->BaseTyp != struct_) {
          OfrontOPM_Mark(180, pos);
        }
      } else {
        OfrontOPP_CheckAlloc(&typ, (INTEGER)obj->mnolev > (INTEGER)OfrontOPP_level, pos);
      }
    } else if ((INTEGER)obj->mode == 2) {
      if (struct_ != NIL) {
        if (typ != struct_) {
          OfrontOPM_Mark(180, pos);
        }
      }
    } else if ((INTEGER)obj->mode == 4) {
      OfrontOPP_CheckAlloc(&typ, 0, pos);
      OfrontOPP_CheckRecursiveType(struct_, typ, pos);
    } else if ((INTEGER)obj->mode == 13) {
      if ((INTEGER)typ->form == 16) {
        typ = OfrontOPT_undftyp;
        OfrontOPM_Mark(54, pos);
      }
    } else if ((INTEGER)obj->mode == 5) {
      if (__IN(typ->form, 0x0203fe)) {
        t = OfrontOPT_NewStr(typ->form, 1);
        i = t->ref;
        __GUARDEQP(t, OfrontOPT_StrDesc) = *typ;
        t->ref = i;
        t->strobj = obj;
        t->mno = 0;
        t->BaseTyp = typ;
        typ = t;
      }
      if ((INTEGER)obj->vis != 0) {
        if ((INTEGER)typ->comp == 4) {
          typ->exp = 1;
        } else if ((INTEGER)typ->form == 13) {
          typ->BaseTyp->exp = 1;
        }
      }
    } else {
      __HALT(100, (CHAR*)"OfrontOPP", 46079);
    }
    obj->typ = typ;
  } else {
    if ((INTEGER)struct_->form == 13) {
      if ((INTEGER)typ->comp != 4 && !__IN(typ->comp, 0x0c)) {
        typ = OfrontOPT_undftyp;
        OfrontOPM_Mark(57, pos);
      }
      if (struct_->strobj != NIL && (INTEGER)struct_->strobj->vis != 0) {
        typ->exp = 1;
      }
    } else if ((INTEGER)struct_->comp == 2) {
      OfrontOPP_CheckAlloc(&typ, 0, pos);
      OfrontOPP_CheckRecursiveType(struct_, typ, pos);
    } else if ((INTEGER)struct_->comp == 3) {
      OfrontOPP_CheckAlloc(&typ, 1, pos);
      OfrontOPP_CheckRecursiveType(struct_, typ, pos);
    } else if ((INTEGER)struct_->comp == 4) {
      if ((INTEGER)typ->form == 13) {
        typ = typ->BaseTyp;
      }
      typ->pvused = 1;
      struct_->extlev = (BYTE)((INTEGER)typ->extlev + 1);
      if ((INTEGER)typ->attribute == 0 || ((INTEGER)typ->attribute == 18 && (INTEGER)typ->mno != 0)) {
        OfrontOPM_Mark(181, pos);
      } else if ((INTEGER)struct_->attribute == 17 && (INTEGER)typ->attribute != 17) {
        OfrontOPM_Mark(191, pos);
      } else if ((INTEGER)typ->attribute == 18 && (INTEGER)struct_->attribute != 18) {
        OfrontOPM_Mark(197, pos);
      }
      f = struct_->link;
      while (f != NIL) {
        _ptr__28 = f->name;
        OfrontOPT_FindField((void*)_ptr__28->data, _ptr__28->len[0], typ, &bf);
        if (bf != NIL) {
          OfrontOPM_Mark(1, pos);
        }
        f = f->link;
      }
      OfrontOPP_CheckRecursiveType(struct_, typ, pos);
    } else if ((INTEGER)struct_->form == 15) {
      if ((INTEGER)typ->form == 16) {
        typ = OfrontOPT_undftyp;
        OfrontOPM_Mark(54, pos);
      }
    } else {
      __HALT(100, (CHAR*)"OfrontOPP", 54015);
    }
    struct_->BaseTyp = typ;
  }
}

static void OfrontOPP_CheckForwardTypes (void)
{
  OfrontOPP_Elem u = NIL;
  OfrontOPP_Elem next = NIL;
  BOOLEAN progress;
  OfrontOPS_Name name;
  u = OfrontOPP_userList;
  OfrontOPP_userList = NIL;
  while (u != NIL) {
    next = u->next;
    __STRCOPYCC(u->name->data, name, __MIN(48, u->name->len[0]), (CHAR*)"OfrontOPP", 56610);
    OfrontOPT_Find((void*)name, 48, &u->base);
    if (u->base == NIL) {
      OfrontOPM_Mark(0, u->pos);
    } else if ((INTEGER)u->base->mode != 5) {
      OfrontOPM_Mark(72, u->pos);
    } else {
      u->next = OfrontOPP_userList;
      OfrontOPP_userList = u;
    }
    u = next;
  }
  do {
    u = OfrontOPP_userList;
    OfrontOPP_userList = NIL;
    progress = 0;
    while (u != NIL) {
      next = u->next;
      if (OfrontOPP_IncompleteType(u->base->typ)) {
        u->next = OfrontOPP_userList;
        OfrontOPP_userList = u;
      } else {
        progress = 1;
        OfrontOPP_FixType(u->struct_, u->obj, u->base->typ, u->pos);
      }
      u = next;
    }
  } while (!(OfrontOPP_userList == NIL || !progress));
  u = OfrontOPP_userList;
  while (u != NIL) {
    if (u->obj == NIL || (INTEGER)u->obj->mode == 5) {
      OfrontOPM_Mark(58, u->pos);
    }
    u = u->next;
  }
}

static void OfrontOPP_CheckUnimpl (OfrontOPT_Object m, OfrontOPT_Struct typ, INTEGER pos)
{
  OfrontOPT_Object obj = NIL;
  OfrontOPS_String _ptr__21 = NIL;
  OfrontOPS_String _ptr__20 = NIL;
  OfrontOPS_String _ptr__19 = NIL;
  OfrontOPS_String _ptr__18 = NIL;
  if (m != NIL) {
    if ((INTEGER)m->mode == 13 && __IN(17, m->conval->setval)) {
      _ptr__21 = m->name;
      OfrontOPT_FindField((void*)_ptr__21->data, _ptr__21->len[0], typ, &obj);
      if ((obj == NIL || (INTEGER)obj->mode != 13) || __IN(17, obj->conval->setval)) {
        OfrontOPM_Mark(192, pos);
        OfrontOPM_LogWLn();
        OfrontOPM_LogWStr((CHAR*)"  ", 3);
        if (typ->strobj != NIL) {
          _ptr__20 = m->name;
          OfrontOPM_LogWStr((void*)_ptr__20->data, _ptr__20->len[0]);
          OfrontOPM_LogWStr((CHAR*)" not implemented in ", 21);
          _ptr__19 = typ->strobj->name;
          OfrontOPM_LogWStr((void*)_ptr__19->data, _ptr__19->len[0]);
        } else {
          _ptr__18 = m->name;
          OfrontOPM_LogWStr((void*)_ptr__18->data, _ptr__18->len[0]);
          OfrontOPM_LogWStr((CHAR*)" not implemented", 17);
        }
      }
    }
    OfrontOPP_CheckUnimpl(m->left, typ, pos);
    OfrontOPP_CheckUnimpl(m->right, typ, pos);
  }
}

static void OfrontOPP_CheckRecords (OfrontOPP_Elem rec)
{
  OfrontOPT_Struct b = NIL;
  while (rec != NIL) {
    b = rec->struct_->BaseTyp;
    while (b != NIL && b != OfrontOPT_undftyp) {
      OfrontOPP_CheckUnimpl(b->link, rec->struct_, rec->pos);
      b = b->BaseTyp;
    }
    rec = rec->next;
  }
}

static INTEGER OfrontOPP_Sign (LONGINT n)
{
  if (n == 0) {
    return 0;
  }
  if (n > 0) {
    return 1;
  }
  return -1;
}

static void OfrontOPP_err (SHORTINT n)
{
  OfrontOPM_err(n);
}

static void OfrontOPP_CheckSym (SHORTINT s)
{
  if ((INTEGER)OfrontOPP_sym == (INTEGER)s) {
    OfrontOPS_Get(&OfrontOPP_sym);
  } else if (OfrontOPM_Lang != '3' || (INTEGER)s != 41) {
    OfrontOPM_err(s);
  }
}

static void OfrontOPP_qualident (OfrontOPT_Object *id)
{
  OfrontOPT_Object obj = NIL;
  BYTE lev;
  OfrontOPT_Find((void*)OfrontOPS_name, 48, &obj);
  OfrontOPS_Get(&OfrontOPP_sym);
  if (((INTEGER)OfrontOPP_sym == 20 && obj != NIL) && (INTEGER)obj->mode == 11) {
    OfrontOPS_Get(&OfrontOPP_sym);
    if ((INTEGER)OfrontOPP_sym == 40) {
      OfrontOPT_FindImport(obj, &obj);
      OfrontOPS_Get(&OfrontOPP_sym);
    } else {
      OfrontOPP_err(40);
      obj = NIL;
    }
  }
  if (obj == NIL) {
    OfrontOPP_err(0);
    obj = OfrontOPT_NewObj();
    obj->mode = 1;
    obj->typ = OfrontOPT_undftyp;
    obj->adr = 0;
  } else {
    lev = obj->mnolev;
    if (__IN(obj->mode, 0x06) && (INTEGER)lev != (INTEGER)OfrontOPP_level) {
      obj->leaf = 0;
      if ((INTEGER)lev > 0) {
        OfrontOPB_StaticLink((BYTE)((INTEGER)OfrontOPP_level - (INTEGER)lev));
      }
    }
  }
  *id = obj;
}

static void OfrontOPP_ConstExpression (OfrontOPT_Node *x)
{
  OfrontOPP_Expression(x);
  if ((INTEGER)(*x)->class != 7) {
    OfrontOPP_err(50);
    *x = OfrontOPB_NewIntConst(1);
  }
}

static void OfrontOPP_CheckMark (OfrontOPT_Object obj)
{
  OfrontOPS_Get(&OfrontOPP_sym);
  if ((INTEGER)OfrontOPP_sym == 1 || (INTEGER)OfrontOPP_sym == 9) {
    if (((INTEGER)OfrontOPP_sym == 9 && OfrontOPT_SYSimported) && (INTEGER)obj->mode == 9) {
      obj->sysflag = -1;
    } else if ((OfrontOPM_Lang == '1' || OfrontOPM_Lang == '7') && (INTEGER)OfrontOPP_sym == 9) {
      OfrontOPP_err(48);
    } else if ((INTEGER)OfrontOPP_level > 0 || (!(__IN(obj->mode, 0x12) || ((INTEGER)obj->mode == 13 && OfrontOPM_Lang == 'C')) && (INTEGER)OfrontOPP_sym == 9)) {
      OfrontOPP_err(48);
    }
    if ((INTEGER)OfrontOPP_sym == 1 && !(OfrontOPM_Lang == '7' && (INTEGER)obj->mode == 1)) {
      obj->vis = 1;
    } else {
      obj->vis = 2;
    }
    OfrontOPS_Get(&OfrontOPP_sym);
  } else {
    obj->vis = 0;
  }
  if (__IN(obj->mode, 0xc2)) {
    if ((INTEGER)OfrontOPP_sym == 33) {
      OfrontOPS_Get(&OfrontOPP_sym);
      if ((INTEGER)obj->mnolev != 0) {
        OfrontOPP_err(48);
      } else if (!(OfrontOPT_SYSimported || __IN(14, OfrontOPM_opt))) {
        OfrontOPP_err(135);
      }
      if ((INTEGER)OfrontOPP_sym == 37 && (INTEGER)OfrontOPS_numtyp == 1) {
        obj->entry = __NEWARR(NIL, 1, 1, 1, 1, (SYSTEM_ARRLEN)2);
        (obj->entry->data)[0] = (CHAR)OfrontOPS_intval;
        (obj->entry->data)[__X(1, obj->entry->len[0], (CHAR*)"OfrontOPP", 89343)] = 0x00;
      } else if ((INTEGER)OfrontOPP_sym == 39) {
        if ((OfrontOPS_str->data)[0] != 0x00) {
          obj->entry = OfrontOPS_str;
        }
        OfrontOPS_Get(&OfrontOPP_sym);
      } else {
        OfrontOPP_err(39);
      }
      OfrontOPP_CheckSym(25);
    } else if (__IN(14, OfrontOPM_opt)) {
      obj->entry = obj->name;
    }
  }
}

static void OfrontOPP_CheckSysFlag (SHORTINT *sysflag, SHORTINT default_, BOOLEAN record)
{
  OfrontOPT_Node x = NIL;
  LONGINT sf;
  if ((INTEGER)OfrontOPP_sym == 33) {
    OfrontOPS_Get(&OfrontOPP_sym);
    if (!(OfrontOPT_SYSimported || __IN(14, OfrontOPM_opt))) {
      OfrontOPP_err(135);
    }
    if ((INTEGER)OfrontOPP_sym == 40 && (__STRCMPCC(OfrontOPS_name, (CHAR*)"notag", 6, (CHAR*)"OfrontOPP", 98310) == 0 || __STRCMPCC(OfrontOPS_name, (CHAR*)"untagged", 9, (CHAR*)"OfrontOPP", 98310) == 0)) {
      OfrontOPS_Get(&OfrontOPP_sym);
      *sysflag = 1;
    } else if ((record && (INTEGER)OfrontOPP_sym == 40) && __STRCMPCC(OfrontOPS_name, (CHAR*)"noalign", 8, (CHAR*)"OfrontOPP", 93951) == 0) {
      OfrontOPS_Get(&OfrontOPP_sym);
      *sysflag = 3;
    } else if ((record && (INTEGER)OfrontOPP_sym == 40) && __STRCMPCC(OfrontOPS_name, (CHAR*)"align2", 7, (CHAR*)"OfrontOPP", 94463) == 0) {
      OfrontOPS_Get(&OfrontOPP_sym);
      *sysflag = 4;
    } else if ((record && (INTEGER)OfrontOPP_sym == 40) && __STRCMPCC(OfrontOPS_name, (CHAR*)"align4", 7, (CHAR*)"OfrontOPP", 94975) == 0) {
      OfrontOPS_Get(&OfrontOPP_sym);
      *sysflag = 5;
    } else if ((record && (INTEGER)OfrontOPP_sym == 40) && __STRCMPCC(OfrontOPS_name, (CHAR*)"align8", 7, (CHAR*)"OfrontOPP", 95487) == 0) {
      OfrontOPS_Get(&OfrontOPP_sym);
      *sysflag = 6;
    } else if ((record && (INTEGER)OfrontOPP_sym == 40) && __STRCMPCC(OfrontOPS_name, (CHAR*)"union", 6, (CHAR*)"OfrontOPP", 95999) == 0) {
      OfrontOPS_Get(&OfrontOPP_sym);
      *sysflag = 7;
    } else {
      OfrontOPP_ConstExpression(&x);
      if (__IN(x->typ->form, 0x4072)) {
        sf = x->conval->intval;
        if (sf < 0 || sf > 1) {
          OfrontOPP_err(178);
          sf = 0;
        }
      } else {
        OfrontOPP_err(51);
        sf = 0;
      }
      *sysflag = (SHORTINT)sf;
    }
    OfrontOPP_CheckSym(25);
  } else {
    *sysflag = default_;
  }
}

static void OfrontOPP_CheckSysFlagVarPar (SHORTINT *sysflag)
{
  if ((INTEGER)OfrontOPP_sym == 33) {
    OfrontOPS_Get(&OfrontOPP_sym);
    if (!(OfrontOPT_SYSimported || __IN(14, OfrontOPM_opt))) {
      OfrontOPP_err(135);
    }
    if ((INTEGER)OfrontOPP_sym == 40 && __STRCMPCC(OfrontOPS_name, (CHAR*)"nil", 4, (CHAR*)"OfrontOPP", 101382) == 0) {
      OfrontOPS_Get(&OfrontOPP_sym);
      *sysflag = 1;
    } else {
      OfrontOPS_Get(&OfrontOPP_sym);
      OfrontOPP_err(178);
      *sysflag = 0;
    }
    OfrontOPP_CheckSym(25);
  } else {
    *sysflag = 0;
  }
}

static void OfrontOPP_CheckSysFlagProc (SHORTINT *sysflag, BOOLEAN checkinline)
{
  if ((INTEGER)OfrontOPP_sym == 33) {
    OfrontOPS_Get(&OfrontOPP_sym);
    if (!(OfrontOPT_SYSimported || __IN(14, OfrontOPM_opt))) {
      OfrontOPP_err(135);
    }
    if ((INTEGER)OfrontOPP_sym == 40 && __STRCMPCC(OfrontOPS_name, (CHAR*)"ccall", 6, (CHAR*)"OfrontOPP", 105222) == 0) {
      OfrontOPS_Get(&OfrontOPP_sym);
      *sysflag = 0;
    } else if ((INTEGER)OfrontOPP_sym == 40 && (__STRCMPCC(OfrontOPS_name, (CHAR*)"stdcall", 8, (CHAR*)"OfrontOPP", 104191) == 0 || __STRCMPCC(OfrontOPS_name, (CHAR*)"callback", 9, (CHAR*)"OfrontOPP", 104191) == 0)) {
      OfrontOPS_Get(&OfrontOPP_sym);
      *sysflag = 1;
    } else if ((INTEGER)OfrontOPP_sym == 40 && __STRCMPCC(OfrontOPS_name, (CHAR*)"fastcall", 9, (CHAR*)"OfrontOPP", 104447) == 0) {
      OfrontOPS_Get(&OfrontOPP_sym);
      *sysflag = 2;
    } else if (((INTEGER)OfrontOPP_sym == 40 && checkinline) && __STRCMPCC(OfrontOPS_name, (CHAR*)"inline", 7, (CHAR*)"OfrontOPP", 104703) == 0) {
      OfrontOPS_Get(&OfrontOPP_sym);
      *sysflag = 3;
    } else {
      OfrontOPS_Get(&OfrontOPP_sym);
      OfrontOPP_err(178);
      *sysflag = 0;
    }
    OfrontOPP_CheckSym(25);
  } else {
    *sysflag = 0;
  }
}

static void OfrontOPP_CheckOverwrite (OfrontOPT_Object proc, OfrontOPT_Object base, OfrontOPT_Struct rec)
{
  OfrontOPT_Object o = NIL;
  OfrontOPT_Object bo = NIL;
  if (base != NIL) {
    if ((base->conval->setval & 0x1a0000) == 0x0) {
      OfrontOPP_err(182);
    }
    if (((INTEGER)proc->link->mode != (INTEGER)base->link->mode || (INTEGER)proc->link->vis != (INTEGER)base->link->vis) || !OfrontOPT_Extends(proc->link->typ, base->link->typ)) {
      OfrontOPP_err(115);
    }
    o = proc->link;
    bo = base->link;
    while (o != NIL && bo != NIL) {
      if ((INTEGER)bo->sysflag != 0 && (INTEGER)o->sysflag == 0) {
        o->sysflag = bo->sysflag;
      }
      o = o->link;
      bo = bo->link;
    }
    OfrontOPB_CheckParameters(proc->link->link, base->link->link, 0);
    if (!OfrontOPT_Extends(proc->typ, base->typ)) {
      OfrontOPP_err(117);
    }
    if ((INTEGER)base->vis != (INTEGER)proc->vis && ((INTEGER)proc->vis != 0 || rec->exp)) {
      OfrontOPP_err(183);
    }
    proc->conval->setval |= __SETOF(2);
  }
}

static void OfrontOPP_GetAttributes (OfrontOPT_Object proc, OfrontOPT_Object base, OfrontOPT_Struct owner)
{
  SET attr, battr;
  OfrontOPT_Object o = NIL;
  attr = 0x0;
  if ((INTEGER)OfrontOPP_sym == 21) {
    OfrontOPS_Get(&OfrontOPP_sym);
    if ((INTEGER)OfrontOPP_sym == 40) {
      OfrontOPT_Find((void*)OfrontOPS_name, 48, &o);
      if ((o != NIL && (INTEGER)o->mode == 8) && o->adr == 1) {
        if (OfrontOPM_Lang == 'C') {
          attr |= __SETOF(16);
        } else {
          OfrontOPP_err(178);
        }
        OfrontOPS_Get(&OfrontOPP_sym);
        if ((INTEGER)OfrontOPP_sym == 21) {
          OfrontOPS_Get(&OfrontOPP_sym);
          if ((INTEGER)OfrontOPP_sym == 40) {
            OfrontOPT_Find((void*)OfrontOPS_name, 48, &o);
          } else {
            o = NIL;
            OfrontOPP_err(40);
          }
        } else {
          o = NIL;
        }
      }
      if (o != NIL) {
        if (((INTEGER)o->mode != 20 || o->adr == 18) || OfrontOPM_Lang != 'C') {
          OfrontOPP_err(178);
        } else {
          attr |= __SETOF(o->adr);
        }
        OfrontOPS_Get(&OfrontOPP_sym);
      }
    } else {
      OfrontOPP_err(40);
    }
  }
  if (base == NIL && !__IN(16, attr)) {
    attr |= __SETOF(16);
    if (OfrontOPM_Lang == 'C') {
      OfrontOPP_err(185);
    }
  } else if (base != NIL && __IN(16, attr)) {
    OfrontOPP_err(186);
  }
  if (OfrontOPM_Lang == '2' || OfrontOPM_Lang == '3') {
    attr |= __SETOF(20);
  }
  if (__IN(17, attr)) {
    if ((INTEGER)owner->attribute != 17) {
      OfrontOPP_err(190);
    }
    if ((INTEGER)proc->vis == 0 && owner->exp) {
      OfrontOPP_err(179);
    }
  }
  if ((INTEGER)owner->attribute == 0 || (INTEGER)owner->attribute == 18) {
    if (__IN(19, attr) && __IN(16, attr)) {
      OfrontOPP_err(187);
    }
  }
  if (base != NIL) {
    battr = base->conval->setval;
    if (__IN(19, battr)) {
      if (__IN(17, attr)) {
        OfrontOPP_err(189);
      }
    } else if (!__IN(17, battr)) {
      if (__IN(17, attr) || __IN(19, attr)) {
        OfrontOPP_err(189);
      }
    }
  }
  if (__IN(19, attr)) {
    if (proc->typ != OfrontOPT_notyp) {
      OfrontOPP_err(195);
    } else {
      o = proc->link;
      while (o != NIL && (INTEGER)o->vis != 4) {
        o = o->link;
      }
      if (o != NIL) {
        OfrontOPP_err(195);
      }
    }
  }
  proc->conval->setval = attr;
}

static void OfrontOPP_RecordType (OfrontOPT_Struct *typ, OfrontOPT_Object attr)
{
  OfrontOPT_Object fld = NIL;
  OfrontOPT_Object first = NIL;
  OfrontOPT_Object last = NIL;
  OfrontOPP_Elem r = NIL;
  OfrontOPT_Struct ftyp = NIL;
  OfrontOPS_String name = NIL;
  *typ = OfrontOPT_NewStr(16, 4);
  (*typ)->BaseTyp = NIL;
  if (OfrontOPM_Lang != 'C') {
    (*typ)->attribute = 20;
  }
  OfrontOPP_CheckSysFlag(&(*typ)->sysflag, 0, 1);
  if ((INTEGER)(*typ)->sysflag == 0 && __IN(14, OfrontOPM_opt)) {
    (*typ)->sysflag = 1;
  }
  if (attr != NIL) {
    if (OfrontOPM_Lang == 'C' && attr->adr != 19) {
      (*typ)->attribute = (BYTE)attr->adr;
    } else {
      OfrontOPP_err(178);
    }
  }
  if ((INTEGER)OfrontOPP_sym == 32) {
    OfrontOPS_Get(&OfrontOPP_sym);
    if ((INTEGER)OfrontOPP_sym == 40) {
      OfrontOPP_Type(&ftyp, &name);
      if ((INTEGER)ftyp->form == 13) {
        ftyp = ftyp->BaseTyp;
      }
      OfrontOPP_SetType(*typ, NIL, ftyp, name);
      if ((INTEGER)ftyp->comp == 4 && ftyp != OfrontOPT_anytyp) {
        ftyp->pvused = 1;
        (*typ)->extlev = (BYTE)((INTEGER)ftyp->extlev + 1);
        if ((INTEGER)ftyp->attribute == 0 || ((INTEGER)ftyp->attribute == 18 && (INTEGER)ftyp->mno != 0)) {
          OfrontOPP_err(181);
        } else if ((INTEGER)(*typ)->attribute == 17 && (INTEGER)ftyp->attribute != 17) {
          OfrontOPP_err(191);
        } else if ((INTEGER)ftyp->attribute == 18 && (INTEGER)(*typ)->attribute != 18) {
          OfrontOPP_err(197);
        }
      } else if (ftyp != OfrontOPT_undftyp) {
        OfrontOPP_err(53);
      }
    } else {
      OfrontOPP_err(40);
    }
    if ((INTEGER)(*typ)->attribute != 17) {
      __NEW(r, OfrontOPP_Elem__rec);
      r->struct_ = *typ;
      r->pos = OfrontOPM_errpos;
      r->next = OfrontOPP_recList;
      OfrontOPP_recList = r;
    }
    OfrontOPP_CheckSym(24);
  }
  OfrontOPT_OpenScope(0, NIL);
  first = NIL;
  last = NIL;
  for (;;) {
    if ((INTEGER)OfrontOPP_sym == 40) {
      for (;;) {
        if ((INTEGER)OfrontOPP_sym == 40) {
          if ((*typ)->BaseTyp != NIL && (*typ)->BaseTyp != OfrontOPT_undftyp) {
            OfrontOPT_FindBaseField((void*)OfrontOPS_name, 48, *typ, &fld);
            if (fld != NIL) {
              OfrontOPP_err(1);
            }
          }
          OfrontOPT_Insert((void*)OfrontOPS_name, 48, &fld);
          fld->mode = 4;
          fld->link = NIL;
          fld->typ = OfrontOPT_undftyp;
          OfrontOPP_CheckMark(fld);
          if (first == NIL) {
            first = fld;
          }
          if (last == NIL) {
            (*typ)->link = fld;
          } else {
            last->link = fld;
          }
          last = fld;
        } else {
          OfrontOPP_err(40);
        }
        if ((INTEGER)OfrontOPP_sym == 21) {
          OfrontOPS_Get(&OfrontOPP_sym);
        } else if ((INTEGER)OfrontOPP_sym == 40) {
          OfrontOPP_err(21);
        } else {
          break;
        }
      }
      OfrontOPP_CheckSym(22);
      OfrontOPP_Type(&ftyp, &name);
      OfrontOPP_CheckAlloc(&ftyp, 0, OfrontOPM_errpos);
      while (first != NIL) {
        OfrontOPP_SetType(*typ, first, ftyp, name);
        first = first->link;
      }
    }
    if ((INTEGER)OfrontOPP_sym == 41) {
      OfrontOPS_Get(&OfrontOPP_sym);
    } else if ((INTEGER)OfrontOPP_sym == 40) {
      OfrontOPP_err(41);
    } else {
      break;
    }
  }
  OfrontOPT_CloseScope();
  OfrontOPB_Inittd(&OfrontOPP_TDinit, &OfrontOPP_lastTDinit, *typ);
  OfrontOPP_CheckSym(43);
}

static void OfrontOPP_ArrayType (OfrontOPT_Struct *typ)
{
  OfrontOPT_Node x = NIL;
  LONGINT n;
  SHORTINT sysflag;
  OfrontOPS_String name = NIL;
  OfrontOPP_CheckSysFlag(&sysflag, 0, 0);
  if ((INTEGER)OfrontOPP_sym == 27) {
    *typ = OfrontOPT_NewStr(16, 3);
    (*typ)->mno = 0;
    (*typ)->sysflag = sysflag;
    OfrontOPS_Get(&OfrontOPP_sym);
    OfrontOPP_Type(&(*typ)->BaseTyp, &name);
    OfrontOPP_SetType(*typ, NIL, (*typ)->BaseTyp, name);
    OfrontOPP_CheckAlloc(&(*typ)->BaseTyp, 1, OfrontOPM_errpos);
    if ((INTEGER)(*typ)->BaseTyp->comp == 3) {
      (*typ)->n = (*typ)->BaseTyp->n + 1;
    } else {
      (*typ)->n = 0;
    }
  } else {
    *typ = OfrontOPT_NewStr(16, 2);
    (*typ)->sysflag = sysflag;
    OfrontOPP_ConstExpression(&x);
    if (__IN(x->typ->form, 0x4072)) {
      n = x->conval->intval;
      if (n <= 0 || n > OfrontOPM_MaxIndex) {
        OfrontOPP_err(63);
        n = 1;
      }
    } else {
      OfrontOPP_err(51);
      n = 1;
    }
    (*typ)->n = (INTEGER)n;
    if ((INTEGER)OfrontOPP_sym == 27) {
      OfrontOPS_Get(&OfrontOPP_sym);
      OfrontOPP_Type(&(*typ)->BaseTyp, &name);
      OfrontOPP_SetType(*typ, NIL, (*typ)->BaseTyp, name);
      OfrontOPP_CheckAlloc(&(*typ)->BaseTyp, 0, OfrontOPM_errpos);
    } else if ((INTEGER)OfrontOPP_sym == 21) {
      OfrontOPS_Get(&OfrontOPP_sym);
      if ((INTEGER)OfrontOPP_sym != 27) {
        OfrontOPP_ArrayType(&(*typ)->BaseTyp);
      }
    } else {
      OfrontOPP_err(35);
    }
    if ((INTEGER)(*typ)->BaseTyp->comp == 3) {
      (*typ)->BaseTyp = OfrontOPT_undftyp;
      OfrontOPP_err(88);
    }
  }
}

static void OfrontOPP_PointerType (OfrontOPT_Struct *typ)
{
  OfrontOPS_String name = NIL;
  *typ = OfrontOPT_NewStr(13, 1);
  OfrontOPP_CheckSysFlag(&(*typ)->sysflag, 0, 0);
  OfrontOPP_CheckSym(30);
  OfrontOPP_Type(&(*typ)->BaseTyp, &name);
  OfrontOPP_SetType(*typ, NIL, (*typ)->BaseTyp, name);
  if ((*typ)->BaseTyp != OfrontOPT_undftyp && (INTEGER)(*typ)->BaseTyp->comp == 1) {
    (*typ)->BaseTyp = OfrontOPT_undftyp;
    OfrontOPP_err(57);
  }
}

static void OfrontOPP_FormalParameters (OfrontOPT_Object *firstPar, OfrontOPT_Struct *resTyp, OfrontOPS_String *name)
{
  BYTE mode, vis;
  SHORTINT sys;
  OfrontOPT_Object par = NIL;
  OfrontOPT_Object first = NIL;
  OfrontOPT_Object last = NIL;
  OfrontOPT_Struct typ = NIL;
  INTEGER errpos;
  first = NIL;
  last = *firstPar;
  if (((INTEGER)OfrontOPP_sym == 40 || (INTEGER)OfrontOPP_sym == 62) || (OfrontOPM_Lang == 'C' && ((INTEGER)OfrontOPP_sym == 17 || (INTEGER)OfrontOPP_sym == 66))) {
    for (;;) {
      sys = 0;
      vis = 0;
      if ((INTEGER)OfrontOPP_sym == 62) {
        OfrontOPS_Get(&OfrontOPP_sym);
        mode = 2;
      } else if ((INTEGER)OfrontOPP_sym == 17 && OfrontOPM_Lang == 'C') {
        OfrontOPS_Get(&OfrontOPP_sym);
        mode = 2;
        vis = 3;
      } else if ((INTEGER)OfrontOPP_sym == 66 && OfrontOPM_Lang == 'C') {
        OfrontOPS_Get(&OfrontOPP_sym);
        mode = 2;
        vis = 4;
      } else {
        mode = 1;
      }
      if ((INTEGER)mode == 2) {
        OfrontOPP_CheckSysFlagVarPar(&sys);
      }
      errpos = -1;
      for (;;) {
        if ((INTEGER)OfrontOPP_sym == 40) {
          OfrontOPT_Insert((void*)OfrontOPS_name, 48, &par);
          OfrontOPS_Get(&OfrontOPP_sym);
          if (((INTEGER)OfrontOPP_sym == 9 && OfrontOPM_Lang <= '2') && (INTEGER)mode != 2) {
            OfrontOPS_Get(&OfrontOPP_sym);
            par->mode = 2;
            par->vis = 3;
            if (!__IN(17, OfrontOPM_opt)) {
              OfrontOPP_err(-304);
            }
            if (errpos == -1) {
              errpos = OfrontOPM_errpos;
            }
          } else {
            par->mode = mode;
            par->vis = vis;
          }
          par->link = NIL;
          par->sysflag = (BYTE)sys;
          if (first == NIL) {
            first = par;
          }
          if (*firstPar == NIL) {
            *firstPar = par;
          } else {
            last->link = par;
          }
          last = par;
        } else {
          OfrontOPP_err(40);
        }
        if ((INTEGER)OfrontOPP_sym == 21) {
          OfrontOPS_Get(&OfrontOPP_sym);
        } else if ((INTEGER)OfrontOPP_sym == 40) {
          OfrontOPP_err(21);
        } else if ((INTEGER)OfrontOPP_sym == 62) {
          OfrontOPP_err(21);
          OfrontOPS_Get(&OfrontOPP_sym);
        } else {
          break;
        }
      }
      OfrontOPP_CheckSym(22);
      OfrontOPP_Type(&typ, name);
      if ((INTEGER)mode != 2) {
        OfrontOPP_CheckAlloc(&typ, 1, OfrontOPM_errpos);
      }
      if (((errpos != -1 && (INTEGER)typ->form != 0) && (INTEGER)typ->form != 16) && (INTEGER)typ->sysflag == 0) {
        OfrontOPM_Mark(177, errpos);
      } else if (((((INTEGER)mode == 2 && (INTEGER)vis == 3) && (INTEGER)typ->form != 0) && (INTEGER)typ->form != 16) && (INTEGER)typ->sysflag == 0) {
        OfrontOPP_err(177);
      } else if ((__MASK((INTEGER)sys, -256) != 0 && ((INTEGER)typ->comp == 4 || (INTEGER)typ->comp == 3)) && __MASK((INTEGER)typ->sysflag, -256) == 0) {
        OfrontOPP_err(142);
      } else if (((INTEGER)mode == 1 && (INTEGER)typ->comp == 3) && __ODD(typ->sysflag)) {
        OfrontOPM_err(145);
      }
      if (((INTEGER)mode == 1 && (INTEGER)typ->form == 16) && (OfrontOPM_Lang == '3' || OfrontOPM_Lang == '7')) {
        par = first;
        while (par != NIL) {
          par->mode = 2;
          par->vis = 3;
          par = par->link;
        }
      }
      while (first != NIL) {
        OfrontOPP_SetType(NIL, first, typ, *name);
        first = first->link;
      }
      if ((INTEGER)OfrontOPP_sym == 41) {
        OfrontOPS_Get(&OfrontOPP_sym);
      } else if ((INTEGER)OfrontOPP_sym == 40) {
        OfrontOPP_err(41);
      } else {
        break;
      }
    }
  }
  OfrontOPP_CheckSym(24);
  *name = NIL;
  if ((INTEGER)OfrontOPP_sym == 22) {
    OfrontOPS_Get(&OfrontOPP_sym);
    OfrontOPP_Type(resTyp, name);
    if ((INTEGER)(*resTyp)->form == 16) {
      *resTyp = OfrontOPT_undftyp;
      OfrontOPP_err(54);
    }
  } else {
    *resTyp = OfrontOPT_notyp;
  }
}

static void OfrontOPP_Type (OfrontOPT_Struct *typ, OfrontOPS_String *name)
{
  OfrontOPT_Object id = NIL;
  OfrontOPS_String tname = NIL;
  *typ = OfrontOPT_undftyp;
  *name = NIL;
  if ((INTEGER)OfrontOPP_sym < 32) {
    OfrontOPP_err(12);
    do {
      OfrontOPS_Get(&OfrontOPP_sym);
    } while (!((INTEGER)OfrontOPP_sym >= 32));
  }
  if ((INTEGER)OfrontOPP_sym == 40) {
    OfrontOPT_Find((void*)OfrontOPS_name, 48, &id);
    if ((id == NIL || (INTEGER)id->mode == -1) || ((INTEGER)id->mode == 5 && OfrontOPP_IncompleteType(id->typ))) {
      *name = OfrontOPT_NewName((void*)OfrontOPS_name, 48);
      OfrontOPS_Get(&OfrontOPP_sym);
      if (id == NIL && (INTEGER)OfrontOPP_sym == 20) {
        OfrontOPP_err(0);
        OfrontOPS_Get(&OfrontOPP_sym);
        *name = NIL;
        if ((INTEGER)OfrontOPP_sym == 40) {
          OfrontOPS_Get(&OfrontOPP_sym);
        }
      } else if ((INTEGER)OfrontOPP_sym == 57) {
        OfrontOPP_err(178);
        OfrontOPS_Get(&OfrontOPP_sym);
        *name = NIL;
        OfrontOPP_RecordType(typ, NIL);
      }
    } else {
      OfrontOPP_qualident(&id);
      if ((INTEGER)id->mode == 5) {
        *typ = id->typ;
      } else if ((INTEGER)id->mode == 20) {
        if ((INTEGER)OfrontOPP_sym == 57) {
          OfrontOPS_Get(&OfrontOPP_sym);
          OfrontOPP_RecordType(typ, id);
        } else {
          OfrontOPP_err(12);
        }
      } else {
        OfrontOPP_err(52);
      }
    }
  } else if ((INTEGER)OfrontOPP_sym == 56) {
    OfrontOPS_Get(&OfrontOPP_sym);
    OfrontOPP_ArrayType(typ);
  } else if ((INTEGER)OfrontOPP_sym == 57) {
    OfrontOPS_Get(&OfrontOPP_sym);
    OfrontOPP_RecordType(typ, NIL);
  } else if ((INTEGER)OfrontOPP_sym == 58) {
    OfrontOPS_Get(&OfrontOPP_sym);
    OfrontOPP_PointerType(typ);
  } else if ((INTEGER)OfrontOPP_sym == 63) {
    OfrontOPS_Get(&OfrontOPP_sym);
    *typ = OfrontOPT_NewStr(15, 1);
    OfrontOPP_CheckSysFlagProc(&(*typ)->sysflag, 0);
    if ((INTEGER)OfrontOPP_sym == 32) {
      OfrontOPS_Get(&OfrontOPP_sym);
      OfrontOPT_OpenScope(OfrontOPP_level, NIL);
      OfrontOPP_FormalParameters(&(*typ)->link, &(*typ)->BaseTyp, &tname);
      OfrontOPP_SetType(*typ, NIL, (*typ)->BaseTyp, tname);
      OfrontOPT_CloseScope();
    } else {
      (*typ)->BaseTyp = OfrontOPT_notyp;
      (*typ)->link = NIL;
    }
  } else {
    OfrontOPP_err(12);
  }
  for (;;) {
    if (((((((INTEGER)OfrontOPP_sym >= 41 && (INTEGER)OfrontOPP_sym <= 63) || (INTEGER)OfrontOPP_sym == 24) || (INTEGER)OfrontOPP_sym == 71) || (INTEGER)OfrontOPP_sym == 37) || (INTEGER)OfrontOPP_sym == 21) || (INTEGER)OfrontOPP_sym == 39) {
      break;
    }
    OfrontOPP_err(15);
    if ((INTEGER)OfrontOPP_sym == 40) {
      break;
    }
    OfrontOPS_Get(&OfrontOPP_sym);
  }
}

static void OfrontOPP_ActualParameters (OfrontOPT_Node *aparlist, OfrontOPT_Object fpar, OfrontOPT_Node *pre, OfrontOPT_Node *lastp)
{
  OfrontOPT_Node apar = NIL;
  OfrontOPT_Node last = NIL;
  OfrontOPT_Node n = NIL;
  *aparlist = NIL;
  last = NIL;
  if ((INTEGER)OfrontOPP_sym != 24) {
    for (;;) {
      if (OfrontOPM_Lang == '3' && fpar != NIL) {
        if ((INTEGER)fpar->mode == 2 && (INTEGER)fpar->vis != 3) {
          if ((INTEGER)OfrontOPP_sym == 69) {
            OfrontOPS_Get(&OfrontOPP_sym);
          } else {
            OfrontOPP_err(42);
          }
        } else if ((INTEGER)OfrontOPP_sym == 69) {
          OfrontOPS_Get(&OfrontOPP_sym);
          OfrontOPP_err(39);
        }
      }
      OfrontOPP_Expression(&apar);
      if (fpar != NIL) {
        if ((OfrontOPM_Lang == 'C' && (INTEGER)apar->typ->form == 13) && (INTEGER)fpar->typ->form == 16) {
          OfrontOPB_DeRef(&apar);
        }
        OfrontOPB_Param(&apar, fpar);
        if ((INTEGER)fpar->mode == 1 || (INTEGER)fpar->vis == 3) {
          OfrontOPB_CheckBuffering(&apar, NIL, fpar, pre, lastp);
        }
        OfrontOPB_Link(aparlist, &last, apar);
        if ((INTEGER)fpar->mode == 2 && ((((INTEGER)fpar->mode == 2 && (INTEGER)fpar->typ->comp == 4) && __MASK((INTEGER)fpar->typ->sysflag, -256) == 0) || ((INTEGER)fpar->typ->comp == 3 && (INTEGER)fpar->typ->sysflag == 0))) {
          n = apar;
          while (__IN(n->class, 0x34)) {
            n = n->left;
          }
          if ((INTEGER)n->class == 3 && (INTEGER)n->subcl == 0) {
            if ((INTEGER)n->left->class == 5) {
              n = n->left;
            }
            OfrontOPB_CheckVarParBuffering(&n->left, pre, lastp);
          }
        }
        fpar = fpar->link;
      } else {
        OfrontOPP_err(64);
      }
      if ((INTEGER)OfrontOPP_sym == 21) {
        OfrontOPS_Get(&OfrontOPP_sym);
      } else if (32 <= (INTEGER)OfrontOPP_sym && (INTEGER)OfrontOPP_sym <= 40) {
        OfrontOPP_err(21);
      } else {
        break;
      }
    }
  }
  if (fpar != NIL) {
    OfrontOPP_err(65);
  }
}

static void OfrontOPP_selector (OfrontOPT_Node *x)
{
  OfrontOPT_Object obj = NIL;
  OfrontOPT_Object proc = NIL;
  OfrontOPT_Object p = NIL;
  OfrontOPT_Object fpar = NIL;
  OfrontOPT_Node y = NIL;
  OfrontOPT_Node apar = NIL;
  OfrontOPT_Node pre = NIL;
  OfrontOPT_Node lastp = NIL;
  OfrontOPT_Struct typ = NIL;
  OfrontOPS_Name name;
  OfrontOPS_String _ptr__80 = NIL;
  for (;;) {
    if ((INTEGER)OfrontOPP_sym == 33) {
      OfrontOPS_Get(&OfrontOPP_sym);
      for (;;) {
        if ((*x)->typ != NIL && (INTEGER)(*x)->typ->form == 13) {
          OfrontOPB_DeRef(x);
        }
        OfrontOPP_Expression(&y);
        OfrontOPB_Index(x, y);
        if ((INTEGER)OfrontOPP_sym == 21) {
          OfrontOPS_Get(&OfrontOPP_sym);
        } else {
          break;
        }
      }
      OfrontOPP_CheckSym(25);
    } else if ((INTEGER)OfrontOPP_sym == 20) {
      OfrontOPS_Get(&OfrontOPP_sym);
      if ((INTEGER)OfrontOPP_sym == 40) {
        __MOVE(OfrontOPS_name, name, 48);
        OfrontOPS_Get(&OfrontOPP_sym);
        if ((*x)->typ != NIL) {
          if ((INTEGER)(*x)->typ->form == 13) {
            OfrontOPB_DeRef(x);
          }
          if ((INTEGER)(*x)->typ->comp == 4) {
            typ = (*x)->typ;
            OfrontOPT_FindField((void*)name, 48, (*x)->typ, &obj);
            OfrontOPB_Field(x, obj);
            if (obj != NIL && (INTEGER)obj->mode == 13) {
              if ((INTEGER)OfrontOPP_sym == 19) {
                OfrontOPS_Get(&OfrontOPP_sym);
                y = (*x)->left;
                if ((INTEGER)y->class == 3) {
                  y = y->left;
                }
                if (y->obj != NIL) {
                  proc = OfrontOPT_topScope;
                  while (proc->link != NIL && (INTEGER)proc->link->mode != 13) {
                    proc = proc->left;
                  }
                  if (proc->link == NIL || proc->link->link != y->obj) {
                    OfrontOPP_err(75);
                  }
                  typ = y->obj->typ;
                  if ((INTEGER)typ->form == 13) {
                    typ = typ->BaseTyp;
                  }
                  _ptr__80 = (*x)->obj->name;
                  OfrontOPT_FindBaseField((void*)_ptr__80->data, _ptr__80->len[0], typ, &p);
                  if (p != NIL) {
                    (*x)->subcl = 1;
                    (*x)->typ = p->typ;
                    if ((p->conval->setval & 0x0a0000) != 0x0) {
                      OfrontOPP_err(194);
                    }
                    if (((INTEGER)p->vis == 2 && (INTEGER)p->mnolev < 0) && __STRCMPCC(proc->link->name->data, name, 48, (CHAR*)"OfrontOPP", 204287) != 0) {
                      OfrontOPP_err(196);
                    }
                  } else {
                    OfrontOPP_err(74);
                  }
                } else {
                  OfrontOPP_err(75);
                }
              } else {
                proc = obj;
                if (((*x)->left->readonly && (INTEGER)proc->link->mode == 2) && (INTEGER)proc->link->vis == 0) {
                  OfrontOPP_err(76);
                }
                while (((INTEGER)proc->mnolev >= 0 && !__IN(16, proc->conval->setval)) && typ->BaseTyp != NIL) {
                  typ = typ->BaseTyp;
                  OfrontOPT_FindField((void*)name, 48, typ, &proc);
                }
                if ((INTEGER)proc->vis == 2 && (INTEGER)proc->mnolev < 0) {
                  OfrontOPP_err(196);
                }
              }
              if (obj->typ != OfrontOPT_notyp && (INTEGER)OfrontOPP_sym != 32) {
                OfrontOPP_err(32);
              }
            }
          } else {
            OfrontOPP_err(53);
          }
        } else {
          OfrontOPP_err(52);
        }
      } else {
        OfrontOPP_err(40);
      }
    } else if ((INTEGER)OfrontOPP_sym == 19) {
      OfrontOPS_Get(&OfrontOPP_sym);
      OfrontOPB_DeRef(x);
    } else if ((INTEGER)OfrontOPP_sym == 67 && (OfrontOPM_Lang == 'C' || OfrontOPM_Lang == '3')) {
      if (OfrontOPM_Lang == 'C' && (INTEGER)(*x)->typ->form == 13) {
        OfrontOPB_DeRef(x);
      }
      OfrontOPS_Get(&OfrontOPP_sym);
      OfrontOPB_StrDeref(x);
    } else if ((INTEGER)OfrontOPP_sym == 32) {
      if ((*x)->obj != NIL && __IN((*x)->obj->mode, 0x22c0)) {
        typ = (*x)->obj->typ;
      } else if ((INTEGER)(*x)->typ->form == 15) {
        typ = (*x)->typ->BaseTyp;
      } else if (__IN((*x)->class, 0x0300)) {
        break;
      } else {
        typ = NIL;
      }
      if (typ != OfrontOPT_notyp) {
        OfrontOPS_Get(&OfrontOPP_sym);
        if (typ == NIL) {
          if (OfrontOPM_Lang == '3') {
            OfrontOPP_CheckSym(22);
          }
          if ((INTEGER)OfrontOPP_sym == 40) {
            OfrontOPP_qualident(&obj);
            if ((INTEGER)obj->mode == 5) {
              OfrontOPB_TypTest(x, obj, 1);
            } else {
              OfrontOPP_err(52);
            }
          } else {
            OfrontOPP_err(40);
          }
          OfrontOPP_CheckSym(24);
        } else {
          pre = NIL;
          lastp = NIL;
          OfrontOPB_PrepCall(x, &fpar);
          if ((*x)->obj != NIL && (INTEGER)(*x)->obj->mode == 13) {
            OfrontOPB_CheckBuffering(&(*x)->left, NIL, (*x)->obj->link, &pre, &lastp);
          }
          OfrontOPP_ActualParameters(&apar, fpar, &pre, &lastp);
          OfrontOPB_Call(x, apar, fpar);
          if (pre != NIL) {
            OfrontOPB_Construct(29, &pre, *x);
            pre->typ = (*x)->typ;
            *x = pre;
          }
          if ((INTEGER)OfrontOPP_level > 0) {
            OfrontOPT_topScope->link->leaf = 0;
          }
          OfrontOPP_CheckSym(24);
          if ((OfrontOPM_Lang != '3' && OfrontOPM_Lang != 'C') && ((INTEGER)OfrontOPP_sym == 19 || (INTEGER)OfrontOPP_sym == 20)) {
            OfrontOPP_err(126);
          }
        }
      } else {
        break;
      }
    } else {
      break;
    }
  }
}

static void OfrontOPP_StandProcCall (OfrontOPT_Node *x)
{
  OfrontOPT_Node y = NIL;
  BYTE m;
  SHORTINT n;
  m = (BYTE)(*x)->obj->adr;
  n = 0;
  if ((INTEGER)OfrontOPP_sym == 32) {
    OfrontOPS_Get(&OfrontOPP_sym);
    if ((INTEGER)OfrontOPP_sym != 24) {
      for (;;) {
        if ((INTEGER)n == 0) {
          if (OfrontOPM_Lang == '3') {
            switch (m) {
              case 1: case 19: case 20: case 21: case 22: 
              case 32: case 33: case 36: 
                if ((INTEGER)OfrontOPP_sym == 69) {
                  OfrontOPS_Get(&OfrontOPP_sym);
                } else {
                  OfrontOPP_err(42);
                }
                break;
              default: 
                break;
            }
          }
          OfrontOPP_Expression(x);
          OfrontOPB_StPar0(x, m);
          n = 1;
        } else if ((INTEGER)n == 1) {
          if (OfrontOPM_Lang == '3') {
            switch (m) {
              case 24: case 30: case 33: 
                if ((INTEGER)OfrontOPP_sym == 69) {
                  OfrontOPS_Get(&OfrontOPP_sym);
                } else {
                  OfrontOPP_err(42);
                }
                break;
              default: 
                break;
            }
          }
          OfrontOPP_Expression(&y);
          OfrontOPB_StPar1(x, y, m);
          n = 2;
        } else {
          OfrontOPP_Expression(&y);
          OfrontOPB_StParN(x, y, m, n);
          n += 1;
        }
        if ((INTEGER)OfrontOPP_sym == 21) {
          OfrontOPS_Get(&OfrontOPP_sym);
        } else if (32 <= (INTEGER)OfrontOPP_sym && (INTEGER)OfrontOPP_sym <= 40) {
          OfrontOPP_err(21);
        } else {
          break;
        }
      }
      OfrontOPP_CheckSym(24);
    } else {
      OfrontOPS_Get(&OfrontOPP_sym);
    }
    OfrontOPB_StFct(x, m, n);
  } else {
    OfrontOPP_err(32);
  }
  if ((INTEGER)OfrontOPP_level > 0 && ((INTEGER)m == 1 || (INTEGER)m == 36)) {
    OfrontOPT_topScope->link->leaf = 0;
  }
}

static void OfrontOPP_Element (OfrontOPT_Node *x)
{
  OfrontOPT_Node y = NIL;
  OfrontOPP_Expression(x);
  if ((INTEGER)OfrontOPP_sym == 23) {
    OfrontOPS_Get(&OfrontOPP_sym);
    OfrontOPP_Expression(&y);
    OfrontOPB_SetRange(x, y);
  } else {
    OfrontOPB_SetElem(x);
  }
}

static void OfrontOPP_Sets (OfrontOPT_Node *x)
{
  OfrontOPT_Node y = NIL;
  if ((INTEGER)OfrontOPP_sym != 26) {
    OfrontOPP_Element(x);
    for (;;) {
      if ((INTEGER)OfrontOPP_sym == 21) {
        OfrontOPS_Get(&OfrontOPP_sym);
      } else if (32 <= (INTEGER)OfrontOPP_sym && (INTEGER)OfrontOPP_sym <= 40) {
        OfrontOPP_err(21);
      } else {
        break;
      }
      OfrontOPP_Element(&y);
      OfrontOPB_Op(8, x, y);
    }
  } else {
    *x = OfrontOPB_EmptySet();
  }
  OfrontOPP_CheckSym(26);
}

static void OfrontOPP_String2Chars (OfrontOPT_Node a, OfrontOPT_Node *x)
{
  INTEGER i, _for__74;
  _for__74 = a->conval->intval2 - 1;
  i = 0;
  while (i <= _for__74) {
    if ((*x)->conval->intval + (LONGINT)i < (LONGINT)(*x)->conval->arr->val1->len[0]) {
      ((*x)->conval->arr->val1->data)[__X((*x)->conval->intval + (LONGINT)i, (*x)->conval->arr->val1->len[0], (CHAR*)"OfrontOPP", 237567)] = (BYTE)(a->conval->ext->data)[__X(i, a->conval->ext->len[0], (CHAR*)"OfrontOPP", 237567)];
    } else {
      OfrontOPP_err(64);
    }
    i += 1;
  }
}

static void OfrontOPP_ConstArray (OfrontOPT_Node *x, OfrontOPT_Struct typ)
{
  OfrontOPT_Node apar = NIL;
  INTEGER n, i;
  OfrontOPT_Object fp = NIL;
  OfrontOPT_ConstArr y = NIL;
  if ((INTEGER)OfrontOPP_sym != 32 && __IN(typ->BaseTyp->form, 0x020008)) {
    OfrontOPP_ConstExpression(&apar);
    if (((INTEGER)apar->typ->comp == 1 && __IN(apar->typ->form, 0x040400)) && apar->conval->intval2 <= typ->n) {
      OfrontOPP_String2Chars(apar, x);
      (*x)->conval->intval += typ->n;
    } else if ((INTEGER)apar->typ->comp == 1 && __IN(apar->typ->form, 0x020008)) {
      if ((*x)->conval->intval < (LONGINT)(*x)->conval->arr->val1->len[0]) {
        ((*x)->conval->arr->val1->data)[__X((*x)->conval->intval, (*x)->conval->arr->val1->len[0], (CHAR*)"OfrontOPP", 242264)] = (BYTE)apar->conval->intval;
        (*x)->conval->intval += typ->n;
      } else {
        OfrontOPP_err(64);
      }
    } else {
      OfrontOPP_err(63);
    }
  } else {
    OfrontOPP_CheckSym(32);
    n = typ->n;
    i = 0;
    if (__IN(typ->BaseTyp->form, 0x02407e)) {
      y = (*x)->conval->arr;
      fp = OfrontOPT_NewObj();
      fp->typ = typ->BaseTyp;
      fp->mode = 1;
      if ((INTEGER)OfrontOPP_sym != 24) {
        for (;;) {
          OfrontOPP_ConstExpression(&apar);
          if (i < n) {
            if ((((i == 0 && __IN(typ->BaseTyp->form, 0x02000a)) && (INTEGER)apar->typ->comp == 1) && __IN(apar->typ->form, 0x040400)) && apar->conval->intval2 <= typ->n) {
              OfrontOPP_String2Chars(apar, x);
            } else {
              OfrontOPB_Param(&apar, fp);
              switch (fp->typ->size) {
                case 1: 
                  if ((*x)->conval->intval + (LONGINT)i < (LONGINT)y->val1->len[0]) {
                    (y->val1->data)[__X((*x)->conval->intval + (LONGINT)i, y->val1->len[0], (CHAR*)"OfrontOPP", 249855)] = (BYTE)apar->conval->intval;
                  } else {
                    OfrontOPP_err(64);
                  }
                  break;
                case 2: 
                  if ((*x)->conval->intval + (LONGINT)i < (LONGINT)y->val2->len[0]) {
                    (y->val2->data)[__X((*x)->conval->intval + (LONGINT)i, y->val2->len[0], (CHAR*)"OfrontOPP", 250879)] = (SHORTINT)apar->conval->intval;
                  } else {
                    OfrontOPP_err(64);
                  }
                  break;
                case 4: 
                  if ((*x)->conval->intval + (LONGINT)i < (LONGINT)y->val4->len[0]) {
                    (y->val4->data)[__X((*x)->conval->intval + (LONGINT)i, y->val4->len[0], (CHAR*)"OfrontOPP", 251903)] = (INTEGER)apar->conval->intval;
                  } else {
                    OfrontOPP_err(64);
                  }
                  break;
                case 8: 
                  if ((*x)->conval->intval + (LONGINT)i < (LONGINT)y->val8->len[0]) {
                    (y->val8->data)[__X((*x)->conval->intval + (LONGINT)i, y->val8->len[0], (CHAR*)"OfrontOPP", 252927)] = apar->conval->intval;
                  } else {
                    OfrontOPP_err(64);
                  }
                  break;
                default: __CASECHK((CHAR*)"OfrontOPP", 252949);
              }
            }
            i += 1;
          } else {
            OfrontOPP_err(64);
          }
          if ((INTEGER)OfrontOPP_sym == 21) {
            OfrontOPS_Get(&OfrontOPP_sym);
          } else if (32 <= (INTEGER)OfrontOPP_sym && (INTEGER)OfrontOPP_sym <= 40) {
            OfrontOPP_err(21);
          } else {
            break;
          }
        }
      }
      if (i != n) {
        if (i == 1 && __IN(typ->BaseTyp->form, 0x02000a)) {
        } else {
          OfrontOPP_err(65);
        }
      }
      (*x)->conval->intval += n;
    } else if ((INTEGER)typ->BaseTyp->form == 16 && (INTEGER)typ->BaseTyp->comp == 2) {
      if ((INTEGER)OfrontOPP_sym != 24) {
        for (;;) {
          OfrontOPP_ConstArray(x, typ->BaseTyp);
          if (i < n) {
            i += 1;
          } else {
            OfrontOPP_err(64);
            break;
          }
          if ((INTEGER)OfrontOPP_sym == 21) {
            OfrontOPS_Get(&OfrontOPP_sym);
          } else if (32 <= (INTEGER)OfrontOPP_sym && (INTEGER)OfrontOPP_sym <= 40) {
            OfrontOPP_err(21);
            break;
          } else {
            break;
          }
        }
      }
      if (i != n) {
        OfrontOPP_err(65);
      }
    } else {
      OfrontOPP_err(51);
    }
    OfrontOPP_CheckSym(24);
  }
}

static void OfrontOPP_Factor (OfrontOPT_Node *x)
{
  OfrontOPT_Object id = NIL;
  if ((INTEGER)OfrontOPP_sym < 32) {
    OfrontOPP_err(13);
    do {
      OfrontOPS_Get(&OfrontOPP_sym);
    } while (!((INTEGER)OfrontOPP_sym >= 32));
  }
  if ((INTEGER)OfrontOPP_sym == 40) {
    OfrontOPP_qualident(&id);
    *x = OfrontOPB_NewLeaf(id);
    OfrontOPP_selector(x);
    if ((INTEGER)(*x)->class == 9 && (INTEGER)(*x)->obj->mode == 8) {
      OfrontOPP_StandProcCall(x);
    } else if (((((INTEGER)OfrontOPP_sym == 32 && OfrontOPM_Lang == '3') && (INTEGER)(*x)->obj->mode == 5) && (INTEGER)(*x)->obj->typ->form == 16) && (INTEGER)(*x)->obj->typ->comp == 2) {
      OfrontOPB_NewArrConst(x);
      OfrontOPP_ConstArray(x, (*x)->obj->typ);
      if ((INTEGER)OfrontOPP_sym != 41) {
        OfrontOPP_err(41);
      }
    }
  } else if ((INTEGER)OfrontOPP_sym == 37) {
    switch (OfrontOPS_numtyp) {
      case 1: 
        *x = OfrontOPB_NewIntConst(OfrontOPS_intval);
        (*x)->typ = OfrontOPT_char8typ;
        if (OfrontOPS_intval > 255) {
          (*x)->typ = OfrontOPT_char16typ;
        }
        break;
      case 2: 
        *x = OfrontOPB_NewIntConst(OfrontOPS_intval);
        break;
      case 3: 
        *x = OfrontOPB_NewRealConst(OfrontOPS_realval, OfrontOPT_realtyp);
        break;
      case 4: 
        *x = OfrontOPB_NewRealConst(OfrontOPS_lrlval, OfrontOPT_lrltyp);
        break;
      default: __CASECHK((CHAR*)"OfrontOPP", 269311);
    }
    OfrontOPS_Get(&OfrontOPP_sym);
  } else if ((INTEGER)OfrontOPP_sym == 39) {
    *x = OfrontOPB_NewString(OfrontOPS_str, (void*)OfrontOPS_lstr, (INTEGER)OfrontOPS_intval);
    OfrontOPS_Get(&OfrontOPP_sym);
  } else if ((INTEGER)OfrontOPP_sym == 38) {
    *x = OfrontOPB_Nil();
    OfrontOPS_Get(&OfrontOPP_sym);
  } else if ((INTEGER)OfrontOPP_sym == 32) {
    OfrontOPS_Get(&OfrontOPP_sym);
    OfrontOPP_Expression(x);
    OfrontOPP_CheckSym(24);
  } else if ((INTEGER)OfrontOPP_sym == 33) {
    OfrontOPS_Get(&OfrontOPP_sym);
    OfrontOPP_err(32);
    OfrontOPP_Expression(x);
    OfrontOPP_CheckSym(24);
  } else if ((INTEGER)OfrontOPP_sym == 34) {
    OfrontOPS_Get(&OfrontOPP_sym);
    OfrontOPP_Sets(x);
  } else if ((INTEGER)OfrontOPP_sym == 35) {
    OfrontOPS_Get(&OfrontOPP_sym);
    OfrontOPP_Factor(x);
    OfrontOPB_MOp(35, x);
  } else {
    OfrontOPP_err(13);
    OfrontOPS_Get(&OfrontOPP_sym);
    *x = NIL;
  }
  if (*x == NIL) {
    *x = OfrontOPB_NewIntConst(1);
    (*x)->typ = OfrontOPT_undftyp;
  }
}

static void OfrontOPP_Term (OfrontOPT_Node *x)
{
  OfrontOPT_Node y = NIL;
  BYTE mulop;
  OfrontOPP_Factor(x);
  while (1 <= (INTEGER)OfrontOPP_sym && (INTEGER)OfrontOPP_sym <= 7) {
    mulop = OfrontOPP_sym;
    OfrontOPS_Get(&OfrontOPP_sym);
    OfrontOPP_Factor(&y);
    OfrontOPB_Op(mulop, x, y);
  }
}

static void OfrontOPP_SimpleExpression (OfrontOPT_Node *x)
{
  OfrontOPT_Node y = NIL;
  BYTE addop;
  if ((INTEGER)OfrontOPP_sym == 9) {
    OfrontOPS_Get(&OfrontOPP_sym);
    OfrontOPP_Term(x);
    OfrontOPB_MOp(9, x);
  } else if ((INTEGER)OfrontOPP_sym == 8) {
    OfrontOPS_Get(&OfrontOPP_sym);
    OfrontOPP_Term(x);
    OfrontOPB_MOp(8, x);
  } else {
    OfrontOPP_Term(x);
  }
  while (8 <= (INTEGER)OfrontOPP_sym && (INTEGER)OfrontOPP_sym <= 10) {
    addop = OfrontOPP_sym;
    OfrontOPS_Get(&OfrontOPP_sym);
    OfrontOPP_Term(&y);
    if (OfrontOPM_Lang == 'C' && (INTEGER)(*x)->typ->form == 13) {
      OfrontOPB_DeRef(x);
    }
    if (__IN((*x)->typ->comp, 0x0c) && __IN((*x)->typ->BaseTyp->form, 0x020008)) {
      OfrontOPB_StrDeref(x);
    }
    if (OfrontOPM_Lang == 'C' && (INTEGER)y->typ->form == 13) {
      OfrontOPB_DeRef(&y);
    }
    if (__IN(y->typ->comp, 0x0c) && __IN(y->typ->BaseTyp->form, 0x020008)) {
      OfrontOPB_StrDeref(&y);
    }
    OfrontOPB_Op(addop, x, y);
  }
}

static void OfrontOPP_Expression (OfrontOPT_Node *x)
{
  OfrontOPT_Node y = NIL;
  OfrontOPT_Node pre = NIL;
  OfrontOPT_Node last = NIL;
  OfrontOPT_Object obj = NIL;
  BYTE relation;
  OfrontOPP_SimpleExpression(x);
  if (11 <= (INTEGER)OfrontOPP_sym && (INTEGER)OfrontOPP_sym <= 16) {
    relation = OfrontOPP_sym;
    OfrontOPS_Get(&OfrontOPP_sym);
    OfrontOPP_SimpleExpression(&y);
    pre = NIL;
    last = NIL;
    if (__IN((*x)->typ->comp, 0x0c) && __IN((*x)->typ->BaseTyp->form, 0x020008)) {
      OfrontOPB_StrDeref(x);
    }
    if (__IN(y->typ->comp, 0x0c) && __IN(y->typ->BaseTyp->form, 0x020008)) {
      OfrontOPB_StrDeref(&y);
    }
    OfrontOPB_CheckBuffering(x, NIL, NIL, &pre, &last);
    OfrontOPB_CheckBuffering(&y, NIL, NIL, &pre, &last);
    OfrontOPB_Op(relation, x, y);
    if (pre != NIL) {
      OfrontOPB_Construct(29, &pre, *x);
      pre->typ = (*x)->typ;
      *x = pre;
    }
  } else if ((INTEGER)OfrontOPP_sym == 17) {
    OfrontOPS_Get(&OfrontOPP_sym);
    OfrontOPP_SimpleExpression(&y);
    OfrontOPB_In(x, y);
  } else if ((INTEGER)OfrontOPP_sym == 18) {
    OfrontOPS_Get(&OfrontOPP_sym);
    if ((INTEGER)OfrontOPP_sym == 40) {
      OfrontOPP_qualident(&obj);
      if ((INTEGER)obj->mode == 5) {
        OfrontOPB_TypTest(x, obj, 0);
      } else {
        OfrontOPP_err(52);
      }
    } else {
      OfrontOPP_err(40);
    }
  }
}

static void OfrontOPP_Receiver (BYTE *mode, BYTE *vis, OfrontOPS_Name name, OfrontOPT_Struct *typ, OfrontOPT_Struct *rec)
{
  OfrontOPS_String tname = NIL;
  *typ = OfrontOPT_undftyp;
  *rec = NIL;
  *vis = 0;
  if ((INTEGER)OfrontOPP_sym == 62) {
    OfrontOPS_Get(&OfrontOPP_sym);
    *mode = 2;
  } else if (OfrontOPM_Lang == 'C' && (INTEGER)OfrontOPP_sym == 17) {
    OfrontOPS_Get(&OfrontOPP_sym);
    *mode = 2;
    *vis = 3;
  } else {
    *mode = 1;
  }
  __MOVE(OfrontOPS_name, name, 48);
  OfrontOPP_CheckSym(40);
  OfrontOPP_CheckSym(22);
  if ((INTEGER)OfrontOPP_sym != 40) {
    OfrontOPP_err(40);
  }
  OfrontOPP_Type(typ, &tname);
  if (tname == NIL) {
    if ((INTEGER)(*typ)->form == 13) {
      *rec = (*typ)->BaseTyp;
    } else {
      *rec = *typ;
    }
    if (!((((INTEGER)*mode == 1 && (INTEGER)(*typ)->form == 13) && (INTEGER)(*rec)->comp == 4) || ((INTEGER)*mode == 2 && (INTEGER)(*typ)->comp == 4))) {
      OfrontOPP_err(70);
      *rec = NIL;
    }
    if (*rec != NIL && (INTEGER)(*rec)->mno != (INTEGER)OfrontOPP_level) {
      OfrontOPP_err(72);
      *rec = NIL;
    }
  } else {
    OfrontOPP_err(0);
  }
  OfrontOPP_CheckSym(24);
  if (*rec == NIL) {
    *rec = OfrontOPT_NewStr(16, 4);
    (*rec)->BaseTyp = NIL;
  }
}

static struct ProcedureDeclaration__34 {
  OfrontOPT_Node *x;
  OfrontOPT_Object *proc, *fwd;
  OfrontOPS_Name *name;
  BYTE *mode;
  BOOLEAN *forward;
  SHORTINT *sys;
  struct ProcedureDeclaration__34 *lnk;
} *ProcedureDeclaration__34_s;

static void __35 (void);
static void __37 (void);
static void __43 (void);
static void __45 (void);

static struct __37__38 {
  INTEGER *n;
  OfrontOPS_String *s;
  struct __37__38 *lnk;
} *__37__38_s;

static void __40 (INTEGER len);

static void __40 (INTEGER len)
{
  INTEGER j;
  OfrontOPS_String s2 = NIL;
  INTEGER _for__42;
  if (len > ((*__37__38_s->s))->len[0]) {
    s2 = __NEWARR(NIL, 1, 1, 1, 1, (SYSTEM_ARRLEN)(__ASHL(((*__37__38_s->s))->len[0], 1, INTEGER)));
    _for__42 = (*__37__38_s->n) - 1;
    j = 0;
    while (j <= _for__42) {
      (s2->data)[__X(j, s2->len[0], (CHAR*)"OfrontOPP", 298049)] = (((*__37__38_s->s))->data)[__X(j, ((*__37__38_s->s))->len[0], (CHAR*)"OfrontOPP", 298049)];
      j += 1;
    }
    (*__37__38_s->s) = s2;
  }
}

static void __37 (void)
{
  OfrontOPS_String ext = NIL;
  INTEGER n, c, i;
  OfrontOPS_String s = NIL;
  INTEGER _for__39;
  struct __37__38 _s;
  _s.n = &n;
  _s.s = &s;
  _s.lnk = __37__38_s;
  __37__38_s = &_s;
  n = 0;
  s = __NEWARR(NIL, 1, 1, 1, 1, (SYSTEM_ARRLEN)128);
  if ((INTEGER)OfrontOPP_sym == 21) {
    OfrontOPP_err(13);
  }
  for (;;) {
    if ((INTEGER)OfrontOPP_sym == 37) {
      c = (INTEGER)OfrontOPS_intval;
      __40(n + 1);
      if ((INTEGER)OfrontOPS_numtyp != 1) {
        OfrontOPP_err(63);
        c = 1;
        n = 0;
      } else if ((LONGCHAR)c < ' ') {
        OfrontOPP_err(3);
      }
      OfrontOPS_Get(&OfrontOPP_sym);
      (s->data)[__X(n, s->len[0], (CHAR*)"OfrontOPP", 300841)] = (CHAR)c;
      n += 1;
    } else if ((INTEGER)OfrontOPP_sym == 39) {
      c = (INTEGER)OfrontOPS_intval - 1;
      if (c == 0) {
        OfrontOPP_err(63);
      }
      __40(n + c);
      _for__39 = c - 1;
      i = 0;
      while (i <= _for__39) {
        (s->data)[__X(n + i, s->len[0], (CHAR*)"OfrontOPP", 301876)] = (OfrontOPS_str->data)[__X(i, OfrontOPS_str->len[0], (CHAR*)"OfrontOPP", 301876)];
        i += 1;
      }
      OfrontOPS_Get(&OfrontOPP_sym);
      n += c;
    }
    if ((INTEGER)OfrontOPP_sym == 21) {
      OfrontOPS_Get(&OfrontOPP_sym);
      if ((INTEGER)OfrontOPP_sym != 37 && (INTEGER)OfrontOPP_sym != 39) {
        OfrontOPP_err(13);
      }
    } else if ((INTEGER)OfrontOPP_sym == 37 || (INTEGER)OfrontOPP_sym == 39) {
      OfrontOPP_err(21);
    } else {
      break;
    }
  }
  if (n != 0) {
    ext = __NEWARR(NIL, 1, 1, 1, 1, (SYSTEM_ARRLEN)n);
    i = 0;
    if ((INTEGER)(*ProcedureDeclaration__34_s->sys) > 0) {
      OfrontOPP_err(127);
    }
    while (i < n) {
      (ext->data)[__X(i, ext->len[0], (CHAR*)"OfrontOPP", 304163)] = (s->data)[__X(i, s->len[0], (CHAR*)"OfrontOPP", 304163)];
      i += 1;
    }
  } else {
    ext = NIL;
  }
  ((*ProcedureDeclaration__34_s->proc))->conval->ext = ext;
  ((*ProcedureDeclaration__34_s->proc))->conval->setval |= __SETOF(1);
  __37__38_s = _s.lnk;
}

static void __43 (void)
{
  OfrontOPS_String name = NIL;
  ((*ProcedureDeclaration__34_s->proc))->mode = (*ProcedureDeclaration__34_s->mode);
  ((*ProcedureDeclaration__34_s->proc))->typ = OfrontOPT_notyp;
  ((*ProcedureDeclaration__34_s->proc))->sysflag = (BYTE)(*ProcedureDeclaration__34_s->sys);
  ((*ProcedureDeclaration__34_s->proc))->conval = OfrontOPT_NewConst();
  ((*ProcedureDeclaration__34_s->proc))->conval->setval = 0x0;
  if ((INTEGER)OfrontOPP_sym == 32) {
    OfrontOPS_Get(&OfrontOPP_sym);
    OfrontOPP_FormalParameters(&((*ProcedureDeclaration__34_s->proc))->link, &((*ProcedureDeclaration__34_s->proc))->typ, &name);
    if (name != NIL) {
      OfrontOPP_err(0);
    }
  }
  OfrontOPP_CheckForwardTypes();
  OfrontOPP_userList = NIL;
  if ((*ProcedureDeclaration__34_s->fwd) != NIL) {
    OfrontOPB_CheckParameters(((*ProcedureDeclaration__34_s->proc))->link, ((*ProcedureDeclaration__34_s->fwd))->link, 1);
    if (((*ProcedureDeclaration__34_s->proc))->typ != ((*ProcedureDeclaration__34_s->fwd))->typ) {
      OfrontOPP_err(117);
    }
    (*ProcedureDeclaration__34_s->proc) = (*ProcedureDeclaration__34_s->fwd);
    OfrontOPT_topScope = ((*ProcedureDeclaration__34_s->proc))->scope;
    if ((INTEGER)(*ProcedureDeclaration__34_s->mode) == 10) {
      ((*ProcedureDeclaration__34_s->proc))->mode = 10;
    }
  }
}

static void __35 (void)
{
  OfrontOPT_Node procdec = NIL;
  OfrontOPT_Node statseq = NIL;
  INTEGER c;
  c = OfrontOPM_errpos;
  ((*ProcedureDeclaration__34_s->proc))->conval->setval |= __SETOF(1);
  OfrontOPP_CheckSym(41);
  OfrontOPP_Block(&procdec, &statseq);
  OfrontOPB_Enter(&procdec, statseq, (*ProcedureDeclaration__34_s->proc));
  *ProcedureDeclaration__34_s->x = procdec;
  (*ProcedureDeclaration__34_s->x)->conval = OfrontOPT_NewConst();
  (*ProcedureDeclaration__34_s->x)->conval->intval = c;
  OfrontOPP_CheckSym(43);
  if ((INTEGER)OfrontOPP_sym == 40) {
    if (__STRCMPCC(OfrontOPS_name, ((*ProcedureDeclaration__34_s->proc))->name->data, ((*ProcedureDeclaration__34_s->proc))->name->len[0], (CHAR*)"OfrontOPP", 313389) != 0) {
      OfrontOPP_err(4);
    }
    OfrontOPS_Get(&OfrontOPP_sym);
  } else {
    OfrontOPP_err(40);
  }
}

static void __45 (void)
{
  OfrontOPT_Object baseProc = NIL;
  OfrontOPT_Object o = NIL;
  OfrontOPT_Struct objTyp = NIL;
  OfrontOPT_Struct recTyp = NIL;
  BYTE objMode, objVis;
  OfrontOPS_Name objName;
  OfrontOPT_Node pnode = NIL;
  SET fwdAttr;
  OfrontOPS_Get(&OfrontOPP_sym);
  (*ProcedureDeclaration__34_s->mode) = 13;
  if ((INTEGER)OfrontOPP_level > 0) {
    OfrontOPP_err(73);
  }
  OfrontOPP_Receiver(&objMode, &objVis, objName, &objTyp, &recTyp);
  if ((INTEGER)OfrontOPP_sym == 40) {
    __MOVE(OfrontOPS_name, (*ProcedureDeclaration__34_s->name), 48);
    OfrontOPT_FindField((void*)(*ProcedureDeclaration__34_s->name), 48, recTyp, &(*ProcedureDeclaration__34_s->fwd));
    OfrontOPT_FindBaseField((void*)(*ProcedureDeclaration__34_s->name), 48, recTyp, &baseProc);
    if (baseProc != NIL && (INTEGER)baseProc->mode != 13) {
      baseProc = NIL;
    }
    if ((*ProcedureDeclaration__34_s->fwd) == baseProc) {
      (*ProcedureDeclaration__34_s->fwd) = NIL;
    }
    if ((*ProcedureDeclaration__34_s->fwd) != NIL && (INTEGER)((*ProcedureDeclaration__34_s->fwd))->mnolev != (INTEGER)OfrontOPP_level) {
      (*ProcedureDeclaration__34_s->fwd) = NIL;
    }
    if (((*ProcedureDeclaration__34_s->fwd) != NIL && (INTEGER)((*ProcedureDeclaration__34_s->fwd))->mode == 13) && (((*ProcedureDeclaration__34_s->fwd))->conval->setval & 0x0a0002) == 0x0) {
      (*ProcedureDeclaration__34_s->proc) = OfrontOPT_NewObj();
      ((*ProcedureDeclaration__34_s->proc))->leaf = 1;
      ((*ProcedureDeclaration__34_s->proc))->mode = 13;
      ((*ProcedureDeclaration__34_s->proc))->conval = OfrontOPT_NewConst();
      OfrontOPP_CheckMark((*ProcedureDeclaration__34_s->proc));
      if ((INTEGER)((*ProcedureDeclaration__34_s->fwd))->vis != (INTEGER)((*ProcedureDeclaration__34_s->proc))->vis) {
        OfrontOPP_err(118);
      }
      fwdAttr = ((*ProcedureDeclaration__34_s->fwd))->conval->setval;
    } else {
      if ((*ProcedureDeclaration__34_s->fwd) != NIL) {
        OfrontOPP_err(1);
        (*ProcedureDeclaration__34_s->fwd) = NIL;
      }
      OfrontOPT_OpenScope(0, NIL);
      OfrontOPT_topScope->right = recTyp->link;
      OfrontOPT_Insert((void*)(*ProcedureDeclaration__34_s->name), 48, &(*ProcedureDeclaration__34_s->proc));
      recTyp->link = OfrontOPT_topScope->right;
      OfrontOPT_CloseScope();
      ((*ProcedureDeclaration__34_s->proc))->mode = 13;
      ((*ProcedureDeclaration__34_s->proc))->conval = OfrontOPT_NewConst();
      OfrontOPP_CheckMark((*ProcedureDeclaration__34_s->proc));
      if (recTyp->strobj != NIL) {
        o = recTyp->strobj->link;
        if (o == NIL) {
          recTyp->strobj->link = (*ProcedureDeclaration__34_s->proc);
        } else {
          while (o->nlink != NIL) {
            o = o->nlink;
          }
          o->nlink = (*ProcedureDeclaration__34_s->proc);
        }
      }
    }
    OfrontOPP_level += 1;
    OfrontOPT_OpenScope(OfrontOPP_level, (*ProcedureDeclaration__34_s->proc));
    OfrontOPT_Insert((void*)objName, 48, &((*ProcedureDeclaration__34_s->proc))->link);
    ((*ProcedureDeclaration__34_s->proc))->link->mode = objMode;
    ((*ProcedureDeclaration__34_s->proc))->link->vis = objVis;
    ((*ProcedureDeclaration__34_s->proc))->link->typ = objTyp;
    __ASSERT(OfrontOPT_topScope != NIL, 0, (CHAR*)"OfrontOPP", 325662);
    __43();
    __ASSERT(OfrontOPT_topScope != NIL, 0, (CHAR*)"OfrontOPP", 326174);
    OfrontOPP_GetAttributes((*ProcedureDeclaration__34_s->proc), baseProc, recTyp);
    if ((*ProcedureDeclaration__34_s->fwd) != NIL && ((fwdAttr ^ ((*ProcedureDeclaration__34_s->proc))->conval->setval) & 0x1a0000) != 0x0) {
      OfrontOPP_err(184);
    }
    OfrontOPP_CheckOverwrite((*ProcedureDeclaration__34_s->proc), baseProc, recTyp);
    if (!(*ProcedureDeclaration__34_s->forward)) {
      if (__IN(19, ((*ProcedureDeclaration__34_s->proc))->conval->setval)) {
        pnode = NIL;
        OfrontOPB_Enter(&pnode, NIL, (*ProcedureDeclaration__34_s->proc));
        pnode->conval = OfrontOPT_NewConst();
        pnode->conval->intval = OfrontOPM_errpos;
        pnode->conval->intval2 = OfrontOPM_errpos;
        *ProcedureDeclaration__34_s->x = pnode;
      } else if (!__IN(17, ((*ProcedureDeclaration__34_s->proc))->conval->setval)) {
        __35();
      }
      ((*ProcedureDeclaration__34_s->proc))->adr = 0;
    } else {
      ((*ProcedureDeclaration__34_s->proc))->adr = OfrontOPM_errpos;
      if ((((*ProcedureDeclaration__34_s->proc))->conval->setval & 0x0a0000) != 0x0) {
        OfrontOPP_err(184);
      }
    }
    OfrontOPP_level -= 1;
    OfrontOPT_CloseScope();
  } else {
    OfrontOPP_err(40);
  }
}

static void OfrontOPP_ProcedureDeclaration (OfrontOPT_Node *x)
{
  OfrontOPT_Object proc = NIL;
  OfrontOPT_Object fwd = NIL;
  OfrontOPS_Name name;
  BYTE mode;
  BOOLEAN forward;
  SHORTINT sys;
  struct ProcedureDeclaration__34 _s;
  _s.x = x;
  _s.proc = &proc;
  _s.fwd = &fwd;
  _s.name = (void*)name;
  _s.mode = &mode;
  _s.forward = &forward;
  _s.sys = &sys;
  _s.lnk = ProcedureDeclaration__34_s;
  ProcedureDeclaration__34_s = &_s;
  proc = NIL;
  forward = 0;
  *x = NIL;
  mode = 6;
  sys = 0;
  if ((INTEGER)OfrontOPP_sym != 40 && (INTEGER)OfrontOPP_sym != 32) {
    switch (OfrontOPP_sym) {
      case 1: 
        OfrontOPS_Get(&OfrontOPP_sym);
        break;
      case 19: 
        forward = 1;
        OfrontOPS_Get(&OfrontOPP_sym);
        break;
      case 8: 
        mode = 10;
        OfrontOPS_Get(&OfrontOPP_sym);
        break;
      case 9: 
        mode = 9;
        OfrontOPS_Get(&OfrontOPP_sym);
        break;
      default: 
        break;
    }
    if (__IN(mode, 0x0600) && !OfrontOPT_SYSimported) {
      OfrontOPP_err(135);
    }
    OfrontOPP_CheckSysFlagProc(&sys, 1);
  }
  if (((((INTEGER)OfrontOPP_sym == 32 && (INTEGER)mode == 6) && (INTEGER)sys == 0) && OfrontOPM_Lang != '1') && OfrontOPM_Lang != '7') {
    __45();
  } else if ((INTEGER)OfrontOPP_sym == 40) {
    OfrontOPT_Find((void*)OfrontOPS_name, 48, &fwd);
    __MOVE(OfrontOPS_name, name, 48);
    if (fwd != NIL && ((INTEGER)fwd->mnolev != (INTEGER)OfrontOPP_level || (INTEGER)fwd->mode == 8)) {
      fwd = NIL;
    }
    if ((fwd != NIL && __IN(fwd->mode, 0xc0)) && !__IN(1, fwd->conval->setval)) {
      proc = OfrontOPT_NewObj();
      proc->leaf = 1;
      if (__IN(mode, 0x0600) || (INTEGER)fwd->sysflag != (INTEGER)sys) {
        OfrontOPP_err(134);
      }
      proc->mode = mode;
      proc->conval = OfrontOPT_NewConst();
      OfrontOPP_CheckMark(proc);
      if ((INTEGER)fwd->vis != (INTEGER)proc->vis) {
        OfrontOPP_err(118);
      }
    } else {
      if (fwd != NIL) {
        OfrontOPP_err(1);
        fwd = NIL;
      }
      OfrontOPT_Insert((void*)name, 48, &proc);
      proc->mode = mode;
      proc->conval = OfrontOPT_NewConst();
      OfrontOPP_CheckMark(proc);
      if ((INTEGER)mode == 9) {
        if ((INTEGER)sys > 0) {
          OfrontOPP_err(127);
        }
        sys = proc->sysflag;
      }
    }
    if ((INTEGER)proc->vis != 0 && (INTEGER)mode == 6) {
      mode = 7;
    }
    if ((INTEGER)mode != 6 && (INTEGER)OfrontOPP_level > 0) {
      OfrontOPP_err(73);
    }
    OfrontOPP_level += 1;
    OfrontOPT_OpenScope(OfrontOPP_level, proc);
    proc->link = NIL;
    __43();
    if ((INTEGER)mode == 9) {
      __37();
    } else if (proc->entry != NIL && (INTEGER)proc->sysflag != 3) {
      proc->conval->setval |= __SETOF(1);
    } else if (!forward) {
      __35();
      proc->adr = 0;
    } else {
      proc->adr = OfrontOPM_errpos;
    }
    OfrontOPP_level -= 1;
    OfrontOPT_CloseScope();
  } else {
    OfrontOPP_err(40);
  }
  ProcedureDeclaration__34_s = _s.lnk;
}

static void OfrontOPP_CaseLabelList (OfrontOPT_Node *lab, SHORTINT LabelForm, SHORTINT *n, OfrontOPP_CaseTable tab)
{
  OfrontOPT_Node x = NIL;
  OfrontOPT_Node y = NIL;
  OfrontOPT_Node lastlab = NIL;
  SHORTINT i, f;
  INTEGER xval, yval;
  *lab = NIL;
  lastlab = NIL;
  for (;;) {
    OfrontOPP_ConstExpression(&x);
    f = x->typ->form;
    if (__IN(f, 0x02407a)) {
      xval = (INTEGER)x->conval->intval;
    } else {
      OfrontOPP_err(61);
      xval = 1;
    }
    if (__IN(f, 0x4072) != __IN(LabelForm, 0x4072)) {
      OfrontOPP_err(60);
    }
    if ((INTEGER)OfrontOPP_sym == 23) {
      OfrontOPS_Get(&OfrontOPP_sym);
      OfrontOPP_ConstExpression(&y);
      yval = (INTEGER)y->conval->intval;
      if ((INTEGER)y->typ->form != (INTEGER)f && !(__IN(f, 0x4072) && __IN(y->typ->form, 0x4072))) {
        OfrontOPP_err(60);
      }
      if (yval < xval) {
        OfrontOPP_err(63);
        yval = xval;
      }
    } else {
      yval = xval;
    }
    x->conval->intval2 = yval;
    i = *n;
    if ((INTEGER)i < 256) {
      for (;;) {
        if ((INTEGER)i == 0) {
          break;
        }
        if (tab[__X((INTEGER)i - 1, 256, (CHAR*)"OfrontOPP", 348936)].low <= yval) {
          if (tab[__X((INTEGER)i - 1, 256, (CHAR*)"OfrontOPP", 348463)].high >= xval) {
            OfrontOPP_err(62);
          }
          break;
        }
        tab[__X(i, 256, (CHAR*)"OfrontOPP", 349207)] = tab[__X((INTEGER)i - 1, 256, (CHAR*)"OfrontOPP", 349207)];
        i -= 1;
      }
      tab[__X(i, 256, (CHAR*)"OfrontOPP", 349718)].low = xval;
      tab[__X(i, 256, (CHAR*)"OfrontOPP", 349739)].high = yval;
      *n += 1;
    } else {
      OfrontOPP_err(213);
    }
    OfrontOPB_Link(lab, &lastlab, x);
    if ((INTEGER)OfrontOPP_sym == 21) {
      OfrontOPS_Get(&OfrontOPP_sym);
    } else if ((INTEGER)OfrontOPP_sym == 37 || (INTEGER)OfrontOPP_sym == 40) {
      OfrontOPP_err(21);
    } else {
      break;
    }
  }
}

static struct StatSeq__54 {
  OfrontOPT_Node *stat;
  OfrontOPT_Object *fpar, *id, *t, *obj;
  OfrontOPT_Struct *idtyp;
  BOOLEAN *e;
  LONGINT *L;
  OfrontOPT_Node *s, *x, *y, *z, *apar, *last, *lastif;
  INTEGER *pos;
  OfrontOPS_Name *name;
  struct StatSeq__54 *lnk;
} *StatSeq__54_s;

static LONGINT __55 (OfrontOPT_Node A, OfrontOPT_Node B, LONGINT Step);
static void __57 (OfrontOPT_Node A, OfrontOPT_Node B, LONGINT Step);
static void __59 (OfrontOPT_Node *x);
static void __61 (OfrontOPT_Node *x);
static void __63 (OfrontOPT_Node A, OfrontOPT_Node B, LONGINT Step);
static void __65 (void);
static void __67 (void);
static void __69 (OfrontOPT_Node x);
static BOOLEAN __71 (OfrontOPT_Object id);

static void __69 (OfrontOPT_Node x)
{
  x->conval = OfrontOPT_NewConst();
  x->conval->intval = (*StatSeq__54_s->pos);
}

static void __59 (OfrontOPT_Node *x)
{
  SHORTINT n;
  INTEGER low, high;
  BOOLEAN e;
  OfrontOPP_CaseTable tab;
  OfrontOPT_Node cases = NIL;
  OfrontOPT_Node lab = NIL;
  OfrontOPT_Node y = NIL;
  OfrontOPT_Node lastcase = NIL;
  OfrontOPP_Expression(x);
  (*StatSeq__54_s->pos) = OfrontOPM_errpos;
  if ((INTEGER)(*x)->class == 8 || (INTEGER)(*x)->class == 9) {
    OfrontOPP_err(126);
  } else if ((OfrontOPM_Lang == '3' || OfrontOPM_Lang == '7') && ((INTEGER)(*x)->typ->form == 13 || ((INTEGER)(*x)->typ->comp == 4 && (INTEGER)(*x)->class == 1))) {
    (*StatSeq__54_s->id) = (*x)->obj;
    (*StatSeq__54_s->idtyp) = NIL;
    *x = NIL;
    if (((*StatSeq__54_s->id) != NIL && (INTEGER)((*StatSeq__54_s->id))->typ->form == 13) && ((INTEGER)((*StatSeq__54_s->id))->mode == 2 || !((*StatSeq__54_s->id))->leaf)) {
      OfrontOPP_err(245);
    }
    OfrontOPP_CheckSym(27);
    for (;;) {
      if ((INTEGER)OfrontOPP_sym < 42) {
        y = OfrontOPB_NewLeaf((*StatSeq__54_s->id));
        if ((INTEGER)OfrontOPP_sym == 40) {
          OfrontOPP_qualident(&(*StatSeq__54_s->t));
          if ((INTEGER)((*StatSeq__54_s->t))->mode == 5) {
            if ((*StatSeq__54_s->id) != NIL) {
              (*StatSeq__54_s->idtyp) = ((*StatSeq__54_s->id))->typ;
              OfrontOPB_TypTest(&y, (*StatSeq__54_s->t), 0);
              ((*StatSeq__54_s->id))->typ = ((*StatSeq__54_s->t))->typ;
              if (((*StatSeq__54_s->id))->ptyp == NIL) {
                ((*StatSeq__54_s->id))->ptyp = (*StatSeq__54_s->idtyp);
              }
            } else {
              OfrontOPP_err(130);
            }
          } else {
            OfrontOPP_err(52);
          }
        } else {
          OfrontOPP_err(40);
        }
        (*StatSeq__54_s->pos) = OfrontOPM_errpos;
        OfrontOPP_CheckSym(22);
        OfrontOPP_StatSeq(&(*StatSeq__54_s->s));
        OfrontOPB_Construct(15, &y, (*StatSeq__54_s->s));
        __69(y);
        if ((*StatSeq__54_s->idtyp) != NIL) {
          if (((*StatSeq__54_s->id))->ptyp == (*StatSeq__54_s->idtyp)) {
            ((*StatSeq__54_s->id))->ptyp = NIL;
          }
          ((*StatSeq__54_s->id))->typ = (*StatSeq__54_s->idtyp);
          (*StatSeq__54_s->idtyp) = NIL;
        }
        if (*x == NIL) {
          *x = y;
          (*StatSeq__54_s->lastif) = *x;
        } else {
          OfrontOPB_Link(x, &(*StatSeq__54_s->lastif), y);
        }
      }
      if ((INTEGER)OfrontOPP_sym == 42) {
        OfrontOPS_Get(&OfrontOPP_sym);
        if (OfrontOPM_Lang == '3' && (((INTEGER)OfrontOPP_sym == 42 || (INTEGER)OfrontOPP_sym == 44) || (INTEGER)OfrontOPP_sym == 43)) {
          OfrontOPP_err(61);
        }
      } else {
        break;
      }
    }
    e = (INTEGER)OfrontOPP_sym == 44 || OfrontOPM_Lang == '7';
    if (e && OfrontOPM_Lang != '7') {
      OfrontOPS_Get(&OfrontOPP_sym);
      OfrontOPP_StatSeq(&(*StatSeq__54_s->s));
    } else {
      (*StatSeq__54_s->s) = NIL;
    }
    OfrontOPB_Construct(27, x, (*StatSeq__54_s->s));
    if (e) {
      (*x)->subcl = 1;
    }
  } else {
    if (!__IN((*x)->typ->form, 0x02407a)) {
      OfrontOPP_err(125);
    }
    OfrontOPP_CheckSym(27);
    cases = NIL;
    lastcase = NIL;
    n = 0;
    for (;;) {
      if ((INTEGER)OfrontOPP_sym < 42) {
        OfrontOPP_CaseLabelList(&lab, (*x)->typ->form, &n, tab);
        OfrontOPP_CheckSym(22);
        OfrontOPP_StatSeq(&y);
        OfrontOPB_Construct(17, &lab, y);
        OfrontOPB_Link(&cases, &lastcase, lab);
      }
      if ((INTEGER)OfrontOPP_sym == 42) {
        OfrontOPS_Get(&OfrontOPP_sym);
        if (OfrontOPM_Lang == '3' && (((INTEGER)OfrontOPP_sym == 42 || (INTEGER)OfrontOPP_sym == 44) || (INTEGER)OfrontOPP_sym == 43)) {
          OfrontOPP_err(61);
        }
      } else {
        break;
      }
    }
    if ((INTEGER)n > 0) {
      low = tab[0].low;
      high = tab[__X((INTEGER)n - 1, 256, (CHAR*)"OfrontOPP", 370746)].high;
      if (high - low > 512) {
        OfrontOPP_err(209);
      }
    } else {
      low = 1;
      high = 0;
    }
    e = (INTEGER)OfrontOPP_sym == 44 || OfrontOPM_Lang == '7';
    if (e && OfrontOPM_Lang != '7') {
      OfrontOPS_Get(&OfrontOPP_sym);
      OfrontOPP_StatSeq(&y);
    } else {
      y = NIL;
    }
    OfrontOPB_Construct(16, &cases, y);
    OfrontOPB_Construct(21, x, cases);
    cases->conval = OfrontOPT_NewConst();
    cases->conval->intval = low;
    cases->conval->intval2 = high;
    if (e) {
      cases->conval->setval = 0x02;
    } else {
      cases->conval->setval = 0x0;
    }
  }
}

static void __61 (OfrontOPT_Node *x)
{
  if ((INTEGER)(*x)->class == 8 || (INTEGER)(*x)->class == 9) {
    OfrontOPP_err(126);
    *x = OfrontOPB_NewBoolConst(0);
  } else if ((INTEGER)(*x)->typ->form != 2) {
    OfrontOPP_err(120);
    *x = OfrontOPB_NewBoolConst(0);
  }
  (*StatSeq__54_s->pos) = OfrontOPM_errpos;
}

static void __67 (void)
{
  BYTE vis, mnolev;
  OfrontOPS_Get(&OfrontOPP_sym);
  if ((INTEGER)OfrontOPP_sym == 40) {
    OfrontOPP_qualident(&(*StatSeq__54_s->id));
    if (!__IN(((*StatSeq__54_s->id))->typ->form, 0x4072)) {
      OfrontOPP_err(68);
    }
    OfrontOPP_CheckSym(36);
    OfrontOPP_Expression(&(*StatSeq__54_s->y));
    (*StatSeq__54_s->pos) = OfrontOPM_errpos;
    (*StatSeq__54_s->x) = OfrontOPB_NewLeaf((*StatSeq__54_s->id));
    OfrontOPB_Assign(&(*StatSeq__54_s->x), (*StatSeq__54_s->y));
    __69((*StatSeq__54_s->x));
    vis = ((*StatSeq__54_s->id))->vis;
    mnolev = ((*StatSeq__54_s->id))->mnolev;
    if (OfrontOPM_Lang == '3') {
      ((*StatSeq__54_s->id))->vis = 2;
      ((*StatSeq__54_s->id))->mnolev = -128;
    }
    OfrontOPP_CheckSym(30);
    OfrontOPP_Expression(&(*StatSeq__54_s->y));
    (*StatSeq__54_s->pos) = OfrontOPM_errpos;
    if (OfrontOPM_Lang != '7' && (INTEGER)((*StatSeq__54_s->y))->class != 7) {
      __MOVE((CHAR*)"@@", (*StatSeq__54_s->name), 3);
      OfrontOPT_Insert((void*)(*StatSeq__54_s->name), 48, &(*StatSeq__54_s->t));
      ((*StatSeq__54_s->t))->name = OfrontOPT_NewName((CHAR*)"@for", 5);
      ((*StatSeq__54_s->t))->mode = 1;
      ((*StatSeq__54_s->t))->typ = ((*StatSeq__54_s->x))->left->typ;
      (*StatSeq__54_s->obj) = OfrontOPT_topScope->scope;
      if ((*StatSeq__54_s->obj) == NIL) {
        OfrontOPT_topScope->scope = (*StatSeq__54_s->t);
      } else {
        while (((*StatSeq__54_s->obj))->link != NIL) {
          (*StatSeq__54_s->obj) = ((*StatSeq__54_s->obj))->link;
        }
        ((*StatSeq__54_s->obj))->link = (*StatSeq__54_s->t);
      }
      (*StatSeq__54_s->z) = OfrontOPB_NewLeaf((*StatSeq__54_s->t));
      OfrontOPB_Assign(&(*StatSeq__54_s->z), (*StatSeq__54_s->y));
      __69((*StatSeq__54_s->z));
      OfrontOPB_Link(StatSeq__54_s->stat, &(*StatSeq__54_s->last), (*StatSeq__54_s->z));
      (*StatSeq__54_s->y) = OfrontOPB_NewLeaf((*StatSeq__54_s->t));
    } else if (__IN(((*StatSeq__54_s->y))->typ->form, 0x02000d)) {
      OfrontOPP_err(113);
    } else {
      OfrontOPB_CheckAssign(((*StatSeq__54_s->x))->left->typ, &(*StatSeq__54_s->y));
    }
    OfrontOPB_Link(StatSeq__54_s->stat, &(*StatSeq__54_s->last), (*StatSeq__54_s->x));
    if ((INTEGER)OfrontOPP_sym == 31) {
      OfrontOPS_Get(&OfrontOPP_sym);
      OfrontOPP_ConstExpression(&(*StatSeq__54_s->z));
    } else {
      (*StatSeq__54_s->z) = OfrontOPB_NewIntConst(1);
    }
    (*StatSeq__54_s->pos) = OfrontOPM_errpos;
    (*StatSeq__54_s->x) = OfrontOPB_NewLeaf((*StatSeq__54_s->id));
    if (((*StatSeq__54_s->z))->conval->intval > 0) {
      OfrontOPB_Op(14, &(*StatSeq__54_s->x), (*StatSeq__54_s->y));
    } else if (((*StatSeq__54_s->z))->conval->intval < 0) {
      OfrontOPB_Op(16, &(*StatSeq__54_s->x), (*StatSeq__54_s->y));
    } else {
      OfrontOPP_err(63);
      OfrontOPB_Op(16, &(*StatSeq__54_s->x), (*StatSeq__54_s->y));
    }
    OfrontOPP_CheckSym(29);
    OfrontOPP_StatSeq(&(*StatSeq__54_s->s));
    (*StatSeq__54_s->y) = OfrontOPB_NewLeaf((*StatSeq__54_s->id));
    OfrontOPB_StPar1(&(*StatSeq__54_s->y), (*StatSeq__54_s->z), 19);
    __69((*StatSeq__54_s->y));
    if ((*StatSeq__54_s->s) == NIL) {
      (*StatSeq__54_s->s) = (*StatSeq__54_s->y);
    } else {
      (*StatSeq__54_s->z) = (*StatSeq__54_s->s);
      while (((*StatSeq__54_s->z))->link != NIL) {
        (*StatSeq__54_s->z) = ((*StatSeq__54_s->z))->link;
      }
      ((*StatSeq__54_s->z))->link = (*StatSeq__54_s->y);
    }
    OfrontOPP_CheckSym(43);
    OfrontOPB_Construct(22, &(*StatSeq__54_s->x), (*StatSeq__54_s->s));
    ((*StatSeq__54_s->id))->vis = vis;
    ((*StatSeq__54_s->id))->mnolev = mnolev;
  } else {
    OfrontOPP_err(40);
  }
}

static void __57 (OfrontOPT_Node A, OfrontOPT_Node B, LONGINT Step)
{
  LONGINT Nmin, Nmax;
  if (Step > 0) {
    if ((INTEGER)A->class == 7) {
      Nmin = A->conval->intval;
    } else {
      Nmin = OfrontOPB_Min(((*StatSeq__54_s->id))->typ->form);
    }
    if ((INTEGER)B->class == 7) {
      Nmax = B->conval->intval;
    } else {
      Nmax = OfrontOPB_Max(((*StatSeq__54_s->id))->typ->form);
    }
    (*StatSeq__54_s->L) = OfrontOPM_UDiv(Nmax - Nmin, Step) + 1;
  } else {
    if ((INTEGER)A->class == 7) {
      Nmax = A->conval->intval;
    } else {
      Nmax = OfrontOPB_Max(((*StatSeq__54_s->id))->typ->form);
    }
    if ((INTEGER)B->class == 7) {
      Nmin = B->conval->intval;
    } else {
      Nmin = OfrontOPB_Min(((*StatSeq__54_s->id))->typ->form);
    }
    (*StatSeq__54_s->L) = OfrontOPM_UDiv(Nmax - Nmin, -Step) + 1;
  }
  (*StatSeq__54_s->e) = (INTEGER)A->class == 7 && (INTEGER)B->class == 7;
}

static LONGINT __55 (OfrontOPT_Node A, OfrontOPT_Node B, LONGINT Step)
{
  __ASSERT((INTEGER)A->class == 7 && (INTEGER)B->class == 7, 0, (CHAR*)"OfrontOPP", 395318);
  return A->conval->intval + ((*StatSeq__54_s->L) - 1) * Step;
}

static void __63 (OfrontOPT_Node A, OfrontOPT_Node B, LONGINT Step)
{
  LONGINT Nlast;
  INTEGER sgnPostLast, sgnPredLast;
  SHORTINT cond;
  cond = 0;
  Nlast = __55(A, B, Step);
  sgnPostLast = OfrontOPP_Sign(OfrontOPB_Short2Size(Nlast + Step, ((*StatSeq__54_s->id))->typ->form));
  sgnPredLast = OfrontOPP_Sign(OfrontOPB_Short2Size(Nlast - Step, ((*StatSeq__54_s->id))->typ->form));
  if (Nlast == 0) {
    cond = -11;
  } else if (OfrontOPP_Sign(Nlast) == -OfrontOPP_Sign(Step) && OfrontOPP_Sign(Nlast) != sgnPostLast) {
    switch (sgnPostLast) {
      case -1: 
        cond = 13;
        break;
      case 0: 
        cond = 11;
        break;
      case 1: 
        cond = 16;
        break;
      default: __CASECHK((CHAR*)"OfrontOPP", 400148);
    }
  } else if (OfrontOPP_Sign(Nlast) == OfrontOPP_Sign(Step)) {
    if (OfrontOPP_Sign(Nlast) != sgnPostLast && OfrontOPP_Sign(A->conval->intval + Step) != sgnPostLast) {
      switch (sgnPostLast) {
        case -1: 
          cond = 13;
          break;
        case 0: 
          cond = 11;
          break;
        case 1: 
          if (A->conval->intval + Step == 0) {
            cond = 15;
          } else {
            cond = 16;
          }
          break;
        default: __CASECHK((CHAR*)"OfrontOPP", 402251);
      }
    }
  }
  if ((((INTEGER)cond == 0 || (INTEGER)cond == 15) && OfrontOPP_Sign(Nlast) == OfrontOPP_Sign(Step)) && sgnPredLast != OfrontOPP_Sign(Nlast)) {
    switch (OfrontOPP_Sign(Nlast)) {
      case -1: 
        cond = -13;
        break;
      case 0: 
        cond = -11;
        break;
      case 1: 
        if (sgnPredLast == 0) {
          cond = -15;
        } else {
          cond = -16;
        }
        break;
      default: __CASECHK((CHAR*)"OfrontOPP", 404800);
    }
  }
  if ((INTEGER)cond != 0) {
    (*StatSeq__54_s->t) = (*StatSeq__54_s->id);
    (*StatSeq__54_s->apar) = OfrontOPB_NewLeaf((*StatSeq__54_s->id));
    if ((INTEGER)cond < 0) {
      (*StatSeq__54_s->idtyp) = NIL;
      OfrontOPB_Assign(&(*StatSeq__54_s->apar), OfrontOPB_NewIntConst(0));
    } else {
      (*StatSeq__54_s->idtyp) = ((*StatSeq__54_s->id))->typ;
      __ASSERT((*StatSeq__54_s->idtyp) != NIL, 0, (CHAR*)"OfrontOPP", 407832);
      if (((*StatSeq__54_s->apar))->typ == OfrontOPT_ubytetyp) {
        ((*StatSeq__54_s->apar))->typ = OfrontOPT_bytetyp;
      }
      OfrontOPB_Assign(&(*StatSeq__54_s->apar), (*StatSeq__54_s->z));
    }
    ((*StatSeq__54_s->apar))->subcl = (BYTE)__ABS((INTEGER)cond);
  } else {
    (*StatSeq__54_s->t) = NIL;
  }
}

static BOOLEAN __71 (OfrontOPT_Object id)
{
  return ((INTEGER)id->mode == 1 && (INTEGER)id->vis == 0) && (INTEGER)id->mnolev == (INTEGER)OfrontOPP_level;
}

static void __65 (void)
{
  BYTE vis, mnolev;
  OfrontOPS_Get(&OfrontOPP_sym);
  if ((INTEGER)OfrontOPP_sym == 40) {
    OfrontOPP_qualident(&(*StatSeq__54_s->id));
    if (__IN(((*StatSeq__54_s->id))->typ->form, 0x4072)) {
      if (!__71((*StatSeq__54_s->id))) {
        OfrontOPP_err(91);
      }
      OfrontOPP_CheckSym(36);
      OfrontOPP_Expression(&(*StatSeq__54_s->apar));
      (*StatSeq__54_s->pos) = OfrontOPM_errpos;
      (*StatSeq__54_s->x) = OfrontOPB_NewLeaf((*StatSeq__54_s->id));
      OfrontOPB_Assign(&(*StatSeq__54_s->x), (*StatSeq__54_s->apar));
      __69((*StatSeq__54_s->x));
      OfrontOPP_CheckSym(30);
      OfrontOPP_Expression(&(*StatSeq__54_s->y));
      (*StatSeq__54_s->pos) = OfrontOPM_errpos;
      if (((*StatSeq__54_s->id))->typ == OfrontOPT_ubytetyp) {
        ((*StatSeq__54_s->y))->typ = OfrontOPT_ubytetyp;
      }
      if ((INTEGER)OfrontOPP_sym == 31) {
        OfrontOPS_Get(&OfrontOPP_sym);
        OfrontOPP_ConstExpression(&(*StatSeq__54_s->z));
      } else {
        (*StatSeq__54_s->z) = OfrontOPB_NewIntConst(1);
      }
      (*StatSeq__54_s->obj) = NIL;
      if ((INTEGER)((*StatSeq__54_s->y))->class == 7) {
        if ((((*StatSeq__54_s->y))->conval->intval < OfrontOPB_Min(((*StatSeq__54_s->x))->left->typ->form) || ((*StatSeq__54_s->y))->conval->intval > OfrontOPB_Max(((*StatSeq__54_s->x))->left->typ->form)) || ((INTEGER)((*StatSeq__54_s->x))->left->typ->form != 1 && (__IN(((*StatSeq__54_s->y))->typ->form, 0x02000d) || (INTEGER)((*StatSeq__54_s->y))->typ->form > (INTEGER)((*StatSeq__54_s->x))->left->typ->form))) {
          OfrontOPP_err(113);
          (*StatSeq__54_s->y) = OfrontOPB_NewIntConst(0);
        }
        if ((INTEGER)((*StatSeq__54_s->apar))->class == 7) {
          if ((((*StatSeq__54_s->z))->conval->intval > 0 && ((*StatSeq__54_s->apar))->conval->intval <= ((*StatSeq__54_s->y))->conval->intval) || (((*StatSeq__54_s->z))->conval->intval < 0 && ((*StatSeq__54_s->apar))->conval->intval >= ((*StatSeq__54_s->y))->conval->intval)) {
            (*StatSeq__54_s->obj) = (*StatSeq__54_s->id);
          } else {
            (*StatSeq__54_s->id) = NIL;
          }
        } else {
          if ((((*StatSeq__54_s->z))->conval->intval > 0 && ((*StatSeq__54_s->y))->conval->intval == OfrontOPB_Max(((*StatSeq__54_s->id))->typ->form)) || (((*StatSeq__54_s->z))->conval->intval < 0 && ((*StatSeq__54_s->y))->conval->intval == OfrontOPB_Min(((*StatSeq__54_s->id))->typ->form))) {
            (*StatSeq__54_s->obj) = (*StatSeq__54_s->id);
          }
        }
      } else {
        if ((INTEGER)((*StatSeq__54_s->apar))->class == 7) {
          if ((((*StatSeq__54_s->z))->conval->intval > 0 && ((*StatSeq__54_s->apar))->conval->intval == OfrontOPB_Min(((*StatSeq__54_s->id))->typ->form)) || (((*StatSeq__54_s->z))->conval->intval < 0 && ((*StatSeq__54_s->apar))->conval->intval == OfrontOPB_Max(((*StatSeq__54_s->id))->typ->form))) {
            (*StatSeq__54_s->obj) = (*StatSeq__54_s->id);
          }
        }
      }
      if ((*StatSeq__54_s->id) != NIL) {
        __57((*StatSeq__54_s->apar), (*StatSeq__54_s->y), ((*StatSeq__54_s->z))->conval->intval);
        if ((INTEGER)((*StatSeq__54_s->y))->class != 7) {
          __69((*StatSeq__54_s->y));
        }
      }
      (*StatSeq__54_s->pos) = OfrontOPM_errpos;
      if ((((*StatSeq__54_s->z))->conval->intval == 0 || __IN(((*StatSeq__54_s->z))->typ->form, 0x02000d)) || (INTEGER)((*StatSeq__54_s->z))->typ->form > (INTEGER)((*StatSeq__54_s->x))->left->typ->form) {
        if (((INTEGER)((*StatSeq__54_s->x))->left->typ->form != 1 || ((*StatSeq__54_s->z))->conval->intval < -128) || ((*StatSeq__54_s->z))->conval->intval > 127) {
          OfrontOPP_err(63);
          (*StatSeq__54_s->z) = OfrontOPB_NewIntConst(1);
        }
      }
      if ((*StatSeq__54_s->id) != NIL) {
        if ((*StatSeq__54_s->L) != 1) {
          if ((*StatSeq__54_s->e)) {
            __63((*StatSeq__54_s->apar), (*StatSeq__54_s->y), ((*StatSeq__54_s->z))->conval->intval);
          } else {
            if (((*StatSeq__54_s->z))->conval->intval == OfrontOPB_Min(((*StatSeq__54_s->id))->typ->form)) {
              (*StatSeq__54_s->t) = (*StatSeq__54_s->id);
              (*StatSeq__54_s->idtyp) = ((*StatSeq__54_s->id))->typ;
              (*StatSeq__54_s->apar) = OfrontOPB_NewLeaf((*StatSeq__54_s->id));
              OfrontOPB_Assign(&(*StatSeq__54_s->apar), (*StatSeq__54_s->z));
              ((*StatSeq__54_s->apar))->subcl = 16;
            } else {
              (*StatSeq__54_s->t) = NIL;
            }
          }
        }
        if ((*StatSeq__54_s->t) != (*StatSeq__54_s->id)) {
          __MOVE((CHAR*)"@@", (*StatSeq__54_s->name), 3);
          OfrontOPT_Insert((void*)(*StatSeq__54_s->name), 48, &(*StatSeq__54_s->t));
          ((*StatSeq__54_s->t))->name = OfrontOPT_NewName((CHAR*)"@for", 5);
          ((*StatSeq__54_s->t))->mode = 1;
          if (((*StatSeq__54_s->x))->left->typ == OfrontOPT_ubytetyp) {
            ((*StatSeq__54_s->t))->typ = OfrontOPT_bytetyp;
          } else {
            ((*StatSeq__54_s->t))->typ = ((*StatSeq__54_s->x))->left->typ;
          }
          (*StatSeq__54_s->fpar) = OfrontOPT_topScope->scope;
          if ((*StatSeq__54_s->fpar) == NIL) {
            OfrontOPT_topScope->scope = (*StatSeq__54_s->t);
          } else {
            while (((*StatSeq__54_s->fpar))->link != NIL) {
              (*StatSeq__54_s->fpar) = ((*StatSeq__54_s->fpar))->link;
            }
            ((*StatSeq__54_s->fpar))->link = (*StatSeq__54_s->t);
          }
          (*StatSeq__54_s->apar) = OfrontOPB_NewLeaf((*StatSeq__54_s->t));
          OfrontOPB_Assign(&(*StatSeq__54_s->apar), OfrontOPB_NewIntConst(-1));
          ((*StatSeq__54_s->apar))->subcl = 11;
        }
        if ((*StatSeq__54_s->t) == (*StatSeq__54_s->id) && (*StatSeq__54_s->idtyp) == NIL) {
          ((*StatSeq__54_s->x))->right = OfrontOPB_NewShortConst(((*StatSeq__54_s->x))->right->conval->intval - ((*StatSeq__54_s->z))->conval->intval, ((*StatSeq__54_s->id))->typ->size);
        }
        OfrontOPB_Link(StatSeq__54_s->stat, &(*StatSeq__54_s->last), (*StatSeq__54_s->x));
        (*StatSeq__54_s->x) = NIL;
        if ((*StatSeq__54_s->t) != (*StatSeq__54_s->id) && (*StatSeq__54_s->L) != 1) {
          if ((*StatSeq__54_s->e)) {
            (*StatSeq__54_s->s) = OfrontOPB_NewShortConst((*StatSeq__54_s->L), ((*StatSeq__54_s->id))->typ->size);
          } else {
            if ((*StatSeq__54_s->obj) == NIL && (INTEGER)((*StatSeq__54_s->y))->class != 7) {
              (*StatSeq__54_s->pos) = (INTEGER)((*StatSeq__54_s->y))->conval->intval;
              (*StatSeq__54_s->x) = OfrontOPB_NewLeaf((*StatSeq__54_s->t));
              OfrontOPB_Assign(&(*StatSeq__54_s->x), (*StatSeq__54_s->y));
              __69((*StatSeq__54_s->x));
              OfrontOPB_Link(StatSeq__54_s->stat, &(*StatSeq__54_s->last), (*StatSeq__54_s->x));
              (*StatSeq__54_s->y) = (*StatSeq__54_s->x);
            }
            (*StatSeq__54_s->pos) = OfrontOPM_errpos;
            (*StatSeq__54_s->x) = OfrontOPB_NewLeaf((*StatSeq__54_s->id));
            if (((*StatSeq__54_s->x))->typ == OfrontOPT_ubytetyp) {
              ((*StatSeq__54_s->x))->typ = OfrontOPT_bytetyp;
            }
            if ((INTEGER)((*StatSeq__54_s->y))->class == 7) {
              (*StatSeq__54_s->s) = OfrontOPB_NewIntConst(((*StatSeq__54_s->y))->conval->intval);
            } else if ((INTEGER)((*StatSeq__54_s->y))->class == 19) {
              (*StatSeq__54_s->s) = OfrontOPB_NewLeaf((*StatSeq__54_s->t));
            } else {
              (*StatSeq__54_s->s) = (*StatSeq__54_s->y);
            }
            if (((*StatSeq__54_s->z))->conval->intval > 0) {
              OfrontOPB_Op(9, &(*StatSeq__54_s->s), (*StatSeq__54_s->x));
              OfrontOPB_MOp(40, &(*StatSeq__54_s->s));
              OfrontOPB_Op(3, &(*StatSeq__54_s->s), OfrontOPB_NewIntConst(((*StatSeq__54_s->z))->conval->intval));
              OfrontOPB_Op(8, &(*StatSeq__54_s->s), OfrontOPB_NewIntConst(1));
            } else {
              OfrontOPB_Op(9, &(*StatSeq__54_s->x), (*StatSeq__54_s->s));
              OfrontOPB_MOp(40, &(*StatSeq__54_s->x));
              OfrontOPB_Op(3, &(*StatSeq__54_s->x), OfrontOPB_NewIntConst(-((*StatSeq__54_s->z))->conval->intval));
              OfrontOPB_Op(8, &(*StatSeq__54_s->x), OfrontOPB_NewIntConst(1));
              (*StatSeq__54_s->s) = (*StatSeq__54_s->x);
            }
          }
          (*StatSeq__54_s->x) = OfrontOPB_NewLeaf((*StatSeq__54_s->t));
          if (((*StatSeq__54_s->id))->typ == OfrontOPT_ubytetyp) {
            ((*StatSeq__54_s->s))->typ = OfrontOPT_ubytetyp;
          }
          OfrontOPB_Assign(&(*StatSeq__54_s->x), (*StatSeq__54_s->s));
          __69((*StatSeq__54_s->x));
        } else {
          (*StatSeq__54_s->x) = OfrontOPB_NewLeaf((*StatSeq__54_s->id));
          OfrontOPB_Assign(&(*StatSeq__54_s->x), OfrontOPB_NewIntConst(0));
          __69((*StatSeq__54_s->x));
        }
        vis = ((*StatSeq__54_s->id))->vis;
        mnolev = ((*StatSeq__54_s->id))->mnolev;
        if (OfrontOPM_Lang == '3') {
          ((*StatSeq__54_s->id))->vis = 2;
          ((*StatSeq__54_s->id))->mnolev = -128;
        }
      } else {
        (*StatSeq__54_s->x) = NIL;
      }
      OfrontOPP_CheckSym(29);
      OfrontOPP_StatSeq(&(*StatSeq__54_s->s));
      OfrontOPP_CheckSym(43);
      if ((*StatSeq__54_s->id) != NIL) {
        ((*StatSeq__54_s->id))->vis = vis;
        ((*StatSeq__54_s->id))->mnolev = mnolev;
        if ((*StatSeq__54_s->t) == (*StatSeq__54_s->id) && (*StatSeq__54_s->idtyp) == NIL) {
          ((*StatSeq__54_s->x))->link = (*StatSeq__54_s->s);
          (*StatSeq__54_s->s) = OfrontOPB_NewLeaf((*StatSeq__54_s->id));
          OfrontOPB_StPar1(&(*StatSeq__54_s->s), (*StatSeq__54_s->z), 19);
          __69((*StatSeq__54_s->s));
          if (((*StatSeq__54_s->x))->link != NIL) {
            ((*StatSeq__54_s->s))->link = ((*StatSeq__54_s->x))->link;
            ((*StatSeq__54_s->x))->link = NIL;
          }
        }
        if ((*StatSeq__54_s->L) != 1) {
          __69((*StatSeq__54_s->apar));
          OfrontOPB_Construct(23, &(*StatSeq__54_s->s), (*StatSeq__54_s->apar));
          __69((*StatSeq__54_s->s));
          if ((*StatSeq__54_s->t) != (*StatSeq__54_s->id)) {
            (*StatSeq__54_s->apar) = OfrontOPB_NewLeaf((*StatSeq__54_s->id));
            OfrontOPB_StPar1(&(*StatSeq__54_s->apar), (*StatSeq__54_s->z), 19);
            __69((*StatSeq__54_s->apar));
            ((*StatSeq__54_s->x))->link = (*StatSeq__54_s->apar);
            (*StatSeq__54_s->apar) = ((*StatSeq__54_s->s))->left;
            if ((*StatSeq__54_s->apar) == NIL) {
              ((*StatSeq__54_s->s))->left = ((*StatSeq__54_s->x))->link;
            } else {
              while (((*StatSeq__54_s->apar))->link != NIL) {
                (*StatSeq__54_s->apar) = ((*StatSeq__54_s->apar))->link;
              }
              ((*StatSeq__54_s->apar))->link = ((*StatSeq__54_s->x))->link;
            }
            ((*StatSeq__54_s->x))->link = NIL;
          }
          if ((*StatSeq__54_s->t) != (*StatSeq__54_s->id)) {
            ((*StatSeq__54_s->x))->link = (*StatSeq__54_s->s);
          } else {
            (*StatSeq__54_s->x) = (*StatSeq__54_s->s);
          }
        } else {
          (*StatSeq__54_s->x) = (*StatSeq__54_s->s);
        }
        if ((*StatSeq__54_s->obj) == NIL) {
          if ((INTEGER)((*StatSeq__54_s->y))->class == 19) {
            (*StatSeq__54_s->y) = OfrontOPB_NewLeaf((*StatSeq__54_s->t));
          }
          (*StatSeq__54_s->s) = OfrontOPB_NewLeaf((*StatSeq__54_s->id));
          if (((*StatSeq__54_s->id))->typ == OfrontOPT_ubytetyp) {
            OfrontOPB_MOp(40, &(*StatSeq__54_s->y));
          }
          if (((*StatSeq__54_s->z))->conval->intval > 0) {
            OfrontOPB_Op(14, &(*StatSeq__54_s->s), (*StatSeq__54_s->y));
          } else {
            OfrontOPB_Op(16, &(*StatSeq__54_s->s), (*StatSeq__54_s->y));
          }
          OfrontOPB_Construct(15, &(*StatSeq__54_s->s), (*StatSeq__54_s->x));
          __69((*StatSeq__54_s->s));
          (*StatSeq__54_s->lastif) = (*StatSeq__54_s->s);
          OfrontOPB_Construct(20, &(*StatSeq__54_s->s), NIL);
          OfrontOPB_OptIf(&(*StatSeq__54_s->s));
          (*StatSeq__54_s->x) = (*StatSeq__54_s->s);
        }
        (*StatSeq__54_s->pos) = OfrontOPM_errpos;
      } else {
        (*StatSeq__54_s->x) = NIL;
      }
    } else {
      OfrontOPP_err(68);
      OfrontOPP_sym = 49;
    }
  } else {
    OfrontOPP_err(40);
  }
}

static void OfrontOPP_StatSeq (OfrontOPT_Node *stat)
{
  OfrontOPT_Object fpar = NIL;
  OfrontOPT_Object id = NIL;
  OfrontOPT_Object t = NIL;
  OfrontOPT_Object obj = NIL;
  OfrontOPT_Struct idtyp = NIL;
  BOOLEAN e;
  LONGINT L;
  OfrontOPT_Node s = NIL;
  OfrontOPT_Node x = NIL;
  OfrontOPT_Node y = NIL;
  OfrontOPT_Node z = NIL;
  OfrontOPT_Node apar = NIL;
  OfrontOPT_Node last = NIL;
  OfrontOPT_Node lastif = NIL;
  OfrontOPT_Node pre = NIL;
  OfrontOPT_Node lastp = NIL;
  INTEGER pos;
  OfrontOPS_Name name;
  struct StatSeq__54 _s;
  _s.stat = stat;
  _s.fpar = &fpar;
  _s.id = &id;
  _s.t = &t;
  _s.obj = &obj;
  _s.idtyp = &idtyp;
  _s.e = &e;
  _s.L = &L;
  _s.s = &s;
  _s.x = &x;
  _s.y = &y;
  _s.z = &z;
  _s.apar = &apar;
  _s.last = &last;
  _s.lastif = &lastif;
  _s.pos = &pos;
  _s.name = (void*)name;
  _s.lnk = StatSeq__54_s;
  StatSeq__54_s = &_s;
  *stat = NIL;
  last = NIL;
  OfrontOPP_ReturnLevel += 1;
  for (;;) {
    x = NIL;
    if ((INTEGER)OfrontOPP_sym < 40) {
      OfrontOPP_err(14);
      do {
        OfrontOPS_Get(&OfrontOPP_sym);
      } while (!((INTEGER)OfrontOPP_sym >= 40));
    }
    if ((INTEGER)OfrontOPP_sym == 40) {
      OfrontOPP_qualident(&id);
      x = OfrontOPB_NewLeaf(id);
      OfrontOPP_selector(&x);
      if ((INTEGER)OfrontOPP_sym == 36) {
        OfrontOPS_Get(&OfrontOPP_sym);
        OfrontOPP_Expression(&y);
        if ((OfrontOPM_Lang == 'C' && (INTEGER)y->typ->form == 13) && (INTEGER)x->typ->form == 16) {
          OfrontOPB_DeRef(&y);
        }
        pre = NIL;
        lastp = NIL;
        OfrontOPB_CheckBuffering(&y, x, NIL, &pre, &lastp);
        OfrontOPB_Assign(&x, y);
        if (pre != NIL) {
          __69(x);
          OfrontOPB_Construct(29, &pre, x);
          x = pre;
        }
      } else if ((INTEGER)OfrontOPP_sym == 11) {
        OfrontOPP_err(36);
        OfrontOPS_Get(&OfrontOPP_sym);
        OfrontOPP_Expression(&y);
        OfrontOPB_Assign(&x, y);
      } else if ((INTEGER)x->class == 9 && (INTEGER)x->obj->mode == 8) {
        OfrontOPP_StandProcCall(&x);
        if (x != NIL && x->typ != OfrontOPT_notyp) {
          OfrontOPP_err(55);
        }
      } else if (OfrontOPM_Lang != '3' && (INTEGER)x->class == 13) {
        OfrontOPP_err(55);
      } else {
        pre = NIL;
        lastp = NIL;
        OfrontOPB_PrepCall(&x, &fpar);
        if (x->obj != NIL && (INTEGER)x->obj->mode == 13) {
          OfrontOPB_CheckBuffering(&x->left, NIL, x->obj->link, &pre, &lastp);
        }
        if ((INTEGER)OfrontOPP_sym == 32) {
          OfrontOPS_Get(&OfrontOPP_sym);
          OfrontOPP_ActualParameters(&apar, fpar, &pre, &lastp);
          OfrontOPP_CheckSym(24);
        } else {
          apar = NIL;
          if (fpar != NIL) {
            OfrontOPP_err(65);
          }
        }
        OfrontOPB_Call(&x, apar, fpar);
        if (x->typ != OfrontOPT_notyp) {
          OfrontOPP_err(55);
        }
        if (pre != NIL) {
          __69(x);
          OfrontOPB_Construct(29, &pre, x);
          x = pre;
        }
        if ((INTEGER)OfrontOPP_level > 0) {
          OfrontOPT_topScope->link->leaf = 0;
        }
      }
      pos = OfrontOPM_errpos;
    } else if ((INTEGER)OfrontOPP_sym == 47) {
      OfrontOPS_Get(&OfrontOPP_sym);
      OfrontOPP_Expression(&x);
      __61(&x);
      OfrontOPP_CheckSym(28);
      OfrontOPP_StatSeq(&y);
      OfrontOPB_Construct(15, &x, y);
      __69(x);
      lastif = x;
      while ((INTEGER)OfrontOPP_sym == 45) {
        OfrontOPS_Get(&OfrontOPP_sym);
        OfrontOPP_Expression(&y);
        __61(&y);
        OfrontOPP_CheckSym(28);
        OfrontOPP_StatSeq(&z);
        OfrontOPB_Construct(15, &y, z);
        __69(y);
        OfrontOPB_Link(&x, &lastif, y);
      }
      if ((INTEGER)OfrontOPP_sym == 44) {
        OfrontOPS_Get(&OfrontOPP_sym);
        OfrontOPP_StatSeq(&y);
      } else {
        y = NIL;
      }
      OfrontOPB_Construct(20, &x, y);
      OfrontOPP_CheckSym(43);
      OfrontOPB_OptIf(&x);
      pos = OfrontOPM_errpos;
    } else if ((INTEGER)OfrontOPP_sym == 48) {
      OfrontOPS_Get(&OfrontOPP_sym);
      __59(&x);
      OfrontOPP_CheckSym(43);
    } else if ((INTEGER)OfrontOPP_sym == 49) {
      OfrontOPS_Get(&OfrontOPP_sym);
      OfrontOPP_Expression(&x);
      __61(&x);
      OfrontOPP_CheckSym(29);
      OfrontOPP_StatSeq(&y);
      if ((INTEGER)OfrontOPP_sym == 43) {
        OfrontOPB_Construct(22, &x, y);
      } else if ((INTEGER)OfrontOPP_sym == 45 && OfrontOPM_Lang == '7') {
        OfrontOPB_Construct(11, &z, NIL);
        __69(z);
        OfrontOPB_Link(stat, &last, z);
        OfrontOPB_Construct(15, &x, y);
        __69(x);
        lastif = x;
        do {
          OfrontOPS_Get(&OfrontOPP_sym);
          OfrontOPP_Expression(&y);
          __61(&y);
          OfrontOPP_CheckSym(29);
          OfrontOPP_StatSeq(&z);
          OfrontOPB_Construct(15, &y, z);
          __69(y);
          OfrontOPB_Link(&x, &lastif, y);
        } while (!((INTEGER)OfrontOPP_sym != 45));
        OfrontOPB_Construct(20, &x, NIL);
        OfrontOPB_OptIf(&x);
        pos = OfrontOPM_errpos;
        __69(x);
        OfrontOPB_Link(stat, &last, x);
        OfrontOPB_Construct(12, &x, NIL);
      }
      OfrontOPP_CheckSym(43);
    } else if ((INTEGER)OfrontOPP_sym == 50) {
      OfrontOPS_Get(&OfrontOPP_sym);
      OfrontOPP_StatSeq(&x);
      if ((INTEGER)OfrontOPP_sym == 46) {
        OfrontOPS_Get(&OfrontOPP_sym);
        OfrontOPP_Expression(&y);
        __61(&y);
      } else {
        OfrontOPP_err(46);
      }
      OfrontOPB_Construct(23, &x, y);
    } else if ((INTEGER)OfrontOPP_sym == 51) {
      if (__IN(12, OfrontOPM_opt)) {
        __65();
      } else {
        __67();
      }
    } else if ((INTEGER)OfrontOPP_sym == 52) {
      OfrontOPS_Get(&OfrontOPP_sym);
      OfrontOPP_LoopLevel += 1;
      OfrontOPP_StatSeq(&x);
      OfrontOPP_LoopLevel -= 1;
      OfrontOPB_Construct(24, &x, NIL);
      OfrontOPP_CheckSym(43);
      pos = OfrontOPM_errpos;
    } else if ((INTEGER)OfrontOPP_sym == 53) {
      OfrontOPS_Get(&OfrontOPP_sym);
      idtyp = NIL;
      x = NIL;
      for (;;) {
        if ((INTEGER)OfrontOPP_sym == 40) {
          OfrontOPP_qualident(&id);
          y = OfrontOPB_NewLeaf(id);
          if ((id != NIL && (INTEGER)id->typ->form == 13) && ((INTEGER)id->mode == 2 || !id->leaf)) {
            OfrontOPP_err(245);
          }
          OfrontOPP_CheckSym(22);
          if ((INTEGER)OfrontOPP_sym == 40) {
            OfrontOPP_qualident(&t);
            if ((INTEGER)t->mode == 5) {
              if (id != NIL) {
                idtyp = id->typ;
                OfrontOPB_TypTest(&y, t, 0);
                id->typ = t->typ;
                if (id->ptyp == NIL) {
                  id->ptyp = idtyp;
                }
              } else {
                OfrontOPP_err(130);
              }
            } else {
              OfrontOPP_err(52);
            }
          } else {
            OfrontOPP_err(40);
          }
        } else {
          OfrontOPP_err(40);
        }
        pos = OfrontOPM_errpos;
        OfrontOPP_CheckSym(29);
        OfrontOPP_StatSeq(&s);
        OfrontOPB_Construct(15, &y, s);
        __69(y);
        if (idtyp != NIL) {
          if (id->ptyp == idtyp) {
            id->ptyp = NIL;
          }
          id->typ = idtyp;
          idtyp = NIL;
        }
        if (x == NIL) {
          x = y;
          lastif = x;
        } else {
          OfrontOPB_Link(&x, &lastif, y);
        }
        if ((INTEGER)OfrontOPP_sym == 42) {
          OfrontOPS_Get(&OfrontOPP_sym);
        } else {
          break;
        }
      }
      e = (INTEGER)OfrontOPP_sym == 44;
      if (e) {
        OfrontOPS_Get(&OfrontOPP_sym);
        OfrontOPP_StatSeq(&s);
      } else {
        s = NIL;
      }
      OfrontOPB_Construct(27, &x, s);
      OfrontOPP_CheckSym(43);
      if (e) {
        x->subcl = 1;
      }
    } else if ((INTEGER)OfrontOPP_sym == 54) {
      OfrontOPS_Get(&OfrontOPP_sym);
      if ((INTEGER)OfrontOPP_LoopLevel == 0) {
        OfrontOPP_err(47);
      }
      OfrontOPB_Construct(25, &x, NIL);
      pos = OfrontOPM_errpos;
    } else if ((INTEGER)OfrontOPP_sym == 55) {
      OfrontOPS_Get(&OfrontOPP_sym);
      if (OfrontOPM_Lang == '7') {
        if ((INTEGER)OfrontOPP_sym < 41 && (INTEGER)OfrontOPP_ReturnLevel == 1) {
          OfrontOPP_Expression(&x);
        } else {
          OfrontOPP_err(49);
        }
      } else if ((INTEGER)OfrontOPP_sym < 41) {
        OfrontOPP_Expression(&x);
      }
      if ((INTEGER)OfrontOPP_level > 0) {
        OfrontOPB_Return(&x, OfrontOPT_topScope->link);
      } else {
        OfrontOPB_Return(&x, NIL);
        OfrontOPP_err(-49);
      }
      OfrontOPP_hasReturn = 1;
      pos = OfrontOPM_errpos;
      if (OfrontOPM_Lang == '7') {
        __69(x);
        OfrontOPB_Link(stat, &last, x);
        break;
      }
    } else if ((INTEGER)OfrontOPP_sym == 70) {
      __NEW(x, OfrontOPT_NodeDesc);
      x->conval = OfrontOPT_NewConst();
      x->conval->ext = OfrontOPS_str;
      OfrontOPB_Construct(30, &x, NIL);
      OfrontOPP_sym = 41;
    }
    if (x != NIL) {
      __69(x);
      OfrontOPB_Link(stat, &last, x);
    }
    if (OfrontOPM_Lang == '7' && (INTEGER)OfrontOPP_sym == 55) {
    } else if ((INTEGER)OfrontOPP_sym == 41) {
      OfrontOPS_Get(&OfrontOPP_sym);
    } else if ((INTEGER)OfrontOPP_sym <= 40 || (47 <= (INTEGER)OfrontOPP_sym && (INTEGER)OfrontOPP_sym <= 55)) {
      if (OfrontOPM_Lang != '3') {
        OfrontOPP_err(41);
      }
    } else {
      break;
    }
  }
  OfrontOPP_ReturnLevel -= 1;
  StatSeq__54_s = _s.lnk;
}

static struct Block__3 {
  OfrontOPT_Node *procdec;
  OfrontOPT_Struct *typ;
  OfrontOPT_Object *obj, *first, *last, *o;
  OfrontOPT_Node *x, *lastdec;
  SHORTINT *i;
  OfrontOPS_Name *rname;
  OfrontOPS_String *name;
  struct Block__3 *lnk;
} *Block__3_s;

static void __4 (void);

static void __4 (void)
{
  for (;;) {
    if ((INTEGER)OfrontOPP_sym == 60) {
      OfrontOPS_Get(&OfrontOPP_sym);
      while ((INTEGER)OfrontOPP_sym == 40) {
        OfrontOPT_Insert((void*)OfrontOPS_name, 48, &(*Block__3_s->obj));
        ((*Block__3_s->obj))->mode = 3;
        OfrontOPP_CheckMark((*Block__3_s->obj));
        ((*Block__3_s->obj))->typ = OfrontOPT_sinttyp;
        ((*Block__3_s->obj))->mode = 1;
        if ((INTEGER)OfrontOPP_sym == 11) {
          OfrontOPS_Get(&OfrontOPP_sym);
          OfrontOPP_ConstExpression(&(*Block__3_s->x));
        } else if ((INTEGER)OfrontOPP_sym == 36) {
          OfrontOPP_err(11);
          OfrontOPS_Get(&OfrontOPP_sym);
          OfrontOPP_ConstExpression(&(*Block__3_s->x));
        } else {
          OfrontOPP_err(11);
          (*Block__3_s->x) = OfrontOPB_NewIntConst(1);
        }
        ((*Block__3_s->obj))->mode = 3;
        ((*Block__3_s->obj))->typ = ((*Block__3_s->x))->typ;
        ((*Block__3_s->obj))->conval = ((*Block__3_s->x))->conval;
        if (((*Block__3_s->obj))->conval->arr != NIL) {
          ((*Block__3_s->obj))->mode = 2;
          if ((INTEGER)((*Block__3_s->obj))->vis == 0) {
            ((*Block__3_s->obj))->vis = 3;
          } else {
            ((*Block__3_s->obj))->vis = 2;
          }
          if (((*Block__3_s->x))->obj != NIL) {
            ((*Block__3_s->obj))->typ = ((*Block__3_s->x))->obj->typ;
          }
          if ((*Block__3_s->last) == NIL) {
            OfrontOPT_topScope->scope = (*Block__3_s->obj);
          } else {
            ((*Block__3_s->last))->link = (*Block__3_s->obj);
          }
          (*Block__3_s->last) = (*Block__3_s->obj);
          (*Block__3_s->first) = NIL;
        }
        OfrontOPP_CheckSym(41);
      }
    }
    if ((INTEGER)OfrontOPP_sym == 61) {
      OfrontOPS_Get(&OfrontOPP_sym);
      while ((INTEGER)OfrontOPP_sym == 40) {
        OfrontOPT_Insert((void*)OfrontOPS_name, 48, &(*Block__3_s->obj));
        ((*Block__3_s->obj))->mode = 5;
        ((*Block__3_s->obj))->typ = OfrontOPT_undftyp;
        OfrontOPP_CheckMark((*Block__3_s->obj));
        ((*Block__3_s->obj))->mode = -1;
        if ((INTEGER)OfrontOPP_sym != 11) {
          OfrontOPP_err(11);
        }
        if (((INTEGER)OfrontOPP_sym == 11 || (INTEGER)OfrontOPP_sym == 36) || (INTEGER)OfrontOPP_sym == 22) {
          OfrontOPS_Get(&OfrontOPP_sym);
          OfrontOPP_Type(&((*Block__3_s->obj))->typ, &(*Block__3_s->name));
          OfrontOPP_SetType(NIL, (*Block__3_s->obj), ((*Block__3_s->obj))->typ, (*Block__3_s->name));
        }
        ((*Block__3_s->obj))->mode = 5;
        if (__IN(((*Block__3_s->obj))->typ->form, 0x0203fe)) {
          (*Block__3_s->typ) = OfrontOPT_NewStr(((*Block__3_s->obj))->typ->form, 1);
          (*Block__3_s->i) = ((*Block__3_s->typ))->ref;
          __GUARDEQP((*Block__3_s->typ), OfrontOPT_StrDesc) = *((*Block__3_s->obj))->typ;
          ((*Block__3_s->typ))->ref = (*Block__3_s->i);
          ((*Block__3_s->typ))->strobj = NIL;
          ((*Block__3_s->typ))->mno = 0;
          ((*Block__3_s->typ))->txtpos = OfrontOPM_errpos;
          ((*Block__3_s->typ))->BaseTyp = ((*Block__3_s->obj))->typ;
          ((*Block__3_s->obj))->typ = (*Block__3_s->typ);
        }
        if (((*Block__3_s->obj))->typ->strobj == NIL) {
          ((*Block__3_s->obj))->typ->strobj = (*Block__3_s->obj);
        }
        if ((INTEGER)((*Block__3_s->obj))->typ->form == 13) {
          (*Block__3_s->typ) = ((*Block__3_s->obj))->typ->BaseTyp;
          if (((*Block__3_s->typ) != NIL && (INTEGER)((*Block__3_s->typ))->comp == 4) && ((*Block__3_s->typ))->strobj == NIL) {
            __STRCOPYCC(((*Block__3_s->obj))->name->data, (*Block__3_s->rname), __MIN(48, ((*Block__3_s->obj))->name->len[0]), (CHAR*)"OfrontOPP", 513305);
            (*Block__3_s->i) = 0;
            while (((*Block__3_s->rname))[__X((*Block__3_s->i), 48, (CHAR*)"OfrontOPP", 513562)] != 0x00) {
              (*Block__3_s->i) += 1;
            }
            ((*Block__3_s->rname))[__X((*Block__3_s->i), 48, (CHAR*)"OfrontOPP", 513814)] = '^';
            ((*Block__3_s->rname))[__X((INTEGER)(*Block__3_s->i) + 1, 48, (CHAR*)"OfrontOPP", 513832)] = 0x00;
            OfrontOPT_Insert((void*)(*Block__3_s->rname), 48, &(*Block__3_s->o));
            ((*Block__3_s->o))->mode = 5;
            ((*Block__3_s->o))->typ = (*Block__3_s->typ);
            ((*Block__3_s->typ))->strobj = (*Block__3_s->o);
          }
        }
        if ((INTEGER)((*Block__3_s->obj))->vis != 0) {
          (*Block__3_s->typ) = ((*Block__3_s->obj))->typ;
          if ((INTEGER)((*Block__3_s->typ))->form == 13) {
            (*Block__3_s->typ) = ((*Block__3_s->typ))->BaseTyp;
          }
          if ((INTEGER)((*Block__3_s->typ))->comp == 4) {
            ((*Block__3_s->typ))->exp = 1;
          }
        }
        OfrontOPP_CheckSym(41);
      }
    }
    if ((INTEGER)OfrontOPP_sym == 62) {
      OfrontOPS_Get(&OfrontOPP_sym);
      while ((INTEGER)OfrontOPP_sym == 40) {
        for (;;) {
          if ((INTEGER)OfrontOPP_sym == 40) {
            OfrontOPT_Insert((void*)OfrontOPS_name, 48, &(*Block__3_s->obj));
            ((*Block__3_s->obj))->mode = 1;
            ((*Block__3_s->obj))->link = NIL;
            ((*Block__3_s->obj))->leaf = (INTEGER)((*Block__3_s->obj))->vis == 0;
            ((*Block__3_s->obj))->typ = OfrontOPT_undftyp;
            OfrontOPP_CheckMark((*Block__3_s->obj));
            if ((*Block__3_s->first) == NIL) {
              (*Block__3_s->first) = (*Block__3_s->obj);
            }
            if ((*Block__3_s->last) == NIL) {
              OfrontOPT_topScope->scope = (*Block__3_s->obj);
            } else {
              ((*Block__3_s->last))->link = (*Block__3_s->obj);
            }
            (*Block__3_s->last) = (*Block__3_s->obj);
          } else {
            OfrontOPP_err(40);
          }
          if ((INTEGER)OfrontOPP_sym == 21) {
            OfrontOPS_Get(&OfrontOPP_sym);
          } else if ((INTEGER)OfrontOPP_sym == 40) {
            OfrontOPP_err(21);
          } else {
            break;
          }
        }
        OfrontOPP_CheckSym(22);
        OfrontOPP_Type(&(*Block__3_s->typ), &(*Block__3_s->name));
        OfrontOPP_CheckAlloc(&(*Block__3_s->typ), 0, OfrontOPM_errpos);
        while ((*Block__3_s->first) != NIL) {
          OfrontOPP_SetType(NIL, (*Block__3_s->first), (*Block__3_s->typ), (*Block__3_s->name));
          (*Block__3_s->first) = ((*Block__3_s->first))->link;
        }
        OfrontOPP_CheckSym(41);
      }
    }
    while ((INTEGER)OfrontOPP_sym == 70) {
      __NEW((*Block__3_s->x), OfrontOPT_NodeDesc);
      ((*Block__3_s->x))->conval = OfrontOPT_NewConst();
      ((*Block__3_s->x))->conval->ext = OfrontOPS_str;
      OfrontOPB_Construct(30, &(*Block__3_s->x), NIL);
      ((*Block__3_s->x))->conval = OfrontOPT_NewConst();
      ((*Block__3_s->x))->conval->intval = OfrontOPM_errpos;
      if ((*Block__3_s->lastdec) == NIL) {
        *Block__3_s->procdec = (*Block__3_s->x);
      } else {
        ((*Block__3_s->lastdec))->link = (*Block__3_s->x);
      }
      (*Block__3_s->lastdec) = (*Block__3_s->x);
      OfrontOPS_Get(&OfrontOPP_sym);
    }
    if ((OfrontOPM_Lang == '7' || (INTEGER)OfrontOPP_sym < 60) || (INTEGER)OfrontOPP_sym > 62) {
      break;
    }
  }
  OfrontOPP_CheckForwardTypes();
}

static void OfrontOPP_Block (OfrontOPT_Node *procdec, OfrontOPT_Node *statseq)
{
  OfrontOPT_Struct typ = NIL;
  OfrontOPT_Object obj = NIL;
  OfrontOPT_Object first = NIL;
  OfrontOPT_Object last = NIL;
  OfrontOPT_Object o = NIL;
  OfrontOPT_Node x = NIL;
  OfrontOPT_Node lastdec = NIL;
  SHORTINT i;
  OfrontOPS_Name rname;
  OfrontOPS_String name = NIL;
  OfrontOPP_Elem rec = NIL;
  struct Block__3 _s;
  _s.procdec = procdec;
  _s.typ = &typ;
  _s.obj = &obj;
  _s.first = &first;
  _s.last = &last;
  _s.o = &o;
  _s.x = &x;
  _s.lastdec = &lastdec;
  _s.i = &i;
  _s.rname = (void*)rname;
  _s.name = &name;
  _s.lnk = Block__3_s;
  Block__3_s = &_s;
  if (((((((INTEGER)OfrontOPP_sym < 59 || (INTEGER)OfrontOPP_sym > 62) && (INTEGER)OfrontOPP_sym != 63) && (INTEGER)OfrontOPP_sym != 43) && (INTEGER)OfrontOPP_sym != 68) && (INTEGER)OfrontOPP_sym != 55) && (INTEGER)OfrontOPP_sym != 70) {
    OfrontOPP_err(33);
  }
  first = NIL;
  last = NIL;
  OfrontOPP_userList = NIL;
  OfrontOPP_recList = NIL;
  *procdec = NIL;
  lastdec = NIL;
  __4();
  OfrontOPT_topScope->adr = OfrontOPM_errpos;
  if (((((INTEGER)OfrontOPP_sym != 63 && (INTEGER)OfrontOPP_sym != 59) && (INTEGER)OfrontOPP_sym != 43) && (INTEGER)OfrontOPP_sym != 68) && (INTEGER)OfrontOPP_sym != 55) {
    OfrontOPP_err(34);
  }
  while ((INTEGER)OfrontOPP_sym == 63) {
    OfrontOPS_Get(&OfrontOPP_sym);
    OfrontOPP_ProcedureDeclaration(&x);
    if (x != NIL) {
      if (lastdec == NIL) {
        *procdec = x;
      } else {
        lastdec->link = x;
      }
      lastdec = x;
    }
    OfrontOPP_CheckSym(41);
    while ((INTEGER)OfrontOPP_sym == 70) {
      __NEW(x, OfrontOPT_NodeDesc);
      x->conval = OfrontOPT_NewConst();
      x->conval->ext = OfrontOPS_str;
      OfrontOPB_Construct(30, &x, NIL);
      x->conval = OfrontOPT_NewConst();
      x->conval->intval = OfrontOPM_errpos;
      if (lastdec == NIL) {
        *procdec = x;
      } else {
        lastdec->link = x;
      }
      lastdec = x;
      OfrontOPS_Get(&OfrontOPP_sym);
    }
    if (OfrontOPM_Lang == '3') {
      __4();
    }
  }
  OfrontOPP_userList = NIL;
  rec = OfrontOPP_recList;
  OfrontOPP_recList = NIL;
  if (OfrontOPM_noerr && OfrontOPM_Lang == 'C') {
    OfrontOPP_CheckRecords(rec);
  }
  OfrontOPP_hasReturn = 0;
  if ((INTEGER)OfrontOPP_sym == 59 && !((INTEGER)OfrontOPP_level == 0 && __IN(15, OfrontOPM_opt))) {
    OfrontOPS_Get(&OfrontOPP_sym);
    OfrontOPP_StatSeq(statseq);
  } else if (OfrontOPM_Lang == '7' && (INTEGER)OfrontOPP_sym == 55) {
    OfrontOPP_StatSeq(statseq);
  } else {
    *statseq = NIL;
  }
  if (((OfrontOPT_topScope->link != NIL && OfrontOPT_topScope->link->typ != OfrontOPT_notyp) && !OfrontOPP_hasReturn) && (INTEGER)OfrontOPT_topScope->link->sysflag == 0) {
    OfrontOPP_err(133);
  }
  if ((INTEGER)OfrontOPP_level == 0 && OfrontOPP_TDinit != NIL) {
    OfrontOPP_lastTDinit->link = *statseq;
    *statseq = OfrontOPP_TDinit;
  }
  Block__3_s = _s.lnk;
}

void OfrontOPP_Module (OfrontOPT_Node *prog, SET opt)
{
  OfrontOPS_Name impName, aliasName;
  OfrontOPT_Node procdec = NIL;
  OfrontOPT_Node statseq = NIL;
  INTEGER c;
  BOOLEAN done;
  OfrontOPS_Init();
  OfrontOPP_LoopLevel = 0;
  OfrontOPP_ReturnLevel = 0;
  OfrontOPP_level = 0;
  OfrontOPS_Get(&OfrontOPP_sym);
  if ((INTEGER)OfrontOPP_sym == 65) {
    OfrontOPS_Get(&OfrontOPP_sym);
  } else {
    OfrontOPP_err(16);
  }
  if ((INTEGER)OfrontOPP_sym == 33) {
    OfrontOPS_Get(&OfrontOPP_sym);
    if ((INTEGER)OfrontOPP_sym == 40 && __STRCMPCC(OfrontOPS_name, (CHAR*)"foreign", 8, (CHAR*)"OfrontOPP", 539142) == 0) {
      OfrontOPM_opt = OfrontOPM_opt | 0xc000;
      OfrontOPS_Get(&OfrontOPP_sym);
    } else if ((INTEGER)OfrontOPP_sym == 40 && __STRCMPCC(OfrontOPS_name, (CHAR*)"main", 5, (CHAR*)"OfrontOPP", 537599) == 0) {
      OfrontOPM_opt |= __SETOF(10);
      OfrontOPS_Get(&OfrontOPP_sym);
    } else if ((INTEGER)OfrontOPP_sym == 40 && __STRCMPCC(OfrontOPS_name, (CHAR*)"noinit", 7, (CHAR*)"OfrontOPP", 538111) == 0) {
      OfrontOPM_opt |= __SETOF(15);
      OfrontOPS_Get(&OfrontOPP_sym);
    } else {
      OfrontOPS_Get(&OfrontOPP_sym);
      OfrontOPP_err(178);
    }
    OfrontOPP_CheckSym(25);
  }
  if ((INTEGER)OfrontOPP_sym == 40) {
    OfrontOPM_LogW(' ');
    OfrontOPM_LogWStr((void*)OfrontOPS_name, 48);
    OfrontOPT_Init((void*)OfrontOPS_name, 48, OfrontOPM_Lang, opt);
    OfrontOPS_Get(&OfrontOPP_sym);
    if (__STRLEN(OfrontOPS_name, 48, (CHAR*)"OfrontOPP", 540730) >= 32) {
      OfrontOPP_err(240);
    }
    OfrontOPP_CheckSym(41);
    if ((INTEGER)OfrontOPP_sym == 64) {
      OfrontOPS_Get(&OfrontOPP_sym);
      for (;;) {
        if ((INTEGER)OfrontOPP_sym == 40) {
          __STRCOPYCC(OfrontOPS_name, aliasName, 48, (CHAR*)"OfrontOPP", 541980);
          __STRCOPYCC(aliasName, impName, 48, (CHAR*)"OfrontOPP", 542003);
          OfrontOPS_Get(&OfrontOPP_sym);
          if ((INTEGER)OfrontOPP_sym == 36) {
            OfrontOPS_Get(&OfrontOPP_sym);
            if ((INTEGER)OfrontOPP_sym == 40) {
              __STRCOPYCC(OfrontOPS_name, impName, 48, (CHAR*)"OfrontOPP", 542511);
              OfrontOPS_Get(&OfrontOPP_sym);
            } else {
              OfrontOPP_err(40);
            }
          }
          OfrontOPT_Import((void*)aliasName, 48, (void*)impName, 48, &done);
        } else {
          OfrontOPP_err(40);
        }
        if ((INTEGER)OfrontOPP_sym == 21) {
          OfrontOPS_Get(&OfrontOPP_sym);
        } else if ((INTEGER)OfrontOPP_sym == 40) {
          OfrontOPP_err(21);
        } else {
          break;
        }
      }
      OfrontOPP_CheckSym(41);
    }
    if (OfrontOPM_noerr) {
      OfrontOPP_TDinit = NIL;
      OfrontOPP_lastTDinit = NIL;
      c = OfrontOPM_errpos;
      OfrontOPP_Block(&procdec, &statseq);
      OfrontOPB_Enter(&procdec, statseq, NIL);
      *prog = procdec;
      (*prog)->conval = OfrontOPT_NewConst();
      (*prog)->conval->intval = c;
      if ((INTEGER)OfrontOPP_sym == 68 && !__IN(15, OfrontOPM_opt)) {
        OfrontOPM_opt |= __SETOF(19);
        OfrontOPS_Get(&OfrontOPP_sym);
        OfrontOPP_StatSeq(&(*prog)->link);
      }
      OfrontOPP_CheckSym(43);
      if ((INTEGER)OfrontOPP_sym == 40) {
        if (__STRCMPCC(OfrontOPS_name, OfrontOPT_SelfName, 48, (CHAR*)"OfrontOPP", 547631) != 0) {
          OfrontOPP_err(4);
        }
        OfrontOPS_Get(&OfrontOPP_sym);
      } else {
        OfrontOPP_err(40);
      }
      if ((INTEGER)OfrontOPP_sym != 20) {
        OfrontOPP_err(20);
      }
    }
  } else {
    OfrontOPP_err(40);
  }
  OfrontOPP_TDinit = NIL;
  OfrontOPP_lastTDinit = NIL;
}

/*----------------------------------------------------------------------------*/
static void EnumPtrs(void (*P)(void*))
{
  P(OfrontOPP_TDinit);
  P(OfrontOPP_lastTDinit);
  P(OfrontOPP_userList);
  P(OfrontOPP_recList);
}

__TDESC(OfrontOPP_Elem__rec__desc, 2, 5) = {__TDFLDS("Elem__rec", 48), {0, 8, 16, 24, 40, -48}};
__TDESC(OfrontOPP__1__desc, 2, 0) = {__TDFLDS("", 8), {-8}};

export void *OfrontOPP__init (void)
{
  __DEFMOD;
  __IMPORT(OfrontOPB__init);
  __IMPORT(OfrontOPM__init);
  __IMPORT(OfrontOPS__init);
  __IMPORT(OfrontOPT__init);
  __REGMOD("OfrontOPP", EnumPtrs);
  __INITYP(OfrontOPP_Elem__rec, OfrontOPP_Elem__rec, 0);
  __INITYP(OfrontOPP__1, OfrontOPP__1, 0);
/* BEGIN */
  __ENDMOD;
}
