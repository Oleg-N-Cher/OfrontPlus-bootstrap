/* Ofront+ 1.0 -sC -44 */
#include "SYSTEM.oh"
#include "Files.oh"
#include "Platform.oh"
#include "Modules.oh"
#include "Heap.oh"
#include "Reals.oh"

typedef
  struct Texts_Alien__rec *Texts_Alien;

typedef
  struct Texts_RunDesc *Texts_Run;

typedef
  struct Texts_FontDesc *Texts_FontsFont;

typedef
  struct Texts_RunDesc {
    Texts_Run prev, next;
    INTEGER len;
    Texts_FontsFont fnt;
    BYTE col, voff;
    BOOLEAN ascii;
  } Texts_RunDesc;

typedef
  struct Texts_ElemDesc *Texts_Elem;

typedef
  struct Texts_ElemMsg {
    char _prvt0[1];
  } Texts_ElemMsg;

typedef
  void (*Texts_Handler)(Texts_Elem, Texts_ElemMsg*, void **);

typedef
  struct Texts_TextDesc *Texts_Text;

typedef
  struct Texts_ElemDesc {
    Texts_Run prev, next;
    INTEGER len;
    Texts_FontsFont fnt;
    BYTE col, voff;
    BOOLEAN ascii;
    INTEGER W, H;
    Texts_Handler handle;
    Texts_Text base;
  } Texts_ElemDesc;

typedef
  struct Texts_Alien__rec { /* Texts_ElemDesc */
    Texts_Run prev, next;
    INTEGER len;
    Texts_FontsFont fnt;
    BYTE col, voff;
    BOOLEAN ascii;
    INTEGER W, H;
    Texts_Handler handle;
    Texts_Text base;
    Files_File file;
    INTEGER org, span;
    CHAR mod[32], proc[32];
  } Texts_Alien__rec;

typedef
  struct Texts_BufDesc {
    INTEGER len;
    Texts_Run head;
  } Texts_BufDesc;

typedef
  Texts_BufDesc *Texts_Buffer;

typedef
  struct Texts_CopyMsg { /* Texts_ElemMsg */
    Texts_Elem e;
  } Texts_CopyMsg;

typedef
  struct Texts_FileMsg { /* Texts_ElemMsg */
    SHORTINT id;
    INTEGER pos;
    Files_Rider r;
  } Texts_FileMsg;

typedef
  struct Texts_FontDesc {
    CHAR name[32];
  } Texts_FontDesc;

typedef
  struct Texts_IdentifyMsg { /* Texts_ElemMsg */
    CHAR mod[32], proc[32];
  } Texts_IdentifyMsg;

typedef
  void (*Texts_Notifier)(Texts_Text, SHORTINT, INTEGER, INTEGER);

typedef
  struct Texts_PieceDesc *Texts_Piece;

typedef
  struct Texts_PieceDesc {
    Texts_Run prev, next;
    INTEGER len;
    Texts_FontsFont fnt;
    BYTE col, voff;
    BOOLEAN ascii;
    Files_File file;
    INTEGER org;
  } Texts_PieceDesc;

typedef
  struct Texts_Reader {
    BOOLEAN eot;
    Texts_FontsFont fnt;
    BYTE col, voff;
    Texts_Elem elem;
    Files_Rider rider;
    Texts_Run run;
    INTEGER org, off;
  } Texts_Reader;

typedef
  struct Texts_Scanner { /* Texts_Reader */
    BOOLEAN eot;
    Texts_FontsFont fnt;
    BYTE col, voff;
    Texts_Elem elem;
    Files_Rider rider;
    Texts_Run run;
    INTEGER org, off;
    CHAR nextCh;
    SHORTINT line, class;
    INTEGER i;
    SHORTREAL x;
    REAL y;
    CHAR c;
    BYTE len;
    CHAR s[64];
  } Texts_Scanner;

typedef
  struct Texts_TextDesc {
    INTEGER len;
    Texts_Notifier notify;
    Texts_Run head, cache;
    INTEGER corg;
  } Texts_TextDesc;

typedef
  struct Texts_Writer {
    Texts_Buffer buf;
    Texts_FontsFont fnt;
    BYTE col, voff;
    Files_Rider rider;
    Files_File file;
  } Texts_Writer;


export Texts_Elem Texts_new;
static Texts_Buffer Texts_del;
static Texts_FontsFont Texts_FontsDefault;

export void **Texts_FontDesc__typ;
export void **Texts_RunDesc__typ;
export void **Texts_PieceDesc__typ;
export void **Texts_ElemMsg__typ;
export void **Texts_ElemDesc__typ;
export void **Texts_FileMsg__typ;
export void **Texts_CopyMsg__typ;
export void **Texts_IdentifyMsg__typ;
export void **Texts_BufDesc__typ;
export void **Texts_TextDesc__typ;
export void **Texts_Reader__typ;
export void **Texts_Scanner__typ;
export void **Texts_Writer__typ;
export void **Texts_Alien__rec__typ;

export void Texts_Append (Texts_Text T, Texts_Buffer B);
export void Texts_ChangeLooks (Texts_Text T, INTEGER beg, INTEGER end, SET sel, Texts_FontsFont fnt, BYTE col, BYTE voff);
static Texts_Elem Texts_CloneElem (Texts_Elem e);
static Texts_Piece Texts_ClonePiece (Texts_Piece p);
export void Texts_Close (Texts_Text T, CHAR *name, INTEGER name__len);
export void Texts_Copy (Texts_Buffer SB, Texts_Buffer DB);
export void Texts_CopyElem (Texts_Elem SE, Texts_Elem DE);
export void Texts_Delete (Texts_Text T, INTEGER beg, INTEGER end);
export Texts_Text Texts_ElemBase (Texts_Elem E);
export INTEGER Texts_ElemPos (Texts_Elem E);
static void Texts_Find (Texts_Text T, INTEGER *pos, Texts_Run *u, INTEGER *org, INTEGER *off);
static Texts_FontsFont Texts_FontsThis (CHAR *name, INTEGER name__len);
static void Texts_HandleAlien (Texts_Elem E, Texts_ElemMsg *msg, void **msg__typ);
export void Texts_Insert (Texts_Text T, INTEGER pos, Texts_Buffer B);
export void Texts_Load (Files_Rider *r, void **r__typ, Texts_Text T);
static void Texts_Load0 (Files_Rider *r, void **r__typ, Texts_Text T);
static void Texts_Merge (Texts_Text T, Texts_Run u, Texts_Run *v);
export void Texts_Open (Texts_Text T, CHAR *name, INTEGER name__len);
export void Texts_OpenBuf (Texts_Buffer B);
export void Texts_OpenReader (Texts_Reader *R, void **R__typ, Texts_Text T, INTEGER pos);
export void Texts_OpenScanner (Texts_Scanner *S, void **S__typ, Texts_Text T, INTEGER pos);
export void Texts_OpenWriter (Texts_Writer *W, void **W__typ);
export INTEGER Texts_Pos (Texts_Reader *R, void **R__typ);
export void Texts_Read (Texts_Reader *R, void **R__typ, CHAR *ch);
export void Texts_ReadElem (Texts_Reader *R, void **R__typ);
export BOOLEAN Texts_ReadLong (Texts_Reader *R, void **R__typ, LONGCHAR *longch);
export void Texts_ReadPrevElem (Texts_Reader *R, void **R__typ);
export void Texts_Recall (Texts_Buffer *B);
export void Texts_Save (Texts_Text T, INTEGER beg, INTEGER end, Texts_Buffer B);
export void Texts_Scan (Texts_Scanner *S, void **S__typ);
export void Texts_SetColor (Texts_Writer *W, void **W__typ, BYTE col);
export void Texts_SetFont (Texts_Writer *W, void **W__typ, Texts_FontsFont fnt);
export void Texts_SetOffset (Texts_Writer *W, void **W__typ, BYTE voff);
static void Texts_Splice (Texts_Run un, Texts_Run v, Texts_Run w, Texts_Text base);
static void Texts_Split (INTEGER off, Texts_Run *u, Texts_Run *un);
export void Texts_Store (Files_Rider *r, void **r__typ, Texts_Text T);
export void Texts_Write (Texts_Writer *W, void **W__typ, CHAR ch);
export void Texts_WriteDate (Texts_Writer *W, void **W__typ, INTEGER t, INTEGER d);
export void Texts_WriteElem (Texts_Writer *W, void **W__typ, Texts_Elem e);
export void Texts_WriteHex (Texts_Writer *W, void **W__typ, INTEGER x);
export void Texts_WriteInt (Texts_Writer *W, void **W__typ, INTEGER x, INTEGER n);
export void Texts_WriteLn (Texts_Writer *W, void **W__typ);
export void Texts_WriteLongHex (Texts_Writer *W, void **W__typ, LONGINT x);
export void Texts_WriteLongInt (Texts_Writer *W, void **W__typ, LONGINT x, INTEGER n);
export void Texts_WriteLongReal (Texts_Writer *W, void **W__typ, REAL x, SHORTINT n);
export void Texts_WriteLongRealHex (Texts_Writer *W, void **W__typ, REAL x);
export void Texts_WriteReal (Texts_Writer *W, void **W__typ, SHORTREAL x, SHORTINT n);
export void Texts_WriteRealFix (Texts_Writer *W, void **W__typ, SHORTREAL x, SHORTINT n, SHORTINT k);
export void Texts_WriteRealHex (Texts_Writer *W, void **W__typ, SHORTREAL x);
export void Texts_WriteString (Texts_Writer *W, void **W__typ, CHAR *s, INTEGER s__len);


/*============================================================================*/

static Texts_FontsFont Texts_FontsThis (CHAR *name, INTEGER name__len)
{
  Texts_FontsFont F = NIL;
  __NEW(F, Texts_FontDesc);
  __STRCOPYCC(name, F->name, __MIN(32, name__len), (CHAR*)"Texts", 33563);
  return F;
}

static void Texts_Find (Texts_Text T, INTEGER *pos, Texts_Run *u, INTEGER *org, INTEGER *off)
{
  Texts_Run v = NIL;
  INTEGER m;
  if (*pos >= T->len) {
    *pos = T->len;
    *u = T->head;
    *org = T->len;
    *off = 0;
    T->cache = T->head;
    T->corg = 0;
  } else {
    v = T->cache->next;
    m = *pos - T->corg;
    if (*pos >= T->corg) {
      while (m >= v->len) {
        m -= v->len;
        v = v->next;
      }
    } else {
      while (m < 0) {
        v = v->prev;
        m += v->len;
      }
    }
    *u = v;
    *org = *pos - m;
    *off = m;
    T->cache = v->prev;
    T->corg = *org;
  }
}

static void Texts_Split (INTEGER off, Texts_Run *u, Texts_Run *un)
{
  Texts_Piece p = NIL;
  Texts_Piece U = NIL;
  if (off == 0) {
    *un = *u;
    *u = (*un)->prev;
  } else if (off >= (*u)->len) {
    *un = (*u)->next;
  } else {
    __NEW(p, Texts_PieceDesc);
    *un = (Texts_Run)p;
    U = __GUARDP(*u, Texts_PieceDesc, 1);
    __GUARDEQP(p, Texts_PieceDesc) = *U;
    p->org += off;
    p->len -= off;
    U->len -= p->len;
    p->ascii = (*u)->ascii;
    p->prev = (Texts_Run)U;
    p->next = U->next;
    p->next->prev = (Texts_Run)p;
    U->next = (Texts_Run)p;
  }
}

static void Texts_Merge (Texts_Text T, Texts_Run u, Texts_Run *v)
{
  Texts_Piece p = NIL;
  Texts_Piece q = NIL;
  if (((((__ISP(u, Texts_PieceDesc, 1) && __ISP(*v, Texts_PieceDesc, 1)) && __STRCMPCC(u->fnt->name, (*v)->fnt->name, 32, (CHAR*)"Texts", 44543) == 0) && (INTEGER)u->col == (INTEGER)(*v)->col) && (INTEGER)u->voff == (INTEGER)(*v)->voff) && (__GUARDP(u, Texts_PieceDesc, 1))->ascii == (__GUARDP(*v, Texts_PieceDesc, 1))->ascii) {
    p = __GUARDP(u, Texts_PieceDesc, 1);
    q = __GUARDP(*v, Texts_PieceDesc, 1);
    if (p->file == q->file && p->org + p->len == q->org) {
      if (T->cache == u) {
        T->corg += q->len;
      } else if (T->cache == *v) {
        T->cache = T->head;
        T->corg = 0;
      }
      p->len += q->len;
      *v = (*v)->next;
    }
  }
}

static void Texts_Splice (Texts_Run un, Texts_Run v, Texts_Run w, Texts_Text base)
{
  Texts_Run u = NIL;
  if (v != w->next) {
    u = un->prev;
    u->next = v;
    v->prev = u;
    un->prev = w;
    w->next = un;
    do {
      if (__ISP(v, Texts_ElemDesc, 1)) {
        (__GUARDP(v, Texts_ElemDesc, 1))->base = base;
      }
      v = v->next;
    } while (!(v == un));
  }
}

static Texts_Piece Texts_ClonePiece (Texts_Piece p)
{
  Texts_Piece q = NIL;
  __NEW(q, Texts_PieceDesc);
  __GUARDEQP(q, Texts_PieceDesc) = *p;
  return q;
}

static Texts_Elem Texts_CloneElem (Texts_Elem e)
{
  Texts_CopyMsg msg = {0};
  msg.e = NIL;
  (*e->handle)(e, (void*)&msg, Texts_CopyMsg__typ);
  return msg.e;
}

void Texts_CopyElem (Texts_Elem SE, Texts_Elem DE)
{
  DE->len = SE->len;
  DE->fnt = SE->fnt;
  DE->col = SE->col;
  DE->voff = SE->voff;
  DE->W = SE->W;
  DE->H = SE->H;
  DE->handle = SE->handle;
}

/*----------------------------------------------------------------------------*/
Texts_Text Texts_ElemBase (Texts_Elem E)
{
  return E->base;
}

/*----------------------------------------------------------------------------*/
INTEGER Texts_ElemPos (Texts_Elem E)
{
  Texts_Run u = NIL;
  INTEGER pos;
  u = E->base->head->next;
  pos = 0;
  while (u != (void *) E) {
    pos = pos + u->len;
    u = u->next;
  }
  return pos;
}

/*----------------------------------------------------------------------------*/
static void Texts_HandleAlien (Texts_Elem E, Texts_ElemMsg *msg, void **msg__typ)
{
  Texts_Alien e = NIL;
  Files_Rider r = {0};
  INTEGER i;
  CHAR ch;
  if (__ISP(E, Texts_Alien__rec, 2)) {
    if (__IS(msg__typ, Texts_CopyMsg, 1)) {
      if (__IS(msg__typ, Texts_CopyMsg, 1)) {
        Texts_CopyMsg *msg__ = (void*)msg;
        __NEW(e, Texts_Alien__rec);
        Texts_CopyElem((void*)((Texts_Alien)E), (void*)e);
        e->file = ((Texts_Alien)E)->file;
        e->org = ((Texts_Alien)E)->org;
        e->span = ((Texts_Alien)E)->span;
        __MOVE(((Texts_Alien)E)->mod, e->mod, 32);
        __MOVE(((Texts_Alien)E)->proc, e->proc, 32);
        (*msg__).e = (Texts_Elem)e;
      } else __WITHCHK((CHAR*)"Texts", 57855);
    } else if (__IS(msg__typ, Texts_IdentifyMsg, 1)) {
      if (__IS(msg__typ, Texts_IdentifyMsg, 1)) {
        Texts_IdentifyMsg *msg__ = (void*)msg;
        __STRCOPYCC(((Texts_Alien)E)->mod, (*msg__).mod, 32, (CHAR*)"Texts", 58651);
        __STRCOPYCC(((Texts_Alien)E)->proc, (*msg__).proc, 32, (CHAR*)"Texts", 58672);
        (*msg__).mod[31] = 0x01;
      } else __WITHCHK((CHAR*)"Texts", 58879);
    } else if (__IS(msg__typ, Texts_FileMsg, 1)) {
      if (__IS(msg__typ, Texts_FileMsg, 1)) {
        Texts_FileMsg *msg__ = (void*)msg;
        if ((INTEGER)(*msg__).id == 1) {
          Files_Set(&r, Files_Rider__typ, ((Texts_Alien)E)->file, ((Texts_Alien)E)->org);
          i = ((Texts_Alien)E)->span;
          while (i > 0) {
            Files_ReadChar(&r, Files_Rider__typ, &ch);
            Files_WriteChar(&(*msg__).r, Files_Rider__typ, ch);
            i -= 1;
          }
        }
      } else __WITHCHK((CHAR*)"Texts", 59988);
    }
  } else __WITHCHK((CHAR*)"Texts", 59988);
}

void Texts_OpenBuf (Texts_Buffer B)
{
  Texts_Run u = NIL;
  __NEW(u, Texts_RunDesc);
  u->next = u;
  u->prev = u;
  B->head = u;
  B->len = 0;
}

/*----------------------------------------------------------------------------*/
void Texts_Copy (Texts_Buffer SB, Texts_Buffer DB)
{
  Texts_Run u = NIL;
  Texts_Run v = NIL;
  Texts_Run vn = NIL;
  u = SB->head->next;
  v = DB->head->prev;
  while (u != SB->head) {
    if (__ISP(u, Texts_PieceDesc, 1)) {
      vn = (Texts_Run)Texts_ClonePiece(__GUARDP(u, Texts_PieceDesc, 1));
    } else {
      vn = (Texts_Run)Texts_CloneElem(__GUARDP(u, Texts_ElemDesc, 1));
    }
    v->next = vn;
    vn->prev = v;
    v = vn;
    u = u->next;
  }
  v->next = DB->head;
  DB->head->prev = v;
  DB->len += SB->len;
}

/*----------------------------------------------------------------------------*/
void Texts_Recall (Texts_Buffer *B)
{
  *B = Texts_del;
  Texts_del = NIL;
}

/*----------------------------------------------------------------------------*/
void Texts_Save (Texts_Text T, INTEGER beg, INTEGER end, Texts_Buffer B)
{
  Texts_Run u = NIL;
  Texts_Run v = NIL;
  Texts_Run w = NIL;
  Texts_Run wn = NIL;
  INTEGER uo, ud, vo, vd;
  Texts_Find(T, &beg, &u, &uo, &ud);
  Texts_Find(T, &end, &v, &vo, &vd);
  w = B->head->prev;
  while (u != v) {
    if (__ISP(u, Texts_PieceDesc, 1)) {
      wn = (Texts_Run)Texts_ClonePiece(__GUARDP(u, Texts_PieceDesc, 1));
      wn->len -= ud;
      (__GUARDP(wn, Texts_PieceDesc, 1))->org += ud;
    } else {
      wn = (Texts_Run)Texts_CloneElem(__GUARDP(u, Texts_ElemDesc, 1));
    }
    w->next = wn;
    wn->prev = w;
    w = wn;
    u = u->next;
    ud = 0;
  }
  if (vd > 0) {
    wn = (Texts_Run)Texts_ClonePiece(__GUARDP(v, Texts_PieceDesc, 1));
    wn->len = vd - ud;
    (__GUARDP(wn, Texts_PieceDesc, 1))->org += ud;
    w->next = wn;
    wn->prev = w;
    w = wn;
  }
  w->next = B->head;
  B->head->prev = w;
  B->len += end - beg;
}

/*----------------------------------------------------------------------------*/
void Texts_Insert (Texts_Text T, INTEGER pos, Texts_Buffer B)
{
  Texts_Run u = NIL;
  Texts_Run un = NIL;
  Texts_Run v = NIL;
  Texts_Piece p = NIL;
  Texts_Piece q = NIL;
  INTEGER uo, ud, len;
  Texts_Find(T, &pos, &u, &uo, &ud);
  Texts_Split(ud, &u, &un);
  len = B->len;
  v = B->head->next;
  Texts_Merge(T, u, &v);
  Texts_Splice(un, v, B->head->prev, T);
  T->len += len;
  B->head->next = B->head;
  B->head->prev = B->head;
  B->len = 0;
  if (T->notify != NIL) {
    (*T->notify)(T, 1, pos, pos + len);
  }
}

/*----------------------------------------------------------------------------*/
void Texts_Append (Texts_Text T, Texts_Buffer B)
{
  Texts_Run v = NIL;
  INTEGER pos, len;
  pos = T->len;
  len = B->len;
  v = B->head->next;
  Texts_Merge(T, T->head->prev, &v);
  Texts_Splice(T->head, v, B->head->prev, T);
  T->len += len;
  B->head->next = B->head;
  B->head->prev = B->head;
  B->len = 0;
  if (T->notify != NIL) {
    (*T->notify)(T, 1, pos, pos + len);
  }
}

/*----------------------------------------------------------------------------*/
void Texts_Delete (Texts_Text T, INTEGER beg, INTEGER end)
{
  Texts_Run c = NIL;
  Texts_Run u = NIL;
  Texts_Run un = NIL;
  Texts_Run v = NIL;
  Texts_Run vn = NIL;
  INTEGER co, uo, ud, vo, vd;
  Texts_Find(T, &beg, &u, &uo, &ud);
  Texts_Split(ud, &u, &un);
  c = T->cache;
  co = T->corg;
  Texts_Find(T, &end, &v, &vo, &vd);
  Texts_Split(vd, &v, &vn);
  T->cache = c;
  T->corg = co;
  __NEW(Texts_del, Texts_BufDesc);
  Texts_OpenBuf(Texts_del);
  Texts_del->len = end - beg;
  Texts_Splice(Texts_del->head, un, v, NIL);
  Texts_Merge(T, u, &vn);
  u->next = vn;
  vn->prev = u;
  T->len -= end - beg;
  if (T->notify != NIL) {
    (*T->notify)(T, 2, beg, end);
  }
}

/*----------------------------------------------------------------------------*/
void Texts_ChangeLooks (Texts_Text T, INTEGER beg, INTEGER end, SET sel, Texts_FontsFont fnt, BYTE col, BYTE voff)
{
  Texts_Run c = NIL;
  Texts_Run u = NIL;
  Texts_Run un = NIL;
  Texts_Run v = NIL;
  Texts_Run vn = NIL;
  INTEGER co, uo, ud, vo, vd;
  Texts_Find(T, &beg, &u, &uo, &ud);
  Texts_Split(ud, &u, &un);
  c = T->cache;
  co = T->corg;
  Texts_Find(T, &end, &v, &vo, &vd);
  Texts_Split(vd, &v, &vn);
  T->cache = c;
  T->corg = co;
  while (un != vn) {
    if (__IN(0, sel) && fnt != NIL) {
      un->fnt = fnt;
    }
    if (__IN(1, sel)) {
      un->col = col;
    }
    if (__IN(2, sel)) {
      un->voff = voff;
    }
    Texts_Merge(T, u, &un);
    if (u->next == un) {
      u = un;
      un = un->next;
    } else {
      u->next = un;
      un->prev = u;
    }
  }
  Texts_Merge(T, u, &un);
  u->next = un;
  un->prev = u;
  if (T->notify != NIL) {
    (*T->notify)(T, 0, beg, end);
  }
}

/*----------------------------------------------------------------------------*/
void Texts_OpenReader (Texts_Reader *R, void **R__typ, Texts_Text T, INTEGER pos)
{
  Texts_Run u = NIL;
  if (pos >= T->len) {
    pos = T->len;
  } else if (pos < 0) {
    pos = 0;
  }
  Texts_Find(T, &pos, &u, &(*R).org, &(*R).off);
  (*R).run = u;
  (*R).eot = 0;
  if (__ISP(u, Texts_PieceDesc, 1)) {
    Files_Set(&(*R).rider, Files_Rider__typ, (__GUARDP(u, Texts_PieceDesc, 1))->file, (__GUARDP(u, Texts_PieceDesc, 1))->org + (*R).off);
  }
}

/*----------------------------------------------------------------------------*/
void Texts_Read (Texts_Reader *R, void **R__typ, CHAR *ch)
{
  Texts_Run u = NIL;
  INTEGER pos;
  CHAR nextch;
  u = (*R).run;
  (*R).fnt = u->fnt;
  (*R).col = u->col;
  (*R).voff = u->voff;
  (*R).off += 1;
  if (__ISP(u, Texts_PieceDesc, 1)) {
    Files_ReadChar(&(*R).rider, Files_Rider__typ, ch);
    (*R).elem = NIL;
    if (*ch == 0x0a && (__GUARDP(u, Texts_PieceDesc, 1))->ascii) {
      *ch = 0x0d;
    } else if (*ch == 0x0d && (__GUARDP(u, Texts_PieceDesc, 1))->ascii) {
      pos = (INTEGER)Files_Pos(&(*R).rider, Files_Rider__typ);
      Files_ReadChar(&(*R).rider, Files_Rider__typ, &nextch);
      if (nextch == 0x0a) {
        (*R).off += 1;
      } else {
        Files_Set(&(*R).rider, Files_Rider__typ, (__GUARDP(u, Texts_PieceDesc, 1))->file, pos);
      }
    }
  } else if (__ISP(u, Texts_ElemDesc, 1)) {
    *ch = 0x1c;
    (*R).elem = __GUARDP(u, Texts_ElemDesc, 1);
  } else {
    *ch = 0x00;
    (*R).elem = NIL;
    (*R).eot = 1;
  }
  if ((*R).off == u->len) {
    (*R).org += u->len;
    u = u->next;
    if (__ISP(u, Texts_PieceDesc, 1)) {
      if (__ISP(u, Texts_PieceDesc, 1)) {
        Files_Set(&(*R).rider, Files_Rider__typ, ((Texts_Piece)u)->file, ((Texts_Piece)u)->org);
      } else __WITHCHK((CHAR*)"Texts", 90938);
    }
    (*R).run = u;
    (*R).off = 0;
  }
}

/*----------------------------------------------------------------------------*/
BOOLEAN Texts_ReadLong (Texts_Reader *R, void **R__typ, LONGCHAR *longch)
{
  CHAR ch;
  INTEGER val;
  Texts_Read(R, R__typ, &ch);
  if (ch < 0x80) {
    *longch = ch;
  } else if (ch < 0xe0) {
    val = (INTEGER)ch - 192;
    if (val < 0) {
      return 0;
    }
    Texts_Read(R, R__typ, &ch);
    val = (__ASHL(val, 6, INTEGER) + (INTEGER)ch) - 128;
    if (ch < 0x80 || ch >= 0xe0) {
      return 0;
    }
    *longch = (LONGCHAR)val;
  } else if (ch < 0xf0) {
    val = (INTEGER)ch - 224;
    Texts_Read(R, R__typ, &ch);
    val = (__ASHL(val, 6, INTEGER) + (INTEGER)ch) - 128;
    if (ch < 0x80 || ch >= 0xe0) {
      return 0;
    }
    Texts_Read(R, R__typ, &ch);
    val = (__ASHL(val, 6, INTEGER) + (INTEGER)ch) - 128;
    if (ch < 0x80 || ch >= 0xe0) {
      return 0;
    }
    *longch = (LONGCHAR)val;
  } else {
    return 0;
  }
  return 1;
}

/*----------------------------------------------------------------------------*/
void Texts_ReadElem (Texts_Reader *R, void **R__typ)
{
  Texts_Run u = NIL;
  Texts_Run un = NIL;
  u = (*R).run;
  while (__ISP(u, Texts_PieceDesc, 1)) {
    (*R).org += u->len;
    u = u->next;
  }
  if (__ISP(u, Texts_ElemDesc, 1)) {
    un = u->next;
    (*R).run = un;
    (*R).org += 1;
    (*R).off = 0;
    (*R).fnt = u->fnt;
    (*R).col = u->col;
    (*R).voff = u->voff;
    (*R).elem = __GUARDP(u, Texts_ElemDesc, 1);
    if (__ISP(un, Texts_PieceDesc, 1)) {
      if (__ISP(un, Texts_PieceDesc, 1)) {
        Files_Set(&(*R).rider, Files_Rider__typ, ((Texts_Piece)un)->file, ((Texts_Piece)un)->org);
      } else __WITHCHK((CHAR*)"Texts", 100413);
    }
  } else {
    (*R).eot = 1;
    (*R).elem = NIL;
  }
}

/*----------------------------------------------------------------------------*/
void Texts_ReadPrevElem (Texts_Reader *R, void **R__typ)
{
  Texts_Run u = NIL;
  u = (*R).run->prev;
  while (__ISP(u, Texts_PieceDesc, 1)) {
    (*R).org -= u->len;
    u = u->prev;
  }
  if (__ISP(u, Texts_ElemDesc, 1)) {
    (*R).run = u;
    (*R).org -= 1;
    (*R).off = 0;
    (*R).fnt = u->fnt;
    (*R).col = u->col;
    (*R).voff = u->voff;
    (*R).elem = __GUARDP(u, Texts_ElemDesc, 1);
  } else {
    (*R).eot = 1;
    (*R).elem = NIL;
  }
}

/*----------------------------------------------------------------------------*/
INTEGER Texts_Pos (Texts_Reader *R, void **R__typ)
{
  return (*R).org + (*R).off;
}

/*----------------------------------------------------------------------------*/
void Texts_OpenScanner (Texts_Scanner *S, void **S__typ, Texts_Text T, INTEGER pos)
{
  Texts_OpenReader((void*)S, S__typ, T, pos);
  (*S).line = 0;
  (*S).nextCh = ' ';
}

/*----------------------------------------------------------------------------*/
static struct Scan__32 {
  Texts_Scanner *S;
  void **S__typ;
  CHAR *ch;
  BOOLEAN *negE;
  SHORTINT *e;
  struct Scan__32 *lnk;
} *Scan__32_s;

static void __33 (void);

static void __33 (void)
{
  Texts_Read((void*)Scan__32_s->S, Scan__32_s->S__typ, &(*Scan__32_s->ch));
  if ((*Scan__32_s->ch) == '-') {
    (*Scan__32_s->negE) = 1;
    Texts_Read((void*)Scan__32_s->S, Scan__32_s->S__typ, &(*Scan__32_s->ch));
  } else {
    (*Scan__32_s->negE) = 0;
    if ((*Scan__32_s->ch) == '+') {
      Texts_Read((void*)Scan__32_s->S, Scan__32_s->S__typ, &(*Scan__32_s->ch));
    }
  }
  while ('0' <= (*Scan__32_s->ch) && (*Scan__32_s->ch) <= '9') {
    (*Scan__32_s->e) = (SHORTINT)(((INTEGER)(*Scan__32_s->e) * 10 + (INTEGER)(*Scan__32_s->ch)) - 48);
    Texts_Read((void*)Scan__32_s->S, Scan__32_s->S__typ, &(*Scan__32_s->ch));
  }
}

void Texts_Scan (Texts_Scanner *S, void **S__typ)
{
  CHAR ch, term;
  BOOLEAN neg, negE, hex;
  BYTE i, j, h;
  SHORTINT e;
  INTEGER k;
  SHORTREAL x, f;
  REAL y, g;
  CHAR d[32];
  struct Scan__32 _s;
  _s.S = S; _s.S__typ = S__typ;
  _s.ch = &ch;
  _s.negE = &negE;
  _s.e = &e;
  _s.lnk = Scan__32_s;
  Scan__32_s = &_s;
  ch = (*S).nextCh;
  i = 0;
  for (;;) {
    if (ch == 0x0d) {
      (*S).line += 1;
    } else if (ch != ' ' && ch != 0x09) {
      break;
    }
    Texts_Read((void*)S, S__typ, &ch);
  }
  if ((('A' <= __CAP(ch) && __CAP(ch) <= 'Z') || ch == '/') || ch == '.') {
    do {
      (*S).s[__X(i, 64, (CHAR*)"Texts", 115481)] = ch;
      i += 1;
      Texts_Read((void*)S, S__typ, &ch);
    } while (!((((__CAP(ch) > 'Z' && ch != '_') || ('A' > __CAP(ch) && ch > '9')) || (('0' > ch && ch != '.') && ch != '/')) || (INTEGER)i == 63));
    (*S).s[__X(i, 64, (CHAR*)"Texts", 116754)] = 0x00;
    (*S).len = i;
    (*S).class = 1;
  } else if (ch == '\"') {
    Texts_Read((void*)S, S__typ, &ch);
    while ((ch != '\"' && ch >= ' ') && (INTEGER)i != 63) {
      (*S).s[__X(i, 64, (CHAR*)"Texts", 117780)] = ch;
      i += 1;
      Texts_Read((void*)S, S__typ, &ch);
    }
    (*S).s[__X(i, 64, (CHAR*)"Texts", 118290)] = 0x00;
    (*S).len = (BYTE)((INTEGER)i + 1);
    Texts_Read((void*)S, S__typ, &ch);
    (*S).class = 2;
  } else {
    if (ch == '-') {
      neg = 1;
      Texts_Read((void*)S, S__typ, &ch);
    } else {
      neg = 0;
    }
    if ('0' <= ch && ch <= '9') {
      hex = 0;
      j = 0;
      for (;;) {
        d[__X(i, 32, (CHAR*)"Texts", 119575)] = ch;
        i += 1;
        Texts_Read((void*)S, S__typ, &ch);
        if (ch < '0') {
          break;
        }
        if ('9' < ch) {
          if ('A' <= ch && ch <= 'F') {
            hex = 1;
            ch = (CHAR)((INTEGER)ch - 7);
          } else if ('a' <= ch && ch <= 'f') {
            hex = 1;
            ch = (CHAR)((INTEGER)ch - 39);
          } else {
            break;
          }
        }
      }
      if (ch == 'H') {
        Texts_Read((void*)S, S__typ, &ch);
        (*S).class = 3;
        if ((INTEGER)i - (INTEGER)j > 8) {
          j = (BYTE)((INTEGER)i - 8);
        }
        k = (INTEGER)d[__X(j, 32, (CHAR*)"Texts", 122654)] - 48;
        j += 1;
        if ((INTEGER)i - (INTEGER)j == 7 && k >= 8) {
          k -= 16;
        }
        while ((INTEGER)j < (INTEGER)i) {
          k = __ASHL(k, 4, INTEGER) + ((INTEGER)d[__X(j, 32, (CHAR*)"Texts", 123191)] - 48);
          j += 1;
        }
        if (neg) {
          (*S).i = -k;
        } else {
          (*S).i = k;
        }
      } else if (ch == '.') {
        Texts_Read((void*)S, S__typ, &ch);
        h = i;
        while ('0' <= ch && ch <= '9') {
          d[__X(i, 32, (CHAR*)"Texts", 124215)] = ch;
          i += 1;
          Texts_Read((void*)S, S__typ, &ch);
        }
        if (ch == 'D') {
          e = 0;
          y = (REAL)0;
          g = (REAL)1;
          do {
            y = y * (REAL)10 + (REAL)((INTEGER)d[__X(j, 32, (CHAR*)"Texts", 124976)] - 48);
            j += 1;
          } while (!((INTEGER)j == (INTEGER)h));
          while ((INTEGER)j < (INTEGER)i) {
            g = g / (REAL)(REAL)10;
            y = (REAL)((INTEGER)d[__X(j, 32, (CHAR*)"Texts", 125250)] - 48) * g + y;
            j += 1;
          }
          __33();
          if (negE) {
            if ((INTEGER)e <= 308) {
              y = y / (REAL)Reals_TenL(e);
            } else {
              y = (REAL)0;
            }
          } else if ((INTEGER)e > 0) {
            if ((INTEGER)e <= 308) {
              y = Reals_TenL(e) * y;
            } else {
              __HALT(40, (CHAR*)"Texts", 126531);
            }
          }
          if (neg) {
            y = -y;
          }
          (*S).class = 5;
          (*S).y = y;
        } else {
          e = 0;
          x = (SHORTREAL)0;
          f = (SHORTREAL)1;
          do {
            x = x * (SHORTREAL)10 + (SHORTREAL)((INTEGER)d[__X(j, 32, (CHAR*)"Texts", 127792)] - 48);
            j += 1;
          } while (!((INTEGER)j == (INTEGER)h));
          while ((INTEGER)j < (INTEGER)i) {
            f = f / (SHORTREAL)(SHORTREAL)10;
            x = (SHORTREAL)((INTEGER)d[__X(j, 32, (CHAR*)"Texts", 128064)] - 48) * f + x;
            j += 1;
          }
          if (ch == 'E') {
            __33();
          }
          if (negE) {
            if ((INTEGER)e <= 38) {
              x = x / (SHORTREAL)Reals_Ten(e);
            } else {
              x = (SHORTREAL)0;
            }
          } else if ((INTEGER)e > 0) {
            if ((INTEGER)e <= 38) {
              x = Reals_Ten(e) * x;
            } else {
              __HALT(40, (CHAR*)"Texts", 129345);
            }
          }
          if (neg) {
            x = -x;
          }
          (*S).class = 4;
          (*S).x = x;
        }
        if (hex) {
          (*S).class = 0;
        }
      } else {
        (*S).class = 3;
        k = 0;
        do {
          k = k * 10 + ((INTEGER)d[__X(j, 32, (CHAR*)"Texts", 131374)] - 48);
          j += 1;
        } while (!((INTEGER)j == (INTEGER)i));
        if (neg) {
          (*S).i = -k;
        } else {
          (*S).i = k;
        }
        if (hex) {
          (*S).class = 0;
        } else {
          (*S).class = 3;
        }
      }
    } else {
      (*S).class = 6;
      if (neg) {
        (*S).c = '-';
      } else {
        (*S).c = ch;
        Texts_Read((void*)S, S__typ, &ch);
      }
    }
  }
  (*S).nextCh = ch;
  Scan__32_s = _s.lnk;
}

/*----------------------------------------------------------------------------*/
void Texts_OpenWriter (Texts_Writer *W, void **W__typ)
{
  __NEW((*W).buf, Texts_BufDesc);
  Texts_OpenBuf((*W).buf);
  (*W).fnt = Texts_FontsDefault;
  (*W).col = 15;
  (*W).voff = 0;
  (*W).file = Files_New((CHAR*)"", 1);
  Files_Set(&(*W).rider, Files_Rider__typ, (*W).file, 0);
}

/*----------------------------------------------------------------------------*/
void Texts_SetFont (Texts_Writer *W, void **W__typ, Texts_FontsFont fnt)
{
  (*W).fnt = fnt;
}

/*----------------------------------------------------------------------------*/
void Texts_SetColor (Texts_Writer *W, void **W__typ, BYTE col)
{
  (*W).col = col;
}

/*----------------------------------------------------------------------------*/
void Texts_SetOffset (Texts_Writer *W, void **W__typ, BYTE voff)
{
  (*W).voff = voff;
}

/*----------------------------------------------------------------------------*/
void Texts_Write (Texts_Writer *W, void **W__typ, CHAR ch)
{
  Texts_Run u = NIL;
  Texts_Run un = NIL;
  Texts_Piece p = NIL;
  Files_WriteChar(&(*W).rider, Files_Rider__typ, ch);
  (*W).buf->len += 1;
  un = (*W).buf->head;
  u = un->prev;
  if (((((__ISP(u, Texts_PieceDesc, 1) && (__GUARDP(u, Texts_PieceDesc, 1))->file == (*W).file) && __STRCMPCC(u->fnt->name, (*W).fnt->name, 32, (CHAR*)"Texts", 142335) == 0) && (INTEGER)u->col == (INTEGER)(*W).col) && (INTEGER)u->voff == (INTEGER)(*W).voff) && !(__GUARDP(u, Texts_PieceDesc, 1))->ascii) {
    u->len += 1;
  } else {
    __NEW(p, Texts_PieceDesc);
    u->next = (Texts_Run)p;
    p->prev = u;
    p->next = un;
    un->prev = (Texts_Run)p;
    p->len = 1;
    p->fnt = (*W).fnt;
    p->col = (*W).col;
    p->voff = (*W).voff;
    p->file = (*W).file;
    p->org = (INTEGER)Files_Length((*W).file) - 1;
    p->ascii = 0;
  }
}

/*----------------------------------------------------------------------------*/
void Texts_WriteElem (Texts_Writer *W, void **W__typ, Texts_Elem e)
{
  Texts_Run u = NIL;
  Texts_Run un = NIL;
  if (e->base != NIL) {
    __HALT(99, (CHAR*)"Texts", 143649);
  }
  (*W).buf->len += 1;
  e->len = 1;
  e->fnt = (*W).fnt;
  e->col = (*W).col;
  e->voff = (*W).voff;
  un = (*W).buf->head;
  u = un->prev;
  u->next = (Texts_Run)e;
  e->prev = u;
  e->next = un;
  un->prev = (Texts_Run)e;
}

/*----------------------------------------------------------------------------*/
void Texts_WriteLn (Texts_Writer *W, void **W__typ)
{
  Texts_Write(W, W__typ, 0x0d);
}

/*----------------------------------------------------------------------------*/
void Texts_WriteString (Texts_Writer *W, void **W__typ, CHAR *s, INTEGER s__len)
{
  SHORTINT i;
  i = 0;
  while (s[__X(i, s__len, (CHAR*)"Texts", 146709)] >= ' ') {
    Texts_Write(W, W__typ, s[__X(i, s__len, (CHAR*)"Texts", 146727)]);
    i += 1;
  }
}

/*----------------------------------------------------------------------------*/
void Texts_WriteInt (Texts_Writer *W, void **W__typ, INTEGER x, INTEGER n)
{
  SHORTINT i;
  INTEGER x0;
  CHAR a[22];
  i = 0;
  if (x < 0) {
    if (x == (-2147483647-1)) {
      Texts_WriteString(W, W__typ, (CHAR*)" -2147483648", 13);
      return;
    } else {
      n -= 1;
      x0 = -x;
    }
  } else {
    x0 = x;
  }
  do {
    a[__X(i, 22, (CHAR*)"Texts", 152105)] = (CHAR)(__MOD(x0, 10) + 48);
    x0 = __DIV(x0, 10);
    i += 1;
  } while (!(x0 == 0));
  while (n > (INTEGER)i) {
    Texts_Write(W, W__typ, ' ');
    n -= 1;
  }
  if (x < 0) {
    Texts_Write(W, W__typ, '-');
  }
  do {
    i -= 1;
    Texts_Write(W, W__typ, a[__X(i, 22, (CHAR*)"Texts", 153121)]);
  } while (!((INTEGER)i == 0));
}

/*----------------------------------------------------------------------------*/
void Texts_WriteLongInt (Texts_Writer *W, void **W__typ, LONGINT x, INTEGER n)
{
  INTEGER i;
  LONGINT x0;
  CHAR a[22];
  i = 0;
  if (x < 0) {
    if (x == (-9223372036854775807LL-1)) {
      Texts_WriteString(W, W__typ, (CHAR*)" -9223372036854775808", 22);
      return;
    } else {
      n -= 1;
      x0 = -x;
    }
  } else {
    x0 = x;
  }
  do {
    a[__X(i, 22, (CHAR*)"Texts", 158505)] = (CHAR)(__MOD(x0, 10) + 48);
    x0 = __DIV(x0, 10);
    i += 1;
  } while (!(x0 == 0));
  while (n > i) {
    Texts_Write(W, W__typ, ' ');
    n -= 1;
  }
  if (x < 0) {
    Texts_Write(W, W__typ, '-');
  }
  do {
    i -= 1;
    Texts_Write(W, W__typ, a[__X(i, 22, (CHAR*)"Texts", 159521)]);
  } while (!(i == 0));
}

/*----------------------------------------------------------------------------*/
void Texts_WriteHex (Texts_Writer *W, void **W__typ, INTEGER x)
{
  SHORTINT i;
  INTEGER y;
  CHAR a[8];
  i = 0;
  Texts_Write(W, W__typ, ' ');
  do {
    y = __MASK(x, -16);
    if (y < 10) {
      a[__X(i, 8, (CHAR*)"Texts", 161584)] = (CHAR)(y + 48);
    } else {
      a[__X(i, 8, (CHAR*)"Texts", 161617)] = (CHAR)(y + 55);
    }
    x = __ASHR(x, 4, INTEGER);
    i += 1;
  } while (!((INTEGER)i == 8));
  do {
    i -= 1;
    Texts_Write(W, W__typ, a[__X(i, 8, (CHAR*)"Texts", 162337)]);
  } while (!((INTEGER)i == 0));
}

/*----------------------------------------------------------------------------*/
void Texts_WriteLongHex (Texts_Writer *W, void **W__typ, LONGINT x)
{
  SHORTINT i;
  INTEGER y;
  CHAR a[16];
  i = 0;
  Texts_Write(W, W__typ, ' ');
  do {
    y = __MASK((INTEGER)x, -16);
    if (y < 10) {
      a[__X(i, 16, (CHAR*)"Texts", 164400)] = (CHAR)(y + 48);
    } else {
      a[__X(i, 16, (CHAR*)"Texts", 164433)] = (CHAR)(y + 55);
    }
    x = __ASHR(x, 4, LONGINT);
    i += 1;
  } while (!((INTEGER)i == 16));
  do {
    i -= 1;
    Texts_Write(W, W__typ, a[__X(i, 16, (CHAR*)"Texts", 165153)]);
  } while (!((INTEGER)i == 0));
}

/*----------------------------------------------------------------------------*/
void Texts_WriteReal (Texts_Writer *W, void **W__typ, SHORTREAL x, SHORTINT n)
{
  SHORTINT e;
  SHORTREAL x0;
  CHAR d[9];
  e = Reals_Expo(x);
  if ((INTEGER)e == 0) {
    Texts_WriteString(W, W__typ, (CHAR*)"0.0", 4);
    do {
      n -= 1;
    } while (!((INTEGER)n <= 3));
  } else if ((INTEGER)e == 255) {
    Texts_WriteString(W, W__typ, (CHAR*)"NaN", 4);
  } else {
    if ((INTEGER)n <= 9) {
      n = 3;
    } else {
      n -= 6;
    }
    do {
      n -= 1;
    } while (!((INTEGER)n <= 8));
    if (x < (SHORTREAL)0) {
      Texts_Write(W, W__typ, '-');
      x = -x;
    }
    e = (SHORTINT)__ASHR(((INTEGER)e - 127) * 77, 8, INTEGER);
    if ((INTEGER)e >= 0) {
      x = x / (SHORTREAL)Reals_Ten(e);
    } else {
      x = Reals_Ten((SHORTINT)(-((INTEGER)e))) * x;
    }
    if (x >= (SHORTREAL)10) {
      x = 0.1 * x;
      e += 1;
    }
    x0 = Reals_Ten((SHORTINT)((INTEGER)n - 1));
    x = x0 * x + 0.5;
    if (x >= (SHORTREAL)10 * x0) {
      x = x * 0.1;
      e += 1;
    }
    Reals_Convert(x, n, (void*)d, 9);
    n -= 1;
    Texts_Write(W, W__typ, d[__X(n, 9, (CHAR*)"Texts", 171036)]);
    Texts_Write(W, W__typ, '.');
    do {
      n -= 1;
      Texts_Write(W, W__typ, d[__X(n, 9, (CHAR*)"Texts", 171299)]);
    } while (!((INTEGER)n == 0));
    Texts_Write(W, W__typ, 'E');
    if ((INTEGER)e >= 0) {
      Texts_Write(W, W__typ, '+');
    }
    Texts_WriteInt(W, W__typ, e, 0);
  }
}

/*----------------------------------------------------------------------------*/
static struct WriteRealFix__57 {
  Texts_Writer *W;
  void **W__typ;
  SHORTINT *i;
  CHAR (*d)[9];
  struct WriteRealFix__57 *lnk;
} *WriteRealFix__57_s;

static void __58 (SHORTINT n);
static void __60 (CHAR ch, SHORTINT n);

static void __60 (CHAR ch, SHORTINT n)
{
  while ((INTEGER)n > 0) {
    Texts_Write(WriteRealFix__57_s->W, WriteRealFix__57_s->W__typ, ch);
    n -= 1;
  }
}

static void __58 (SHORTINT n)
{
  while ((INTEGER)n > 0) {
    (*WriteRealFix__57_s->i) -= 1;
    Texts_Write(WriteRealFix__57_s->W, WriteRealFix__57_s->W__typ, ((*WriteRealFix__57_s->d))[__X((*WriteRealFix__57_s->i), 9, (CHAR*)"Texts", 175902)]);
    n -= 1;
  }
}

void Texts_WriteRealFix (Texts_Writer *W, void **W__typ, SHORTREAL x, SHORTINT n, SHORTINT k)
{
  SHORTINT e, i;
  CHAR sign;
  SHORTREAL x0;
  CHAR d[9];
  struct WriteRealFix__57 _s;
  _s.W = W; _s.W__typ = W__typ;
  _s.i = &i;
  _s.d = (void*)d;
  _s.lnk = WriteRealFix__57_s;
  WriteRealFix__57_s = &_s;
  e = Reals_Expo(x);
  if ((INTEGER)k < 0) {
    k = 0;
  }
  if ((INTEGER)e == 0) {
    __60(' ', (SHORTINT)(((INTEGER)n - (INTEGER)k) - 2));
    Texts_Write(W, W__typ, '0');
    __60(' ', (SHORTINT)((INTEGER)k + 1));
  } else if ((INTEGER)e == 255) {
    Texts_WriteString(W, W__typ, (CHAR*)" NaN", 5);
    __60(' ', (SHORTINT)((INTEGER)n - 4));
  } else {
    e = (SHORTINT)__ASHR(((INTEGER)e - 127) * 77, 8, INTEGER);
    if (x < (SHORTREAL)0) {
      sign = '-';
      x = -x;
    } else {
      sign = ' ';
    }
    if ((INTEGER)e >= 0) {
      x = x / (SHORTREAL)Reals_Ten(e);
    } else {
      x = Reals_Ten((SHORTINT)(-((INTEGER)e))) * x;
    }
    if (x >= (SHORTREAL)10) {
      x = 0.1 * x;
      e += 1;
    }
    if ((INTEGER)k + (INTEGER)e >= 8) {
      k = (SHORTINT)(8 - (INTEGER)e);
    } else if ((INTEGER)k + (INTEGER)e < 0) {
      k = (SHORTINT)(-((INTEGER)e));
      x = (REAL)0;
    }
    x0 = Reals_Ten((SHORTINT)((INTEGER)k + (INTEGER)e));
    x = x0 * x + 0.5;
    if (x >= (SHORTREAL)10 * x0) {
      e += 1;
    }
    e += 1;
    i = (SHORTINT)((INTEGER)k + (INTEGER)e);
    Reals_Convert(x, i, (void*)d, 9);
    if ((INTEGER)e > 0) {
      __60(' ', (SHORTINT)((((INTEGER)n - (INTEGER)e) - (INTEGER)k) - 2));
      Texts_Write(W, W__typ, sign);
      __58(e);
      Texts_Write(W, W__typ, '.');
      __58(k);
    } else {
      __60(' ', (SHORTINT)(((INTEGER)n - (INTEGER)k) - 3));
      Texts_Write(W, W__typ, sign);
      Texts_Write(W, W__typ, '0');
      Texts_Write(W, W__typ, '.');
      __60('0', (SHORTINT)(-((INTEGER)e)));
      __58((SHORTINT)((INTEGER)k + (INTEGER)e));
    }
  }
  WriteRealFix__57_s = _s.lnk;
}

/*----------------------------------------------------------------------------*/
void Texts_WriteRealHex (Texts_Writer *W, void **W__typ, SHORTREAL x)
{
  SHORTINT i;
  CHAR d[8];
  Reals_ConvertH(x, (void*)d, 8);
  i = 0;
  do {
    Texts_Write(W, W__typ, d[__X(i, 8, (CHAR*)"Texts", 185113)]);
    i += 1;
  } while (!((INTEGER)i == 8));
}

/*----------------------------------------------------------------------------*/
void Texts_WriteLongReal (Texts_Writer *W, void **W__typ, REAL x, SHORTINT n)
{
  CHAR ch;
  SHORTINT i;
  BOOLEAN dotzero;
  CHAR d[28];
  Reals_RealToStr(x, n, (void*)d, 28);
  i = 0;
  ch = d[0];
  dotzero = 1;
  while (ch != 0x00 && ch != 'E') {
    if (ch == '.' || ch > '9') {
      dotzero = 0;
    }
    Texts_Write(W, W__typ, ch);
    i += 1;
    ch = d[__X(i, 28, (CHAR*)"Texts", 188159)];
  }
  if (ch == 'E') {
    Texts_Write(W, W__typ, 'E');
    i += 1;
    ch = d[__X(i, 28, (CHAR*)"Texts", 188711)];
    if (ch == '+' || ch == '-') {
      Texts_Write(W, W__typ, ch);
      i += 1;
      ch = d[__X(i, 28, (CHAR*)"Texts", 188999)];
    }
    if (ch == '0') {
      i += 1;
      ch = d[__X(i, 28, (CHAR*)"Texts", 189225)];
      if (ch == '0') {
        i += 1;
        ch = d[__X(i, 28, (CHAR*)"Texts", 189483)];
      }
    }
    while (ch != 0x00) {
      Texts_Write(W, W__typ, ch);
      i += 1;
      ch = d[__X(i, 28, (CHAR*)"Texts", 190007)];
    }
  } else if (dotzero) {
    Texts_Write(W, W__typ, '.');
    Texts_Write(W, W__typ, '0');
  }
}

/*----------------------------------------------------------------------------*/
void Texts_WriteLongRealHex (Texts_Writer *W, void **W__typ, REAL x)
{
  SHORTINT i;
  CHAR d[16];
  Reals_ConvertHL(x, (void*)d, 16);
  i = 0;
  do {
    Texts_Write(W, W__typ, d[__X(i, 16, (CHAR*)"Texts", 192537)]);
    i += 1;
  } while (!((INTEGER)i == 16));
}

/*----------------------------------------------------------------------------*/
static struct WriteDate__45 {
  Texts_Writer *W;
  void **W__typ;
  struct WriteDate__45 *lnk;
} *WriteDate__45_s;

static void __46 (CHAR ch, INTEGER x);

static void __46 (CHAR ch, INTEGER x)
{
  Texts_Write(WriteDate__45_s->W, WriteDate__45_s->W__typ, ch);
  Texts_Write(WriteDate__45_s->W, WriteDate__45_s->W__typ, (CHAR)(__DIV(x, 10) + 48));
  Texts_Write(WriteDate__45_s->W, WriteDate__45_s->W__typ, (CHAR)(__MOD(x, 10) + 48));
}

void Texts_WriteDate (Texts_Writer *W, void **W__typ, INTEGER t, INTEGER d)
{
  struct WriteDate__45 _s;
  _s.W = W; _s.W__typ = W__typ;
  _s.lnk = WriteDate__45_s;
  WriteDate__45_s = &_s;
  __46(' ', __MASK(d, -32));
  __46('.', __MASK(__ASHR(d, 5, INTEGER), -16));
  __46('.', __MASK(__ASHR(d, 9, INTEGER), -128));
  __46(' ', __MASK(__ASHR(t, 12, INTEGER), -32));
  __46(':', __MASK(__ASHR(t, 6, INTEGER), -64));
  __46(':', __MASK(t, -64));
  WriteDate__45_s = _s.lnk;
}

/*----------------------------------------------------------------------------*/
static struct Load0__16 {
  Texts_Text *T;
  BYTE *ecnt;
  Files_File *f;
  Texts_FileMsg *msg;
  CHAR (*mods)[64][32], (*procs)[64][32];
  struct Load0__16 *lnk;
} *Load0__16_s;

static void __17 (Files_Rider *r, void **r__typ, INTEGER pos, INTEGER span, Texts_Elem *e);

static void __17 (Files_Rider *r, void **r__typ, INTEGER pos, INTEGER span, Texts_Elem *e)
{
  Heap_Module M = NIL;
  Heap_Command Cmd = NIL;
  Texts_Alien a = NIL;
  INTEGER org, ew, eh;
  BYTE eno;
  Texts_new = NIL;
  Files_ReadInt(r, r__typ, &ew);
  Files_ReadInt(r, r__typ, &eh);
  Files_ReadByte(r, r__typ, &eno);
  if ((INTEGER)eno > (INTEGER)(*Load0__16_s->ecnt)) {
    (*Load0__16_s->ecnt) = eno;
    Files_ReadString(r, r__typ, (void*)((*Load0__16_s->mods))[__X(eno, 64, (CHAR*)"Texts", 200772)], 32);
    Files_ReadString(r, r__typ, (void*)((*Load0__16_s->procs))[__X(eno, 64, (CHAR*)"Texts", 200805)], 32);
  }
  org = (INTEGER)Files_Pos(r, r__typ);
  M = Modules_ThisMod((void*)((*Load0__16_s->mods))[__X(eno, 64, (CHAR*)"Texts", 201025)], 32);
  if (M != NIL) {
    Cmd = Modules_ThisCommand(M, (void*)((*Load0__16_s->procs))[__X(eno, 64, (CHAR*)"Texts", 201279)], 32);
    if (Cmd != NIL) {
      (*Cmd)();
    }
  }
  *e = Texts_new;
  if (*e != NIL) {
    (*e)->W = ew;
    (*e)->H = eh;
    (*e)->base = (*Load0__16_s->T);
    ((*Load0__16_s->msg)).pos = pos;
    (*(*e)->handle)(*e, (void*)&(*Load0__16_s->msg), Texts_FileMsg__typ);
    if ((INTEGER)Files_Pos(r, r__typ) != org + span) {
      *e = NIL;
    }
  }
  if (*e == NIL) {
    Files_Set(r, r__typ, (*Load0__16_s->f), org + span);
    __NEW(a, Texts_Alien__rec);
    a->W = ew;
    a->H = eh;
    a->handle = Texts_HandleAlien;
    a->base = (*Load0__16_s->T);
    a->file = (*Load0__16_s->f);
    a->org = org;
    a->span = span;
    __STRCOPYCC(((*Load0__16_s->mods))[__X(eno, 64, (CHAR*)"Texts", 204059)], a->mod, 32, (CHAR*)"Texts", 204059);
    __STRCOPYCC(((*Load0__16_s->procs))[__X(eno, 64, (CHAR*)"Texts", 204082)], a->proc, 32, (CHAR*)"Texts", 204082);
    *e = (Texts_Elem)a;
  }
}

static void Texts_Load0 (Files_Rider *r, void **r__typ, Texts_Text T)
{
  Texts_Run u = NIL;
  Texts_Run un = NIL;
  Texts_Piece p = NIL;
  Texts_Elem e = NIL;
  INTEGER org, pos, hlen, plen;
  BYTE ecnt, fno, fcnt, col, voff;
  Files_File f = NIL;
  Texts_FileMsg msg = {0};
  CHAR mods[64][32], procs[64][32];
  CHAR name[32];
  Texts_FontsFont fnts[32] = {0};
  struct Load0__16 _s;
  _s.T = &T;
  _s.ecnt = &ecnt;
  _s.f = &f;
  _s.msg = &msg;
  _s.mods = (void*)mods;
  _s.procs = (void*)procs;
  _s.lnk = Load0__16_s;
  Load0__16_s = &_s;
  pos = (INTEGER)Files_Pos(r, r__typ);
  f = Files_Base(r, r__typ);
  __NEW(u, Texts_RunDesc);
  u->len = 2147483647;
  u->fnt = NIL;
  u->col = 15;
  T->head = u;
  ecnt = 0;
  fcnt = 0;
  msg.id = 0;
  msg.r = *r;
  Files_ReadInt(&msg.r, Files_Rider__typ, &hlen);
  org = (pos - 2) + hlen;
  pos = org;
  Files_ReadByte(&msg.r, Files_Rider__typ, &fno);
  while ((INTEGER)fno != 0) {
    if ((INTEGER)fno > (INTEGER)fcnt) {
      fcnt = fno;
      Files_ReadString(&msg.r, Files_Rider__typ, (void*)name, 32);
      fnts[__X(fno, 32, (CHAR*)"Texts", 206945)] = Texts_FontsThis((void*)name, 32);
    }
    Files_ReadByte(&msg.r, Files_Rider__typ, &col);
    Files_ReadByte(&msg.r, Files_Rider__typ, &voff);
    Files_ReadInt(&msg.r, Files_Rider__typ, &plen);
    if (plen > 0) {
      __NEW(p, Texts_PieceDesc);
      p->file = f;
      p->org = pos;
      p->ascii = 0;
      un = (Texts_Run)p;
      un->len = plen;
    } else {
      __17(&msg.r, Files_Rider__typ, pos - org, -plen, &e);
      un = (Texts_Run)e;
      un->len = 1;
    }
    un->col = col;
    un->voff = voff;
    pos += un->len;
    u->next = un;
    un->prev = u;
    u = un;
    Files_ReadByte(&msg.r, Files_Rider__typ, &fno);
  }
  u->next = T->head;
  T->head->prev = u;
  T->cache = T->head;
  T->corg = 0;
  Files_ReadInt(&msg.r, Files_Rider__typ, &T->len);
  Files_Set(r, r__typ, f, (INTEGER)Files_Pos(&msg.r, Files_Rider__typ) + T->len);
  Load0__16_s = _s.lnk;
}

void Texts_Load (Files_Rider *r, void **r__typ, Texts_Text T)
{
  SHORTINT tag;
  Files_ReadSInt(r, r__typ, &tag);
  if ((INTEGER)tag != -4095) {
    Files_Set(r, r__typ, Files_Base(r, r__typ), Files_Pos(r, r__typ) - 2);
  }
  Texts_Load0(r, r__typ, T);
}

/*----------------------------------------------------------------------------*/
void Texts_Open (Texts_Text T, CHAR *name, INTEGER name__len)
{
  Files_File f = NIL;
  Files_Rider r = {0};
  Texts_Run u = NIL;
  Texts_Piece p = NIL;
  CHAR tag, version, bom;
  INTEGER hlen;
  f = Files_Old((void*)name, name__len);
  if (f == NIL) {
    f = Files_New((CHAR*)"", 1);
  }
  Files_Set(&r, Files_Rider__typ, f, 0);
  Files_ReadChar(&r, Files_Rider__typ, &tag);
  Files_ReadChar(&r, Files_Rider__typ, &version);
  if (tag == 0xf0 || (tag == 0x01 && version == 0xf0)) {
    Texts_Load0(&r, Files_Rider__typ, T);
  } else {
    __NEW(u, Texts_RunDesc);
    u->len = 2147483647;
    u->fnt = NIL;
    u->col = 15;
    __NEW(p, Texts_PieceDesc);
    if (tag == 0xf7 && version == 0x07) {
      Files_Set(&r, Files_Rider__typ, f, 28);
      Files_ReadInt(&r, Files_Rider__typ, &hlen);
      Files_Set(&r, Files_Rider__typ, f, 22 + hlen);
      Files_ReadInt(&r, Files_Rider__typ, &T->len);
      p->org = 26 + hlen;
    } else {
      T->len = (INTEGER)Files_Length(f);
      Files_ReadChar(&r, Files_Rider__typ, &bom);
      if ((tag == 0xef && version == 0xbb) && bom == 0xbf) {
        p->org = 3;
      } else {
        p->org = 0;
      }
    }
    if (T->len > 0) {
      p->len = T->len;
      p->fnt = Texts_FontsDefault;
      p->col = 15;
      p->voff = 0;
      p->file = f;
      p->ascii = 1;
      u->next = (Texts_Run)p;
      u->prev = (Texts_Run)p;
      p->next = u;
      p->prev = u;
    } else {
      u->next = u;
      u->prev = u;
    }
    T->head = u;
    T->cache = T->head;
    T->corg = 0;
  }
}

/*----------------------------------------------------------------------------*/
static struct Store__40 {
  BYTE *ecnt;
  Texts_FileMsg *msg;
  Texts_IdentifyMsg *iden;
  CHAR (*mods)[64][32], (*procs)[64][32];
  struct Store__40 *lnk;
} *Store__40_s;

static void __42 (Files_Rider *r, void **r__typ, INTEGER pos, Texts_Elem e);

static void __42 (Files_Rider *r, void **r__typ, INTEGER pos, Texts_Elem e)
{
  Files_Rider r1 = {0};
  INTEGER org, span;
  BYTE eno;
  __STRCOPYCC(((*Store__40_s->iden)).mod, ((*Store__40_s->mods))[__X((*Store__40_s->ecnt), 64, (CHAR*)"Texts", 221985)], 32, (CHAR*)"Texts", 221985);
  __STRCOPYCC(((*Store__40_s->iden)).proc, ((*Store__40_s->procs))[__X((*Store__40_s->ecnt), 64, (CHAR*)"Texts", 222012)], 32, (CHAR*)"Texts", 222012);
  eno = 1;
  while (__STRCMPCC(((*Store__40_s->mods))[__X(eno, 64, (CHAR*)"Texts", 222270)], ((*Store__40_s->iden)).mod, 32, (CHAR*)"Texts", 222270) != 0 || __STRCMPCC(((*Store__40_s->procs))[__X(eno, 64, (CHAR*)"Texts", 222270)], ((*Store__40_s->iden)).proc, 32, (CHAR*)"Texts", 222270) != 0) {
    eno += 1;
  }
  Files_Set(&r1, Files_Rider__typ, Files_Base(r, r__typ), Files_Pos(r, r__typ));
  Files_WriteInt(r, r__typ, 0);
  Files_WriteInt(r, r__typ, 0);
  Files_WriteInt(r, r__typ, 0);
  Files_WriteByte(r, r__typ, eno);
  if ((INTEGER)eno == (INTEGER)(*Store__40_s->ecnt)) {
    (*Store__40_s->ecnt) += 1;
    Files_WriteString(r, r__typ, (void*)((*Store__40_s->iden)).mod, 32);
    Files_WriteString(r, r__typ, (void*)((*Store__40_s->iden)).proc, 32);
  }
  ((*Store__40_s->msg)).pos = pos;
  org = (INTEGER)Files_Pos(r, r__typ);
  (*e->handle)(e, (void*)&(*Store__40_s->msg), Texts_FileMsg__typ);
  span = (INTEGER)Files_Pos(r, r__typ) - org;
  Files_WriteInt(&r1, Files_Rider__typ, -span);
  Files_WriteInt(&r1, Files_Rider__typ, e->W);
  Files_WriteInt(&r1, Files_Rider__typ, e->H);
}

void Texts_Store (Files_Rider *r, void **r__typ, Texts_Text T)
{
  Files_Rider r1 = {0};
  Texts_Run u = NIL;
  Texts_Run un = NIL;
  Texts_Elem e = NIL;
  INTEGER org, pos, delta, hlen, rlen;
  BYTE ecnt, fno, fcnt;
  CHAR ch;
  Texts_FileMsg msg = {0};
  Texts_IdentifyMsg iden;
  CHAR mods[64][32], procs[64][32];
  Texts_FontsFont fnts[32] = {0};
  CHAR block[1024];
  Texts_FontsFont _ptr__41 = NIL;
  struct Store__40 _s;
  _s.ecnt = &ecnt;
  _s.msg = &msg;
  _s.iden = &iden;
  _s.mods = (void*)mods;
  _s.procs = (void*)procs;
  _s.lnk = Store__40_s;
  Store__40_s = &_s;
  org = (INTEGER)Files_Pos(r, r__typ);
  msg.id = 1;
  msg.r = *r;
  Files_WriteInt(&msg.r, Files_Rider__typ, 0);
  u = T->head->next;
  pos = 0;
  delta = 0;
  fcnt = 1;
  ecnt = 1;
  while (u != T->head) {
    if (__ISP(u, Texts_ElemDesc, 1)) {
      iden.mod[0] = 0x00;
      (*(__GUARDP(u, Texts_ElemDesc, 1))->handle)(__GUARDP(u, Texts_ElemDesc, 1), (void*)&iden, Texts_IdentifyMsg__typ);
    } else {
      iden.mod[0] = 0x01;
    }
    if (iden.mod[0] != 0x00) {
      fnts[__X(fcnt, 32, (CHAR*)"Texts", 226075)] = u->fnt;
      fno = 1;
      while (__STRCMPCC(fnts[__X(fno, 32, (CHAR*)"Texts", 226345)]->name, u->fnt->name, 32, (CHAR*)"Texts", 226345) != 0) {
        fno += 1;
      }
      Files_WriteByte(&msg.r, Files_Rider__typ, fno);
      if ((INTEGER)fno == (INTEGER)fcnt) {
        fcnt += 1;
        _ptr__41 = u->fnt;
        Files_WriteString(&msg.r, Files_Rider__typ, (void*)_ptr__41->name, 32);
      }
      Files_WriteByte(&msg.r, Files_Rider__typ, u->col);
      Files_WriteByte(&msg.r, Files_Rider__typ, u->voff);
    }
    if (__ISP(u, Texts_PieceDesc, 1)) {
      rlen = u->len;
      un = u->next;
      while (((__ISP(un, Texts_PieceDesc, 1) && un->fnt == u->fnt) && (INTEGER)un->col == (INTEGER)u->col) && (INTEGER)un->voff == (INTEGER)u->voff) {
        rlen += un->len;
        un = un->next;
      }
      Files_WriteInt(&msg.r, Files_Rider__typ, rlen);
      pos += rlen;
      u = un;
    } else if (iden.mod[0] != 0x00) {
      __42(&msg.r, Files_Rider__typ, pos, __GUARDP(u, Texts_ElemDesc, 1));
      pos += 1;
      u = u->next;
    } else {
      delta += 1;
      u = u->next;
    }
  }
  Files_WriteByte(&msg.r, Files_Rider__typ, 0);
  Files_WriteInt(&msg.r, Files_Rider__typ, T->len - delta);
  hlen = ((INTEGER)Files_Pos(&msg.r, Files_Rider__typ) - org) + 2;
  Files_Set(&r1, Files_Rider__typ, Files_Base(&msg.r, Files_Rider__typ), org);
  Files_WriteInt(&r1, Files_Rider__typ, hlen);
  u = T->head->next;
  while (u != T->head) {
    if (__ISP(u, Texts_PieceDesc, 1)) {
      if (__ISP(u, Texts_PieceDesc, 1)) {
        if (((Texts_Piece)u)->ascii) {
          Files_Set(&r1, Files_Rider__typ, ((Texts_Piece)u)->file, ((Texts_Piece)u)->org);
          delta = ((Texts_Piece)u)->len;
          while (delta > 0) {
            Files_ReadChar(&r1, Files_Rider__typ, &ch);
            delta -= 1;
            if (ch == 0x0a) {
              Files_WriteChar(&msg.r, Files_Rider__typ, 0x0d);
            } else {
              Files_WriteChar(&msg.r, Files_Rider__typ, ch);
            }
          }
        } else {
          Files_Set(&r1, Files_Rider__typ, ((Texts_Piece)u)->file, ((Texts_Piece)u)->org);
          delta = ((Texts_Piece)u)->len;
          while (delta > 1024) {
            Files_ReadBytes(&r1, Files_Rider__typ, (void*)(SYSTEM_ADRINT)block, 1024, 1024);
            Files_WriteBytes(&msg.r, Files_Rider__typ, (void*)(SYSTEM_ADRINT)block, 1024, 1024);
            delta -= 1024;
          }
          Files_ReadBytes(&r1, Files_Rider__typ, (void*)(SYSTEM_ADRINT)block, 1024, delta);
          Files_WriteBytes(&msg.r, Files_Rider__typ, (void*)(SYSTEM_ADRINT)block, 1024, delta);
        }
      } else __WITHCHK((CHAR*)"Texts", 234751);
    } else {
      iden.mod[0] = 0x00;
      (*(__GUARDP(u, Texts_ElemDesc, 1))->handle)(__GUARDP(u, Texts_ElemDesc, 1), (void*)&iden, Texts_IdentifyMsg__typ);
      if (iden.mod[0] != 0x00) {
        Files_WriteChar(&msg.r, Files_Rider__typ, 0x1c);
      }
    }
    u = u->next;
  }
  __GUARDEQR(r, r__typ, Files_Rider) = msg.r;
  if (T->notify != NIL) {
    (*T->notify)(T, 3, 0, 0);
  }
  Store__40_s = _s.lnk;
}

/*----------------------------------------------------------------------------*/
void Texts_Close (Texts_Text T, CHAR *name, INTEGER name__len)
{
  Files_File f = NIL;
  Files_Rider r = {0};
  INTEGER i, res;
  CHAR bak[64];
  f = Files_New((void*)name, name__len);
  Files_Set(&r, Files_Rider__typ, f, 0);
  Files_WriteChar(&r, Files_Rider__typ, 0xf0);
  Files_WriteChar(&r, Files_Rider__typ, 0x01);
  Texts_Store(&r, Files_Rider__typ, T);
  i = 0;
  while (name[__X(i, name__len, (CHAR*)"Texts", 238622)] != 0x00) {
    i += 1;
  }
  __STRCOPYCC(name, bak, __MIN(64, name__len), (CHAR*)"Texts", 238864);
  bak[__X(i, 64, (CHAR*)"Texts", 238879)] = '.';
  bak[__X(i + 1, 64, (CHAR*)"Texts", 238896)] = 'B';
  bak[__X(i + 2, 64, (CHAR*)"Texts", 238913)] = 'a';
  bak[__X(i + 3, 64, (CHAR*)"Texts", 238930)] = 'k';
  bak[__X(i + 4, 64, (CHAR*)"Texts", 238946)] = 0x00;
  Files_Rename((void*)name, name__len, (void*)bak, 64, &res);
  Files_Register(f);
}

/*----------------------------------------------------------------------------*/
static void EnumPtrs(void (*P)(void*))
{
  P(Texts_new);
  P(Texts_del);
  P(Texts_FontsDefault);
}

__TDESC(Texts_FontDesc__desc, 2, 0) = {__TDFLDS("FontDesc", 32), {-4}};
__TDESC(Texts_RunDesc__desc, 1, 3) = {__TDFLDS("RunDesc", 20), {0, 4, 12, -16}};
__TDESC(Texts_PieceDesc__desc, 1, 4) = {__TDFLDS("PieceDesc", 28), {0, 4, 12, 20, -20}};
__TDESC(Texts_ElemMsg__desc, 1, 0) = {__TDFLDS("ElemMsg", 1), {-4}};
__TDESC(Texts_ElemDesc__desc, 1, 4) = {__TDFLDS("ElemDesc", 36), {0, 4, 12, 32, -20}};
__TDESC(Texts_FileMsg__desc, 1, 1) = {__TDFLDS("FileMsg", 32), {16, -8}};
__TDESC(Texts_CopyMsg__desc, 1, 1) = {__TDFLDS("CopyMsg", 4), {0, -8}};
__TDESC(Texts_IdentifyMsg__desc, 1, 0) = {__TDFLDS("IdentifyMsg", 64), {-4}};
__TDESC(Texts_BufDesc__desc, 2, 1) = {__TDFLDS("BufDesc", 8), {4, -8}};
__TDESC(Texts_TextDesc__desc, 2, 2) = {__TDFLDS("TextDesc", 20), {8, 12, -12}};
__TDESC(Texts_Reader__desc, 2, 4) = {__TDFLDS("Reader", 52), {4, 12, 24, 40, -20}};
__TDESC(Texts_Scanner__desc, 2, 4) = {__TDFLDS("Scanner", 144), {4, 12, 24, 40, -20}};
__TDESC(Texts_Writer__desc, 2, 4) = {__TDFLDS("Writer", 40), {0, 4, 20, 36, -20}};
__TDESC(Texts_Alien__rec__desc, 1, 5) = {__TDFLDS("Alien__rec", 112), {0, 4, 12, 32, 36, -24}};

export void *Texts__init (void)
{
  __DEFMOD;
  __IMPORT(Files__init);
  __IMPORT(Modules__init);
  __IMPORT(Reals__init);
  __REGMOD("Texts", EnumPtrs);
  __INITYP(Texts_FontDesc, Texts_FontDesc, 0);
  __INITYP(Texts_RunDesc, Texts_RunDesc, 0);
  __INITYP(Texts_PieceDesc, Texts_RunDesc, 1);
  __INITYP(Texts_ElemMsg, Texts_ElemMsg, 0);
  __INITYP(Texts_ElemDesc, Texts_RunDesc, 1);
  __INITYP(Texts_FileMsg, Texts_ElemMsg, 1);
  __INITYP(Texts_CopyMsg, Texts_ElemMsg, 1);
  __INITYP(Texts_IdentifyMsg, Texts_ElemMsg, 1);
  __INITYP(Texts_BufDesc, Texts_BufDesc, 0);
  __INITYP(Texts_TextDesc, Texts_TextDesc, 0);
  __INITYP(Texts_Reader, Texts_Reader, 0);
  __INITYP(Texts_Scanner, Texts_Reader, 1);
  __INITYP(Texts_Writer, Texts_Writer, 0);
  __INITYP(Texts_Alien__rec, Texts_ElemDesc, 2);
/* BEGIN */
  Texts_del = NIL;
  __NEW(Texts_FontsDefault, Texts_FontDesc);
  __MOVE((CHAR*)"Syntax10.Scn.Fnt", Texts_FontsDefault->name, 17);
  __ENDMOD;
}
