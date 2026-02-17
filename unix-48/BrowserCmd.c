/* Ofront+ 1.0 -mC -48 */
#include "SYSTEM.oh"
#include "OfrontOPM.oh"
#include "OfrontOPS.oh"
#include "OfrontOPT.oh"
#include "OfrontOPV.oh"
#include "Texts.oh"
#include "Files.oh"
#include "Console.oh"
#include "CmdArgs.oh"

struct BrowserCmd__1 {
  INTEGER level;
  BOOLEAN gap;
};


static Texts_Writer BrowserCmd_W;
static CHAR BrowserCmd_lang, BrowserCmd_option;
static CHAR BrowserCmd_hex[17];
static struct BrowserCmd__1 BrowserCmd_global;

export void **BrowserCmd__1__typ;

static void BrowserCmd_Ident (CHAR *name, INTEGER name__len, CHAR *first, INTEGER first__len);
static void BrowserCmd_Indent (INTEGER i);
static void BrowserCmd_Objects (OfrontOPT_Object obj, SET mode);
export void BrowserCmd_ShowDef (void);
static void BrowserCmd_StringConst (CHAR *s, INTEGER s__len);
static void BrowserCmd_WModule (OfrontOPS_Name name, Texts_Text T);
static void BrowserCmd_Wch (CHAR ch);
static void BrowserCmd_Wflds (OfrontOPT_Struct typ, BOOLEAN *cont);
static void BrowserCmd_Whex (INTEGER i);
static void BrowserCmd_Wi (LONGINT i);
static void BrowserCmd_Wln (void);
static void BrowserCmd_Wmthd (OfrontOPT_Object obj, BOOLEAN *cont);
static void BrowserCmd_Ws (CHAR *s, INTEGER s__len);
static void BrowserCmd_Wsign (OfrontOPT_Struct result, OfrontOPT_Object par);
static void BrowserCmd_Wstruct (OfrontOPT_Struct typ);
static void BrowserCmd_Wtype (OfrontOPT_Struct typ);


/*============================================================================*/

static void BrowserCmd_Ws (CHAR *s, INTEGER s__len)
{
  Texts_WriteString(&BrowserCmd_W, Texts_Writer__typ, (void*)s, s__len);
}

static void BrowserCmd_Wch (CHAR ch)
{
  Texts_Write(&BrowserCmd_W, Texts_Writer__typ, ch);
}

static void BrowserCmd_Wi (LONGINT i)
{
  Texts_WriteLongInt(&BrowserCmd_W, Texts_Writer__typ, i, 0);
}

static void BrowserCmd_Wln (void)
{
  Texts_WriteLn(&BrowserCmd_W, Texts_Writer__typ);
}

static void BrowserCmd_Whex (INTEGER i)
{
  Texts_WriteHex(&BrowserCmd_W, Texts_Writer__typ, i);
}

static void BrowserCmd_StringConst (CHAR *s, INTEGER s__len)
{
  CHAR ch;
  INTEGER i;
  BOOLEAN quoted, first;
  ch = s[0];
  i = 1;
  quoted = 0;
  first = 1;
  while (ch != 0x00) {
    if (ch == '\"') {
      quoted = 1;
    } else if ((ch < ' ' || ch == '\'') || ch >= 0x7f) {
      first = 0;
    }
    ch = s[__X(i, s__len, (CHAR*)"BrowserCmd", 15373)];
    i += 1;
  }
  if (quoted && first) {
    BrowserCmd_Wch('\'');
    BrowserCmd_Ws((void*)s, s__len);
    BrowserCmd_Wch('\'');
  } else {
    ch = s[0];
    i = 1;
    quoted = 0;
    first = 1;
    while (ch != 0x00) {
      if ((ch < ' ' || ch == '\"') || ch >= 0x7f) {
        if (quoted) {
          BrowserCmd_Wch('\"');
        }
        if (!first) {
          BrowserCmd_Ws((CHAR*)" + ", 4);
        }
        if (ch > 0x9f) {
          BrowserCmd_Wch('0');
        }
        BrowserCmd_Wch(BrowserCmd_hex[__X(__ASHR((INTEGER)ch, 4, INTEGER), 17, (CHAR*)"BrowserCmd", 17950)]);
        BrowserCmd_Wch(BrowserCmd_hex[__X(__MASK((INTEGER)ch, -16), 17, (CHAR*)"BrowserCmd", 17977)]);
        BrowserCmd_Wch('X');
        quoted = 0;
      } else {
        if (!quoted) {
          if (!first) {
            BrowserCmd_Ws((CHAR*)" + ", 4);
          }
          BrowserCmd_Wch('\"');
        }
        BrowserCmd_Wch(ch);
        quoted = 1;
      }
      ch = s[__X(i, s__len, (CHAR*)"BrowserCmd", 20494)];
      i += 1;
      first = 0;
    }
    if (quoted) {
      BrowserCmd_Wch('\"');
    }
  }
}

static void BrowserCmd_Indent (INTEGER i)
{
  if (BrowserCmd_global.gap) {
    BrowserCmd_global.gap = 0;
    BrowserCmd_Wln();
  }
  while (i > 0) {
    BrowserCmd_Wch(' ');
    BrowserCmd_Wch(' ');
    i -= 1;
  }
}

static void BrowserCmd_Wsign (OfrontOPT_Struct result, OfrontOPT_Object par)
{
  BOOLEAN paren, res, first;
  OfrontOPS_String _ptr__30 = NIL;
  OfrontOPS_String _ptr__29 = NIL;
  first = 1;
  res = result != NIL && result != OfrontOPT_notyp;
  paren = res || par != NIL;
  if (paren) {
    BrowserCmd_Ws((CHAR*)" (", 3);
  }
  while (par != NIL) {
    if (!first) {
      BrowserCmd_Ws((CHAR*)"; ", 3);
    } else {
      first = 0;
    }
    if (BrowserCmd_option == 'x') {
      BrowserCmd_Wi(par->adr);
      BrowserCmd_Wch(' ');
    }
    if ((INTEGER)par->mode == 2) {
      if (BrowserCmd_lang == 'C') {
        if ((INTEGER)par->vis == 3) {
          BrowserCmd_Ws((CHAR*)"IN ", 4);
        } else if ((INTEGER)par->vis == 4) {
          BrowserCmd_Ws((CHAR*)"OUT ", 5);
        } else {
          BrowserCmd_Ws((CHAR*)"VAR ", 5);
        }
      } else if ((INTEGER)par->vis != 3) {
        BrowserCmd_Ws((CHAR*)"VAR ", 5);
      }
      if (__ODD((INTEGER)par->sysflag)) {
        BrowserCmd_Ws((CHAR*)"[nil] ", 7);
      }
    }
    _ptr__30 = par->name;
    BrowserCmd_Ws((void*)_ptr__30->data, _ptr__30->len[0]);
    if (BrowserCmd_lang <= '2' && (INTEGER)par->vis == 3) {
      BrowserCmd_Wch('-');
    }
    while ((((par->link != NIL && par->link->typ == par->typ) && (INTEGER)par->link->mode == (INTEGER)par->mode) && (INTEGER)par->link->vis == (INTEGER)par->vis) && (INTEGER)par->link->sysflag == (INTEGER)par->sysflag) {
      par = par->link;
      BrowserCmd_Ws((CHAR*)", ", 3);
      _ptr__29 = par->name;
      BrowserCmd_Ws((void*)_ptr__29->data, _ptr__29->len[0]);
    }
    BrowserCmd_Ws((CHAR*)": ", 3);
    BrowserCmd_Wtype(par->typ);
    par = par->link;
  }
  if (paren) {
    BrowserCmd_Wch(')');
  }
  if (res) {
    BrowserCmd_Ws((CHAR*)": ", 3);
    BrowserCmd_Wtype(result);
  }
}

static void BrowserCmd_Objects (OfrontOPT_Object obj, SET mode)
{
  INTEGER i, m;
  SET s;
  OfrontOPS_String ext = NIL;
  OfrontOPS_String _ptr__8 = NIL;
  OfrontOPS_String _ptr__7 = NIL;
  OfrontOPS_String _ptr__6 = NIL;
  OfrontOPS_String _ptr__5 = NIL;
  OfrontOPS_String _ptr__4 = NIL;
  if (obj != NIL) {
    BrowserCmd_Objects(obj->left, mode);
    if (__IN(obj->mode, mode)) {
      switch (obj->mode) {
        case 3: 
          BrowserCmd_Indent(2);
          _ptr__8 = obj->name;
          BrowserCmd_Ws((void*)_ptr__8->data, _ptr__8->len[0]);
          BrowserCmd_Ws((CHAR*)" = ", 4);
          switch (obj->typ->form) {
            case 2: 
              if (obj->conval->intval == 1) {
                BrowserCmd_Ws((CHAR*)"TRUE", 5);
              } else {
                BrowserCmd_Ws((CHAR*)"FALSE", 6);
              }
              break;
            case 3: case 17: 
              if (obj->conval->intval == 34) {
                BrowserCmd_Wch('\'');
                BrowserCmd_Wch('\"');
                BrowserCmd_Wch('\'');
              } else if (obj->conval->intval >= 32 && obj->conval->intval <= 126) {
                BrowserCmd_Wch('\"');
                BrowserCmd_Wch((CHAR)obj->conval->intval);
                BrowserCmd_Wch('\"');
              } else {
                BrowserCmd_Whex((INTEGER)obj->conval->intval);
                BrowserCmd_Wch('X');
              }
              break;
            case 1: case 4: case 5: case 6: 
              BrowserCmd_Wi(obj->conval->intval);
              break;
            case 9: 
              BrowserCmd_Wch('{');
              i = 0;
              s = obj->conval->setval;
              while (i <= 31) {
                if (__IN(i, s)) {
                  BrowserCmd_Wi(i);
                  s &= ~__SETOF(i);
                  if (s != 0x0) {
                    BrowserCmd_Ws((CHAR*)", ", 3);
                  }
                }
                i += 1;
              }
              BrowserCmd_Wch('}');
              break;
            case 7: 
              Texts_WriteLongReal(&BrowserCmd_W, Texts_Writer__typ, obj->conval->realval, 8);
              break;
            case 8: 
              Texts_WriteLongReal(&BrowserCmd_W, Texts_Writer__typ, obj->conval->realval, 17);
              break;
            case 10: case 18: 
              _ptr__7 = obj->conval->ext;
              BrowserCmd_StringConst((void*)_ptr__7->data, _ptr__7->len[0]);
              break;
            case 11: 
              BrowserCmd_Ws((CHAR*)"NIL", 4);
              break;
            default: __CASECHK((CHAR*)"BrowserCmd", 41727);
          }
          BrowserCmd_Wch(';');
          BrowserCmd_Wln();
          break;
        case 5: 
          if (obj->name != OfrontOPT_null) {
            BrowserCmd_Indent(2);
            if (obj->typ->strobj == obj) {
              BrowserCmd_Wtype(obj->typ);
              BrowserCmd_Ws((CHAR*)" = ", 4);
              BrowserCmd_Wstruct(obj->typ);
            } else {
              _ptr__6 = obj->name;
              BrowserCmd_Ws((void*)_ptr__6->data, _ptr__6->len[0]);
              BrowserCmd_Ws((CHAR*)" = ", 4);
              BrowserCmd_Wtype(obj->typ);
            }
            BrowserCmd_Wch(';');
            BrowserCmd_Wln();
          }
          break;
        case 1: 
          BrowserCmd_Indent(2);
          _ptr__5 = obj->name;
          BrowserCmd_Ws((void*)_ptr__5->data, _ptr__5->len[0]);
          if (BrowserCmd_lang != '7' && (INTEGER)obj->vis == 2) {
            BrowserCmd_Ws((CHAR*)"-: ", 4);
          } else {
            BrowserCmd_Ws((CHAR*)": ", 3);
          }
          BrowserCmd_Wtype(obj->typ);
          BrowserCmd_Wch(';');
          BrowserCmd_Wln();
          break;
        case 7: case 9: case 10: 
          if ((INTEGER)obj->mode != 9 || (INTEGER)obj->sysflag >= 0) {
            BrowserCmd_Indent(1);
            BrowserCmd_Ws((CHAR*)"PROCEDURE", 10);
            if ((INTEGER)obj->mode == 10) {
              BrowserCmd_Wch('+');
            } else if (BrowserCmd_option == 'x' && (INTEGER)obj->mode == 9) {
              BrowserCmd_Wch('-');
            }
            BrowserCmd_Wch(' ');
            switch (obj->sysflag) {
              case 0: 
                break;
              case 1: 
                BrowserCmd_Ws((CHAR*)"[stdcall] ", 11);
                break;
              case 2: 
                BrowserCmd_Ws((CHAR*)"[fastcall] ", 12);
                break;
              case 3: 
                BrowserCmd_Ws((CHAR*)"[inline] ", 10);
                break;
              default: __CASECHK((CHAR*)"BrowserCmd", 48639);
            }
            _ptr__4 = obj->name;
            BrowserCmd_Ws((void*)_ptr__4->data, _ptr__4->len[0]);
            BrowserCmd_Wsign(obj->typ, obj->link);
            if ((INTEGER)obj->mode == 9) {
              ext = obj->conval->ext;
              if (BrowserCmd_option == 'x' && ext != NIL) {
                m = ext->len[0];
                i = 0;
                BrowserCmd_Ws((CHAR*)" \"", 3);
                while (i < m) {
                  BrowserCmd_Wch((ext->data)[__X(i, ext->len[0], (CHAR*)"BrowserCmd", 49956)]);
                  i += 1;
                }
                BrowserCmd_Wch('\"');
              }
            }
            BrowserCmd_Wch(';');
            BrowserCmd_Wln();
          }
          break;
        default: __CASECHK((CHAR*)"BrowserCmd", 51199);
      }
    }
    BrowserCmd_Objects(obj->right, mode);
  }
}

static void BrowserCmd_Wmthd (OfrontOPT_Object obj, BOOLEAN *cont)
{
  OfrontOPS_String _ptr__26 = NIL;
  OfrontOPS_String _ptr__25 = NIL;
  if (obj != NIL) {
    BrowserCmd_Wmthd(obj->left, cont);
    if ((INTEGER)obj->mode == 13 && (__STRCMPCC(obj->name->data, (CHAR*)"@tproc", 7, (CHAR*)"BrowserCmd", 60934) != 0 || BrowserCmd_option == 'x')) {
      if (*cont) {
        BrowserCmd_Wch(';');
      }
      BrowserCmd_Wln();
      BrowserCmd_Indent(BrowserCmd_global.level);
      BrowserCmd_global.level += 1;
      BrowserCmd_Wch('(');
      if (__STRCMPCC(obj->name->data, (CHAR*)"@tproc", 7, (CHAR*)"BrowserCmd", 57095) != 0) {
        if ((INTEGER)obj->link->mode == 2) {
          if (BrowserCmd_lang == 'C') {
            if ((INTEGER)obj->link->vis == 3) {
              BrowserCmd_Ws((CHAR*)"IN ", 4);
            } else if ((INTEGER)obj->link->vis == 4) {
              BrowserCmd_Ws((CHAR*)"OUT ", 5);
            } else {
              BrowserCmd_Ws((CHAR*)"VAR ", 5);
            }
          } else if ((INTEGER)obj->link->vis != 3) {
            BrowserCmd_Ws((CHAR*)"VAR ", 5);
          }
          if (__ODD((INTEGER)obj->link->sysflag)) {
            BrowserCmd_Ws((CHAR*)"[nil] ", 7);
          }
        }
        _ptr__26 = obj->link->name;
        BrowserCmd_Ws((void*)_ptr__26->data, _ptr__26->len[0]);
        BrowserCmd_Ws((CHAR*)": ", 3);
        BrowserCmd_Wtype(obj->link->typ);
      }
      BrowserCmd_Ws((CHAR*)") ", 3);
      _ptr__25 = obj->name;
      BrowserCmd_Ws((void*)_ptr__25->data, _ptr__25->len[0]);
      BrowserCmd_Wsign(obj->typ, obj->link->link);
      if (BrowserCmd_lang == 'C') {
        if (__IN(16, (SET)obj->link->typ->attribute)) {
          BrowserCmd_Ws((CHAR*)", NEW", 6);
        }
        if (__IN(17, (SET)obj->link->typ->attribute)) {
          BrowserCmd_Ws((CHAR*)", ABSTRACT", 11);
        } else if (__IN(19, (SET)obj->link->typ->attribute)) {
          BrowserCmd_Ws((CHAR*)", EMPTY", 8);
        } else if (__IN(20, (SET)obj->link->typ->attribute)) {
          BrowserCmd_Ws((CHAR*)", EXTENSIBLE", 13);
        }
      }
      *cont = 1;
      if (BrowserCmd_option == 'x') {
        BrowserCmd_Indent(1);
        BrowserCmd_Ws((CHAR*)"(* methno: ", 12);
        BrowserCmd_Wi(__ASHR(obj->adr, 16, INTEGER));
        BrowserCmd_Ws((CHAR*)" *)", 4);
      }
      BrowserCmd_global.level -= 1;
    }
    BrowserCmd_Wmthd(obj->right, cont);
  }
}

static void BrowserCmd_Wflds (OfrontOPT_Struct typ, BOOLEAN *cont)
{
  OfrontOPT_Object fld = NIL;
  OfrontOPS_String _ptr__20 = NIL;
  OfrontOPS_String _ptr__19 = NIL;
  fld = typ->link;
  while (fld != NIL && (INTEGER)fld->mode == 4) {
    if (BrowserCmd_option == 'x' || (fld->name->data)[0] != '@') {
      if (*cont) {
        BrowserCmd_Wch(';');
      }
      BrowserCmd_Wln();
      BrowserCmd_Indent(BrowserCmd_global.level);
      if (BrowserCmd_option == 'x') {
        BrowserCmd_Wi(fld->adr);
        BrowserCmd_Wch(' ');
      }
      _ptr__20 = fld->name;
      BrowserCmd_Ws((void*)_ptr__20->data, _ptr__20->len[0]);
      while ((fld->link != NIL && fld->link->typ == fld->typ) && fld->link->name != NIL) {
        if ((INTEGER)fld->vis == 2) {
          BrowserCmd_Wch('-');
        }
        fld = fld->link;
        BrowserCmd_Ws((CHAR*)", ", 3);
        _ptr__19 = fld->name;
        BrowserCmd_Ws((void*)_ptr__19->data, _ptr__19->len[0]);
      }
      if ((INTEGER)fld->vis == 2) {
        BrowserCmd_Wch('-');
      }
      BrowserCmd_Ws((CHAR*)": ", 3);
      BrowserCmd_Wtype(fld->typ);
      *cont = 1;
    }
    fld = fld->link;
  }
}

static struct Wstruct__31 {
  OfrontOPT_Struct *typ;
  struct Wstruct__31 *lnk;
} *Wstruct__31_s;

static void __32 (void);

static void __32 (void)
{
  if (BrowserCmd_option == 'x' && (INTEGER)((*Wstruct__31_s->typ))->sysflag != 0) {
    BrowserCmd_Ws((CHAR*)" [", 3);
    BrowserCmd_Wi(((*Wstruct__31_s->typ))->sysflag);
    BrowserCmd_Wch(']');
  } else {
    switch (__MASK((INTEGER)((*Wstruct__31_s->typ))->sysflag, -256)) {
      case 0: 
        break;
      case 1: 
        BrowserCmd_Ws((CHAR*)" [notag]", 9);
        break;
      case 3: 
        BrowserCmd_Ws((CHAR*)" [noalign]", 11);
        break;
      case 4: 
        BrowserCmd_Ws((CHAR*)" [align2]", 10);
        break;
      case 5: 
        BrowserCmd_Ws((CHAR*)" [align4]", 10);
        break;
      case 6: 
        BrowserCmd_Ws((CHAR*)" [align8]", 10);
        break;
      case 7: 
        BrowserCmd_Ws((CHAR*)" [union]", 9);
        break;
      default: 
        BrowserCmd_Ws((CHAR*)" [", 3);
        BrowserCmd_Wi(__MASK((INTEGER)((*Wstruct__31_s->typ))->sysflag, -256));
        BrowserCmd_Wch(']');
        break;
    }
  }
}

static void BrowserCmd_Wstruct (OfrontOPT_Struct typ)
{
  BOOLEAN cont;
  struct Wstruct__31 _s;
  _s.typ = &typ;
  _s.lnk = Wstruct__31_s;
  Wstruct__31_s = &_s;
  BrowserCmd_global.level += 1;
  switch (typ->form) {
    case 0: 
      BrowserCmd_Ws((CHAR*)"Undef", 6);
      break;
    case 13: 
      BrowserCmd_Ws((CHAR*)"POINTER", 8);
      __32();
      BrowserCmd_Ws((CHAR*)" TO ", 5);
      BrowserCmd_global.level -= 1;
      BrowserCmd_Wtype(typ->BaseTyp);
      BrowserCmd_global.level += 1;
      break;
    case 15: 
      BrowserCmd_Ws((CHAR*)"PROCEDURE", 10);
      if ((INTEGER)typ->sysflag == 1) {
        BrowserCmd_Ws((CHAR*)" [stdcall]", 11);
      } else if ((INTEGER)typ->sysflag == 2) {
        BrowserCmd_Ws((CHAR*)" [fastcall]", 12);
      }
      BrowserCmd_Wsign(typ->BaseTyp, typ->link);
      break;
    case 16: 
      switch (typ->comp) {
        case 2: 
          BrowserCmd_Ws((CHAR*)"ARRAY", 6);
          __32();
          BrowserCmd_Wch(' ');
          BrowserCmd_Wi(typ->n);
          BrowserCmd_Ws((CHAR*)" OF ", 5);
          BrowserCmd_Wtype(typ->BaseTyp);
          break;
        case 3: 
          BrowserCmd_Ws((CHAR*)"ARRAY", 6);
          __32();
          BrowserCmd_Ws((CHAR*)" OF ", 5);
          BrowserCmd_Wtype(typ->BaseTyp);
          break;
        case 4: 
          if (BrowserCmd_lang == 'C') {
            if ((INTEGER)typ->attribute == 17) {
              BrowserCmd_Ws((CHAR*)"ABSTRACT ", 10);
            } else if ((INTEGER)typ->attribute == 18) {
              BrowserCmd_Ws((CHAR*)"LIMITED ", 9);
            } else if ((INTEGER)typ->attribute == 20) {
              BrowserCmd_Ws((CHAR*)"EXTENSIBLE ", 12);
            }
          }
          BrowserCmd_Ws((CHAR*)"RECORD", 7);
          __32();
          cont = 0;
          if (typ->BaseTyp != NIL) {
            BrowserCmd_Ws((CHAR*)" (", 3);
            BrowserCmd_Wtype(typ->BaseTyp);
            BrowserCmd_Wch(')');
          }
          BrowserCmd_Wflds(typ, &cont);
          BrowserCmd_Wmthd(typ->link, &cont);
          if (cont) {
            BrowserCmd_Wln();
            BrowserCmd_Indent(BrowserCmd_global.level - 1);
          } else {
            BrowserCmd_Wch(' ');
          }
          BrowserCmd_Ws((CHAR*)"END", 4);
          if (BrowserCmd_option == 'x') {
            BrowserCmd_Indent(1);
            BrowserCmd_Ws((CHAR*)"(* size: ", 10);
            BrowserCmd_Wi(typ->size);
            BrowserCmd_Ws((CHAR*)" align: ", 9);
            BrowserCmd_Wi(typ->align);
            BrowserCmd_Ws((CHAR*)" nofm: ", 8);
            BrowserCmd_Wi(typ->n);
            BrowserCmd_Ws((CHAR*)" *)", 4);
          }
          break;
        default: __CASECHK((CHAR*)"BrowserCmd", 82687);
      }
      break;
    default: 
      if (typ->BaseTyp != OfrontOPT_undftyp) {
        BrowserCmd_Wtype(typ->BaseTyp);
      }
      break;
  }
  BrowserCmd_global.level -= 1;
  Wstruct__31_s = _s.lnk;
}

static void BrowserCmd_Wtype (OfrontOPT_Struct typ)
{
  OfrontOPT_Object obj = NIL;
  OfrontOPS_String _ptr__39 = NIL;
  OfrontOPS_String _ptr__38 = NIL;
  OfrontOPS_String _ptr__37 = NIL;
  OfrontOPS_String _ptr__36 = NIL;
  OfrontOPS_String _ptr__35 = NIL;
  obj = typ->strobj;
  if (obj->name != OfrontOPT_null) {
    if ((INTEGER)typ->mno != 0) {
      _ptr__39 = OfrontOPT_GlbMod[__X(typ->mno, 64, (CHAR*)"BrowserCmd", 86070)]->name;
      BrowserCmd_Ws((void*)_ptr__39->data, _ptr__39->len[0]);
      BrowserCmd_Wch('.');
    } else if (typ == OfrontOPT_sysptrtyp) {
      BrowserCmd_Ws((CHAR*)"SYSTEM.", 8);
    } else if ((INTEGER)obj->vis == 0) {
      BrowserCmd_Wch('#');
    }
    if (BrowserCmd_lang == 'C') {
      if (obj == OfrontOPT_char8typ->strobj) {
        BrowserCmd_Ws((CHAR*)"SHORTCHAR", 10);
      } else if (obj == OfrontOPT_char16typ->strobj) {
        BrowserCmd_Ws((CHAR*)"CHAR", 5);
      } else if (obj == OfrontOPT_bytetyp->strobj) {
        BrowserCmd_Ws((CHAR*)"BYTE", 5);
      } else if (obj == OfrontOPT_sinttyp->strobj) {
        BrowserCmd_Ws((CHAR*)"SHORTINT", 9);
      } else if (obj == OfrontOPT_inttyp->strobj) {
        BrowserCmd_Ws((CHAR*)"INTEGER", 8);
      } else if (obj == OfrontOPT_linttyp->strobj) {
        BrowserCmd_Ws((CHAR*)"LONGINT", 8);
      } else if (obj == OfrontOPT_realtyp->strobj) {
        BrowserCmd_Ws((CHAR*)"SHORTREAL", 10);
      } else if (obj == OfrontOPT_lrltyp->strobj) {
        BrowserCmd_Ws((CHAR*)"REAL", 5);
      } else if (obj == OfrontOPT_ubytetyp->strobj) {
        BrowserCmd_Ws((CHAR*)"UBYTE", 6);
      } else {
        _ptr__38 = obj->name;
        BrowserCmd_Ws((void*)_ptr__38->data, _ptr__38->len[0]);
      }
    } else if (BrowserCmd_lang == '3') {
      if (obj == OfrontOPT_char8typ->strobj) {
        BrowserCmd_Ws((CHAR*)"CHAR", 5);
      } else if (obj == OfrontOPT_char16typ->strobj) {
        BrowserCmd_Ws((CHAR*)"LONGCHAR", 9);
      } else if (obj == OfrontOPT_bytetyp->strobj) {
        BrowserCmd_Ws((CHAR*)"INT8", 5);
      } else if (obj == OfrontOPT_sinttyp->strobj) {
        BrowserCmd_Ws((CHAR*)"INT16", 6);
      } else if (obj == OfrontOPT_inttyp->strobj) {
        BrowserCmd_Ws((CHAR*)"INT32", 6);
      } else if (obj == OfrontOPT_linttyp->strobj) {
        BrowserCmd_Ws((CHAR*)"INT64", 6);
      } else if (obj == OfrontOPT_realtyp->strobj) {
        BrowserCmd_Ws((CHAR*)"REAL32", 7);
      } else if (obj == OfrontOPT_lrltyp->strobj) {
        BrowserCmd_Ws((CHAR*)"REAL64", 7);
      } else if (obj == OfrontOPT_ubytetyp->strobj) {
        BrowserCmd_Ws((CHAR*)"SYSTEM.BYTE", 12);
      } else {
        _ptr__37 = obj->name;
        BrowserCmd_Ws((void*)_ptr__37->data, _ptr__37->len[0]);
      }
    } else if (BrowserCmd_lang <= '2') {
      if (obj == OfrontOPT_char8typ->strobj) {
        BrowserCmd_Ws((CHAR*)"CHAR", 5);
      } else if (obj == OfrontOPT_bytetyp->strobj) {
        BrowserCmd_Ws((CHAR*)"SHORTINT", 9);
      } else if (obj == OfrontOPT_sinttyp->strobj) {
        BrowserCmd_Ws((CHAR*)"INTEGER", 8);
      } else if (obj == OfrontOPT_inttyp->strobj) {
        BrowserCmd_Ws((CHAR*)"LONGINT", 8);
      } else if (obj == OfrontOPT_linttyp->strobj) {
        BrowserCmd_Ws((CHAR*)"HUGEINT", 8);
      } else if (obj == OfrontOPT_realtyp->strobj) {
        BrowserCmd_Ws((CHAR*)"REAL", 5);
      } else if (obj == OfrontOPT_lrltyp->strobj) {
        BrowserCmd_Ws((CHAR*)"LONGREAL", 9);
      } else if (obj == OfrontOPT_ubytetyp->strobj) {
        BrowserCmd_Ws((CHAR*)"SYSTEM.BYTE", 12);
      } else if (obj == OfrontOPT_char16typ->strobj) {
        BrowserCmd_Ws((CHAR*)"SYSTEM.CHAR16", 14);
      } else {
        _ptr__36 = obj->name;
        BrowserCmd_Ws((void*)_ptr__36->data, _ptr__36->len[0]);
      }
    } else {
      if (obj == OfrontOPT_char8typ->strobj) {
        BrowserCmd_Ws((CHAR*)"CHAR", 5);
      } else if (obj == OfrontOPT_ubytetyp->strobj) {
        BrowserCmd_Ws((CHAR*)"BYTE", 5);
      } else if (obj == OfrontOPT_bytetyp->strobj) {
        BrowserCmd_Ws((CHAR*)"SYSTEM.INT8", 12);
      } else if (obj == OfrontOPT_sinttyp->strobj) {
        BrowserCmd_Ws((CHAR*)"SYSTEM.INT16", 13);
      } else if (obj == OfrontOPT_inttyp->strobj) {
        BrowserCmd_Ws((CHAR*)"INTEGER", 8);
      } else if (obj == OfrontOPT_linttyp->strobj) {
        BrowserCmd_Ws((CHAR*)"SYSTEM.INT64", 13);
      } else if (obj == OfrontOPT_realtyp->strobj) {
        BrowserCmd_Ws((CHAR*)"REAL", 5);
      } else if (obj == OfrontOPT_lrltyp->strobj) {
        BrowserCmd_Ws((CHAR*)"SYSTEM.REAL64", 14);
      } else if (obj == OfrontOPT_char16typ->strobj) {
        BrowserCmd_Ws((CHAR*)"SYSTEM.CHAR16", 14);
      } else {
        _ptr__35 = obj->name;
        BrowserCmd_Ws((void*)_ptr__35->data, _ptr__35->len[0]);
      }
    }
  } else {
    if (BrowserCmd_option == 'x' && (INTEGER)typ->ref > 1754) {
      BrowserCmd_Wch('#');
      BrowserCmd_Wi((INTEGER)typ->ref - 1754);
      BrowserCmd_Wch(' ');
    }
    BrowserCmd_Wstruct(typ);
  }
}

static struct WModule__11 {
  Texts_Text *T;
  INTEGER *beg, *end;
  struct WModule__11 *lnk;
} *WModule__11_s;

static void __13 (void);
static void __15 (CHAR *s, INTEGER s__len);

static void __15 (CHAR *s, INTEGER s__len)
{
  (*WModule__11_s->beg) = BrowserCmd_W.buf->len;
  BrowserCmd_Indent(1);
  BrowserCmd_Ws((void*)s, s__len);
  BrowserCmd_Wln();
  (*WModule__11_s->end) = BrowserCmd_W.buf->len;
  BrowserCmd_global.level = 2;
}

static void __13 (void)
{
  INTEGER len;
  BrowserCmd_global.gap = 1;
  len = ((*WModule__11_s->T))->len;
  if ((*WModule__11_s->end) == BrowserCmd_W.buf->len) {
    Texts_Append((*WModule__11_s->T), BrowserCmd_W.buf);
    Texts_Delete((*WModule__11_s->T), len + (*WModule__11_s->beg), len + (*WModule__11_s->end));
  }
}

static void BrowserCmd_WModule (OfrontOPS_Name name, Texts_Text T)
{
  INTEGER i, beg, end;
  BOOLEAN first, done;
  OfrontOPS_String _ptr__12 = NIL;
  struct WModule__11 _s;
  _s.T = &T;
  _s.beg = &beg;
  _s.end = &end;
  _s.lnk = WModule__11_s;
  WModule__11_s = &_s;
  OfrontOPT_Import((CHAR*)"@notself", 9, (void*)name, 48, &done);
  if (done) {
    BrowserCmd_Ws((CHAR*)"DEFINITION ", 12);
    BrowserCmd_Ws((void*)name, 48);
    BrowserCmd_Ws((CHAR*)"; (* ", 6);
    switch (BrowserCmd_lang) {
      case '1': 
        BrowserCmd_Ws((CHAR*)"Oberon", 7);
        break;
      case '2': 
        BrowserCmd_Ws((CHAR*)"Oberon-2", 9);
        break;
      case '7': 
        BrowserCmd_Ws((CHAR*)"Oberon-07", 10);
        break;
      case 'C': 
        BrowserCmd_Ws((CHAR*)"Component Pascal", 17);
        break;
      case '3': 
        BrowserCmd_Ws((CHAR*)"Oberon-3", 9);
        break;
      default: __CASECHK((CHAR*)"BrowserCmd", 108287);
    }
    BrowserCmd_Ws((CHAR*)" *)", 4);
    BrowserCmd_Wln();
    BrowserCmd_global.gap = 1;
    __15((CHAR*)"IMPORT", 7);
    i = 1;
    first = 1;
    while (i < (INTEGER)OfrontOPT_nofGmod) {
      if (first) {
        first = 0;
        BrowserCmd_Indent(2);
      } else {
        BrowserCmd_Ws((CHAR*)", ", 3);
      }
      _ptr__12 = OfrontOPT_GlbMod[__X(i, 64, (CHAR*)"BrowserCmd", 109595)]->name;
      BrowserCmd_Ws((void*)_ptr__12->data, _ptr__12->len[0]);
      i += 1;
    }
    if (!first) {
      BrowserCmd_Wch(';');
      BrowserCmd_Wln();
    }
    __13();
    __15((CHAR*)"CONST", 6);
    BrowserCmd_Objects(OfrontOPT_GlbMod[0]->right, 0x08);
    __13();
    __15((CHAR*)"TYPE", 5);
    BrowserCmd_Objects(OfrontOPT_GlbMod[0]->right, 0x20);
    __13();
    __15((CHAR*)"VAR", 4);
    BrowserCmd_Objects(OfrontOPT_GlbMod[0]->right, 0x02);
    __13();
    BrowserCmd_Objects(OfrontOPT_GlbMod[0]->right, 0x0680);
    BrowserCmd_Wln();
    BrowserCmd_Ws((CHAR*)"END ", 5);
    BrowserCmd_Ws((void*)name, 48);
    BrowserCmd_Wch('.');
    BrowserCmd_Wln();
    Texts_Append(T, BrowserCmd_W.buf);
  } else {
    Texts_WriteString(&BrowserCmd_W, Texts_Writer__typ, (void*)name, 48);
    Texts_WriteString(&BrowserCmd_W, Texts_Writer__typ, (CHAR*)" -- symbol file not found", 26);
    Texts_WriteLn(&BrowserCmd_W, Texts_Writer__typ);
    Texts_Append(T, BrowserCmd_W.buf);
  }
  WModule__11_s = _s.lnk;
}

static void BrowserCmd_Ident (CHAR *name, INTEGER name__len, CHAR *first, INTEGER first__len)
{
  SHORTINT i, j;
  CHAR ch;
  i = 0;
  while (name[__X(i, name__len, (CHAR*)"BrowserCmd", 114708)] != 0x00) {
    i += 1;
  }
  while ((INTEGER)i >= 0 && name[__X(i, name__len, (CHAR*)"BrowserCmd", 114978)] != '/') {
    i -= 1;
  }
  i += 1;
  j = 0;
  ch = name[__X(i, name__len, (CHAR*)"BrowserCmd", 115231)];
  while (ch != '.' && ch != 0x00) {
    first[__X(j, first__len, (CHAR*)"BrowserCmd", 115504)] = ch;
    i += 1;
    j += 1;
    ch = name[__X(i, name__len, (CHAR*)"BrowserCmd", 115535)];
  }
  first[__X(j, first__len, (CHAR*)"BrowserCmd", 115967)] = 0x00;
}

void BrowserCmd_ShowDef (void)
{
  Texts_Text T = NIL;
  Texts_Text dummyT = NIL;
  OfrontOPS_Name S, vname, name;
  Texts_Reader R = {0};
  CHAR ch;
  CHAR s[1024];
  SHORTINT i;
  BrowserCmd_option = 0x00;
  CmdArgs_Get(1, (void*)S, 48);
  if (CmdArgs_Count > 1) {
    if (S[0] == '-') {
      BrowserCmd_option = S[1];
      CmdArgs_Get(2, (void*)S, 48);
    } else {
      CmdArgs_Get(2, (void*)vname, 48);
      BrowserCmd_option = vname[1];
    }
  }
  switch (BrowserCmd_option) {
    case '1': case '2': case '3': case '7': 
      BrowserCmd_lang = BrowserCmd_option;
      break;
    default: 
      BrowserCmd_lang = 'C';
      break;
  }
  if (CmdArgs_Count >= 1) {
    BrowserCmd_Ident((void*)S, 48, (void*)name, 48);
    __NEW(T, Texts_TextDesc);
    Texts_Open(T, (CHAR*)"", 1);
    OfrontOPT_Init((void*)name, 48, BrowserCmd_lang, 0x0);
    __MOVE((CHAR*)"AvoidErr154", OfrontOPT_SelfName, 12);
    BrowserCmd_WModule(name, T);
    OfrontOPT_Close();
    Texts_OpenReader(&R, Texts_Reader__typ, T, 0);
    Texts_Read(&R, Texts_Reader__typ, &ch);
    i = 0;
    while (!R.eot) {
      if (ch == 0x0d) {
        s[__X(i, 1024, (CHAR*)"BrowserCmd", 120863)] = 0x00;
        i = 0;
        Console_String((void*)s, 1024);
        Console_Ln();
      } else {
        s[__X(i, 1024, (CHAR*)"BrowserCmd", 121107)] = ch;
        i += 1;
      }
      Texts_Read(&R, Texts_Reader__typ, &ch);
    }
    s[__X(i, 1024, (CHAR*)"BrowserCmd", 122125)] = 0x00;
    Console_String((void*)s, 1024);
  }
}

/*----------------------------------------------------------------------------*/
static void EnumPtrs(void (*P)(void*))
{
  __ENUMR(&BrowserCmd_W, Texts_Writer__typ, 56, 1, P);
}

__TDESC(BrowserCmd__1__desc, 1, 0) = {__TDFLDS("", 8), {-4}};

int main (int argc, char **argv)
{
  __INIT(argc, argv);
  __IMPORT(CmdArgs__init);
  __IMPORT(Console__init);
  __IMPORT(OfrontOPM__init);
  __IMPORT(OfrontOPS__init);
  __IMPORT(OfrontOPT__init);
  __IMPORT(OfrontOPV__init);
  __IMPORT(Texts__init);
  __REGMAIN("BrowserCmd", EnumPtrs);
  __REGCMD("ShowDef", BrowserCmd_ShowDef);
  __INITYP(BrowserCmd__1, BrowserCmd__1, 0);
/* BEGIN */
  __MOVE((CHAR*)"0123456789ABCDEF", BrowserCmd_hex, 17);
  OfrontOPT_typSize = OfrontOPV_TypSize;
  Texts_OpenWriter(&BrowserCmd_W, Texts_Writer__typ);
  if (CmdArgs_Count != 0) {
    BrowserCmd_ShowDef();
  } else {
    Console_String((CHAR*)"Ofront+ (TM) Show Definition (Browser) Tool v1.0", 49);
    Console_Ln();
    Console_String((CHAR*)"Copyright (c) Software Templ OG, 1995-2020 & VEDAsoft Oberon Club, 2013-2025", 77);
    Console_Ln();
    Console_Ln();
    Console_String((CHAR*)"  command = \"showdef\" [-option] module", 39);
    Console_Ln();
    Console_String((CHAR*)"  option  = \"1\" | \"2\" | \"7\" | \"C\" | \"3\" | \"x\"", 46);
    Console_Ln();
    Console_Ln();
    Console_String((CHAR*)"       \"1\": Oberon (1990)", 26);
    Console_Ln();
    Console_String((CHAR*)"       \"2\": Oberon-2", 21);
    Console_Ln();
    Console_String((CHAR*)"       \"7\": Oberon-07/16", 25);
    Console_Ln();
    Console_String((CHAR*)"       \"C\": Component Pascal (by default)", 42);
    Console_Ln();
    Console_String((CHAR*)"       \"3\": Oberon-3 (experimental dialect)", 44);
    Console_Ln();
    Console_String((CHAR*)"       \"x\": eXtra system information", 37);
    Console_Ln();
  }
  __FINI;
}
