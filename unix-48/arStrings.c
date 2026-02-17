/* Ofront+ 1.0 -s2 -48 */
#include "SYSTEM.oh"

typedef
  struct CHAR8_ARRAY *arStrings_StringPtr;


#ifndef CHAR8_ARRAY_DEF
#define CHAR8_ARRAY_DEF
typedef struct CHAR8_ARRAY {
  INTEGER len[1];
  CHAR data[1];
} CHAR8_ARRAY;
#endif 



export void arStrings_Append (CHAR *source, INTEGER source__len, CHAR *destination, INTEGER destination__len);
export void arStrings_Assign (CHAR *source, INTEGER source__len, CHAR *destination, INTEGER destination__len);
export BYTE arStrings_Compare (CHAR *stringVal1, INTEGER stringVal1__len, CHAR *stringVal2, INTEGER stringVal2__len);
export arStrings_StringPtr arStrings_Copy (CHAR *value, INTEGER value__len);
export BOOLEAN arStrings_EndsWith (CHAR *str, INTEGER str__len, CHAR *suffix, INTEGER suffix__len);
export BOOLEAN arStrings_Equal (CHAR *stringVal1, INTEGER stringVal1__len, CHAR *stringVal2, INTEGER stringVal2__len);
export void arStrings_Extract (CHAR *source, INTEGER source__len, INTEGER startPos, INTEGER numberToExtract, CHAR *destination, INTEGER destination__len);
export INTEGER arStrings_IndexOf (CHAR *str, INTEGER str__len, CHAR ch, INTEGER pos);
export INTEGER arStrings_LastIndexOf (CHAR *str, INTEGER str__len, CHAR ch, INTEGER pos);
export INTEGER arStrings_Length (CHAR *stringVal, INTEGER stringVal__len);
export BOOLEAN arStrings_StartsWith (CHAR *str, INTEGER str__len, CHAR *prefix, INTEGER prefix__len);


/*============================================================================*/

INTEGER arStrings_Length (CHAR *stringVal, INTEGER stringVal__len)
{
  INTEGER i;
  i = 0;
  while (stringVal[__X(i, stringVal__len, (CHAR*)"arStrings", 4637)] != 0x00) {
    i += 1;
  }
  return i;
}

/*----------------------------------------------------------------------------*/
BOOLEAN arStrings_Equal (CHAR *stringVal1, INTEGER stringVal1__len, CHAR *stringVal2, INTEGER stringVal2__len)
{
  INTEGER i;
  i = 0;
  while (stringVal1[__X(i, stringVal1__len, (CHAR*)"arStrings", 8000)] != 0x00 && stringVal1[__X(i, stringVal1__len, (CHAR*)"arStrings", 8000)] == stringVal2[__X(i, stringVal2__len, (CHAR*)"arStrings", 8000)]) {
    i += 1;
  }
  return stringVal1[__X(i, stringVal1__len, (CHAR*)"arStrings", 8959)] == 0x00 && stringVal2[__X(i, stringVal2__len, (CHAR*)"arStrings", 8959)] == 0x00;
}

/*----------------------------------------------------------------------------*/
void arStrings_Assign (CHAR *source, INTEGER source__len, CHAR *destination, INTEGER destination__len)
{
  INTEGER i;
  i = -1;
  do {
    i += 1;
    destination[__X(i, destination__len, (CHAR*)"arStrings", 12287)] = source[__X(i, source__len, (CHAR*)"arStrings", 12287)];
  } while (!(destination[__X(i, destination__len, (CHAR*)"arStrings", 12287)] == 0x00 || i == destination__len - 1));
  destination[__X(i, destination__len, (CHAR*)"arStrings", 12799)] = 0x00;
}

/*----------------------------------------------------------------------------*/
void arStrings_Extract (CHAR *source, INTEGER source__len, INTEGER startPos, INTEGER numberToExtract, CHAR *destination, INTEGER destination__len)
{
  INTEGER sourceLength, i;
  sourceLength = arStrings_Length(source, source__len);
  if (startPos > sourceLength) {
    startPos = sourceLength;
  }
  if (numberToExtract >= destination__len) {
    numberToExtract = destination__len - 1;
  }
  i = 0;
  while (i < numberToExtract && source[__X(startPos + i, source__len, (CHAR*)"arStrings", 19515)] != 0x00) {
    destination[__X(i, destination__len, (CHAR*)"arStrings", 19754)] = source[__X(startPos + i, source__len, (CHAR*)"arStrings", 19754)];
    i += 1;
  }
  destination[__X(i, destination__len, (CHAR*)"arStrings", 20735)] = 0x00;
}

/*----------------------------------------------------------------------------*/
void arStrings_Append (CHAR *source, INTEGER source__len, CHAR *destination, INTEGER destination__len)
{
  INTEGER destLength, i;
  destLength = arStrings_Length(destination, destination__len);
  i = 0;
  while (destLength < destination__len - 1 && source[__X(i, source__len, (CHAR*)"arStrings", 23103)] != 0x00) {
    destination[__X(destLength, destination__len, (CHAR*)"arStrings", 23338)] = source[__X(i, source__len, (CHAR*)"arStrings", 23338)];
    destLength += 1;
    i += 1;
  }
  destination[__X(destLength, destination__len, (CHAR*)"arStrings", 24575)] = 0x00;
}

/*----------------------------------------------------------------------------*/
BYTE arStrings_Compare (CHAR *stringVal1, INTEGER stringVal1__len, CHAR *stringVal2, INTEGER stringVal2__len)
{
  INTEGER i;
  i = 0;
  while (stringVal1[__X(i, stringVal1__len, (CHAR*)"arStrings", 27456)] != 0x00 && stringVal1[__X(i, stringVal1__len, (CHAR*)"arStrings", 27456)] == stringVal2[__X(i, stringVal2__len, (CHAR*)"arStrings", 27456)]) {
    i += 1;
  }
  if (stringVal1[__X(i, stringVal1__len, (CHAR*)"arStrings", 29951)] < stringVal2[__X(i, stringVal2__len, (CHAR*)"arStrings", 29951)]) {
    return -1;
  } else if (stringVal1[__X(i, stringVal1__len, (CHAR*)"arStrings", 28431)] > stringVal2[__X(i, stringVal2__len, (CHAR*)"arStrings", 28431)]) {
    return 1;
  } else {
    return 0;
  }
  __RETCHK((CHAR*)"arStrings", 29695);
}

/*----------------------------------------------------------------------------*/
BOOLEAN arStrings_StartsWith (CHAR *str, INTEGER str__len, CHAR *prefix, INTEGER prefix__len)
{
  INTEGER lenStr, lenPrefix, i, _for__13;
  lenStr = arStrings_Length(str, str__len);
  lenPrefix = arStrings_Length(prefix, prefix__len);
  if (lenPrefix > lenStr) {
    return 0;
  }
  _for__13 = lenPrefix - 1;
  i = 0;
  while (i <= _for__13) {
    if (prefix[__X(i, prefix__len, (CHAR*)"arStrings", 32301)] != str[__X(i, str__len, (CHAR*)"arStrings", 32301)]) {
      return 0;
    }
    i += 1;
  }
  return 1;
}

/*----------------------------------------------------------------------------*/
BOOLEAN arStrings_EndsWith (CHAR *str, INTEGER str__len, CHAR *suffix, INTEGER suffix__len)
{
  INTEGER lenStr, lenSuffix, i, _for__6;
  lenStr = arStrings_Length(str, str__len);
  lenSuffix = arStrings_Length(suffix, suffix__len);
  if (lenSuffix > lenStr) {
    return 0;
  }
  _for__6 = lenSuffix - 1;
  i = 0;
  while (i <= _for__6) {
    if (suffix[__X(i, suffix__len, (CHAR*)"arStrings", 35390)] != str[__X((lenStr - lenSuffix) + i, str__len, (CHAR*)"arStrings", 35390)]) {
      return 0;
    }
    i += 1;
  }
  return 1;
}

/*----------------------------------------------------------------------------*/
INTEGER arStrings_IndexOf (CHAR *str, INTEGER str__len, CHAR ch, INTEGER pos)
{
  INTEGER length;
  length = arStrings_Length(str, str__len);
  if (length == 0) {
    return -1;
  }
  if (pos < 0) {
    pos = length + pos;
  }
  if (pos < 0 || pos >= length) {
    return -1;
  }
  while (pos < length) {
    if (str[__X(pos, str__len, (CHAR*)"arStrings", 38694)] == ch) {
      return pos;
    }
    pos += 1;
  }
  return -1;
}

/*----------------------------------------------------------------------------*/
INTEGER arStrings_LastIndexOf (CHAR *str, INTEGER str__len, CHAR ch, INTEGER pos)
{
  INTEGER length;
  length = arStrings_Length(str, str__len);
  if (length == 0) {
    return -1;
  }
  if (pos < 0) {
    pos = length + pos;
  }
  if (pos < 0 || pos >= length) {
    return -1;
  }
  while (pos >= 0) {
    if (str[__X(pos, str__len, (CHAR*)"arStrings", 42278)] == ch) {
      return pos;
    }
    pos -= 1;
  }
  return -1;
}

/*----------------------------------------------------------------------------*/
arStrings_StringPtr arStrings_Copy (CHAR *value, INTEGER value__len)
{
  INTEGER length;
  arStrings_StringPtr result = NIL;
  length = arStrings_Length(value, value__len);
  result = __NEWARR(NIL, 1, 1, 1, 1, (SYSTEM_ARRLEN)(length + 1));
  __COPY(value, result->data, __MIN(result->len[0], value__len));
  return result;
}

/*----------------------------------------------------------------------------*/

export void *arStrings__init (void)
{
  __DEFMOD;
  __REGMOD("arStrings", 0);
/* BEGIN */
  __ENDMOD;
}
