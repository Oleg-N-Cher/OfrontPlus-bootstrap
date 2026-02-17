/* Ofront+ 1.0 -s2 -88 */
#include "SYSTEM.oh"

typedef
  struct ZlibBuffers_Buffer {
    INTEGER avail, size, totalOut, totalIn;
    LONGINT next, adr;
  } ZlibBuffers_Buffer;



export void **ZlibBuffers_Buffer__typ;

export void ZlibBuffers_Drain (ZlibBuffers_Buffer *buf, void **buf__typ, CHAR *dst, INTEGER dst__len, INTEGER offset, INTEGER size);
export void ZlibBuffers_Fill (ZlibBuffers_Buffer *buf, void **buf__typ, CHAR *src, INTEGER src__len, INTEGER offset, INTEGER size);
export void ZlibBuffers_Init (ZlibBuffers_Buffer *buf, void **buf__typ, CHAR *mem, INTEGER mem__len, INTEGER offset, INTEGER size, INTEGER avail);
export void ZlibBuffers_Read (ZlibBuffers_Buffer *buf, void **buf__typ, CHAR *ch);
export void ZlibBuffers_ReadBytes (ZlibBuffers_Buffer *buf, void **buf__typ, CHAR *dst, INTEGER dst__len, INTEGER offset, INTEGER len);
export void ZlibBuffers_Reread (ZlibBuffers_Buffer *buf, void **buf__typ, INTEGER offset);
export void ZlibBuffers_Reset (ZlibBuffers_Buffer *buf, void **buf__typ);
export void ZlibBuffers_Rewind (ZlibBuffers_Buffer *buf, void **buf__typ, INTEGER avail);
export void ZlibBuffers_Rewrite (ZlibBuffers_Buffer *buf, void **buf__typ);
export void ZlibBuffers_Write (ZlibBuffers_Buffer *buf, void **buf__typ, CHAR ch);
export void ZlibBuffers_WriteBytes (ZlibBuffers_Buffer *buf, void **buf__typ, CHAR *src, INTEGER src__len, INTEGER offset, INTEGER len);


/*============================================================================*/

void ZlibBuffers_Reset (ZlibBuffers_Buffer *buf, void **buf__typ)
{
  (*buf).totalIn = 0;
  (*buf).totalOut = 0;
}

/*----------------------------------------------------------------------------*/
void ZlibBuffers_Init (ZlibBuffers_Buffer *buf, void **buf__typ, CHAR *mem, INTEGER mem__len, INTEGER offset, INTEGER size, INTEGER avail)
{
  __ASSERT((0 <= offset && 0 < size) && offset + size <= mem__len, 100, (CHAR*)"ZlibBuffers", 9286);
  __ASSERT(0 <= avail && avail <= size, 101, (CHAR*)"ZlibBuffers", 9515);
  (*buf).avail = avail;
  (*buf).size = size;
  (*buf).adr = (SYSTEM_ADRINT)&mem[__X(offset, mem__len, (CHAR*)"ZlibBuffers", 9801)];
  (*buf).next = (*buf).adr;
}

/*----------------------------------------------------------------------------*/
void ZlibBuffers_Read (ZlibBuffers_Buffer *buf, void **buf__typ, CHAR *ch)
{
  __ASSERT((*buf).avail > 0, 100, (CHAR*)"ZlibBuffers", 11291);
  __GET((*buf).next, *ch, CHAR);
  (*buf).next += 1;
  (*buf).avail -= 1;
  (*buf).totalIn += 1;
}

/*----------------------------------------------------------------------------*/
void ZlibBuffers_ReadBytes (ZlibBuffers_Buffer *buf, void **buf__typ, CHAR *dst, INTEGER dst__len, INTEGER offset, INTEGER len)
{
  __ASSERT(((0 <= offset && 0 < len) && offset + len <= dst__len) && len <= (*buf).avail, 100, (CHAR*)"ZlibBuffers", 13401);
  __MOVE((*buf).next, (SYSTEM_ADRINT)&dst[__X(offset, dst__len, (CHAR*)"ZlibBuffers", 13620)], len);
  (*buf).next += len;
  (*buf).avail -= len;
  (*buf).totalIn += len;
}

/*----------------------------------------------------------------------------*/
void ZlibBuffers_Write (ZlibBuffers_Buffer *buf, void **buf__typ, CHAR ch)
{
  __ASSERT((*buf).avail > 0, 100, (CHAR*)"ZlibBuffers", 15387);
  __PUT((*buf).next, ch, CHAR);
  (*buf).next += 1;
  (*buf).avail -= 1;
  (*buf).totalOut += 1;
}

/*----------------------------------------------------------------------------*/
void ZlibBuffers_WriteBytes (ZlibBuffers_Buffer *buf, void **buf__typ, CHAR *src, INTEGER src__len, INTEGER offset, INTEGER len)
{
  __ASSERT(((0 <= offset && 0 < len) && offset + len <= src__len) && len <= (*buf).avail, 100, (CHAR*)"ZlibBuffers", 17497);
  __MOVE((SYSTEM_ADRINT)&src[__X(offset, src__len, (CHAR*)"ZlibBuffers", 17716)], (*buf).next, len);
  (*buf).next += len;
  (*buf).avail -= len;
  (*buf).totalOut += len;
}

/*----------------------------------------------------------------------------*/
void ZlibBuffers_Rewind (ZlibBuffers_Buffer *buf, void **buf__typ, INTEGER avail)
{
  __ASSERT((*buf).avail == 0, 100, (CHAR*)"ZlibBuffers", 19483);
  __ASSERT(0 <= avail && avail <= (*buf).size, 101, (CHAR*)"ZlibBuffers", 19760);
  (*buf).next = (*buf).adr;
  (*buf).avail = avail;
}

/*----------------------------------------------------------------------------*/
void ZlibBuffers_Reread (ZlibBuffers_Buffer *buf, void **buf__typ, INTEGER offset)
{
  __ASSERT(0 <= offset && (*buf).avail + offset <= (*buf).size, 101, (CHAR*)"ZlibBuffers", 21566);
  (*buf).next -= offset;
  (*buf).avail += offset;
}

/*----------------------------------------------------------------------------*/
void ZlibBuffers_Rewrite (ZlibBuffers_Buffer *buf, void **buf__typ)
{
  (*buf).next = (*buf).adr;
  (*buf).avail = (*buf).size;
}

/*----------------------------------------------------------------------------*/
void ZlibBuffers_Fill (ZlibBuffers_Buffer *buf, void **buf__typ, CHAR *src, INTEGER src__len, INTEGER offset, INTEGER size)
{
  __ASSERT((0 <= offset && 0 < size) && offset + size <= src__len, 100, (CHAR*)"ZlibBuffers", 24902);
  __ASSERT((*buf).avail + size <= (*buf).size, 101, (CHAR*)"ZlibBuffers", 25130);
  if ((*buf).avail != 0) {
    __MOVE((*buf).next, (*buf).adr, (*buf).avail);
  }
  (*buf).next = (*buf).adr + (LONGINT)(*buf).avail;
  __MOVE((SYSTEM_ADRINT)&src[__X(offset, src__len, (CHAR*)"ZlibBuffers", 26421)], (*buf).next, size);
  (*buf).avail += size;
}

/*----------------------------------------------------------------------------*/
void ZlibBuffers_Drain (ZlibBuffers_Buffer *buf, void **buf__typ, CHAR *dst, INTEGER dst__len, INTEGER offset, INTEGER size)
{
  INTEGER i, n;
  LONGINT d, s;
  CHAR c;
  INTEGER _for__2;
  __ASSERT((0 <= offset && 0 < size) && offset + size <= dst__len, 100, (CHAR*)"ZlibBuffers", 28486);
  __ASSERT((*buf).avail + size <= (*buf).size, 101, (CHAR*)"ZlibBuffers", 28714);
  __MOVE((*buf).adr, (SYSTEM_ADRINT)&dst[__X(offset, dst__len, (CHAR*)"ZlibBuffers", 28980)], size);
  n = ((*buf).size - (*buf).avail) - size;
  s = (*buf).adr + (LONGINT)size;
  d = (*buf).adr;
  _for__2 = n - 1;
  i = 0;
  while (i <= _for__2) {
    __GET(s + (LONGINT)i, c, CHAR);
    __PUT(d + (LONGINT)i, c, CHAR);
    i += 1;
  }
  (*buf).avail += size;
  (*buf).next -= size;
}

/*----------------------------------------------------------------------------*/
__TDESC(ZlibBuffers_Buffer__desc, 2, 0) = {__TDFLDS("Buffer", 32), {-8}};

export void *ZlibBuffers__init (void)
{
  __DEFMOD;
  __REGMOD("ZlibBuffers", 0);
  __INITYP(ZlibBuffers_Buffer, ZlibBuffers_Buffer, 0);
/* BEGIN */
  __ENDMOD;
}
