/* Ofront+ 1.0 -sC -88 */
#include "SYSTEM.oh"
#include "Platform.oh"
#include "Kernel.oh"


export BOOLEAN Out_IsConsole;
static CHAR Out_buf[128];
static SHORTINT Out_in;


export void Out_Char (CHAR ch);
export void Out_ConvertL (REAL x, SHORTINT n, CHAR *d, INTEGER d__len);
export SHORTINT Out_Expo (SHORTREAL x);
export void Out_Flush (void);
export void Out_Hex (LONGINT x, LONGINT n);
export void Out_Int (LONGINT x, LONGINT n);
static INTEGER Out_Length (CHAR *s, INTEGER s__len);
export void Out_Ln (void);
export void Out_LongReal (REAL x, SHORTINT n);
export void Out_Open (void);
export void Out_Real (SHORTREAL x, SHORTINT n);
export void Out_RealFix (SHORTREAL x, SHORTINT n, SHORTINT k);
static void Out_RealP (REAL x, SHORTINT n, BOOLEAN long_);
export void Out_String (CHAR *str, INTEGER str__len);
export REAL Out_Ten (SHORTINT e);
static void Out_digit (LONGINT n, CHAR *s, INTEGER s__len, SHORTINT *i);
static void Out_prepend (CHAR *t, INTEGER t__len, CHAR *s, INTEGER s__len, SHORTINT *i);

#define Out_Entier64(x)  (LONGINT)(x)

/*============================================================================*/

void Out_Flush (void)
{
  INTEGER error;
  if ((INTEGER)Out_in > 0) {
    error = Platform_Write(1, (SYSTEM_ADRINT)Out_buf, Out_in);
  }
  Out_in = 0;
}

/*----------------------------------------------------------------------------*/
void Out_Open (void)
{
}

/*----------------------------------------------------------------------------*/
void Out_Char (CHAR ch)
{
  if ((INTEGER)Out_in >= 128) {
    Out_Flush();
  }
  Out_buf[__X(Out_in, 128, (CHAR*)"Out", 7951)] = ch;
  Out_in += 1;
  if (ch == 0x0a) {
    Out_Flush();
  }
}

/*----------------------------------------------------------------------------*/
static INTEGER Out_Length (CHAR *s, INTEGER s__len)
{
  INTEGER l;
  l = 0;
  while (l < s__len && s[__X(l, s__len, (CHAR*)"Out", 9518)] != 0x00) {
    l += 1;
  }
  return l;
}

void Out_String (CHAR *str, INTEGER str__len)
{
  INTEGER l, error;
  l = Out_Length((void*)str, str__len);
  if ((INTEGER)Out_in + l > 128) {
    Out_Flush();
  }
  if (l > 128) {
    error = Platform_Write(1, (SYSTEM_ADRINT)str, l);
  } else {
    __MOVE((SYSTEM_ADRINT)str, (SYSTEM_ADRINT)&Out_buf[__X(Out_in, 128, (CHAR*)"Out", 12600)], l);
    Out_in += (SHORTINT)l;
  }
}

/*----------------------------------------------------------------------------*/
void Out_Int (LONGINT x, LONGINT n)
{
  CHAR s[22];
  SHORTINT i;
  BOOLEAN negative;
  negative = x < 0;
  if (x == (-9223372036854775807LL-1)) {
    __MOVE((CHAR*)"8085774586302733229", s, 20);
    i = 19;
  } else {
    if (x < 0) {
      x = -x;
    }
    s[0] = (CHAR)(48 + __MOD(x, 10));
    x = __DIV(x, 10);
    i = 1;
    while (x != 0) {
      s[__X(i, 22, (CHAR*)"Out", 16683)] = (CHAR)(48 + __MOD(x, 10));
      x = __DIV(x, 10);
      i += 1;
    }
  }
  if (negative) {
    s[__X(i, 22, (CHAR*)"Out", 17950)] = '-';
    i += 1;
  }
  while (n > (LONGINT)i) {
    Out_Char(' ');
    n -= 1;
  }
  while ((INTEGER)i > 0) {
    i -= 1;
    Out_Char(s[__X(i, 22, (CHAR*)"Out", 18467)]);
  }
}

/*----------------------------------------------------------------------------*/
void Out_Hex (LONGINT x, LONGINT n)
{
  if (n < 1) {
    n = 1;
  } else if (n > 16) {
    n = 16;
  }
  if (x >= 0) {
    while (n < 16 && __LSH(x, -__ASHL(n, 2, LONGINT), LONGINT) != 0) {
      n += 1;
    }
  }
  x = __ROT(x, __ASHL(16 - n, 2, LONGINT), LONGINT);
  while (n > 0) {
    x = __ROTL(x, 4, LONGINT);
    n -= 1;
    if (__MASK(x, -16) < 10) {
      Out_Char((CHAR)(__MASK(x, -16) + 48));
    } else {
      Out_Char((CHAR)((__MASK(x, -16) - 10) + 65));
    }
  }
}

/*----------------------------------------------------------------------------*/
void Out_Ln (void)
{
  Out_String((CHAR*)"\x0a", 2);
  Out_Flush();
}

/*----------------------------------------------------------------------------*/
static void Out_digit (LONGINT n, CHAR *s, INTEGER s__len, SHORTINT *i)
{
  *i -= 1;
  s[__X(*i, s__len, (CHAR*)"Out", 25387)] = (CHAR)(__MOD(n, 10) + 48);
}

static void Out_prepend (CHAR *t, INTEGER t__len, CHAR *s, INTEGER s__len, SHORTINT *i)
{
  SHORTINT j;
  INTEGER l;
  l = Out_Length((void*)t, t__len);
  if (l > (INTEGER)*i) {
    l = *i;
  }
  *i -= (SHORTINT)l;
  j = 0;
  while ((INTEGER)j < l) {
    s[__X((INTEGER)*i + (INTEGER)j, s__len, (CHAR*)"Out", 27423)] = t[__X(j, t__len, (CHAR*)"Out", 27423)];
    j += 1;
  }
}

REAL Out_Ten (SHORTINT e)
{
  REAL r, power;
  r = (REAL)1;
  power = (REAL)10;
  while ((INTEGER)e > 0) {
    if (__ODD(e)) {
      r = r * power;
    }
    power = power * power;
    e = (SHORTINT)__ASHR((INTEGER)e, 1, INTEGER);
  }
  return r;
}

/*----------------------------------------------------------------------------*/
static void Out_RealP (REAL x, SHORTINT n, BOOLEAN long_)
{
  SHORTINT e;
  LONGINT f;
  CHAR s[30];
  SHORTINT i, el;
  REAL x0;
  BOOLEAN nn, en;
  LONGINT m;
  SHORTINT d, dr;
  e = (SHORTINT)__MASK(__ASHR(__VAL(LONGINT, x), 52, LONGINT), -2048);
  f = __MASK(__VAL(LONGINT, x), -4503599627370496LL);
  nn = __VAL(LONGINT, x) < 0 && !((INTEGER)e == 2047 && f != 0);
  if (nn) {
    n -= 1;
  }
  i = 30;
  if ((INTEGER)e == 2047) {
    if (f == 0) {
      Out_prepend((CHAR*)"Infinity", 9, (void*)s, 30, &i);
    } else {
      Out_prepend((CHAR*)"NaN", 4, (void*)s, 30, &i);
    }
  } else {
    if (long_) {
      el = 3;
      dr = (SHORTINT)((INTEGER)n - 6);
      if ((INTEGER)dr > 17) {
        dr = 17;
      }
      d = dr;
      if ((INTEGER)d < 15) {
        d = 15;
      }
    } else {
      el = 2;
      dr = (SHORTINT)((INTEGER)n - 5);
      if ((INTEGER)dr > 9) {
        dr = 9;
      }
      d = dr;
      if ((INTEGER)d < 6) {
        d = 6;
      }
    }
    if ((INTEGER)e == 0) {
      while ((INTEGER)el > 0) {
        i -= 1;
        s[__X(i, 30, (CHAR*)"Out", 44073)] = '0';
        el -= 1;
      }
      i -= 1;
      s[__X(i, 30, (CHAR*)"Out", 44313)] = '+';
      m = 0;
    } else {
      if (nn) {
        x = -x;
      }
      e = (SHORTINT)__ASHR((LONGINT)((INTEGER)e - 1023) * 77, 8, LONGINT);
      if ((INTEGER)e >= 0) {
        x = x / (REAL)Out_Ten(e);
      } else {
        x = Out_Ten((SHORTINT)(-((INTEGER)e))) * x;
      }
      if (x >= (REAL)10) {
        x = 0.1 * x;
        e += 1;
      }
      en = (INTEGER)e < 0;
      if (en) {
        e = (SHORTINT)(-((INTEGER)e));
      }
      while ((INTEGER)el > 0) {
        Out_digit(e, (void*)s, 30, &i);
        e = (SHORTINT)__DIV((INTEGER)e, 10);
        el -= 1;
      }
      i -= 1;
      if (en) {
        s[__X(i, 30, (CHAR*)"Out", 47652)] = '-';
      } else {
        s[__X(i, 30, (CHAR*)"Out", 47669)] = '+';
      }
      x0 = Out_Ten((SHORTINT)((INTEGER)d - 1));
      x = x0 * x;
      x = x + 0.5;
      if (x >= (REAL)10 * x0) {
        x = 0.1 * x;
        e += 1;
      }
      m = Out_Entier64(x);
    }
    i -= 1;
    if (long_) {
      s[__X(i, 30, (CHAR*)"Out", 50980)] = 'D';
    } else {
      s[__X(i, 30, (CHAR*)"Out", 50997)] = 'E';
    }
    if ((INTEGER)dr < 2) {
      dr = 2;
    }
    while ((INTEGER)d > (INTEGER)dr && __MOD(m, 10) == 0) {
      m = __DIV(m, 10);
      d -= 1;
    }
    while ((INTEGER)d > 1) {
      Out_digit(m, (void*)s, 30, &i);
      m = __DIV(m, 10);
      d -= 1;
    }
    i -= 1;
    s[__X(i, 30, (CHAR*)"Out", 53015)] = '.';
    Out_digit(m, (void*)s, 30, &i);
  }
  n -= (SHORTINT)(30 - (INTEGER)i);
  while ((INTEGER)n > 0) {
    Out_Char(' ');
    n -= 1;
  }
  if (nn) {
    Out_Char('-');
  }
  while ((INTEGER)i < 30) {
    Out_Char(s[__X(i, 30, (CHAR*)"Out", 55328)]);
    i += 1;
  }
}

void Out_Real (SHORTREAL x, SHORTINT n)
{
  Out_RealP(x, n, 0);
}

/*----------------------------------------------------------------------------*/
void Out_LongReal (REAL x, SHORTINT n)
{
  Out_RealP(x, n, 1);
}

/*----------------------------------------------------------------------------*/
void Out_ConvertL (REAL x, SHORTINT n, CHAR *d, INTEGER d__len)
{
  LONGINT i, j, k;
  if (x < (REAL)0) {
    x = -x;
  }
  k = 0;
  if ((INTEGER)n > 9) {
    i = __ENTIERL(x / (REAL)(REAL)1000000000);
    j = __ENTIERL(x - (REAL)i * (REAL)1000000000);
    if (j < 0) {
      j = 0;
    }
    while (k < 9) {
      d[__X(k, d__len, (CHAR*)"Out", 62759)] = (CHAR)(__MOD(j, 10) + 48);
      j = __DIV(j, 10);
      k += 1;
    }
  } else {
    i = __ENTIERL(x);
  }
  while (k < (LONGINT)n) {
    d[__X(k, d__len, (CHAR*)"Out", 65061)] = (CHAR)(__MOD(i, 10) + 48);
    i = __DIV(i, 10);
    k += 1;
  }
}

/*----------------------------------------------------------------------------*/
SHORTINT Out_Expo (SHORTREAL x)
{
  SHORTINT i;
  __GET((SYSTEM_ADRINT)&x + 2, i, SHORTINT);
  return (SHORTINT)__MASK(__ASHR((INTEGER)i, 7, INTEGER), -256);
}

/*----------------------------------------------------------------------------*/
static struct RealFix__13 {
  SHORTINT *i;
  CHAR (*d)[9];
  struct RealFix__13 *lnk;
} *RealFix__13_s;

static void __14 (SHORTINT n);
static void __16 (CHAR ch, SHORTINT n);

static void __16 (CHAR ch, SHORTINT n)
{
  while ((INTEGER)n > 0) {
    Out_Char(ch);
    n -= 1;
  }
}

static void __14 (SHORTINT n)
{
  while ((INTEGER)n > 0) {
    (*RealFix__13_s->i) -= 1;
    Out_Char(((*RealFix__13_s->d))[__X((*RealFix__13_s->i), 9, (CHAR*)"Out", 70936)]);
    n -= 1;
  }
}

void Out_RealFix (SHORTREAL x, SHORTINT n, SHORTINT k)
{
  SHORTINT e, i;
  CHAR sign;
  SHORTREAL x0;
  CHAR d[9];
  struct RealFix__13 _s;
  _s.i = &i;
  _s.d = (void*)d;
  _s.lnk = RealFix__13_s;
  RealFix__13_s = &_s;
  e = Out_Expo(x);
  if ((INTEGER)k < 0) {
    k = 0;
  }
  if ((INTEGER)e == 0) {
    __16(' ', (SHORTINT)(((INTEGER)n - (INTEGER)k) - 2));
    Out_Char('0');
    __16(' ', (SHORTINT)((INTEGER)k + 1));
  } else if ((INTEGER)e == 255) {
    Out_String((CHAR*)" NaN", 5);
    __16(' ', (SHORTINT)((INTEGER)n - 4));
  } else {
    e = (SHORTINT)__ASHR(((INTEGER)e - 127) * 77, 8, INTEGER);
    if (x < (SHORTREAL)0) {
      sign = '-';
      x = -x;
    } else {
      sign = ' ';
    }
    if ((INTEGER)e >= 0) {
      x = (SHORTREAL)((REAL)x / (REAL)Out_Ten(e));
    } else {
      x = (SHORTREAL)(Out_Ten((SHORTINT)(-((INTEGER)e))) * (REAL)x);
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
    x0 = (SHORTREAL)Out_Ten((SHORTINT)((INTEGER)k + (INTEGER)e));
    x = x0 * x + 0.5;
    if (x >= (SHORTREAL)10 * x0) {
      e += 1;
    }
    e += 1;
    i = (SHORTINT)((INTEGER)k + (INTEGER)e);
    Out_ConvertL(x, i, (void*)d, 9);
    if ((INTEGER)e > 0) {
      __16(' ', (SHORTINT)((((INTEGER)n - (INTEGER)e) - (INTEGER)k) - 2));
      Out_Char(sign);
      __14(e);
      Out_Char('.');
      __14(k);
    } else {
      __16(' ', (SHORTINT)(((INTEGER)n - (INTEGER)k) - 3));
      Out_Char(sign);
      Out_Char('0');
      Out_Char('.');
      __16('0', (SHORTINT)(-((INTEGER)e)));
      __14((SHORTINT)((INTEGER)k + (INTEGER)e));
    }
  }
  RealFix__13_s = _s.lnk;
}

/*----------------------------------------------------------------------------*/

export void *Out__init (void)
{
  __DEFMOD;
  __IMPORT(Kernel__init);
  __IMPORT(Platform__init);
  __REGMOD("Out", 0);
  __REGCMD("Flush", Out_Flush);
  __REGCMD("Ln", Out_Ln);
  __REGCMD("Open", Out_Open);
/* BEGIN */
  Out_IsConsole = Platform_IsConsole(1);
  Out_in = 0;
  __ENDMOD;
}
