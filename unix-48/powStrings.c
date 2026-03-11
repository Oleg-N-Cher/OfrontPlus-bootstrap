/* Ofront+ 1.0 -sC -48 */
#include "SYSTEM.oh"

typedef
  struct CHAR8_ARRAY *powStrings_String;


#ifndef CHAR8_ARRAY_DEF
#define CHAR8_ARRAY_DEF
typedef struct CHAR8_ARRAY {
  INTEGER len[1];
  CHAR data[1];
} CHAR8_ARRAY;
#endif 



export void powStrings_Append (CHAR *dest, INTEGER dest__len, CHAR *src, INTEGER src__len);
export void powStrings_AppendChar (CHAR *dest, INTEGER dest__len, CHAR ch);
export void powStrings_Copy (CHAR *source, INTEGER source__len, CHAR *dest, INTEGER dest__len, INTEGER pos, INTEGER n);
export void powStrings_Delete (CHAR *t, INTEGER t__len, INTEGER pos, INTEGER n);
export void powStrings_HexStr (INTEGER x, CHAR *t, INTEGER t__len);
export void powStrings_Insert (CHAR *source, INTEGER source__len, CHAR *dest, INTEGER dest__len, INTEGER pos);
export void powStrings_InsertChar (CHAR x, CHAR *t, INTEGER t__len, INTEGER pos);
export void powStrings_LeftAlign (CHAR *t, INTEGER t__len, INTEGER n);
export INTEGER powStrings_Length (CHAR *t, INTEGER t__len);
export INTEGER powStrings_Pos (CHAR *pattern, INTEGER pattern__len, CHAR *t, INTEGER t__len, INTEGER start);
export INTEGER powStrings_PosChar (CHAR x, CHAR *t, INTEGER t__len, INTEGER start);
export void powStrings_RemoveLeadingSpaces (CHAR *t, INTEGER t__len);
export void powStrings_RemoveTrailingSpaces (CHAR *t, INTEGER t__len);
export void powStrings_ReverseStringT (CHAR *t, INTEGER t__len, INTEGER n);
export void powStrings_RightAlign (CHAR *t, INTEGER t__len, INTEGER n);
export void powStrings_Str (INTEGER x, CHAR *t, INTEGER t__len);
export void powStrings_UpCase (CHAR *t, INTEGER t__len);
export CHAR powStrings_UpCaseChar (CHAR x);
export INTEGER powStrings_Val (CHAR *t, INTEGER t__len);
export SHORTINT powStrings_ValResult (CHAR *t, INTEGER t__len);


/*============================================================================*/

INTEGER powStrings_Length (CHAR *t, INTEGER t__len)
{
  INTEGER i, maxlen;
  maxlen = t__len;
  i = 0;
  while (i < maxlen && t[__X(i, t__len, (CHAR*)"powStrings", 13086)] != 0x00) {
    i += 1;
  }
  return i;
}

/*----------------------------------------------------------------------------*/
INTEGER powStrings_PosChar (CHAR x, CHAR *t, INTEGER t__len, INTEGER start)
{
  INTEGER maxl;
  if (start < 1) {
    start = 0;
  } else {
    start -= 1;
  }
  maxl = powStrings_Length(t, t__len);
  while (start < maxl && t[__X(start, t__len, (CHAR*)"powStrings", 17955)] != x) {
    start += 1;
  }
  if (start < maxl && t[__X(start, t__len, (CHAR*)"powStrings", 18247)] == x) {
    return start + 1;
  } else {
    return 0;
  }
  __RETCHK((CHAR*)"powStrings", 18242);
}

/*----------------------------------------------------------------------------*/
INTEGER powStrings_Pos (CHAR *pattern, INTEGER pattern__len, CHAR *t, INTEGER t__len, INTEGER start)
{
  INTEGER i, j, maxl, patLen;
  if (start < 1) {
    start = 0;
  } else {
    start -= 1;
  }
  maxl = powStrings_Length(t, t__len);
  patLen = powStrings_Length(pattern, pattern__len);
  i = start;
  j = 0;
  while (j < patLen && i + j < maxl) {
    if (t[__X(i + j, t__len, (CHAR*)"powStrings", 23610)] == pattern[__X(j, pattern__len, (CHAR*)"powStrings", 23610)]) {
      j += 1;
    } else {
      j = 0;
      i += 1;
    }
  }
  if (j == patLen) {
    return i + 1;
  } else {
    return 0;
  }
  __RETCHK((CHAR*)"powStrings", 24107);
}

/*----------------------------------------------------------------------------*/
void powStrings_Copy (CHAR *source, INTEGER source__len, CHAR *dest, INTEGER dest__len, INTEGER pos, INTEGER n)
{
  INTEGER i, j, l1, l2;
  if (pos < 1) {
    dest[0] = 0x00;
    return;
  }
  l1 = (powStrings_Length(source, source__len) - pos) + 1;
  if (l1 < 1) {
    dest[0] = 0x00;
    return;
  }
  l2 = dest__len - 1;
  if (l2 < l1) {
    l1 = l2;
  }
  if (n < l1) {
    l1 = n;
  }
  i = 0;
  j = pos - 1;
  while (i < l1) {
    dest[__X(i, dest__len, (CHAR*)"powStrings", 32278)] = source[__X(j, source__len, (CHAR*)"powStrings", 32278)];
    i += 1;
    j += 1;
  }
  dest[__X(i, dest__len, (CHAR*)"powStrings", 33293)] = 0x00;
}

/*----------------------------------------------------------------------------*/
void powStrings_Append (CHAR *dest, INTEGER dest__len, CHAR *src, INTEGER src__len)
{
  INTEGER i, j, lSrc, lDest;
  i = powStrings_Length(dest, dest__len);
  j = 0;
  lDest = dest__len - 1;
  lSrc = src__len;
  while ((i < lDest && j < lSrc) && src[__X(j, src__len, (CHAR*)"powStrings", 36394)] != 0x00) {
    dest[__X(i, dest__len, (CHAR*)"powStrings", 36627)] = src[__X(j, src__len, (CHAR*)"powStrings", 36627)];
    i += 1;
    j += 1;
  }
  dest[__X(i, dest__len, (CHAR*)"powStrings", 37645)] = 0x00;
}

/*----------------------------------------------------------------------------*/
void powStrings_AppendChar (CHAR *dest, INTEGER dest__len, CHAR ch)
{
  INTEGER l;
  l = powStrings_Length(dest, dest__len);
  if (dest__len >= l + 2) {
    dest[__X(l, dest__len, (CHAR*)"powStrings", 40207)] = ch;
    dest[__X(l + 1, dest__len, (CHAR*)"powStrings", 40465)] = 0x00;
  }
}

/*----------------------------------------------------------------------------*/
CHAR powStrings_UpCaseChar (CHAR x)
{
  switch (x) {
    case 'a': case 'b': case 'c': case 'd': case 'e': 
    case 'f': case 'g': case 'h': case 'i': case 'j': 
    case 'k': case 'l': case 'm': case 'n': case 'o': 
    case 'p': case 'q': case 'r': case 's': case 't': 
    case 'u': case 'v': case 'w': case 'x': case 'y': 
    case 'z': 
      x = (CHAR)(((INTEGER)x + 65) - 97);
      break;
    case 0xf6: 
      x = 0xd6;
      break;
    case 0xe4: 
      x = 0xc4;
      break;
    case 0xfc: 
      x = 0xdc;
      break;
    case 0xe1: 
      x = 0xc1;
      break;
    case 0xe9: 
      x = 0xc9;
      break;
    case 0xed: 
      x = 0xcd;
      break;
    case 0xf3: 
      x = 0xd3;
      break;
    case 0xfa: 
      x = 0xda;
      break;
    case 0xe0: 
      x = 0xc0;
      break;
    case 0xe8: 
      x = 0xc8;
      break;
    case 0xec: 
      x = 0xcc;
      break;
    case 0xf2: 
      x = 0xd2;
      break;
    case 0xf9: 
      x = 0xd9;
      break;
    case 0xe2: 
      x = 0xc2;
      break;
    case 0xea: 
      x = 0xca;
      break;
    case 0xee: 
      x = 0xce;
      break;
    case 0xf4: 
      x = 0xd4;
      break;
    case 0xfb: 
      x = 0xdb;
      break;
    default: 
      break;
  }
  return x;
}

/*----------------------------------------------------------------------------*/
void powStrings_UpCase (CHAR *t, INTEGER t__len)
{
  INTEGER i, l;
  i = 0;
  l = t__len;
  while (i < l && t[__X(i, t__len, (CHAR*)"powStrings", 51993)] != 0x00) {
    t[__X(i, t__len, (CHAR*)"powStrings", 52250)] = powStrings_UpCaseChar(t[__X(i, t__len, (CHAR*)"powStrings", 52250)]);
    i += 1;
  }
}

/*----------------------------------------------------------------------------*/
void powStrings_Delete (CHAR *t, INTEGER t__len, INTEGER pos, INTEGER n)
{
  INTEGER i, l, _for__5;
  l = powStrings_Length(t, t__len);
  if ((n < 1 || pos < 1) || pos > l) {
    return;
  }
  if (n > (l - pos) + 1) {
    n = (l - pos) + 1;
  }
  _for__5 = l - n;
  i = pos - 1;
  while (i <= _for__5) {
    t[__X(i, t__len, (CHAR*)"powStrings", 55589)] = t[__X(i + n, t__len, (CHAR*)"powStrings", 55589)];
    i += 1;
  }
}

/*----------------------------------------------------------------------------*/
void powStrings_ReverseStringT (CHAR *t, INTEGER t__len, INTEGER n)
{
  INTEGER a, b;
  CHAR x;
  a = 0;
  b = n - 1;
  while (a < b) {
    x = t[__X(a, t__len, (CHAR*)"powStrings", 58379)];
    t[__X(a, t__len, (CHAR*)"powStrings", 58638)] = t[__X(b, t__len, (CHAR*)"powStrings", 58638)];
    t[__X(b, t__len, (CHAR*)"powStrings", 58891)] = x;
    a += 1;
    b -= 1;
  }
}

/*----------------------------------------------------------------------------*/
void powStrings_RemoveTrailingSpaces (CHAR *t, INTEGER t__len)
{
  INTEGER i;
  i = powStrings_Length(t, t__len) - 1;
  while (i >= 0 && t[__X(i, t__len, (CHAR*)"powStrings", 61979)] == ' ') {
    i -= 1;
  }
  t[__X(i + 1, t__len, (CHAR*)"powStrings", 62220)] = 0x00;
}

/*----------------------------------------------------------------------------*/
void powStrings_RemoveLeadingSpaces (CHAR *t, INTEGER t__len)
{
  INTEGER i, ml;
  i = 0;
  ml = t__len - 1;
  while (i < ml && t[__X(i, t__len, (CHAR*)"powStrings", 64795)] == ' ') {
    i += 1;
  }
  if (i > 0) {
    powStrings_Delete(t, t__len, 1, i);
  }
}

/*----------------------------------------------------------------------------*/
INTEGER powStrings_Val (CHAR *t, INTEGER t__len)
{
  INTEGER inx, l, v, res;
  BOOLEAN hex, exit, neg;
  CHAR ch;
  __DUP(t, t__len);
  powStrings_RemoveTrailingSpaces(t, t__len);
  powStrings_RemoveLeadingSpaces(t, t__len);
  l = powStrings_Length(t, t__len);
  if (l < 1) {
    return (-2147483647-1);
  }
  hex = __CAP(t[__X(l - 1, t__len, (CHAR*)"powStrings", 70678)]) == 'H';
  if (hex) {
    l -= 1;
    t[__X(l, t__len, (CHAR*)"powStrings", 71436)] = 0x00;
    if (l < 1) {
      return (-2147483647-1);
    }
  }
  inx = 0;
  neg = 0;
  res = 0;
  if (t[0] == '+') {
    inx += 1;
  } else if (t[0] == '-') {
    inx += 1;
    neg = 1;
  }
  if (t[__X(l - 1, t__len, (CHAR*)"powStrings", 73774)] == '+') {
    l -= 1;
  } else if (t[__X(l - 1, t__len, (CHAR*)"powStrings", 73499)] == '-') {
    l -= 1;
    neg = 1;
  }
  exit = 0;
  if (hex) {
    if (neg) {
      while (inx < l && !exit) {
        ch = __CAP(t[__X(inx, t__len, (CHAR*)"powStrings", 75031)]);
        if (ch >= '0' && ch <= '9') {
          v = (INTEGER)ch - 48;
        } else if (ch >= 'A' && ch <= 'F') {
          v = ((INTEGER)ch - 65) + 10;
        } else {
          v = -1;
        }
        if ((v < 0 || v > 15) || res < -134217727) {
          exit = 1;
        } else {
          res = __ASHL(res, 4, INTEGER) - v;
          inx += 1;
        }
      }
    } else {
      while (inx < l && !exit) {
        ch = __CAP(t[__X(inx, t__len, (CHAR*)"powStrings", 79383)]);
        if (ch >= '0' && ch <= '9') {
          v = (INTEGER)ch - 48;
        } else if (ch >= 'A' && ch <= 'F') {
          v = ((INTEGER)ch - 65) + 10;
        } else {
          v = -1;
        }
        if ((v < 0 || v > 15) || res > 134217727) {
          exit = 1;
        } else {
          res = __ASHL(res, 4, INTEGER) + v;
          inx += 1;
        }
      }
    }
  } else {
    if (neg) {
      while (inx < l && !exit) {
        v = (INTEGER)t[__X(inx, t__len, (CHAR*)"powStrings", 84249)] - 48;
        if (((v < 0 || v > 9) || res < -214748364) || (res == -214748364 && v > 8)) {
          exit = 1;
        } else {
          res = res * 10 - v;
          inx += 1;
        }
      }
    } else {
      while (inx < l && !exit) {
        v = (INTEGER)t[__X(inx, t__len, (CHAR*)"powStrings", 86809)] - 48;
        if (((v < 0 || v > 9) || res > 214748364) || (res == 214748364 && v > 7)) {
          exit = 1;
        } else {
          res = res * 10 + v;
          inx += 1;
        }
      }
    }
  }
  if (exit) {
    return (-2147483647-1);
  } else {
    return res;
  }
  __RETCHK((CHAR*)"powStrings", 90126);
}

/*----------------------------------------------------------------------------*/
SHORTINT powStrings_ValResult (CHAR *t, INTEGER t__len)
{
  INTEGER inx, l, v, res;
  SHORTINT h;
  BOOLEAN hex, exit, neg;
  CHAR ch;
  __DUP(t, t__len);
  powStrings_RemoveTrailingSpaces(t, t__len);
  powStrings_RemoveLeadingSpaces(t, t__len);
  l = powStrings_Length(t, t__len);
  if (l < 1) {
    return 5;
  }
  hex = __CAP(t[__X(l - 1, t__len, (CHAR*)"powStrings", 99606)]) == 'H';
  if (hex) {
    l -= 1;
    t[__X(l, t__len, (CHAR*)"powStrings", 100364)] = 0x00;
    if (l < 1) {
      return 5;
    }
  }
  inx = 0;
  neg = 0;
  res = 0;
  if (t[0] == '+') {
    inx += 1;
  } else if (t[0] == '-') {
    inx += 1;
    neg = 1;
  }
  if (t[__X(l - 1, t__len, (CHAR*)"powStrings", 102702)] == '+') {
    l -= 1;
  } else if (t[__X(l - 1, t__len, (CHAR*)"powStrings", 102427)] == '-') {
    l -= 1;
    neg = 1;
  }
  exit = 0;
  if (hex) {
    if (neg) {
      while (inx < l && !exit) {
        ch = __CAP(t[__X(inx, t__len, (CHAR*)"powStrings", 103959)]);
        if (ch >= '0' && ch <= '9') {
          v = (INTEGER)ch - 48;
        } else if (ch >= 'A' && ch <= 'F') {
          v = ((INTEGER)ch - 65) + 10;
        } else {
          v = -1;
        }
        if (((v < 0 || v > 15) || res < -134217728) || (res == -134217728 && v > 0)) {
          exit = 1;
        } else {
          res = __ASHL(res, 4, INTEGER) - v;
          inx += 1;
        }
      }
    } else {
      while (inx < l && !exit) {
        ch = __CAP(t[__X(inx, t__len, (CHAR*)"powStrings", 108311)]);
        if (ch >= '0' && ch <= '9') {
          v = (INTEGER)ch - 48;
        } else if (ch >= 'A' && ch <= 'F') {
          v = ((INTEGER)ch - 65) + 10;
        } else {
          v = -1;
        }
        if ((v < 0 || v > 15) || res > 134217727) {
          exit = 1;
        } else {
          res = __ASHL(res, 4, INTEGER) + v;
          inx += 1;
        }
      }
    }
  } else {
    if (neg) {
      while (inx < l && !exit) {
        v = (INTEGER)t[__X(inx, t__len, (CHAR*)"powStrings", 113177)] - 48;
        if (((v < 0 || v > 9) || res < -214748364) || (res == -214748364 && v > 8)) {
          exit = 1;
        } else {
          res = res * 10 - v;
          inx += 1;
        }
      }
    } else {
      while (inx < l && !exit) {
        v = (INTEGER)t[__X(inx, t__len, (CHAR*)"powStrings", 115737)] - 48;
        if (((v < 0 || v > 9) || res > 214748364) || (res == 214748364 && v > 7)) {
          exit = 1;
        } else {
          res = res * 10 + v;
          inx += 1;
        }
      }
    }
  }
  if (exit) {
    if ((v < 0 || (hex && v > 15)) || (!hex && v > 9)) {
      return 6;
    } else {
      return 4;
    }
  } else {
    h = 3;
    if (res >= -32768 && res <= 32767) {
      h -= 1;
    }
    if (res >= -128 && res <= 127) {
      h -= 1;
    }
    return h;
  }
  __RETCHK((CHAR*)"powStrings", 119820);
}

/*----------------------------------------------------------------------------*/
void powStrings_Str (INTEGER x, CHAR *t, INTEGER t__len)
{
  INTEGER i, maxlen;
  BOOLEAN neg;
  INTEGER _for__26, _for__25;
  maxlen = t__len - 1;
  if (maxlen < 1) {
    t[0] = 0x00;
    return;
  }
  if (x == 0) {
    t[0] = '0';
    t[__X(1, t__len, (CHAR*)"powStrings", 124940)] = 0x00;
  } else {
    i = 0;
    neg = x < 0;
    if (neg) {
      if (x == (-2147483647-1)) {
        __STRCOPYCC((CHAR*)"-2147483648", t, t__len, (CHAR*)"powStrings", 126490);
        if (powStrings_Length(t, t__len) != 11) {
          _for__26 = maxlen - 1;
          i = 0;
          while (i <= _for__26) {
            t[__X(i, t__len, (CHAR*)"powStrings", 127019)] = '$';
            i += 1;
          }
          t[__X(maxlen, t__len, (CHAR*)"powStrings", 127255)] = 0x00;
        }
        return;
      } else {
        x = -x;
      }
    }
    while (x != 0 && i < maxlen) {
      t[__X(i, t__len, (CHAR*)"powStrings", 129315)] = (CHAR)(48 + __MOD(x, 10));
      x = __DIV(x, 10);
      i += 1;
    }
    if (x != 0 || (neg && i >= maxlen)) {
      _for__25 = maxlen - 1;
      i = 0;
      while (i <= _for__25) {
        t[__X(i, t__len, (CHAR*)"powStrings", 130599)] = '$';
        i += 1;
      }
      t[__X(maxlen, t__len, (CHAR*)"powStrings", 130835)] = 0x00;
    } else {
      if (neg) {
        t[__X(i, t__len, (CHAR*)"powStrings", 131601)] = '-';
        i += 1;
      }
      t[__X(i, t__len, (CHAR*)"powStrings", 132366)] = 0x00;
      powStrings_ReverseStringT(t, t__len, i);
    }
  }
}

/*----------------------------------------------------------------------------*/
void powStrings_HexStr (INTEGER x, CHAR *t, INTEGER t__len)
{
  INTEGER i, digit, maxlen;
  BOOLEAN neg;
  INTEGER _for__8, _for__7;
  maxlen = t__len - 1;
  if (maxlen < 2) {
    if (maxlen == 1) {
      t[0] = '$';
      t[__X(1, t__len, (CHAR*)"powStrings", 137768)] = 0x00;
    } else {
      t[0] = 0x00;
    }
    return;
  }
  if (x == 0) {
    t[0] = '0';
    t[__X(1, t__len, (CHAR*)"powStrings", 139021)] = 'h';
    t[__X(2, t__len, (CHAR*)"powStrings", 139276)] = 0x00;
  } else {
    t[0] = 'h';
    i = 1;
    neg = x < 0;
    if (neg) {
      if (x == (-2147483647-1)) {
        __STRCOPYCC((CHAR*)"-80000000h", t, t__len, (CHAR*)"powStrings", 141081);
        if (powStrings_Length(t, t__len) != 10) {
          _for__8 = maxlen - 1;
          i = 0;
          while (i <= _for__8) {
            t[__X(i, t__len, (CHAR*)"powStrings", 141611)] = '$';
            i += 1;
          }
          t[__X(maxlen, t__len, (CHAR*)"powStrings", 141847)] = 0x00;
        }
        return;
      } else {
        x = -x;
      }
    }
    while (x != 0 && i < maxlen) {
      digit = __MASK(x, -16);
      if (digit < 10) {
        t[__X(i, t__len, (CHAR*)"powStrings", 144177)] = (CHAR)(48 + digit);
      } else {
        t[__X(i, t__len, (CHAR*)"powStrings", 144209)] = (CHAR)(55 + digit);
      }
      x = __ASHR(x, 4, INTEGER);
      i += 1;
    }
    if (x != 0 || (neg && i >= maxlen)) {
      _for__7 = maxlen - 1;
      i = 0;
      while (i <= _for__7) {
        t[__X(i, t__len, (CHAR*)"powStrings", 145447)] = '$';
        i += 1;
      }
      t[__X(maxlen, t__len, (CHAR*)"powStrings", 145683)] = 0x00;
    } else {
      if (neg) {
        t[__X(i, t__len, (CHAR*)"powStrings", 146449)] = '-';
        i += 1;
      }
      t[__X(i, t__len, (CHAR*)"powStrings", 147214)] = 0x00;
      powStrings_ReverseStringT(t, t__len, i);
    }
  }
}

/*----------------------------------------------------------------------------*/
void powStrings_InsertChar (CHAR x, CHAR *t, INTEGER t__len, INTEGER pos)
{
  INTEGER i, l, _for__13;
  l = powStrings_Length(t, t__len);
  if (l + 1 < t__len) {
    if (pos < 1) {
      pos = 1;
    } else if (pos > l + 1) {
      pos = l + 1;
    }
    _for__13 = pos - 1;
    i = l;
    while (i >= _for__13) {
      t[__X(i + 1, t__len, (CHAR*)"powStrings", 151083)] = t[__X(i, t__len, (CHAR*)"powStrings", 151083)];
      i += -1;
    }
    t[__X(pos - 1, t__len, (CHAR*)"powStrings", 151311)] = x;
  }
}

/*----------------------------------------------------------------------------*/
void powStrings_Insert (CHAR *source, INTEGER source__len, CHAR *dest, INTEGER dest__len, INTEGER pos)
{
  INTEGER i, l, dif, _for__11, _for__10;
  dif = powStrings_Length(source, source__len);
  l = powStrings_Length(dest, dest__len);
  if ((l + dif) + 1 > dest__len) {
    dif = (dest__len - l) - 1;
  }
  if (pos < 1) {
    pos = 1;
  } else if (pos > l + 1) {
    pos = l + 1;
  }
  _for__11 = pos - 1;
  i = l;
  while (i >= _for__11) {
    dest[__X(i + dif, dest__len, (CHAR*)"powStrings", 155185)] = dest[__X(i, dest__len, (CHAR*)"powStrings", 155185)];
    i += -1;
  }
  _for__10 = (pos - 2) + dif;
  i = pos - 1;
  while (i <= _for__10) {
    dest[__X(i, dest__len, (CHAR*)"powStrings", 155447)] = source[__X((i + 1) - pos, source__len, (CHAR*)"powStrings", 155447)];
    i += 1;
  }
}

/*----------------------------------------------------------------------------*/
void powStrings_LeftAlign (CHAR *t, INTEGER t__len, INTEGER n)
{
  INTEGER l, i, maxlen, _for__15;
  maxlen = t__len;
  if (n + 1 > maxlen) {
    n = maxlen - 1;
  }
  l = powStrings_Length(t, t__len);
  if (l <= n - 1) {
    _for__15 = n - 1;
    i = l;
    while (i <= _for__15) {
      t[__X(i, t__len, (CHAR*)"powStrings", 159008)] = ' ';
      i += 1;
    }
    t[__X(n, t__len, (CHAR*)"powStrings", 159244)] = 0x00;
  }
}

/*----------------------------------------------------------------------------*/
void powStrings_RightAlign (CHAR *t, INTEGER t__len, INTEGER n)
{
  INTEGER l, i, maxlen, _for__23;
  maxlen = t__len;
  if (n + 1 > maxlen) {
    n = maxlen - 1;
  }
  l = powStrings_Length(t, t__len);
  if (l < n) {
    t[__X(n, t__len, (CHAR*)"powStrings", 163084)] = 0x00;
    n = n - l;
    i = l - 1;
    while (i >= 0) {
      t[__X(i + n, t__len, (CHAR*)"powStrings", 163625)] = t[__X(i, t__len, (CHAR*)"powStrings", 163625)];
      i += -1;
    }
    _for__23 = n - 1;
    i = 0;
    while (i <= _for__23) {
      t[__X(i, t__len, (CHAR*)"powStrings", 163872)] = ' ';
      i += 1;
    }
  }
}

/*----------------------------------------------------------------------------*/

export void *powStrings__init (void)
{
  __DEFMOD;
  __REGMOD("powStrings", 0);
/* BEGIN */
  __ENDMOD;
}
