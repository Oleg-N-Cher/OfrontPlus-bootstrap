/* Ofront+ 1.0 -s2 -44 */
#include "SYSTEM.oh"


static INTEGER Zlib_CRCTable[256];


export INTEGER Zlib_Adler32 (INTEGER adler, CHAR *buf, INTEGER buf__len, INTEGER offset, INTEGER len);
export INTEGER Zlib_CRC32 (INTEGER crc, CHAR *buf, INTEGER buf__len, INTEGER offset, INTEGER len);
export void Zlib_InitCRCTable (void);


/*============================================================================*/

INTEGER Zlib_Adler32 (INTEGER adler, CHAR *buf, INTEGER buf__len, INTEGER offset, INTEGER len)
{
  INTEGER s1, s2, k, offset0, len0;
  offset0 = offset;
  len0 = len;
  if (len < 0) {
    return 1;
  } else {
    s1 = __MASK(adler, -65536);
    s2 = __MASK(__LSHR(adler, 16, INTEGER), -65536);
    while (len > 0) {
      if (len < 5552) {
        k = len;
      } else {
        k = 5552;
      }
      len -= k;
      do {
        s1 += (INTEGER)buf[__X(offset, buf__len, (CHAR*)"Zlib", 22307)];
        s2 += s1;
        offset += 1;
        k -= 1;
      } while (!(k == 0));
      s1 = __MOD(s1, 65521);
      s2 = __MOD(s2, 65521);
    }
    return __LSHL(s2, 16, INTEGER) + s1;
  }
  __RETCHK((CHAR*)"Zlib", 24575);
}

/*----------------------------------------------------------------------------*/
void Zlib_InitCRCTable (void)
{
  INTEGER n, c, k;
  n = 0;
  while (n <= 255) {
    c = n;
    k = 0;
    while (k <= 7) {
      if (__ODD(c)) {
        c = (INTEGER)((SET)-306674912 ^ (SET)__LSHR(c, 1, INTEGER));
      } else {
        c = __LSHR(c, 1, INTEGER);
      }
      k += 1;
    }
    Zlib_CRCTable[__X(n, 256, (CHAR*)"Zlib", 35071)] = c;
    n += 1;
  }
}

/*----------------------------------------------------------------------------*/
INTEGER Zlib_CRC32 (INTEGER crc, CHAR *buf, INTEGER buf__len, INTEGER offset, INTEGER len)
{
  INTEGER idx;
  if (offset < 0) {
    crc = 0;
  } else {
    crc = (INTEGER)((SET)crc ^ 0xffffffff);
    while (len > 0) {
      idx = __MASK((INTEGER)((SET)crc ^ (SET)((INTEGER)buf[__X(offset, buf__len, (CHAR*)"Zlib", 38244)])), -256);
      crc = (INTEGER)((SET)Zlib_CRCTable[__X(idx, 256, (CHAR*)"Zlib", 38498)] ^ (SET)__LSHR(crc, 8, INTEGER));
      len -= 1;
      offset += 1;
    }
    crc = (INTEGER)((SET)crc ^ 0xffffffff);
  }
  return crc;
}

/*----------------------------------------------------------------------------*/

export void *Zlib__init (void)
{
  __DEFMOD;
  __REGMOD("Zlib", 0);
  __REGCMD("InitCRCTable", Zlib_InitCRCTable);
/* BEGIN */
  Zlib_InitCRCTable();
  __ENDMOD;
}
