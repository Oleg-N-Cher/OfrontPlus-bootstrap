/* Ofront+ 1.0 -s2 -48 */
#include "SYSTEM.oh"
#include "Files.oh"
#include "Platform.oh"
#include "Zlib.oh"
#include "ZlibBuffers.oh"
#include "ZlibInflate.oh"

typedef
  struct ZlibReaders_Reader {
    INTEGER res, crc32;
    BOOLEAN wrapper, eof;
    Files_Rider r;
    CHAR (*in)[16384];
    ZlibInflate_Stream s;
  } ZlibReaders_Reader;



export void **ZlibReaders_Reader__typ;

export void ZlibReaders_Close (ZlibReaders_Reader *r, void **r__typ);
export void ZlibReaders_Open (ZlibReaders_Reader *r, void **r__typ, BOOLEAN wrapper, Files_Rider *fr, void **fr__typ);
export void ZlibReaders_Read (ZlibReaders_Reader *r, void **r__typ, CHAR *ch);
export void ZlibReaders_ReadBytes (ZlibReaders_Reader *r, void **r__typ, CHAR *buf, INTEGER buf__len, INTEGER offset, INTEGER len, INTEGER *read);
export void ZlibReaders_Uncompress (Files_Rider *src, void **src__typ, Files_Rider *dst, void **dst__typ, INTEGER *crc32, INTEGER *res);


/*============================================================================*/

void ZlibReaders_Open (ZlibReaders_Reader *r, void **r__typ, BOOLEAN wrapper, Files_Rider *fr, void **fr__typ)
{
  CHAR (*_ptr__4)[16384] = NIL;
  CHAR (*_ptr__3)[16384] = NIL;
  (*r).wrapper = wrapper;
  (*r).eof = (*fr).eof;
  ZlibInflate_Open(&(*r).s, ZlibInflate_Stream__typ, wrapper);
  if ((*r).s.res.code == 0) {
    (*r).in = __NEWARR(NIL, 1, 1, 1, 0, (SYSTEM_ARRLEN)16384);
    _ptr__4 = (*r).in;
    ZlibBuffers_Init(&(*r).s.in, ZlibBuffers_Buffer__typ, (void*)*_ptr__4, 16384, 0, 16384, 0);
    (*r).crc32 = (_ptr__3 = (*r).in, 
      Zlib_CRC32(0, (void*)*_ptr__3, 16384, -1, -1));
    (*r).r = *fr;
    (*r).res = 0;
  } else {
    (*r).res = (*r).s.res.code;
  }
}

/*----------------------------------------------------------------------------*/
void ZlibReaders_ReadBytes (ZlibReaders_Reader *r, void **r__typ, CHAR *buf, INTEGER buf__len, INTEGER offset, INTEGER len, INTEGER *read)
{
  __ASSERT((0 <= offset && 0 <= len) && offset + len <= buf__len, 100, (CHAR*)"ZlibReaders", 12357);
  if (!(*r).s.open) {
    (*r).res = -2;
    *read = 0;
  } else if (((*r).res < 0 || (*r).res == 1) || len <= 0) {
    *read = 0;
  } else {
    ZlibBuffers_Init(&(*r).s.out, ZlibBuffers_Buffer__typ, (void*)buf, buf__len, offset, len, len);
    while ((*r).s.out.avail != 0 && (*r).res == 0) {
      if ((*r).s.in.avail == 0) {
        Files_ReadBytes(&(*r).r, Files_Rider__typ, (void*)(SYSTEM_ADRINT)*(*r).in, 16384, 16384);
        ZlibBuffers_Rewind(&(*r).s.in, ZlibBuffers_Buffer__typ, 16384 - (*r).r.res);
        if ((*r).s.in.avail == 0) {
          (*r).eof = 1;
          if ((*r).r.res < 0) {
            (*r).res = -1;
          }
        }
      }
      if ((*r).res == 0) {
        ZlibInflate_Inflate(&(*r).s, ZlibInflate_Stream__typ, 0);
        (*r).res = (*r).s.res.code;
      }
    }
    (*r).crc32 = Zlib_CRC32((*r).crc32, (void*)buf, buf__len, offset, len - (*r).s.out.avail);
    *read = len - (*r).s.out.avail;
  }
}

/*----------------------------------------------------------------------------*/
void ZlibReaders_Read (ZlibReaders_Reader *r, void **r__typ, CHAR *ch)
{
  CHAR buf[1];
  INTEGER read;
  ZlibReaders_ReadBytes(r, r__typ, (void*)buf, 1, 0, 1, &read);
  *ch = buf[0];
}

/*----------------------------------------------------------------------------*/
void ZlibReaders_Close (ZlibReaders_Reader *r, void **r__typ)
{
  ZlibInflate_Close(&(*r).s, ZlibInflate_Stream__typ);
  (*r).in = NIL;
  if ((*r).res == 1) {
    (*r).res = 0;
  }
}

/*----------------------------------------------------------------------------*/
void ZlibReaders_Uncompress (Files_Rider *src, void **src__typ, Files_Rider *dst, void **dst__typ, INTEGER *crc32, INTEGER *res)
{
  ZlibReaders_Reader r = {0};
  CHAR buf[16384];
  INTEGER read;
  ZlibReaders_Open(&r, ZlibReaders_Reader__typ, 0, src, src__typ);
  if (r.res == 0) {
    do {
      ZlibReaders_ReadBytes(&r, ZlibReaders_Reader__typ, (void*)buf, 16384, 0, 16384, &read);
      Files_WriteBytes(dst, dst__typ, (void*)(SYSTEM_ADRINT)buf, 16384, read);
    } while (!(r.res != 0 || read == 0));
    *crc32 = r.crc32;
    ZlibReaders_Close(&r, ZlibReaders_Reader__typ);
  }
  *res = r.res;
}

/*----------------------------------------------------------------------------*/
__TDESC(ZlibReaders_Reader__desc, 1, 9) = {__TDFLDS("Reader", 560), {24, 48, 104, 112, 492, 496, 512, 524, 536, -40}};

export void *ZlibReaders__init (void)
{
  __DEFMOD;
  __IMPORT(Files__init);
  __IMPORT(Zlib__init);
  __IMPORT(ZlibBuffers__init);
  __IMPORT(ZlibInflate__init);
  __REGMOD("ZlibReaders", 0);
  __INITYP(ZlibReaders_Reader, ZlibReaders_Reader, 0);
/* BEGIN */
  __ENDMOD;
}
