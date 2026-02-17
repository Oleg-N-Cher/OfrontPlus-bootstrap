/* Ofront+ 1.0 -s2 -48 */
#include "SYSTEM.oh"
#include "Files.oh"
#include "Platform.oh"
#include "Zlib.oh"
#include "ZlibReaders.oh"
#include "ZlibWriters.oh"

typedef
  struct Zip_ArchiveDesc *Zip_Archive;

typedef
  struct Zip_EntryDesc *Zip_Entry;

typedef
  struct Zip_ArchiveDesc {
    SHORTINT nofEntries;
    struct CHAR8_ARRAY *comment;
    Files_File file;
    INTEGER offset;
    Zip_Entry firstEntry, lastEntry;
  } Zip_ArchiveDesc;

typedef
  struct Zip_DefReaderDesc *Zip_DefReader;

typedef
  struct Zip_ReaderDesc {
    INTEGER res;
    BOOLEAN open;
    Zip_Entry ent;
  } Zip_ReaderDesc;

typedef
  struct Zip_DefReaderDesc { /* Zip_ReaderDesc */
    INTEGER res;
    BOOLEAN open;
    Zip_Entry ent;
    ZlibReaders_Reader zr;
  } Zip_DefReaderDesc;

typedef
  struct Zip_EntryDesc {
    CHAR name[256];
    SHORTINT method;
    INTEGER time, date, crc32, compSize, uncompSize;
    SHORTINT intFileAttr;
    INTEGER extFileAttr;
    struct CHAR8_ARRAY *extraField, *comment;
    SHORTINT genPurpBitFlag;
    BYTE support;
    BOOLEAN dataDescriptor;
    INTEGER offsetLocal, offsetFileData, offsetCentralDir;
    Zip_Entry next;
  } Zip_EntryDesc;

typedef
  Zip_ReaderDesc *Zip_Reader;

typedef
  struct Zip_UncompReaderDesc *Zip_UncompReader;

typedef
  struct Zip_UncompReaderDesc { /* Zip_ReaderDesc */
    INTEGER res;
    BOOLEAN open;
    Zip_Entry ent;
    Files_Rider fr;
    INTEGER crc32;
  } Zip_UncompReaderDesc;


#ifndef CHAR8_ARRAY_DEF
#define CHAR8_ARRAY_DEF
typedef struct CHAR8_ARRAY {
  INTEGER len[1];
  CHAR data[1];
} CHAR8_ARRAY;
#endif 


export void **Zip_EntryDesc__typ;
export void **Zip_ArchiveDesc__typ;
export void **Zip_ReaderDesc__typ;
export void **Zip_UncompReaderDesc__typ;
export void **Zip_DefReaderDesc__typ;

export void Zip_AddEntry (Zip_Archive arc, CHAR *name, INTEGER name__len, Files_Rider *src, void **src__typ, INTEGER len, BYTE level, BYTE strategy, INTEGER *res);
export void Zip_Close (Zip_Reader r);
static void Zip_Copy (Files_Rider *src, void **src__typ, Files_Rider *dst, void **dst__typ, INTEGER len, BOOLEAN compCRC32, INTEGER *crc32);
export Zip_Archive Zip_CreateArchive (CHAR *name, INTEGER name__len, INTEGER *res);
export void Zip_DeleteEntry (Zip_Archive arc, Zip_Entry *ent, INTEGER *res);
static INTEGER Zip_DosToOberonDate (SHORTINT d);
static INTEGER Zip_DosToOberonTime (SHORTINT t);
export void Zip_ExtractEntry (Zip_Archive arc, Zip_Entry ent, Files_Rider *dst, void **dst__typ, INTEGER *res);
export Zip_Entry Zip_FirstEntry (Zip_Archive arc);
export Zip_Entry Zip_GetEntry (Zip_Archive arc, CHAR *name, INTEGER name__len, INTEGER *res);
export Zip_Entry Zip_NextEntry (Zip_Entry ent);
static SHORTINT Zip_OberonToDosDate (INTEGER d);
static SHORTINT Zip_OberonToDosTime (INTEGER t);
export Zip_Archive Zip_OpenArchive (CHAR *name, INTEGER name__len, INTEGER *res);
export Zip_Reader Zip_OpenReader (Zip_Archive arc, Zip_Entry ent);
export void Zip_Read (Zip_Reader r, CHAR *ch);
export void Zip_ReadBytes (Zip_Reader r, CHAR *buf, INTEGER buf__len, INTEGER offset, INTEGER len, INTEGER *read);
static Zip_Entry Zip_ReadEntry (Files_Rider *r, void **r__typ);
static INTEGER Zip_StringLength (CHAR *str, INTEGER str__len);
static void Zip_WriteCentralDirectory (Zip_Archive arc, Files_Rider *r, void **r__typ);
static void Zip_WriteEndOfCentDir (Zip_Archive arc, Files_Rider *r, void **r__typ);
static void Zip_WriteFileHeader (Zip_Entry ent, Files_Rider *r, void **r__typ);
static void Zip_WriteLocalFileHeader (Zip_Entry ent, Files_Rider *r, void **r__typ);


/*============================================================================*/

static INTEGER Zip_StringLength (CHAR *str, INTEGER str__len)
{
  INTEGER i, l;
  l = str__len;
  i = 0;
  while (i < l && str[__X(i, str__len, (CHAR*)"Zip", 26142)] != 0x00) {
    i += 1;
  }
  return i;
}

static SHORTINT Zip_OberonToDosTime (INTEGER t)
{
  return (SHORTINT)((__ASHL(__MASK(__ASHR(t, 12, INTEGER), -32), 11, INTEGER) + __ASHL(__MASK(__ASHR(t, 6, INTEGER), -64), 5, INTEGER)) + __ASHR(__MASK(t, -64), 1, INTEGER));
}

static SHORTINT Zip_OberonToDosDate (INTEGER d)
{
  return (SHORTINT)(__ASHL((__ASHR(d, 9, INTEGER) + 1900) - 1980, 9, INTEGER) + __MASK(d, -512));
}

static INTEGER Zip_DosToOberonTime (SHORTINT t)
{
  return (__ASHL(__MASK(__ASHR((INTEGER)t, 11, INTEGER), -32), 12, INTEGER) + (INTEGER)__ASHL(__MASK(__ASHR(t, 5, SHORTINT), -64), 6, SHORTINT)) + (INTEGER)__ASHL(__MASK(t, -32), 1, SHORTINT);
}

static INTEGER Zip_DosToOberonDate (SHORTINT d)
{
  return __ASHL((__MASK(__ASHR((INTEGER)d, 9, INTEGER), -128) + 1980) - 1900, 9, INTEGER) + (INTEGER)__MASK(d, -512);
}

static void Zip_Copy (Files_Rider *src, void **src__typ, Files_Rider *dst, void **dst__typ, INTEGER len, BOOLEAN compCRC32, INTEGER *crc32)
{
  INTEGER n;
  CHAR buf[16384];
  if (compCRC32) {
    *crc32 = Zlib_CRC32(0, (void*)buf, 16384, -1, -1);
  }
  do {
    if (len < 16384) {
      n = len;
    } else {
      n = 16384;
    }
    Files_ReadBytes(src, src__typ, (void*)(SYSTEM_ADRINT)buf, 16384, n);
    if (compCRC32) {
      *crc32 = Zlib_CRC32(*crc32, (void*)buf, 16384, 0, n - (*src).res);
    }
    Files_WriteBytes(dst, dst__typ, (void*)(SYSTEM_ADRINT)buf, 16384, n - (*src).res);
    len -= n;
  } while (!(len == 0));
}

static Zip_Entry Zip_ReadEntry (Files_Rider *r, void **r__typ)
{
  Zip_Entry ent = NIL;
  SHORTINT intDummy, nameLen, extraLen, commentLen;
  INTEGER longDummy;
  CHAR bufDummy[256];
  Files_ReadInt(r, r__typ, &longDummy);
  if (longDummy == 33639248) {
    __NEW(ent, Zip_EntryDesc);
    ent->offsetCentralDir = (INTEGER)Files_Pos(r, r__typ) - 4;
    ent->support = 0;
    Files_ReadSInt(r, r__typ, &intDummy);
    Files_ReadSInt(r, r__typ, &intDummy);
    if ((SHORTREAL)__MASK(intDummy, -256) / (SHORTREAL)(SHORTREAL)10 < (SHORTREAL)1) {
      ent->support = 1;
    }
    Files_ReadSInt(r, r__typ, &ent->genPurpBitFlag);
    if (__ODD(ent->genPurpBitFlag)) {
      ent->support = 2;
    }
    ent->dataDescriptor = __ODD(__ASHR(intDummy, 3, SHORTINT));
    Files_ReadSInt(r, r__typ, &ent->method);
    if (ent->support == 0 && !__IN(ent->method, 0x0101)) {
      ent->support = 3;
    }
    Files_ReadSInt(r, r__typ, &intDummy);
    ent->time = Zip_DosToOberonTime(intDummy);
    Files_ReadSInt(r, r__typ, &intDummy);
    ent->date = Zip_DosToOberonDate(intDummy);
    Files_ReadInt(r, r__typ, &ent->crc32);
    Files_ReadInt(r, r__typ, &ent->compSize);
    Files_ReadInt(r, r__typ, &ent->uncompSize);
    Files_ReadSInt(r, r__typ, &nameLen);
    Files_ReadSInt(r, r__typ, &extraLen);
    Files_ReadSInt(r, r__typ, &commentLen);
    Files_ReadSInt(r, r__typ, &intDummy);
    Files_ReadSInt(r, r__typ, &ent->intFileAttr);
    Files_ReadInt(r, r__typ, &ent->extFileAttr);
    Files_ReadInt(r, r__typ, &ent->offsetLocal);
    Files_ReadBytes(r, r__typ, (void*)(SYSTEM_ADRINT)ent->name, 256, nameLen);
    if (extraLen != 0) {
      ent->extraField = __NEWARR(NIL, 1, 1, 1, 1, (SYSTEM_ARRLEN)extraLen);
      Files_ReadBytes(r, r__typ, (void*)(SYSTEM_ADRINT)ent->extraField->data, ent->extraField->len[0], extraLen);
    }
    if (commentLen > 0) {
      ent->comment = __NEWARR(NIL, 1, 1, 1, 1, (SYSTEM_ARRLEN)commentLen);
      Files_ReadBytes(r, r__typ, (void*)(SYSTEM_ADRINT)ent->comment->data, ent->comment->len[0], commentLen);
    }
    longDummy = (INTEGER)Files_Pos(r, r__typ);
    Files_Set(r, r__typ, Files_Base(r, r__typ), ent->offsetLocal + 28);
    Files_ReadSInt(r, r__typ, &extraLen);
    ent->offsetFileData = ((ent->offsetLocal + 30) + (INTEGER)nameLen) + (INTEGER)extraLen;
    Files_Set(r, r__typ, Files_Base(r, r__typ), longDummy);
    if ((*r).eof) {
      ent = NIL;
    }
  }
  return ent;
}

static void Zip_WriteLocalFileHeader (Zip_Entry ent, Files_Rider *r, void **r__typ)
{
  Files_WriteLInt(r, r__typ, 67324752);
  Files_WriteInt(r, r__typ, 10);
  Files_WriteInt(r, r__typ, ent->genPurpBitFlag);
  Files_WriteInt(r, r__typ, ent->method);
  Files_WriteInt(r, r__typ, Zip_OberonToDosTime(ent->time));
  Files_WriteInt(r, r__typ, Zip_OberonToDosDate(ent->date));
  Files_WriteLInt(r, r__typ, ent->crc32);
  Files_WriteLInt(r, r__typ, ent->compSize);
  Files_WriteLInt(r, r__typ, ent->uncompSize);
  Files_WriteInt(r, r__typ, (SHORTINT)Zip_StringLength((void*)ent->name, 256));
  if (ent->extraField != NIL) {
    Files_WriteInt(r, r__typ, (SHORTINT)ent->extraField->len[0]);
  } else {
    Files_WriteInt(r, r__typ, 0);
  }
  Files_WriteBytes(r, r__typ, (void*)(SYSTEM_ADRINT)ent->name, 256, Zip_StringLength((void*)ent->name, 256));
  if (ent->extraField != NIL) {
    Files_WriteBytes(r, r__typ, (void*)(SYSTEM_ADRINT)ent->extraField->data, ent->extraField->len[0], ent->extraField->len[0]);
  }
}

static void Zip_WriteFileHeader (Zip_Entry ent, Files_Rider *r, void **r__typ)
{
  ent->offsetCentralDir = (INTEGER)Files_Pos(r, r__typ);
  Files_WriteLInt(r, r__typ, 33639248);
  Files_WriteInt(r, r__typ, 10);
  Files_WriteInt(r, r__typ, 10);
  Files_WriteInt(r, r__typ, ent->genPurpBitFlag);
  Files_WriteInt(r, r__typ, ent->method);
  Files_WriteInt(r, r__typ, Zip_OberonToDosTime(ent->time));
  Files_WriteInt(r, r__typ, Zip_OberonToDosDate(ent->date));
  Files_WriteLInt(r, r__typ, ent->crc32);
  Files_WriteLInt(r, r__typ, ent->compSize);
  Files_WriteLInt(r, r__typ, ent->uncompSize);
  Files_WriteInt(r, r__typ, (SHORTINT)Zip_StringLength((void*)ent->name, 256));
  if (ent->extraField == NIL) {
    Files_WriteInt(r, r__typ, 0);
  } else {
    Files_WriteInt(r, r__typ, (SHORTINT)ent->extraField->len[0]);
  }
  if (ent->comment == NIL) {
    Files_WriteInt(r, r__typ, 0);
  } else {
    Files_WriteInt(r, r__typ, (SHORTINT)ent->comment->len[0]);
  }
  Files_WriteInt(r, r__typ, 0);
  Files_WriteInt(r, r__typ, ent->intFileAttr);
  Files_WriteLInt(r, r__typ, ent->extFileAttr);
  Files_WriteLInt(r, r__typ, ent->offsetLocal);
  Files_WriteBytes(r, r__typ, (void*)(SYSTEM_ADRINT)ent->name, 256, Zip_StringLength((void*)ent->name, 256));
  if (ent->extraField != NIL) {
    Files_WriteBytes(r, r__typ, (void*)(SYSTEM_ADRINT)ent->extraField->data, ent->extraField->len[0], ent->extraField->len[0]);
  }
  if (ent->comment != NIL) {
    Files_WriteBytes(r, r__typ, (void*)(SYSTEM_ADRINT)ent->comment->data, ent->comment->len[0], ent->comment->len[0]);
  }
}

static void Zip_WriteEndOfCentDir (Zip_Archive arc, Files_Rider *r, void **r__typ)
{
  INTEGER size;
  Files_WriteLInt(r, r__typ, 101010256);
  Files_WriteInt(r, r__typ, 0);
  Files_WriteInt(r, r__typ, 0);
  Files_WriteInt(r, r__typ, arc->nofEntries);
  Files_WriteInt(r, r__typ, arc->nofEntries);
  if (arc->firstEntry != NIL) {
    Files_WriteLInt(r, r__typ, arc->offset - arc->firstEntry->offsetCentralDir);
  } else {
    Files_WriteLInt(r, r__typ, 0);
  }
  if (arc->firstEntry == NIL) {
    Files_WriteLInt(r, r__typ, arc->offset);
  } else {
    Files_WriteLInt(r, r__typ, arc->firstEntry->offsetCentralDir);
  }
  if (arc->comment == NIL) {
    Files_WriteInt(r, r__typ, 0);
  } else {
    Files_WriteInt(r, r__typ, (SHORTINT)arc->comment->len[0]);
    Files_WriteBytes(r, r__typ, (void*)(SYSTEM_ADRINT)arc->comment->data, arc->comment->len[0], arc->comment->len[0]);
  }
}

static void Zip_WriteCentralDirectory (Zip_Archive arc, Files_Rider *r, void **r__typ)
{
  Zip_Entry ent = NIL;
  ent = arc->firstEntry;
  while (ent != NIL) {
    Zip_WriteFileHeader(ent, r, r__typ);
    ent = ent->next;
  }
  arc->offset = (INTEGER)Files_Pos(r, r__typ);
  Zip_WriteEndOfCentDir(arc, r, r__typ);
}

Zip_Archive Zip_OpenArchive (CHAR *name, INTEGER name__len, INTEGER *res)
{
  Zip_Archive arc = NIL;
  Zip_Entry ent = NIL;
  Files_File f = NIL;
  Files_Rider r = {0};
  INTEGER longDummy;
  SHORTINT intDummy;
  __DUP(name, name__len);
  *res = 0;
  f = Files_Old((void*)name, name__len);
  if (f == NIL) {
    *res = -1;
  } else if (Files_Length(f) < 22) {
    *res = -2;
  } else {
    longDummy = 0;
    Files_Set(&r, Files_Rider__typ, f, Files_Length(f) - 17);
    while (longDummy != 101010256 && Files_Pos(&r, Files_Rider__typ) > 4) {
      Files_Set(&r, Files_Rider__typ, f, Files_Pos(&r, Files_Rider__typ) - 5);
      Files_ReadInt(&r, Files_Rider__typ, &longDummy);
    }
    if (longDummy != 101010256) {
      *res = -2;
    } else {
      __NEW(arc, Zip_ArchiveDesc);
      arc->file = f;
      arc->offset = (INTEGER)Files_Pos(&r, Files_Rider__typ) - 4;
      Files_ReadSInt(&r, Files_Rider__typ, &intDummy);
      Files_ReadSInt(&r, Files_Rider__typ, &intDummy);
      Files_ReadSInt(&r, Files_Rider__typ, &intDummy);
      Files_ReadSInt(&r, Files_Rider__typ, &arc->nofEntries);
      Files_ReadInt(&r, Files_Rider__typ, &longDummy);
      Files_ReadInt(&r, Files_Rider__typ, &longDummy);
      Files_ReadSInt(&r, Files_Rider__typ, &intDummy);
      if (intDummy != 0) {
        arc->comment = __NEWARR(NIL, 1, 1, 1, 1, (SYSTEM_ARRLEN)intDummy);
        Files_ReadBytes(&r, Files_Rider__typ, (void*)(SYSTEM_ADRINT)arc->comment->data, arc->comment->len[0], intDummy);
      }
      if (Files_Pos(&r, Files_Rider__typ) != Files_Length(f)) {
        *res = -2;
        arc = NIL;
      } else {
        Files_Set(&r, Files_Rider__typ, f, longDummy);
        arc->firstEntry = Zip_ReadEntry(&r, Files_Rider__typ);
        arc->lastEntry = arc->firstEntry;
        ent = arc->firstEntry;
        intDummy = 0;
        while (ent != NIL) {
          arc->lastEntry = ent;
          intDummy += 1;
          ent->next = Zip_ReadEntry(&r, Files_Rider__typ);
          ent = ent->next;
        }
        if (intDummy != arc->nofEntries) {
          *res = -2;
          arc = NIL;
        }
      }
      Files_Close(f);
    }
  }
  return arc;
}

/*----------------------------------------------------------------------------*/
Zip_Archive Zip_CreateArchive (CHAR *name, INTEGER name__len, INTEGER *res)
{
  Files_File f = NIL;
  Files_Rider r = {0};
  Zip_Archive arc = NIL;
  f = Files_Old((void*)name, name__len);
  if (f != NIL) {
    return Zip_OpenArchive(name, name__len, res);
  } else {
    f = Files_New((void*)name, name__len);
    __NEW(arc, Zip_ArchiveDesc);
    arc->file = f;
    arc->nofEntries = 0;
    arc->offset = 0;
    Files_Set(&r, Files_Rider__typ, f, 0);
    Zip_WriteEndOfCentDir(arc, &r, Files_Rider__typ);
    Files_Register(f);
    *res = 0;
    return arc;
  }
  __RETCHK((CHAR*)"Zip", 104191);
}

/*----------------------------------------------------------------------------*/
Zip_Entry Zip_FirstEntry (Zip_Archive arc)
{
  if (arc == NIL) {
    return NIL;
  } else {
    return arc->firstEntry;
  }
  __RETCHK((CHAR*)"Zip", 106751);
}

/*----------------------------------------------------------------------------*/
Zip_Entry Zip_NextEntry (Zip_Entry ent)
{
  return ent->next;
}

/*----------------------------------------------------------------------------*/
Zip_Entry Zip_GetEntry (Zip_Archive arc, CHAR *name, INTEGER name__len, INTEGER *res)
{
  Zip_Entry ent = NIL;
  if (arc == NIL) {
    *res = -2;
  } else {
    ent = arc->firstEntry;
    while (ent != NIL && __STRCMPCC(ent->name, name, name__len, (CHAR*)"Zip", 112423) != 0) {
      ent = ent->next;
    }
    if (ent == NIL) {
      *res = -3;
    } else {
      *res = 0;
    }
  }
  return ent;
}

/*----------------------------------------------------------------------------*/
void Zip_ExtractEntry (Zip_Archive arc, Zip_Entry ent, Files_Rider *dst, void **dst__typ, INTEGER *res)
{
  Files_Rider src = {0};
  INTEGER crc32;
  if (arc == NIL) {
    *res = -2;
  } else if (Files_Base(dst, dst__typ) == NIL) {
    *res = -7;
  } else if (ent == NIL || ent != Zip_GetEntry(arc, (void*)ent->name, 256, res)) {
    *res = -3;
  } else if (!__IN(ent->method, 0x0101) || ent->support > 0) {
    *res = -5;
  } else {
    switch (ent->method) {
      case 0: 
        Files_Set(&src, Files_Rider__typ, arc->file, ent->offsetFileData);
        Zip_Copy(&src, Files_Rider__typ, dst, dst__typ, ent->uncompSize, 1, &crc32);
        if (crc32 == ent->crc32) {
          *res = 0;
        } else {
          *res = -6;
        }
        break;
      case 8: 
        Files_Set(&src, Files_Rider__typ, arc->file, ent->offsetFileData);
        ZlibReaders_Uncompress(&src, Files_Rider__typ, dst, dst__typ, &crc32, res);
        if (*res == 0 && crc32 == ent->crc32) {
          *res = 0;
        } else {
          *res = -6;
        }
        break;
      default: __CASECHK((CHAR*)"Zip", 124927);
    }
    if (*res == 0) {
      Files_Close(Files_Base(dst, dst__typ));
    }
  }
}

/*----------------------------------------------------------------------------*/
void Zip_AddEntry (Zip_Archive arc, CHAR *name, INTEGER name__len, Files_Rider *src, void **src__typ, INTEGER len, BYTE level, BYTE strategy, INTEGER *res)
{
  Files_Rider dst = {0};
  Zip_Entry ent = NIL;
  INTEGER start;
  if (arc == NIL) {
    *res = -2;
  } else if (Files_Base(src, src__typ) == NIL) {
    *res = -7;
  } else if (Zip_GetEntry(arc, (void*)name, name__len, res) != NIL && *res == 0) {
    *res = -4;
  } else {
    __NEW(ent, Zip_EntryDesc);
    __COPY(name, ent->name, __MIN(256, name__len));
    ent->genPurpBitFlag = 0;
    if (level == 0) {
      ent->method = 0;
    } else {
      ent->method = 8;
    }
    Files_GetDate(Files_Base(src, src__typ), &ent->time, &ent->date);
    ent->uncompSize = len;
    ent->intFileAttr = 0;
    ent->extFileAttr = 0;
    ent->comment = NIL;
    ent->support = 0;
    ent->dataDescriptor = 0;
    if (arc->firstEntry != NIL) {
      ent->offsetLocal = arc->firstEntry->offsetCentralDir;
    } else {
      ent->offsetLocal = 0;
    }
    Files_Set(&dst, Files_Rider__typ, arc->file, ent->offsetLocal);
    Zip_WriteLocalFileHeader(ent, &dst, Files_Rider__typ);
    ent->offsetFileData = (INTEGER)Files_Pos(&dst, Files_Rider__typ);
    Files_Close(arc->file);
    start = (INTEGER)Files_Pos(src, src__typ);
    if (level == 0) {
      Zip_Copy(src, src__typ, &dst, Files_Rider__typ, len, 1, &ent->crc32);
      ent->compSize = len;
      *res = 0;
    } else {
      ZlibWriters_Compress(src, src__typ, &dst, Files_Rider__typ, len, &ent->compSize, level, strategy, &ent->crc32, res);
      if (*res != 0) {
        *res = -6;
      } else {
        *res = 0;
      }
    }
    if (*res == 0) {
      ent->uncompSize = (INTEGER)Files_Pos(src, src__typ) - start;
      Files_Close(arc->file);
      Files_Set(&dst, Files_Rider__typ, arc->file, ent->offsetLocal + 14);
      Files_WriteLInt(&dst, Files_Rider__typ, ent->crc32);
      Files_WriteLInt(&dst, Files_Rider__typ, ent->compSize);
      Files_Close(arc->file);
      if (arc->lastEntry != NIL) {
        arc->lastEntry->next = ent;
      } else {
        arc->firstEntry = ent;
      }
      arc->lastEntry = ent;
      arc->nofEntries += 1;
      Files_Set(&dst, Files_Rider__typ, arc->file, ent->offsetFileData + ent->compSize);
      Zip_WriteCentralDirectory(arc, &dst, Files_Rider__typ);
      Files_Close(arc->file);
      *res = 0;
    }
  }
}

/*----------------------------------------------------------------------------*/
void Zip_DeleteEntry (Zip_Archive arc, Zip_Entry *ent, INTEGER *res)
{
  Files_File f = NIL;
  Files_Rider r1 = {0}, r2 = {0};
  Zip_Entry ent2 = NIL;
  CHAR arcname[256];
  CHAR buf[16384];
  INTEGER offset, diff;
  if (arc == NIL) {
    *res = -2;
  } else if (arc->firstEntry == NIL) {
    *res = -3;
  } else if (arc->firstEntry == *ent) {
    offset = arc->firstEntry->offsetLocal;
    if (arc->lastEntry == arc->firstEntry) {
      arc->lastEntry = arc->firstEntry->next;
    }
    arc->firstEntry = arc->firstEntry->next;
    ent2 = arc->firstEntry;
    *res = 0;
  } else {
    ent2 = arc->firstEntry;
    while (ent2->next != NIL && ent2->next != *ent) {
      ent2 = ent2->next;
    }
    if (ent2->next == NIL) {
      *res = -3;
    } else {
      if (arc->lastEntry == ent2->next) {
        arc->lastEntry = ent2;
      }
      offset = ent2->next->offsetLocal;
      ent2->next = ent2->next->next;
      ent2 = ent2->next;
      *res = 0;
    }
  }
  if (*res == 0) {
    Files_GetName(arc->file, (void*)arcname, 256);
    f = Files_New((void*)arcname, 256);
    Files_Set(&r2, Files_Rider__typ, f, 0);
    Files_Set(&r1, Files_Rider__typ, arc->file, 0);
    Zip_Copy(&r1, Files_Rider__typ, &r2, Files_Rider__typ, offset, 0, &diff);
    Files_Close(f);
    __ASSERT(ent2 == (*ent)->next, 0, (CHAR*)"Zip", 160025);
    if (ent2 != NIL) {
      Files_Set(&r1, Files_Rider__typ, arc->file, ent2->offsetLocal);
      Zip_Copy(&r1, Files_Rider__typ, &r2, Files_Rider__typ, arc->firstEntry->offsetCentralDir - ent2->offsetLocal, 0, &diff);
      Files_Close(f);
      diff = ent2->offsetLocal - offset;
    } else {
      diff = arc->offset - offset;
    }
    while (ent2 != NIL) {
      ent2->offsetLocal -= diff;
      ent2->offsetFileData -= diff;
      ent2->offsetCentralDir -= diff;
      ent2 = ent2->next;
    }
    arc->offset -= diff;
    arc->nofEntries -= 1;
    Zip_WriteCentralDirectory(arc, &r2, Files_Rider__typ);
    Files_Register(f);
    arc->file = f;
    *ent = NIL;
  }
}

/*----------------------------------------------------------------------------*/
Zip_Reader Zip_OpenReader (Zip_Archive arc, Zip_Entry ent)
{
  CHAR dummyBuf[1];
  Files_Rider fr = {0};
  Zip_Reader r = NIL;
  Zip_UncompReader ur = NIL;
  Zip_DefReader dr = NIL;
  if (ent->support == 0) {
    if (ent->method == 0) {
      __NEW(ur, Zip_UncompReaderDesc);
      ur->crc32 = Zlib_CRC32(0, (void*)dummyBuf, 1, -1, -1);
      Files_Set(&ur->fr, Files_Rider__typ, arc->file, ent->offsetFileData);
      r = (Zip_Reader)ur;
      r->open = 1;
      r->res = 0;
    } else if (ent->method == 8) {
      Files_Set(&fr, Files_Rider__typ, arc->file, ent->offsetFileData);
      __NEW(dr, Zip_DefReaderDesc);
      ZlibReaders_Open(&dr->zr, ZlibReaders_Reader__typ, 0, &fr, Files_Rider__typ);
      dr->res = dr->zr.res;
      r = (Zip_Reader)dr;
      r->open = 1;
    } else {
      __NEW(r, Zip_ReaderDesc);
      r->open = 0;
      r->res = -5;
    }
  } else {
    __NEW(r, Zip_ReaderDesc);
    r->open = 0;
    r->res = -5;
  }
  r->ent = ent;
  return r;
}

/*----------------------------------------------------------------------------*/
void Zip_ReadBytes (Zip_Reader r, CHAR *buf, INTEGER buf__len, INTEGER offset, INTEGER len, INTEGER *read)
{
  struct CHAR8_ARRAY *bufp = NIL;
  INTEGER i, _for__18;
  if (r->open) {
    if (__ISP(r, Zip_UncompReaderDesc, 1)) {
      if (offset == 0) {
        Files_ReadBytes(&(__GUARDP(r, Zip_UncompReaderDesc, 1))->fr, Files_Rider__typ, (void*)(SYSTEM_ADRINT)buf, buf__len, len);
      } else {
        bufp = __NEWARR(NIL, 1, 1, 1, 1, (SYSTEM_ARRLEN)len);
        Files_ReadBytes(&(__GUARDP(r, Zip_UncompReaderDesc, 1))->fr, Files_Rider__typ, (void*)(SYSTEM_ADRINT)bufp->data, bufp->len[0], len);
        _for__18 = len - 1;
        i = 0;
        while (i <= _for__18) {
          buf[__X(offset + i, buf__len, (CHAR*)"Zip", 178431)] = (bufp->data)[__X(i, bufp->len[0], (CHAR*)"Zip", 178431)];
          i += 1;
        }
      }
      *read = len - (__GUARDP(r, Zip_UncompReaderDesc, 1))->fr.res;
      (__GUARDP(r, Zip_UncompReaderDesc, 1))->crc32 = Zlib_CRC32((__GUARDP(r, Zip_UncompReaderDesc, 1))->crc32, (void*)buf, buf__len, offset, *read);
    } else if (__ISP(r, Zip_DefReaderDesc, 1)) {
      ZlibReaders_ReadBytes(&(__GUARDP(r, Zip_DefReaderDesc, 1))->zr, ZlibReaders_Reader__typ, (void*)buf, buf__len, offset, len, read);
      r->res = (__GUARDP(r, Zip_DefReaderDesc, 1))->zr.res;
    }
  } else {
    r->res = -8;
  }
}

/*----------------------------------------------------------------------------*/
void Zip_Read (Zip_Reader r, CHAR *ch)
{
  CHAR buf[1];
  INTEGER read;
  Zip_ReadBytes(r, (void*)buf, 1, 0, 1, &read);
  *ch = buf[0];
}

/*----------------------------------------------------------------------------*/
void Zip_Close (Zip_Reader r)
{
  if (r->open) {
    if (__ISP(r, Zip_UncompReaderDesc, 1)) {
      if ((__GUARDP(r, Zip_UncompReaderDesc, 1))->crc32 != r->ent->crc32) {
        r->res = -6;
      } else {
        r->res = 0;
      }
    } else if (__ISP(r, Zip_DefReaderDesc, 1)) {
      ZlibReaders_Close(&(__GUARDP(r, Zip_DefReaderDesc, 1))->zr, ZlibReaders_Reader__typ);
      if ((__GUARDP(r, Zip_DefReaderDesc, 1))->zr.crc32 != r->ent->crc32) {
        r->res = -6;
      } else {
        r->res = (__GUARDP(r, Zip_DefReaderDesc, 1))->zr.res;
      }
    } else {
      r->res = -8;
    }
    r->open = 0;
  } else {
    r->res = -8;
  }
}

/*----------------------------------------------------------------------------*/
__TDESC(Zip_EntryDesc__desc, 2, 3) = {__TDFLDS("EntryDesc", 316), {288, 292, 312, -16}};
__TDESC(Zip_ArchiveDesc__desc, 2, 4) = {__TDFLDS("ArchiveDesc", 24), {4, 8, 16, 20, -20}};
__TDESC(Zip_ReaderDesc__desc, 2, 1) = {__TDFLDS("ReaderDesc", 12), {8, -8}};
__TDESC(Zip_UncompReaderDesc__desc, 2, 2) = {__TDFLDS("UncompReaderDesc", 56), {8, 24, -12}};
__TDESC(Zip_DefReaderDesc__desc, 2, 10) = {__TDFLDS("DefReaderDesc", 576), {8, 40, 64, 120, 128, 508, 512, 528, 540, 552, -44}};

export void *Zip__init (void)
{
  __DEFMOD;
  __IMPORT(Files__init);
  __IMPORT(Zlib__init);
  __IMPORT(ZlibReaders__init);
  __IMPORT(ZlibWriters__init);
  __REGMOD("Zip", 0);
  __INITYP(Zip_EntryDesc, Zip_EntryDesc, 0);
  __INITYP(Zip_ArchiveDesc, Zip_ArchiveDesc, 0);
  __INITYP(Zip_ReaderDesc, Zip_ReaderDesc, 0);
  __INITYP(Zip_UncompReaderDesc, Zip_ReaderDesc, 1);
  __INITYP(Zip_DefReaderDesc, Zip_ReaderDesc, 1);
/* BEGIN */
  __ENDMOD;
}
