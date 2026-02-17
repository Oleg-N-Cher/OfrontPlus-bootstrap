/* Ofront+ 1.0 -sC -48 */
#include "SYSTEM.oh"
#include "Reals.oh"




export void Strings_Append (CHAR *extra, INTEGER extra__len, CHAR *dest, INTEGER dest__len);
export void Strings_Cap (CHAR *s, INTEGER s__len);
export void Strings_Delete (CHAR *s, INTEGER s__len, INTEGER pos, INTEGER n);
export void Strings_Extract (CHAR *source, INTEGER source__len, INTEGER pos, INTEGER n, CHAR *dest, INTEGER dest__len);
export void Strings_Insert (CHAR *source, INTEGER source__len, INTEGER pos, CHAR *dest, INTEGER dest__len);
export INTEGER Strings_Length (CHAR *s, INTEGER s__len);
export BOOLEAN Strings_Match (CHAR *string, INTEGER string__len, CHAR *pattern, INTEGER pattern__len);
export INTEGER Strings_Pos (CHAR *pattern, INTEGER pattern__len, CHAR *s, INTEGER s__len, INTEGER pos);
export void Strings_Replace (CHAR *source, INTEGER source__len, INTEGER pos, CHAR *dest, INTEGER dest__len);
export void Strings_StrToLongReal (CHAR *s, INTEGER s__len, REAL *r);
export void Strings_StrToReal (CHAR *s, INTEGER s__len, SHORTREAL *r);


/*============================================================================*/

INTEGER Strings_Length (CHAR *s, INTEGER s__len)
{
  INTEGER i;
  i = 0;
  while (i < s__len && s[__X(i, s__len, (CHAR*)"Strings", 11561)] != 0x00) {
    i += 1;
  }
  return i;
}

/*----------------------------------------------------------------------------*/
void Strings_Append (CHAR *extra, INTEGER extra__len, CHAR *dest, INTEGER dest__len)
{
  INTEGER n1, n2, i;
  n1 = Strings_Length((void*)dest, dest__len);
  n2 = Strings_Length((void*)extra, extra__len);
  i = 0;
  while (i < n2 && i + n1 < dest__len) {
    dest[__X(i + n1, dest__len, (CHAR*)"Strings", 13890)] = extra[__X(i, extra__len, (CHAR*)"Strings", 13890)];
    i += 1;
  }
  if (i + n1 < dest__len) {
    dest[__X(i + n1, dest__len, (CHAR*)"Strings", 14126)] = 0x00;
  } else {
    dest[__X(dest__len - 1, dest__len, (CHAR*)"Strings", 14155)] = 0x00;
  }
}

/*----------------------------------------------------------------------------*/
void Strings_Insert (CHAR *source, INTEGER source__len, INTEGER pos, CHAR *dest, INTEGER dest__len)
{
  INTEGER n1, n2, len, i, j;
  n1 = Strings_Length((void*)dest, dest__len);
  n2 = Strings_Length((void*)source, source__len);
  len = dest__len;
  if (pos < 0) {
    pos = 0;
  }
  if (pos > n1) {
    Strings_Append((void*)source, source__len, (void*)dest, dest__len);
    return;
  }
  if (pos + n2 < len) {
    i = n1;
    j = i + n2;
    while (i >= pos) {
      if (j < len) {
        dest[__X(j, dest__len, (CHAR*)"Strings", 17701)] = dest[__X(i, dest__len, (CHAR*)"Strings", 17701)];
      }
      i -= 1;
      j -= 1;
    }
  }
  i = 0;
  j = pos;
  while (i < n2 && j < len) {
    dest[__X(j, dest__len, (CHAR*)"Strings", 19478)] = source[__X(i, source__len, (CHAR*)"Strings", 19478)];
    i += 1;
    j += 1;
  }
  if (j >= len) {
    dest[__X(len - 1, dest__len, (CHAR*)"Strings", 20259)] = 0x00;
  }
}

/*----------------------------------------------------------------------------*/
void Strings_Delete (CHAR *s, INTEGER s__len, INTEGER pos, INTEGER n)
{
  INTEGER len, i;
  len = Strings_Length((void*)s, s__len);
  if (pos < 0) {
    pos = 0;
  } else if (pos >= len) {
    return;
  }
  if (pos + n < len) {
    i = pos + n;
    while (i < len) {
      s[__X(i - n, s__len, (CHAR*)"Strings", 22829)] = s[__X(i, s__len, (CHAR*)"Strings", 22829)];
      i += 1;
    }
    if (i - n < s__len) {
      s[__X(i - n, s__len, (CHAR*)"Strings", 23077)] = 0x00;
    }
  } else {
    s[__X(pos, s__len, (CHAR*)"Strings", 23551)] = 0x00;
  }
}

/*----------------------------------------------------------------------------*/
void Strings_Replace (CHAR *source, INTEGER source__len, INTEGER pos, CHAR *dest, INTEGER dest__len)
{
  Strings_Delete((void*)dest, dest__len, pos, pos + Strings_Length((void*)source, source__len));
  Strings_Insert((void*)source, source__len, pos, (void*)dest, dest__len);
}

/*----------------------------------------------------------------------------*/
void Strings_Extract (CHAR *source, INTEGER source__len, INTEGER pos, INTEGER n, CHAR *dest, INTEGER dest__len)
{
  INTEGER len, destLen, i;
  len = Strings_Length((void*)source, source__len);
  destLen = dest__len - 1;
  if (pos < 0) {
    pos = 0;
  }
  if (pos >= len) {
    dest[0] = 0x00;
    return;
  }
  i = 0;
  while ((pos + i <= source__len && source[__X(pos + i, source__len, (CHAR*)"Strings", 28226)] != 0x00) && i < n) {
    if (i < destLen) {
      dest[__X(i, dest__len, (CHAR*)"Strings", 28464)] = source[__X(pos + i, source__len, (CHAR*)"Strings", 28464)];
    }
    i += 1;
  }
  dest[__X(i, dest__len, (CHAR*)"Strings", 29439)] = 0x00;
}

/*----------------------------------------------------------------------------*/
INTEGER Strings_Pos (CHAR *pattern, INTEGER pattern__len, CHAR *s, INTEGER s__len, INTEGER pos)
{
  INTEGER n1, n2, i, j;
  n1 = Strings_Length((void*)s, s__len);
  n2 = Strings_Length((void*)pattern, pattern__len);
  if (n2 == 0) {
    return 0;
  }
  i = pos;
  while (i <= n1 - n2) {
    if (s[__X(i, s__len, (CHAR*)"Strings", 32773)] == pattern[0]) {
      j = 1;
      while (j < n2 && s[__X(i + j, s__len, (CHAR*)"Strings", 32307)] == pattern[__X(j, pattern__len, (CHAR*)"Strings", 32307)]) {
        j += 1;
      }
      if (j == n2) {
        return i;
      }
    }
    i += 1;
  }
  return -1;
}

/*----------------------------------------------------------------------------*/
void Strings_Cap (CHAR *s, INTEGER s__len)
{
  INTEGER i;
  i = 0;
  while (s[__X(i, s__len, (CHAR*)"Strings", 35600)] != 0x00) {
    if ('a' <= s[__X(i, s__len, (CHAR*)"Strings", 35901)] && s[__X(i, s__len, (CHAR*)"Strings", 35901)] <= 'z') {
      s[__X(i, s__len, (CHAR*)"Strings", 35897)] = __CAP(s[__X(i, s__len, (CHAR*)"Strings", 35897)]);
    }
    i += 1;
  }
}

/*----------------------------------------------------------------------------*/
static struct Match__7 {
  struct Match__7 *lnk;
} *Match__7_s;

static BOOLEAN __8 (CHAR *name, INTEGER name__len, CHAR *mask, INTEGER mask__len, INTEGER n, INTEGER m);

static BOOLEAN __8 (CHAR *name, INTEGER name__len, CHAR *mask, INTEGER mask__len, INTEGER n, INTEGER m)
{
  while ((n >= 0 && m >= 0) && mask[__X(m, mask__len, (CHAR*)"Strings", 38445)] != '*') {
    if (name[__X(n, name__len, (CHAR*)"Strings", 38701)] != mask[__X(m, mask__len, (CHAR*)"Strings", 38701)]) {
      return 0;
    }
    n -= 1;
    m -= 1;
  }
  if (m < 0) {
    return n < 0;
  }
  while (m >= 0 && mask[__X(m, mask__len, (CHAR*)"Strings", 40226)] == '*') {
    m -= 1;
  }
  if (m < 0) {
    return 1;
  }
  while (n >= 0) {
    if (__8(name, name__len, mask, mask__len, n, m)) {
      return 1;
    }
    n -= 1;
  }
  return 0;
}

BOOLEAN Strings_Match (CHAR *string, INTEGER string__len, CHAR *pattern, INTEGER pattern__len)
{
  struct Match__7 _s;
  BOOLEAN __retval;
  _s.lnk = Match__7_s;
  Match__7_s = &_s;
  __retval = __8((void*)string, string__len, (void*)pattern, pattern__len, Strings_Length((void*)string, string__len) - 1, Strings_Length((void*)pattern, pattern__len) - 1);
  Match__7_s = _s.lnk;
  ;
  return __retval;
}

/*----------------------------------------------------------------------------*/
void Strings_StrToReal (CHAR *s, INTEGER s__len, SHORTREAL *r)
{
  SHORTINT p, e;
  SHORTREAL y, g;
  BOOLEAN neg, negE;
  p = 0;
  while (s[__X(p, s__len, (CHAR*)"Strings", 44835)] == ' ' || s[__X(p, s__len, (CHAR*)"Strings", 44835)] == '0') {
    p += 1;
  }
  if (s[__X(p, s__len, (CHAR*)"Strings", 45117)] == '-') {
    neg = 1;
    p += 1;
  } else {
    neg = 0;
  }
  while (s[__X(p, s__len, (CHAR*)"Strings", 45347)] == ' ' || s[__X(p, s__len, (CHAR*)"Strings", 45347)] == '0') {
    p += 1;
  }
  y = (SHORTREAL)0;
  while ('0' <= s[__X(p, s__len, (CHAR*)"Strings", 46116)] && s[__X(p, s__len, (CHAR*)"Strings", 46116)] <= '9') {
    y = y * (SHORTREAL)10 + (SHORTREAL)((INTEGER)s[__X(p, s__len, (CHAR*)"Strings", 46369)] - 48);
    p += 1;
  }
  if (s[__X(p, s__len, (CHAR*)"Strings", 48644)] == '.') {
    p += 1;
    g = (SHORTREAL)1;
    while ('0' <= s[__X(p, s__len, (CHAR*)"Strings", 47653)] && s[__X(p, s__len, (CHAR*)"Strings", 47653)] <= '9') {
      g = g / (SHORTREAL)(SHORTREAL)10;
      y = y + g * (SHORTREAL)((INTEGER)s[__X(p, s__len, (CHAR*)"Strings", 47918)] - 48);
      p += 1;
    }
  }
  if (s[__X(p, s__len, (CHAR*)"Strings", 51460)] == 'D' || s[__X(p, s__len, (CHAR*)"Strings", 51460)] == 'E') {
    p += 1;
    e = 0;
    if (s[__X(p, s__len, (CHAR*)"Strings", 49472)] == '-') {
      negE = 1;
      p += 1;
    } else {
      negE = 0;
    }
    while (s[__X(p, s__len, (CHAR*)"Strings", 49684)] == '0') {
      p += 1;
    }
    while ('0' <= s[__X(p, s__len, (CHAR*)"Strings", 49957)] && s[__X(p, s__len, (CHAR*)"Strings", 49957)] <= '9') {
      e = (SHORTINT)((INTEGER)e * 10 + ((INTEGER)s[__X(p, s__len, (CHAR*)"Strings", 50217)] - 48));
      p += 1;
    }
    if (negE) {
      y = y / (SHORTREAL)Reals_Ten(e);
    } else {
      y = y * Reals_Ten(e);
    }
  }
  if (neg) {
    y = -y;
  }
  *r = y;
}

/*----------------------------------------------------------------------------*/
void Strings_StrToLongReal (CHAR *s, INTEGER s__len, REAL *r)
{
  INTEGER p, e;
  REAL y, g;
  BOOLEAN neg, negE;
  p = 0;
  while (s[__X(p, s__len, (CHAR*)"Strings", 53795)] == ' ' || s[__X(p, s__len, (CHAR*)"Strings", 53795)] == '0') {
    p += 1;
  }
  if (s[__X(p, s__len, (CHAR*)"Strings", 54077)] == '-') {
    neg = 1;
    p += 1;
  } else {
    neg = 0;
  }
  while (s[__X(p, s__len, (CHAR*)"Strings", 54307)] == ' ' || s[__X(p, s__len, (CHAR*)"Strings", 54307)] == '0') {
    p += 1;
  }
  y = (REAL)0;
  while ('0' <= s[__X(p, s__len, (CHAR*)"Strings", 55076)] && s[__X(p, s__len, (CHAR*)"Strings", 55076)] <= '9') {
    y = y * (REAL)10 + (REAL)((INTEGER)s[__X(p, s__len, (CHAR*)"Strings", 55329)] - 48);
    p += 1;
  }
  if (s[__X(p, s__len, (CHAR*)"Strings", 57604)] == '.') {
    p += 1;
    g = (REAL)1;
    while ('0' <= s[__X(p, s__len, (CHAR*)"Strings", 56613)] && s[__X(p, s__len, (CHAR*)"Strings", 56613)] <= '9') {
      g = g / (REAL)(REAL)10;
      y = y + g * (REAL)((INTEGER)s[__X(p, s__len, (CHAR*)"Strings", 56878)] - 48);
      p += 1;
    }
  }
  if (s[__X(p, s__len, (CHAR*)"Strings", 60420)] == 'D' || s[__X(p, s__len, (CHAR*)"Strings", 60420)] == 'E') {
    p += 1;
    e = 0;
    if (s[__X(p, s__len, (CHAR*)"Strings", 58432)] == '-') {
      negE = 1;
      p += 1;
    } else {
      negE = 0;
    }
    while (s[__X(p, s__len, (CHAR*)"Strings", 58644)] == '0') {
      p += 1;
    }
    while ('0' <= s[__X(p, s__len, (CHAR*)"Strings", 58917)] && s[__X(p, s__len, (CHAR*)"Strings", 58917)] <= '9') {
      e = e * 10 + ((INTEGER)s[__X(p, s__len, (CHAR*)"Strings", 59170)] - 48);
      p += 1;
    }
    if (negE) {
      y = y / (REAL)(REAL)Reals_Ten((SHORTINT)e);
    } else {
      y = y * (REAL)Reals_Ten((SHORTINT)e);
    }
  }
  if (neg) {
    y = -y;
  }
  *r = y;
}

/*----------------------------------------------------------------------------*/

export void *Strings__init (void)
{
  __DEFMOD;
  __IMPORT(Reals__init);
  __REGMOD("Strings", 0);
/* BEGIN */
  __ENDMOD;
}
