/* Ofront+ 1.0 -sC -44 */
#include "SYSTEM.oh"
#include "OfrontOPT.oh"
#include "OfrontOPS.oh"
#include "OfrontOPM.oh"


static INTEGER OfrontOPC_indentLevel;
static BOOLEAN OfrontOPC_ptrinit, OfrontOPC_mainprog, OfrontOPC_ansi, OfrontOPC_oldc, OfrontOPC_dynlib, OfrontOPC_windows;
export BOOLEAN OfrontOPC_retmain;
static SHORTINT OfrontOPC_hashtab[169];
static CHAR OfrontOPC_keytab[37][9];
static BOOLEAN OfrontOPC_GlbPtrs;
static CHAR OfrontOPC_BodyNameExt[15], OfrontOPC_CloseNameExt[15];
static OfrontOPT_Struct OfrontOPC_arrayTypes[1024];
static INTEGER OfrontOPC_arrayIndex;


export void OfrontOPC_Align (INTEGER *adr, INTEGER base);
export void OfrontOPC_Andent (OfrontOPT_Struct typ);
static void OfrontOPC_AnsiParamList (OfrontOPT_Object obj, BOOLEAN showParamNames);
export BOOLEAN OfrontOPC_ArrayType (OfrontOPT_Struct typ);
export INTEGER OfrontOPC_BaseAlignment (OfrontOPT_Struct typ, SHORTINT sysflag);
export OfrontOPT_Object OfrontOPC_BaseTProc (OfrontOPT_Object obj);
export void OfrontOPC_BegBlk (void);
export void OfrontOPC_BegStat (void);
static void OfrontOPC_CProcDefs (OfrontOPT_Object obj, SHORTINT vis);
export void OfrontOPC_Case (INTEGER caseVal, SHORTINT form);
export void OfrontOPC_CleanupArrays (void);
export void OfrontOPC_Cmp (SHORTINT rel);
export void OfrontOPC_CompleteIdent (OfrontOPT_Object obj);
export void OfrontOPC_CompleteIdentAdr (OfrontOPT_Object obj);
export void OfrontOPC_Constant (OfrontOPT_Const con, SHORTINT form);
static void OfrontOPC_DeclareBase (OfrontOPT_Object dcl);
static void OfrontOPC_DeclareObj (OfrontOPT_Object dcl, INTEGER vis);
static void OfrontOPC_DeclareObjEx (OfrontOPT_Object dcl, INTEGER vis, INTEGER *n);
static void OfrontOPC_DeclareParams (OfrontOPT_Object par, BOOLEAN macro);
static void OfrontOPC_DeclareReturnType (OfrontOPT_Struct retTyp);
static void OfrontOPC_DeclareTProcs (OfrontOPT_Object obj, BOOLEAN *empty);
static void OfrontOPC_DefAnonArrays (void);
static void OfrontOPC_DefAnonRecs (OfrontOPT_Node n);
static void OfrontOPC_DefineCyclicType (OfrontOPT_Struct str);
export void OfrontOPC_DefineInter (OfrontOPT_Object proc);
static void OfrontOPC_DefineTProcMacros (OfrontOPT_Object obj, BOOLEAN *empty);
static void OfrontOPC_DefineTProcTypes (OfrontOPT_Object obj);
static void OfrontOPC_DefineType (OfrontOPT_Struct str);
export void OfrontOPC_DllMainBody (BOOLEAN close);
static void OfrontOPC_DoClose (OfrontOPT_Object obj);
export void OfrontOPC_EndBlk (void);
export void OfrontOPC_EndBlk0 (void);
export void OfrontOPC_EndStat (void);
export void OfrontOPC_EnterBody (void);
export void OfrontOPC_EnterClose (void);
export void OfrontOPC_EnterProc (OfrontOPT_Object proc);
export void OfrontOPC_ExitBody (void);
export void OfrontOPC_ExitClose (void);
export void OfrontOPC_ExitProc (OfrontOPT_Object proc, BOOLEAN eoBlock, BOOLEAN implicitRet);
static void OfrontOPC_FieldList (OfrontOPT_Struct typ, BOOLEAN last, INTEGER *off, INTEGER *n, INTEGER *curAlign);
static void OfrontOPC_FillGap (INTEGER gap, INTEGER off, INTEGER align, INTEGER *n, INTEGER *curAlign);
export void OfrontOPC_GenBdy (OfrontOPT_Node n);
static void OfrontOPC_GenDynTypes (OfrontOPT_Node n, SHORTINT vis);
export void OfrontOPC_GenEnumPtrs (OfrontOPT_Object var);
export void OfrontOPC_GenHdr (OfrontOPT_Node n);
export void OfrontOPC_GenHdrIncludes (void);
static void OfrontOPC_GenHeaderMsg (void);
static void OfrontOPC_GenPackedRecEnter (SHORTINT sysflag);
static void OfrontOPC_GenPackedRecLeave (SHORTINT sysflag);
export void OfrontOPC_Halt (INTEGER n);
static BOOLEAN OfrontOPC_HasPtrs (OfrontOPT_Struct typ);
export void OfrontOPC_Ident (OfrontOPT_Object obj);
static void OfrontOPC_IdentList (OfrontOPT_Object obj, SHORTINT vis);
static void OfrontOPC_Include (CHAR *name, INTEGER name__len);
static void OfrontOPC_IncludeImports (SHORTINT vis);
export void OfrontOPC_Increment (BOOLEAN decrement);
export void OfrontOPC_Indent (SHORTINT count);
export void OfrontOPC_Init (void);
static void OfrontOPC_InitImports (OfrontOPT_Object obj);
static void OfrontOPC_InitKeywords (void);
export void OfrontOPC_InitTDesc (OfrontOPT_Struct typ);
static void OfrontOPC_InitTProcs (OfrontOPT_Object typ, OfrontOPT_Object obj);
export void OfrontOPC_InsertArrayType (OfrontOPT_Struct typ);
export void OfrontOPC_Len (OfrontOPT_Object obj, OfrontOPT_Struct array, INTEGER dim);
static void OfrontOPC_LenList (OfrontOPT_Object par, BOOLEAN ansiDefine, BOOLEAN showParamName);
static SHORTINT OfrontOPC_Length (CHAR *s, INTEGER s__len);
export BOOLEAN OfrontOPC_NeedsRetval (OfrontOPT_Object proc);
export INTEGER OfrontOPC_NofPtrs (OfrontOPT_Struct typ);
static SHORTINT OfrontOPC_PerfectHash (CHAR *s, INTEGER s__len);
static BOOLEAN OfrontOPC_Prefixed (OfrontOPS_String x, CHAR *y, INTEGER y__len);
static void OfrontOPC_ProcHeader (OfrontOPT_Object proc, BOOLEAN define);
static void OfrontOPC_ProcPredefs (OfrontOPT_Object obj, BYTE vis);
static void OfrontOPC_PutBase (OfrontOPT_Struct typ);
static void OfrontOPC_PutPtrOffsets (OfrontOPT_Struct typ, INTEGER adr, INTEGER *cnt);
static void OfrontOPC_RegCmds (OfrontOPT_Object obj);
export void OfrontOPC_SetInclude (BOOLEAN exclude);
static INTEGER OfrontOPC_SizeAlignment (INTEGER size, SHORTINT sysflag);
static void OfrontOPC_Stars (OfrontOPT_Struct typ, BOOLEAN forProc, BOOLEAN *openClause);
static void OfrontOPC_Str1 (CHAR *s, INTEGER s__len, INTEGER x);
export void OfrontOPC_TDescDecl (OfrontOPT_Struct typ);
export void OfrontOPC_TypeDefs (OfrontOPT_Object obj);
export void OfrontOPC_TypeOf (OfrontOPT_Object ap);
static BOOLEAN OfrontOPC_Undefined (OfrontOPT_Object obj);
static BOOLEAN OfrontOPC_Universal (OfrontOPT_Struct typ);
static void OfrontOPC_UniversalArrayName (OfrontOPT_Struct typ);
static void OfrontOPC_UniversalArrayNameEx (OfrontOPT_Struct typ, OfrontOPT_Struct initial, BOOLEAN check);
static BOOLEAN OfrontOPC_UniversalEx (OfrontOPT_Struct typ, OfrontOPT_Struct initial, BOOLEAN check);
static void OfrontOPC_WriteCharLiteral (LONGCHAR ch, BOOLEAN wide);
static void OfrontOPC_WriteConstArr (OfrontOPT_Object *obj, OfrontOPT_Struct typ);
static void OfrontOPC_WriteName (CHAR *s, INTEGER s__len);
static void OfrontOPC_WriteStringLiteral (CHAR *str, INTEGER str__len, INTEGER len);


/*============================================================================*/

void OfrontOPC_Init (void)
{
  OfrontOPC_indentLevel = 0;
  OfrontOPC_ptrinit = __IN(5, OfrontOPM_opt);
  OfrontOPC_mainprog = __IN(10, OfrontOPM_opt);
  OfrontOPC_ansi = __IN(6, OfrontOPM_opt);
  OfrontOPC_oldc = __IN(13, OfrontOPM_opt);
  OfrontOPC_dynlib = __IN(11, OfrontOPM_opt);
  OfrontOPC_windows = 0;
  OfrontOPC_retmain = 0;
  if (OfrontOPC_ansi) {
    __MOVE((CHAR*)"__init (void)", OfrontOPC_BodyNameExt, 14);
    __MOVE((CHAR*)"__close (void)", OfrontOPC_CloseNameExt, 15);
  } else {
    __MOVE((CHAR*)"__init ()", OfrontOPC_BodyNameExt, 10);
    __MOVE((CHAR*)"__close ()", OfrontOPC_CloseNameExt, 11);
  }
  OfrontOPC_arrayIndex = 0;
}

/*----------------------------------------------------------------------------*/
void OfrontOPC_Indent (SHORTINT count)
{
  OfrontOPC_indentLevel += count;
}

/*----------------------------------------------------------------------------*/
void OfrontOPC_BegStat (void)
{
  INTEGER i;
  i = OfrontOPC_indentLevel;
  while (i > 0) {
    OfrontOPM_WriteTab();
    i -= 1;
  }
}

/*----------------------------------------------------------------------------*/
void OfrontOPC_EndStat (void)
{
  OfrontOPM_Write(';');
  OfrontOPM_WriteLn();
}

/*----------------------------------------------------------------------------*/
void OfrontOPC_BegBlk (void)
{
  OfrontOPM_Write('{');
  OfrontOPM_WriteLn();
  OfrontOPC_indentLevel += 1;
}

/*----------------------------------------------------------------------------*/
void OfrontOPC_EndBlk (void)
{
  OfrontOPC_indentLevel -= 1;
  OfrontOPC_BegStat();
  OfrontOPM_Write('}');
  OfrontOPM_WriteLn();
}

/*----------------------------------------------------------------------------*/
void OfrontOPC_EndBlk0 (void)
{
  OfrontOPC_indentLevel -= 1;
  OfrontOPC_BegStat();
  OfrontOPM_Write('}');
}

/*----------------------------------------------------------------------------*/
static void OfrontOPC_Str1 (CHAR *s, INTEGER s__len, INTEGER x)
{
  CHAR ch;
  SHORTINT i;
  ch = s[0];
  i = 0;
  while (ch != 0x00) {
    if (ch == '#') {
      OfrontOPM_WriteInt(x);
    } else {
      OfrontOPM_Write(ch);
    }
    i += 1;
    ch = s[__X(i, s__len, (CHAR*)"OfrontOPC", 41983)];
  }
}

static SHORTINT OfrontOPC_Length (CHAR *s, INTEGER s__len)
{
  SHORTINT i;
  i = 0;
  while (s[__X(i, s__len, (CHAR*)"OfrontOPC", 43537)] != 0x00) {
    i += 1;
  }
  return i;
}

static SHORTINT OfrontOPC_PerfectHash (CHAR *s, INTEGER s__len)
{
  SHORTINT i, h;
  i = 0;
  h = 0;
  while (s[__X(i, s__len, (CHAR*)"OfrontOPC", 45341)] != 0x00 && (INTEGER)i < 5) {
    h = (SHORTINT)(3 * (INTEGER)h + (INTEGER)s[__X(i, s__len, (CHAR*)"OfrontOPC", 45372)]);
    i += 1;
  }
  return (SHORTINT)__MOD((INTEGER)h, 169);
}

static void OfrontOPC_WriteName (CHAR *s, INTEGER s__len)
{
  INTEGER i;
  CHAR ch;
  if (__STRCMPCC(s, (CHAR*)"Windows", 8, (CHAR*)"OfrontOPC", 49151) == 0) {
    OfrontOPM_WriteString((CHAR*)"Windows_", 9);
  } else {
    i = 0;
    ch = s[0];
    while (ch != 0x00) {
      if (ch == '^') {
        OfrontOPM_WriteString((CHAR*)"__rec", 6);
      } else {
        OfrontOPM_Write(ch);
      }
      i += 1;
      ch = s[__X(i, s__len, (CHAR*)"OfrontOPC", 48639)];
    }
  }
}

void OfrontOPC_Ident (OfrontOPT_Object obj)
{
  SHORTINT mode, level, h;
  OfrontOPS_String _ptr__74 = NIL;
  OfrontOPS_String _ptr__73 = NIL;
  OfrontOPS_String _ptr__72 = NIL;
  OfrontOPS_String _ptr__71 = NIL;
  OfrontOPS_String _ptr__70 = NIL;
  mode = obj->mode;
  level = obj->mnolev;
  if (obj->entry != NIL && (INTEGER)level <= 0) {
    _ptr__74 = obj->entry;
    OfrontOPM_WriteString((void*)_ptr__74->data, _ptr__74->len[0]);
    if (OfrontOPM_currFile == 0 && (INTEGER)level < 0) {
      OfrontOPT_GlbMod[__X(-((INTEGER)level), 64, (CHAR*)"OfrontOPC", 51284)]->vis = 1;
    }
  } else if ((__IN(mode, 0x62) && (INTEGER)level > 0) || (__IN(mode, 0x14) && !(obj->conval != NIL && obj->conval->arr != NIL))) {
    if (!OfrontOPC_oldc) {
      _ptr__73 = obj->name;
      OfrontOPM_WriteString((void*)_ptr__73->data, _ptr__73->len[0]);
    } else {
      OfrontOPM_Write((obj->name->data)[0]);
    }
    h = (_ptr__72 = obj->name, 
      OfrontOPC_PerfectHash((void*)_ptr__72->data, _ptr__72->len[0]));
    if ((INTEGER)OfrontOPC_hashtab[__X(h, 169, (CHAR*)"OfrontOPC", 53503)] >= 0) {
      if (__STRCMPCC(OfrontOPC_keytab[__X(OfrontOPC_hashtab[__X(h, 169, (CHAR*)"OfrontOPC", 53247)], 37, (CHAR*)"OfrontOPC", 53247)], obj->name->data, obj->name->len[0], (CHAR*)"OfrontOPC", 53247) == 0) {
        OfrontOPM_Write('_');
      }
    }
  } else if ((INTEGER)mode == 5 && __IN(obj->typ->form, 0x0243fe)) {
    switch (obj->typ->form) {
      case 1: 
        OfrontOPM_WriteString((CHAR*)"BYTE", 5);
        break;
      case 2: 
        OfrontOPM_WriteString((CHAR*)"BOOLEAN", 8);
        break;
      case 3: case 14: 
        OfrontOPM_WriteString((CHAR*)"CHAR", 5);
        break;
      case 17: 
        OfrontOPM_WriteString((CHAR*)"LONGCHAR", 9);
        break;
      case 4: 
        OfrontOPM_WriteString((CHAR*)"SHORTINT", 9);
        break;
      case 5: 
        OfrontOPM_WriteString((CHAR*)"INTEGER", 8);
        break;
      case 6: 
        OfrontOPM_WriteString((CHAR*)"LONGINT", 8);
        break;
      case 7: 
        OfrontOPM_WriteString((CHAR*)"SHORTREAL", 10);
        break;
      case 8: 
        OfrontOPM_WriteString((CHAR*)"REAL", 5);
        break;
      case 9: 
        OfrontOPM_WriteString((CHAR*)"SET", 4);
        break;
      default: __CASECHK((CHAR*)"OfrontOPC", 56575);
    }
  } else {
    if ((INTEGER)mode != 5 || obj->linkadr != 2) {
      if ((INTEGER)mode == 13) {
        OfrontOPC_Ident(obj->link->typ->strobj);
      } else if ((INTEGER)level < 0) {
        if (!OfrontOPC_oldc) {
          _ptr__71 = OfrontOPT_GlbMod[__X(-((INTEGER)level), 64, (CHAR*)"OfrontOPC", 58111)]->name;
          OfrontOPM_WriteString((void*)_ptr__71->data, _ptr__71->len[0]);
        } else {
          OfrontOPM_Write((OfrontOPT_GlbMod[__X(-((INTEGER)level), 64, (CHAR*)"OfrontOPC", 58367)]->name->data)[0]);
        }
        if (OfrontOPM_currFile == 0) {
          OfrontOPT_GlbMod[__X(-((INTEGER)level), 64, (CHAR*)"OfrontOPC", 58721)]->vis = 1;
        }
      } else if (!OfrontOPC_oldc) {
        OfrontOPM_WriteString((void*)OfrontOPM_modName, 32);
      }
      OfrontOPM_Write('_');
    } else if (obj == OfrontOPT_sysptrtyp->strobj) {
      OfrontOPM_WriteString((CHAR*)"SYSTEM_", 8);
    }
    _ptr__70 = obj->name;
    OfrontOPC_WriteName((void*)_ptr__70->data, _ptr__70->len[0]);
  }
}

/*----------------------------------------------------------------------------*/
static void OfrontOPC_Stars (OfrontOPT_Struct typ, BOOLEAN forProc, BOOLEAN *openClause)
{
  SHORTINT pointers;
  OfrontOPT_Struct t0 = NIL;
  *openClause = 0;
  if ((INTEGER)typ->comp != 4 && (typ->strobj == NIL || (typ->strobj->name->data)[0] == 0x00)) {
    if (__IN(typ->comp, 0x0c)) {
      OfrontOPC_Stars(typ->BaseTyp, forProc, openClause);
      *openClause = (INTEGER)typ->comp == 2;
    } else if ((INTEGER)typ->form == 15) {
      OfrontOPC_Stars(typ->BaseTyp, forProc, openClause);
      OfrontOPM_Write('(');
      if ((INTEGER)typ->sysflag == 1) {
        OfrontOPM_WriteString((CHAR*)"__STDCALL ", 11);
      } else if ((INTEGER)typ->sysflag == 2) {
        OfrontOPM_WriteString((CHAR*)"__FASTCALL ", 12);
      }
      OfrontOPM_Write('*');
    } else if ((INTEGER)typ->form == 13) {
      pointers = 0;
      t0 = typ;
      while ((INTEGER)typ->form == 13 && (typ->strobj == NIL || (typ->strobj->name->data)[0] == 0x00)) {
        pointers += 1;
        typ = typ->BaseTyp;
      }
      if ((INTEGER)typ->comp != 3 && t0 != typ->BaseTyp) {
        __ASSERT(t0 != typ, 0, (CHAR*)"OfrontOPC", 66631);
        OfrontOPC_Stars(typ, forProc, openClause);
      }
      if ((INTEGER)pointers > 0) {
        if (*openClause && !forProc) {
          OfrontOPM_Write('(');
        }
        *openClause = 0;
        while ((INTEGER)pointers > 0) {
          OfrontOPM_Write('*');
          pointers -= 1;
        }
      }
    }
  }
}

static void OfrontOPC_DeclareObjEx (OfrontOPT_Object dcl, INTEGER vis, INTEGER *n)
{
  OfrontOPT_Struct typ = NIL;
  BOOLEAN varPar, openClause;
  SHORTINT form, comp;
  typ = dcl->typ;
  varPar = (((INTEGER)dcl->mode == 2 && (INTEGER)typ->comp != 2) || (INTEGER)typ->comp == 3) || vis == 3;
  OfrontOPC_Stars(typ, 0, &openClause);
  if (varPar) {
    if (openClause) {
      OfrontOPM_Write('(');
    }
    OfrontOPM_Write('*');
  }
  if (dcl->name != OfrontOPT_null) {
    if (((INTEGER)dcl->mode == 4 && (INTEGER)dcl->vis == 0) && OfrontOPM_currFile == 0) {
      OfrontOPC_Str1((CHAR*)"_prvt#", 7, *n);
      *n += 1;
    } else {
      OfrontOPC_Ident(dcl);
    }
    if (vis == 4) {
      OfrontOPM_WriteString((CHAR*)"__copy", 7);
    }
  }
  if (varPar && openClause) {
    OfrontOPM_Write(')');
  }
  openClause = 0;
  for (;;) {
    form = typ->form;
    comp = typ->comp;
    if (((((typ->strobj != NIL && typ->strobj->name != OfrontOPT_null) && (INTEGER)comp != 3) || (INTEGER)form == 12) || (INTEGER)comp == 4) || dcl->typ == typ->BaseTyp) {
      break;
    } else if ((INTEGER)form == 13 && (INTEGER)typ->BaseTyp->comp != 3) {
      openClause = 1;
    } else if ((INTEGER)form == 15 || __IN(comp, 0x0c)) {
      if (openClause) {
        OfrontOPM_Write(')');
        openClause = 0;
      }
      if ((INTEGER)form == 15) {
        if (OfrontOPC_ansi) {
          OfrontOPM_Write(')');
          OfrontOPC_AnsiParamList(typ->link, 0);
        } else {
          OfrontOPM_WriteString((CHAR*)")()", 4);
        }
        OfrontOPC_DeclareReturnType(typ->BaseTyp);
        break;
      } else if ((INTEGER)comp == 2) {
        OfrontOPM_Write('[');
        OfrontOPM_WriteInt(typ->n);
        OfrontOPM_Write(']');
      }
    } else {
      break;
    }
    typ = typ->BaseTyp;
  }
}

static void OfrontOPC_DeclareObj (OfrontOPT_Object dcl, INTEGER vis)
{
  INTEGER n;
  n = 0;
  OfrontOPC_DeclareObjEx(dcl, vis, &n);
}

void OfrontOPC_Andent (OfrontOPT_Struct typ)
{
  if (typ->strobj == NIL || typ->align >= 65536) {
    OfrontOPM_WriteString((void*)OfrontOPM_modName, 32);
    OfrontOPC_Str1((CHAR*)"__#", 4, __ASHR(typ->align, 16, INTEGER));
  } else {
    OfrontOPC_Ident(typ->strobj);
  }
}

/*----------------------------------------------------------------------------*/
static BOOLEAN OfrontOPC_Undefined (OfrontOPT_Object obj)
{
  return ((((INTEGER)obj->mnolev >= 0 && obj->linkadr < 6 + OfrontOPM_currFile) && obj->linkadr != 2) && obj->linkadr != 4 + OfrontOPM_currFile) || obj->name == OfrontOPT_null;
}

BOOLEAN OfrontOPC_ArrayType (OfrontOPT_Struct typ)
{
  if ((INTEGER)typ->comp == 3) {
    return (INTEGER)typ->sysflag == 0;
  }
  return ((INTEGER)typ->comp == 2 && (INTEGER)typ->sysflag == 0) && ((typ->strobj != NIL && typ->strobj->linkadr == 4 + OfrontOPM_currFile) || typ == typ->BaseTyp->BaseTyp);
}

/*----------------------------------------------------------------------------*/
static void OfrontOPC_DeclareBase (OfrontOPT_Object dcl)
{
  OfrontOPT_Struct typ = NIL;
  OfrontOPT_Struct prev = NIL;
  OfrontOPT_Object obj = NIL;
  INTEGER off, n, dummy;
  typ = dcl->typ;
  prev = typ;
  while (((((typ->strobj == NIL || (INTEGER)typ->comp == 3) || OfrontOPC_Undefined(typ->strobj)) && (INTEGER)typ->comp != 4) && (INTEGER)typ->form != 12) && !((INTEGER)typ->form == 13 && OfrontOPC_ArrayType(typ->BaseTyp))) {
    prev = typ;
    typ = typ->BaseTyp;
  }
  obj = typ->strobj;
  if ((INTEGER)typ->form == 12) {
    OfrontOPM_WriteString((CHAR*)"void", 5);
  } else if (obj != NIL && !OfrontOPC_Undefined(obj)) {
    OfrontOPC_Ident(obj);
  } else if ((INTEGER)typ->comp == 4) {
    if (__MASK((INTEGER)typ->sysflag, -256) == 7) {
      OfrontOPM_WriteString((CHAR*)"union ", 7);
    } else {
      OfrontOPM_WriteString((CHAR*)"struct ", 8);
    }
    if (obj == NIL || obj->name != OfrontOPT_null) {
      OfrontOPC_Andent(typ);
    } else {
      OfrontOPM_WriteString((CHAR*)"/* ", 4);
      OfrontOPC_Andent(typ);
      OfrontOPM_WriteString((CHAR*)" */", 4);
    }
    if ((INTEGER)prev->form != 13 && (obj != NIL || dcl->name == OfrontOPT_null)) {
      if (typ->BaseTyp != NIL && (INTEGER)typ->BaseTyp->strobj->vis != 0) {
        OfrontOPM_WriteString((CHAR*)" { /* ", 7);
        OfrontOPC_Ident(typ->BaseTyp->strobj);
        OfrontOPM_WriteString((CHAR*)" */", 4);
        OfrontOPM_WriteLn();
        OfrontOPC_Indent(1);
      } else {
        OfrontOPM_Write(' ');
        OfrontOPC_BegBlk();
      }
      OfrontOPC_FieldList(typ, 1, &off, &n, &dummy);
      OfrontOPC_EndBlk0();
    }
  } else if ((INTEGER)typ->form == 13 && OfrontOPC_ArrayType(typ->BaseTyp)) {
    typ = typ->BaseTyp;
    OfrontOPM_WriteString((CHAR*)"struct ", 8);
    if (OfrontOPC_Universal(typ)) {
      OfrontOPC_UniversalArrayName(typ);
    } else {
      OfrontOPC_Andent(typ);
    }
  }
}

INTEGER OfrontOPC_NofPtrs (OfrontOPT_Struct typ)
{
  OfrontOPT_Object fld = NIL;
  OfrontOPT_Struct btyp = NIL;
  INTEGER n;
  if ((INTEGER)typ->form == 13 && (INTEGER)typ->sysflag == 0) {
    return 1;
  } else if ((INTEGER)typ->comp == 4 && __MASK((INTEGER)typ->sysflag, -256) == 0) {
    btyp = typ->BaseTyp;
    if (btyp != NIL) {
      n = OfrontOPC_NofPtrs(btyp);
    } else {
      n = 0;
    }
    fld = typ->link;
    while (fld != NIL && (INTEGER)fld->mode == 4) {
      if (__STRCMPCC(fld->name->data, (CHAR*)"@ptr", 5, (CHAR*)"OfrontOPC", 104967) != 0) {
        n = n + OfrontOPC_NofPtrs(fld->typ);
      } else {
        n += 1;
      }
      fld = fld->link;
    }
    return n;
  } else if ((INTEGER)typ->comp == 2) {
    btyp = typ->BaseTyp;
    n = typ->n;
    while ((INTEGER)btyp->comp == 2) {
      n = btyp->n * n;
      btyp = btyp->BaseTyp;
    }
    return OfrontOPC_NofPtrs(btyp) * n;
  } else {
    return 0;
  }
  __RETCHK((CHAR*)"OfrontOPC", 107263);
}

/*----------------------------------------------------------------------------*/
static void OfrontOPC_PutPtrOffsets (OfrontOPT_Struct typ, INTEGER adr, INTEGER *cnt)
{
  OfrontOPT_Object fld = NIL;
  OfrontOPT_Struct btyp = NIL;
  INTEGER n, i;
  if ((INTEGER)typ->form == 13 && (INTEGER)typ->sysflag == 0) {
    OfrontOPM_WriteInt(adr);
    OfrontOPM_WriteString((CHAR*)", ", 3);
    *cnt += 1;
    if (__MASK(*cnt, -16) == 0) {
      OfrontOPM_WriteLn();
      OfrontOPM_WriteTab();
    }
  } else if ((INTEGER)typ->comp == 4 && __MASK((INTEGER)typ->sysflag, -256) == 0) {
    btyp = typ->BaseTyp;
    if (btyp != NIL) {
      OfrontOPC_PutPtrOffsets(btyp, adr, cnt);
    }
    fld = typ->link;
    while (fld != NIL && (INTEGER)fld->mode == 4) {
      if (__STRCMPCC(fld->name->data, (CHAR*)"@ptr", 5, (CHAR*)"OfrontOPC", 111879) != 0) {
        OfrontOPC_PutPtrOffsets(fld->typ, adr + fld->adr, cnt);
      } else {
        OfrontOPM_WriteInt(adr + fld->adr);
        OfrontOPM_WriteString((CHAR*)", ", 3);
        *cnt += 1;
        if (__MASK(*cnt, -16) == 0) {
          OfrontOPM_WriteLn();
          OfrontOPM_WriteTab();
        }
      }
      fld = fld->link;
    }
  } else if ((INTEGER)typ->comp == 2) {
    btyp = typ->BaseTyp;
    n = typ->n;
    while ((INTEGER)btyp->comp == 2) {
      n = btyp->n * n;
      btyp = btyp->BaseTyp;
    }
    if (OfrontOPC_NofPtrs(btyp) > 0) {
      i = 0;
      while (i < n) {
        OfrontOPC_PutPtrOffsets(btyp, adr + i * btyp->size, cnt);
        i += 1;
      }
    }
  }
}

static void OfrontOPC_InitTProcs (OfrontOPT_Object typ, OfrontOPT_Object obj)
{
  if (obj != NIL) {
    OfrontOPC_InitTProcs(typ, obj->left);
    if ((INTEGER)obj->mode == 13) {
      OfrontOPC_BegStat();
      OfrontOPM_WriteString((CHAR*)"__INITBP(", 10);
      OfrontOPC_Ident(typ);
      OfrontOPM_WriteString((CHAR*)", ", 3);
      OfrontOPC_Ident(obj);
      OfrontOPC_Str1((CHAR*)", #)", 5, __ASHR(obj->adr, 16, INTEGER));
      OfrontOPC_EndStat();
    }
    OfrontOPC_InitTProcs(typ, obj->right);
  }
}

static void OfrontOPC_PutBase (OfrontOPT_Struct typ)
{
  if (typ != NIL) {
    OfrontOPC_PutBase(typ->BaseTyp);
    OfrontOPC_Ident(typ->strobj);
    OfrontOPM_WriteString((CHAR*)"__typ", 6);
    OfrontOPM_WriteString((CHAR*)", ", 3);
  }
}

static void OfrontOPC_LenList (OfrontOPT_Object par, BOOLEAN ansiDefine, BOOLEAN showParamName)
{
  OfrontOPT_Struct typ = NIL;
  SHORTINT dim;
  if (showParamName) {
    OfrontOPC_Ident(par);
    OfrontOPM_WriteString((CHAR*)"__len", 6);
  }
  dim = 1;
  typ = par->typ->BaseTyp;
  while ((INTEGER)typ->comp == 3 && !__ODD(typ->sysflag)) {
    if (ansiDefine) {
      switch (OfrontOPM_IndexSize) {
        case 2: 
          OfrontOPM_WriteString((CHAR*)", SHORTINT ", 12);
          break;
        case 4: 
          OfrontOPM_WriteString((CHAR*)", INTEGER ", 11);
          break;
        default: 
          OfrontOPM_WriteString((CHAR*)", LONGINT ", 11);
          break;
      }
    } else {
      OfrontOPM_WriteString((CHAR*)", ", 3);
    }
    if (showParamName) {
      OfrontOPC_Ident(par);
      OfrontOPM_WriteString((CHAR*)"__len", 6);
      OfrontOPM_WriteInt(dim);
    }
    typ = typ->BaseTyp;
    dim += 1;
  }
}

static void OfrontOPC_DeclareParams (OfrontOPT_Object par, BOOLEAN macro)
{
  OfrontOPS_String _ptr__27 = NIL;
  OfrontOPS_String _ptr__26 = NIL;
  OfrontOPM_Write('(');
  while (par != NIL) {
    if (macro) {
      _ptr__27 = par->name;
      OfrontOPM_WriteString((void*)_ptr__27->data, _ptr__27->len[0]);
    } else {
      if ((INTEGER)par->mode == 1 && (INTEGER)par->typ->form == 7) {
        OfrontOPM_Write('_');
      }
      OfrontOPC_Ident(par);
    }
    if ((INTEGER)par->typ->comp == 3 && !__ODD(par->typ->sysflag)) {
      OfrontOPM_WriteString((CHAR*)", ", 3);
      OfrontOPC_LenList(par, 0, 1);
    } else if (((INTEGER)par->mode == 2 && (INTEGER)par->typ->comp == 4) && __MASK((INTEGER)par->typ->sysflag, -256) == 0) {
      OfrontOPM_WriteString((CHAR*)", ", 3);
      _ptr__26 = par->name;
      OfrontOPM_WriteString((void*)_ptr__26->data, _ptr__26->len[0]);
      OfrontOPM_WriteString((CHAR*)"__typ", 6);
    }
    par = par->link;
    if (par != NIL) {
      OfrontOPM_WriteString((CHAR*)", ", 3);
    }
  }
  OfrontOPM_Write(')');
}

static void OfrontOPC_DefineTProcTypes (OfrontOPT_Object obj)
{
  OfrontOPT_Object par = NIL;
  if (obj->typ != OfrontOPT_notyp) {
    OfrontOPC_DefineType(obj->typ);
  }
  if (OfrontOPC_ansi) {
    par = obj->link;
    while (par != NIL) {
      OfrontOPC_DefineType(par->typ);
      par = par->link;
    }
  }
}

static void OfrontOPC_DeclareTProcs (OfrontOPT_Object obj, BOOLEAN *empty)
{
  if (obj != NIL) {
    OfrontOPC_DeclareTProcs(obj->left, empty);
    if ((INTEGER)obj->mode == 13) {
      if (obj->typ != OfrontOPT_notyp) {
        OfrontOPC_DefineType(obj->typ);
      }
      if (OfrontOPM_currFile == 0) {
        if ((INTEGER)obj->vis == 1) {
          OfrontOPC_DefineTProcTypes(obj);
          OfrontOPM_WriteString((CHAR*)"import ", 8);
          *empty = 0;
          OfrontOPC_ProcHeader(obj, 0);
        }
      } else {
        *empty = 0;
        OfrontOPC_DefineTProcTypes(obj);
        if ((INTEGER)obj->vis == 0) {
          OfrontOPM_WriteString((CHAR*)"static ", 8);
        } else if (OfrontOPC_dynlib) {
          OfrontOPM_WriteString((CHAR*)"__EXPORT ", 10);
        } else {
          OfrontOPM_WriteString((CHAR*)"export ", 8);
        }
        OfrontOPC_ProcHeader(obj, 0);
      }
    }
    OfrontOPC_DeclareTProcs(obj->right, empty);
  }
}

OfrontOPT_Object OfrontOPC_BaseTProc (OfrontOPT_Object obj)
{
  OfrontOPT_Struct typ = NIL;
  OfrontOPT_Struct base = NIL;
  INTEGER mno;
  OfrontOPS_String _ptr__7 = NIL;
  typ = obj->link->typ;
  if ((INTEGER)typ->form == 13) {
    typ = typ->BaseTyp;
  }
  base = typ->BaseTyp;
  mno = __ASHR(obj->adr, 16, INTEGER);
  while (base != NIL && mno < base->n) {
    typ = base;
    base = typ->BaseTyp;
  }
  _ptr__7 = obj->name;
  OfrontOPT_FindField((void*)_ptr__7->data, _ptr__7->len[0], typ, &obj);
  return obj;
}

/*----------------------------------------------------------------------------*/
static void OfrontOPC_DefineTProcMacros (OfrontOPT_Object obj, BOOLEAN *empty)
{
  BOOLEAN oc;
  if (obj != NIL) {
    OfrontOPC_DefineTProcMacros(obj->left, empty);
    if (((INTEGER)obj->mode == 13 && obj == OfrontOPC_BaseTProc(obj)) && (OfrontOPM_currFile != 0 || (INTEGER)obj->vis == 1)) {
      OfrontOPM_WriteString((CHAR*)"#define __", 11);
      OfrontOPC_Ident(obj);
      OfrontOPC_DeclareParams(obj->link, 1);
      OfrontOPM_WriteString((CHAR*)" __SEND(", 9);
      if ((INTEGER)obj->link->typ->form == 13) {
        OfrontOPM_WriteString((CHAR*)"__TYPEOF(", 10);
        OfrontOPC_Ident(obj->link);
        OfrontOPM_Write(')');
      } else {
        OfrontOPC_Ident(obj->link);
        OfrontOPM_WriteString((CHAR*)"__typ", 6);
      }
      OfrontOPM_WriteString((CHAR*)", ", 3);
      OfrontOPC_Ident(obj);
      OfrontOPC_Str1((CHAR*)", #, ", 6, __ASHR(obj->adr, 16, INTEGER));
      OfrontOPC_DeclareBase(obj);
      if ((INTEGER)obj->typ->form != 12) {
        OfrontOPC_Stars(obj->typ, 1, &oc);
      }
      OfrontOPM_WriteString((CHAR*)"(*)", 4);
      if (OfrontOPC_ansi) {
        OfrontOPC_AnsiParamList(obj->link, 0);
      } else {
        OfrontOPM_WriteString((CHAR*)"()", 3);
      }
      OfrontOPC_DeclareReturnType(obj->typ);
      OfrontOPM_WriteString((CHAR*)", ", 3);
      OfrontOPC_DeclareParams(obj->link, 1);
      OfrontOPM_Write(')');
      OfrontOPM_WriteLn();
    }
    OfrontOPC_DefineTProcMacros(obj->right, empty);
  }
}

void OfrontOPC_InsertArrayType (OfrontOPT_Struct typ)
{
  INTEGER i;
  __ASSERT(__IN(typ->comp, 0x0c), 0, (CHAR*)"OfrontOPC", 152101);
  i = 0;
  while (i < OfrontOPC_arrayIndex) {
    if (OfrontOPT_EqualType(typ, OfrontOPC_arrayTypes[__X(i, 1024, (CHAR*)"OfrontOPC", 152887)])) {
      return;
    }
    i += 1;
  }
  OfrontOPC_arrayTypes[__X(OfrontOPC_arrayIndex, 1024, (CHAR*)"OfrontOPC", 153631)] = typ;
  OfrontOPC_arrayIndex += 1;
}

/*----------------------------------------------------------------------------*/
void OfrontOPC_CleanupArrays (void)
{
  INTEGER i;
  i = 0;
  while (i < OfrontOPC_arrayIndex) {
    OfrontOPC_arrayTypes[__X(i, 1024, (CHAR*)"OfrontOPC", 155694)] = NIL;
    i += 1;
  }
}

/*----------------------------------------------------------------------------*/
static void OfrontOPC_DefineCyclicType (OfrontOPT_Struct str)
{
  OfrontOPT_Object obj = NIL;
  OfrontOPT_Object field = NIL;
  OfrontOPT_Struct base = NIL;
  obj = str->strobj;
  base = str->BaseTyp;
  if ((INTEGER)str->form == 15) {
    OfrontOPM_WriteString((CHAR*)"typedef", 8);
    OfrontOPM_WriteLn();
    OfrontOPM_WriteTab();
    OfrontOPC_Indent(1);
    if (str == base) {
      OfrontOPM_WriteString((CHAR*)"void*", 6);
    } else {
      OfrontOPC_DeclareBase(obj);
    }
    OfrontOPM_WriteString((CHAR*)" (*", 4);
    OfrontOPC_DeclareObj(obj, 0);
    OfrontOPM_WriteString((CHAR*)")()", 4);
    OfrontOPC_EndStat();
    OfrontOPC_Indent(-1);
    OfrontOPM_WriteLn();
    obj->linkadr = 4 + OfrontOPM_currFile;
  } else if (((INTEGER)str->form != 13 && base != NIL) && str == base->BaseTyp) {
    if (base->strobj == NIL) {
      OfrontOPM_WriteString((CHAR*)"typedef", 8);
      OfrontOPM_WriteLn();
      OfrontOPM_WriteTab();
      OfrontOPC_Indent(1);
      OfrontOPM_WriteString((CHAR*)"struct ", 8);
      OfrontOPC_UniversalArrayName(str);
      OfrontOPM_Write(' ');
      obj->typ->strobj = NIL;
      OfrontOPC_DeclareObj(obj, 0);
      obj->typ->strobj = obj;
      OfrontOPC_EndStat();
      OfrontOPC_Indent(-1);
      OfrontOPM_WriteLn();
    }
    obj->linkadr = 4 + OfrontOPM_currFile;
    OfrontOPC_InsertArrayType(str);
  } else if ((INTEGER)str->form == 13 && base->strobj == NIL) {
    OfrontOPM_WriteString((CHAR*)"typedef", 8);
    OfrontOPM_WriteLn();
    OfrontOPM_WriteTab();
    OfrontOPC_Indent(1);
    OfrontOPM_WriteString((CHAR*)"struct ", 8);
    OfrontOPC_Andent(base);
    OfrontOPM_Write(' ');
    obj->typ->strobj = NIL;
    OfrontOPC_DeclareObj(obj, 0);
    obj->typ->strobj = obj;
    OfrontOPC_EndStat();
    OfrontOPC_Indent(-1);
    OfrontOPM_WriteLn();
    obj->linkadr = 4 + OfrontOPM_currFile;
  } else if ((base != NIL && (INTEGER)base->form == 16) && (INTEGER)base->comp == 4) {
    obj->linkadr = 3;
  } else if ((INTEGER)str->comp == 2 && str->strobj != NIL) {
    OfrontOPC_InsertArrayType(str);
    obj->linkadr = 4 + OfrontOPM_currFile;
  }
}

static void OfrontOPC_GenPackedRecEnter (SHORTINT sysflag)
{
  sysflag = (SHORTINT)__MASK((INTEGER)sysflag, -256);
  if (3 <= (INTEGER)sysflag && (INTEGER)sysflag <= 6) {
    OfrontOPM_WriteString((CHAR*)"#pragma pack(push, ", 20);
    switch (sysflag) {
      case 3: 
        OfrontOPM_Write('1');
        break;
      case 4: 
        OfrontOPM_Write('2');
        break;
      case 5: 
        OfrontOPM_Write('4');
        break;
      case 6: 
        OfrontOPM_Write('8');
        break;
      default: __CASECHK((CHAR*)"OfrontOPC", 167423);
    }
    OfrontOPM_Write(')');
    OfrontOPM_WriteLn();
  }
}

static void OfrontOPC_GenPackedRecLeave (SHORTINT sysflag)
{
  sysflag = (SHORTINT)__MASK((INTEGER)sysflag, -256);
  if (3 <= (INTEGER)sysflag && (INTEGER)sysflag <= 6) {
    OfrontOPM_WriteString((CHAR*)"#pragma pack(pop)", 18);
    OfrontOPM_WriteLn();
  }
}

static void OfrontOPC_DefineType (OfrontOPT_Struct str)
{
  OfrontOPT_Object obj = NIL;
  OfrontOPT_Object field = NIL;
  OfrontOPT_Object par = NIL;
  BOOLEAN empty;
  if ((INTEGER)str->comp == 3 || __IN(str->form, 0x0243fe)) {
    return;
  }
  if (OfrontOPM_currFile == 1 || (INTEGER)str->ref < 1754) {
    obj = str->strobj;
    if (obj == NIL || OfrontOPC_Undefined(obj)) {
      if (obj != NIL) {
        if (obj->linkadr == 1) {
          if (OfrontOPM_Lang == 'C') {
            OfrontOPC_DefineCyclicType(str);
          } else if ((INTEGER)str->form != 13 || str->BaseTyp->strobj == NIL) {
            OfrontOPM_Mark(244, str->txtpos);
            obj->linkadr = 2;
          }
        } else {
          obj->linkadr = 1;
        }
      }
      if ((INTEGER)str->comp == 4) {
        if (str->BaseTyp != NIL) {
          OfrontOPC_DefineType(str->BaseTyp);
        }
        field = str->link;
        while (field != NIL && (INTEGER)field->mode == 4) {
          if ((INTEGER)field->vis != 0 || OfrontOPM_currFile == 1) {
            OfrontOPC_DefineType(field->typ);
          }
          field = field->link;
        }
      } else if ((INTEGER)str->form == 13) {
        if ((INTEGER)str->BaseTyp->comp != 4) {
          OfrontOPC_DefineType(str->BaseTyp);
        }
      } else if (__IN(str->comp, 0x0c)) {
        OfrontOPC_DefineType(str->BaseTyp);
      } else if ((INTEGER)str->form == 15) {
        if (str->BaseTyp != OfrontOPT_notyp) {
          OfrontOPC_DefineType(str->BaseTyp);
        }
        field = str->link;
        while (field != NIL) {
          OfrontOPC_DefineType(field->typ);
          field = field->link;
        }
      }
    }
    if (obj != NIL && (OfrontOPC_Undefined(obj) || obj->linkadr == 3)) {
      if (obj->linkadr != 4 + OfrontOPM_currFile || (INTEGER)str->comp == 2) {
        if ((INTEGER)obj->typ->comp == 4) {
          OfrontOPC_GenPackedRecEnter(obj->typ->sysflag);
        }
        OfrontOPM_WriteString((CHAR*)"typedef", 8);
        OfrontOPM_WriteLn();
        OfrontOPM_WriteTab();
        OfrontOPC_Indent(1);
        obj->linkadr = 1;
        OfrontOPC_DeclareBase(obj);
        OfrontOPM_Write(' ');
        obj->typ->strobj = NIL;
        OfrontOPC_DeclareObj(obj, 0);
        obj->typ->strobj = obj;
        obj->linkadr = 6 + OfrontOPM_currFile;
        OfrontOPC_EndStat();
        OfrontOPC_Indent(-1);
        if ((INTEGER)obj->typ->comp == 4) {
          OfrontOPC_GenPackedRecLeave(obj->typ->sysflag);
        }
        OfrontOPM_WriteLn();
        if ((INTEGER)obj->typ->comp == 4) {
          empty = 1;
          OfrontOPC_DeclareTProcs(str->link, &empty);
          OfrontOPC_DefineTProcMacros(str->link, &empty);
          if (!empty) {
            OfrontOPM_WriteLn();
          }
        }
        if ((INTEGER)str->form == 13 && (INTEGER)str->BaseTyp->comp == 2) {
          obj = str->BaseTyp->strobj;
          if (obj != NIL && obj->linkadr == 4 + OfrontOPM_currFile) {
            obj->linkadr = 3;
            OfrontOPC_DefineType(str->BaseTyp);
            obj->linkadr = 4 + OfrontOPM_currFile;
          }
        }
      }
    }
  }
}

static BOOLEAN OfrontOPC_Prefixed (OfrontOPS_String x, CHAR *y, INTEGER y__len)
{
  INTEGER i;
  i = 0;
  while (i < x->len[0] && (x->data)[__X(i, x->len[0], (CHAR*)"OfrontOPC", 187940)] == y[__X(i, y__len, (CHAR*)"OfrontOPC", 187940)]) {
    i += 1;
  }
  return y[__X(i, y__len, (CHAR*)"OfrontOPC", 188415)] == 0x00;
}

static void OfrontOPC_CProcDefs (OfrontOPT_Object obj, SHORTINT vis)
{
  INTEGER i;
  OfrontOPS_String ext = NIL;
  BOOLEAN oc;
  INTEGER _for__11;
  if (obj != NIL) {
    OfrontOPC_CProcDefs(obj->left, vis);
    if (((INTEGER)obj->mode == 9 && (INTEGER)obj->vis >= (INTEGER)vis) && obj->adr == 1) {
      ext = obj->conval->ext;
      if (ext != NIL) {
        if ((ext->data)[0] != '#' && !(OfrontOPC_Prefixed(ext, (CHAR*)"extern ", 8) || OfrontOPC_Prefixed(ext, (CHAR*)"import ", 8))) {
          OfrontOPM_WriteString((CHAR*)"#define ", 9);
          OfrontOPC_Ident(obj);
          OfrontOPC_DeclareParams(obj->link, 1);
          OfrontOPM_WriteTab();
        }
        _for__11 = ext->len[0] - 1;
        i = 0;
        while (i <= _for__11) {
          OfrontOPM_Write((ext->data)[__X(i, ext->len[0], (CHAR*)"OfrontOPC", 192310)]);
          i += 1;
        }
      } else {
        OfrontOPM_WriteString((CHAR*)"import ", 8);
        OfrontOPC_DeclareBase(obj);
        OfrontOPM_Write(' ');
        if (obj->typ != OfrontOPT_notyp) {
          OfrontOPC_Stars(obj->typ, 1, &oc);
        }
        if ((INTEGER)obj->sysflag == 1) {
          OfrontOPM_WriteString((CHAR*)"__STDCALL ", 11);
        } else if ((INTEGER)obj->sysflag == 2) {
          OfrontOPM_WriteString((CHAR*)"__FASTCALL ", 12);
        }
        OfrontOPC_Ident(obj);
        OfrontOPM_Write(' ');
        OfrontOPC_AnsiParamList(obj->link, 1);
        OfrontOPM_Write(';');
      }
      OfrontOPM_WriteLn();
    }
    OfrontOPC_CProcDefs(obj->right, vis);
  }
}

void OfrontOPC_TypeDefs (OfrontOPT_Object obj)
{
  if (obj != NIL) {
    OfrontOPC_TypeDefs(obj->left);
    if ((INTEGER)obj->mode == 5 && obj->typ->txtpos > 0) {
      OfrontOPC_DefineType(obj->typ);
    }
    OfrontOPC_TypeDefs(obj->right);
  }
}

/*----------------------------------------------------------------------------*/
static void OfrontOPC_DefAnonRecs (OfrontOPT_Node n)
{
  OfrontOPT_Object o = NIL;
  OfrontOPT_Struct typ = NIL;
  while (n != NIL && (INTEGER)n->class == 14) {
    typ = n->typ;
    if (typ->strobj == NIL && (OfrontOPM_currFile == 1 || (INTEGER)typ->ref < 1754)) {
      OfrontOPC_DefineType(typ);
      __NEW(o, OfrontOPT_ObjDesc);
      o->typ = typ;
      o->name = OfrontOPT_null;
      OfrontOPC_GenPackedRecEnter(typ->sysflag);
      OfrontOPC_DeclareBase(o);
      OfrontOPC_EndStat();
      OfrontOPC_GenPackedRecLeave(typ->sysflag);
      OfrontOPM_WriteLn();
    }
    n = n->link;
  }
}

static BOOLEAN OfrontOPC_UniversalEx (OfrontOPT_Struct typ, OfrontOPT_Struct initial, BOOLEAN check)
{
  OfrontOPT_Object p = NIL;
  if (check && typ == initial) {
    return 1;
  } else if (__IN(typ->comp, 0x14)) {
    return typ->strobj != NIL && (typ->strobj->name->data)[0] != 0x00;
  } else if (__IN(typ->form, 0x012000)) {
    return OfrontOPC_UniversalEx(typ->BaseTyp, initial, 1);
  } else if ((INTEGER)typ->form == 15) {
    p = typ->link;
    while (p != NIL) {
      if (!OfrontOPC_UniversalEx(p->typ, initial, 1)) {
        return 0;
      }
      p = p->link;
    }
    return OfrontOPC_UniversalEx(typ->BaseTyp, initial, 1);
  }
  return 1;
}

static BOOLEAN OfrontOPC_Universal (OfrontOPT_Struct typ)
{
  return OfrontOPC_UniversalEx(typ, typ, 0);
}

static void OfrontOPC_UniversalArrayNameEx (OfrontOPT_Struct typ, OfrontOPT_Struct initial, BOOLEAN check)
{
  OfrontOPT_Object p = NIL;
  OfrontOPS_String _ptr__116 = NIL;
  if (check && typ == initial) {
  } else if (__IN(typ->form, 0x0243fe)) {
    if (typ->BaseTyp != OfrontOPT_undftyp) {
      typ = typ->BaseTyp;
    }
    _ptr__116 = typ->strobj->name;
    OfrontOPM_WriteString((void*)_ptr__116->data, _ptr__116->len[0]);
  } else if (typ == OfrontOPT_sysptrtyp) {
    OfrontOPC_Ident(typ->strobj);
  } else {
    if ((INTEGER)typ->comp == 4) {
      __ASSERT(typ->strobj != NIL && (typ->strobj->name->data)[0] != 0x00, 100, (CHAR*)"OfrontOPC", 211773);
      OfrontOPC_Ident(typ->strobj);
    } else if ((INTEGER)typ->comp == 2) {
      __ASSERT(typ->strobj != NIL && (typ->strobj->name->data)[0] != 0x00, 100, (CHAR*)"OfrontOPC", 212541);
      OfrontOPC_Ident(typ->strobj);
      OfrontOPM_WriteString((CHAR*)"_OBJ", 5);
    } else if ((INTEGER)typ->comp == 3) {
      OfrontOPC_UniversalArrayNameEx(typ->BaseTyp, initial, 1);
      OfrontOPM_WriteString((CHAR*)"_ARRAY", 7);
    } else if ((INTEGER)typ->form == 13) {
      OfrontOPC_UniversalArrayNameEx(typ->BaseTyp, initial, 1);
      OfrontOPM_WriteString((CHAR*)"_PTR", 5);
    } else if ((INTEGER)typ->form == 15) {
      OfrontOPM_WriteString((CHAR*)"X__", 4);
      p = typ->link;
      while (p != NIL) {
        OfrontOPC_UniversalArrayNameEx(p->typ, initial, 1);
        OfrontOPM_WriteString((CHAR*)"__", 3);
        p = p->link;
      }
      OfrontOPM_Write('X');
      if (typ->BaseTyp != OfrontOPT_notyp) {
        OfrontOPM_Write('R');
        OfrontOPM_WriteString((CHAR*)"__", 3);
        OfrontOPC_UniversalArrayNameEx(typ->BaseTyp, initial, 1);
      }
    } else {
      __HALT(100, (CHAR*)"OfrontOPC", 217343);
    }
  }
}

static void OfrontOPC_UniversalArrayName (OfrontOPT_Struct typ)
{
  OfrontOPC_UniversalArrayNameEx(typ, typ, 0);
}

static void OfrontOPC_DefAnonArrays (void)
{
  INTEGER i;
  OfrontOPT_Struct atyp = NIL;
  OfrontOPT_Struct typ = NIL;
  OfrontOPT_Struct t = NIL;
  OfrontOPT_Object obj = NIL;
  i = 0;
  while (i < OfrontOPC_arrayIndex) {
    atyp = OfrontOPC_arrayTypes[__X(i, 1024, (CHAR*)"OfrontOPC", 220952)];
    typ = atyp;
    if (OfrontOPC_Universal(atyp)) {
      OfrontOPM_WriteString((CHAR*)"#ifndef ", 9);
      OfrontOPC_UniversalArrayName(atyp);
      OfrontOPM_WriteString((CHAR*)"_DEF", 5);
      OfrontOPM_WriteLn();
      OfrontOPM_WriteString((CHAR*)"#define ", 9);
      OfrontOPC_UniversalArrayName(atyp);
      OfrontOPM_WriteString((CHAR*)"_DEF", 5);
      OfrontOPM_WriteLn();
    }
    OfrontOPM_WriteString((CHAR*)"typedef struct ", 16);
    if (OfrontOPC_Universal(atyp)) {
      OfrontOPC_UniversalArrayName(atyp);
    } else {
      OfrontOPC_Andent(atyp);
    }
    OfrontOPM_Write(' ');
    OfrontOPC_BegBlk();
    if ((INTEGER)atyp->comp == 3) {
      OfrontOPC_BegStat();
      switch (OfrontOPM_IndexSize) {
        case 2: 
          OfrontOPC_Str1((CHAR*)"SHORTINT len[#]", 16, atyp->n + 1);
          break;
        case 4: 
          OfrontOPC_Str1((CHAR*)"INTEGER len[#]", 15, atyp->n + 1);
          break;
        default: 
          OfrontOPC_Str1((CHAR*)"LONGINT len[#]", 15, atyp->n + 1);
          break;
      }
      while ((INTEGER)typ->comp == 3) {
        typ = typ->BaseTyp;
      }
      if ((INTEGER)typ->form == 13 && typ != OfrontOPT_sysptrtyp) {
        __NEW(t, OfrontOPT_StrDesc);
        t->BaseTyp = typ->BaseTyp;
        t->sysflag = typ->sysflag;
        typ = t;
        typ->form = 13;
        typ->comp = 1;
      }
      __NEW(t, OfrontOPT_StrDesc);
      t->BaseTyp = typ;
      typ = t;
      typ->form = 16;
      typ->comp = 2;
      typ->n = 1;
      OfrontOPC_EndStat();
    }
    OfrontOPC_BegStat();
    __NEW(obj, OfrontOPT_ObjDesc);
    obj->typ = typ;
    obj->mode = 4;
    obj->vis = 1;
    obj->name = OfrontOPT_NewName((CHAR*)"data", 5);
    obj->linkadr = 0;
    OfrontOPC_DeclareBase(obj);
    OfrontOPM_Write(' ');
    OfrontOPC_DeclareObj(obj, 0);
    OfrontOPC_EndStat();
    OfrontOPC_EndBlk0();
    OfrontOPM_Write(' ');
    if (OfrontOPC_Universal(atyp)) {
      OfrontOPC_UniversalArrayName(atyp);
      OfrontOPM_Write(';');
      OfrontOPM_WriteLn();
      OfrontOPM_WriteString((CHAR*)"#endif ", 8);
      OfrontOPM_WriteLn();
    } else {
      OfrontOPC_Andent(atyp);
      OfrontOPM_Write(';');
      OfrontOPM_WriteLn();
    }
    OfrontOPM_WriteLn();
    i += 1;
  }
}

void OfrontOPC_TDescDecl (OfrontOPT_Struct typ)
{
  INTEGER nofptrs;
  OfrontOPT_Object o = NIL;
  OfrontOPS_String _ptr__108 = NIL;
  if (__MASK((INTEGER)typ->sysflag, -256) == 0) {
    OfrontOPC_BegStat();
    OfrontOPM_WriteString((CHAR*)"__TDESC(", 9);
    OfrontOPC_Andent(typ);
    OfrontOPM_WriteString((CHAR*)"__desc", 7);
    OfrontOPC_Str1((CHAR*)", #", 4, typ->n + 1);
    OfrontOPC_Str1((CHAR*)", #) = {__TDFLDS(", 18, OfrontOPC_NofPtrs(typ));
    OfrontOPM_Write('\"');
    if (typ->strobj != NIL) {
      _ptr__108 = typ->strobj->name;
      OfrontOPC_WriteName((void*)_ptr__108->data, _ptr__108->len[0]);
    }
    OfrontOPC_Str1((CHAR*)"\", #), {", 9, typ->size);
    nofptrs = 0;
    OfrontOPC_PutPtrOffsets(typ, 0, &nofptrs);
    OfrontOPC_Str1((CHAR*)"#}}", 4, -((nofptrs + 1) * (INTEGER)OfrontOPM_AdrSize));
    OfrontOPC_EndStat();
  }
}

/*----------------------------------------------------------------------------*/
void OfrontOPC_InitTDesc (OfrontOPT_Struct typ)
{
  if (__MASK((INTEGER)typ->sysflag, -256) == 0) {
    OfrontOPC_BegStat();
    OfrontOPM_WriteString((CHAR*)"__INITYP(", 10);
    OfrontOPC_Andent(typ);
    OfrontOPM_WriteString((CHAR*)", ", 3);
    if (typ->BaseTyp != NIL) {
      OfrontOPC_Andent(typ->BaseTyp);
    } else {
      OfrontOPC_Andent(typ);
    }
    OfrontOPC_Str1((CHAR*)", #)", 5, typ->extlev);
    OfrontOPC_EndStat();
    if (typ->strobj != NIL) {
      OfrontOPC_InitTProcs(typ->strobj, typ->link);
    }
  }
}

/*----------------------------------------------------------------------------*/
void OfrontOPC_Align (INTEGER *adr, INTEGER base)
{
  switch (base) {
    case 2: 
      *adr += __MASK(*adr, -2);
      break;
    case 4: 
      *adr += __MASK(-*adr, -4);
      break;
    case 8: 
      *adr += __MASK(-*adr, -8);
      break;
    case 16: 
      *adr += __MASK(-*adr, -16);
      break;
    default: 
      break;
  }
}

/*----------------------------------------------------------------------------*/
static INTEGER OfrontOPC_SizeAlignment (INTEGER size, SHORTINT sysflag)
{
  INTEGER alignment;
  switch (__MASK((INTEGER)sysflag, -256)) {
    case 3: 
      alignment = 1;
      break;
    case 4: 
      alignment = 2;
      break;
    case 5: 
      alignment = 4;
      break;
    case 6: 
      alignment = 8;
      break;
    default: 
      alignment = OfrontOPM_Alignment;
      break;
  }
  if (size < alignment) {
    alignment = 1;
    while (alignment < size) {
      alignment = __ASHL(alignment, 1, INTEGER);
    }
  }
  return alignment;
}

INTEGER OfrontOPC_BaseAlignment (OfrontOPT_Struct typ, SHORTINT sysflag)
{
  if ((INTEGER)typ->form == 16) {
    if ((INTEGER)typ->comp == 4) {
      return __MASK(typ->align, -65536);
    } else {
      return OfrontOPC_BaseAlignment(typ->BaseTyp, sysflag);
    }
  }
  return OfrontOPC_SizeAlignment(typ->size, sysflag);
}

/*----------------------------------------------------------------------------*/
static void OfrontOPC_FillGap (INTEGER gap, INTEGER off, INTEGER align, INTEGER *n, INTEGER *curAlign)
{
  INTEGER adr;
  adr = off;
  OfrontOPC_Align(&adr, align);
  if (*curAlign < align && gap - (adr - off) >= align) {
    gap -= (adr - off) + align;
    OfrontOPC_BegStat();
    switch (align) {
      case 2: 
        OfrontOPM_WriteString((CHAR*)"SHORTINT", 9);
        break;
      case 4: 
        OfrontOPM_WriteString((CHAR*)"INTEGER", 8);
        break;
      default: 
        OfrontOPM_WriteString((CHAR*)"LONGINT", 8);
        break;
    }
    OfrontOPC_Str1((CHAR*)" _prvt#", 8, *n);
    *n += 1;
    OfrontOPC_EndStat();
    *curAlign = align;
  }
  if (gap > 0) {
    OfrontOPC_BegStat();
    OfrontOPC_Str1((CHAR*)"char _prvt#", 12, *n);
    *n += 1;
    OfrontOPC_Str1((CHAR*)"[#]", 4, gap);
    OfrontOPC_EndStat();
  }
}

static void OfrontOPC_FieldList (OfrontOPT_Struct typ, BOOLEAN last, INTEGER *off, INTEGER *n, INTEGER *curAlign)
{
  OfrontOPT_Object fld = NIL;
  OfrontOPT_Struct base = NIL;
  INTEGER gap, adr, align, fldAlign;
  fld = typ->link;
  align = __MASK(typ->align, -65536);
  if (typ->BaseTyp != NIL) {
    OfrontOPC_FieldList(typ->BaseTyp, 0, off, n, curAlign);
  } else {
    *off = 0;
    *n = 0;
    *curAlign = 1;
  }
  while (fld != NIL && (INTEGER)fld->mode == 4) {
    if (((OfrontOPM_currFile == 0 && (INTEGER)fld->vis == 0) || ((OfrontOPM_currFile == 1 && (INTEGER)fld->vis == 0) && (INTEGER)typ->mno != 0)) && !OfrontOPT_ContainsRealType(fld->typ)) {
      fld = fld->link;
      while (((fld != NIL && (INTEGER)fld->mode == 4) && (INTEGER)fld->vis == 0) && !OfrontOPT_ContainsRealType(fld->typ)) {
        fld = fld->link;
      }
    } else {
      adr = *off;
      fldAlign = OfrontOPC_BaseAlignment(fld->typ, typ->sysflag);
      OfrontOPC_Align(&adr, fldAlign);
      gap = fld->adr - adr;
      if (fldAlign > *curAlign) {
        *curAlign = fldAlign;
      }
      if (gap > 0) {
        OfrontOPC_FillGap(gap, *off, align, n, curAlign);
      }
      OfrontOPC_BegStat();
      OfrontOPC_DeclareBase(fld);
      OfrontOPM_Write(' ');
      OfrontOPC_DeclareObjEx(fld, 0, n);
      *off = fld->adr + fld->typ->size;
      base = fld->typ;
      fld = fld->link;
      if ((fld != NIL && (INTEGER)fld->typ->form == (INTEGER)base->form) && __IN(base->form, 0x0243fe)) {
        base = fld->typ;
      }
      while ((((fld != NIL && (INTEGER)fld->mode == 4) && fld->typ == base) && fld->adr == *off) && (((OfrontOPM_currFile == 1 || (INTEGER)fld->vis != 0) || fld->typ->strobj == NIL) || OfrontOPT_ContainsRealType(fld->typ))) {
        OfrontOPM_WriteString((CHAR*)", ", 3);
        OfrontOPC_DeclareObjEx(fld, 0, n);
        *off = fld->adr + fld->typ->size;
        fld = fld->link;
        if ((fld != NIL && (INTEGER)fld->typ->form == (INTEGER)base->form) && __IN(base->form, 0x0243fe)) {
          base = fld->typ;
        }
      }
      OfrontOPC_EndStat();
    }
  }
  if (last) {
    adr = typ->size - __ASHR((INTEGER)typ->sysflag, 8, INTEGER);
    if (adr == 0) {
      gap = 1;
    } else {
      gap = adr - *off;
    }
    if (gap > 0) {
      OfrontOPC_FillGap(gap, *off, align, n, curAlign);
    }
  }
}

static BOOLEAN OfrontOPC_HasPtrs (OfrontOPT_Struct typ)
{
  OfrontOPT_Object fld = NIL;
  if (__IN(typ->form, 0xa000)) {
    return 1;
  } else if ((INTEGER)typ->comp == 4) {
    fld = typ->link;
    while (fld != NIL && (INTEGER)fld->mode == 4) {
      if ((__STRCMPCC(fld->name->data, (CHAR*)"@ptr", 5, (CHAR*)"OfrontOPC", 266091) == 0 || __STRCMPCC(fld->name->data, (CHAR*)"@proc", 6, (CHAR*)"OfrontOPC", 266091) == 0) || OfrontOPC_HasPtrs(fld->typ)) {
        return 1;
      }
      fld = fld->link;
    }
    if (typ->BaseTyp != NIL) {
      return OfrontOPC_HasPtrs(typ->BaseTyp);
    }
  } else if ((INTEGER)typ->comp == 2) {
    return OfrontOPC_HasPtrs(typ->BaseTyp);
  }
  return 0;
}

static struct WriteConstArr__119 {
  struct WriteConstArr__119 *lnk;
} *WriteConstArr__119_s;

static void __122 (OfrontOPT_ConstArr arr, INTEGER i, OfrontOPT_Struct bt);

static void __122 (OfrontOPT_ConstArr arr, INTEGER i, OfrontOPT_Struct bt)
{
  switch (bt->size) {
    case 1: 
      if (__IN(bt->form, 0x4008)) {
        OfrontOPM_WriteInt(__MASK((INTEGER)(arr->val1->data)[__X(i, arr->val1->len[0], (CHAR*)"OfrontOPC", 270670)], -256));
      } else {
        OfrontOPM_WriteInt((arr->val1->data)[__X(i, arr->val1->len[0], (CHAR*)"OfrontOPC", 270701)]);
      }
      break;
    case 2: 
      if ((INTEGER)bt->form == 17) {
        OfrontOPM_WriteInt(__MASK((INTEGER)(arr->val1->data)[__X(i, arr->val1->len[0], (CHAR*)"OfrontOPC", 270919)], -65536));
      } else {
        OfrontOPM_WriteInt((arr->val2->data)[__X(i, arr->val2->len[0], (CHAR*)"OfrontOPC", 270950)]);
      }
      break;
    case 4: 
      OfrontOPM_WriteInt((arr->val4->data)[__X(i, arr->val4->len[0], (CHAR*)"OfrontOPC", 271359)]);
      break;
    case 8: 
      OfrontOPM_WriteInt((arr->val8->data)[__X(i, arr->val8->len[0], (CHAR*)"OfrontOPC", 271615)]);
      break;
    default: __CASECHK((CHAR*)"OfrontOPC", 271615);
  }
}

static void OfrontOPC_WriteConstArr (OfrontOPT_Object *obj, OfrontOPT_Struct typ)
{
  OfrontOPT_Node apar = NIL;
  INTEGER i, _for__121, _for__120;
  struct WriteConstArr__119 _s;
  _s.lnk = WriteConstArr__119_s;
  WriteConstArr__119_s = &_s;
  OfrontOPM_WriteString((CHAR*)"{", 2);
  i = 0;
  if ((INTEGER)typ->BaseTyp->form != 16) {
    _for__121 = typ->n - 2;
    i = 0;
    while (i <= _for__121) {
      __122((*obj)->conval->arr, i + (INTEGER)(*obj)->conval->intval, typ->BaseTyp);
      OfrontOPM_WriteString((CHAR*)",", 2);
      if (__MOD(i + 1, 10) == 0) {
        OfrontOPM_WriteLn();
        OfrontOPC_BegStat();
      }
      i += 1;
    }
    __122((*obj)->conval->arr, (typ->n - 1) + (INTEGER)(*obj)->conval->intval, typ->BaseTyp);
    (*obj)->conval->intval += typ->n;
  } else {
    _for__120 = typ->n - 2;
    i = 0;
    while (i <= _for__120) {
      OfrontOPC_WriteConstArr(obj, typ->BaseTyp);
      OfrontOPM_WriteString((CHAR*)",", 2);
      OfrontOPM_WriteLn();
      OfrontOPC_BegStat();
      i += 1;
    }
    OfrontOPC_WriteConstArr(obj, typ->BaseTyp);
  }
  OfrontOPM_WriteString((CHAR*)"}", 2);
  WriteConstArr__119_s = _s.lnk;
}

static void OfrontOPC_IdentList (OfrontOPT_Object obj, SHORTINT vis)
{
  OfrontOPT_Struct base = NIL;
  BOOLEAN first, constarr;
  SHORTINT lastvis;
  base = NIL;
  first = 1;
  while (obj != NIL && (INTEGER)obj->mode != 13) {
    constarr = obj->conval != NIL && obj->conval->arr != NIL;
    if ((constarr && (INTEGER)vis != 0) && (INTEGER)obj->vis != 2) {
    } else if (((__IN(vis, 0x05) || ((INTEGER)vis == 1 && (INTEGER)obj->vis != 0)) || ((INTEGER)vis == 3 && !obj->leaf)) || (((INTEGER)vis == 4 && (INTEGER)obj->typ->comp == 2) && (INTEGER)obj->mode == 1)) {
      if ((base != NIL && (INTEGER)obj->typ->form == (INTEGER)base->form) && __IN(base->form, 0x0243fe)) {
        base = obj->typ;
      }
      if ((obj->typ != base || (INTEGER)obj->vis != (INTEGER)lastvis) || constarr) {
        if (!first) {
          OfrontOPC_EndStat();
        }
        first = 0;
        base = obj->typ;
        lastvis = obj->vis;
        OfrontOPC_BegStat();
        if ((INTEGER)vis == 1 && (INTEGER)obj->vis != 0) {
          OfrontOPM_WriteString((CHAR*)"import ", 8);
        } else if ((INTEGER)obj->mnolev == 0 && (INTEGER)vis == 0) {
          if ((INTEGER)obj->vis == 0 || (constarr && (INTEGER)obj->vis != 2)) {
            OfrontOPM_WriteString((CHAR*)"static ", 8);
          } else if (OfrontOPC_dynlib) {
            if (OfrontOPC_mainprog && obj->entry == NIL) {
              obj->entry = obj->name;
            }
            OfrontOPM_WriteString((CHAR*)"__EXPORT ", 10);
          } else {
            OfrontOPM_WriteString((CHAR*)"export ", 8);
          }
        }
        if (constarr) {
          OfrontOPM_WriteString((CHAR*)"__CONSTARR ", 12);
        }
        if (((INTEGER)vis == 2 && (INTEGER)obj->mode == 1) && (INTEGER)base->form == 7) {
          OfrontOPM_WriteString((CHAR*)"REAL", 5);
        } else {
          OfrontOPC_DeclareBase(obj);
        }
      } else {
        OfrontOPM_Write(',');
      }
      OfrontOPM_Write(' ');
      if (((INTEGER)vis == 2 && (INTEGER)obj->mode == 1) && (INTEGER)base->form == 7) {
        OfrontOPM_Write('_');
      }
      OfrontOPC_DeclareObj(obj, vis);
      if ((INTEGER)obj->typ->comp == 3 && !__ODD(obj->typ->sysflag)) {
        OfrontOPC_EndStat();
        OfrontOPC_BegStat();
        base = OfrontOPT_linttyp;
        switch (OfrontOPM_IndexSize) {
          case 2: 
            OfrontOPM_WriteString((CHAR*)"SHORTINT ", 10);
            break;
          case 4: 
            OfrontOPM_WriteString((CHAR*)"INTEGER ", 9);
            break;
          default: 
            OfrontOPM_WriteString((CHAR*)"LONGINT ", 9);
            break;
        }
        OfrontOPC_LenList(obj, 0, 1);
      } else if (((INTEGER)obj->mode == 2 && (INTEGER)obj->typ->comp == 4) && __MASK((INTEGER)obj->typ->sysflag, -256) == 0) {
        OfrontOPC_EndStat();
        OfrontOPC_BegStat();
        OfrontOPM_WriteString((CHAR*)"void **", 8);
        OfrontOPC_Ident(obj);
        OfrontOPM_WriteString((CHAR*)"__typ", 6);
        base = NIL;
      } else if (constarr && (INTEGER)vis == 0) {
        OfrontOPM_WriteString((CHAR*)" =", 3);
        OfrontOPM_WriteLn();
        OfrontOPC_Indent(1);
        OfrontOPC_BegStat();
        obj->conval->intval = 0;
        OfrontOPC_WriteConstArr(&obj, obj->typ);
        OfrontOPC_Indent(-1);
      } else if ((OfrontOPC_ptrinit && (INTEGER)vis == 0) && (INTEGER)obj->mnolev > 0) {
        if (__IN(obj->typ->form, 0xa000)) {
          OfrontOPM_WriteString((CHAR*)" = NIL", 7);
          base = NIL;
        } else if ((INTEGER)obj->typ->form == 16 && OfrontOPC_HasPtrs(obj->typ)) {
          OfrontOPM_WriteString((CHAR*)" = {0}", 7);
        }
      }
    }
    obj = obj->link;
  }
  if (!first) {
    OfrontOPC_EndStat();
  }
}

static void OfrontOPC_AnsiParamList (OfrontOPT_Object obj, BOOLEAN showParamNames)
{
  OfrontOPS_String name = NIL;
  OfrontOPM_Write('(');
  if (obj == NIL || (INTEGER)obj->mode == 13) {
    OfrontOPM_WriteString((CHAR*)"void", 5);
  } else {
    for (;;) {
      OfrontOPC_DeclareBase(obj);
      if (showParamNames) {
        OfrontOPM_Write(' ');
        OfrontOPC_DeclareObj(obj, 0);
      } else {
        name = obj->name;
        obj->name = OfrontOPT_null;
        OfrontOPC_DeclareObj(obj, 0);
        obj->name = name;
      }
      if ((INTEGER)obj->typ->comp == 3 && !__ODD(obj->typ->sysflag)) {
        switch (OfrontOPM_IndexSize) {
          case 2: 
            OfrontOPM_WriteString((CHAR*)", SHORTINT ", 12);
            break;
          case 4: 
            OfrontOPM_WriteString((CHAR*)", INTEGER ", 11);
            break;
          default: 
            OfrontOPM_WriteString((CHAR*)", LONGINT ", 11);
            break;
        }
        OfrontOPC_LenList(obj, 1, showParamNames);
      } else if (((INTEGER)obj->mode == 2 && (INTEGER)obj->typ->comp == 4) && __MASK((INTEGER)obj->typ->sysflag, -256) == 0) {
        OfrontOPM_WriteString((CHAR*)", void **", 10);
        if (showParamNames) {
          OfrontOPC_Ident(obj);
          OfrontOPM_WriteString((CHAR*)"__typ", 6);
        }
      }
      if (obj->link == NIL || (INTEGER)obj->link->mode == 13) {
        break;
      }
      OfrontOPM_WriteString((CHAR*)", ", 3);
      obj = obj->link;
    }
  }
  OfrontOPM_Write(')');
}

static void OfrontOPC_DeclareReturnType (OfrontOPT_Struct retTyp)
{
  if ((INTEGER)retTyp->form == 15 && (retTyp->strobj == NIL || (retTyp->strobj->name->data)[0] == 0x00)) {
    if (OfrontOPC_ansi) {
      OfrontOPM_Write(')');
      OfrontOPC_AnsiParamList(retTyp->link, 0);
    } else {
      OfrontOPM_WriteString((CHAR*)")()", 4);
    }
    OfrontOPC_DeclareReturnType(retTyp->BaseTyp);
  }
}

static void OfrontOPC_ProcHeader (OfrontOPT_Object proc, BOOLEAN define)
{
  BOOLEAN oc;
  if ((INTEGER)proc->sysflag == 3) {
    OfrontOPM_WriteString((CHAR*)"static inline ", 15);
  }
  OfrontOPC_DeclareBase(proc);
  OfrontOPM_Write(' ');
  if ((INTEGER)proc->typ->form != 12) {
    OfrontOPC_Stars(proc->typ, 1, &oc);
  }
  if ((INTEGER)proc->sysflag == 1) {
    OfrontOPM_WriteString((CHAR*)"__STDCALL ", 11);
  } else if ((INTEGER)proc->sysflag == 2) {
    OfrontOPM_WriteString((CHAR*)"__FASTCALL ", 12);
  }
  OfrontOPC_Ident(proc);
  OfrontOPM_Write(' ');
  if (OfrontOPC_ansi) {
    OfrontOPC_AnsiParamList(proc->link, 1);
    OfrontOPC_DeclareReturnType(proc->typ);
    if (!define) {
      OfrontOPM_Write(';');
    }
    OfrontOPM_WriteLn();
  } else if (define) {
    OfrontOPC_DeclareParams(proc->link, 0);
    OfrontOPC_DeclareReturnType(proc->typ);
    OfrontOPM_WriteLn();
    OfrontOPC_Indent(1);
    OfrontOPC_IdentList(proc->link, 2);
    OfrontOPC_Indent(-1);
  } else {
    OfrontOPM_WriteString((CHAR*)"();", 4);
    OfrontOPM_WriteLn();
  }
}

static void OfrontOPC_ProcPredefs (OfrontOPT_Object obj, BYTE vis)
{
  if (obj != NIL) {
    OfrontOPC_ProcPredefs(obj->left, vis);
    if ((__IN(obj->mode, 0xc0) && (INTEGER)obj->vis >= (INTEGER)vis) && ((INTEGER)obj->history != 4 || (INTEGER)obj->mode == 6)) {
      if ((INTEGER)obj->sysflag == 3) {
      } else if ((INTEGER)vis == 1) {
        if (obj->entry != NIL || OfrontOPC_dynlib) {
          OfrontOPM_WriteString((CHAR*)"__EXTERN ", 10);
        } else {
          OfrontOPM_WriteString((CHAR*)"import ", 8);
        }
      } else if ((INTEGER)obj->vis == 0) {
        if ((INTEGER)obj->mnolev == 0 && obj->entry != NIL) {
          OfrontOPM_WriteString((CHAR*)"__EXTERN ", 10);
        } else {
          OfrontOPM_WriteString((CHAR*)"static ", 8);
        }
      } else if (OfrontOPC_dynlib) {
        if (OfrontOPC_mainprog && obj->entry == NIL) {
          obj->entry = obj->name;
        }
        OfrontOPM_WriteString((CHAR*)"__EXPORT ", 10);
      } else {
        OfrontOPM_WriteString((CHAR*)"export ", 8);
      }
      OfrontOPC_ProcHeader(obj, 0);
    }
    OfrontOPC_ProcPredefs(obj->right, vis);
  }
}

static void OfrontOPC_Include (CHAR *name, INTEGER name__len)
{
  OfrontOPM_WriteString((CHAR*)"#include ", 10);
  OfrontOPM_Write('\"');
  OfrontOPM_WriteString((void*)name, name__len);
  OfrontOPM_WriteString((CHAR*)".oh", 4);
  OfrontOPM_Write('\"');
  OfrontOPM_WriteLn();
}

static void OfrontOPC_IncludeImports (SHORTINT vis)
{
  OfrontOPT_Object mod = NIL;
  INTEGER i;
  OfrontOPS_String _ptr__78 = NIL;
  i = 1;
  while (i < (INTEGER)OfrontOPT_nofGmod) {
    mod = OfrontOPT_GlbMod[__X(i, 64, (CHAR*)"OfrontOPC", 321559)];
    if ((INTEGER)mod->vis >= (INTEGER)vis) {
      _ptr__78 = mod->name;
      OfrontOPC_Include((void*)_ptr__78->data, _ptr__78->len[0]);
      if (__STRCMPCC(mod->name->data, (CHAR*)"WinApi", 7, (CHAR*)"OfrontOPC", 322559) == 0) {
        OfrontOPC_windows = 1;
      }
    }
    i += 1;
  }
}

static void OfrontOPC_GenDynTypes (OfrontOPT_Node n, SHORTINT vis)
{
  OfrontOPT_Struct typ = NIL;
  while (n != NIL && (INTEGER)n->class == 14) {
    typ = n->typ;
    if (__MASK((INTEGER)typ->sysflag, -256) == 0 && ((INTEGER)vis == 0 || (INTEGER)typ->ref < 1754)) {
      OfrontOPC_BegStat();
      if ((INTEGER)vis == 1) {
        OfrontOPM_WriteString((CHAR*)"import ", 8);
      } else if (typ->strobj != NIL && (INTEGER)typ->strobj->mnolev > 0) {
        OfrontOPM_WriteString((CHAR*)"static ", 8);
      } else if (OfrontOPC_dynlib) {
        OfrontOPM_WriteString((CHAR*)"__EXPORT ", 10);
      } else {
        OfrontOPM_WriteString((CHAR*)"export ", 8);
      }
      OfrontOPM_WriteString((CHAR*)"void **", 8);
      OfrontOPC_Andent(typ);
      OfrontOPM_WriteString((CHAR*)"__typ", 6);
      OfrontOPC_EndStat();
    }
    n = n->link;
  }
}

void OfrontOPC_GenHdr (OfrontOPT_Node n)
{
  OfrontOPM_currFile = 0;
  OfrontOPC_DefAnonRecs(n);
  OfrontOPC_TypeDefs(OfrontOPT_topScope->right);
  OfrontOPM_WriteLn();
  OfrontOPC_DefAnonArrays();
  OfrontOPC_IdentList(OfrontOPT_topScope->scope, 1);
  OfrontOPM_WriteLn();
  OfrontOPC_GenDynTypes(n, 1);
  OfrontOPM_WriteLn();
  OfrontOPC_ProcPredefs(OfrontOPT_topScope->right, 1);
  if (!__IN(15, OfrontOPM_opt)) {
    if (OfrontOPC_dynlib) {
      OfrontOPM_WriteString((CHAR*)"__EXTERN ", 10);
    } else {
      OfrontOPM_WriteString((CHAR*)"import ", 8);
    }
    OfrontOPM_WriteString((CHAR*)"void *", 7);
    OfrontOPM_WriteString((void*)OfrontOPM_modName, 32);
    OfrontOPM_WriteString((void*)OfrontOPC_BodyNameExt, 15);
    OfrontOPC_EndStat();
    if (__IN(19, OfrontOPM_opt)) {
      if (OfrontOPC_dynlib) {
        OfrontOPM_WriteString((CHAR*)"__EXTERN ", 10);
      } else {
        OfrontOPM_WriteString((CHAR*)"import ", 8);
      }
      OfrontOPM_WriteString((CHAR*)"void ", 6);
      OfrontOPM_WriteString((void*)OfrontOPM_modName, 32);
      OfrontOPM_WriteString((void*)OfrontOPC_CloseNameExt, 15);
      OfrontOPC_EndStat();
    }
  }
  OfrontOPM_WriteLn();
  OfrontOPC_CProcDefs(OfrontOPT_topScope->right, 1);
  OfrontOPM_WriteLn();
}

/*----------------------------------------------------------------------------*/
static void OfrontOPC_GenHeaderMsg (void)
{
  OfrontOPM_WriteString((CHAR*)"/* ", 4);
  OfrontOPM_WriteString((CHAR*)"Ofront+ 1.0 -", 14);
  if (OfrontOPC_mainprog) {
    OfrontOPM_Write('m');
  } else if (__IN(4, OfrontOPM_opt)) {
    OfrontOPM_Write('s');
  } else if (__IN(9, OfrontOPM_opt)) {
    OfrontOPM_Write('e');
  }
  if (!__IN(0, OfrontOPM_opt)) {
    OfrontOPM_Write('x');
  }
  if (__IN(1, OfrontOPM_opt)) {
    OfrontOPM_Write('v');
  }
  if (__IN(2, OfrontOPM_opt)) {
    OfrontOPM_Write('r');
  }
  if (!__IN(3, OfrontOPM_opt)) {
    OfrontOPM_Write('t');
  }
  if (!__IN(7, OfrontOPM_opt)) {
    OfrontOPM_Write('a');
  }
  if (__IN(13, OfrontOPM_opt)) {
    OfrontOPM_Write('o');
  }
  if (!OfrontOPC_ansi) {
    OfrontOPM_Write('k');
  }
  if (!OfrontOPC_ptrinit) {
    OfrontOPM_Write('p');
  }
  if (__IN(8, OfrontOPM_opt)) {
    OfrontOPM_Write('i');
  }
  if (OfrontOPC_dynlib) {
    OfrontOPM_Write('d');
  }
  if (__IN(18, OfrontOPM_opt)) {
    OfrontOPM_Write('w');
  }
  OfrontOPM_Write(OfrontOPM_Lang);
  if (__IN(12, OfrontOPM_opt)) {
    OfrontOPM_Write('f');
  }
  OfrontOPM_WriteString((CHAR*)" -", 3);
  OfrontOPM_WriteInt(OfrontOPM_AdrSize);
  if ((INTEGER)OfrontOPM_AdrSize != 2) {
    OfrontOPM_WriteInt(OfrontOPM_Alignment);
  } else {
    OfrontOPM_WriteInt(OfrontOPM_SetSize);
  }
  OfrontOPM_WriteString((CHAR*)" */", 4);
  OfrontOPM_WriteLn();
}

void OfrontOPC_GenHdrIncludes (void)
{
  OfrontOPM_currFile = 2;
  OfrontOPC_GenHeaderMsg();
  OfrontOPM_WriteLn();
  OfrontOPM_WriteString((CHAR*)"#ifndef ", 9);
  OfrontOPM_WriteString((void*)OfrontOPM_modName, 32);
  OfrontOPM_WriteString((CHAR*)"__oh", 5);
  OfrontOPM_WriteLn();
  OfrontOPM_WriteString((CHAR*)"#define ", 9);
  OfrontOPM_WriteString((void*)OfrontOPM_modName, 32);
  OfrontOPM_WriteString((CHAR*)"__oh", 5);
  OfrontOPM_WriteLn();
  OfrontOPM_WriteLn();
  OfrontOPC_Include((CHAR*)"SYSTEM", 7);
  OfrontOPC_IncludeImports(1);
  OfrontOPM_WriteLn();
}

/*----------------------------------------------------------------------------*/
void OfrontOPC_GenBdy (OfrontOPT_Node n)
{
  if (__IN(14, OfrontOPM_opt)) {
    OfrontOPM_currFile = -1;
  } else {
    OfrontOPM_currFile = 1;
  }
  OfrontOPC_GenHeaderMsg();
  OfrontOPC_Include((CHAR*)"SYSTEM", 7);
  OfrontOPC_IncludeImports(0);
  OfrontOPM_WriteLn();
  OfrontOPC_DefAnonRecs(n);
  OfrontOPC_TypeDefs(OfrontOPT_topScope->right);
  OfrontOPM_WriteLn();
  OfrontOPC_DefAnonArrays();
  OfrontOPC_IdentList(OfrontOPT_topScope->scope, 0);
  OfrontOPM_WriteLn();
  OfrontOPC_GenDynTypes(n, 0);
  OfrontOPM_WriteLn();
  OfrontOPC_ProcPredefs(OfrontOPT_topScope->right, 0);
  OfrontOPM_WriteLn();
  OfrontOPC_CProcDefs(OfrontOPT_topScope->right, 0);
  OfrontOPM_WriteLn();
  if (((OfrontOPC_mainprog && !OfrontOPC_dynlib) && __IN(19, OfrontOPM_opt)) && !__IN(15, OfrontOPM_opt)) {
    OfrontOPM_WriteString((CHAR*)"static void ", 13);
    OfrontOPM_WriteString((void*)OfrontOPM_modName, 32);
    OfrontOPM_WriteString((void*)OfrontOPC_CloseNameExt, 15);
    OfrontOPC_EndStat();
    OfrontOPM_WriteLn();
  }
  OfrontOPM_WriteString((CHAR*)"/*============================================================================*/", 81);
  OfrontOPM_WriteLn();
  OfrontOPM_WriteLn();
}

/*----------------------------------------------------------------------------*/
static void OfrontOPC_RegCmds (OfrontOPT_Object obj)
{
  OfrontOPS_String _ptr__102 = NIL;
  if (obj != NIL) {
    OfrontOPC_RegCmds(obj->left);
    if ((INTEGER)obj->mode == 7 && (INTEGER)obj->history != 4) {
      if (((INTEGER)obj->vis != 0 && obj->link == NIL) && obj->typ == OfrontOPT_notyp) {
        OfrontOPC_BegStat();
        OfrontOPM_WriteString((CHAR*)"__REGCMD(\"", 11);
        _ptr__102 = obj->name;
        OfrontOPM_WriteString((void*)_ptr__102->data, _ptr__102->len[0]);
        OfrontOPM_WriteString((CHAR*)"\", ", 4);
        OfrontOPC_Ident(obj);
        OfrontOPM_Write(')');
        OfrontOPC_EndStat();
      }
    }
    OfrontOPC_RegCmds(obj->right);
  }
}

static void OfrontOPC_InitImports (OfrontOPT_Object obj)
{
  OfrontOPS_String _ptr__83 = NIL;
  if (obj != NIL) {
    OfrontOPC_InitImports(obj->left);
    if (((INTEGER)obj->mode == 11 && (INTEGER)obj->mnolev != 0) && !__ODD(OfrontOPT_GlbMod[__X(-((INTEGER)obj->mnolev), 64, (CHAR*)"OfrontOPC", 356358)]->sysflag)) {
      OfrontOPC_BegStat();
      OfrontOPM_WriteString((CHAR*)"__IMPORT(", 10);
      _ptr__83 = OfrontOPT_GlbMod[__X(-((INTEGER)obj->mnolev), 64, (CHAR*)"OfrontOPC", 355891)]->name;
      OfrontOPM_WriteString((void*)_ptr__83->data, _ptr__83->len[0]);
      OfrontOPM_WriteString((CHAR*)"__init);", 9);
      OfrontOPM_WriteLn();
    }
    OfrontOPC_InitImports(obj->right);
  }
}

void OfrontOPC_GenEnumPtrs (OfrontOPT_Object var)
{
  OfrontOPT_Struct typ = NIL;
  INTEGER n;
  OfrontOPC_GlbPtrs = 0;
  while (var != NIL) {
    typ = var->typ;
    if (OfrontOPC_NofPtrs(typ) > 0) {
      if (!OfrontOPC_GlbPtrs) {
        OfrontOPC_GlbPtrs = 1;
        OfrontOPM_WriteString((CHAR*)"static ", 8);
        if (OfrontOPC_ansi) {
          OfrontOPM_WriteString((CHAR*)"void EnumPtrs(void (*P)(void*))", 32);
        } else {
          OfrontOPM_WriteString((CHAR*)"void EnumPtrs(P)", 17);
          OfrontOPM_WriteLn();
          OfrontOPM_WriteTab();
          OfrontOPM_WriteString((CHAR*)"void (*P)();", 13);
        }
        OfrontOPM_WriteLn();
        OfrontOPC_BegBlk();
      }
      OfrontOPC_BegStat();
      if ((INTEGER)typ->form == 13) {
        OfrontOPM_WriteString((CHAR*)"P(", 3);
        OfrontOPC_Ident(var);
        OfrontOPM_Write(')');
      } else if ((INTEGER)typ->comp == 4) {
        OfrontOPM_WriteString((CHAR*)"__ENUMR(&", 10);
        OfrontOPC_Ident(var);
        OfrontOPM_WriteString((CHAR*)", ", 3);
        OfrontOPC_Andent(typ);
        OfrontOPM_WriteString((CHAR*)"__typ", 6);
        OfrontOPC_Str1((CHAR*)", #", 4, typ->size);
        OfrontOPM_WriteString((CHAR*)", 1, P)", 8);
      } else if ((INTEGER)typ->comp == 2) {
        n = typ->n;
        typ = typ->BaseTyp;
        while ((INTEGER)typ->comp == 2) {
          n = n * typ->n;
          typ = typ->BaseTyp;
        }
        if ((INTEGER)typ->form == 13) {
          OfrontOPM_WriteString((CHAR*)"__ENUMP(", 9);
          OfrontOPC_Ident(var);
          OfrontOPC_Str1((CHAR*)", #, P)", 8, n);
        } else if ((INTEGER)typ->comp == 4) {
          OfrontOPM_WriteString((CHAR*)"__ENUMR(", 9);
          OfrontOPC_Ident(var);
          OfrontOPM_WriteString((CHAR*)", ", 3);
          OfrontOPC_Andent(typ);
          OfrontOPM_WriteString((CHAR*)"__typ", 6);
          OfrontOPC_Str1((CHAR*)", #", 4, typ->size);
          OfrontOPC_Str1((CHAR*)", #, P)", 8, n);
        }
      }
      OfrontOPC_EndStat();
    }
    var = var->link;
  }
  if (OfrontOPC_GlbPtrs) {
    OfrontOPC_EndBlk();
    OfrontOPM_WriteLn();
  }
}

/*----------------------------------------------------------------------------*/
void OfrontOPC_EnterBody (void)
{
  OfrontOPM_WriteLn();
  if (OfrontOPC_mainprog && !OfrontOPC_dynlib) {
    if (OfrontOPC_ansi) {
      OfrontOPM_WriteString((CHAR*)"int main (int argc, char **argv)", 33);
    } else {
      OfrontOPM_WriteString((CHAR*)"main (argc, argv)", 18);
      OfrontOPM_WriteLn();
      OfrontOPM_WriteTab();
      OfrontOPM_WriteString((CHAR*)"int argc; char **argv;", 23);
    }
  } else {
    if (OfrontOPC_mainprog) {
      OfrontOPM_WriteString((CHAR*)"__ONBEGIN void ", 16);
    } else if (OfrontOPC_dynlib) {
      OfrontOPM_WriteString((CHAR*)"__EXPORT void *", 16);
    } else {
      OfrontOPM_WriteString((CHAR*)"export void *", 14);
    }
    OfrontOPM_WriteString((void*)OfrontOPM_modName, 32);
    OfrontOPM_WriteString((void*)OfrontOPC_BodyNameExt, 15);
  }
  OfrontOPM_WriteLn();
  OfrontOPC_BegBlk();
  if (OfrontOPC_mainprog && !OfrontOPC_dynlib) {
    OfrontOPC_BegStat();
    OfrontOPM_WriteString((CHAR*)"__INIT(argc, argv)", 19);
    OfrontOPC_EndStat();
  } else if (!OfrontOPC_mainprog) {
    OfrontOPC_BegStat();
    OfrontOPM_WriteString((CHAR*)"__DEFMOD", 9);
    OfrontOPC_EndStat();
  }
  OfrontOPC_InitImports(OfrontOPT_topScope->right);
  OfrontOPC_BegStat();
  if (OfrontOPC_mainprog) {
    OfrontOPM_WriteString((CHAR*)"__REGMAIN(\"", 12);
  } else {
    OfrontOPM_WriteString((CHAR*)"__REGMOD(\"", 11);
  }
  OfrontOPM_WriteString((void*)OfrontOPM_modName, 32);
  if (OfrontOPC_GlbPtrs) {
    OfrontOPM_WriteString((CHAR*)"\", EnumPtrs)", 13);
  } else {
    OfrontOPM_WriteString((CHAR*)"\", 0)", 6);
  }
  OfrontOPC_EndStat();
  if (__STRCMPCC(OfrontOPM_modName, (CHAR*)"SYSTEM", 7, (CHAR*)"OfrontOPC", 375551) != 0) {
    OfrontOPC_RegCmds(OfrontOPT_topScope);
  }
}

/*----------------------------------------------------------------------------*/
static void OfrontOPC_DoClose (OfrontOPT_Object obj)
{
  OfrontOPS_String _ptr__43 = NIL;
  OfrontOPS_String _ptr__42 = NIL;
  if (obj != NIL) {
    OfrontOPC_DoClose(obj->left);
    if ((INTEGER)obj->mode == 11 && __ODD(__ASHR((INTEGER)OfrontOPT_GlbMod[__X(-((INTEGER)obj->mnolev), 64, (CHAR*)"OfrontOPC", 378374)]->sysflag, 1, INTEGER))) {
      OfrontOPC_BegStat();
      OfrontOPM_WriteString((CHAR*)"__CLOSE(", 9);
      _ptr__43 = OfrontOPT_GlbMod[__X(-((INTEGER)obj->mnolev), 64, (CHAR*)"OfrontOPC", 377651)]->name;
      OfrontOPM_WriteString((void*)_ptr__43->data, _ptr__43->len[0]);
      OfrontOPM_WriteString((CHAR*)"__init, ", 9);
      _ptr__42 = OfrontOPT_GlbMod[__X(-((INTEGER)obj->mnolev), 64, (CHAR*)"OfrontOPC", 377907)]->name;
      OfrontOPM_WriteString((void*)_ptr__42->data, _ptr__42->len[0]);
      OfrontOPM_WriteString((CHAR*)"__close);", 10);
      OfrontOPM_WriteLn();
    }
    OfrontOPC_DoClose(obj->right);
  }
}

void OfrontOPC_ExitBody (void)
{
  if (!(OfrontOPC_mainprog && OfrontOPC_dynlib)) {
    if (OfrontOPC_retmain) {
      OfrontOPC_retmain = 0;
      OfrontOPM_WriteString((CHAR*)"return__:", 10);
      OfrontOPM_WriteLn();
    }
    OfrontOPC_BegStat();
    if (OfrontOPC_mainprog) {
      if (__IN(19, OfrontOPM_opt)) {
        OfrontOPM_WriteString((void*)OfrontOPM_modName, 32);
        OfrontOPM_WriteString((CHAR*)"__close();", 11);
        OfrontOPM_WriteLn();
        OfrontOPC_BegStat();
      }
      OfrontOPM_WriteString((CHAR*)"__FINI;", 8);
    } else {
      OfrontOPM_WriteString((CHAR*)"__ENDMOD;", 10);
    }
    OfrontOPM_WriteLn();
  }
  OfrontOPC_EndBlk();
}

/*----------------------------------------------------------------------------*/
void OfrontOPC_EnterClose (void)
{
  OfrontOPM_WriteLn();
  if (OfrontOPC_mainprog) {
    if (OfrontOPC_dynlib) {
      OfrontOPM_WriteString((CHAR*)"__ONCLOSE ", 11);
    } else {
      OfrontOPM_WriteString((CHAR*)"static ", 8);
    }
  } else {
    OfrontOPM_WriteString((CHAR*)"export ", 8);
  }
  OfrontOPM_WriteString((CHAR*)"void ", 6);
  OfrontOPM_WriteString((void*)OfrontOPM_modName, 32);
  OfrontOPM_WriteString((void*)OfrontOPC_CloseNameExt, 15);
  OfrontOPM_WriteLn();
  OfrontOPC_BegBlk();
  OfrontOPM_WriteString((CHAR*)"/* CLOSE */", 12);
  OfrontOPM_WriteLn();
}

/*----------------------------------------------------------------------------*/
void OfrontOPC_ExitClose (void)
{
  if (OfrontOPC_retmain) {
    OfrontOPC_retmain = 0;
    OfrontOPM_WriteString((CHAR*)"return__: ", 11);
    OfrontOPM_WriteLn();
  }
  OfrontOPC_DoClose(OfrontOPT_topScope->right);
  OfrontOPC_EndBlk();
}

/*----------------------------------------------------------------------------*/
void OfrontOPC_DllMainBody (BOOLEAN close)
{
  if ((OfrontOPC_mainprog && OfrontOPC_dynlib) && OfrontOPC_windows) {
    OfrontOPM_WriteLn();
    OfrontOPM_WriteString((CHAR*)"int __STDCALL DllMainCRTStartup (void *hinst, int reason, void *reserved)", 74);
    OfrontOPM_WriteLn();
    OfrontOPC_BegBlk();
    OfrontOPC_BegStat();
    OfrontOPM_WriteString((CHAR*)"switch (reason) ", 17);
    OfrontOPC_BegBlk();
    OfrontOPC_BegStat();
    OfrontOPM_WriteString((CHAR*)"case 1: ", 9);
    OfrontOPM_WriteString((void*)OfrontOPM_modName, 32);
    OfrontOPM_WriteString((CHAR*)"__init(); break", 16);
    OfrontOPC_EndStat();
    if (close) {
      OfrontOPC_BegStat();
      OfrontOPM_WriteString((CHAR*)"case 0: ", 9);
      OfrontOPM_WriteString((void*)OfrontOPM_modName, 32);
      OfrontOPM_WriteString((CHAR*)"__close(); break", 17);
      OfrontOPC_EndStat();
    }
    OfrontOPC_EndBlk();
    OfrontOPC_BegStat();
    OfrontOPM_WriteString((CHAR*)"return 1", 9);
    OfrontOPC_EndStat();
    OfrontOPC_EndBlk();
  }
}

/*----------------------------------------------------------------------------*/
void OfrontOPC_DefineInter (OfrontOPT_Object proc)
{
  OfrontOPT_Object scope = NIL;
  OfrontOPS_String _ptr__36 = NIL;
  OfrontOPS_String _ptr__35 = NIL;
  OfrontOPS_String _ptr__34 = NIL;
  scope = proc->scope;
  OfrontOPM_WriteString((CHAR*)"static ", 8);
  OfrontOPM_WriteString((CHAR*)"struct ", 8);
  _ptr__36 = scope->name;
  OfrontOPM_WriteString((void*)_ptr__36->data, _ptr__36->len[0]);
  OfrontOPM_Write(' ');
  OfrontOPC_BegBlk();
  OfrontOPC_IdentList(proc->link, 3);
  OfrontOPC_IdentList(scope->scope, 3);
  OfrontOPC_BegStat();
  OfrontOPM_WriteString((CHAR*)"struct ", 8);
  _ptr__35 = scope->name;
  OfrontOPM_WriteString((void*)_ptr__35->data, _ptr__35->len[0]);
  OfrontOPM_Write(' ');
  OfrontOPM_Write('*');
  OfrontOPM_WriteString((CHAR*)"lnk", 4);
  OfrontOPC_EndStat();
  OfrontOPC_EndBlk0();
  OfrontOPM_Write(' ');
  OfrontOPM_Write('*');
  _ptr__34 = scope->name;
  OfrontOPM_WriteString((void*)_ptr__34->data, _ptr__34->len[0]);
  OfrontOPM_WriteString((CHAR*)"_s", 3);
  OfrontOPC_EndStat();
  OfrontOPM_WriteLn();
  OfrontOPC_ProcPredefs(scope->right, 0);
  OfrontOPM_WriteLn();
}

/*----------------------------------------------------------------------------*/
BOOLEAN OfrontOPC_NeedsRetval (OfrontOPT_Object proc)
{
  return proc->typ != OfrontOPT_notyp && !proc->scope->leaf;
}

/*----------------------------------------------------------------------------*/
void OfrontOPC_EnterProc (OfrontOPT_Object proc)
{
  OfrontOPT_Object var = NIL;
  OfrontOPT_Object scope = NIL;
  OfrontOPT_Struct typ = NIL;
  SHORTINT dim;
  OfrontOPS_String _ptr__52 = NIL;
  OfrontOPS_String _ptr__51 = NIL;
  OfrontOPS_String _ptr__50 = NIL;
  if ((INTEGER)proc->vis != 1 && (INTEGER)proc->sysflag != 3) {
    OfrontOPM_WriteString((CHAR*)"static ", 8);
  }
  OfrontOPC_ProcHeader(proc, 1);
  OfrontOPC_BegBlk();
  scope = proc->scope;
  OfrontOPC_IdentList(scope->scope, 0);
  if (!scope->leaf) {
    OfrontOPC_BegStat();
    OfrontOPM_WriteString((CHAR*)"struct ", 8);
    _ptr__52 = scope->name;
    OfrontOPM_WriteString((void*)_ptr__52->data, _ptr__52->len[0]);
    OfrontOPM_Write(' ');
    OfrontOPM_WriteString((CHAR*)"_s", 3);
    OfrontOPC_EndStat();
  }
  if (OfrontOPC_NeedsRetval(proc)) {
    OfrontOPC_BegStat();
    OfrontOPC_Ident(proc->typ->strobj);
    OfrontOPM_WriteString((CHAR*)" __retval", 10);
    OfrontOPC_EndStat();
  }
  OfrontOPC_IdentList(proc->link, 4);
  if (!OfrontOPC_ansi) {
    var = proc->link;
    while (var != NIL) {
      if ((INTEGER)var->typ->form == 7 && (INTEGER)var->mode == 1) {
        OfrontOPC_BegStat();
        OfrontOPC_Ident(var->typ->strobj);
        OfrontOPM_Write(' ');
        OfrontOPC_Ident(var);
        OfrontOPM_WriteString((CHAR*)" = _", 5);
        OfrontOPC_Ident(var);
        OfrontOPC_EndStat();
      }
      var = var->link;
    }
  }
  var = proc->link;
  while (var != NIL) {
    if ((__IN(var->typ->comp, 0x0c) && (INTEGER)var->mode == 1) && (INTEGER)var->typ->sysflag == 0) {
      OfrontOPC_BegStat();
      if ((INTEGER)var->typ->comp == 2) {
        OfrontOPM_WriteString((CHAR*)"__DUPARR(", 10);
        OfrontOPC_Ident(var);
      } else {
        OfrontOPM_WriteString((CHAR*)"__DUP(", 7);
        OfrontOPC_Ident(var);
        OfrontOPM_WriteString((CHAR*)", ", 3);
        OfrontOPC_Ident(var);
        OfrontOPM_WriteString((CHAR*)"__len", 6);
        typ = var->typ->BaseTyp;
        dim = 1;
        while ((INTEGER)typ->comp == 3) {
          OfrontOPM_WriteString((CHAR*)" * ", 4);
          OfrontOPC_Ident(var);
          OfrontOPM_WriteString((CHAR*)"__len", 6);
          OfrontOPM_WriteInt(dim);
          typ = typ->BaseTyp;
          dim += 1;
        }
      }
      OfrontOPM_Write(')');
      OfrontOPC_EndStat();
    } else if (((OfrontOPC_ptrinit && (INTEGER)var->mode == 2) && (INTEGER)var->vis == 4) && __IN(var->typ->form, 0xa000)) {
      OfrontOPC_BegStat();
      OfrontOPM_Write('*');
      OfrontOPC_Ident(var);
      if (__IN(var->typ->form, 0xa000)) {
        OfrontOPM_WriteString((CHAR*)" = NIL", 7);
      } else {
        OfrontOPM_WriteString((CHAR*)" = {0}", 7);
      }
      OfrontOPC_EndStat();
    }
    var = var->link;
  }
  if (!scope->leaf) {
    var = proc->link;
    while (var != NIL) {
      if (!var->leaf) {
        OfrontOPC_BegStat();
        OfrontOPM_WriteString((CHAR*)"_s", 3);
        OfrontOPM_Write('.');
        OfrontOPC_Ident(var);
        OfrontOPM_WriteString((CHAR*)" = ", 4);
        if (__IN(var->typ->comp, 0x0c)) {
          OfrontOPM_WriteString((CHAR*)"(void*)", 8);
        } else if ((INTEGER)var->mode != 2) {
          OfrontOPM_Write('&');
        }
        OfrontOPC_Ident(var);
        if ((INTEGER)var->typ->comp == 3 && !__ODD(var->typ->sysflag)) {
          typ = var->typ;
          dim = 0;
          do {
            OfrontOPM_WriteString((CHAR*)"; ", 3);
            OfrontOPM_WriteString((CHAR*)"_s", 3);
            OfrontOPM_Write('.');
            OfrontOPC_Ident(var);
            OfrontOPM_WriteString((CHAR*)"__len", 6);
            if ((INTEGER)dim != 0) {
              OfrontOPM_WriteInt(dim);
            }
            OfrontOPM_WriteString((CHAR*)" = ", 4);
            OfrontOPC_Ident(var);
            OfrontOPM_WriteString((CHAR*)"__len", 6);
            if ((INTEGER)dim != 0) {
              OfrontOPM_WriteInt(dim);
            }
            typ = typ->BaseTyp;
            dim += 1;
          } while (!((INTEGER)typ->comp != 3));
        } else if (((INTEGER)var->mode == 2 && (INTEGER)var->typ->comp == 4) && __MASK((INTEGER)var->typ->sysflag, -256) == 0) {
          OfrontOPM_WriteString((CHAR*)"; ", 3);
          OfrontOPM_WriteString((CHAR*)"_s", 3);
          OfrontOPM_Write('.');
          OfrontOPC_Ident(var);
          OfrontOPM_WriteString((CHAR*)"__typ", 6);
          OfrontOPM_WriteString((CHAR*)" = ", 4);
          OfrontOPC_Ident(var);
          OfrontOPM_WriteString((CHAR*)"__typ", 6);
        }
        OfrontOPC_EndStat();
      }
      var = var->link;
    }
    var = scope->scope;
    while (var != NIL) {
      if (!var->leaf) {
        OfrontOPC_BegStat();
        OfrontOPM_WriteString((CHAR*)"_s", 3);
        OfrontOPM_Write('.');
        OfrontOPC_Ident(var);
        OfrontOPM_WriteString((CHAR*)" = ", 4);
        if ((INTEGER)var->typ->comp != 2) {
          OfrontOPM_Write('&');
        } else {
          OfrontOPM_WriteString((CHAR*)"(void*)", 8);
        }
        OfrontOPC_Ident(var);
        OfrontOPC_EndStat();
      }
      var = var->link;
    }
    OfrontOPC_BegStat();
    OfrontOPM_WriteString((CHAR*)"_s", 3);
    OfrontOPM_Write('.');
    OfrontOPM_WriteString((CHAR*)"lnk", 4);
    OfrontOPM_WriteString((CHAR*)" = ", 4);
    _ptr__51 = scope->name;
    OfrontOPM_WriteString((void*)_ptr__51->data, _ptr__51->len[0]);
    OfrontOPM_WriteString((CHAR*)"_s", 3);
    OfrontOPC_EndStat();
    OfrontOPC_BegStat();
    _ptr__50 = scope->name;
    OfrontOPM_WriteString((void*)_ptr__50->data, _ptr__50->len[0]);
    OfrontOPM_WriteString((CHAR*)"_s", 3);
    OfrontOPM_WriteString((CHAR*)" = ", 4);
    OfrontOPM_Write('&');
    OfrontOPM_WriteString((CHAR*)"_s", 3);
    OfrontOPC_EndStat();
  }
}

/*----------------------------------------------------------------------------*/
void OfrontOPC_ExitProc (OfrontOPT_Object proc, BOOLEAN eoBlock, BOOLEAN implicitRet)
{
  OfrontOPT_Object var = NIL;
  BOOLEAN indent;
  OfrontOPS_String _ptr__56 = NIL;
  indent = eoBlock;
  if (implicitRet && proc->typ != OfrontOPT_notyp) {
    OfrontOPM_WriteTab();
    OfrontOPM_WriteString((CHAR*)"__RETCHK(", 10);
    OfrontOPM_WriteModPos();
    OfrontOPM_WriteString((CHAR*)");", 3);
    OfrontOPM_WriteLn();
  } else if (!eoBlock || implicitRet) {
    if (!proc->scope->leaf) {
      if (indent) {
        OfrontOPC_BegStat();
      } else {
        indent = 1;
      }
      _ptr__56 = proc->scope->name;
      OfrontOPM_WriteString((void*)_ptr__56->data, _ptr__56->len[0]);
      OfrontOPM_WriteString((CHAR*)"_s", 3);
      OfrontOPM_WriteString((CHAR*)" = ", 4);
      OfrontOPM_WriteString((CHAR*)"_s", 3);
      OfrontOPM_Write('.');
      OfrontOPM_WriteString((CHAR*)"lnk", 4);
      OfrontOPC_EndStat();
    }
    var = proc->link;
    while (0) {
      if (((INTEGER)var->typ->comp == 3 && (INTEGER)var->mode == 1) && (INTEGER)var->typ->sysflag == 0) {
        if (indent) {
          OfrontOPC_BegStat();
        } else {
          indent = 1;
        }
        OfrontOPM_WriteString((CHAR*)"__DEL(", 7);
        OfrontOPC_Ident(var);
        OfrontOPM_Write(')');
        OfrontOPC_EndStat();
      }
      var = var->link;
    }
  }
  if (eoBlock) {
    OfrontOPC_EndBlk();
    OfrontOPM_WriteLn();
  } else if (indent) {
    OfrontOPC_BegStat();
  }
  if ((eoBlock && (INTEGER)proc->vis == 1) && OfrontOPM_currFile == 1) {
    OfrontOPM_WriteString((CHAR*)"/*----------------------------------------------------------------------------*/", 81);
    OfrontOPM_WriteLn();
  }
}

/*----------------------------------------------------------------------------*/
void OfrontOPC_CompleteIdent (OfrontOPT_Object obj)
{
  SHORTINT comp, level;
  OfrontOPS_String _ptr__16 = NIL;
  level = obj->mnolev;
  if (obj->adr == 1) {
    if ((INTEGER)obj->typ->comp == 4) {
      OfrontOPC_Ident(obj);
      OfrontOPM_WriteString((CHAR*)"__", 3);
    } else {
      OfrontOPM_WriteString((CHAR*)"((", 3);
      OfrontOPC_Ident(obj->typ->strobj);
      if ((INTEGER)obj->mode == 2) {
        OfrontOPM_Write('*');
      }
      OfrontOPM_Write(')');
      OfrontOPC_Ident(obj);
      OfrontOPM_Write(')');
    }
  } else if ((INTEGER)level != OfrontOPM_level && (INTEGER)level > 0) {
    comp = obj->typ->comp;
    if ((INTEGER)comp == 2 || ((INTEGER)obj->mode != 2 && (INTEGER)comp != 3)) {
      OfrontOPM_WriteString((CHAR*)"(*", 3);
    }
    _ptr__16 = obj->scope->name;
    OfrontOPM_WriteString((void*)_ptr__16->data, _ptr__16->len[0]);
    OfrontOPM_WriteString((CHAR*)"_s", 3);
    OfrontOPM_WriteString((CHAR*)"->", 3);
    OfrontOPC_Ident(obj);
    if ((INTEGER)comp == 2 || ((INTEGER)obj->mode != 2 && (INTEGER)comp != 3)) {
      OfrontOPM_Write(')');
    }
  } else {
    OfrontOPC_Ident(obj);
  }
}

/*----------------------------------------------------------------------------*/
void OfrontOPC_CompleteIdentAdr (OfrontOPT_Object obj)
{
  if (obj->adr == 1 && (INTEGER)obj->typ->comp != 4) {
    OfrontOPM_Write('(');
    OfrontOPC_Ident(obj->typ->strobj);
    OfrontOPM_WriteString((CHAR*)"*)&", 4);
    OfrontOPC_Ident(obj);
  } else {
    OfrontOPM_Write('&');
    OfrontOPC_CompleteIdent(obj);
  }
}

/*----------------------------------------------------------------------------*/
void OfrontOPC_TypeOf (OfrontOPT_Object ap)
{
  OfrontOPS_String _ptr__111 = NIL;
  __ASSERT((INTEGER)ap->typ->comp == 4, 0, (CHAR*)"OfrontOPC", 441886);
  if ((INTEGER)ap->mode == 2) {
    if ((INTEGER)ap->mnolev != OfrontOPM_level) {
      _ptr__111 = ap->scope->name;
      OfrontOPM_WriteString((void*)_ptr__111->data, _ptr__111->len[0]);
      OfrontOPM_WriteString((CHAR*)"_s->", 5);
      OfrontOPC_Ident(ap);
    } else {
      OfrontOPC_Ident(ap);
    }
    OfrontOPM_WriteString((CHAR*)"__typ", 6);
  } else if (ap->typ->strobj != NIL) {
    OfrontOPC_Ident(ap->typ->strobj);
    OfrontOPM_WriteString((CHAR*)"__typ", 6);
  } else {
    OfrontOPC_Andent(ap->typ);
  }
}

/*----------------------------------------------------------------------------*/
void OfrontOPC_Cmp (SHORTINT rel)
{
  switch (rel) {
    case 11: 
      OfrontOPM_WriteString((CHAR*)" == ", 5);
      break;
    case 12: 
      OfrontOPM_WriteString((CHAR*)" != ", 5);
      break;
    case 13: 
      OfrontOPM_WriteString((CHAR*)" < ", 4);
      break;
    case 14: 
      OfrontOPM_WriteString((CHAR*)" <= ", 5);
      break;
    case 15: 
      OfrontOPM_WriteString((CHAR*)" > ", 4);
      break;
    case 16: 
      OfrontOPM_WriteString((CHAR*)" >= ", 5);
      break;
    default: __CASECHK((CHAR*)"OfrontOPC", 449052);
  }
}

/*----------------------------------------------------------------------------*/
static void OfrontOPC_WriteCharLiteral (LONGCHAR ch, BOOLEAN wide)
{
  if (ch >= ' ' && ch <= '~') {
    OfrontOPM_Write('\'');
    if (((ch == '\\' || ch == '\?') || ch == '\'') || ch == '\"') {
      OfrontOPM_Write('\\');
    }
    OfrontOPM_Write((CHAR)ch);
    OfrontOPM_Write('\'');
  } else if (wide && ch > 0xff) {
    OfrontOPM_WriteString((CHAR*)"0x", 3);
    OfrontOPM_WriteHex(__ASHR((INTEGER)ch, 8, INTEGER));
    OfrontOPM_WriteHex(__MASK((INTEGER)ch, -256));
  } else {
    __ASSERT(ch <= 0xff, 0, (CHAR*)"OfrontOPC", 452373);
    OfrontOPM_WriteString((CHAR*)"0x", 3);
    OfrontOPM_WriteHex((INTEGER)ch);
  }
}

static void OfrontOPC_WriteStringLiteral (CHAR *str, INTEGER str__len, INTEGER len)
{
  CHAR ch;
  INTEGER i;
  OfrontOPM_Write('\"');
  i = 0;
  while (i < len) {
    ch = str[__X(i, str__len, (CHAR*)"OfrontOPC", 454687)];
    if (ch >= ' ' && ch <= '~') {
      if (((ch == '\\' || ch == '\?') || ch == '\'') || ch == '\"') {
        OfrontOPM_Write('\\');
      }
      OfrontOPM_Write(ch);
    } else {
      OfrontOPM_WriteString((CHAR*)"\\x", 3);
      OfrontOPM_WriteHex((SHORTINT)ch);
      if (i + 1 < len) {
        switch (str[__X(i + 1, str__len, (CHAR*)"OfrontOPC", 456724)]) {
          case '0': case '1': case '2': case '3': case '4': 
          case '5': case '6': case '7': case '8': case '9': 
          case 'a': case 'b': case 'c': case 'd': case 'e': 
          case 'f': case 'A': case 'B': case 'C': case 'D': 
          case 'E': case 'F': 
            OfrontOPM_Write('\"');
            OfrontOPM_Write('\"');
            break;
          default: 
            break;
        }
      }
    }
    i += 1;
  }
  OfrontOPM_Write('\"');
}

void OfrontOPC_Case (INTEGER caseVal, SHORTINT form)
{
  OfrontOPM_WriteString((CHAR*)"case ", 6);
  switch (form) {
    case 3: case 17: 
      OfrontOPC_WriteCharLiteral((LONGCHAR)caseVal, (INTEGER)form == 17);
      break;
    case 1: case 14: case 4: case 5: case 6: 
      OfrontOPM_WriteInt(caseVal);
      break;
    default: __CASECHK((CHAR*)"OfrontOPC", 461567);
  }
  OfrontOPM_WriteString((CHAR*)": ", 3);
}

/*----------------------------------------------------------------------------*/
void OfrontOPC_SetInclude (BOOLEAN exclude)
{
  if (exclude) {
    OfrontOPM_WriteString((CHAR*)" &= ~", 6);
  } else {
    OfrontOPM_WriteString((CHAR*)" |= ", 5);
  }
}

/*----------------------------------------------------------------------------*/
void OfrontOPC_Increment (BOOLEAN decrement)
{
  if (decrement) {
    OfrontOPM_WriteString((CHAR*)" -= ", 5);
  } else {
    OfrontOPM_WriteString((CHAR*)" += ", 5);
  }
}

/*----------------------------------------------------------------------------*/
void OfrontOPC_Halt (INTEGER n)
{
  OfrontOPC_Str1((CHAR*)"__HALT(#, ", 11, n);
  OfrontOPM_WriteModPos();
  OfrontOPM_Write(')');
}

/*----------------------------------------------------------------------------*/
void OfrontOPC_Len (OfrontOPT_Object obj, OfrontOPT_Struct array, INTEGER dim)
{
  INTEGER d;
  d = dim;
  while (d > 0) {
    array = array->BaseTyp;
    d -= 1;
  }
  if ((INTEGER)array->comp == 3) {
    if (__ODD(array->sysflag)) {
      OfrontOPM_err(136);
    }
    OfrontOPC_CompleteIdent(obj);
    OfrontOPM_WriteString((CHAR*)"__len", 6);
    if (dim != 0) {
      OfrontOPM_WriteInt(dim);
    }
  } else {
    OfrontOPM_WriteInt(array->n);
    OfrontOPM_PromoteIntConstToLInt();
  }
}

/*----------------------------------------------------------------------------*/
void OfrontOPC_Constant (OfrontOPT_Const con, SHORTINT form)
{
  INTEGER i, x;
  SET s;
  INTEGER hex;
  BOOLEAN skipLeading;
  OfrontOPS_String _ptr__21 = NIL;
  OfrontOPS_String _ptr__20 = NIL;
  OfrontOPS_String _ptr__19 = NIL;
  switch (form) {
    case 2: case 1: case 14: case 4: case 5: 
    case 6: 
      OfrontOPM_WriteInt(con->intval);
      break;
    case 3: case 17: 
      OfrontOPC_WriteCharLiteral((LONGCHAR)con->intval, (INTEGER)form == 17);
      break;
    case 7: 
      if (con->realval == __INF) {
        OfrontOPM_WriteString((CHAR*)"__INFS", 7);
      } else if (con->realval == -__INF) {
        OfrontOPM_WriteString((CHAR*)"-__INFS", 8);
      } else {
        OfrontOPM_WriteReal(con->realval, 'f');
      }
      break;
    case 8: 
      if (con->realval == __INF) {
        OfrontOPM_WriteString((CHAR*)"__INF", 6);
      } else if (con->realval == -__INF) {
        OfrontOPM_WriteString((CHAR*)"-__INF", 7);
      } else {
        OfrontOPM_WriteReal(con->realval, 0x00);
      }
      break;
    case 9: 
      OfrontOPM_WriteString((CHAR*)"0x", 3);
      skipLeading = 1;
      s = con->setval;
      i = 32;
      do {
        hex = 0;
        do {
          i -= 1;
          hex = __ASHL(hex, 1, INTEGER);
          if (__IN(i, s)) {
            hex += 1;
          }
        } while (!(__MASK(i, -8) == 0));
        if (hex != 0 || !skipLeading) {
          OfrontOPM_WriteHex(hex);
          skipLeading = 0;
        }
      } while (!(i == 0));
      if (skipLeading) {
        OfrontOPM_Write('0');
      }
      break;
    case 10: 
      if (OfrontOPC_ansi) {
        OfrontOPM_WriteString((CHAR*)"(CHAR*)", 8);
      }
      _ptr__21 = con->ext;
      OfrontOPC_WriteStringLiteral((void*)_ptr__21->data, _ptr__21->len[0], con->intval2 - 1);
      break;
    case 18: 
      OfrontOPM_WriteString((CHAR*)"((LONGCHAR[]){", 15);
      i = 0;
      _ptr__20 = con->ext;
      OfrontOPM_GetUtf8((void*)_ptr__20->data, _ptr__20->len[0], &x, &i);
      while (x != 0) {
        OfrontOPM_WriteInt(x);
        OfrontOPM_WriteString((CHAR*)", ", 3);
        _ptr__19 = con->ext;
        OfrontOPM_GetUtf8((void*)_ptr__19->data, _ptr__19->len[0], &x, &i);
      }
      OfrontOPM_WriteString((CHAR*)"0})", 4);
      break;
    case 11: 
      OfrontOPM_WriteString((CHAR*)"NIL", 4);
      break;
    default: __CASECHK((CHAR*)"OfrontOPC", 481535);
  }
}

/*----------------------------------------------------------------------------*/
static struct InitKeywords__84 {
  SHORTINT *n;
  struct InitKeywords__84 *lnk;
} *InitKeywords__84_s;

static void __85 (CHAR *s, INTEGER s__len);

static void __85 (CHAR *s, INTEGER s__len)
{
  SHORTINT h;
  h = OfrontOPC_PerfectHash((void*)s, s__len);
  OfrontOPC_hashtab[__X(h, 169, (CHAR*)"OfrontOPC", 483884)] = (*InitKeywords__84_s->n);
  __STRCOPYCC(s, OfrontOPC_keytab[__X((*InitKeywords__84_s->n), 37, (CHAR*)"OfrontOPC", 483901)], __MIN(9, s__len), (CHAR*)"OfrontOPC", 483901);
  (*InitKeywords__84_s->n) += 1;
}

static void OfrontOPC_InitKeywords (void)
{
  SHORTINT n, i;
  struct InitKeywords__84 _s;
  _s.n = &n;
  _s.lnk = InitKeywords__84_s;
  InitKeywords__84_s = &_s;
  n = 0;
  i = 0;
  while ((INTEGER)i <= 168) {
    OfrontOPC_hashtab[__X(i, 169, (CHAR*)"OfrontOPC", 484916)] = -1;
    i += 1;
  }
  __85((CHAR*)"asm", 4);
  __85((CHAR*)"auto", 5);
  __85((CHAR*)"break", 6);
  __85((CHAR*)"case", 5);
  __85((CHAR*)"char", 5);
  __85((CHAR*)"const", 6);
  __85((CHAR*)"continue", 9);
  __85((CHAR*)"default", 8);
  __85((CHAR*)"do", 3);
  __85((CHAR*)"double", 7);
  __85((CHAR*)"else", 5);
  __85((CHAR*)"enum", 5);
  __85((CHAR*)"extern", 7);
  __85((CHAR*)"export", 7);
  __85((CHAR*)"float", 6);
  __85((CHAR*)"for", 4);
  __85((CHAR*)"fortran", 8);
  __85((CHAR*)"goto", 5);
  __85((CHAR*)"if", 3);
  __85((CHAR*)"import", 7);
  __85((CHAR*)"inline", 7);
  __85((CHAR*)"int", 4);
  __85((CHAR*)"long", 5);
  __85((CHAR*)"register", 9);
  __85((CHAR*)"return", 7);
  __85((CHAR*)"short", 6);
  __85((CHAR*)"signed", 7);
  __85((CHAR*)"sizeof", 7);
  __85((CHAR*)"static", 7);
  __85((CHAR*)"struct", 7);
  __85((CHAR*)"switch", 7);
  __85((CHAR*)"typedef", 8);
  __85((CHAR*)"union", 6);
  __85((CHAR*)"unsigned", 9);
  __85((CHAR*)"void", 5);
  __85((CHAR*)"volatile", 9);
  __85((CHAR*)"while", 6);
  InitKeywords__84_s = _s.lnk;
}

static void EnumPtrs(void (*P)(void*))
{
  __ENUMP(OfrontOPC_arrayTypes, 1024, P);
}


export void *OfrontOPC__init (void)
{
  __DEFMOD;
  __IMPORT(OfrontOPM__init);
  __IMPORT(OfrontOPT__init);
  __REGMOD("OfrontOPC", EnumPtrs);
  __REGCMD("BegBlk", OfrontOPC_BegBlk);
  __REGCMD("BegStat", OfrontOPC_BegStat);
  __REGCMD("CleanupArrays", OfrontOPC_CleanupArrays);
  __REGCMD("EndBlk", OfrontOPC_EndBlk);
  __REGCMD("EndBlk0", OfrontOPC_EndBlk0);
  __REGCMD("EndStat", OfrontOPC_EndStat);
  __REGCMD("EnterBody", OfrontOPC_EnterBody);
  __REGCMD("EnterClose", OfrontOPC_EnterClose);
  __REGCMD("ExitBody", OfrontOPC_ExitBody);
  __REGCMD("ExitClose", OfrontOPC_ExitClose);
  __REGCMD("GenHdrIncludes", OfrontOPC_GenHdrIncludes);
  __REGCMD("Init", OfrontOPC_Init);
/* BEGIN */
  OfrontOPC_InitKeywords();
  __ENDMOD;
}
