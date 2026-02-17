/* Ofront+ 1.0 -s2 -44 */
#include "SYSTEM.oh"
#include "Files.oh"
#include "Platform.oh"
#include "Zlib.oh"
#include "ZlibBuffers.oh"
#include "ZlibDeflate.oh"

typedef
  struct ZlibWriters_Writer {
    INTEGER res;
    BYTE flush;
    BOOLEAN wrapper;
    Files_Rider r;
    INTEGER pos, crc32;
    CHAR (*out)[65536];
    ZlibDeflate_Stream s;
  } ZlibWriters_Writer;



export void **ZlibWriters_Writer__typ;

export void ZlibWriters_Close (ZlibWriters_Writer *w, void **w__typ);
export void ZlibWriters_Compress (Files_Rider *src, void **src__typ, Files_Rider *dst, void **dst__typ, INTEGER srclen, INTEGER *dstlen, BYTE level, BYTE strategy, INTEGER *crc32, INTEGER *res);
export void ZlibWriters_Open (ZlibWriters_Writer *w, void **w__typ, BYTE level, BYTE strategy, BYTE flush, BOOLEAN wrapper, Files_Rider r);
export void ZlibWriters_SetParams (ZlibWriters_Writer *w, void **w__typ, BYTE level, BYTE strategy, BYTE flush);
export void ZlibWriters_Write (ZlibWriters_Writer *w, void **w__typ, CHAR ch);
export void ZlibWriters_WriteBytes (ZlibWriters_Writer *w, void **w__typ, CHAR *buf, INTEGER buf__len, INTEGER offset, INTEGER len, INTEGER *written);


/*============================================================================*/

void ZlibWriters_SetParams (ZlibWriters_Writer *w, void **w__typ, BYTE level, BYTE strategy, BYTE flush)
{
  if (__IN(flush, 0x0d)) {
    ZlibDeflate_SetParams(&(*w).s, ZlibDeflate_Stream__typ, level, strategy);
    (*w).flush = flush;
    (*w).res = (*w).s.res;
  } else {
    (*w).res = -2;
  }
}

/*----------------------------------------------------------------------------*/
void ZlibWriters_Open (ZlibWriters_Writer *w, void **w__typ, BYTE level, BYTE strategy, BYTE flush, BOOLEAN wrapper, Files_Rider r)
{
  CHAR (*_ptr__5)[65536] = NIL;
  CHAR (*_ptr__4)[65536] = NIL;
  if (__IN(flush, 0x0d)) {
    (*w).flush = flush;
    (*w).wrapper = wrapper;
    ZlibDeflate_Open(&(*w).s, ZlibDeflate_Stream__typ, level, strategy, wrapper);
    if ((*w).s.res == 0) {
      (*w).out = __NEWARR(NIL, 1, 1, 1, 0, (SYSTEM_ARRLEN)65536);
      _ptr__5 = (*w).out;
      ZlibBuffers_Init(&(*w).s.out, ZlibBuffers_Buffer__typ, (void*)*_ptr__5, 65536, 0, 65536, 65536);
      (*w).crc32 = (_ptr__4 = (*w).out, 
        Zlib_CRC32(0, (void*)*_ptr__4, 65536, -1, -1));
      (*w).r = r;
      (*w).res = 0;
    } else {
      (*w).res = (*w).s.res;
    }
  } else {
    (*w).res = -2;
  }
}

/*----------------------------------------------------------------------------*/
void ZlibWriters_WriteBytes (ZlibWriters_Writer *w, void **w__typ, CHAR *buf, INTEGER buf__len, INTEGER offset, INTEGER len, INTEGER *written)
{
  __ASSERT((0 <= offset && 0 <= len) && len <= buf__len, 110, (CHAR*)"ZlibWriters", 19772);
  if (!(*w).s.open) {
    (*w).res = -2;
    *written = 0;
  } else if ((*w).res < 0 || len <= 0) {
    *written = 0;
  } else {
    ZlibBuffers_Init(&(*w).s.in, ZlibBuffers_Buffer__typ, (void*)buf, buf__len, offset, len, len);
    while ((*w).res == 0 && (*w).s.in.avail != 0) {
      if ((*w).s.out.avail == 0) {
        Files_WriteBytes(&(*w).r, Files_Rider__typ, (void*)(SYSTEM_ADRINT)*(*w).out, 65536, 65536);
        ZlibBuffers_Rewrite(&(*w).s.out, ZlibBuffers_Buffer__typ);
      }
      if ((*w).res == 0) {
        ZlibDeflate_Deflate(&(*w).s, ZlibDeflate_Stream__typ, (*w).flush);
        (*w).res = (*w).s.res;
      }
    }
    (*w).crc32 = Zlib_CRC32((*w).crc32, (void*)buf, buf__len, offset, len - (*w).s.in.avail);
    *written = len - (*w).s.in.avail;
  }
}

/*----------------------------------------------------------------------------*/
void ZlibWriters_Write (ZlibWriters_Writer *w, void **w__typ, CHAR ch)
{
  CHAR buf[1];
  INTEGER written;
  buf[0] = ch;
  ZlibWriters_WriteBytes(w, w__typ, (void*)buf, 1, 0, 1, &written);
}

/*----------------------------------------------------------------------------*/
void ZlibWriters_Close (ZlibWriters_Writer *w, void **w__typ)
{
  BOOLEAN done;
  INTEGER len;
  __ASSERT((*w).s.in.avail == 0, 110, (CHAR*)"ZlibWriters", 29470);
  done = 0;
  for (;;) {
    len = 65536 - (*w).s.out.avail;
    if (len != 0) {
      Files_WriteBytes(&(*w).r, Files_Rider__typ, (void*)(SYSTEM_ADRINT)*(*w).out, 65536, len);
      ZlibBuffers_Rewrite(&(*w).s.out, ZlibBuffers_Buffer__typ);
    }
    if (done) {
      break;
    }
    ZlibDeflate_Deflate(&(*w).s, ZlibDeflate_Stream__typ, 4);
    if (len == 0 && (*w).s.res == -5) {
      (*w).res = 0;
    } else {
      (*w).res = (*w).s.res;
    }
    done = (*w).s.out.avail != 0 || (*w).res == 1;
    if ((*w).res != 0 && (*w).res != 1) {
      break;
    }
  }
  ZlibDeflate_Close(&(*w).s, ZlibDeflate_Stream__typ);
  (*w).res = (*w).s.res;
}

/*----------------------------------------------------------------------------*/
void ZlibWriters_Compress (Files_Rider *src, void **src__typ, Files_Rider *dst, void **dst__typ, INTEGER srclen, INTEGER *dstlen, BYTE level, BYTE strategy, INTEGER *crc32, INTEGER *res)
{
  ZlibWriters_Writer w = {0};
  CHAR buf[65536];
  INTEGER totWritten, written, read;
  ZlibWriters_Open(&w, ZlibWriters_Writer__typ, level, strategy, 0, 0, *dst);
  if (w.res == 0) {
    totWritten = 0;
    do {
      if (srclen - totWritten >= 65536) {
        read = 65536;
      } else {
        read = srclen - totWritten;
      }
      Files_ReadBytes(src, src__typ, (void*)(SYSTEM_ADRINT)buf, 65536, read);
      ZlibWriters_WriteBytes(&w, ZlibWriters_Writer__typ, (void*)buf, 65536, 0, read - (*src).res, &written);
      totWritten += written;
    } while (!(w.res != 0 || totWritten >= srclen));
    ZlibWriters_Close(&w, ZlibWriters_Writer__typ);
    *crc32 = w.crc32;
    *dstlen = (INTEGER)(Files_Pos(&w.r, Files_Rider__typ) - Files_Pos(dst, dst__typ));
  }
  *res = w.res;
}

/*----------------------------------------------------------------------------*/
__TDESC(ZlibWriters_Writer__desc, 2, 20) = {__TDFLDS("Writer", 2608), {16, 40, 108, 120, 124, 156, 168, 176, 180, 192, 200, 204, 216, 224, 228, 240, 
  244, 248, 2580, 2584, -84}};

export void *ZlibWriters__init (void)
{
  __DEFMOD;
  __IMPORT(Files__init);
  __IMPORT(Zlib__init);
  __IMPORT(ZlibBuffers__init);
  __IMPORT(ZlibDeflate__init);
  __REGMOD("ZlibWriters", 0);
  __INITYP(ZlibWriters_Writer, ZlibWriters_Writer, 0);
/* BEGIN */
  __ENDMOD;
}
