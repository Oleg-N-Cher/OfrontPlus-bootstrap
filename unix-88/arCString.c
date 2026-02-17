/* Ofront+ 1.0 -s2 -88 */
#include "SYSTEM.oh"
#include "arC.oh"

typedef
  struct CHAR8_ARRAY *arCString_String;


#ifndef CHAR8_ARRAY_DEF
#define CHAR8_ARRAY_DEF
typedef struct CHAR8_ARRAY {
  INTEGER len[1];
  CHAR data[1];
} CHAR8_ARRAY;
#endif 



export arCString_String arCString_Copy (arC_string src);
export void arCString_CopyToArray (arC_string src, CHAR *dst, INTEGER dst__len);

#include <string.h>
#define arCString_strlen(argStr)  strlen((const char *)argStr)
#define arCString_strncpy(dst, src, len)  (CHAR *)strncpy((char *)dst, (const char *)src, len)

/*============================================================================*/

void arCString_CopyToArray (arC_string src, CHAR *dst, INTEGER dst__len)
{
  arC_string dummy = NIL;
  dummy = arCString_strncpy((arC_string)((SYSTEM_ADRINT)dst), src, dst__len);
}

/*----------------------------------------------------------------------------*/
arCString_String arCString_Copy (arC_string src)
{
  arCString_String result = NIL;
  INTEGER i, len;
  len = arCString_strlen(src);
  result = __NEWARR(NIL, 1, 1, 1, 1, (SYSTEM_ARRLEN)(len + 1));
  arCString_CopyToArray(src, (void*)result->data, result->len[0]);
  return result;
}

/*----------------------------------------------------------------------------*/
