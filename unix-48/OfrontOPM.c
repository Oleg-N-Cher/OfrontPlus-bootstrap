/* Ofront+ 1.0 -sC -48 */
#include "SYSTEM.oh"
#include "Texts.oh"
#include "Files.oh"
#include "Platform.oh"
#include "Strings.oh"
#include "CmdArgs.oh"
#include "Console.oh"
#include "OfrontErrors.oh"

typedef
  CHAR OfrontOPM_FileName[36];


static BOOLEAN OfrontOPM_LEHost;
export REAL OfrontOPM_MinReal32, OfrontOPM_MaxReal32, OfrontOPM_InfReal, OfrontOPM_MinReal64, OfrontOPM_MaxReal64;
export SHORTINT OfrontOPM_SetSize, OfrontOPM_IndexSize, OfrontOPM_MaxSet;
export LONGINT OfrontOPM_MaxIndex;
export BOOLEAN OfrontOPM_noerr, OfrontOPM_warning156;
export INTEGER OfrontOPM_curpos;
export INTEGER OfrontOPM_errpos;
export INTEGER OfrontOPM_breakpc;
export INTEGER OfrontOPM_currFile, OfrontOPM_level;
export INTEGER OfrontOPM_pc, OfrontOPM_entno;
export CHAR OfrontOPM_modName[32];
export CHAR OfrontOPM_objname[64];
export INTEGER OfrontOPM_checksum;
export SET OfrontOPM_opt;
static SET OfrontOPM_glbopt;
static CHAR OfrontOPM_GlobalLang;
export CHAR OfrontOPM_Lang;
static SHORTINT OfrontOPM_GlobalAdrSize;
export SHORTINT OfrontOPM_AdrSize;
static SHORTINT OfrontOPM_GlobalAlignment;
export SHORTINT OfrontOPM_Alignment;
static INTEGER OfrontOPM_crc32tab[256];
static INTEGER OfrontOPM_lasterrpos;
static Texts_Reader OfrontOPM_inR;
static Texts_Text OfrontOPM_Log;
static Texts_Writer OfrontOPM_W;
static Files_Rider OfrontOPM_oldSF, OfrontOPM_newSF;
static Files_Rider OfrontOPM_R[3];
static Files_File OfrontOPM_oldSFile, OfrontOPM_newSFile, OfrontOPM_HFile, OfrontOPM_BFile, OfrontOPM_HIFile;
static INTEGER OfrontOPM_S;
static BOOLEAN OfrontOPM_stop;
static CHAR OfrontOPM_OBERON[1024];


static void OfrontOPM_Append (Files_Rider *R, void **R__typ, Files_File F);
static void OfrontOPM_ChkSum (INTEGER *fp, INTEGER val);
export void OfrontOPM_CloseFiles (void);
export void OfrontOPM_CloseOldSym (void);
static REAL OfrontOPM_Compound (INTEGER lo, INTEGER hi);
export void OfrontOPM_DeleteNewSym (void);
export LONGINT OfrontOPM_Div0 (LONGINT x, LONGINT y);
export void OfrontOPM_FPrint (INTEGER *fp, INTEGER val);
export void OfrontOPM_FPrintLReal (INTEGER *fp, REAL lr);
export void OfrontOPM_FPrintReal (INTEGER *fp, SHORTREAL real);
export void OfrontOPM_FPrintSet (INTEGER *fp, SET set);
export void OfrontOPM_Get (LONGCHAR *longch);
static void OfrontOPM_GetCh (LONGCHAR *longch, BOOLEAN chk);
export void OfrontOPM_GetNoChk (LONGCHAR *longch);
static void OfrontOPM_GetProperties (void);
export void OfrontOPM_GetUtf8 (CHAR *str, INTEGER str__len, INTEGER *val, INTEGER *idx);
static INTEGER OfrontOPM_HiWord (REAL *r);
export void OfrontOPM_Init (CHAR *msg, INTEGER msg__len, BOOLEAN *done);
static void OfrontOPM_InitCrcTab (void);
static void OfrontOPM_InitHost (void);
export void OfrontOPM_InitOptions (void);
export REAL OfrontOPM_IntPower (REAL x, INTEGER n);
static INTEGER OfrontOPM_LoWord (REAL *r);
static void OfrontOPM_LogErrMsg (SHORTINT n);
export void OfrontOPM_LogW (CHAR ch);
export void OfrontOPM_LogWLn (void);
export void OfrontOPM_LogWNum (INTEGER i, INTEGER len);
export void OfrontOPM_LogWStr (CHAR *s, INTEGER s__len);
export LONGINT OfrontOPM_Lsl (LONGINT x, INTEGER n);
export LONGINT OfrontOPM_Lsr (LONGINT x, INTEGER n);
static void OfrontOPM_MakeFileName (CHAR *name, INTEGER name__len, CHAR *FName, INTEGER FName__len, CHAR *ext, INTEGER ext__len);
export void OfrontOPM_Mark (SHORTINT n, INTEGER pos);
export void OfrontOPM_NewSym (CHAR *modName, INTEGER modName__len);
export void OfrontOPM_OldSym (CHAR *modName, INTEGER modName__len, BOOLEAN *done);
export void OfrontOPM_OpenFiles (CHAR *moduleName, INTEGER moduleName__len);
export void OfrontOPM_OpenPar (CHAR *title, INTEGER title__len, CHAR *cmd, INTEGER cmd__len);
export void OfrontOPM_PromoteIntConstToLInt (void);
export void OfrontOPM_PutUtf8 (CHAR *str, INTEGER str__len, INTEGER val, INTEGER *idx);
static void OfrontOPM_ReadInt32 (INTEGER *i);
export void OfrontOPM_RegisterNewSym (void);
export LONGINT OfrontOPM_Rem0 (LONGINT x, LONGINT y);
export LONGINT OfrontOPM_Ror (LONGINT x, INTEGER n);
static void OfrontOPM_ScanOptions (CHAR *s, INTEGER s__len, SET *opt);
export void OfrontOPM_SymRCh (CHAR *ch);
export LONGINT OfrontOPM_SymRInt (void);
export void OfrontOPM_SymRLReal (REAL *lr);
export void OfrontOPM_SymRReal (SHORTREAL *r);
export void OfrontOPM_SymRSet (SET *s);
export void OfrontOPM_SymWCh (CHAR ch);
export void OfrontOPM_SymWInt (LONGINT x);
export void OfrontOPM_SymWLReal (REAL lr);
export void OfrontOPM_SymWReal (SHORTREAL r);
export void OfrontOPM_SymWSet (SET s);
export LONGINT OfrontOPM_UDiv (LONGINT x, LONGINT y);
export void OfrontOPM_Write (CHAR ch);
export void OfrontOPM_WriteHex (INTEGER i);
export void OfrontOPM_WriteInt (LONGINT i);
static void OfrontOPM_WriteInt32 (INTEGER i);
export void OfrontOPM_WriteLn (void);
export void OfrontOPM_WriteModPos (void);
export void OfrontOPM_WriteReal (REAL r, CHAR suffx);
export void OfrontOPM_WriteString (CHAR *s, INTEGER s__len);
export void OfrontOPM_WriteTab (void);
export BOOLEAN OfrontOPM_eofSF (void);
export void OfrontOPM_err (SHORTINT n);

#define OfrontOPM_GetAlignment(a)  struct {char c; long long l;} _s; *a = (char*)&_s.l - (char*)&_s
#define OfrontOPM_udiv(x, y)  ((__U_LONGINT)(x) / (__U_LONGINT)(y))

/*============================================================================*/

LONGINT OfrontOPM_UDiv (LONGINT x, LONGINT y)
{
  __ASSERT(y != 0, 0, (CHAR*)"OfrontOPM", 34319);
  return OfrontOPM_udiv(x, y);
}

/*----------------------------------------------------------------------------*/
LONGINT OfrontOPM_Div0 (LONGINT x, LONGINT y)
{
  __ASSERT(y != 0, 0, (CHAR*)"OfrontOPM", 35599);
  return x / y;
}

/*----------------------------------------------------------------------------*/
LONGINT OfrontOPM_Rem0 (LONGINT x, LONGINT y)
{
  __ASSERT(y != 0, 0, (CHAR*)"OfrontOPM", 36879);
  return x % y;
}

/*----------------------------------------------------------------------------*/
LONGINT OfrontOPM_Lsl (LONGINT x, INTEGER n)
{
  __ASSERT(0 <= n && n <= 63, 0, (CHAR*)"OfrontOPM", 38174);
  return __LSH(x, n, LONGINT);
}

/*----------------------------------------------------------------------------*/
LONGINT OfrontOPM_Lsr (LONGINT x, INTEGER n)
{
  __ASSERT(0 <= n && n <= 63, 0, (CHAR*)"OfrontOPM", 39710);
  return __LSH(x, -n, LONGINT);
}

/*----------------------------------------------------------------------------*/
LONGINT OfrontOPM_Ror (LONGINT x, INTEGER n)
{
  __ASSERT(0 <= n && n <= 63, 0, (CHAR*)"OfrontOPM", 41246);
  return __ROT(x, -n, LONGINT);
}

/*----------------------------------------------------------------------------*/
REAL OfrontOPM_IntPower (REAL x, INTEGER n)
{
  REAL y;
  if (n == (-2147483647-1)) {
    return OfrontOPM_IntPower(x, n + 1) / x;
  }
  y = (REAL)1;
  if (n < 0) {
    x = (REAL)1 / x;
    n = -n;
  }
  while (n > 0) {
    if (__ODD(n)) {
      y = y * x;
      n -= 1;
    } else {
      x = x * x;
      n = __ASHR(n, 1, INTEGER);
    }
  }
  return y;
}

/*----------------------------------------------------------------------------*/
static void OfrontOPM_ChkSum (INTEGER *fp, INTEGER val)
{
  *fp = (INTEGER)((SET)__ASHL(*fp, 8, INTEGER) ^ (SET)OfrontOPM_crc32tab[__X(__MASK((INTEGER)((SET)__ASHR(*fp, 24, INTEGER) ^ (SET)val), -256), 256, (CHAR*)"OfrontOPM", 46847)]);
}

static INTEGER OfrontOPM_LoWord (REAL *r)
{
  INTEGER x, adr;
  adr = (SYSTEM_ADRINT)r;
  if (!OfrontOPM_LEHost) {
    adr += 4;
  }
  __GET(adr, x, INTEGER);
  return x;
}

static INTEGER OfrontOPM_HiWord (REAL *r)
{
  INTEGER x, adr;
  adr = (SYSTEM_ADRINT)r;
  if (OfrontOPM_LEHost) {
    adr += 4;
  }
  __GET(adr, x, INTEGER);
  return x;
}

static REAL OfrontOPM_Compound (INTEGER lo, INTEGER hi)
{
  REAL r;
  if (OfrontOPM_LEHost) {
    __PUT((SYSTEM_ADRINT)&r, lo, INTEGER);
    __PUT((SYSTEM_ADRINT)&r + 4, hi, INTEGER);
  } else {
    __PUT((SYSTEM_ADRINT)&r + 4, lo, INTEGER);
    __PUT((SYSTEM_ADRINT)&r, hi, INTEGER);
  }
  return r;
}

void OfrontOPM_PutUtf8 (CHAR *str, INTEGER str__len, INTEGER val, INTEGER *idx)
{
  __ASSERT(val >= 0 && val < 65536, 0, (CHAR*)"OfrontOPM", 56356);
  if (val < 128) {
    str[__X(*idx, str__len, (CHAR*)"OfrontOPM", 56862)] = (CHAR)val;
    *idx += 1;
  } else if (val < 2048) {
    str[__X(*idx, str__len, (CHAR*)"OfrontOPM", 57387)] = (CHAR)(__ASHR(val, 6, INTEGER) + 192);
    *idx += 1;
    str[__X(*idx, str__len, (CHAR*)"OfrontOPM", 57643)] = (CHAR)(__MASK(val, -64) + 128);
    *idx += 1;
  } else {
    str[__X(*idx, str__len, (CHAR*)"OfrontOPM", 58157)] = (CHAR)(__ASHR(val, 12, INTEGER) + 224);
    *idx += 1;
    str[__X(*idx, str__len, (CHAR*)"OfrontOPM", 58418)] = (CHAR)(__MASK(__ASHR(val, 6, INTEGER), -64) + 128);
    *idx += 1;
    str[__X(*idx, str__len, (CHAR*)"OfrontOPM", 58667)] = (CHAR)(__MASK(val, -64) + 128);
    *idx += 1;
  }
}

/*----------------------------------------------------------------------------*/
void OfrontOPM_GetUtf8 (CHAR *str, INTEGER str__len, INTEGER *val, INTEGER *idx)
{
  CHAR ch;
  ch = str[__X(*idx, str__len, (CHAR*)"OfrontOPM", 60432)];
  *idx += 1;
  if (ch < 0x80) {
    *val = (SHORTINT)ch;
  } else if (ch < 0xe0) {
    *val = (INTEGER)ch - 192;
    ch = str[__X(*idx, str__len, (CHAR*)"OfrontOPM", 61713)];
    *idx += 1;
    *val = (__ASHL(*val, 6, INTEGER) + (INTEGER)ch) - 128;
  } else {
    *val = (INTEGER)ch - 224;
    ch = str[__X(*idx, str__len, (CHAR*)"OfrontOPM", 62481)];
    *idx += 1;
    *val = (__ASHL(*val, 6, INTEGER) + (INTEGER)ch) - 128;
    ch = str[__X(*idx, str__len, (CHAR*)"OfrontOPM", 62737)];
    *idx += 1;
    *val = (__ASHL(*val, 6, INTEGER) + (INTEGER)ch) - 128;
  }
}

/*----------------------------------------------------------------------------*/
void OfrontOPM_LogW (CHAR ch)
{
  Console_Char(ch);
}

/*----------------------------------------------------------------------------*/
void OfrontOPM_LogWStr (CHAR *s, INTEGER s__len)
{
  Console_String((void*)s, s__len);
}

/*----------------------------------------------------------------------------*/
void OfrontOPM_LogWNum (INTEGER i, INTEGER len)
{
  Console_Int(i, len);
}

/*----------------------------------------------------------------------------*/
void OfrontOPM_LogWLn (void)
{
  Console_Ln();
}

/*----------------------------------------------------------------------------*/
static void OfrontOPM_GetProperties (void)
{
  OfrontOPM_warning156 = (INTEGER)OfrontOPM_AdrSize == -1;
  if (OfrontOPM_warning156) {
    OfrontOPM_AdrSize = 4;
    OfrontOPM_GetAlignment(&OfrontOPM_Alignment);
  }
  if ((INTEGER)OfrontOPM_AdrSize == 2) {
    OfrontOPM_SetSize = OfrontOPM_Alignment;
    OfrontOPM_MaxSet = (SHORTINT)(__ASHL((INTEGER)OfrontOPM_SetSize, 3, INTEGER) - 1);
    OfrontOPM_IndexSize = 2;
    OfrontOPM_MaxIndex = 32767;
  } else {
    OfrontOPM_SetSize = 4;
    OfrontOPM_MaxSet = 31;
    OfrontOPM_IndexSize = 4;
    OfrontOPM_MaxIndex = 2147483647;
  }
}

static void OfrontOPM_ScanOptions (CHAR *s, INTEGER s__len, SET *opt)
{
  INTEGER i;
  i = 1;
  while (s[__X(i, s__len, (CHAR*)"OfrontOPM", 75793)] != 0x00) {
    switch (s[__X(i, s__len, (CHAR*)"OfrontOPM", 76044)]) {
      case 'e': 
        *opt = *opt ^ 0x0200;
        break;
      case 's': 
        *opt = *opt ^ 0x10;
        break;
      case 'm': 
        *opt = *opt ^ 0x0400;
        break;
      case 'x': 
        *opt = *opt ^ 0x01;
        break;
      case 'v': 
        *opt = *opt ^ 0x02;
        break;
      case 'r': 
        *opt = *opt ^ 0x04;
        break;
      case 't': 
        *opt = *opt ^ 0x08;
        break;
      case 'a': 
        *opt = *opt ^ 0x80;
        break;
      case 'k': 
        *opt = *opt ^ 0x40;
        break;
      case 'p': 
        *opt = *opt ^ 0x20;
        break;
      case 'i': 
        *opt = *opt ^ 0x0100;
        break;
      case 'd': 
        *opt = *opt ^ 0x0800;
        break;
      case 'f': 
        *opt = *opt ^ 0x1000;
        break;
      case 'o': 
        *opt = *opt ^ 0x2000;
        break;
      case 'w': 
        *opt = *opt ^ 0x040000;
        break;
      case '1': case '3': case 'C': case '7': 
        OfrontOPM_Lang = s[__X(i, s__len, (CHAR*)"OfrontOPM", 80383)];
        break;
      case 'G': 
        *opt = *opt ^ 0x010000;
        break;
      case 'O': 
        *opt = *opt ^ 0x020000;
        break;
      case '2': 
        if (s[__X(i + 1, s__len, (CHAR*)"OfrontOPM", 83711)] == '1') {
          OfrontOPM_AdrSize = 2;
          OfrontOPM_Alignment = 1;
          i += 1;
        } else if (s[__X(i + 1, s__len, (CHAR*)"OfrontOPM", 82943)] == '2') {
          OfrontOPM_AdrSize = 2;
          OfrontOPM_Alignment = 2;
          i += 1;
        } else {
          OfrontOPM_Lang = '2';
        }
        break;
      case '4': 
        if (s[__X(i + 1, s__len, (CHAR*)"OfrontOPM", 85759)] == '4') {
          OfrontOPM_AdrSize = 4;
          OfrontOPM_Alignment = 4;
          i += 1;
        } else if (s[__X(i + 1, s__len, (CHAR*)"OfrontOPM", 84223)] == '8') {
          OfrontOPM_AdrSize = 4;
          OfrontOPM_Alignment = 8;
          i += 1;
        } else {
          OfrontOPM_LogWStr((CHAR*)"  warning: option ", 19);
          OfrontOPM_LogW('-');
          OfrontOPM_LogW('4');
          if (s[__X(i + 1, s__len, (CHAR*)"OfrontOPM", 85041)] != 0x00) {
            OfrontOPM_LogW(s[__X(i + 1, s__len, (CHAR*)"OfrontOPM", 85029)]);
            i += 1;
          }
          OfrontOPM_LogWStr((CHAR*)" ignored", 9);
          OfrontOPM_LogWLn();
        }
        break;
      case '8': 
        if (s[__X(i + 1, s__len, (CHAR*)"OfrontOPM", 87551)] == '8') {
          OfrontOPM_AdrSize = 8;
          OfrontOPM_Alignment = 8;
          i += 1;
        } else {
          OfrontOPM_LogWStr((CHAR*)"  warning: option ", 19);
          OfrontOPM_LogW('-');
          OfrontOPM_LogW('8');
          if (s[__X(i + 1, s__len, (CHAR*)"OfrontOPM", 86833)] != 0x00) {
            OfrontOPM_LogW(s[__X(i + 1, s__len, (CHAR*)"OfrontOPM", 86821)]);
            i += 1;
          }
          OfrontOPM_LogWStr((CHAR*)" ignored", 9);
          OfrontOPM_LogWLn();
        }
        break;
      default: 
        OfrontOPM_LogWStr((CHAR*)"  warning: option ", 19);
        OfrontOPM_LogW('-');
        OfrontOPM_LogW(s[__X(i, s__len, (CHAR*)"OfrontOPM", 87619)]);
        OfrontOPM_LogWStr((CHAR*)" ignored", 9);
        OfrontOPM_LogWLn();
        break;
    }
    i += 1;
  }
  if ((0x42 & *opt) == 0x02) {
    *opt |= __SETOF(6);
    OfrontOPM_LogWStr((CHAR*)"  warning: option ", 19);
    OfrontOPM_LogW('-');
    OfrontOPM_LogWStr((CHAR*)"k ignored", 10);
    OfrontOPM_LogWLn();
  }
}

void OfrontOPM_OpenPar (CHAR *title, INTEGER title__len, CHAR *cmd, INTEGER cmd__len)
{
  CHAR s[256];
  if (CmdArgs_Count == 0) {
    OfrontOPM_stop = 1;
    Console_Ln();
    Console_String((void*)title, title__len);
    Console_Ln();
    Console_String((CHAR*)"Copyright (c) Software Templ OG, 1995-2020 & VEDAsoft Oberon Club, 2013-2025", 77);
    Console_Ln();
    Console_Ln();
    Console_String((CHAR*)"  command = \"", 14);
    Console_String((void*)cmd, cmd__len);
    Console_String((CHAR*)"\" options {file options}.", 26);
    Console_Ln();
    Console_String((CHAR*)"  options = [\"-\" {option} ].", 29);
    Console_Ln();
    Console_String((CHAR*)"  option  = \"m\" | \"s\" | \"e\" | \"i\" | \"r\" | \"x\" | \"a\" | \"p\" | \"t\" | \"f\" | \"d\"", 76);
    Console_Ln();
    Console_String((CHAR*)"            [ \"1\" | \"2\" | \"C\" | \"7\" | \"3\" ]    [ \"21\" |\"44\" |\"48\" | \"88\" ].", 76);
    Console_Ln();
    Console_String((CHAR*)"       \"m\": generate a main module                                  (off)", 74);
    Console_Ln();
    Console_String((CHAR*)"       \"s\": allow changing the symbol file                          (off)", 74);
    Console_Ln();
    Console_String((CHAR*)"       \"e\": allow extending the module interface                    (off)", 74);
    Console_Ln();
    Console_String((CHAR*)"       \"i\": include header and body prefix files (Module.h0/.c0)    (off)", 74);
    Console_Ln();
    Console_String((CHAR*)"       \"r\": check value ranges                                      (off)", 74);
    Console_Ln();
    Console_String((CHAR*)"       \"x\": check array indices                                      (on)", 74);
    Console_Ln();
    Console_String((CHAR*)"       \"a\": check assertions                                         (on)", 74);
    Console_Ln();
    Console_String((CHAR*)"       \"p\": pointer initialization                                   (on)", 74);
    Console_Ln();
    Console_String((CHAR*)"       \"t\": check type guards                                        (on)", 74);
    Console_Ln();
    Console_String((CHAR*)"       \"f\": allow \"proper FOR\" (concept by Oleg Komlev)             (off)", 74);
    Console_Ln();
    Console_String((CHAR*)"       \"d\": translate a module into dynamic library (.dll/.so)      (off)", 74);
    Console_Ln();
    Console_String((CHAR*)"       \"w\": UTF-8 to UCS-2 wide character transcoding enabled       (off)", 74);
    Console_Ln();
    Console_String((CHAR*)"  \"1\": Oberon \"2\": Oberon-2 \"C\": Component Pascal \"7\": Oberon-07 \"3\": Oberon-3", 79);
    Console_Ln();
    Console_String((CHAR*)"  \"21\": 16-bit addresses, SIZE(SET) = 1 byte (e.g. Zilog Z80 CPU)", 66);
    Console_Ln();
    Console_String((CHAR*)"  \"44\": 32-bit addresses, 32-bit alignment (32-bit UNIX/Linux on x86)", 70);
    Console_Ln();
    Console_String((CHAR*)"  \"48\": 32-bit addresses, 64-bit alignment (32-bit Windows, 32-bit Linux/ARMv7)", 80);
    Console_Ln();
    Console_String((CHAR*)"  \"88\": 64-bit addresses, 64-bit alignment (64-bit platforms)", 62);
    Console_Ln();
  } else {
    OfrontOPM_Lang = 'C';
    OfrontOPM_AdrSize = -1;
    OfrontOPM_glbopt = 0xe9;
    OfrontOPM_S = 1;
    CmdArgs_Get(1, (void*)s, 256);
    OfrontOPM_stop = 0;
    while (s[0] == '-') {
      OfrontOPM_ScanOptions((void*)s, 256, &OfrontOPM_glbopt);
      OfrontOPM_S += 1;
      CmdArgs_Get(OfrontOPM_S, (void*)s, 256);
    }
    OfrontOPM_GlobalAdrSize = OfrontOPM_AdrSize;
    OfrontOPM_GlobalAlignment = OfrontOPM_Alignment;
    OfrontOPM_GlobalLang = OfrontOPM_Lang;
  }
}

/*----------------------------------------------------------------------------*/
void OfrontOPM_InitOptions (void)
{
  CHAR s[256];
  OfrontOPM_Alignment = OfrontOPM_GlobalAlignment;
  OfrontOPM_AdrSize = OfrontOPM_GlobalAdrSize;
  OfrontOPM_opt = OfrontOPM_glbopt;
  CmdArgs_Get(OfrontOPM_S, (void*)s, 256);
  while (s[0] == '-') {
    OfrontOPM_ScanOptions((void*)s, 256, &OfrontOPM_opt);
    OfrontOPM_S += 1;
    CmdArgs_Get(OfrontOPM_S, (void*)s, 256);
  }
  OfrontOPM_curpos = 256;
  OfrontOPM_errpos = OfrontOPM_curpos;
  OfrontOPM_lasterrpos = OfrontOPM_curpos - 10;
  OfrontOPM_GetProperties();
}

/*----------------------------------------------------------------------------*/
void OfrontOPM_Init (CHAR *msg, INTEGER msg__len, BOOLEAN *done)
{
  Texts_Text T = NIL;
  INTEGER endpos;
  CHAR s[256];
  *done = 0;
  OfrontOPM_curpos = 0;
  if (OfrontOPM_stop || OfrontOPM_S > CmdArgs_Count) {
    OfrontOPM_noerr = 1;
    return;
  }
  CmdArgs_Get(OfrontOPM_S, (void*)s, 256);
  endpos = __STRLEN(s, 256, (CHAR*)"OfrontOPM", 104727) - 4;
  if (Strings_Pos((CHAR*)".ob1", 5, (void*)s, 256, 1) == endpos) {
    OfrontOPM_Lang = '1';
  } else if (Strings_Pos((CHAR*)".ob2", 5, (void*)s, 256, 1) == endpos) {
    OfrontOPM_Lang = '2';
  } else if (Strings_Pos((CHAR*)".ob3", 5, (void*)s, 256, 1) == endpos) {
    OfrontOPM_Lang = '3';
  } else if (Strings_Pos((CHAR*)".ob7", 5, (void*)s, 256, 1) == endpos) {
    OfrontOPM_Lang = '7';
  } else {
    OfrontOPM_Lang = OfrontOPM_GlobalLang;
  }
  __NEW(T, Texts_TextDesc);
  Texts_Open(T, (void*)s, 256);
  OfrontOPM_LogWStr((void*)s, 256);
  if (Files_Old((void*)s, 256) == NIL) {
    OfrontOPM_LogWStr((CHAR*)" not found", 11);
    OfrontOPM_LogWLn();
    OfrontOPM_noerr = 0;
  } else {
    Texts_OpenReader(&OfrontOPM_inR, Texts_Reader__typ, T, 0);
    OfrontOPM_LogWStr((CHAR*)"  ", 3);
    OfrontOPM_LogWStr((void*)msg, msg__len);
    *done = 1;
    OfrontOPM_noerr = 1;
  }
  OfrontOPM_S += 1;
  OfrontOPM_level = 0;
  OfrontOPM_errpos = OfrontOPM_curpos;
  OfrontOPM_lasterrpos = OfrontOPM_curpos - 10;
}

/*----------------------------------------------------------------------------*/
static void OfrontOPM_GetCh (LONGCHAR *longch, BOOLEAN chk)
{
  CHAR ch;
  if (!__IN(18, OfrontOPM_opt)) {
    Texts_Read(&OfrontOPM_inR, Texts_Reader__typ, &ch);
    *longch = ch;
  } else if (!Texts_ReadLong(&OfrontOPM_inR, Texts_Reader__typ, longch)) {
    *longch = '\?';
    if (chk) {
      OfrontOPM_err(-3);
    }
  }
  if (*longch == 0x0d) {
    OfrontOPM_curpos = __ASHL(__ASHR(OfrontOPM_curpos, 8, INTEGER) + 1, 8, INTEGER);
  } else if (__MASK(OfrontOPM_curpos, -256) != 255) {
    OfrontOPM_curpos += 1;
  }
  if (*longch < 0x09 && !OfrontOPM_inR.eot) {
    *longch = ' ';
  }
}

void OfrontOPM_Get (LONGCHAR *longch)
{
  OfrontOPM_GetCh(longch, 1);
}

/*----------------------------------------------------------------------------*/
void OfrontOPM_GetNoChk (LONGCHAR *longch)
{
  OfrontOPM_GetCh(longch, 0);
}

/*----------------------------------------------------------------------------*/
static void OfrontOPM_MakeFileName (CHAR *name, INTEGER name__len, CHAR *FName, INTEGER FName__len, CHAR *ext, INTEGER ext__len)
{
  INTEGER i, j;
  CHAR ch;
  i = 0;
  for (;;) {
    ch = name[__X(i, name__len, (CHAR*)"OfrontOPM", 117268)];
    if (ch == 0x00) {
      break;
    }
    FName[__X(i, FName__len, (CHAR*)"OfrontOPM", 117777)] = ch;
    i += 1;
  }
  j = 0;
  do {
    ch = ext[__X(j, ext__len, (CHAR*)"OfrontOPM", 118549)];
    FName[__X(i, FName__len, (CHAR*)"OfrontOPM", 118565)] = ch;
    i += 1;
    j += 1;
  } while (!(ch == 0x00));
}

static void OfrontOPM_LogErrMsg (SHORTINT n)
{
  if ((INTEGER)n >= 0) {
    OfrontOPM_LogWStr((CHAR*)"  err ", 7);
  } else {
    OfrontOPM_LogWStr((CHAR*)"  warning ", 11);
    n = (SHORTINT)(-((INTEGER)n));
  }
  OfrontOPM_LogWNum(n, 1);
  OfrontOPM_LogWStr((CHAR*)"  ", 3);
  OfrontErrors_LogErrMsg(n);
}

void OfrontOPM_Mark (SHORTINT n, INTEGER pos)
{
  if ((INTEGER)n >= 0) {
    OfrontOPM_noerr = 0;
    if (pos < OfrontOPM_lasterrpos || OfrontOPM_lasterrpos + 9 < pos) {
      OfrontOPM_lasterrpos = pos;
      OfrontOPM_LogWLn();
      OfrontOPM_LogWStr((CHAR*)"  ", 3);
      if ((INTEGER)n < 249) {
        OfrontOPM_LogWStr((CHAR*)"  ", 3);
        OfrontOPM_LogWNum(__ASHR(pos, 8, INTEGER), 1);
        OfrontOPM_LogW(':');
        OfrontOPM_LogWNum(__MASK(pos, -256) + 1, 1);
        OfrontOPM_LogErrMsg(n);
      } else if ((INTEGER)n == 255) {
        OfrontOPM_LogWStr((CHAR*)"  ", 3);
        OfrontOPM_LogWNum(__ASHR(pos, 8, INTEGER), 1);
        OfrontOPM_LogW(':');
        OfrontOPM_LogWNum(__MASK(pos, -256) + 1, 1);
        OfrontOPM_LogWStr((CHAR*)"  pc ", 6);
        OfrontOPM_LogWNum(OfrontOPM_breakpc, 1);
      } else if ((INTEGER)n == 254) {
        OfrontOPM_LogWStr((CHAR*)"pc not found", 13);
      } else {
        OfrontOPM_LogWStr((void*)OfrontOPM_objname, 64);
        if ((INTEGER)n == 253) {
          OfrontOPM_LogWStr((CHAR*)" is new, compile with option e", 31);
        } else if ((INTEGER)n == 252) {
          OfrontOPM_LogWStr((CHAR*)" is redefined, compile with option s", 37);
        } else if ((INTEGER)n == 251) {
          OfrontOPM_LogWStr((CHAR*)" is redefined (private part only), compile with option s", 57);
        } else if ((INTEGER)n == 250) {
          OfrontOPM_LogWStr((CHAR*)" is no longer visible, compile with option s", 45);
        } else if ((INTEGER)n == 249) {
          OfrontOPM_LogWStr((CHAR*)" is not consistently imported, recompile imports", 49);
        }
      }
    }
  } else {
    if (pos >= 0) {
      OfrontOPM_LogWLn();
      OfrontOPM_LogWStr((CHAR*)"  ", 3);
      OfrontOPM_LogWNum(__ASHR(pos, 8, INTEGER), 1);
      OfrontOPM_LogW(':');
      OfrontOPM_LogWNum(__MASK(pos, -256) + 1, 1);
    }
    OfrontOPM_LogErrMsg(n);
    if (pos < 0) {
      OfrontOPM_LogWLn();
    }
  }
}

/*----------------------------------------------------------------------------*/
void OfrontOPM_err (SHORTINT n)
{
  if (__MASK(OfrontOPM_errpos, -256) == 255) {
    OfrontOPM_Mark(n, OfrontOPM_errpos + 1);
  } else {
    OfrontOPM_Mark(n, OfrontOPM_errpos);
  }
}

/*----------------------------------------------------------------------------*/
static void OfrontOPM_InitCrcTab (void)
{
  INTEGER x, c, i;
  x = 0;
  while (x < 256) {
    c = __ASHL(x, 24, INTEGER);
    i = 0;
    while (i < 8) {
      if (c < 0) {
        c = (INTEGER)((SET)__ASHL(c, 1, INTEGER) ^ 0x04c11db7);
      } else {
        c = __ASHL(c, 1, INTEGER);
      }
      i += 1;
    }
    OfrontOPM_crc32tab[__X((INTEGER)((SET)x ^ 0xff), 256, (CHAR*)"OfrontOPM", 136001)] = (INTEGER)((SET)c ^ 0xff);
    x += 1;
  }
}

void OfrontOPM_FPrint (INTEGER *fp, INTEGER val)
{
  INTEGER c;
  c = (INTEGER)((SET)__ASHL(*fp, 8, INTEGER) ^ (SET)OfrontOPM_crc32tab[__X(__MASK((INTEGER)((SET)__ASHR(*fp, 24, INTEGER) ^ (SET)__ASHR(val, 24, INTEGER)), -256), 256, (CHAR*)"OfrontOPM", 138344)]);
  c = (INTEGER)((SET)__ASHL(c, 8, INTEGER) ^ (SET)OfrontOPM_crc32tab[__X(__MASK((INTEGER)((SET)__ASHR(c, 24, INTEGER) ^ (SET)__ASHR(val, 16, INTEGER)), -256), 256, (CHAR*)"OfrontOPM", 138596)]);
  c = (INTEGER)((SET)__ASHL(c, 8, INTEGER) ^ (SET)OfrontOPM_crc32tab[__X(__MASK((INTEGER)((SET)__ASHR(c, 24, INTEGER) ^ (SET)__ASHR(val, 8, INTEGER)), -256), 256, (CHAR*)"OfrontOPM", 138850)]);
  *fp = (INTEGER)((SET)__ASHL(c, 8, INTEGER) ^ (SET)OfrontOPM_crc32tab[__X(__MASK((INTEGER)((SET)__ASHR(c, 24, INTEGER) ^ (SET)val), -256), 256, (CHAR*)"OfrontOPM", 139263)]);
}

/*----------------------------------------------------------------------------*/
void OfrontOPM_FPrintSet (INTEGER *fp, SET set)
{
  OfrontOPM_FPrint(fp, (INTEGER)set);
}

/*----------------------------------------------------------------------------*/
void OfrontOPM_FPrintReal (INTEGER *fp, SHORTREAL real)
{
  OfrontOPM_FPrint(fp, __VAL(INTEGER, real));
}

/*----------------------------------------------------------------------------*/
void OfrontOPM_FPrintLReal (INTEGER *fp, REAL lr)
{
  OfrontOPM_FPrint(fp, OfrontOPM_LoWord(&lr));
  OfrontOPM_FPrint(fp, OfrontOPM_HiWord(&lr));
}

/*----------------------------------------------------------------------------*/
static void OfrontOPM_ReadInt32 (INTEGER *i)
{
  BYTE b;
  INTEGER x;
  Files_ReadByte(&OfrontOPM_oldSF, Files_Rider__typ, &b);
  x = __MASK((INTEGER)b, -256);
  OfrontOPM_ChkSum(&OfrontOPM_checksum, b);
  Files_ReadByte(&OfrontOPM_oldSF, Files_Rider__typ, &b);
  x = x + __ASHL(__MASK((INTEGER)b, -256), 8, INTEGER);
  OfrontOPM_ChkSum(&OfrontOPM_checksum, b);
  Files_ReadByte(&OfrontOPM_oldSF, Files_Rider__typ, &b);
  x = x + __ASHL(__MASK((INTEGER)b, -256), 16, INTEGER);
  OfrontOPM_ChkSum(&OfrontOPM_checksum, b);
  Files_ReadByte(&OfrontOPM_oldSF, Files_Rider__typ, &b);
  *i = x + __ASHL((INTEGER)b, 24, INTEGER);
  OfrontOPM_ChkSum(&OfrontOPM_checksum, b);
}

void OfrontOPM_SymRCh (CHAR *ch)
{
  Files_ReadChar(&OfrontOPM_oldSF, Files_Rider__typ, ch);
  OfrontOPM_ChkSum(&OfrontOPM_checksum, (BYTE)*ch);
}

/*----------------------------------------------------------------------------*/
LONGINT OfrontOPM_SymRInt (void)
{
  BYTE b;
  INTEGER s;
  LONGINT n;
  s = 0;
  n = 0;
  Files_ReadByte(&OfrontOPM_oldSF, Files_Rider__typ, &b);
  if (!OfrontOPM_oldSF.eof) {
    OfrontOPM_ChkSum(&OfrontOPM_checksum, b);
  }
  while ((INTEGER)b < 0) {
    n += __ASH((LONGINT)((INTEGER)b + 128), s, LONGINT);
    s += 7;
    Files_ReadByte(&OfrontOPM_oldSF, Files_Rider__typ, &b);
    OfrontOPM_ChkSum(&OfrontOPM_checksum, b);
  }
  n += __ASH((LONGINT)(__MASK((INTEGER)b + 64, -128) - 64), s, LONGINT);
  return n;
}

/*----------------------------------------------------------------------------*/
void OfrontOPM_SymRSet (SET *s)
{
  *s = (SET)((INTEGER)OfrontOPM_SymRInt());
}

/*----------------------------------------------------------------------------*/
void OfrontOPM_SymRReal (SHORTREAL *r)
{
  OfrontOPM_ReadInt32((INTEGER*)r);
}

/*----------------------------------------------------------------------------*/
void OfrontOPM_SymRLReal (REAL *lr)
{
  INTEGER h, l;
  OfrontOPM_ReadInt32(&l);
  OfrontOPM_ReadInt32(&h);
  *lr = OfrontOPM_Compound(l, h);
}

/*----------------------------------------------------------------------------*/
void OfrontOPM_CloseOldSym (void)
{
}

/*----------------------------------------------------------------------------*/
void OfrontOPM_OldSym (CHAR *modName, INTEGER modName__len, BOOLEAN *done)
{
  CHAR ch;
  OfrontOPM_FileName fileName;
  OfrontOPM_MakeFileName((void*)modName, modName__len, (void*)fileName, 36, (CHAR*)".sym", 5);
  OfrontOPM_oldSFile = Files_Old((void*)fileName, 36);
  *done = OfrontOPM_oldSFile != NIL;
  if (*done) {
    Files_Set(&OfrontOPM_oldSF, Files_Rider__typ, OfrontOPM_oldSFile, 0);
    Files_ReadChar(&OfrontOPM_oldSF, Files_Rider__typ, &ch);
    if (ch != 0xf7) {
      OfrontOPM_err(-306);
      OfrontOPM_CloseOldSym();
      *done = 0;
    }
  }
}

/*----------------------------------------------------------------------------*/
BOOLEAN OfrontOPM_eofSF (void)
{
  return OfrontOPM_oldSF.eof;
}

/*----------------------------------------------------------------------------*/
static void OfrontOPM_WriteInt32 (INTEGER i)
{
  OfrontOPM_ChkSum(&OfrontOPM_checksum, i);
  Files_WriteByte(&OfrontOPM_newSF, Files_Rider__typ, (BYTE)__MASK(i, -256));
  i = __ASHR(i, 8, INTEGER);
  OfrontOPM_ChkSum(&OfrontOPM_checksum, i);
  Files_WriteByte(&OfrontOPM_newSF, Files_Rider__typ, (BYTE)__MASK(i, -256));
  i = __ASHR(i, 8, INTEGER);
  OfrontOPM_ChkSum(&OfrontOPM_checksum, i);
  Files_WriteByte(&OfrontOPM_newSF, Files_Rider__typ, (BYTE)__MASK(i, -256));
  i = __ASHR(i, 8, INTEGER);
  OfrontOPM_ChkSum(&OfrontOPM_checksum, i);
  Files_WriteByte(&OfrontOPM_newSF, Files_Rider__typ, (BYTE)__MASK(i, -256));
}

void OfrontOPM_SymWCh (CHAR ch)
{
  OfrontOPM_ChkSum(&OfrontOPM_checksum, (SHORTINT)ch);
  Files_WriteChar(&OfrontOPM_newSF, Files_Rider__typ, ch);
}

/*----------------------------------------------------------------------------*/
void OfrontOPM_SymWInt (LONGINT x)
{
  while (x < -64 || x > 63) {
    OfrontOPM_ChkSum(&OfrontOPM_checksum, __MASK((INTEGER)x, -128) - 128);
    Files_WriteByte(&OfrontOPM_newSF, Files_Rider__typ, (BYTE)(__MASK((INTEGER)x, -128) - 128));
    x = __ASHR(x, 7, LONGINT);
  }
  OfrontOPM_ChkSum(&OfrontOPM_checksum, __MASK((INTEGER)x, -128));
  Files_WriteByte(&OfrontOPM_newSF, Files_Rider__typ, (BYTE)__MASK((INTEGER)x, -128));
}

/*----------------------------------------------------------------------------*/
void OfrontOPM_SymWSet (SET s)
{
  OfrontOPM_SymWInt((INTEGER)s);
}

/*----------------------------------------------------------------------------*/
void OfrontOPM_SymWReal (SHORTREAL r)
{
  OfrontOPM_WriteInt32(__VAL(INTEGER, r));
}

/*----------------------------------------------------------------------------*/
void OfrontOPM_SymWLReal (REAL lr)
{
  OfrontOPM_WriteInt32(OfrontOPM_LoWord(&lr));
  OfrontOPM_WriteInt32(OfrontOPM_HiWord(&lr));
}

/*----------------------------------------------------------------------------*/
void OfrontOPM_RegisterNewSym (void)
{
  if (__STRCMPCC(OfrontOPM_modName, (CHAR*)"SYSTEM", 7, (CHAR*)"OfrontOPM", 170239) != 0 || __IN(10, OfrontOPM_opt)) {
    Files_Register(OfrontOPM_newSFile);
  }
}

/*----------------------------------------------------------------------------*/
void OfrontOPM_DeleteNewSym (void)
{
}

/*----------------------------------------------------------------------------*/
void OfrontOPM_NewSym (CHAR *modName, INTEGER modName__len)
{
  OfrontOPM_FileName fileName;
  OfrontOPM_MakeFileName((void*)modName, modName__len, (void*)fileName, 36, (CHAR*)".sym", 5);
  OfrontOPM_newSFile = Files_New((void*)fileName, 36);
  if (OfrontOPM_newSFile != NIL) {
    Files_Set(&OfrontOPM_newSF, Files_Rider__typ, OfrontOPM_newSFile, 0);
    Files_WriteChar(&OfrontOPM_newSF, Files_Rider__typ, 0xf7);
  } else {
    OfrontOPM_err(153);
  }
}

/*----------------------------------------------------------------------------*/
void OfrontOPM_Write (CHAR ch)
{
  if (OfrontOPM_currFile != -1) {
    Files_WriteChar(&OfrontOPM_R[__X(OfrontOPM_currFile, 3, (CHAR*)"OfrontOPM", 174911)], Files_Rider__typ, ch);
  }
}

/*----------------------------------------------------------------------------*/
void OfrontOPM_WriteString (CHAR *s, INTEGER s__len)
{
  INTEGER i;
  if (OfrontOPM_currFile != -1) {
    i = __STRLEN(s, s__len, (CHAR*)"OfrontOPM", 176655);
    Files_WriteBytes(&OfrontOPM_R[__X(OfrontOPM_currFile, 3, (CHAR*)"OfrontOPM", 177151)], Files_Rider__typ, (void*)(SYSTEM_ADRINT)s, i, i);
  }
}

/*----------------------------------------------------------------------------*/
void OfrontOPM_WriteHex (INTEGER i)
{
  CHAR s[3];
  INTEGER digit;
  digit = __ASHR((INTEGER)((SHORTINT)i), 4, INTEGER);
  if (digit < 10) {
    s[0] = (CHAR)(48 + digit);
  } else {
    s[0] = (CHAR)(87 + digit);
  }
  digit = __MASK((INTEGER)((SHORTINT)i), -16);
  if (digit < 10) {
    s[1] = (CHAR)(48 + digit);
  } else {
    s[1] = (CHAR)(87 + digit);
  }
  s[2] = 0x00;
  OfrontOPM_WriteString((void*)s, 3);
}

/*----------------------------------------------------------------------------*/
void OfrontOPM_WriteInt (LONGINT i)
{
  CHAR s[20];
  LONGINT i1;
  INTEGER k;
  if (i == (-2147483647-1) || i == (-9223372036854775807LL-1)) {
    OfrontOPM_Write('(');
    OfrontOPM_WriteInt(i + 1);
    OfrontOPM_WriteString((CHAR*)"-1)", 4);
  } else {
    i1 = __ABS(i);
    s[0] = (CHAR)(__MOD(i1, 10) + 48);
    i1 = __DIV(i1, 10);
    k = 1;
    while (i1 > 0) {
      s[__X(k, 20, (CHAR*)"OfrontOPM", 184635)] = (CHAR)(__MOD(i1, 10) + 48);
      i1 = __DIV(i1, 10);
      k += 1;
    }
    if (i < 0) {
      s[__X(k, 20, (CHAR*)"OfrontOPM", 184860)] = '-';
      k += 1;
    }
    while (k > 0) {
      k -= 1;
      OfrontOPM_Write(s[__X(k, 20, (CHAR*)"OfrontOPM", 185126)]);
    }
    if (__IN(6, OfrontOPM_opt) && (i < (-2147483647-1) || i > 2147483647)) {
      OfrontOPM_WriteString((CHAR*)"LL", 3);
    }
  }
}

/*----------------------------------------------------------------------------*/
void OfrontOPM_WriteReal (REAL r, CHAR suffx)
{
  Texts_Writer W = {0};
  Texts_Text T = NIL;
  Texts_Reader R = {0};
  CHAR s[32];
  CHAR ch;
  INTEGER i;
  if (__ABS(r) > (4.9999999999999994e+307 * 2)) {
    OfrontOPM_Write('(');
    OfrontOPM_WriteReal(r / (REAL)(REAL)2, suffx);
    OfrontOPM_WriteString((CHAR*)" * 2)", 6);
    return;
  }
  if ((r < 9223372036854775600.0 && r > -9223372036854775600.0) && r == (REAL)(__ENTIERL(r))) {
    if (suffx == 'f') {
      OfrontOPM_WriteString((CHAR*)"(SHORTREAL)", 12);
    } else {
      OfrontOPM_WriteString((CHAR*)"(REAL)", 7);
    }
    OfrontOPM_WriteInt(__ENTIERL(r));
  } else {
    Texts_OpenWriter(&W, Texts_Writer__typ);
    if (suffx == 'f') {
      Texts_WriteLongReal(&W, Texts_Writer__typ, r, 8);
    } else {
      Texts_WriteLongReal(&W, Texts_Writer__typ, r, 17);
    }
    __NEW(T, Texts_TextDesc);
    Texts_Open(T, (CHAR*)"", 1);
    Texts_Append(T, W.buf);
    Texts_OpenReader(&R, Texts_Reader__typ, T, 0);
    i = 0;
    Texts_Read(&R, Texts_Reader__typ, &ch);
    while (ch != 0x00) {
      s[__X(i, 32, (CHAR*)"OfrontOPM", 189470)] = ch;
      i += 1;
      Texts_Read(&R, Texts_Reader__typ, &ch);
    }
    s[__X(i, 32, (CHAR*)"OfrontOPM", 190221)] = 0x00;
    i = 0;
    ch = s[0];
    while (ch != 'E' && ch != 0x00) {
      i += 1;
      ch = s[__X(i, 32, (CHAR*)"OfrontOPM", 190773)];
    }
    if (ch == 'E') {
      s[__X(i, 32, (CHAR*)"OfrontOPM", 191007)] = 'e';
    }
    OfrontOPM_WriteString((void*)s, 32);
  }
}

/*----------------------------------------------------------------------------*/
void OfrontOPM_WriteLn (void)
{
  OfrontOPM_WriteString((CHAR*)"\x0a", 2);
}

/*----------------------------------------------------------------------------*/
void OfrontOPM_WriteTab (void)
{
  OfrontOPM_WriteString((CHAR*)"  ", 3);
}

/*----------------------------------------------------------------------------*/
void OfrontOPM_WriteModPos (void)
{
  if (__IN(6, OfrontOPM_opt)) {
    OfrontOPM_WriteString((CHAR*)"(CHAR*)", 8);
  }
  OfrontOPM_Write('\"');
  OfrontOPM_WriteString((void*)OfrontOPM_modName, 32);
  OfrontOPM_WriteString((CHAR*)"\", ", 4);
  OfrontOPM_WriteInt(OfrontOPM_errpos);
}

/*----------------------------------------------------------------------------*/
static void OfrontOPM_Append (Files_Rider *R, void **R__typ, Files_File F)
{
  Files_Rider R1 = {0};
  CHAR buffer[4096];
  if (F != NIL) {
    Files_Set(&R1, Files_Rider__typ, F, 0);
    Files_ReadBytes(&R1, Files_Rider__typ, (void*)(SYSTEM_ADRINT)buffer, 4096, 4096);
    while (4096 - R1.res > 0) {
      Files_WriteBytes(R, R__typ, (void*)(SYSTEM_ADRINT)buffer, 4096, 4096 - R1.res);
      Files_ReadBytes(&R1, Files_Rider__typ, (void*)(SYSTEM_ADRINT)buffer, 4096, 4096);
    }
  }
}

void OfrontOPM_OpenFiles (CHAR *moduleName, INTEGER moduleName__len)
{
  OfrontOPM_FileName FName;
  __STRCOPYCC(moduleName, OfrontOPM_modName, __MIN(32, moduleName__len), (CHAR*)"OfrontOPM", 200216);
  OfrontOPM_HFile = Files_New((CHAR*)"", 1);
  if (OfrontOPM_HFile != NIL) {
    Files_Set(&OfrontOPM_R[0], Files_Rider__typ, OfrontOPM_HFile, 0);
  } else {
    OfrontOPM_err(153);
  }
  if (!__IN(14, OfrontOPM_opt)) {
    OfrontOPM_MakeFileName((void*)moduleName, moduleName__len, (void*)FName, 36, (CHAR*)".c", 3);
    OfrontOPM_BFile = Files_New((void*)FName, 36);
    if (OfrontOPM_BFile != NIL) {
      Files_Set(&OfrontOPM_R[1], Files_Rider__typ, OfrontOPM_BFile, 0);
    } else {
      OfrontOPM_err(153);
    }
  }
  OfrontOPM_MakeFileName((void*)moduleName, moduleName__len, (void*)FName, 36, (CHAR*)".oh", 4);
  OfrontOPM_HIFile = Files_New((void*)FName, 36);
  if (OfrontOPM_HIFile != NIL) {
    Files_Set(&OfrontOPM_R[2], Files_Rider__typ, OfrontOPM_HIFile, 0);
  } else {
    OfrontOPM_err(153);
  }
  if (__IN(8, OfrontOPM_opt)) {
    OfrontOPM_MakeFileName((void*)moduleName, moduleName__len, (void*)FName, 36, (CHAR*)".h0", 4);
    OfrontOPM_Append(&OfrontOPM_R[2], Files_Rider__typ, Files_Old((void*)FName, 36));
    if (!__IN(14, OfrontOPM_opt)) {
      OfrontOPM_MakeFileName((void*)moduleName, moduleName__len, (void*)FName, 36, (CHAR*)".c0", 4);
      OfrontOPM_Append(&OfrontOPM_R[1], Files_Rider__typ, Files_Old((void*)FName, 36));
    }
  }
}

/*----------------------------------------------------------------------------*/
void OfrontOPM_CloseFiles (void)
{
  OfrontOPM_FileName FName;
  INTEGER res;
  BOOLEAN body;
  body = !__IN(14, OfrontOPM_opt);
  if (OfrontOPM_noerr) {
    OfrontOPM_LogWStr((CHAR*)"    ", 5);
    if (body) {
      OfrontOPM_LogWNum((INTEGER)Files_Pos(&OfrontOPM_R[1], Files_Rider__typ), 0);
    } else {
      OfrontOPM_LogWNum((INTEGER)Files_Pos(&OfrontOPM_R[0], Files_Rider__typ), 0);
    }
  }
  if (OfrontOPM_noerr) {
    OfrontOPM_LogWStr((CHAR*)"    ", 5);
  }
  if (OfrontOPM_noerr) {
    if (__STRCMPCC(OfrontOPM_modName, (CHAR*)"SYSTEM", 7, (CHAR*)"OfrontOPM", 212223) == 0) {
      if (!__IN(10, OfrontOPM_opt)) {
        if (body) {
          Files_Register(OfrontOPM_BFile);
        } else {
          OfrontOPM_MakeFileName((void*)OfrontOPM_modName, 32, (void*)FName, 36, (CHAR*)".c", 3);
          Files_Delete((void*)FName, 36, &res);
        }
      }
    } else if (!__IN(10, OfrontOPM_opt)) {
      OfrontOPM_Append(&OfrontOPM_R[2], Files_Rider__typ, OfrontOPM_HFile);
      Files_Register(OfrontOPM_HIFile);
      if (body) {
        Files_Register(OfrontOPM_BFile);
      } else {
        OfrontOPM_MakeFileName((void*)OfrontOPM_modName, 32, (void*)FName, 36, (CHAR*)".c", 3);
        Files_Delete((void*)FName, 36, &res);
      }
    } else {
      OfrontOPM_MakeFileName((void*)OfrontOPM_modName, 32, (void*)FName, 36, (CHAR*)".oh", 4);
      Files_Delete((void*)FName, 36, &res);
      OfrontOPM_MakeFileName((void*)OfrontOPM_modName, 32, (void*)FName, 36, (CHAR*)".sym", 5);
      Files_Delete((void*)FName, 36, &res);
      if (body) {
        Files_Register(OfrontOPM_BFile);
      } else {
        OfrontOPM_MakeFileName((void*)OfrontOPM_modName, 32, (void*)FName, 36, (CHAR*)".c", 3);
        Files_Delete((void*)FName, 36, &res);
      }
    }
  }
  OfrontOPM_HFile = NIL;
  OfrontOPM_BFile = NIL;
  OfrontOPM_HIFile = NIL;
  OfrontOPM_newSFile = NIL;
  OfrontOPM_oldSFile = NIL;
  Files_Set(&OfrontOPM_R[0], Files_Rider__typ, NIL, 0);
  Files_Set(&OfrontOPM_R[1], Files_Rider__typ, NIL, 0);
  Files_Set(&OfrontOPM_R[2], Files_Rider__typ, NIL, 0);
  Files_Set(&OfrontOPM_newSF, Files_Rider__typ, NIL, 0);
  Files_Set(&OfrontOPM_oldSF, Files_Rider__typ, NIL, 0);
}

/*----------------------------------------------------------------------------*/
void OfrontOPM_PromoteIntConstToLInt (void)
{
  if (!__IN(6, OfrontOPM_opt)) {
    OfrontOPM_Write('L');
  }
}

/*----------------------------------------------------------------------------*/
static void OfrontOPM_InitHost (void)
{
  SHORTINT test;
  CHAR lo;
  test = 1;
  __GET((SYSTEM_ADRINT)&test, lo, CHAR);
  OfrontOPM_LEHost = lo == 0x01;
  OfrontOPM_InfReal = __VALSR((INTEGER)2139095040);
  OfrontOPM_MinReal32 = __VALSR((INTEGER)-8388609);
  OfrontOPM_MaxReal32 = __VALSR((INTEGER)2139095039);
  OfrontOPM_MinReal64 = OfrontOPM_Compound(-1, -1048577);
  OfrontOPM_MaxReal64 = OfrontOPM_Compound(-1, 2146435071);
}

static void EnumPtrs(void (*P)(void*))
{
  __ENUMR(&OfrontOPM_inR, Texts_Reader__typ, 64, 1, P);
  P(OfrontOPM_Log);
  __ENUMR(&OfrontOPM_W, Texts_Writer__typ, 56, 1, P);
  __ENUMR(&OfrontOPM_oldSF, Files_Rider__typ, 32, 1, P);
  __ENUMR(&OfrontOPM_newSF, Files_Rider__typ, 32, 1, P);
  __ENUMR(OfrontOPM_R, Files_Rider__typ, 32, 3, P);
  P(OfrontOPM_oldSFile);
  P(OfrontOPM_newSFile);
  P(OfrontOPM_HFile);
  P(OfrontOPM_BFile);
  P(OfrontOPM_HIFile);
}


export void *OfrontOPM__init (void)
{
  __DEFMOD;
  __IMPORT(CmdArgs__init);
  __IMPORT(Console__init);
  __IMPORT(Files__init);
  __IMPORT(OfrontErrors__init);
  __IMPORT(Platform__init);
  __IMPORT(Strings__init);
  __IMPORT(Texts__init);
  __REGMOD("OfrontOPM", EnumPtrs);
  __REGCMD("CloseFiles", OfrontOPM_CloseFiles);
  __REGCMD("CloseOldSym", OfrontOPM_CloseOldSym);
  __REGCMD("DeleteNewSym", OfrontOPM_DeleteNewSym);
  __REGCMD("InitOptions", OfrontOPM_InitOptions);
  __REGCMD("LogWLn", OfrontOPM_LogWLn);
  __REGCMD("PromoteIntConstToLInt", OfrontOPM_PromoteIntConstToLInt);
  __REGCMD("RegisterNewSym", OfrontOPM_RegisterNewSym);
  __REGCMD("WriteLn", OfrontOPM_WriteLn);
  __REGCMD("WriteModPos", OfrontOPM_WriteModPos);
  __REGCMD("WriteTab", OfrontOPM_WriteTab);
/* BEGIN */
  OfrontOPM_InitCrcTab();
  OfrontOPM_InitHost();
  Texts_OpenWriter(&OfrontOPM_W, Texts_Writer__typ);
  CmdArgs_GetEnv((CHAR*)"OBERON", 7, (void*)OfrontOPM_OBERON, 1024);
  if (OfrontOPM_OBERON[0] == 0x00) {
    __MOVE((CHAR*)".", OfrontOPM_OBERON, 2);
  }
  Files_SetSearchPath((void*)OfrontOPM_OBERON, 1024);
  __ENDMOD;
}
