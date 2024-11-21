/* Ofront+ 1.0 -swC -44 */
#include "SYSTEM.oh"
#include "bbKernel.oh"
#include "bbMath.oh"


static INTEGER bbStrings_maxExp, bbStrings_maxDig;
static REAL bbStrings_factor;
static LONGCHAR bbStrings_digits[17];
static LONGCHAR bbStrings_toUpper[256], bbStrings_toLower[256];


export void bbStrings_Extract (LONGCHAR *s, INTEGER s__len, INTEGER pos, INTEGER len, LONGCHAR *res, INTEGER res__len);
export void bbStrings_Find (LONGCHAR *s, INTEGER s__len, LONGCHAR *pat, INTEGER pat__len, INTEGER start, INTEGER *pos);
static void bbStrings_Init (void);
export void bbStrings_IntToString (LONGINT x, LONGCHAR *s, INTEGER s__len);
export void bbStrings_IntToStringForm (LONGINT x, INTEGER form, INTEGER minWidth, LONGCHAR fillCh, BOOLEAN showBase, LONGCHAR *s, INTEGER s__len);
export BOOLEAN bbStrings_IsAlpha (LONGCHAR ch);
export BOOLEAN bbStrings_IsAlphaNumeric (LONGCHAR ch);
export BOOLEAN bbStrings_IsIdent (LONGCHAR ch);
export BOOLEAN bbStrings_IsIdentStart (LONGCHAR ch);
export BOOLEAN bbStrings_IsLower (LONGCHAR ch);
export BOOLEAN bbStrings_IsNumeric (LONGCHAR ch);
export BOOLEAN bbStrings_IsUpper (LONGCHAR ch);
export LONGCHAR bbStrings_Lower (LONGCHAR ch);
export void bbStrings_RealToString (REAL x, LONGCHAR *s, INTEGER s__len);
export void bbStrings_RealToStringForm (REAL x, INTEGER precision, INTEGER minW, INTEGER expW, LONGCHAR fillCh, LONGCHAR *s, INTEGER s__len);
export void bbStrings_Replace (LONGCHAR *s, INTEGER s__len, INTEGER pos, INTEGER len, LONGCHAR *rep, INTEGER rep__len);
export void bbStrings_SetToString (SET x, LONGCHAR *str, INTEGER str__len);
export void bbStrings_StringToInt (LONGCHAR *s, INTEGER s__len, INTEGER *x, INTEGER *res);
export void bbStrings_StringToLInt (LONGCHAR *s, INTEGER s__len, LONGINT *x, INTEGER *res);
export void bbStrings_StringToReal (LONGCHAR *s, INTEGER s__len, REAL *x, INTEGER *res);
export void bbStrings_StringToSet (LONGCHAR *s, INTEGER s__len, SET *x, INTEGER *res);
export void bbStrings_StringToUtf8 (LONGCHAR *in, INTEGER in__len, CHAR *out, INTEGER out__len, INTEGER *res);
export void bbStrings_ToLower (LONGCHAR *in, INTEGER in__len, LONGCHAR *out, INTEGER out__len);
export void bbStrings_ToUpper (LONGCHAR *in, INTEGER in__len, LONGCHAR *out, INTEGER out__len);
export LONGCHAR bbStrings_Upper (LONGCHAR ch);
export void bbStrings_Utf8ToString (CHAR *in, INTEGER in__len, LONGCHAR *out, INTEGER out__len, INTEGER *res);
export BOOLEAN bbStrings_Valid (LONGCHAR *s, INTEGER s__len);


/*============================================================================*/

void bbStrings_IntToString (LONGINT x, LONGCHAR *s, INTEGER s__len)
{
  INTEGER j, k;
  LONGCHAR ch;
  LONGCHAR a[32];
  if (x != (-9223372036854775807LL-1)) {
    if (x < 0) {
      s[0] = '-';
      k = 1;
      x = -x;
    } else {
      k = 0;
    }
    j = 0;
    do {
      a[__X(j, 32, (CHAR*)"bbStrings", 9522)] = (LONGCHAR)(__MOD(x, 10) + 48);
      x = __DIV(x, 10);
      j += 1;
    } while (!(x == 0));
  } else {
    __MOVE(((LONGCHAR[]){56, 48, 56, 53, 55, 55, 52, 53, 56, 54, 51, 48, 50, 55, 51, 51, 50, 50, 57, 0}), a, 40);
    s[0] = '-';
    k = 1;
    j = 0;
    while (a[__X(j, 32, (CHAR*)"bbStrings", 10266)] != 0x00) {
      j += 1;
    }
  }
  __ASSERT(k + j < s__len, 23, (CHAR*)"bbStrings", 10780);
  do {
    j -= 1;
    ch = a[__X(j, 32, (CHAR*)"bbStrings", 11035)];
    s[__X(k, s__len, (CHAR*)"bbStrings", 11047)] = ch;
    k += 1;
  } while (!(j == 0));
  s[__X(k, s__len, (CHAR*)"bbStrings", 11519)] = 0x00;
}

/*----------------------------------------------------------------------------*/
void bbStrings_IntToStringForm (LONGINT x, INTEGER form, INTEGER minWidth, LONGCHAR fillCh, BOOLEAN showBase, LONGCHAR *s, INTEGER s__len)
{
  INTEGER base, i, j, k, si;
  BOOLEAN mSign;
  LONGCHAR a[128];
  LONGCHAR c1, c5, c10;
  __ASSERT(((form == -1 || form == -2) || form == -3) || (form >= 2 && form <= 16), 20, (CHAR*)"bbStrings", 13161);
  __ASSERT(minWidth >= 0, 22, (CHAR*)"bbStrings", 13339);
  if (form == -1) {
    base = 16;
  } else if (form == -2) {
    base = 16;
  } else {
    base = form;
  }
  if (form == -3) {
    __ASSERT(x > 0 && x < 3999, 21, (CHAR*)"bbStrings", 15139);
    base = 1000;
    i = 0;
    mSign = 0;
    while (base > 0 && x > 0) {
      if (base == 1) {
        c1 = 'I';
        c5 = 'V';
        c10 = 'X';
      } else if (base == 10) {
        c1 = 'X';
        c5 = 'L';
        c10 = 'C';
      } else if (base == 100) {
        c1 = 'C';
        c5 = 'D';
        c10 = 'M';
      } else {
        c1 = 'M';
      }
      k = (INTEGER)__DIVFL(x, (LONGINT)base);
      x = __MODFL(x, (LONGINT)base);
      if (__IN(k, 0x0210)) {
        a[__X(i, 128, (CHAR*)"bbStrings", 17442)] = c1;
        i += 1;
      }
      if (__IN(k, 0x01f0)) {
        a[__X(i, 128, (CHAR*)"bbStrings", 17700)] = c5;
        i += 1;
      }
      if (k == 9) {
        a[__X(i, 128, (CHAR*)"bbStrings", 17949)] = c10;
        i += 1;
      } else if (__IN(k, 0x01ce)) {
        j = __MOD(k, 5);
        do {
          a[__X(i, 128, (CHAR*)"bbStrings", 18710)] = c1;
          i += 1;
          j -= 1;
        } while (!(j == 0));
      }
      base = __DIV(base, 10);
    }
  } else if (form == -2 || form == -1) {
    i = 0;
    mSign = 0;
    if (showBase) {
      minWidth -= 1;
    }
    do {
      a[__X(i, 128, (CHAR*)"bbStrings", 20766)] = bbStrings_digits[__X(__MODFL(x, (LONGINT)base), 17, (CHAR*)"bbStrings", 20766)];
      x = __DIVFL(x, (LONGINT)base);
      i += 1;
    } while (!((x == 0 || x == -1) || i == 128));
    if (x == -1) {
      fillCh = 'F';
    }
  } else {
    if (x < 0) {
      i = 0;
      mSign = 1;
      minWidth -= 1;
      do {
        if (__MODFL(x, (LONGINT)base) == 0) {
          a[__X(i, 128, (CHAR*)"bbStrings", 22807)] = bbStrings_digits[0];
          x = __DIVFL(x, (LONGINT)base);
        } else {
          a[__X(i, 128, (CHAR*)"bbStrings", 23335)] = bbStrings_digits[__X((LONGINT)base - __MODFL(x, (LONGINT)base), 17, (CHAR*)"bbStrings", 23335)];
          x = __DIVFL(x, (LONGINT)base) + 1;
        }
        i += 1;
      } while (!(x == 0 || i == 128));
    } else {
      i = 0;
      mSign = 0;
      do {
        a[__X(i, 128, (CHAR*)"bbStrings", 25119)] = bbStrings_digits[__X(__MODFL(x, (LONGINT)base), 17, (CHAR*)"bbStrings", 25119)];
        x = __DIVFL(x, (LONGINT)base);
        i += 1;
      } while (!(x == 0 || i == 128));
    }
    if (showBase) {
      minWidth -= 1;
      if (base < 10) {
        minWidth -= 1;
      } else {
        minWidth -= 2;
      }
    }
  }
  si = 0;
  if ((mSign && fillCh == '0') && si < s__len) {
    s[__X(si, s__len, (CHAR*)"bbStrings", 27197)] = '-';
    si += 1;
    mSign = 0;
  }
  while (minWidth > i) {
    if (si < s__len) {
      s[__X(si, s__len, (CHAR*)"bbStrings", 27686)] = fillCh;
      si += 1;
    }
    minWidth -= 1;
  }
  if (mSign && si < s__len) {
    s[__X(si, s__len, (CHAR*)"bbStrings", 28460)] = '-';
    si += 1;
  }
  if (form == -3) {
    j = 0;
    while (j < i) {
      if (si < s__len) {
        s[__X(si, s__len, (CHAR*)"bbStrings", 29477)] = a[__X(j, 128, (CHAR*)"bbStrings", 29477)];
        si += 1;
      }
      j += 1;
    }
  } else {
    do {
      i -= 1;
      if (si < s__len) {
        s[__X(si, s__len, (CHAR*)"bbStrings", 30757)] = a[__X(i, 128, (CHAR*)"bbStrings", 30757)];
        si += 1;
      }
    } while (!(i == 0));
  }
  if (showBase && form != -3) {
    if (form == -1 && si < s__len) {
      s[__X(si, s__len, (CHAR*)"bbStrings", 31801)] = 'X';
      si += 1;
    } else if (form == -2 && si < s__len) {
      s[__X(si, s__len, (CHAR*)"bbStrings", 32063)] = 'H';
      si += 1;
    } else if (form < 10 && si < s__len - 1) {
      s[__X(si, s__len, (CHAR*)"bbStrings", 32312)] = '%';
      s[__X(si + 1, s__len, (CHAR*)"bbStrings", 32337)] = bbStrings_digits[__X(base, 17, (CHAR*)"bbStrings", 32337)];
      si += 2;
    } else if (si < s__len - 2) {
      s[__X(si, s__len, (CHAR*)"bbStrings", 32784)] = '%';
      s[__X(si + 1, s__len, (CHAR*)"bbStrings", 32816)] = bbStrings_digits[__X(__DIV(base, 10), 17, (CHAR*)"bbStrings", 32816)];
      s[__X(si + 2, s__len, (CHAR*)"bbStrings", 32848)] = bbStrings_digits[__X(__MOD(base, 10), 17, (CHAR*)"bbStrings", 32848)];
      si += 3;
    }
  }
  if (si < s__len) {
    s[__X(si, s__len, (CHAR*)"bbStrings", 33569)] = 0x00;
  } else {
    __HALT(23, (CHAR*)"bbStrings", 33583);
  }
}

/*----------------------------------------------------------------------------*/
void bbStrings_StringToInt (LONGCHAR *s, INTEGER s__len, INTEGER *x, INTEGER *res)
{
  INTEGER i, j, k, digits;
  LONGCHAR ch, top;
  BOOLEAN neg;
  INTEGER base;
  *res = 0;
  i = 0;
  ch = s[0];
  while ((((ch != 0x00 && ch <= ' ') || ch == 0x8b) || ch == 0x8f) || ch == 0xa0) {
    i += 1;
    ch = s[__X(i, s__len, (CHAR*)"bbStrings", 36095)];
  }
  j = i;
  top = '0';
  while (((ch != 0x00 && ch != 'H') && ch != 'X') && ch != '%') {
    if (ch > top) {
      top = ch;
    }
    j += 1;
    ch = s[__X(j, s__len, (CHAR*)"bbStrings", 37375)];
  }
  if (ch == 'H' || ch == 'X') {
    *x = 0;
    ch = s[__X(i, s__len, (CHAR*)"bbStrings", 37909)];
    if (('0' <= ch && ch <= '9') || ('A' <= ch && ch <= 'F')) {
      while (ch == '0') {
        i += 1;
        ch = s[__X(i, s__len, (CHAR*)"bbStrings", 38440)];
      }
      digits = 0;
      while (*res == 0 && (('0' <= ch && ch <= '9') || ('A' <= ch && ch <= 'F'))) {
        if (ch < 'A') {
          k = (INTEGER)ch - 48;
        } else {
          k = ((INTEGER)ch - 65) + 10;
        }
        if (digits < 8) {
          *x = __MASK(*x, -268435456);
          if (*x >= 134217728) {
            *x = *x - 268435456;
          }
          *x = __ASHL(*x, 4, INTEGER) + k;
          i += 1;
          ch = s[__X(i, s__len, (CHAR*)"bbStrings", 40959)];
        } else {
          *res = 1;
        }
        digits += 1;
      }
      if (*res == 0) {
        if ((ch != 'H' && ch != 'X') || s[__X(i + 1, s__len, (CHAR*)"bbStrings", 42495)] != 0x00) {
          *res = 2;
        }
      }
    } else {
      *res = 2;
    }
  } else {
    if (ch == '%') {
      j += 1;
      ch = s[__X(j, s__len, (CHAR*)"bbStrings", 43798)];
      base = 0;
      if ('0' <= ch && ch <= '9') {
        k = (INTEGER)ch - 48;
        do {
          base = base * 10 + k;
          j += 1;
          ch = s[__X(j, s__len, (CHAR*)"bbStrings", 45080)];
          k = (INTEGER)ch - 48;
        } while (!((ch < '0' || ch > '9') || base > __DIV(2147483647 - k, 10)));
        if ('0' <= ch && ch <= '9') {
          base = 0;
        }
      }
    } else {
      base = 10;
    }
    if (base < 2 || base > 16) {
      *res = 2;
    } else if ((base <= 10 && (INTEGER)top < base + 48) || (base > 10 && (INTEGER)top < (base - 10) + 65)) {
      *x = 0;
      ch = s[__X(i, s__len, (CHAR*)"bbStrings", 48150)];
      neg = 0;
      if (ch == '-') {
        i += 1;
        ch = s[__X(i, s__len, (CHAR*)"bbStrings", 48423)];
        neg = 1;
      } else if (ch == '+') {
        i += 1;
        ch = s[__X(i, s__len, (CHAR*)"bbStrings", 48475)];
      }
      while (ch != 0x00 && ch <= ' ') {
        i += 1;
        ch = s[__X(i, s__len, (CHAR*)"bbStrings", 48695)];
      }
      if (('0' <= ch && ch <= '9') || ('A' <= ch && ch <= 'F')) {
        if (ch <= '9') {
          k = (INTEGER)ch - 48;
        } else {
          k = ((INTEGER)ch - 65) + 10;
        }
        while ((('0' <= ch && ch <= '9') || ('A' <= ch && ch <= 'F')) && *res == 0) {
          if (*x >= __DIVF(((-2147483647-1) + (base - 1)) + k, base)) {
            *x = *x * base - k;
            i += 1;
            ch = s[__X(i, s__len, (CHAR*)"bbStrings", 49964)];
            if (ch <= '9') {
              k = (INTEGER)ch - 48;
            } else {
              k = ((INTEGER)ch - 65) + 10;
            }
          } else {
            *res = 1;
          }
        }
      } else {
        *res = 2;
      }
      if (*res == 0) {
        if (!neg) {
          if (*x > (-2147483647-1)) {
            *x = -*x;
          } else {
            *res = 1;
          }
        }
        if (ch != 0x00 && ch != '%') {
          *res = 2;
        }
      }
    } else {
      *res = 2;
    }
  }
}

/*----------------------------------------------------------------------------*/
void bbStrings_StringToLInt (LONGCHAR *s, INTEGER s__len, LONGINT *x, INTEGER *res)
{
  INTEGER i, j, k, digits;
  LONGCHAR ch, top;
  BOOLEAN neg;
  INTEGER base;
  *res = 0;
  i = 0;
  ch = s[0];
  while ((((ch != 0x00 && ch <= ' ') || ch == 0x8b) || ch == 0x8f) || ch == 0xa0) {
    i += 1;
    ch = s[__X(i, s__len, (CHAR*)"bbStrings", 56575)];
  }
  j = i;
  top = '0';
  while (((ch != 0x00 && ch != 'H') && ch != 'X') && ch != '%') {
    if (ch > top) {
      top = ch;
    }
    j += 1;
    ch = s[__X(j, s__len, (CHAR*)"bbStrings", 57855)];
  }
  if (ch == 'H' || ch == 'X') {
    *x = 0;
    ch = s[__X(i, s__len, (CHAR*)"bbStrings", 58389)];
    if (('0' <= ch && ch <= '9') || ('A' <= ch && ch <= 'F')) {
      while (ch == '0') {
        i += 1;
        ch = s[__X(i, s__len, (CHAR*)"bbStrings", 58920)];
      }
      digits = 0;
      while (*res == 0 && (('0' <= ch && ch <= '9') || ('A' <= ch && ch <= 'F'))) {
        if (ch < 'A') {
          k = (INTEGER)ch - 48;
        } else {
          k = ((INTEGER)ch - 65) + 10;
        }
        if (digits < 16) {
          *x = __MASK(*x, -1152921504606846976LL);
          if (*x >= 576460752303423488LL) {
            *x = *x - 1152921504606846976LL;
          }
          *x = __ASHL(*x, 4, LONGINT) + (LONGINT)k;
          i += 1;
          ch = s[__X(i, s__len, (CHAR*)"bbStrings", 61439)];
        } else {
          *res = 1;
        }
        digits += 1;
      }
      if (*res == 0) {
        if ((ch != 'H' && ch != 'X') || s[__X(i + 1, s__len, (CHAR*)"bbStrings", 62975)] != 0x00) {
          *res = 2;
        }
      }
    } else {
      *res = 2;
    }
  } else {
    if (ch == '%') {
      j += 1;
      ch = s[__X(j, s__len, (CHAR*)"bbStrings", 64278)];
      base = 0;
      if ('0' <= ch && ch <= '9') {
        k = (INTEGER)ch - 48;
        do {
          base = base * 10 + k;
          j += 1;
          ch = s[__X(j, s__len, (CHAR*)"bbStrings", 65560)];
          k = (INTEGER)ch - 48;
        } while (!((ch < '0' || ch > '9') || base > __DIV(2147483647 - k, 10)));
        if ('0' <= ch && ch <= '9') {
          base = 0;
        }
      }
    } else {
      base = 10;
    }
    if (base < 2 || base > 16) {
      *res = 2;
    } else if ((base <= 10 && (INTEGER)top < base + 48) || (base > 10 && (INTEGER)top < (base - 10) + 65)) {
      *x = 0;
      ch = s[__X(i, s__len, (CHAR*)"bbStrings", 68630)];
      neg = 0;
      if (ch == '-') {
        i += 1;
        ch = s[__X(i, s__len, (CHAR*)"bbStrings", 68903)];
        neg = 1;
      } else if (ch == '+') {
        i += 1;
        ch = s[__X(i, s__len, (CHAR*)"bbStrings", 68955)];
      }
      while (ch != 0x00 && ch <= ' ') {
        i += 1;
        ch = s[__X(i, s__len, (CHAR*)"bbStrings", 69175)];
      }
      if (('0' <= ch && ch <= '9') || ('A' <= ch && ch <= 'F')) {
        if (ch <= '9') {
          k = (INTEGER)ch - 48;
        } else {
          k = ((INTEGER)ch - 65) + 10;
        }
        while ((('0' <= ch && ch <= '9') || ('A' <= ch && ch <= 'F')) && *res == 0) {
          if (*x >= __DIVFL(((-9223372036854775807LL-1) + (LONGINT)(base - 1)) + (LONGINT)k, (LONGINT)base)) {
            *x = *x * (LONGINT)base - (LONGINT)k;
            i += 1;
            ch = s[__X(i, s__len, (CHAR*)"bbStrings", 70444)];
            if (ch <= '9') {
              k = (INTEGER)ch - 48;
            } else {
              k = ((INTEGER)ch - 65) + 10;
            }
          } else {
            *res = 1;
          }
        }
      } else {
        *res = 2;
      }
      if (*res == 0) {
        if (!neg) {
          if (*x > (-9223372036854775807LL-1)) {
            *x = -*x;
          } else {
            *res = 1;
          }
        }
        if (ch != 0x00 && ch != '%') {
          *res = 2;
        }
      }
    } else {
      *res = 2;
    }
  }
}

/*----------------------------------------------------------------------------*/
void bbStrings_RealToStringForm (REAL x, INTEGER precision, INTEGER minW, INTEGER expW, LONGCHAR fillCh, LONGCHAR *s, INTEGER s__len)
{
  INTEGER exp, len, i, j, n, k, p;
  LONGCHAR m[80];
  BOOLEAN neg;
  __ASSERT(precision > 0, 20, (CHAR*)"bbStrings", 77109);
  __ASSERT(minW >= 0 && minW < s__len, 21, (CHAR*)"bbStrings", 77355);
  __ASSERT(expW > -s__len && expW <= 3, 22, (CHAR*)"bbStrings", 77612);
  exp = bbMath_Exponent(x);
  if (exp == 2147483647) {
    if (fillCh == '0') {
      fillCh = 0x8f;
    }
    x = bbMath_Mantissa(x);
    if (x == (REAL)-1) {
      __MOVE(((LONGCHAR[]){45, 105, 110, 102, 0}), m, 10);
      n = 4;
    } else if (x == (REAL)1) {
      __MOVE(((LONGCHAR[]){105, 110, 102, 0}), m, 8);
      n = 3;
    } else {
      __MOVE(((LONGCHAR[]){110, 97, 110, 0}), m, 8);
      n = 3;
    }
    i = 0;
    j = 0;
    while (minW > n) {
      s[__X(i, s__len, (CHAR*)"bbStrings", 80163)] = fillCh;
      i += 1;
      minW -= 1;
    }
    while (j <= n && i < s__len) {
      s[__X(i, s__len, (CHAR*)"bbStrings", 80432)] = m[__X(j, 80, (CHAR*)"bbStrings", 80432)];
      i += 1;
      j += 1;
    }
  } else {
    neg = 0;
    len = 1;
    __MOVE(((LONGCHAR[]){48, 48, 0}), m, 6);
    if (x < (REAL)0) {
      x = -x;
      neg = 1;
      minW -= 1;
    }
    if (x != (REAL)0) {
      exp = __DIV((exp - 8) * 30103, 100000);
      if (exp > 0) {
        n = (INTEGER)__ENTIER(x / bbMath_IntPower((REAL)10, exp));
        x = x / bbMath_IntPower((REAL)10, exp) - (REAL)n;
      } else if (exp > -bbStrings_maxExp) {
        n = (INTEGER)__ENTIER(x * bbMath_IntPower((REAL)10, -exp));
        x = x * bbMath_IntPower((REAL)10, -exp) - (REAL)n;
      } else {
        n = (INTEGER)__ENTIER(((x * bbMath_IntPower((REAL)10, -exp - __ASHL(bbStrings_maxDig, 1, INTEGER))) * bbStrings_factor) * bbStrings_factor);
        x = ((x * bbMath_IntPower((REAL)10, -exp - __ASHL(bbStrings_maxDig, 1, INTEGER))) * bbStrings_factor) * bbStrings_factor - (REAL)n;
      }
      p = precision - 4;
      if (n < 1000) {
        p += 1;
      }
      if (expW < 0 && p > exp - expW) {
        p = exp - expW;
      }
      if (p >= 0) {
        x = x + 0.5 / bbMath_IntPower((REAL)10, p);
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
        m[__X(i, 80, (CHAR*)"bbStrings", 88862)] = (LONGCHAR)(p + 48);
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
      s[__X(i, s__len, (CHAR*)"bbStrings", 95275)] = '-';
      i += 1;
      neg = 0;
    }
    while (j > 0) {
      s[__X(i, s__len, (CHAR*)"bbStrings", 95520)] = fillCh;
      i += 1;
      j -= 1;
    }
    if (neg && i < s__len) {
      s[__X(i, s__len, (CHAR*)"bbStrings", 95785)] = '-';
      i += 1;
    }
    j = 0;
    while (n > 0 && i < s__len) {
      if (p <= 0 && j < len) {
        s[__X(i, s__len, (CHAR*)"bbStrings", 96557)] = m[__X(j, 80, (CHAR*)"bbStrings", 96557)];
        j += 1;
      } else {
        s[__X(i, s__len, (CHAR*)"bbStrings", 96582)] = '0';
      }
      i += 1;
      n -= 1;
      p -= 1;
    }
    if (i < s__len) {
      s[__X(i, s__len, (CHAR*)"bbStrings", 97313)] = '.';
      i += 1;
    }
    while (k > 0 && i < s__len) {
      if (p <= 0 && j < len) {
        s[__X(i, s__len, (CHAR*)"bbStrings", 97837)] = m[__X(j, 80, (CHAR*)"bbStrings", 97837)];
        j += 1;
      } else {
        s[__X(i, s__len, (CHAR*)"bbStrings", 97862)] = '0';
      }
      i += 1;
      k -= 1;
      p -= 1;
    }
    if (expW > 0) {
      if (i < s__len) {
        s[__X(i, s__len, (CHAR*)"bbStrings", 98850)] = 'E';
        i += 1;
      }
      if (i < s__len) {
        if (exp < 0) {
          s[__X(i, s__len, (CHAR*)"bbStrings", 99360)] = '-';
          exp = -exp;
        } else {
          s[__X(i, s__len, (CHAR*)"bbStrings", 99390)] = '+';
        }
        i += 1;
      }
      if (expW == 3 && i < s__len) {
        s[__X(i, s__len, (CHAR*)"bbStrings", 100169)] = (LONGCHAR)(__DIV(exp, 100) + 48);
        i += 1;
      }
      if (expW >= 2 && i < s__len) {
        s[__X(i, s__len, (CHAR*)"bbStrings", 100432)] = (LONGCHAR)(__MOD(__DIV(exp, 10), 10) + 48);
        i += 1;
      }
      if (i < s__len) {
        s[__X(i, s__len, (CHAR*)"bbStrings", 100665)] = (LONGCHAR)(__MOD(exp, 10) + 48);
        i += 1;
      }
    }
  }
  if (i < s__len) {
    s[__X(i, s__len, (CHAR*)"bbStrings", 101407)] = 0x00;
  } else {
    __HALT(23, (CHAR*)"bbStrings", 101421);
  }
}

/*----------------------------------------------------------------------------*/
void bbStrings_RealToString (REAL x, LONGCHAR *s, INTEGER s__len)
{
  bbStrings_RealToStringForm(x, 16, 0, 0, 0x8f, (void*)s, s__len);
}

/*----------------------------------------------------------------------------*/
void bbStrings_StringToReal (LONGCHAR *s, INTEGER s__len, REAL *x, INTEGER *res)
{
  INTEGER first, last, point, e, n, i, exp;
  REAL y;
  LONGCHAR ch;
  BOOLEAN neg, negExp, dig;
  *res = 0;
  i = 0;
  ch = s[0];
  dig = 0;
  while ((((ch != 0x00 && ch <= ' ') || ch == 0x8b) || ch == 0x8f) || ch == 0xa0) {
    i += 1;
    ch = s[__X(i, s__len, (CHAR*)"bbStrings", 104800)];
  }
  if (ch == '+') {
    neg = 0;
    i += 1;
    ch = s[__X(i, s__len, (CHAR*)"bbStrings", 105471)];
  } else if (ch == '-') {
    neg = 1;
    i += 1;
    ch = s[__X(i, s__len, (CHAR*)"bbStrings", 105983)];
  } else {
    neg = 0;
  }
  while (ch == '0') {
    i += 1;
    ch = s[__X(i, s__len, (CHAR*)"bbStrings", 106790)];
    dig = 1;
  }
  first = i;
  e = 0;
  while ('0' <= ch && ch <= '9') {
    i += 1;
    ch = s[__X(i, s__len, (CHAR*)"bbStrings", 107319)];
    e += 1;
    dig = 1;
  }
  point = i;
  if (ch == '.') {
    i += 1;
    ch = s[__X(i, s__len, (CHAR*)"bbStrings", 108053)];
    if (e == 0) {
      while (ch == '0') {
        i += 1;
        ch = s[__X(i, s__len, (CHAR*)"bbStrings", 108584)];
        e -= 1;
        dig = 1;
      }
      first = i;
    }
    while ('0' <= ch && ch <= '9') {
      i += 1;
      ch = s[__X(i, s__len, (CHAR*)"bbStrings", 109368)];
      dig = 1;
    }
  }
  last = i - 1;
  exp = 0;
  if (ch == 'E' || ch == 'D') {
    i += 1;
    ch = s[__X(i, s__len, (CHAR*)"bbStrings", 110357)];
    negExp = 0;
    if (ch == '-') {
      negExp = 1;
      i += 1;
      ch = s[__X(i, s__len, (CHAR*)"bbStrings", 110847)];
    } else if (ch == '+') {
      i += 1;
      ch = s[__X(i, s__len, (CHAR*)"bbStrings", 111103)];
    }
    while (('0' <= ch && ch <= '9') && exp < 1000) {
      exp = exp * 10 + ((INTEGER)ch - 48);
      i += 1;
      ch = s[__X(i, s__len, (CHAR*)"bbStrings", 112127)];
    }
    if (negExp) {
      exp = -exp;
    }
  }
  exp = exp + e;
  *x = (REAL)0;
  y = (REAL)0;
  n = 0;
  while (n < bbStrings_maxDig && first <= last) {
    if (first != point) {
      *x = *x * (REAL)10 + (REAL)((INTEGER)s[__X(first, s__len, (CHAR*)"bbStrings", 113473)] - 48);
      n += 1;
    }
    first += 1;
  }
  while (last >= first) {
    if (last != point) {
      y = (y + (REAL)((INTEGER)s[__X(last, s__len, (CHAR*)"bbStrings", 114497)] - 48)) / (REAL)(REAL)10;
    }
    last -= 1;
  }
  if (!dig || ch != 0x00) {
    *res = 2;
  } else if (exp < -bbStrings_maxExp - bbStrings_maxDig) {
    *x = (REAL)0;
  } else if (exp < -bbStrings_maxExp + bbStrings_maxDig) {
    *x = (((*x + y) / bbMath_IntPower((REAL)10, (n - exp) - __ASHL(bbStrings_maxDig, 1, INTEGER))) / bbStrings_factor) / bbStrings_factor;
  } else if (exp < n) {
    *x = (*x + y) / bbMath_IntPower((REAL)10, n - exp);
  } else if (exp < bbStrings_maxExp) {
    *x = (*x + y) * bbMath_IntPower((REAL)10, exp - n);
  } else if (exp == bbStrings_maxExp) {
    *x = (*x + y) * (bbMath_IntPower((REAL)10, exp - n) / (REAL)(REAL)16);
    if (*x <= 1.1235582092889467e+307) {
      *x = *x * (REAL)16;
    } else {
      *res = 1;
    }
  } else {
    *res = 1;
  }
  if (neg) {
    *x = -*x;
  }
}

/*----------------------------------------------------------------------------*/
static struct SetToString__17 {
  LONGCHAR *str;
  INTEGER str__len;
  INTEGER *len;
  struct SetToString__17 *lnk;
} *SetToString__17_s;

static void __18 (LONGCHAR ch);
static void __20 (INTEGER x);

static void __18 (LONGCHAR ch)
{
  __ASSERT((*SetToString__17_s->len) < SetToString__17_s->str__len, 23, (CHAR*)"bbStrings", 122146);
  SetToString__17_s->str[__X((*SetToString__17_s->len), SetToString__17_s->str__len, (CHAR*)"bbStrings", 122162)] = ch;
  (*SetToString__17_s->len) += 1;
}

static void __20 (INTEGER x)
{
  INTEGER i;
  LONGCHAR ch;
  LONGCHAR buf[32];
  bbStrings_IntToString(x, (void*)buf, 32);
  ch = buf[0];
  i = 0;
  while (ch != 0x00) {
    __18(ch);
    i += 1;
    ch = buf[__X(i, 32, (CHAR*)"bbStrings", 124216)];
  }
}

void bbStrings_SetToString (SET x, LONGCHAR *str, INTEGER str__len)
{
  INTEGER len, i;
  struct SetToString__17 _s;
  _s.str = (void*)str; _s.str__len = str__len;
  _s.len = &len;
  _s.lnk = SetToString__17_s;
  SetToString__17_s = &_s;
  len = 0;
  __18('{');
  i = 0;
  while (x != 0x0) {
    if (__IN(i, x)) {
      __20(i);
      x &= ~__SETOF(i);
      if ((i <= 29 && __IN(i + 1, x)) && __IN(i + 2, x)) {
        __18('.');
        __18('.');
        x = x & ~(__SETOF(i + 1) | __SETOF(i + 2));
        i += 3;
        while (i <= 31 && __IN(i, x)) {
          x &= ~__SETOF(i);
          i += 1;
        }
        __20(i - 1);
      }
      if (x != 0x0) {
        __18(',');
        __18(' ');
      }
    }
    i += 1;
  }
  __18('}');
  __18(0x00);
  SetToString__17_s = _s.lnk;
}

/*----------------------------------------------------------------------------*/
static struct StringToSet__25 {
  LONGCHAR *s;
  INTEGER s__len;
  SET *x;
  INTEGER *res;
  INTEGER *next, *x1;
  LONGCHAR *ch;
  struct StringToSet__25 *lnk;
} *StringToSet__25_s;

static void __26 (void);
static INTEGER __28 (void);
static void __30 (void);

static void __26 (void)
{
  (*StringToSet__25_s->ch) = StringToSet__25_s->s[__X((*StringToSet__25_s->next), StringToSet__25_s->s__len, (CHAR*)"bbStrings", 130325)];
  while ((*StringToSet__25_s->ch) <= ' ' && (*StringToSet__25_s->ch) != 0x00) {
    (*StringToSet__25_s->next) += 1;
    (*StringToSet__25_s->ch) = StringToSet__25_s->s[__X((*StringToSet__25_s->next), StringToSet__25_s->s__len, (CHAR*)"bbStrings", 130620)];
  }
  if ((*StringToSet__25_s->ch) != 0x00) {
    (*StringToSet__25_s->next) += 1;
  }
}

static INTEGER __28 (void)
{
  INTEGER intval;
  intval = (INTEGER)(*StringToSet__25_s->ch) - 48;
  (*StringToSet__25_s->ch) = StringToSet__25_s->s[__X((*StringToSet__25_s->next), StringToSet__25_s->s__len, (CHAR*)"bbStrings", 132624)];
  while ('0' <= (*StringToSet__25_s->ch) && (*StringToSet__25_s->ch) <= '9') {
    intval = (intval * 10 + (INTEGER)(*StringToSet__25_s->ch)) - 48;
    if (intval > 31) {
      *StringToSet__25_s->res = 1;
      intval = 0;
    }
    (*StringToSet__25_s->next) += 1;
    (*StringToSet__25_s->ch) = StringToSet__25_s->s[__X((*StringToSet__25_s->next), StringToSet__25_s->s__len, (CHAR*)"bbStrings", 133887)];
  }
  __26();
  return intval;
}

static void __30 (void)
{
  INTEGER x2, i, _for__32;
  (*StringToSet__25_s->ch) = StringToSet__25_s->s[__X((*StringToSet__25_s->next), StringToSet__25_s->s__len, (CHAR*)"bbStrings", 135952)];
  (*StringToSet__25_s->next) += 1;
  if ((*StringToSet__25_s->ch) == '.') {
    __26();
    if ('0' <= (*StringToSet__25_s->ch) && (*StringToSet__25_s->ch) <= '9') {
      x2 = __28();
      if (*StringToSet__25_s->res == 0) {
        if (x2 >= (*StringToSet__25_s->x1)) {
          _for__32 = x2;
          i = (*StringToSet__25_s->x1);
          while (i <= _for__32) {
            *StringToSet__25_s->x |= __SETOF(i);
            i += 1;
          }
        } else {
          *StringToSet__25_s->res = 2;
        }
      }
    } else {
      *StringToSet__25_s->res = 2;
    }
  } else {
    *StringToSet__25_s->res = 2;
  }
}

void bbStrings_StringToSet (LONGCHAR *s, INTEGER s__len, SET *x, INTEGER *res)
{
  INTEGER next, x1;
  LONGCHAR ch;
  struct StringToSet__25 _s;
  _s.s = (void*)s; _s.s__len = s__len;
  _s.x = x;
  _s.res = res;
  _s.next = &next;
  _s.x1 = &x1;
  _s.ch = &ch;
  _s.lnk = StringToSet__25_s;
  StringToSet__25_s = &_s;
  *x = 0x0;
  *res = 0;
  next = 0;
  __26();
  if (ch == '{') {
    __26();
    while (('0' <= ch && ch <= '9') && *res != 2) {
      x1 = __28();
      if (ch == '.') {
        __30();
      } else if (*res == 0) {
        *x |= __SETOF(x1);
      }
      if (ch == ',') {
        __26();
      }
    }
    if (ch == '}') {
      __26();
      if (ch != 0x00) {
        *res = 2;
      }
    } else {
      *res = 2;
    }
  } else {
    *res = 2;
  }
  StringToSet__25_s = _s.lnk;
}

/*----------------------------------------------------------------------------*/
BOOLEAN bbStrings_IsUpper (LONGCHAR ch)
{
  if ((INTEGER)ch < 256) {
    return bbStrings_toLower[__X((INTEGER)ch, 256, (CHAR*)"bbStrings", 144948)] != ch;
  } else {
    return bbKernel_IsUpper(ch);
  }
  __RETCHK((CHAR*)"bbStrings", 144979);
}

/*----------------------------------------------------------------------------*/
LONGCHAR bbStrings_Upper (LONGCHAR ch)
{
  if ((INTEGER)ch < 256) {
    return bbStrings_toUpper[__X((INTEGER)ch, 256, (CHAR*)"bbStrings", 146223)];
  } else {
    return bbKernel_Upper(ch);
  }
  __RETCHK((CHAR*)"bbStrings", 146252);
}

/*----------------------------------------------------------------------------*/
BOOLEAN bbStrings_IsLower (LONGCHAR ch)
{
  if ((INTEGER)ch < 256) {
    return bbStrings_toUpper[__X((INTEGER)ch, 256, (CHAR*)"bbStrings", 147508)] != ch;
  } else {
    return bbKernel_IsLower(ch);
  }
  __RETCHK((CHAR*)"bbStrings", 147539);
}

/*----------------------------------------------------------------------------*/
LONGCHAR bbStrings_Lower (LONGCHAR ch)
{
  if ((INTEGER)ch < 256) {
    return bbStrings_toLower[__X((INTEGER)ch, 256, (CHAR*)"bbStrings", 148783)];
  } else {
    return bbKernel_Lower(ch);
  }
  __RETCHK((CHAR*)"bbStrings", 148812);
}

/*----------------------------------------------------------------------------*/
BOOLEAN bbStrings_IsAlpha (LONGCHAR ch)
{
  switch (ch) {
    case 'a': case 'b': case 'c': case 'd': case 'e': 
    case 'f': case 'g': case 'h': case 'i': case 'j': 
    case 'k': case 'l': case 'm': case 'n': case 'o': 
    case 'p': case 'q': case 'r': case 's': case 't': 
    case 'u': case 'v': case 'w': case 'x': case 'y': 
    case 'z': case 'A': case 'B': case 'C': case 'D': 
    case 'E': case 'F': case 'G': case 'H': case 'I': 
    case 'J': case 'K': case 'L': case 'M': case 'N': 
    case 'O': case 'P': case 'Q': case 'R': case 'S': 
    case 'T': case 'U': case 'V': case 'W': case 'X': 
    case 'Y': case 'Z': 
      return 1;
      break;
    default: 
      if (ch > 0x7f) {
        return bbKernel_IsAlpha(ch);
      } else {
        return 0;
      }
      break;
  }
  __RETCHK((CHAR*)"bbStrings", 150847);
}

/*----------------------------------------------------------------------------*/
BOOLEAN bbStrings_IsNumeric (LONGCHAR ch)
{
  return '0' <= ch && ch <= '9';
}

/*----------------------------------------------------------------------------*/
BOOLEAN bbStrings_IsAlphaNumeric (LONGCHAR ch)
{
  return bbStrings_IsAlpha(ch) || bbStrings_IsNumeric(ch);
}

/*----------------------------------------------------------------------------*/
BOOLEAN bbStrings_IsIdentStart (LONGCHAR ch)
{
  switch (ch) {
    case 'a': case 'b': case 'c': case 'd': case 'e': 
    case 'f': case 'g': case 'h': case 'i': case 'j': 
    case 'k': case 'l': case 'm': case 'n': case 'o': 
    case 'p': case 'q': case 'r': case 's': case 't': 
    case 'u': case 'v': case 'w': case 'x': case 'y': 
    case 'z': case 'A': case 'B': case 'C': case 'D': 
    case 'E': case 'F': case 'G': case 'H': case 'I': 
    case 'J': case 'K': case 'L': case 'M': case 'N': 
    case 'O': case 'P': case 'Q': case 'R': case 'S': 
    case 'T': case 'U': case 'V': case 'W': case 'X': 
    case 'Y': case 'Z': case '_': 
      return 1;
      break;
    default: 
      if (ch > 0x7f) {
        return bbKernel_IsAlpha(ch);
      } else {
        return 0;
      }
      break;
  }
  __RETCHK((CHAR*)"bbStrings", 156223);
}

/*----------------------------------------------------------------------------*/
BOOLEAN bbStrings_IsIdent (LONGCHAR ch)
{
  switch (ch) {
    case 'a': case 'b': case 'c': case 'd': case 'e': 
    case 'f': case 'g': case 'h': case 'i': case 'j': 
    case 'k': case 'l': case 'm': case 'n': case 'o': 
    case 'p': case 'q': case 'r': case 's': case 't': 
    case 'u': case 'v': case 'w': case 'x': case 'y': 
    case 'z': case 'A': case 'B': case 'C': case 'D': 
    case 'E': case 'F': case 'G': case 'H': case 'I': 
    case 'J': case 'K': case 'L': case 'M': case 'N': 
    case 'O': case 'P': case 'Q': case 'R': case 'S': 
    case 'T': case 'U': case 'V': case 'W': case 'X': 
    case 'Y': case 'Z': case '_': case '0': case '1': 
    case '2': case '3': case '4': case '5': case '6': 
    case '7': case '8': case '9': 
      return 1;
      break;
    default: 
      if (ch > 0x7f) {
        return bbKernel_IsAlpha(ch);
      } else {
        return 0;
      }
      break;
  }
  __RETCHK((CHAR*)"bbStrings", 158783);
}

/*----------------------------------------------------------------------------*/
BOOLEAN bbStrings_Valid (LONGCHAR *s, INTEGER s__len)
{
  INTEGER i;
  i = 0;
  while (i < s__len && s[__X(i, s__len, (CHAR*)"bbStrings", 161058)] != 0x00) {
    i += 1;
  }
  return i < s__len;
}

/*----------------------------------------------------------------------------*/
void bbStrings_ToUpper (LONGCHAR *in, INTEGER in__len, LONGCHAR *out, INTEGER out__len)
{
  INTEGER i, max;
  i = 0;
  max = out__len - 1;
  while (in[__X(i, in__len, (CHAR*)"bbStrings", 162848)] != 0x00 && i < max) {
    if ((INTEGER)in[__X(i, in__len, (CHAR*)"bbStrings", 163168)] < 256) {
      out[__X(i, out__len, (CHAR*)"bbStrings", 163129)] = bbStrings_toUpper[__X((INTEGER)in[__X(i, in__len, (CHAR*)"bbStrings", 163129)], 256, (CHAR*)"bbStrings", 163129)];
    } else {
      out[__X(i, out__len, (CHAR*)"bbStrings", 163164)] = bbKernel_Upper(in[__X(i, in__len, (CHAR*)"bbStrings", 163164)]);
    }
    i += 1;
  }
  out[__X(i, out__len, (CHAR*)"bbStrings", 164095)] = 0x00;
}

/*----------------------------------------------------------------------------*/
void bbStrings_ToLower (LONGCHAR *in, INTEGER in__len, LONGCHAR *out, INTEGER out__len)
{
  INTEGER i, max;
  i = 0;
  max = out__len - 1;
  while (in[__X(i, in__len, (CHAR*)"bbStrings", 165408)] != 0x00 && i < max) {
    if ((INTEGER)in[__X(i, in__len, (CHAR*)"bbStrings", 165728)] < 256) {
      out[__X(i, out__len, (CHAR*)"bbStrings", 165689)] = bbStrings_toLower[__X((INTEGER)in[__X(i, in__len, (CHAR*)"bbStrings", 165689)], 256, (CHAR*)"bbStrings", 165689)];
    } else {
      out[__X(i, out__len, (CHAR*)"bbStrings", 165724)] = bbKernel_Lower(in[__X(i, in__len, (CHAR*)"bbStrings", 165724)]);
    }
    i += 1;
  }
  out[__X(i, out__len, (CHAR*)"bbStrings", 166655)] = 0x00;
}

/*----------------------------------------------------------------------------*/
void bbStrings_Utf8ToString (CHAR *in, INTEGER in__len, LONGCHAR *out, INTEGER out__len, INTEGER *res)
{
  bbKernel_Utf8ToString((void*)in, in__len, (void*)out, out__len, res);
}

/*----------------------------------------------------------------------------*/
void bbStrings_StringToUtf8 (LONGCHAR *in, INTEGER in__len, CHAR *out, INTEGER out__len, INTEGER *res)
{
  bbKernel_StringToUtf8((void*)in, in__len, (void*)out, out__len, res);
}

/*----------------------------------------------------------------------------*/
void bbStrings_Replace (LONGCHAR *s, INTEGER s__len, INTEGER pos, INTEGER len, LONGCHAR *rep, INTEGER rep__len)
{
  INTEGER i, j, k, max, lenS;
  LONGCHAR ch;
  __ASSERT(len >= 0, 20, (CHAR*)"bbStrings", 171030);
  __ASSERT(pos >= 0, 21, (CHAR*)"bbStrings", 171052);
  lenS = __STRLENL(s, s__len, (CHAR*)"bbStrings", 171281);
  max = s__len - 1;
  if (pos <= lenS) {
    i = pos;
    j = 0;
    ch = rep[0];
    if (pos + len > lenS) {
      len = lenS - pos;
    }
    while (ch != 0x00 && len > 0) {
      s[__X(i, s__len, (CHAR*)"bbStrings", 172302)] = ch;
      i += 1;
      j += 1;
      len -= 1;
      ch = rep[__X(j, rep__len, (CHAR*)"bbStrings", 172543)];
    }
    if (len > 0) {
      do {
        ch = s[__X(i + len, s__len, (CHAR*)"bbStrings", 173081)];
        s[__X(i, s__len, (CHAR*)"bbStrings", 173093)] = ch;
        i += 1;
      } while (!(ch == 0x00));
    } else if (ch != 0x00) {
      len = __STRLENL(rep, rep__len, (CHAR*)"bbStrings", 173592) - j;
      k = lenS + len;
      if (k > max) {
        k = max;
      }
      s[__X(k, s__len, (CHAR*)"bbStrings", 174094)] = 0x00;
      k -= 1;
      while (k - len >= i) {
        s[__X(k, s__len, (CHAR*)"bbStrings", 174378)] = s[__X(k - len, s__len, (CHAR*)"bbStrings", 174378)];
        k -= 1;
      }
      while (rep[__X(j, rep__len, (CHAR*)"bbStrings", 174627)] != 0x00 && i < max) {
        s[__X(i, s__len, (CHAR*)"bbStrings", 174645)] = rep[__X(j, rep__len, (CHAR*)"bbStrings", 174645)];
        i += 1;
        j += 1;
      }
    }
  }
}

/*----------------------------------------------------------------------------*/
void bbStrings_Extract (LONGCHAR *s, INTEGER s__len, INTEGER pos, INTEGER len, LONGCHAR *res, INTEGER res__len)
{
  INTEGER i, j, max;
  __DUP(s, s__len);
  __ASSERT(len >= 0, 20, (CHAR*)"bbStrings", 176662);
  __ASSERT(pos >= 0, 21, (CHAR*)"bbStrings", 176684);
  i = 0;
  j = 0;
  max = res__len - 1;
  while (i < pos && s[__X(i, s__len, (CHAR*)"bbStrings", 177183)] != 0x00) {
    i += 1;
  }
  while ((j < len && j < max) && s[__X(i, s__len, (CHAR*)"bbStrings", 177451)] != 0x00) {
    res[__X(j, res__len, (CHAR*)"bbStrings", 177469)] = s[__X(i, s__len, (CHAR*)"bbStrings", 177469)];
    j += 1;
    i += 1;
  }
  res[__X(j, res__len, (CHAR*)"bbStrings", 177919)] = 0x00;
}

/*----------------------------------------------------------------------------*/
void bbStrings_Find (LONGCHAR *s, INTEGER s__len, LONGCHAR *pat, INTEGER pat__len, INTEGER start, INTEGER *pos)
{
  INTEGER j;
  __ASSERT(start >= 0, 20, (CHAR*)"bbStrings", 179224);
  if (start == 0 || start <= __STRLENL(s, s__len, (CHAR*)"bbStrings", 181509) - __STRLENL(pat, pat__len, (CHAR*)"bbStrings", 181509)) {
    *pos = start;
    while (s[__X(*pos, s__len, (CHAR*)"bbStrings", 180244)] != 0x00) {
      j = 0;
      while (s[__X(*pos + j, s__len, (CHAR*)"bbStrings", 180525)] == pat[__X(j, pat__len, (CHAR*)"bbStrings", 180525)] && pat[__X(j, pat__len, (CHAR*)"bbStrings", 180525)] != 0x00) {
        j += 1;
      }
      if (pat[__X(j, pat__len, (CHAR*)"bbStrings", 180770)] == 0x00) {
        return;
      }
      *pos += 1;
    }
  }
  *pos = -1;
}

/*----------------------------------------------------------------------------*/
static void bbStrings_Init (void)
{
  INTEGER i;
  i = 0;
  while (i <= 255) {
    bbStrings_toUpper[__X(i, 256, (CHAR*)"bbStrings", 183340)] = (LONGCHAR)i;
    bbStrings_toLower[__X(i, 256, (CHAR*)"bbStrings", 183362)] = (LONGCHAR)i;
    i += 1;
  }
  i = 65;
  while (i <= 90) {
    bbStrings_toLower[__X(i, 256, (CHAR*)"bbStrings", 183612)] = (LONGCHAR)(i + 32);
    bbStrings_toUpper[__X(i + 32, 256, (CHAR*)"bbStrings", 183639)] = (LONGCHAR)i;
    i += 1;
  }
  i = 192;
  while (i <= 214) {
    bbStrings_toLower[__X(i, 256, (CHAR*)"bbStrings", 183869)] = (LONGCHAR)(i + 32);
    bbStrings_toUpper[__X(i + 32, 256, (CHAR*)"bbStrings", 183896)] = (LONGCHAR)i;
    i += 1;
  }
  i = 216;
  while (i <= 222) {
    bbStrings_toLower[__X(i, 256, (CHAR*)"bbStrings", 184125)] = (LONGCHAR)(i + 32);
    bbStrings_toUpper[__X(i + 32, 256, (CHAR*)"bbStrings", 184152)] = (LONGCHAR)i;
    i += 1;
  }
  bbStrings_toUpper[255] = 0x0178;
  __MOVE(((LONGCHAR[]){48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 65, 66, 67, 68, 69, 70, 0}), bbStrings_digits, 34);
  bbStrings_maxExp = (INTEGER)__ENTIER(bbMath_Log((8.9884656743115738e+307 * 2))) + 1;
  bbStrings_maxDig = (INTEGER)__ENTIER(-bbMath_Log(bbMath_Eps()));
  bbStrings_factor = bbMath_IntPower((REAL)10, bbStrings_maxDig);
}


export void *bbStrings__init (void)
{
  __DEFMOD;
  __IMPORT(bbKernel__init);
  __IMPORT(bbMath__init);
  __REGMOD("bbStrings", 0);
/* BEGIN */
  bbStrings_Init();
  __ENDMOD;
}
