/* Ofront+ 1.0 -sC -48 */
#include "SYSTEM.oh"
#include "Platform.oh"
#include "Strings.oh"
#include "Out.oh"


export BOOLEAN In_Done;
static CHAR In_nextch;
static SHORTINT In_readstate;


export void In_Char (CHAR *ch);
export void In_HugeInt (LONGINT *h);
export void In_Int (INTEGER *i);
export void In_Int16 (SHORTINT *i);
export void In_Line (CHAR *line, INTEGER line__len);
export void In_LongInt (INTEGER *i);
export void In_LongReal (REAL *y);
export void In_Name (CHAR *name, INTEGER name__len);
export void In_Open (void);
static void In_ReadChar (void);
export void In_Real (SHORTREAL *x);
static void In_StartAndSkip (void);
static void In_StartRead (void);
export void In_String (CHAR *str, INTEGER str__len);


/*============================================================================*/

void In_Open (void)
{
  INTEGER error;
  error = Platform_Seek(0, 0, Platform_SeekSet);
  In_readstate = 0;
  In_Done = 1;
}

/*----------------------------------------------------------------------------*/
static void In_ReadChar (void)
{
  INTEGER error, n;
  BYTE m[1];
  error = Platform_ReadBuf(0, (void*)m, 1, &n);
  In_nextch = (CHAR)m[0];
  if (error == 0 && n == 1) {
    In_readstate = 1;
  } else {
    In_readstate = 2;
  }
}

static void In_StartRead (void)
{
  Out_Flush();
  if ((INTEGER)In_readstate == 0) {
    In_ReadChar();
  }
}

static void In_StartAndSkip (void)
{
  In_StartRead();
  while ((INTEGER)In_readstate == 1 && In_nextch <= ' ') {
    In_ReadChar();
  }
}

void In_Char (CHAR *ch)
{
  In_StartRead();
  In_Done = (INTEGER)In_readstate == 1;
  if (In_Done) {
    *ch = In_nextch;
    if (*ch == 0x0a) {
      In_readstate = 0;
    } else {
      In_ReadChar();
    }
  } else {
    *ch = 0x00;
  }
}

/*----------------------------------------------------------------------------*/
void In_HugeInt (LONGINT *h)
{
  BOOLEAN neg, hex, endofnum;
  LONGINT decacc, hexacc, digit;
  In_StartAndSkip();
  In_Done = 0;
  if ((INTEGER)In_readstate == 1) {
    neg = In_nextch == '-';
    if (neg) {
      In_ReadChar();
    }
    hex = 0;
    endofnum = 0;
    decacc = 0;
    hexacc = 0;
    while ((INTEGER)In_readstate == 1 && !endofnum) {
      digit = -1;
      if (In_nextch >= '0' && In_nextch <= '9') {
        digit = __MASK((INTEGER)In_nextch, -16);
      } else if ((In_nextch >= 'a' && In_nextch <= 'f') || (In_nextch >= 'A' && In_nextch <= 'F')) {
        digit = __MASK((INTEGER)In_nextch, -16) + 9;
        hex = 1;
      }
      if (digit >= 0) {
        In_Done = 1;
        decacc = decacc * 10 + digit;
        hexacc = __ASHL(hexacc, 4, LONGINT) + digit;
        In_ReadChar();
      } else if (In_nextch == 'H') {
        hex = 1;
        endofnum = 1;
        In_ReadChar();
      } else {
        endofnum = 1;
      }
    }
    if (In_Done) {
      if (hex) {
        *h = hexacc;
      } else {
        *h = decacc;
      }
      if (neg) {
        *h = -*h;
      }
    } else {
      *h = 0;
    }
  }
}

/*----------------------------------------------------------------------------*/
void In_Int16 (SHORTINT *i)
{
  LONGINT h;
  In_HugeInt(&h);
  *i = (SHORTINT)h;
}

/*----------------------------------------------------------------------------*/
void In_LongInt (INTEGER *i)
{
  LONGINT h;
  In_HugeInt(&h);
  *i = (INTEGER)h;
}

/*----------------------------------------------------------------------------*/
void In_Int (INTEGER *i)
{
  In_LongInt(i);
}

/*----------------------------------------------------------------------------*/
void In_Line (CHAR *line, INTEGER line__len)
{
  SHORTINT i;
  In_StartRead();
  i = 0;
  In_Done = (INTEGER)In_readstate == 1;
  while ((((INTEGER)In_readstate == 1 && In_nextch != 0x0d) && In_nextch != 0x0a) && (INTEGER)i < line__len - 1) {
    line[__X(i, line__len, (CHAR*)"In", 29461)] = In_nextch;
    i += 1;
    In_ReadChar();
  }
  line[__X(i, line__len, (CHAR*)"In", 29967)] = 0x00;
  if ((INTEGER)In_readstate == 1 && In_nextch == 0x0d) {
    In_ReadChar();
  }
  if ((INTEGER)In_readstate == 1 && In_nextch == 0x0a) {
    In_readstate = 0;
  }
}

/*----------------------------------------------------------------------------*/
void In_String (CHAR *str, INTEGER str__len)
{
  SHORTINT i;
  In_StartAndSkip();
  i = 0;
  if ((INTEGER)In_readstate == 1 && In_nextch == '\"') {
    In_ReadChar();
    while ((((INTEGER)In_readstate == 1 && (INTEGER)i < str__len - 1) && In_nextch >= ' ') && In_nextch != '\"') {
      str[__X(i, str__len, (CHAR*)"In", 33558)] = In_nextch;
      In_ReadChar();
      i += 1;
    }
  }
  In_Done = ((INTEGER)In_readstate == 1 && (INTEGER)i < str__len - 1) && In_nextch == '\"';
  if (In_Done) {
    In_ReadChar();
    str[__X(i, str__len, (CHAR*)"In", 35583)] = 0x00;
  } else {
    str[0] = 0x00;
  }
}

/*----------------------------------------------------------------------------*/
void In_Name (CHAR *name, INTEGER name__len)
{
  __HALT(99, (CHAR*)"In", 37375);
}

/*----------------------------------------------------------------------------*/
void In_Real (SHORTREAL *x)
{
  CHAR str[16];
  In_StartAndSkip();
  In_Line((void*)str, 16);
  Strings_StrToReal((void*)str, 16, x);
}

/*----------------------------------------------------------------------------*/
void In_LongReal (REAL *y)
{
  CHAR str[16];
  In_StartAndSkip();
  In_Line((void*)str, 16);
  Strings_StrToLongReal((void*)str, 16, y);
}

/*----------------------------------------------------------------------------*/

export void *In__init (void)
{
  __DEFMOD;
  __IMPORT(Out__init);
  __IMPORT(Platform__init);
  __IMPORT(Strings__init);
  __REGMOD("In", 0);
  __REGCMD("Open", In_Open);
/* BEGIN */
  In_nextch = 0x00;
  In_readstate = 0;
  In_Done = 1;
  __ENDMOD;
}
