/* Ofront+ 1.0 -swC -88 */
#include "SYSTEM.oh"
#include "bbLinLibc.oh"
#include "bbLinLibW.oh"

typedef
  struct bbKernel_Type__rec *bbKernel_Type;

struct bbKernel__1 {
  INTEGER id;
  bbKernel_Type struct_;
};

typedef
  void (*bbKernel_Command)(void);

typedef
  struct bbKernel_Directory__rec *bbKernel_Directory;

typedef
  struct bbKernel_ObjDesc {
    INTEGER fprint, offs, id;
    bbKernel_Type struct_;
  } bbKernel_ObjDesc;

typedef
  struct bbKernel_Directory__rec {
    INTEGER num;
    bbKernel_ObjDesc obj[1000000];
  } bbKernel_Directory__rec;

typedef
  void (*bbKernel_Handler)(void);

typedef
  struct bbKernel_Hook__rec *bbKernel_Hook;

typedef
  struct bbKernel_Hook__rec {
    char _prvt0[1];
  } bbKernel_Hook__rec;

typedef
  struct bbKernel_Module__rec *bbKernel_Module;

typedef
  CHAR bbKernel_Utf8Name[256];

typedef
  struct bbKernel_Module__rec {
    bbKernel_Module next;
    SET opts;
    INTEGER refcnt;
    SHORTINT compTime[6], loadTime[6];
    bbKernel_Command body, term;
    INTEGER nofimps, nofptrs, csize, dsize, rsize, code, data, refs, procBase, varBase;
    CHAR *names;
    INTEGER *ptrs;
    bbKernel_Module *imports;
    bbKernel_Directory export_;
    bbKernel_Utf8Name name;
  } bbKernel_Module__rec;

typedef
  LONGCHAR bbKernel_Name[256];

typedef
  bbKernel_ObjDesc *bbKernel_Object;

typedef
  struct bbKernel_Signature__rec *bbKernel_Signature;

typedef
  struct bbKernel_Signature__rec {
    bbKernel_Type retStruct;
    INTEGER num;
    struct bbKernel__1 par[1000000];
  } bbKernel_Signature__rec;

typedef
  struct bbKernel_Type__rec {
    INTEGER size;
    bbKernel_Module mod;
    INTEGER id;
    bbKernel_Type base[16];
    bbKernel_Directory fields;
    INTEGER ptroffs[1000000];
  } bbKernel_Type__rec;


export INTEGER bbKernel_trapCount;

export void **bbKernel_Hook__rec__typ;

export BOOLEAN bbKernel_IsAlpha (LONGCHAR ch);
export BOOLEAN bbKernel_IsLower (LONGCHAR ch);
export BOOLEAN bbKernel_IsUpper (LONGCHAR ch);
export LONGCHAR bbKernel_Lower (LONGCHAR ch);
export void bbKernel_MakeFileName (LONGCHAR *name, INTEGER name__len, LONGCHAR *type, INTEGER type__len);
export void bbKernel_SplitName (LONGCHAR *name, INTEGER name__len, LONGCHAR *head, INTEGER head__len, LONGCHAR *tail, INTEGER tail__len);
export void bbKernel_StringToUtf8 (LONGCHAR *in, INTEGER in__len, CHAR *out, INTEGER out__len, INTEGER *res);
export LONGCHAR bbKernel_Upper (LONGCHAR ch);
export void bbKernel_Utf8ToString (CHAR *in, INTEGER in__len, LONGCHAR *out, INTEGER out__len, INTEGER *res);


/*============================================================================*/

BOOLEAN bbKernel_IsAlpha (LONGCHAR ch)
{
  return bbLinLibW_iswalpha((INTEGER)ch) != 0;
}

/*----------------------------------------------------------------------------*/
LONGCHAR bbKernel_Upper (LONGCHAR ch)
{
  if ('a' <= ch && ch <= 'z') {
    return __CAP(ch);
  } else if (ch > 0x7f) {
    return (LONGCHAR)bbLinLibW_towupper((INTEGER)ch);
  } else {
    return ch;
  }
  __RETCHK((CHAR*)"bbKernel", 111103);
}

/*----------------------------------------------------------------------------*/
BOOLEAN bbKernel_IsUpper (LONGCHAR ch)
{
  if ('A' <= ch && ch <= 'Z') {
    return 1;
  } else if (ch > 0x7f) {
    return bbLinLibW_iswupper((INTEGER)ch) != 0;
  } else {
    return 0;
  }
  __RETCHK((CHAR*)"bbKernel", 113151);
}

/*----------------------------------------------------------------------------*/
LONGCHAR bbKernel_Lower (LONGCHAR ch)
{
  if ('A' <= ch && ch <= 'Z') {
    return (LONGCHAR)((INTEGER)ch + 32);
  } else if (ch > 0x7f) {
    return (LONGCHAR)bbLinLibW_towlower((INTEGER)ch);
  } else {
    return ch;
  }
  __RETCHK((CHAR*)"bbKernel", 115199);
}

/*----------------------------------------------------------------------------*/
BOOLEAN bbKernel_IsLower (LONGCHAR ch)
{
  if ('a' <= ch && ch <= 'z') {
    return 1;
  } else if (ch > 0x7f) {
    return bbLinLibW_iswlower((INTEGER)ch) != 0;
  } else {
    return 0;
  }
  __RETCHK((CHAR*)"bbKernel", 117247);
}

/*----------------------------------------------------------------------------*/
static struct Utf8ToString__9 {
  CHAR *in;
  INTEGER in__len;
  LONGCHAR *out;
  INTEGER out__len;
  INTEGER *res;
  struct Utf8ToString__9 *lnk;
} *Utf8ToString__9_s;

static void __10 (void);

static void __10 (void)
{
  __STRCOPYCL(Utf8ToString__9_s->in, Utf8ToString__9_s->out, Utf8ToString__9_s->out__len, (CHAR*)"bbKernel", 119314);
  *Utf8ToString__9_s->res = 2;
}

void bbKernel_Utf8ToString (CHAR *in, INTEGER in__len, LONGCHAR *out, INTEGER out__len, INTEGER *res)
{
  INTEGER i, j, val, max;
  CHAR ch;
  struct Utf8ToString__9 _s;
  _s.in = (void*)in; _s.in__len = in__len;
  _s.out = (void*)out; _s.out__len = out__len;
  _s.res = res;
  _s.lnk = Utf8ToString__9_s;
  Utf8ToString__9_s = &_s;
  ch = in[0];
  i = 1;
  j = 0;
  max = out__len - 1;
  while (ch != 0x00 && j < max) {
    if (ch < 0x80) {
      out[__X(j, out__len, (CHAR*)"bbKernel", 121104)] = ch;
      j += 1;
    } else if (ch < 0xe0) {
      val = (INTEGER)ch - 192;
      if (val < 0) {
        __10();
        Utf8ToString__9_s = _s.lnk;
        return;
      }
      ch = in[__X(i, in__len, (CHAR*)"bbKernel", 122127)];
      i += 1;
      val = (__ASHL(val, 6, INTEGER) + (INTEGER)ch) - 128;
      if (ch < 0x80 || ch >= 0xe0) {
        __10();
        Utf8ToString__9_s = _s.lnk;
        return;
      }
      out[__X(j, out__len, (CHAR*)"bbKernel", 122646)] = (LONGCHAR)val;
      j += 1;
    } else if (ch < 0xf0) {
      val = (INTEGER)ch - 224;
      ch = in[__X(i, in__len, (CHAR*)"bbKernel", 123407)];
      i += 1;
      val = (__ASHL(val, 6, INTEGER) + (INTEGER)ch) - 128;
      if (ch < 0x80 || ch >= 0xe0) {
        __10();
        Utf8ToString__9_s = _s.lnk;
        return;
      }
      ch = in[__X(i, in__len, (CHAR*)"bbKernel", 123919)];
      i += 1;
      val = (__ASHL(val, 6, INTEGER) + (INTEGER)ch) - 128;
      if (ch < 0x80 || ch >= 0xe0) {
        __10();
        Utf8ToString__9_s = _s.lnk;
        return;
      }
      out[__X(j, out__len, (CHAR*)"bbKernel", 124438)] = (LONGCHAR)val;
      j += 1;
    } else {
      __10();
      Utf8ToString__9_s = _s.lnk;
      return;
    }
    ch = in[__X(i, in__len, (CHAR*)"bbKernel", 125454)];
    i += 1;
  }
  out[__X(j, out__len, (CHAR*)"bbKernel", 125966)] = 0x00;
  if (ch == 0x00) {
    *res = 0;
  } else {
    *res = 1;
  }
  Utf8ToString__9_s = _s.lnk;
}

/*----------------------------------------------------------------------------*/
void bbKernel_StringToUtf8 (LONGCHAR *in, INTEGER in__len, CHAR *out, INTEGER out__len, INTEGER *res)
{
  INTEGER i, j, val, max;
  i = 0;
  j = 0;
  max = out__len - 3;
  while (in[__X(i, in__len, (CHAR*)"bbKernel", 128288)] != 0x00 && j < max) {
    val = (INTEGER)in[__X(i, in__len, (CHAR*)"bbKernel", 128532)];
    i += 1;
    if (val < 128) {
      out[__X(j, out__len, (CHAR*)"bbKernel", 129053)] = (CHAR)val;
      j += 1;
    } else if (val < 2048) {
      out[__X(j, out__len, (CHAR*)"bbKernel", 129578)] = (CHAR)(__ASHR(val, 6, INTEGER) + 192);
      j += 1;
      out[__X(j, out__len, (CHAR*)"bbKernel", 129834)] = (CHAR)(__MASK(val, -64) + 128);
      j += 1;
    } else {
      out[__X(j, out__len, (CHAR*)"bbKernel", 130348)] = (CHAR)(__ASHR(val, 12, INTEGER) + 224);
      j += 1;
      out[__X(j, out__len, (CHAR*)"bbKernel", 130609)] = (CHAR)(__MASK(__ASHR(val, 6, INTEGER), -64) + 128);
      j += 1;
      out[__X(j, out__len, (CHAR*)"bbKernel", 130858)] = (CHAR)(__MASK(val, -64) + 128);
      j += 1;
    }
  }
  out[__X(j, out__len, (CHAR*)"bbKernel", 131598)] = 0x00;
  if (in[__X(i, in__len, (CHAR*)"bbKernel", 132095)] == 0x00) {
    *res = 0;
  } else {
    *res = 1;
  }
}

/*----------------------------------------------------------------------------*/
void bbKernel_SplitName (LONGCHAR *name, INTEGER name__len, LONGCHAR *head, INTEGER head__len, LONGCHAR *tail, INTEGER tail__len)
{
  INTEGER i, j;
  LONGCHAR ch, lch;
  i = 0;
  ch = name[0];
  if (ch != 0x00) {
    do {
      head[__X(i, head__len, (CHAR*)"bbKernel", 134417)] = ch;
      lch = ch;
      i += 1;
      ch = name[__X(i, name__len, (CHAR*)"bbKernel", 134655)];
    } while (!((ch == 0x00 || ch == '.') || (bbKernel_IsUpper(ch) && !bbKernel_IsUpper(lch))));
    if (ch == '.') {
      i = 0;
      ch = name[0];
    }
    head[__X(i, head__len, (CHAR*)"bbKernel", 135184)] = 0x00;
    j = 0;
    while (ch != 0x00) {
      tail[__X(j, tail__len, (CHAR*)"bbKernel", 135457)] = ch;
      i += 1;
      j += 1;
      ch = name[__X(i, name__len, (CHAR*)"bbKernel", 135488)];
    }
    tail[__X(j, tail__len, (CHAR*)"bbKernel", 135696)] = 0x00;
    if (tail[0] == 0x00) {
      __STRCOPYLL(head, tail, __MIN(tail__len, head__len), (CHAR*)"bbKernel", 135970);
      head[0] = 0x00;
    }
  } else {
    head[0] = 0x00;
    tail[0] = 0x00;
  }
}

/*----------------------------------------------------------------------------*/
void bbKernel_MakeFileName (LONGCHAR *name, INTEGER name__len, LONGCHAR *type, INTEGER type__len)
{
  INTEGER i, j;
  LONGCHAR ext[8];
  LONGCHAR ch;
  i = 0;
  while (name[__X(i, name__len, (CHAR*)"bbKernel", 138280)] != 0x00 && name[__X(i, name__len, (CHAR*)"bbKernel", 138280)] != '.') {
    i += 1;
  }
  if (name[__X(i, name__len, (CHAR*)"bbKernel", 141567)] == '.') {
    if (name[__X(i + 1, name__len, (CHAR*)"bbKernel", 139007)] == 0x00) {
      name[__X(i, name__len, (CHAR*)"bbKernel", 138793)] = 0x00;
    }
  } else {
    if (type[0] == 0x00) {
      __MOVE(((LONGCHAR[]){111, 100, 99, 0}), ext, 8);
    } else {
      __STRCOPYLL(type, ext, __MIN(8, type__len), (CHAR*)"bbKernel", 139317);
    }
    if (i < (name__len - __STRLENL(ext, 8, (CHAR*)"bbKernel", 141311)) - 1) {
      name[__X(i, name__len, (CHAR*)"bbKernel", 139794)] = '.';
      i += 1;
      j = 0;
      ch = ext[0];
      while (ch != 0x00) {
        name[__X(i, name__len, (CHAR*)"bbKernel", 140313)] = bbKernel_Lower(ch);
        i += 1;
        j += 1;
        ch = ext[__X(j, 8, (CHAR*)"bbKernel", 140543)];
      }
      name[__X(i, name__len, (CHAR*)"bbKernel", 141055)] = 0x00;
    }
  }
}

/*----------------------------------------------------------------------------*/
__TDESC(bbKernel_Hook__rec__desc, 1, 0) = {__TDFLDS("Hook__rec", 1), {-8}};

export void *bbKernel__init (void)
{
  __DEFMOD;
  __REGMOD("bbKernel", 0);
  __INITYP(bbKernel_Hook__rec, bbKernel_Hook__rec, 0);
/* BEGIN */
  __ENDMOD;
}
