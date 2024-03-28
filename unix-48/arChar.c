/* Ofront+ 1.0 -s2 -48 */
#include "SYSTEM.oh"




export BOOLEAN arChar_IsAlphaNumeric (CHAR ch);
export BOOLEAN arChar_IsDigit (CHAR ch);
export BOOLEAN arChar_IsLetter (CHAR ch);
export BOOLEAN arChar_IsSpace (CHAR ch);


/*============================================================================*/

BOOLEAN arChar_IsLetter (CHAR ch)
{
  return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
}

/*----------------------------------------------------------------------------*/
BOOLEAN arChar_IsDigit (CHAR ch)
{
  return ch >= '0' && ch <= '9';
}

/*----------------------------------------------------------------------------*/
BOOLEAN arChar_IsAlphaNumeric (CHAR ch)
{
  return arChar_IsLetter(ch) || arChar_IsDigit(ch);
}

/*----------------------------------------------------------------------------*/
BOOLEAN arChar_IsSpace (CHAR ch)
{
  return ((ch == ' ' || ch == 0x09) || ch == 0x0a) || ch == 0x0d;
}

/*----------------------------------------------------------------------------*/

export void *arChar__init (void)
{
  __DEFMOD;
  __REGMOD("arChar", 0);
/* BEGIN */
  __ENDMOD;
}
