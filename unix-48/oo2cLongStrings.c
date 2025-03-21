/* Ofront+ 1.0 -sC -48 */
#include "SYSTEM.oh"




export void oo2cLongStrings_Append (LONGCHAR *source, INTEGER source__len, LONGCHAR *destination, INTEGER destination__len);
export void oo2cLongStrings_Assign (LONGCHAR *source, INTEGER source__len, LONGCHAR *destination, INTEGER destination__len);
export BOOLEAN oo2cLongStrings_CanAppendAll (INTEGER sourceLength, LONGCHAR *destination, INTEGER destination__len);
export BOOLEAN oo2cLongStrings_CanAssignAll (INTEGER sourceLength, LONGCHAR *destination, INTEGER destination__len);
export BOOLEAN oo2cLongStrings_CanConcatAll (INTEGER source1Length, INTEGER source2Length, LONGCHAR *destination, INTEGER destination__len);
export BOOLEAN oo2cLongStrings_CanDeleteAll (INTEGER stringLength, INTEGER startPos, INTEGER numberToDelete);
export BOOLEAN oo2cLongStrings_CanExtractAll (INTEGER sourceLength, INTEGER startPos, INTEGER numberToExtract, LONGCHAR *destination, INTEGER destination__len);
export BOOLEAN oo2cLongStrings_CanInsertAll (INTEGER sourceLength, INTEGER startPos, LONGCHAR *destination, INTEGER destination__len);
export BOOLEAN oo2cLongStrings_CanReplaceAll (INTEGER sourceLength, INTEGER startPos, LONGCHAR *destination, INTEGER destination__len);
export void oo2cLongStrings_Capitalize (LONGCHAR *stringVar, INTEGER stringVar__len);
export BYTE oo2cLongStrings_Compare (LONGCHAR *stringVal1, INTEGER stringVal1__len, LONGCHAR *stringVal2, INTEGER stringVal2__len);
export void oo2cLongStrings_Concat (LONGCHAR *source1, INTEGER source1__len, LONGCHAR *source2, INTEGER source2__len, LONGCHAR *destination, INTEGER destination__len);
export void oo2cLongStrings_Delete (LONGCHAR *stringVar, INTEGER stringVar__len, INTEGER startPos, INTEGER numberToDelete);
export BOOLEAN oo2cLongStrings_Equal (LONGCHAR *stringVal1, INTEGER stringVal1__len, LONGCHAR *stringVal2, INTEGER stringVal2__len);
export void oo2cLongStrings_Extract (LONGCHAR *source, INTEGER source__len, INTEGER startPos, INTEGER numberToExtract, LONGCHAR *destination, INTEGER destination__len);
export void oo2cLongStrings_FindDiff (LONGCHAR *stringVal1, INTEGER stringVal1__len, LONGCHAR *stringVal2, INTEGER stringVal2__len, BOOLEAN *differenceFound, INTEGER *posOfDifference);
export void oo2cLongStrings_FindNext (LONGCHAR *pattern, INTEGER pattern__len, LONGCHAR *stringToSearch, INTEGER stringToSearch__len, INTEGER startPos, BOOLEAN *patternFound, INTEGER *posOfPattern);
export void oo2cLongStrings_FindPrev (LONGCHAR *pattern, INTEGER pattern__len, LONGCHAR *stringToSearch, INTEGER stringToSearch__len, INTEGER startPos, BOOLEAN *patternFound, INTEGER *posOfPattern);
export void oo2cLongStrings_Insert (LONGCHAR *source, INTEGER source__len, INTEGER startPos, LONGCHAR *destination, INTEGER destination__len);
export INTEGER oo2cLongStrings_Length (LONGCHAR *stringVal, INTEGER stringVal__len);
export void oo2cLongStrings_Long (CHAR *source, INTEGER source__len, LONGCHAR *destination, INTEGER destination__len);
export void oo2cLongStrings_Replace (LONGCHAR *source, INTEGER source__len, INTEGER startPos, LONGCHAR *destination, INTEGER destination__len);
export void oo2cLongStrings_Short (LONGCHAR *source, INTEGER source__len, CHAR repl, CHAR *destination, INTEGER destination__len);


/*============================================================================*/

INTEGER oo2cLongStrings_Length (LONGCHAR *stringVal, INTEGER stringVal__len)
{
  return __STRLENL(stringVal, stringVal__len, (CHAR*)"oo2cLongStrings", 15359);
}

/*----------------------------------------------------------------------------*/
void oo2cLongStrings_Assign (LONGCHAR *source, INTEGER source__len, LONGCHAR *destination, INTEGER destination__len)
{
  INTEGER i;
  i = -1;
  do {
    i += 1;
    destination[__X(i, destination__len, (CHAR*)"oo2cLongStrings", 19199)] = source[__X(i, source__len, (CHAR*)"oo2cLongStrings", 19199)];
  } while (!(destination[__X(i, destination__len, (CHAR*)"oo2cLongStrings", 19199)] == 0x00 || i == destination__len - 1));
  destination[__X(i, destination__len, (CHAR*)"oo2cLongStrings", 19711)] = 0x00;
}

/*----------------------------------------------------------------------------*/
void oo2cLongStrings_Extract (LONGCHAR *source, INTEGER source__len, INTEGER startPos, INTEGER numberToExtract, LONGCHAR *destination, INTEGER destination__len)
{
  INTEGER sourceLength, i;
  sourceLength = __STRLENL(source, source__len, (CHAR*)"oo2cLongStrings", 24097);
  if (startPos > sourceLength) {
    startPos = sourceLength;
  }
  if (numberToExtract >= destination__len) {
    numberToExtract = destination__len - 1;
  }
  i = 0;
  while (i < numberToExtract && source[__X(startPos + i, source__len, (CHAR*)"oo2cLongStrings", 27451)] != 0x00) {
    destination[__X(i, destination__len, (CHAR*)"oo2cLongStrings", 27690)] = source[__X(startPos + i, source__len, (CHAR*)"oo2cLongStrings", 27690)];
    i += 1;
  }
  destination[__X(i, destination__len, (CHAR*)"oo2cLongStrings", 28671)] = 0x00;
}

/*----------------------------------------------------------------------------*/
void oo2cLongStrings_Delete (LONGCHAR *stringVar, INTEGER stringVar__len, INTEGER startPos, INTEGER numberToDelete)
{
  INTEGER stringLength, i, _for__14;
  stringLength = __STRLENL(stringVar, stringVar__len, (CHAR*)"oo2cLongStrings", 32548);
  if (startPos + numberToDelete < stringLength) {
    _for__14 = stringLength - numberToDelete;
    i = startPos;
    while (i <= _for__14) {
      stringVar[__X(i, stringVar__len, (CHAR*)"oo2cLongStrings", 34047)] = stringVar[__X(i + numberToDelete, stringVar__len, (CHAR*)"oo2cLongStrings", 34047)];
      i += 1;
    }
  } else if (startPos < stringLength) {
    stringVar[__X(startPos, stringVar__len, (CHAR*)"oo2cLongStrings", 34815)] = 0x00;
  }
}

/*----------------------------------------------------------------------------*/
void oo2cLongStrings_Insert (LONGCHAR *source, INTEGER source__len, INTEGER startPos, LONGCHAR *destination, INTEGER destination__len)
{
  INTEGER sourceLength, destLength, destMax, i, _for__22, _for__21;
  destLength = __STRLENL(destination, destination__len, (CHAR*)"oo2cLongStrings", 39972);
  sourceLength = __STRLENL(source, source__len, (CHAR*)"oo2cLongStrings", 40225);
  destMax = destination__len - 1;
  if (startPos + sourceLength < destMax) {
    if (destLength + sourceLength > destMax) {
      destLength = destMax - sourceLength;
      destination[__X(destLength, destination__len, (CHAR*)"oo2cLongStrings", 42239)] = 0x00;
    }
    _for__22 = startPos;
    i = destLength;
    while (i >= _for__22) {
      destination[__X(i + sourceLength, destination__len, (CHAR*)"oo2cLongStrings", 43519)] = destination[__X(i, destination__len, (CHAR*)"oo2cLongStrings", 43519)];
      i += -1;
    }
  } else if (startPos <= destLength) {
    destination[__X(destMax, destination__len, (CHAR*)"oo2cLongStrings", 44320)] = 0x00;
    sourceLength = destMax - startPos;
  } else {
    sourceLength = 0;
  }
  _for__21 = sourceLength - 1;
  i = 0;
  while (i <= _for__21) {
    destination[__X(startPos + i, destination__len, (CHAR*)"oo2cLongStrings", 46335)] = source[__X(i, source__len, (CHAR*)"oo2cLongStrings", 46335)];
    i += 1;
  }
}

/*----------------------------------------------------------------------------*/
void oo2cLongStrings_Replace (LONGCHAR *source, INTEGER source__len, INTEGER startPos, LONGCHAR *destination, INTEGER destination__len)
{
  INTEGER destLength, i;
  destLength = __STRLENL(destination, destination__len, (CHAR*)"oo2cLongStrings", 50980);
  if (startPos < destLength) {
    i = 0;
    while (startPos != destLength && source[__X(i, source__len, (CHAR*)"oo2cLongStrings", 52278)] != 0x00) {
      destination[__X(startPos, destination__len, (CHAR*)"oo2cLongStrings", 52522)] = source[__X(i, source__len, (CHAR*)"oo2cLongStrings", 52522)];
      startPos += 1;
      i += 1;
    }
  }
}

/*----------------------------------------------------------------------------*/
void oo2cLongStrings_Append (LONGCHAR *source, INTEGER source__len, LONGCHAR *destination, INTEGER destination__len)
{
  INTEGER destLength, i;
  destLength = __STRLENL(destination, destination__len, (CHAR*)"oo2cLongStrings", 55588);
  i = 0;
  while (destLength < destination__len - 1 && source[__X(i, source__len, (CHAR*)"oo2cLongStrings", 56127)] != 0x00) {
    destination[__X(destLength, destination__len, (CHAR*)"oo2cLongStrings", 56362)] = source[__X(i, source__len, (CHAR*)"oo2cLongStrings", 56362)];
    destLength += 1;
    i += 1;
  }
  destination[__X(destLength, destination__len, (CHAR*)"oo2cLongStrings", 57599)] = 0x00;
}

/*----------------------------------------------------------------------------*/
void oo2cLongStrings_Concat (LONGCHAR *source1, INTEGER source1__len, LONGCHAR *source2, INTEGER source2__len, LONGCHAR *destination, INTEGER destination__len)
{
  INTEGER i, j;
  i = 0;
  while (source1[__X(i, source1__len, (CHAR*)"oo2cLongStrings", 60470)] != 0x00 && i < destination__len - 1) {
    destination[__X(i, destination__len, (CHAR*)"oo2cLongStrings", 60706)] = source1[__X(i, source1__len, (CHAR*)"oo2cLongStrings", 60706)];
    i += 1;
  }
  j = 0;
  while (source2[__X(j, source2__len, (CHAR*)"oo2cLongStrings", 62263)] != 0x00 && i < destination__len - 1) {
    destination[__X(i, destination__len, (CHAR*)"oo2cLongStrings", 62498)] = source2[__X(j, source2__len, (CHAR*)"oo2cLongStrings", 62498)];
    j += 1;
    i += 1;
  }
  destination[__X(i, destination__len, (CHAR*)"oo2cLongStrings", 63487)] = 0x00;
}

/*----------------------------------------------------------------------------*/
BOOLEAN oo2cLongStrings_CanAssignAll (INTEGER sourceLength, LONGCHAR *destination, INTEGER destination__len)
{
  return sourceLength < destination__len;
}

/*----------------------------------------------------------------------------*/
BOOLEAN oo2cLongStrings_CanExtractAll (INTEGER sourceLength, INTEGER startPos, INTEGER numberToExtract, LONGCHAR *destination, INTEGER destination__len)
{
  return startPos + numberToExtract <= sourceLength && numberToExtract < destination__len;
}

/*----------------------------------------------------------------------------*/
BOOLEAN oo2cLongStrings_CanDeleteAll (INTEGER stringLength, INTEGER startPos, INTEGER numberToDelete)
{
  return startPos + numberToDelete <= stringLength;
}

/*----------------------------------------------------------------------------*/
BOOLEAN oo2cLongStrings_CanInsertAll (INTEGER sourceLength, INTEGER startPos, LONGCHAR *destination, INTEGER destination__len)
{
  INTEGER lenDestination;
  lenDestination = __STRLENL(destination, destination__len, (CHAR*)"oo2cLongStrings", 78376);
  return startPos <= lenDestination && sourceLength + lenDestination < destination__len;
}

/*----------------------------------------------------------------------------*/
BOOLEAN oo2cLongStrings_CanReplaceAll (INTEGER sourceLength, INTEGER startPos, LONGCHAR *destination, INTEGER destination__len)
{
  return sourceLength + startPos <= __STRLENL(destination, destination__len, (CHAR*)"oo2cLongStrings", 82431);
}

/*----------------------------------------------------------------------------*/
BOOLEAN oo2cLongStrings_CanAppendAll (INTEGER sourceLength, LONGCHAR *destination, INTEGER destination__len)
{
  return __STRLENL(destination, destination__len, (CHAR*)"oo2cLongStrings", 85759) + sourceLength < destination__len;
}

/*----------------------------------------------------------------------------*/
BOOLEAN oo2cLongStrings_CanConcatAll (INTEGER source1Length, INTEGER source2Length, LONGCHAR *destination, INTEGER destination__len)
{
  return source1Length + source2Length < destination__len;
}

/*----------------------------------------------------------------------------*/
BYTE oo2cLongStrings_Compare (LONGCHAR *stringVal1, INTEGER stringVal1__len, LONGCHAR *stringVal2, INTEGER stringVal2__len)
{
  INTEGER i;
  i = 0;
  while (stringVal1[__X(i, stringVal1__len, (CHAR*)"oo2cLongStrings", 92480)] != 0x00 && stringVal1[__X(i, stringVal1__len, (CHAR*)"oo2cLongStrings", 92480)] == stringVal2[__X(i, stringVal2__len, (CHAR*)"oo2cLongStrings", 92480)]) {
    i += 1;
  }
  if (stringVal1[__X(i, stringVal1__len, (CHAR*)"oo2cLongStrings", 94975)] < stringVal2[__X(i, stringVal2__len, (CHAR*)"oo2cLongStrings", 94975)]) {
    return -1;
  } else if (stringVal1[__X(i, stringVal1__len, (CHAR*)"oo2cLongStrings", 93457)] > stringVal2[__X(i, stringVal2__len, (CHAR*)"oo2cLongStrings", 93457)]) {
    return 1;
  } else {
    return 0;
  }
  __RETCHK((CHAR*)"oo2cLongStrings", 94719);
}

/*----------------------------------------------------------------------------*/
BOOLEAN oo2cLongStrings_Equal (LONGCHAR *stringVal1, INTEGER stringVal1__len, LONGCHAR *stringVal2, INTEGER stringVal2__len)
{
  INTEGER i;
  i = 0;
  while (stringVal1[__X(i, stringVal1__len, (CHAR*)"oo2cLongStrings", 97344)] != 0x00 && stringVal1[__X(i, stringVal1__len, (CHAR*)"oo2cLongStrings", 97344)] == stringVal2[__X(i, stringVal2__len, (CHAR*)"oo2cLongStrings", 97344)]) {
    i += 1;
  }
  return stringVal1[__X(i, stringVal1__len, (CHAR*)"oo2cLongStrings", 98303)] == 0x00 && stringVal2[__X(i, stringVal2__len, (CHAR*)"oo2cLongStrings", 98303)] == 0x00;
}

/*----------------------------------------------------------------------------*/
void oo2cLongStrings_FindNext (LONGCHAR *pattern, INTEGER pattern__len, LONGCHAR *stringToSearch, INTEGER stringToSearch__len, INTEGER startPos, BOOLEAN *patternFound, INTEGER *posOfPattern)
{
  INTEGER patternPos;
  if (startPos < __STRLENL(stringToSearch, stringToSearch__len, (CHAR*)"oo2cLongStrings", 110079)) {
    patternPos = 0;
    for (;;) {
      if (pattern[__X(patternPos, pattern__len, (CHAR*)"oo2cLongStrings", 109055)] == 0x00) {
        *patternFound = 1;
        *posOfPattern = startPos - patternPos;
        break;
      } else if (stringToSearch[__X(startPos, stringToSearch__len, (CHAR*)"oo2cLongStrings", 105727)] == 0x00) {
        *patternFound = 0;
        break;
      } else if (stringToSearch[__X(startPos, stringToSearch__len, (CHAR*)"oo2cLongStrings", 106751)] == pattern[__X(patternPos, pattern__len, (CHAR*)"oo2cLongStrings", 106751)]) {
        startPos += 1;
        patternPos += 1;
      } else {
        startPos = (startPos - patternPos) + 1;
        patternPos = 0;
      }
    }
  } else {
    *patternFound = 0;
  }
}

/*----------------------------------------------------------------------------*/
void oo2cLongStrings_FindPrev (LONGCHAR *pattern, INTEGER pattern__len, LONGCHAR *stringToSearch, INTEGER stringToSearch__len, INTEGER startPos, BOOLEAN *patternFound, INTEGER *posOfPattern)
{
  INTEGER patternPos, stringLength, patternLength;
  stringLength = __STRLENL(stringToSearch, stringToSearch__len, (CHAR*)"oo2cLongStrings", 114985);
  patternLength = __STRLENL(pattern, pattern__len, (CHAR*)"oo2cLongStrings", 115235);
  if (startPos > stringLength - patternLength) {
    startPos = stringLength - patternLength;
  }
  if (startPos >= 0) {
    patternPos = 0;
    for (;;) {
      if (pattern[__X(patternPos, pattern__len, (CHAR*)"oo2cLongStrings", 122111)] == 0x00) {
        *patternFound = 1;
        *posOfPattern = startPos - patternPos;
        break;
      } else if (stringToSearch[__X(startPos, stringToSearch__len, (CHAR*)"oo2cLongStrings", 118527)] != pattern[__X(patternPos, pattern__len, (CHAR*)"oo2cLongStrings", 118527)]) {
        if (startPos > patternPos) {
          startPos = (startPos - patternPos) - 1;
          patternPos = 0;
        } else {
          *patternFound = 0;
          break;
        }
      } else {
        startPos += 1;
        patternPos += 1;
      }
    }
  } else {
    *patternFound = 0;
  }
}

/*----------------------------------------------------------------------------*/
void oo2cLongStrings_FindDiff (LONGCHAR *stringVal1, INTEGER stringVal1__len, LONGCHAR *stringVal2, INTEGER stringVal2__len, BOOLEAN *differenceFound, INTEGER *posOfDifference)
{
  INTEGER i;
  i = 0;
  while (stringVal1[__X(i, stringVal1__len, (CHAR*)"oo2cLongStrings", 126784)] != 0x00 && stringVal1[__X(i, stringVal1__len, (CHAR*)"oo2cLongStrings", 126784)] == stringVal2[__X(i, stringVal2__len, (CHAR*)"oo2cLongStrings", 126784)]) {
    i += 1;
  }
  *differenceFound = stringVal1[__X(i, stringVal1__len, (CHAR*)"oo2cLongStrings", 127555)] != 0x00 || stringVal2[__X(i, stringVal2__len, (CHAR*)"oo2cLongStrings", 127555)] != 0x00;
  if (*differenceFound) {
    *posOfDifference = i;
  }
}

/*----------------------------------------------------------------------------*/
void oo2cLongStrings_Capitalize (LONGCHAR *stringVar, INTEGER stringVar__len)
{
  INTEGER i;
  i = 0;
  while (stringVar[__X(i, stringVar__len, (CHAR*)"oo2cLongStrings", 131101)] != 0x00) {
    stringVar[__X(i, stringVar__len, (CHAR*)"oo2cLongStrings", 131368)] = __CAP(stringVar[__X(i, stringVar__len, (CHAR*)"oo2cLongStrings", 131368)]);
    i += 1;
  }
}

/*----------------------------------------------------------------------------*/
void oo2cLongStrings_Long (CHAR *source, INTEGER source__len, LONGCHAR *destination, INTEGER destination__len)
{
  __STRCOPYCL(source, destination, destination__len, (CHAR*)"oo2cLongStrings", 134399);
}

/*----------------------------------------------------------------------------*/
void oo2cLongStrings_Short (LONGCHAR *source, INTEGER source__len, CHAR repl, CHAR *destination, INTEGER destination__len)
{
  INTEGER i, len;
  len = destination__len - 1;
  i = 0;
  while (source[__X(i, source__len, (CHAR*)"oo2cLongStrings", 137254)] != 0x00 && i != len) {
    if (source[__X(i, source__len, (CHAR*)"oo2cLongStrings", 138505)] <= 0xffff) {
      destination[__X(i, destination__len, (CHAR*)"oo2cLongStrings", 137983)] = (CHAR)source[__X(i, source__len, (CHAR*)"oo2cLongStrings", 137983)];
    } else {
      destination[__X(i, destination__len, (CHAR*)"oo2cLongStrings", 138495)] = repl;
    }
    i += 1;
  }
  destination[__X(i, destination__len, (CHAR*)"oo2cLongStrings", 139519)] = 0x00;
}

/*----------------------------------------------------------------------------*/

export void *oo2cLongStrings__init (void)
{
  __DEFMOD;
  __REGMOD("oo2cLongStrings", 0);
/* BEGIN */
  __ENDMOD;
}
