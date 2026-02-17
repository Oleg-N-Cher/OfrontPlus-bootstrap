/* Ofront+ 1.0 -sC -48 */
#include "SYSTEM.oh"
#include "MathL.oh"


static INTEGER Reals_maxExp, Reals_maxDig;
static REAL Reals_factor;


export void Reals_Convert (SHORTREAL x, SHORTINT n, CHAR *d, INTEGER d__len);
export void Reals_ConvertH (SHORTREAL y, CHAR *d, INTEGER d__len);
export void Reals_ConvertHL (REAL x, CHAR *d, INTEGER d__len);
export SHORTINT Reals_Expo (SHORTREAL x);
export SHORTINT Reals_ExpoL (REAL x);
export void Reals_RealToStr (REAL x, INTEGER digits, CHAR *d, INTEGER d__len);
export void Reals_RealToStringForm (REAL x, INTEGER precision, INTEGER minW, INTEGER expW, CHAR fillCh, CHAR *s, INTEGER s__len);
export void Reals_SetExpo (SHORTINT e, SHORTREAL *x);
export void Reals_SetExpoL (SHORTINT e, REAL *x);
export SHORTREAL Reals_Ten (SHORTINT e);
export REAL Reals_TenL (INTEGER n);
static void Reals_Unpack (BYTE *b, INTEGER b__len, BYTE *d, INTEGER d__len);


/*============================================================================*/

SHORTREAL Reals_Ten (SHORTINT e)
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
  return (SHORTREAL)r;
}

/*----------------------------------------------------------------------------*/
REAL Reals_TenL (INTEGER n)
{
  REAL r, power;
  r = (REAL)1;
  power = (REAL)10;
  while (n > 0) {
    if (__ODD(n)) {
      r = r * power;
    }
    power = power * power;
    n = (SHORTINT)__ASHR(n, 1, INTEGER);
  }
  return r;
}

/*----------------------------------------------------------------------------*/
SHORTINT Reals_Expo (SHORTREAL x)
{
  return (SHORTINT)__MASK(__ASHR(__VAL(INTEGER, x), 23, INTEGER), -256);
}

/*----------------------------------------------------------------------------*/
SHORTINT Reals_ExpoL (REAL x)
{
  INTEGER exp, offset;
  x = __ABS(x);
  exp = (INTEGER)__ASHR(__VAL(LONGINT, x), 52, LONGINT);
  offset = 1023;
  while (exp == 0) {
    x = x + x;
    exp = (INTEGER)__ASHR(__VAL(LONGINT, x), 52, LONGINT);
    offset += 1;
  }
  return (SHORTINT)(exp - offset);
}

/*----------------------------------------------------------------------------*/
void Reals_SetExpo (SHORTINT e, SHORTREAL *x)
{
  *x = __VALSR((INTEGER)((__VAL(SET, *x) & ~0x01fe) | (SET)__ASHL((INTEGER)e, 23, INTEGER)));
}

/*----------------------------------------------------------------------------*/
void Reals_SetExpoL (SHORTINT e, REAL *x)
{
  SET h;
  __GET((SYSTEM_ADRINT)x + 4, h, SET);
  h = (h & ~0x0ffe) | (SET)__ASHL((INTEGER)e, 20, INTEGER);
  __PUT((SYSTEM_ADRINT)x + 4, h, SET);
}

/*----------------------------------------------------------------------------*/
void Reals_Convert (SHORTREAL x, SHORTINT n, CHAR *d, INTEGER d__len)
{
  INTEGER i, k;
  i = (INTEGER)__ENTIER(x);
  k = 0;
  while (k < (INTEGER)n) {
    d[__X(k, d__len, (CHAR*)"Reals", 17703)] = (CHAR)(__MOD(i, 10) + 48);
    i = __DIV(i, 10);
    k += 1;
  }
}

/*----------------------------------------------------------------------------*/
static void Reals_Unpack (BYTE *b, INTEGER b__len, BYTE *d, INTEGER d__len)
{
  BYTE i, k;
  INTEGER len;
  i = 0;
  len = b__len;
  while ((INTEGER)i < len) {
    k = (BYTE)__ASHR((INTEGER)((CHAR)b[__X(i, b__len, (CHAR*)"Reals", 19771)]), 4, INTEGER);
    if ((INTEGER)k > 9) {
      d[__X(__ASHL((INTEGER)i, 1, INTEGER), d__len, (CHAR*)"Reals", 20018)] = (BYTE)((INTEGER)k + 55);
    } else {
      d[__X(__ASHL((INTEGER)i, 1, INTEGER), d__len, (CHAR*)"Reals", 20054)] = (BYTE)((INTEGER)k + 48);
    }
    k = (BYTE)__MASK((INTEGER)((CHAR)b[__X(i, b__len, (CHAR*)"Reals", 20283)]), -16);
    if ((INTEGER)k > 9) {
      d[__X(__ASHL((INTEGER)i, 1, INTEGER) + 1, d__len, (CHAR*)"Reals", 20532)] = (BYTE)((INTEGER)k + 55);
    } else {
      d[__X(__ASHL((INTEGER)i, 1, INTEGER) + 1, d__len, (CHAR*)"Reals", 20570)] = (BYTE)((INTEGER)k + 48);
    }
    i += 1;
  }
}

void Reals_ConvertH (SHORTREAL y, CHAR *d, INTEGER d__len)
{
  Reals_Unpack((void*)(SYSTEM_ADRINT)&y, 4, (void*)(SYSTEM_ADRINT)d, d__len);
}

/*----------------------------------------------------------------------------*/
void Reals_ConvertHL (REAL x, CHAR *d, INTEGER d__len)
{
  Reals_Unpack((void*)(SYSTEM_ADRINT)&x, 8, (void*)(SYSTEM_ADRINT)d, d__len);
}

/*----------------------------------------------------------------------------*/
void Reals_RealToStringForm (REAL x, INTEGER precision, INTEGER minW, INTEGER expW, CHAR fillCh, CHAR *s, INTEGER s__len)
{
  INTEGER exp, len, i, j, n, k, p;
  CHAR m[80];
  BOOLEAN neg;
  __ASSERT(precision > 0, 20, (CHAR*)"Reals", 26423);
  __ASSERT(minW >= 0 && minW < s__len, 21, (CHAR*)"Reals", 26669);
  __ASSERT(expW > -s__len && expW <= 3, 22, (CHAR*)"Reals", 26926);
  exp = MathL_exponent(x);
  if (exp == 2147483647) {
    if (fillCh == '0') {
      fillCh = ' ';
    }
    x = MathL_fraction(x);
    if (x == (REAL)-1) {
      __MOVE((CHAR*)"-INF", m, 5);
      n = 4;
    } else if (x == (REAL)1) {
      __MOVE((CHAR*)"INF", m, 4);
      n = 3;
    } else {
      __MOVE((CHAR*)"NaN", m, 4);
      n = 3;
    }
    i = 0;
    j = 0;
    while (minW > n) {
      s[__X(i, s__len, (CHAR*)"Reals", 29478)] = fillCh;
      i += 1;
      minW -= 1;
    }
    while (j <= n && i < s__len) {
      s[__X(i, s__len, (CHAR*)"Reals", 29747)] = m[__X(j, 80, (CHAR*)"Reals", 29747)];
      i += 1;
      j += 1;
    }
  } else {
    neg = 0;
    len = 1;
    __MOVE((CHAR*)"00", m, 3);
    if (x < (REAL)0) {
      x = -x;
      neg = 1;
      minW -= 1;
    }
    if (x != (REAL)0) {
      exp = __DIV((exp - 8) * 30103, 100000);
      if (exp > 0) {
        n = (INTEGER)__ENTIER(x / (REAL)Reals_TenL(exp));
        x = x / (REAL)Reals_TenL(exp) - (REAL)n;
      } else if (exp > -Reals_maxExp) {
        n = (INTEGER)__ENTIER(x * Reals_TenL(-exp));
        x = x * Reals_TenL(-exp) - (REAL)n;
      } else {
        n = (INTEGER)__ENTIER(((x * Reals_TenL(-exp - __ASHL(Reals_maxDig, 1, INTEGER))) * Reals_factor) * Reals_factor);
        x = ((x * Reals_TenL(-exp - __ASHL(Reals_maxDig, 1, INTEGER))) * Reals_factor) * Reals_factor - (REAL)n;
      }
      p = precision - 4;
      if (n < 1000) {
        p += 1;
      }
      if (expW < 0 && p > exp - expW) {
        p = exp - expW;
      }
      if (p >= 0) {
        x = x + 0.5 / (REAL)Reals_TenL(p);
        if (x >= (REAL)1) {
          n += 1;
          x = x - (REAL)1;
        }
      } else if (p == -1) {
        n += 5;
      } else if (p == -2) {
        n += 50;
      } else if (p == -3) {
        n += 500;
      }
      i = 0;
      k = 1000;
      exp += 3;
      if (n < 1000) {
        k = 100;
        exp -= 1;
      }
      while (i < precision && (k > 0 || x != (REAL)0)) {
        if (k > 0) {
          p = __DIVF(n, k);
          n = __MODF(n, k);
          k = __DIV(k, 10);
        } else {
          x = x * (REAL)10;
          p = (INTEGER)__ENTIER(x);
          x = x - (REAL)p;
        }
        m[__X(i, 80, (CHAR*)"Reals", 38186)] = (CHAR)(p + 48);
        i += 1;
        if (p != 0) {
          len = i;
        }
      }
    }
    i = 0;
    if (expW < 0 || ((expW == 0 && exp >= -3) && exp <= len + 1)) {
      n = exp + 1;
      k = len - n;
      if (n < 1) {
        n = 1;
      }
      if (expW < 0) {
        k = -expW;
      } else if (k < 1) {
        k = 1;
      }
      j = ((minW - n) - k) - 1;
      p = -exp;
      if (neg && p >= __MAX(0, n) + __MAX(0, k)) {
        neg = 0;
        j += 1;
      }
    } else {
      if (__ABS(exp) >= 100) {
        expW = 3;
      } else if (expW < 2 && __ABS(exp) >= 10) {
        expW = 2;
      } else if (expW < 1) {
        expW = 1;
      }
      if (len < 2) {
        len = 2;
      }
      j = ((minW - len) - 3) - expW;
      k = len;
      if (j > 0) {
        k = k + j;
        j = 0;
        if (k > precision) {
          j = k - precision;
          k = precision;
        }
      }
      n = 1;
      k -= 1;
      p = 0;
    }
    if (neg && fillCh == '0') {
      s[__X(i, s__len, (CHAR*)"Reals", 44590)] = '-';
      i += 1;
      neg = 0;
    }
    while (j > 0) {
      s[__X(i, s__len, (CHAR*)"Reals", 44835)] = fillCh;
      i += 1;
      j -= 1;
    }
    if (neg && i < s__len) {
      s[__X(i, s__len, (CHAR*)"Reals", 45100)] = '-';
      i += 1;
    }
    j = 0;
    while (n > 0 && i < s__len) {
      if (p <= 0 && j < len) {
        s[__X(i, s__len, (CHAR*)"Reals", 45873)] = m[__X(j, 80, (CHAR*)"Reals", 45873)];
        j += 1;
      } else {
        s[__X(i, s__len, (CHAR*)"Reals", 45898)] = '0';
      }
      i += 1;
      n -= 1;
      p -= 1;
    }
    if (i < s__len) {
      s[__X(i, s__len, (CHAR*)"Reals", 46628)] = '.';
      i += 1;
    }
    while (k > 0 && i < s__len) {
      if (p <= 0 && j < len) {
        s[__X(i, s__len, (CHAR*)"Reals", 47153)] = m[__X(j, 80, (CHAR*)"Reals", 47153)];
        j += 1;
      } else {
        s[__X(i, s__len, (CHAR*)"Reals", 47178)] = '0';
      }
      i += 1;
      k -= 1;
      p -= 1;
    }
    if (expW > 0) {
      if (i < s__len) {
        s[__X(i, s__len, (CHAR*)"Reals", 48166)] = 'E';
        i += 1;
      }
      if (i < s__len) {
        if (exp < 0) {
          s[__X(i, s__len, (CHAR*)"Reals", 48677)] = '-';
          exp = -exp;
        } else {
          s[__X(i, s__len, (CHAR*)"Reals", 48707)] = '+';
        }
        i += 1;
      }
      if (expW == 3 && i < s__len) {
        s[__X(i, s__len, (CHAR*)"Reals", 49492)] = (CHAR)(__DIV(exp, 100) + 48);
        i += 1;
      }
      if (expW >= 2 && i < s__len) {
        s[__X(i, s__len, (CHAR*)"Reals", 49755)] = (CHAR)(__MOD(__DIV(exp, 10), 10) + 48);
        i += 1;
      }
      if (i < s__len) {
        s[__X(i, s__len, (CHAR*)"Reals", 49988)] = (CHAR)(__MOD(exp, 10) + 48);
        i += 1;
      }
    }
  }
  if (i < s__len) {
    s[__X(i, s__len, (CHAR*)"Reals", 50721)] = 0x00;
  } else {
    __HALT(23, (CHAR*)"Reals", 50735);
  }
}

/*----------------------------------------------------------------------------*/
void Reals_RealToStr (REAL x, INTEGER digits, CHAR *d, INTEGER d__len)
{
  Reals_RealToStringForm(x, digits, 0, 0, ' ', (void*)d, d__len);
}

/*----------------------------------------------------------------------------*/

export void *Reals__init (void)
{
  __DEFMOD;
  __IMPORT(MathL__init);
  __REGMOD("Reals", 0);
/* BEGIN */
  Reals_maxExp = (INTEGER)__ENTIER(MathL_log((8.9884656743115738e+307 * 2), (REAL)10)) + 1;
  Reals_maxDig = (INTEGER)__ENTIER(-MathL_log(MathL_ulp((REAL)1), (REAL)10));
  Reals_factor = Reals_TenL(Reals_maxDig);
  __ENDMOD;
}
