/* Ofront+ 1.0 -sC -44 */
#include "SYSTEM.oh"
#include "OfrontOPM.oh"

typedef
  CHAR OfrontOPS_Name[48];

typedef
  struct CHAR8_ARRAY *OfrontOPS_String;


#ifndef CHAR8_ARRAY_DEF
#define CHAR8_ARRAY_DEF
typedef struct CHAR8_ARRAY {
  INTEGER len[1];
  CHAR data[1];
} CHAR8_ARRAY;
#endif 

#ifndef CHAR16_ARRAY_DEF
#define CHAR16_ARRAY_DEF
typedef struct CHAR16_ARRAY {
  INTEGER len[1];
  LONGCHAR data[1];
} CHAR16_ARRAY;
#endif 

export OfrontOPS_Name OfrontOPS_name;
export OfrontOPS_String OfrontOPS_str;
export struct CHAR16_ARRAY *OfrontOPS_lstr;
export SHORTINT OfrontOPS_numtyp;
export LONGINT OfrontOPS_intval;
export SHORTREAL OfrontOPS_realval;
export REAL OfrontOPS_lrlval;
export BOOLEAN OfrontOPS_lowcase;
static LONGCHAR OfrontOPS_ch;
static void (*OfrontOPS_checkKeyword)(BYTE*);


static void OfrontOPS_AutoKeywords (BYTE *sym);
static BOOLEAN OfrontOPS_Cmp (CHAR *std, INTEGER std__len, CHAR *low, INTEGER low__len);
export void OfrontOPS_Get (BYTE *sym);
static void OfrontOPS_Identifier (BYTE *sym);
export void OfrontOPS_Init (void);
static void OfrontOPS_LowKeywords (BYTE *sym);
static void OfrontOPS_Number (void);
static void OfrontOPS_StdKeywords (BYTE *sym);
static void OfrontOPS_Str (BYTE *sym);
static void OfrontOPS_err (SHORTINT n);


/*============================================================================*/

static void OfrontOPS_err (SHORTINT n)
{
  OfrontOPM_err(n);
}

static void OfrontOPS_Str (BYTE *sym)
{
  INTEGER i;
  LONGCHAR och, lch;
  BOOLEAN long_;
  LONGCHAR s[256];
  struct CHAR16_ARRAY *t = NIL;
  i = 0;
  och = OfrontOPS_ch;
  long_ = 0;
  for (;;) {
    OfrontOPM_Get(&lch);
    if (lch == och) {
      break;
    }
    if (lch < ' ') {
      OfrontOPS_err(3);
      break;
    }
    if (lch > 0xff) {
      long_ = 1;
    }
    if (i < 255) {
      s[__X(i, 256, (CHAR*)"OfrontOPS", 21247)] = lch;
    } else if (i == 255) {
      s[__X(i, 256, (CHAR*)"OfrontOPS", 21287)] = 0x00;
      OfrontOPS_lstr = __NEWARR(NIL, 2, 2, 1, 1, (SYSTEM_ARRLEN)512);
      __STRCOPYLL(s, OfrontOPS_lstr->data, __MIN(OfrontOPS_lstr->len[0], 256), (CHAR*)"OfrontOPS", 21323);
      (OfrontOPS_lstr->data)[__X(i, OfrontOPS_lstr->len[0], (CHAR*)"OfrontOPS", 21503)] = lch;
    } else if (i < OfrontOPS_lstr->len[0] - 1) {
      (OfrontOPS_lstr->data)[__X(i, OfrontOPS_lstr->len[0], (CHAR*)"OfrontOPS", 21759)] = lch;
    } else {
      t = OfrontOPS_lstr;
      (t->data)[__X(i, t->len[0], (CHAR*)"OfrontOPS", 21789)] = 0x00;
      OfrontOPS_lstr = __NEWARR(NIL, 2, 2, 1, 1, (SYSTEM_ARRLEN)(__ASHL(t->len[0], 1, INTEGER)));
      __STRCOPYLL(t->data, OfrontOPS_lstr->data, __MIN(OfrontOPS_lstr->len[0], t->len[0]), (CHAR*)"OfrontOPS", 21827);
      (OfrontOPS_lstr->data)[__X(i, OfrontOPS_lstr->len[0], (CHAR*)"OfrontOPS", 22015)] = lch;
    }
    i += 1;
  }
  if (i == 1) {
    *sym = 37;
    OfrontOPS_numtyp = 1;
    OfrontOPS_intval = (INTEGER)s[0];
    if (s[0] < ' ') {
      OfrontOPS_err(3);
    }
  } else {
    *sym = 39;
    OfrontOPS_numtyp = 0;
    OfrontOPS_intval = i + 1;
    OfrontOPS_str = __NEWARR(NIL, 1, 1, 1, 1, (SYSTEM_ARRLEN)OfrontOPS_intval);
    if (long_) {
      if (i < 256) {
        s[__X(i, 256, (CHAR*)"OfrontOPS", 24097)] = 0x00;
        OfrontOPS_lstr = __NEWARR(NIL, 2, 2, 1, 1, (SYSTEM_ARRLEN)OfrontOPS_intval);
        __STRCOPYLL(s, OfrontOPS_lstr->data, __MIN(OfrontOPS_lstr->len[0], 256), (CHAR*)"OfrontOPS", 24319);
      } else {
        (OfrontOPS_lstr->data)[__X(i, OfrontOPS_lstr->len[0], (CHAR*)"OfrontOPS", 24575)] = 0x00;
      }
      __STRCOPYTC(OfrontOPS_lstr->data, OfrontOPS_str->data, OfrontOPS_str->len[0], (CHAR*)"OfrontOPS", 25087);
    } else {
      if (i < 256) {
        s[__X(i, 256, (CHAR*)"OfrontOPS", 25377)] = 0x00;
        __STRCOPYTC(s, OfrontOPS_str->data, OfrontOPS_str->len[0], (CHAR*)"OfrontOPS", 25396);
      } else {
        (OfrontOPS_lstr->data)[__X(i, OfrontOPS_lstr->len[0], (CHAR*)"OfrontOPS", 25622)] = 0x00;
        __STRCOPYTC(OfrontOPS_lstr->data, OfrontOPS_str->data, OfrontOPS_str->len[0], (CHAR*)"OfrontOPS", 25855);
      }
      OfrontOPS_lstr = NIL;
    }
  }
  OfrontOPM_Get(&OfrontOPS_ch);
}

static void OfrontOPS_StdKeywords (BYTE *sym)
{
  switch (OfrontOPS_name[0]) {
    case 'A': 
      if (__STRCMPCC(OfrontOPS_name, (CHAR*)"ARRAY", 6, (CHAR*)"OfrontOPS", 28927) == 0) {
        *sym = 56;
      }
      break;
    case 'B': 
      if (__STRCMPCC(OfrontOPS_name, (CHAR*)"BEGIN", 6, (CHAR*)"OfrontOPS", 29951) == 0) {
        *sym = 59;
      } else if (__STRCMPCC(OfrontOPS_name, (CHAR*)"BY", 3, (CHAR*)"OfrontOPS", 29439) == 0) {
        *sym = 31;
      }
      break;
    case 'C': 
      if (__STRCMPCC(OfrontOPS_name, (CHAR*)"CASE", 5, (CHAR*)"OfrontOPS", 31231) == 0) {
        *sym = 48;
      } else if (__STRCMPCC(OfrontOPS_name, (CHAR*)"CONST", 6, (CHAR*)"OfrontOPS", 30463) == 0) {
        *sym = 60;
      } else if ((OfrontOPM_Lang == 'C' || OfrontOPM_Lang == '3') && __STRCMPCC(OfrontOPS_name, (CHAR*)"CLOSE", 6, (CHAR*)"OfrontOPS", 30719) == 0) {
        *sym = 68;
      }
      break;
    case 'D': 
      if (__STRCMPCC(OfrontOPS_name, (CHAR*)"DO", 3, (CHAR*)"OfrontOPS", 32511) == 0) {
        *sym = 29;
      } else if (__STRCMPCC(OfrontOPS_name, (CHAR*)"DIV", 4, (CHAR*)"OfrontOPS", 31743) == 0) {
        *sym = 3;
      } else if ((OfrontOPM_Lang == 'C' || OfrontOPM_Lang == '3') && __STRCMPCC(OfrontOPS_name, (CHAR*)"DIV0", 5, (CHAR*)"OfrontOPS", 31999) == 0) {
        *sym = 5;
      }
      break;
    case 'E': 
      if (__STRCMPCC(OfrontOPS_name, (CHAR*)"END", 4, (CHAR*)"OfrontOPS", 34047) == 0) {
        *sym = 43;
      } else if (__STRCMPCC(OfrontOPS_name, (CHAR*)"ELSE", 5, (CHAR*)"OfrontOPS", 33023) == 0) {
        *sym = 44;
      } else if (__STRCMPCC(OfrontOPS_name, (CHAR*)"ELSIF", 6, (CHAR*)"OfrontOPS", 33279) == 0) {
        *sym = 45;
      } else if (OfrontOPM_Lang != '7' && __STRCMPCC(OfrontOPS_name, (CHAR*)"EXIT", 5, (CHAR*)"OfrontOPS", 33535) == 0) {
        *sym = 54;
      }
      break;
    case 'F': 
      if (OfrontOPM_Lang != '1' && __STRCMPCC(OfrontOPS_name, (CHAR*)"FOR", 4, (CHAR*)"OfrontOPS", 34559) == 0) {
        *sym = 51;
      }
      break;
    case 'I': 
      if (__STRCMPCC(OfrontOPS_name, (CHAR*)"IF", 3, (CHAR*)"OfrontOPS", 36095) == 0) {
        *sym = 47;
      } else if (__STRCMPCC(OfrontOPS_name, (CHAR*)"IN", 3, (CHAR*)"OfrontOPS", 35071) == 0) {
        *sym = 17;
      } else if (__STRCMPCC(OfrontOPS_name, (CHAR*)"IS", 3, (CHAR*)"OfrontOPS", 35327) == 0) {
        *sym = 18;
      } else if (__STRCMPCC(OfrontOPS_name, (CHAR*)"IMPORT", 7, (CHAR*)"OfrontOPS", 35583) == 0) {
        *sym = 64;
      }
      break;
    case 'L': 
      if (OfrontOPM_Lang != '7' && __STRCMPCC(OfrontOPS_name, (CHAR*)"LOOP", 5, (CHAR*)"OfrontOPS", 36607) == 0) {
        *sym = 52;
      }
      break;
    case 'M': 
      if (__STRCMPCC(OfrontOPS_name, (CHAR*)"MOD", 4, (CHAR*)"OfrontOPS", 37631) == 0) {
        *sym = 4;
      } else if (__STRCMPCC(OfrontOPS_name, (CHAR*)"MODULE", 7, (CHAR*)"OfrontOPS", 37119) == 0) {
        *sym = 65;
      }
      break;
    case 'N': 
      if (__STRCMPCC(OfrontOPS_name, (CHAR*)"NIL", 4, (CHAR*)"OfrontOPS", 38143) == 0) {
        *sym = 38;
      }
      break;
    case 'O': 
      if (__STRCMPCC(OfrontOPS_name, (CHAR*)"OR", 3, (CHAR*)"OfrontOPS", 39423) == 0) {
        *sym = 10;
      } else if (__STRCMPCC(OfrontOPS_name, (CHAR*)"OF", 3, (CHAR*)"OfrontOPS", 38655) == 0) {
        *sym = 27;
      } else if (OfrontOPM_Lang == 'C' && __STRCMPCC(OfrontOPS_name, (CHAR*)"OUT", 4, (CHAR*)"OfrontOPS", 38911) == 0) {
        *sym = 66;
      }
      break;
    case 'P': 
      if (__STRCMPCC(OfrontOPS_name, (CHAR*)"PROCEDURE", 10, (CHAR*)"OfrontOPS", 40447) == 0) {
        *sym = 63;
      } else if (__STRCMPCC(OfrontOPS_name, (CHAR*)"POINTER", 8, (CHAR*)"OfrontOPS", 39935) == 0) {
        *sym = 58;
      }
      break;
    case 'R': 
      if (__STRCMPCC(OfrontOPS_name, (CHAR*)"RECORD", 7, (CHAR*)"OfrontOPS", 41983) == 0) {
        *sym = 57;
      } else if ((OfrontOPM_Lang == 'C' || OfrontOPM_Lang == '3') && __STRCMPCC(OfrontOPS_name, (CHAR*)"REM0", 5, (CHAR*)"OfrontOPS", 40959) == 0) {
        *sym = 6;
      } else if (__STRCMPCC(OfrontOPS_name, (CHAR*)"REPEAT", 7, (CHAR*)"OfrontOPS", 41215) == 0) {
        *sym = 50;
      } else if (__STRCMPCC(OfrontOPS_name, (CHAR*)"RETURN", 7, (CHAR*)"OfrontOPS", 41471) == 0) {
        *sym = 55;
      }
      break;
    case 'T': 
      if (__STRCMPCC(OfrontOPS_name, (CHAR*)"THEN", 5, (CHAR*)"OfrontOPS", 43263) == 0) {
        *sym = 28;
      } else if (__STRCMPCC(OfrontOPS_name, (CHAR*)"TO", 3, (CHAR*)"OfrontOPS", 42495) == 0) {
        *sym = 30;
      } else if (__STRCMPCC(OfrontOPS_name, (CHAR*)"TYPE", 5, (CHAR*)"OfrontOPS", 42751) == 0) {
        *sym = 61;
      }
      break;
    case 'U': 
      if (__STRCMPCC(OfrontOPS_name, (CHAR*)"UNTIL", 6, (CHAR*)"OfrontOPS", 43775) == 0) {
        *sym = 46;
      }
      break;
    case 'V': 
      if (__STRCMPCC(OfrontOPS_name, (CHAR*)"VAR", 4, (CHAR*)"OfrontOPS", 44287) == 0) {
        *sym = 62;
      }
      break;
    case 'W': 
      if (__STRCMPCC(OfrontOPS_name, (CHAR*)"WHILE", 6, (CHAR*)"OfrontOPS", 45311) == 0) {
        *sym = 49;
      } else if ((OfrontOPM_Lang != '3' && OfrontOPM_Lang != '7') && __STRCMPCC(OfrontOPS_name, (CHAR*)"WITH", 5, (CHAR*)"OfrontOPS", 44799) == 0) {
        *sym = 53;
      }
      break;
    default: 
      break;
  }
}

static BOOLEAN OfrontOPS_Cmp (CHAR *std, INTEGER std__len, CHAR *low, INTEGER low__len)
{
  if (__STRCMPCC(OfrontOPS_name, std, std__len, (CHAR*)"OfrontOPS", 46902) == 0) {
    OfrontOPM_Mark(214, OfrontOPM_curpos - 1);
  }
  return __STRCMPCC(OfrontOPS_name, low, low__len, (CHAR*)"OfrontOPS", 47359) == 0;
}

static void OfrontOPS_LowKeywords (BYTE *sym)
{
  switch (__CAP(OfrontOPS_name[0])) {
    case 'A': 
      if (OfrontOPS_Cmp((CHAR*)"ARRAY", 6, (CHAR*)"array", 6)) {
        *sym = 56;
      }
      break;
    case 'B': 
      if (OfrontOPS_Cmp((CHAR*)"BEGIN", 6, (CHAR*)"begin", 6)) {
        *sym = 59;
      } else if (OfrontOPS_Cmp((CHAR*)"BY", 3, (CHAR*)"by", 3)) {
        *sym = 31;
      }
      break;
    case 'C': 
      if (OfrontOPS_Cmp((CHAR*)"CASE", 5, (CHAR*)"case", 5)) {
        *sym = 48;
      } else if (OfrontOPS_Cmp((CHAR*)"CONST", 6, (CHAR*)"const", 6)) {
        *sym = 60;
      } else if ((OfrontOPM_Lang == 'C' || OfrontOPM_Lang == '3') && OfrontOPS_Cmp((CHAR*)"CLOSE", 6, (CHAR*)"close", 6)) {
        *sym = 68;
      }
      break;
    case 'D': 
      if (OfrontOPS_Cmp((CHAR*)"DO", 3, (CHAR*)"do", 3)) {
        *sym = 29;
      } else if (OfrontOPS_Cmp((CHAR*)"DIV", 4, (CHAR*)"div", 4)) {
        *sym = 3;
      } else if ((OfrontOPM_Lang == 'C' || OfrontOPM_Lang == '3') && OfrontOPS_Cmp((CHAR*)"DIV0", 5, (CHAR*)"div0", 5)) {
        *sym = 5;
      }
      break;
    case 'E': 
      if (OfrontOPS_Cmp((CHAR*)"END", 4, (CHAR*)"end", 4)) {
        *sym = 43;
      } else if (OfrontOPS_Cmp((CHAR*)"ELSE", 5, (CHAR*)"else", 5)) {
        *sym = 44;
      } else if (OfrontOPS_Cmp((CHAR*)"ELSIF", 6, (CHAR*)"elsif", 6)) {
        *sym = 45;
      } else if (OfrontOPM_Lang != '7' && OfrontOPS_Cmp((CHAR*)"EXIT", 5, (CHAR*)"exit", 5)) {
        *sym = 54;
      }
      break;
    case 'F': 
      if (OfrontOPM_Lang != '1' && OfrontOPS_Cmp((CHAR*)"FOR", 4, (CHAR*)"for", 4)) {
        *sym = 51;
      }
      break;
    case 'I': 
      if (OfrontOPS_Cmp((CHAR*)"IF", 3, (CHAR*)"if", 3)) {
        *sym = 47;
      } else if (OfrontOPS_Cmp((CHAR*)"IN", 3, (CHAR*)"in", 3)) {
        *sym = 17;
      } else if (OfrontOPS_Cmp((CHAR*)"IS", 3, (CHAR*)"is", 3)) {
        *sym = 18;
      } else if (OfrontOPS_Cmp((CHAR*)"IMPORT", 7, (CHAR*)"import", 7)) {
        *sym = 64;
      }
      break;
    case 'L': 
      if (OfrontOPM_Lang != '7' && OfrontOPS_Cmp((CHAR*)"LOOP", 5, (CHAR*)"loop", 5)) {
        *sym = 52;
      }
      break;
    case 'M': 
      if (OfrontOPS_Cmp((CHAR*)"MOD", 4, (CHAR*)"mod", 4)) {
        *sym = 4;
      } else if (OfrontOPS_Cmp((CHAR*)"MODULE", 7, (CHAR*)"module", 7)) {
        *sym = 65;
      }
      break;
    case 'N': 
      if (OfrontOPS_Cmp((CHAR*)"NIL", 4, (CHAR*)"nil", 4)) {
        *sym = 38;
      }
      break;
    case 'O': 
      if (OfrontOPS_Cmp((CHAR*)"OR", 3, (CHAR*)"or", 3)) {
        *sym = 10;
      } else if (OfrontOPS_Cmp((CHAR*)"OF", 3, (CHAR*)"of", 3)) {
        *sym = 27;
      } else if (OfrontOPM_Lang == 'C' && OfrontOPS_Cmp((CHAR*)"OUT", 4, (CHAR*)"out", 4)) {
        *sym = 66;
      }
      break;
    case 'P': 
      if (OfrontOPS_Cmp((CHAR*)"PROCEDURE", 10, (CHAR*)"procedure", 10)) {
        *sym = 63;
      } else if (OfrontOPS_Cmp((CHAR*)"POINTER", 8, (CHAR*)"pointer", 8)) {
        *sym = 58;
      }
      break;
    case 'R': 
      if (OfrontOPS_Cmp((CHAR*)"RECORD", 7, (CHAR*)"record", 7)) {
        *sym = 57;
      } else if ((OfrontOPM_Lang == 'C' || OfrontOPM_Lang == '3') && OfrontOPS_Cmp((CHAR*)"REM0", 5, (CHAR*)"rem0", 5)) {
        *sym = 6;
      } else if (OfrontOPS_Cmp((CHAR*)"REPEAT", 7, (CHAR*)"repeat", 7)) {
        *sym = 50;
      } else if (OfrontOPS_Cmp((CHAR*)"RETURN", 7, (CHAR*)"return", 7)) {
        *sym = 55;
      }
      break;
    case 'S': 
      if (__STRCMPCC(OfrontOPS_name, (CHAR*)"system", 7, (CHAR*)"OfrontOPS", 63231) == 0) {
        __MOVE((CHAR*)"SYSTEM", OfrontOPS_name, 7);
      } else if (__STRCMPCC(OfrontOPS_name, (CHAR*)"SYSTEM", 7, (CHAR*)"OfrontOPS", 62719) == 0) {
        __MOVE((CHAR*)"system", OfrontOPS_name, 7);
      }
      break;
    case 'T': 
      if (OfrontOPS_Cmp((CHAR*)"THEN", 5, (CHAR*)"then", 5)) {
        *sym = 28;
      } else if (OfrontOPS_Cmp((CHAR*)"TO", 3, (CHAR*)"to", 3)) {
        *sym = 30;
      } else if (OfrontOPS_Cmp((CHAR*)"TYPE", 5, (CHAR*)"type", 5)) {
        *sym = 61;
      }
      break;
    case 'U': 
      if (OfrontOPS_Cmp((CHAR*)"UNTIL", 6, (CHAR*)"until", 6)) {
        *sym = 46;
      }
      break;
    case 'V': 
      if (OfrontOPS_Cmp((CHAR*)"VAR", 4, (CHAR*)"var", 4)) {
        *sym = 62;
      }
      break;
    case 'W': 
      if (OfrontOPS_Cmp((CHAR*)"WHILE", 6, (CHAR*)"while", 6)) {
        *sym = 49;
      } else if ((OfrontOPM_Lang != '3' && OfrontOPM_Lang != '7') && OfrontOPS_Cmp((CHAR*)"WITH", 5, (CHAR*)"with", 5)) {
        *sym = 53;
      }
      break;
    default: 
      break;
  }
}

static void OfrontOPS_AutoKeywords (BYTE *sym)
{
  if (__STRCMPCC(OfrontOPS_name, (CHAR*)"MODULE", 7, (CHAR*)"OfrontOPS", 70399) == 0) {
    *sym = 65;
    OfrontOPS_checkKeyword = OfrontOPS_StdKeywords;
    OfrontOPS_lowcase = 0;
  } else if (OfrontOPM_Lang == '3' && __STRCMPCC(OfrontOPS_name, (CHAR*)"module", 7, (CHAR*)"OfrontOPS", 69119) == 0) {
    *sym = 65;
    OfrontOPS_checkKeyword = OfrontOPS_LowKeywords;
    OfrontOPS_lowcase = 1;
  }
}

static void OfrontOPS_Identifier (BYTE *sym)
{
  INTEGER i;
  i = 0;
  do {
    OfrontOPS_name[__X(i, 48, (CHAR*)"OfrontOPS", 71959)] = (CHAR)OfrontOPS_ch;
    i += 1;
    OfrontOPM_Get(&OfrontOPS_ch);
  } while (!(((OfrontOPS_ch < '0' || ('9' < OfrontOPS_ch && __CAP(OfrontOPS_ch) < 'A')) || ('Z' < __CAP(OfrontOPS_ch) && OfrontOPS_ch != '_')) || i == 48));
  if (i == 48) {
    OfrontOPS_err(240);
    i -= 1;
  }
  OfrontOPS_name[__X(i, 48, (CHAR*)"OfrontOPS", 72719)] = 0x00;
  *sym = 40;
  (*OfrontOPS_checkKeyword)(sym);
}

static struct Number__12 {
  struct Number__12 *lnk;
} *Number__12_s;

static INTEGER __13 (LONGCHAR ch, BOOLEAN hex);

static INTEGER __13 (LONGCHAR ch, BOOLEAN hex)
{
  if (ch <= '9') {
    return (INTEGER)ch - 48;
  } else if (hex) {
    return ((INTEGER)ch - 65) + 10;
  }
  OfrontOPS_err(2);
  return 0;
}

static void OfrontOPS_Number (void)
{
  INTEGER i, j, m, n, d, e;
  REAL f, g;
  CHAR expCh;
  BOOLEAN neg;
  CHAR dig[24];
  struct Number__12 _s;
  _s.lnk = Number__12_s;
  Number__12_s = &_s;
  i = 0;
  m = 0;
  n = 0;
  d = 0;
  for (;;) {
    if (('0' <= OfrontOPS_ch && OfrontOPS_ch <= '9') || ((d == 0 && 'A' <= OfrontOPS_ch) && OfrontOPS_ch <= 'F')) {
      if (m > 0 || OfrontOPS_ch != '0') {
        if (n < 24) {
          dig[__X(n, 24, (CHAR*)"OfrontOPS", 77869)] = (CHAR)OfrontOPS_ch;
          n += 1;
        }
        m += 1;
      }
      OfrontOPM_Get(&OfrontOPS_ch);
      i += 1;
    } else if (OfrontOPS_ch == '.') {
      OfrontOPM_Get(&OfrontOPS_ch);
      if (OfrontOPS_ch == '.') {
        OfrontOPS_ch = 0x7f;
        break;
      } else if (d == 0) {
        d = i;
      } else {
        OfrontOPS_err(2);
      }
    } else {
      break;
    }
  }
  if (d == 0) {
    if (n == m) {
      OfrontOPS_intval = 0;
      i = 0;
      if (OfrontOPS_ch == 'X') {
        OfrontOPM_Get(&OfrontOPS_ch);
        OfrontOPS_numtyp = 1;
        if (n <= 4) {
          while (i < n) {
            OfrontOPS_intval = __ASHL(OfrontOPS_intval, 4, LONGINT) + (LONGINT)__13(dig[__X(i, 24, (CHAR*)"OfrontOPS", 81981)], 1);
            i += 1;
          }
        } else {
          OfrontOPS_err(203);
        }
      } else if (OfrontOPS_ch == 'H') {
        OfrontOPM_Get(&OfrontOPS_ch);
        OfrontOPS_numtyp = 2;
        if (OfrontOPM_Lang == '3') {
          m = 16;
        } else {
          m = 8;
        }
        if (n <= m) {
          if (n == m && dig[0] > '7') {
            OfrontOPS_intval = -1;
            if (OfrontOPM_Lang == '3') {
              OfrontOPS_err(203);
            }
          }
          while (i < n) {
            OfrontOPS_intval = __ASHL(OfrontOPS_intval, 4, LONGINT) + (LONGINT)__13(dig[__X(i, 24, (CHAR*)"OfrontOPS", 84797)], 1);
            i += 1;
          }
        } else {
          OfrontOPS_err(203);
          OfrontOPS_intval = 1;
        }
      } else if (OfrontOPS_ch == 'L' && OfrontOPM_Lang != '3') {
        OfrontOPM_Get(&OfrontOPS_ch);
        OfrontOPS_numtyp = 2;
        if (n <= 16) {
          if (n == 16 && dig[0] > '7') {
            OfrontOPS_intval = -1;
          }
          while (i < n) {
            OfrontOPS_intval = __ASHL(OfrontOPS_intval, 4, LONGINT) + (LONGINT)__13(dig[__X(i, 24, (CHAR*)"OfrontOPS", 86589)], 1);
            i += 1;
          }
        } else {
          OfrontOPS_err(203);
          OfrontOPS_intval = 1;
        }
      } else {
        OfrontOPS_numtyp = 2;
        while (i < n) {
          d = __13(dig[__X(i, 24, (CHAR*)"OfrontOPS", 87595)], 0);
          i += 1;
          if (OfrontOPS_intval <= __DIV(9223372036854775807LL - (LONGINT)d, 10)) {
            OfrontOPS_intval = OfrontOPS_intval * 10 + (LONGINT)d;
          } else {
            OfrontOPS_err(203);
          }
        }
        if (OfrontOPM_Lang == '7' && OfrontOPS_intval > 2147483647) {
          OfrontOPS_err(-203);
        }
      }
    } else {
      OfrontOPS_err(203);
    }
  } else {
    f = (REAL)0;
    g = (REAL)0;
    e = 0;
    j = 0;
    expCh = 'E';
    while (j < 15 && j < n) {
      g = g * (REAL)10 + (REAL)__13(dig[__X(j, 24, (CHAR*)"OfrontOPS", 90431)], 0);
      j += 1;
    }
    while (n > j) {
      n -= 1;
      f = ((REAL)__13(dig[__X(n, 24, (CHAR*)"OfrontOPS", 90699)], 0) + f) / (REAL)(REAL)10;
    }
    if (OfrontOPS_ch == 'E' || (OfrontOPS_ch == 'D' && OfrontOPM_Lang <= '3')) {
      expCh = (CHAR)OfrontOPS_ch;
      OfrontOPM_Get(&OfrontOPS_ch);
      neg = 0;
      if (OfrontOPS_ch == '-') {
        neg = 1;
        OfrontOPM_Get(&OfrontOPS_ch);
      } else if (OfrontOPS_ch == '+') {
        OfrontOPM_Get(&OfrontOPS_ch);
      }
      if ('0' <= OfrontOPS_ch && OfrontOPS_ch <= '9') {
        do {
          n = __13(OfrontOPS_ch, 0);
          OfrontOPM_Get(&OfrontOPS_ch);
          if (e <= __DIV(32767 - n, 10)) {
            e = (SHORTINT)(e * 10 + n);
          } else {
            OfrontOPS_err(203);
          }
        } while (!(OfrontOPS_ch < '0' || '9' < OfrontOPS_ch));
        if (neg) {
          e = -e;
        }
      } else {
        OfrontOPS_err(2);
      }
    }
    e -= (i - d) - m;
    if (expCh == 'E' && OfrontOPM_Lang != 'C') {
      OfrontOPS_numtyp = 3;
      if (-37 < e && e <= 38) {
        if (e < j) {
          OfrontOPS_realval = (SHORTREAL)((f + g) / OfrontOPM_IntPower((REAL)10, j - e));
        } else {
          OfrontOPS_realval = (SHORTREAL)((f + g) * OfrontOPM_IntPower((REAL)10, e - j));
        }
      } else {
        OfrontOPS_err(203);
      }
    } else {
      OfrontOPS_numtyp = 4;
      if (e < -324) {
        OfrontOPS_lrlval = (REAL)0;
      } else if (e < -294) {
        OfrontOPS_lrlval = (((f + g) / OfrontOPM_IntPower((REAL)10, (j - e) - 30)) / (REAL)(REAL)1000000000000000LL) / (REAL)(REAL)1000000000000000LL;
      } else if (e < j) {
        OfrontOPS_lrlval = (f + g) / OfrontOPM_IntPower((REAL)10, j - e);
      } else if (e <= 308) {
        OfrontOPS_lrlval = (f + g) * OfrontOPM_IntPower((REAL)10, e - j);
      } else if (e == 309) {
        OfrontOPS_lrlval = (f + g) * (OfrontOPM_IntPower((REAL)10, e - j) / (REAL)(REAL)16);
        if (OfrontOPS_lrlval <= OfrontOPM_MaxReal64 / (REAL)(REAL)16) {
          OfrontOPS_lrlval = OfrontOPS_lrlval * (REAL)16;
        } else {
          OfrontOPS_err(203);
        }
      } else {
        OfrontOPS_err(203);
      }
    }
  }
  Number__12_s = _s.lnk;
}

static struct Get__3 {
  struct Get__3 *lnk;
} *Get__3_s;

static BOOLEAN __4 (void);

static struct __4__5 {
  INTEGER *n;
  struct __4__5 *lnk;
} *__4__5_s;

static void __6 (INTEGER len);

static void __6 (INTEGER len)
{
  INTEGER j;
  OfrontOPS_String s2 = NIL;
  INTEGER _for__8;
  if (len > OfrontOPS_str->len[0]) {
    s2 = __NEWARR(NIL, 1, 1, 1, 1, (SYSTEM_ARRLEN)(__ASHL(OfrontOPS_str->len[0], 1, INTEGER)));
    _for__8 = (*__4__5_s->n) - 1;
    j = 0;
    while (j <= _for__8) {
      (s2->data)[__X(j, s2->len[0], (CHAR*)"OfrontOPS", 104773)] = (OfrontOPS_str->data)[__X(j, OfrontOPS_str->len[0], (CHAR*)"OfrontOPS", 104773)];
      j += 1;
    }
    OfrontOPS_str = s2;
  }
}

static BOOLEAN __4 (void)
{
  INTEGER n;
  struct __4__5 _s;
  BOOLEAN __retval;
  _s.n = &n;
  _s.lnk = __4__5_s;
  __4__5_s = &_s;
  OfrontOPS_str = NIL;
  OfrontOPM_Get(&OfrontOPS_ch);
  if (OfrontOPS_ch != '@') {
    for (;;) {
      for (;;) {
        while (OfrontOPS_ch == '(') {
          OfrontOPM_GetNoChk(&OfrontOPS_ch);
          if (OfrontOPS_ch == '*') {
            if (__4()) {
            }
          }
        }
        if (OfrontOPS_ch == '*') {
          OfrontOPM_GetNoChk(&OfrontOPS_ch);
          break;
        }
        if (OfrontOPS_ch == 0x00) {
          break;
        }
        OfrontOPM_GetNoChk(&OfrontOPS_ch);
      }
      if (OfrontOPS_ch == ')') {
        OfrontOPM_GetNoChk(&OfrontOPS_ch);
        break;
      }
      if (OfrontOPS_ch == 0x00) {
        OfrontOPS_err(5);
        break;
      }
    }
    __retval = 1;
    __4__5_s = _s.lnk;
    ;
    return __retval;
  }
  n = 0;
  OfrontOPS_str = __NEWARR(NIL, 1, 1, 1, 1, (SYSTEM_ARRLEN)1024);
  for (;;) {
    OfrontOPM_Get(&OfrontOPS_ch);
    if (OfrontOPS_ch == '*') {
      OfrontOPM_Get(&OfrontOPS_ch);
      if (OfrontOPS_ch == ')') {
        OfrontOPM_Get(&OfrontOPS_ch);
        (OfrontOPS_str->data)[__X(n, OfrontOPS_str->len[0], (CHAR*)"OfrontOPS", 111407)] = 0x00;
        break;
      }
      __6(n + 1);
      (OfrontOPS_str->data)[__X(n, OfrontOPS_str->len[0], (CHAR*)"OfrontOPS", 111652)] = '*';
      n += 1;
    }
    if (OfrontOPS_ch == 0x00) {
      OfrontOPS_err(5);
      (OfrontOPS_str->data)[__X(n, OfrontOPS_str->len[0], (CHAR*)"OfrontOPS", 112173)] = 0x00;
      break;
    }
    __6(n + 1);
    (OfrontOPS_str->data)[__X(n, OfrontOPS_str->len[0], (CHAR*)"OfrontOPS", 112425)] = (CHAR)OfrontOPS_ch;
    n += 1;
  }
  __retval = 0;
  __4__5_s = _s.lnk;
  ;
  return __retval;
}

void OfrontOPS_Get (BYTE *sym)
{
  BYTE s;
  struct Get__3 _s;
  _s.lnk = Get__3_s;
  Get__3_s = &_s;
  OfrontOPM_errpos = OfrontOPM_curpos - 1;
  while (OfrontOPS_ch <= ' ') {
    if (OfrontOPS_ch == 0x00) {
      *sym = 71;
      Get__3_s = _s.lnk;
      return;
    } else {
      OfrontOPM_Get(&OfrontOPS_ch);
    }
  }
  switch (OfrontOPS_ch) {
    case '\"': case '\'': 
      OfrontOPS_Str(&s);
      break;
    case '#': 
      s = 12;
      OfrontOPM_Get(&OfrontOPS_ch);
      break;
    case '&': 
      s = 7;
      OfrontOPM_Get(&OfrontOPS_ch);
      break;
    case '(': 
      OfrontOPM_Get(&OfrontOPS_ch);
      if (OfrontOPS_ch == '*') {
        if (!__4()) {
          *sym = 70;
          Get__3_s = _s.lnk;
          return;
        }
        OfrontOPS_Get(&s);
      } else {
        s = 32;
      }
      break;
    case ')': 
      s = 24;
      OfrontOPM_Get(&OfrontOPS_ch);
      break;
    case '*': 
      s = 1;
      OfrontOPM_Get(&OfrontOPS_ch);
      break;
    case '+': 
      s = 8;
      OfrontOPM_Get(&OfrontOPS_ch);
      break;
    case ',': 
      s = 21;
      OfrontOPM_Get(&OfrontOPS_ch);
      break;
    case '-': 
      s = 9;
      OfrontOPM_Get(&OfrontOPS_ch);
      break;
    case '.': 
      OfrontOPM_Get(&OfrontOPS_ch);
      if (OfrontOPS_ch == '.') {
        OfrontOPM_Get(&OfrontOPS_ch);
        s = 23;
      } else {
        s = 20;
      }
      break;
    case '/': 
      s = 2;
      OfrontOPM_Get(&OfrontOPS_ch);
      break;
    case '0': case '1': case '2': case '3': case '4': 
    case '5': case '6': case '7': case '8': case '9': 
      OfrontOPS_Number();
      s = 37;
      break;
    case ':': 
      OfrontOPM_Get(&OfrontOPS_ch);
      if (OfrontOPS_ch == '=') {
        OfrontOPM_Get(&OfrontOPS_ch);
        s = 36;
      } else {
        s = 22;
      }
      break;
    case ';': 
      s = 41;
      OfrontOPM_Get(&OfrontOPS_ch);
      break;
    case '<': 
      OfrontOPM_Get(&OfrontOPS_ch);
      if (OfrontOPS_ch == '=') {
        OfrontOPM_Get(&OfrontOPS_ch);
        s = 14;
      } else {
        s = 13;
      }
      break;
    case '=': 
      s = 11;
      OfrontOPM_Get(&OfrontOPS_ch);
      break;
    case '>': 
      OfrontOPM_Get(&OfrontOPS_ch);
      if (OfrontOPS_ch == '=') {
        OfrontOPM_Get(&OfrontOPS_ch);
        s = 16;
      } else {
        s = 15;
      }
      break;
    case '@': 
      s = 69;
      OfrontOPM_Get(&OfrontOPS_ch);
      break;
    case 'A': case 'B': case 'C': case 'D': case 'E': 
    case 'F': case 'G': case 'H': case 'I': case 'J': 
    case 'K': case 'L': case 'M': case 'N': case 'O': 
    case 'P': case 'Q': case 'R': case 'S': case 'T': 
    case 'U': case 'V': case 'W': case 'X': case 'Y': 
    case 'Z': case 'a': case 'b': case 'c': case 'd': 
    case 'e': case 'f': case 'g': case 'h': case 'i': 
    case 'j': case 'k': case 'l': case 'm': case 'n': 
    case 'o': case 'p': case 'q': case 'r': case 's': 
    case 't': case 'u': case 'v': case 'w': case 'x': 
    case 'y': case 'z': case '_': 
      OfrontOPS_Identifier(&s);
      break;
    case '[': 
      s = 33;
      OfrontOPM_Get(&OfrontOPS_ch);
      break;
    case ']': 
      s = 25;
      OfrontOPM_Get(&OfrontOPS_ch);
      break;
    case '^': 
      s = 19;
      OfrontOPM_Get(&OfrontOPS_ch);
      break;
    case '$': 
      s = 67;
      OfrontOPM_Get(&OfrontOPS_ch);
      break;
    case '{': 
      s = 34;
      OfrontOPM_Get(&OfrontOPS_ch);
      break;
    case '|': 
      s = 42;
      OfrontOPM_Get(&OfrontOPS_ch);
      break;
    case '}': 
      s = 26;
      OfrontOPM_Get(&OfrontOPS_ch);
      break;
    case '~': 
      s = 35;
      OfrontOPM_Get(&OfrontOPS_ch);
      break;
    case 0x7f: 
      s = 23;
      OfrontOPM_Get(&OfrontOPS_ch);
      break;
    default: 
      s = 0;
      OfrontOPM_Get(&OfrontOPS_ch);
      break;
  }
  *sym = s;
  Get__3_s = _s.lnk;
}

/*----------------------------------------------------------------------------*/
void OfrontOPS_Init (void)
{
  OfrontOPS_checkKeyword = OfrontOPS_AutoKeywords;
  OfrontOPS_lowcase = 0;
  OfrontOPS_ch = ' ';
}

/*----------------------------------------------------------------------------*/
static void EnumPtrs(void (*P)(void*))
{
  P(OfrontOPS_str);
  P(OfrontOPS_lstr);
}


export void *OfrontOPS__init (void)
{
  __DEFMOD;
  __IMPORT(OfrontOPM__init);
  __REGMOD("OfrontOPS", EnumPtrs);
  __REGCMD("Init", OfrontOPS_Init);
/* BEGIN */
  __ENDMOD;
}
