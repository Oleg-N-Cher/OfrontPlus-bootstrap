/* Ofront+ 1.0 -sC -44 */
#include "SYSTEM.oh"
#include "Platform.oh"
#include "Heap.oh"
#include "Strings.oh"
#include "CmdArgs.oh"
#include "Console.oh"

typedef
  struct Files_FileDesc *Files_File;

typedef
  struct Files_BufDesc {
    Files_File f;
    BOOLEAN chg;
    LONGINT org;
    INTEGER size;
    BYTE data[4096];
  } Files_BufDesc;

typedef
  Files_BufDesc *Files_Buffer;

typedef
  CHAR Files_FileName[256];

typedef
  struct Files_FileDesc {
    Files_FileName workName, registerName;
    BOOLEAN tempFile;
    Platform_FileIdentity identity;
    INTEGER fd;
    LONGINT len, pos;
    Files_Buffer bufs[4];
    SHORTINT swapper, state;
    struct Files_FileDesc *next;
  } Files_FileDesc;

typedef
  struct Files_Rider {
    INTEGER res;
    BOOLEAN eof;
    Files_Buffer buf;
    LONGINT org;
    INTEGER offset;
  } Files_Rider;


#ifndef CHAR8_ARRAY_DEF
#define CHAR8_ARRAY_DEF
typedef struct CHAR8_ARRAY {
  INTEGER len[1];
  CHAR data[1];
} CHAR8_ARRAY;
#endif 

static Files_FileDesc *Files_files;
static INTEGER Files_tempno;
static CHAR Files_HOME[1024];
static struct CHAR8_ARRAY *Files_SearchPath;

export void **Files_FileDesc__typ;
export void **Files_BufDesc__typ;
export void **Files_Rider__typ;

export Files_File Files_Base (Files_Rider *r, void **r__typ);
static Files_File Files_CacheEntry (Platform_FileIdentity identity);
export void Files_ChangeDirectory (CHAR *path, INTEGER path__len, INTEGER *res);
export void Files_Close (Files_File f);
static void Files_CloseOSFile (Files_File f);
static void Files_Create (Files_File f);
export void Files_Delete (CHAR *name, INTEGER name__len, INTEGER *res);
static void Files_Deregister (CHAR *name, INTEGER name__len);
static void Files_Err (CHAR *s, INTEGER s__len, Files_File f, INTEGER errcode);
static void Files_Finalize (SYSTEM_PTR o);
static void Files_FlipBytes (BYTE *src, INTEGER src__len, BYTE *dest, INTEGER dest__len);
static void Files_Flush (Files_Buffer buf);
export void Files_GetDate (Files_File f, INTEGER *t, INTEGER *d);
export void Files_GetName (Files_File f, CHAR *name, INTEGER name__len);
static void Files_GetTempName (CHAR *name, INTEGER name__len);
static BOOLEAN Files_HasDir (CHAR *name, INTEGER name__len);
export LONGINT Files_Length (Files_File f);
static void Files_MakeFileName (CHAR *dir, INTEGER dir__len, CHAR *name, INTEGER name__len, CHAR *dest, INTEGER dest__len);
export Files_File Files_New (CHAR *name, INTEGER name__len);
export Files_File Files_Old (CHAR *name, INTEGER name__len);
export LONGINT Files_Pos (Files_Rider *r, void **r__typ);
export void Files_Purge (Files_File f);
export void Files_ReadBool (Files_Rider *R, void **R__typ, BOOLEAN *x);
export void Files_ReadByte (Files_Rider *r, void **r__typ, BYTE *x);
export void Files_ReadBytes (Files_Rider *r, void **r__typ, BYTE *x, INTEGER x__len, INTEGER n);
export void Files_ReadChar (Files_Rider *r, void **r__typ, CHAR *x);
export void Files_ReadInt (Files_Rider *R, void **R__typ, INTEGER *x);
export void Files_ReadLInt (Files_Rider *R, void **R__typ, LONGINT *x);
export void Files_ReadLReal (Files_Rider *R, void **R__typ, REAL *x);
export void Files_ReadLine (Files_Rider *R, void **R__typ, CHAR *x, INTEGER x__len);
export void Files_ReadNum (Files_Rider *R, void **R__typ, LONGINT *x);
export void Files_ReadReal (Files_Rider *R, void **R__typ, SHORTREAL *x);
export void Files_ReadSInt (Files_Rider *R, void **R__typ, SHORTINT *x);
export void Files_ReadSet (Files_Rider *R, void **R__typ, SET *x);
export void Files_ReadString (Files_Rider *R, void **R__typ, CHAR *x, INTEGER x__len);
export void Files_Register (Files_File f);
export void Files_Rename (CHAR *old, INTEGER old__len, CHAR *new, INTEGER new__len, INTEGER *res);
static void Files_ScanPath (INTEGER *pos, CHAR *dir, INTEGER dir__len);
export void Files_Set (Files_Rider *r, void **r__typ, Files_File f, LONGINT pos);
export void Files_SetSearchPath (CHAR *path, INTEGER path__len);
export void Files_WriteBool (Files_Rider *R, void **R__typ, BOOLEAN x);
export void Files_WriteByte (Files_Rider *r, void **r__typ, BYTE x);
export void Files_WriteBytes (Files_Rider *r, void **r__typ, BYTE *x, INTEGER x__len, INTEGER n);
export void Files_WriteChar (Files_Rider *R, void **R__typ, CHAR x);
export void Files_WriteInt (Files_Rider *R, void **R__typ, INTEGER x);
export void Files_WriteLInt (Files_Rider *R, void **R__typ, LONGINT x);
export void Files_WriteLReal (Files_Rider *R, void **R__typ, REAL x);
export void Files_WriteNum (Files_Rider *R, void **R__typ, LONGINT x);
export void Files_WriteReal (Files_Rider *R, void **R__typ, SHORTREAL x);
export void Files_WriteSInt (Files_Rider *R, void **R__typ, SHORTINT x);
export void Files_WriteSet (Files_Rider *R, void **R__typ, SET x);
export void Files_WriteString (Files_Rider *R, void **R__typ, CHAR *x, INTEGER x__len);

#define Files_IdxTrap(pos)  __HALT(-1, "Files.Mod", pos)

/*============================================================================*/

static void Files_Err (CHAR *s, INTEGER s__len, Files_File f, INTEGER errcode)
{
  Console_Ln();
  Console_String((CHAR*)"-- ", 4);
  Console_String((void*)s, s__len);
  Console_String((CHAR*)": ", 3);
  if (f != NIL) {
    if (f->registerName[0] != 0x00) {
      Console_String((void*)f->registerName, 256);
    } else {
      Console_String((void*)f->workName, 256);
    }
    if (f->fd != 0) {
      Console_String((CHAR*)" f.fd = ", 9);
      Console_LongInt(f->fd, 1);
    }
  }
  if (errcode != 0) {
    Console_String((CHAR*)" errcode = ", 12);
    Console_Int(errcode, 1);
  }
  Console_Ln();
  __HALT(99, (CHAR*)"Files", 22271);
}

static void Files_MakeFileName (CHAR *dir, INTEGER dir__len, CHAR *name, INTEGER name__len, CHAR *dest, INTEGER dest__len)
{
  INTEGER i, j;
  i = 0;
  j = 0;
  while (dir[__X(i, dir__len, (CHAR*)"Files", 23573)] != 0x00) {
    dest[__X(i, dest__len, (CHAR*)"Files", 23594)] = dir[__X(i, dir__len, (CHAR*)"Files", 23594)];
    i += 1;
  }
  if (dest[__X(i - 1, dest__len, (CHAR*)"Files", 23882)] != '/') {
    dest[__X(i, dest__len, (CHAR*)"Files", 23870)] = '/';
    i += 1;
  }
  while (name[__X(j, name__len, (CHAR*)"Files", 24086)] != 0x00) {
    dest[__X(i, dest__len, (CHAR*)"Files", 24108)] = name[__X(j, name__len, (CHAR*)"Files", 24108)];
    i += 1;
    j += 1;
  }
  dest[__X(i, dest__len, (CHAR*)"Files", 24575)] = 0x00;
}

static void Files_GetTempName (CHAR *name, INTEGER name__len)
{
  INTEGER n, i;
  Files_tempno += 1;
  Platform_GetTempPath((void*)name, name__len);
  i = 0;
  while (name[__X(i, name__len, (CHAR*)"Files", 26398)] != 0x00) {
    i += 1;
  }
  name[__X(i, name__len, (CHAR*)"Files", 26898)] = 'o';
  i += 1;
  name[__X(i, name__len, (CHAR*)"Files", 26922)] = 'b';
  i += 1;
  name[__X(i, name__len, (CHAR*)"Files", 26946)] = 'e';
  i += 1;
  name[__X(i, name__len, (CHAR*)"Files", 27154)] = 'r';
  i += 1;
  name[__X(i, name__len, (CHAR*)"Files", 27178)] = 'o';
  i += 1;
  name[__X(i, name__len, (CHAR*)"Files", 27202)] = 'n';
  i += 1;
  name[__X(i, name__len, (CHAR*)"Files", 27410)] = '.';
  i += 1;
  n = Files_tempno;
  do {
    name[__X(i, name__len, (CHAR*)"Files", 27701)] = (CHAR)(__MOD(n, 10) + 48);
    n = __DIV(n, 10);
    i += 1;
  } while (!(n == 0));
  name[__X(i, name__len, (CHAR*)"Files", 28178)] = '.';
  i += 1;
  n = Platform_PID;
  do {
    name[__X(i, name__len, (CHAR*)"Files", 28469)] = (CHAR)(__MOD(n, 10) + 48);
    n = __DIV(n, 10);
    i += 1;
  } while (!(n == 0));
  name[__X(i, name__len, (CHAR*)"Files", 28927)] = 0x00;
}

static void Files_Deregister (CHAR *name, INTEGER name__len)
{
  Platform_FileIdentity identity;
  Files_File osfile = NIL;
  INTEGER error;
  if (Platform_IdentifyByName((void*)name, name__len, &identity) == 0) {
    osfile = (Files_File)Files_files;
    while (osfile != NIL && !Platform_SameFile(osfile->identity, identity)) {
      osfile = (Files_File)osfile->next;
    }
    if (osfile != NIL) {
      __ASSERT(!osfile->tempFile, 0, (CHAR*)"Files", 34592);
      __ASSERT(osfile->fd >= 0, 0, (CHAR*)"Files", 34616);
      __MOVE(osfile->workName, osfile->registerName, 256);
      Files_GetTempName((void*)osfile->workName, 256);
      osfile->tempFile = 1;
      error = Platform_CloseFile(osfile->fd);
      osfile->state = 2;
      error = Platform_RenameFile((void*)name, name__len, (void*)osfile->workName, 256);
      if (error != 0) {
        Files_Err((CHAR*)"Couldn\'t rename previous version of file being registered", 58, osfile, error);
      }
    }
  }
}

static void Files_Create (Files_File f)
{
  BOOLEAN done;
  INTEGER error;
  CHAR err[32];
  if (f->fd == Platform_InvalidHandleValue()) {
    if ((INTEGER)f->state == 1) {
      Files_GetTempName((void*)f->workName, 256);
      f->tempFile = 1;
    } else {
      __ASSERT((INTEGER)f->state == 2, 0, (CHAR*)"Files", 41759);
      Files_Deregister((void*)f->registerName, 256);
      __MOVE(f->registerName, f->workName, 256);
      f->registerName[0] = 0x00;
      f->tempFile = 0;
    }
    error = Platform_DeleteFile((void*)f->workName, 256);
    error = Platform_NewFile((void*)f->workName, 256, &f->fd);
    done = error == 0;
    if (done) {
      f->next = Files_files;
      Files_files = f;
      Heap_FileCount += 1;
      Heap_RegisterFinalizer((void*)f, Files_Finalize);
      f->state = 0;
      f->pos = 0;
      error = Platform_Identify(f->fd, &f->identity);
    } else {
      if (Platform_NoSuchDirectory(error)) {
        __MOVE((CHAR*)"no such directory", err, 18);
      } else if (Platform_TooManyFiles(error)) {
        __MOVE((CHAR*)"too many files open", err, 20);
      } else {
        __MOVE((CHAR*)"file not created", err, 17);
      }
      Files_Err((void*)err, 32, f, error);
    }
  }
}

static void Files_Flush (Files_Buffer buf)
{
  INTEGER error;
  Files_File f = NIL;
  if (buf->chg) {
    f = buf->f;
    Files_Create(f);
    if (buf->org != f->pos) {
      error = Platform_Seek(f->fd, buf->org, Platform_SeekSet);
    }
    error = Platform_Write(f->fd, (SYSTEM_ADRINT)buf->data, buf->size);
    if (error != 0) {
      Files_Err((CHAR*)"error writing file", 19, f, error);
    }
    f->pos = buf->org + (LONGINT)buf->size;
    buf->chg = 0;
    error = Platform_Identify(f->fd, &f->identity);
    if (error != 0) {
      Files_Err((CHAR*)"error identifying file", 23, f, error);
    }
  }
}

static void Files_CloseOSFile (Files_File f)
{
  Files_File prev = NIL;
  INTEGER error;
  if (Files_files == (void *) f) {
    Files_files = f->next;
  } else {
    prev = (Files_File)Files_files;
    while (prev != NIL && prev->next != (void *) f) {
      prev = (Files_File)prev->next;
    }
    if (prev->next != NIL) {
      prev->next = f->next;
    }
  }
  error = Platform_CloseFile(f->fd);
  f->fd = Platform_InvalidHandleValue();
  f->state = 1;
  Heap_FileCount -= 1;
}

void Files_Close (Files_File f)
{
  INTEGER i;
  if ((INTEGER)f->state != 1 || f->registerName[0] != 0x00) {
    Files_Create(f);
    i = 0;
    while (i < 4 && f->bufs[__X(i, 4, (CHAR*)"Files", 58925)] != NIL) {
      Files_Flush(f->bufs[__X(i, 4, (CHAR*)"Files", 58945)]);
      i += 1;
    }
  }
}

/*----------------------------------------------------------------------------*/
LONGINT Files_Length (Files_File f)
{
  return f->len;
}

/*----------------------------------------------------------------------------*/
Files_File Files_New (CHAR *name, INTEGER name__len)
{
  Files_File f = NIL;
  __NEW(f, Files_FileDesc);
  f->workName[0] = 0x00;
  __STRCOPYCC(name, f->registerName, __MIN(256, name__len), (CHAR*)"Files", 61493);
  f->fd = Platform_InvalidHandleValue();
  f->state = 1;
  f->len = 0;
  f->pos = 0;
  f->swapper = -1;
  return f;
}

/*----------------------------------------------------------------------------*/
static void Files_ScanPath (INTEGER *pos, CHAR *dir, INTEGER dir__len)
{
  INTEGER i;
  CHAR ch;
  i = 0;
  if (Files_SearchPath == NIL) {
    if (*pos == 0) {
      dir[0] = '.';
      i = 1;
      *pos += 1;
    }
  } else {
    ch = (Files_SearchPath->data)[__X(*pos, Files_SearchPath->len[0], (CHAR*)"Files", 65819)];
    while (ch == ' ' || ch == ':') {
      *pos += 1;
      ch = (Files_SearchPath->data)[__X(*pos, Files_SearchPath->len[0], (CHAR*)"Files", 66129)];
    }
    if (ch == '~') {
      *pos += 1;
      ch = (Files_SearchPath->data)[__X(*pos, Files_SearchPath->len[0], (CHAR*)"Files", 66599)];
      while (Files_HOME[__X(i, 1024, (CHAR*)"Files", 66842)] != 0x00) {
        dir[__X(i, dir__len, (CHAR*)"Files", 66863)] = Files_HOME[__X(i, 1024, (CHAR*)"Files", 66863)];
        i += 1;
      }
      if (((ch != '/' && ch != 0x00) && ch != ':') && ch != ' ') {
        while (i > 0 && dir[__X(i - 1, dir__len, (CHAR*)"Files", 67380)] != '/') {
          i -= 1;
        }
      }
    }
    while (ch != 0x00 && ch != ':') {
      dir[__X(i, dir__len, (CHAR*)"Files", 68156)] = ch;
      i += 1;
      *pos += 1;
      ch = (Files_SearchPath->data)[__X(*pos, Files_SearchPath->len[0], (CHAR*)"Files", 68197)];
    }
    while (i > 0 && dir[__X(i - 1, dir__len, (CHAR*)"Files", 68390)] == ' ') {
      i -= 1;
    }
  }
  dir[__X(i, dir__len, (CHAR*)"Files", 69119)] = 0x00;
}

static BOOLEAN Files_HasDir (CHAR *name, INTEGER name__len)
{
  INTEGER i;
  CHAR ch;
  i = 0;
  ch = name[0];
  while (ch != 0x00 && ch != '/') {
    i += 1;
    ch = name[__X(i, name__len, (CHAR*)"Files", 70467)];
  }
  return ch == '/';
}

static Files_File Files_CacheEntry (Platform_FileIdentity identity)
{
  Files_File f = NIL;
  INTEGER i, error;
  f = (Files_File)Files_files;
  while (f != NIL) {
    if (Platform_SameFile(identity, f->identity)) {
      if (!Platform_SameFileTime(identity, f->identity)) {
        i = 0;
        while (i < 4) {
          if (f->bufs[__X(i, 4, (CHAR*)"Files", 73293)] != NIL) {
            f->bufs[__X(i, 4, (CHAR*)"Files", 73271)]->org = -1;
            f->bufs[__X(i, 4, (CHAR*)"Files", 73289)] = NIL;
          }
          i += 1;
        }
        f->swapper = -1;
        f->identity = identity;
        error = Platform_FileSize(f->fd, &f->len);
      }
      return f;
    }
    f = (Files_File)f->next;
  }
  return NIL;
}

Files_File Files_Old (CHAR *name, INTEGER name__len)
{
  Files_File f = NIL;
  INTEGER fd, pos;
  BOOLEAN done;
  CHAR dir[256], path[256];
  INTEGER error;
  Platform_FileIdentity identity;
  if (name[0] != 0x00) {
    if (Files_HasDir((void*)name, name__len)) {
      dir[0] = 0x00;
      __STRCOPYCC(name, path, __MIN(256, name__len), (CHAR*)"Files", 79871);
    } else {
      pos = 0;
      Files_ScanPath(&pos, (void*)dir, 256);
      Files_MakeFileName((void*)dir, 256, (void*)name, name__len, (void*)path, 256);
      Files_ScanPath(&pos, (void*)dir, 256);
    }
    for (;;) {
      error = Platform_OldRW((void*)path, 256, &fd);
      done = error == 0;
      if (!done && Platform_TooManyFiles(error)) {
        Files_Err((CHAR*)"too many files open", 20, f, error);
      }
      if (!done && Platform_Inaccessible(error)) {
        error = Platform_OldRO((void*)path, 256, &fd);
        done = error == 0;
      }
      if (!done && !Platform_Absent(error)) {
        Console_String((CHAR*)"Warning: Files.Old ", 20);
        Console_String((void*)name, name__len);
        Console_String((CHAR*)" error = ", 10);
        Console_Int(error, 0);
        Console_Ln();
      }
      if (done) {
        error = Platform_Identify(fd, &identity);
        f = Files_CacheEntry(identity);
        if (f != NIL) {
          error = Platform_CloseFile(fd);
          return f;
        } else {
          __NEW(f, Files_FileDesc);
          Heap_RegisterFinalizer((void*)f, Files_Finalize);
          f->fd = fd;
          f->state = 0;
          f->pos = 0;
          f->swapper = -1;
          error = Platform_FileSize(fd, &f->len);
          __STRCOPYCC(name, f->workName, __MIN(256, name__len), (CHAR*)"Files", 85535);
          f->registerName[0] = 0x00;
          f->tempFile = 0;
          f->identity = identity;
          f->next = Files_files;
          Files_files = f;
          Heap_FileCount += 1;
          return f;
        }
      } else if (dir[0] == 0x00) {
        return NIL;
      } else {
        Files_MakeFileName((void*)dir, 256, (void*)name, name__len, (void*)path, 256);
        Files_ScanPath(&pos, (void*)dir, 256);
      }
    }
  } else {
    return NIL;
  }
  __RETCHK((CHAR*)"Files", 88063);
}

/*----------------------------------------------------------------------------*/
void Files_Purge (Files_File f)
{
  INTEGER i;
  Platform_FileIdentity identity;
  INTEGER error;
  i = 0;
  while (i < 4) {
    if (f->bufs[__X(i, 4, (CHAR*)"Files", 89927)] != NIL) {
      f->bufs[__X(i, 4, (CHAR*)"Files", 89905)]->org = -1;
      f->bufs[__X(i, 4, (CHAR*)"Files", 89923)] = NIL;
    }
    i += 1;
  }
  if (f->fd != Platform_InvalidHandleValue()) {
    error = Platform_TruncateFile(f->fd, 0);
    error = Platform_Seek(f->fd, 0, Platform_SeekSet);
  }
  f->pos = 0;
  f->len = 0;
  f->swapper = -1;
  error = Platform_Identify(f->fd, &identity);
  Platform_SetMTime(&f->identity, identity);
}

/*----------------------------------------------------------------------------*/
void Files_GetDate (Files_File f, INTEGER *t, INTEGER *d)
{
  Platform_FileIdentity identity;
  INTEGER error;
  Files_Create(f);
  error = Platform_Identify(f->fd, &identity);
  Platform_MTimeAsClock(identity, t, d);
}

/*----------------------------------------------------------------------------*/
LONGINT Files_Pos (Files_Rider *r, void **r__typ)
{
  return (*r).org + (LONGINT)(*r).offset;
}

/*----------------------------------------------------------------------------*/
void Files_Set (Files_Rider *r, void **r__typ, Files_File f, LONGINT pos)
{
  LONGINT org;
  INTEGER offset, i, n;
  Files_Buffer buf = NIL;
  INTEGER error;
  if (f != NIL) {
    if (pos > f->len) {
      pos = f->len;
    } else if (pos < 0) {
      pos = 0;
    }
    offset = (INTEGER)__MASK(pos, -4096);
    org = pos - (LONGINT)offset;
    i = 0;
    while ((i < 4 && f->bufs[__X(i, 4, (CHAR*)"Files", 97349)] != NIL) && org != f->bufs[__X(i, 4, (CHAR*)"Files", 97349)]->org) {
      i += 1;
    }
    if (i < 4) {
      if (f->bufs[__X(i, 4, (CHAR*)"Files", 98815)] == NIL) {
        __NEW(buf, Files_BufDesc);
        buf->chg = 0;
        buf->org = -1;
        buf->f = f;
        f->bufs[__X(i, 4, (CHAR*)"Files", 98303)] = buf;
      } else {
        buf = f->bufs[__X(i, 4, (CHAR*)"Files", 98559)];
      }
    } else {
      f->swapper = (SHORTINT)__MASK((INTEGER)f->swapper + 1, -4);
      buf = f->bufs[__X(f->swapper, 4, (CHAR*)"Files", 99360)];
      Files_Flush(buf);
    }
    if (buf->org != org) {
      if (org == f->len) {
        buf->size = 0;
      } else {
        Files_Create(f);
        if (f->pos != org) {
          error = Platform_Seek(f->fd, org, Platform_SeekSet);
        }
        error = Platform_ReadBuf(f->fd, (void*)buf->data, 4096, &n);
        if (error != 0) {
          Files_Err((CHAR*)"read from file not done", 24, f, error);
        }
        f->pos = org + (LONGINT)n;
        buf->size = n;
      }
      buf->org = org;
      buf->chg = 0;
    }
  } else {
    buf = NIL;
    org = 0;
    offset = 0;
  }
  (*r).buf = buf;
  (*r).org = org;
  (*r).offset = offset;
  (*r).eof = 0;
  (*r).res = 0;
}

/*----------------------------------------------------------------------------*/
void Files_ReadByte (Files_Rider *r, void **r__typ, BYTE *x)
{
  INTEGER offset;
  Files_Buffer buf = NIL;
  buf = (*r).buf;
  offset = (*r).offset;
  if ((*r).org != buf->org) {
    Files_Set(r, r__typ, buf->f, (*r).org + (LONGINT)offset);
    buf = (*r).buf;
    offset = (*r).offset;
  }
  if (offset < buf->size) {
    *x = buf->data[__X(offset, 4096, (CHAR*)"Files", 106267)];
    (*r).offset = offset + 1;
  } else if ((*r).org + (LONGINT)offset < buf->f->len) {
    Files_Set(r, r__typ, (*r).buf->f, (*r).org + (LONGINT)offset);
    *x = (*r).buf->data[0];
    (*r).offset = 1;
  } else {
    *x = 0;
    (*r).eof = 1;
  }
}

/*----------------------------------------------------------------------------*/
void Files_ReadBytes (Files_Rider *r, void **r__typ, BYTE *x, INTEGER x__len, INTEGER n)
{
  INTEGER xpos, min, restInBuf, offset;
  Files_Buffer buf = NIL;
  if (n > x__len) {
    Files_IdxTrap(433);
  }
  xpos = 0;
  buf = (*r).buf;
  offset = (*r).offset;
  while (n > 0) {
    if ((*r).org != buf->org || offset >= 4096) {
      Files_Set(r, r__typ, buf->f, (*r).org + (LONGINT)offset);
      buf = (*r).buf;
      offset = (*r).offset;
    }
    restInBuf = buf->size - offset;
    if (restInBuf == 0) {
      (*r).res = n;
      (*r).eof = 1;
      return;
    } else if (n > restInBuf) {
      min = restInBuf;
    } else {
      min = n;
    }
    __MOVE((SYSTEM_ADRINT)buf->data + offset, (SYSTEM_ADRINT)x + xpos, min);
    offset += min;
    (*r).offset = offset;
    xpos += min;
    n -= min;
  }
  (*r).res = 0;
  (*r).eof = 0;
}

/*----------------------------------------------------------------------------*/
void Files_ReadChar (Files_Rider *r, void **r__typ, CHAR *x)
{
  Files_ReadByte(r, r__typ, (BYTE*)x);
}

/*----------------------------------------------------------------------------*/
Files_File Files_Base (Files_Rider *r, void **r__typ)
{
  return (*r).buf->f;
}

/*----------------------------------------------------------------------------*/
void Files_WriteByte (Files_Rider *r, void **r__typ, BYTE x)
{
  Files_Buffer buf = NIL;
  INTEGER offset;
  buf = (*r).buf;
  offset = (*r).offset;
  if ((*r).org != buf->org || offset >= 4096) {
    Files_Set(r, r__typ, buf->f, (*r).org + (LONGINT)offset);
    buf = (*r).buf;
    offset = (*r).offset;
  }
  buf->data[__X(offset, 4096, (CHAR*)"Files", 117785)] = x;
  buf->chg = 1;
  if (offset == buf->size) {
    buf->size += 1;
    buf->f->len += 1;
  }
  (*r).offset = offset + 1;
  (*r).res = 0;
}

/*----------------------------------------------------------------------------*/
void Files_WriteBytes (Files_Rider *r, void **r__typ, BYTE *x, INTEGER x__len, INTEGER n)
{
  INTEGER xpos, min, restInBuf, offset;
  Files_Buffer buf = NIL;
  if (n > x__len) {
    Files_IdxTrap(477);
  }
  xpos = 0;
  buf = (*r).buf;
  offset = (*r).offset;
  while (n > 0) {
    if ((*r).org != buf->org || offset >= 4096) {
      Files_Set(r, r__typ, buf->f, (*r).org + (LONGINT)offset);
      buf = (*r).buf;
      offset = (*r).offset;
    }
    restInBuf = 4096 - offset;
    if (n > restInBuf) {
      min = restInBuf;
    } else {
      min = n;
    }
    __MOVE((SYSTEM_ADRINT)x + xpos, (SYSTEM_ADRINT)buf->data + offset, min);
    offset += min;
    (*r).offset = offset;
    if (offset > buf->size) {
      buf->f->len = buf->f->len + (LONGINT)(offset - buf->size);
      buf->size = offset;
    }
    xpos += min;
    n -= min;
    buf->chg = 1;
  }
  (*r).res = 0;
}

/*----------------------------------------------------------------------------*/
void Files_Delete (CHAR *name, INTEGER name__len, INTEGER *res)
{
  INTEGER pos;
  CHAR dir[256], path[256];
  if (name[0] != 0x00) {
    if (Files_HasDir((void*)name, name__len)) {
      dir[0] = 0x00;
      __STRCOPYCC(name, path, __MIN(256, name__len), (CHAR*)"Files", 134911);
    } else {
      pos = 0;
      Files_ScanPath(&pos, (void*)dir, 256);
      Files_MakeFileName((void*)dir, 256, (void*)name, name__len, (void*)path, 256);
      Files_ScanPath(&pos, (void*)dir, 256);
    }
    Files_Deregister((void*)path, 256);
    *res = Platform_DeleteFile((void*)path, 256);
  } else {
    *res = 1;
  }
}

/*----------------------------------------------------------------------------*/
void Files_Rename (CHAR *old, INTEGER old__len, CHAR *new, INTEGER new__len, INTEGER *res)
{
  INTEGER fdold, fdnew, n, error, ignore;
  Platform_FileIdentity oldidentity, newidentity;
  CHAR buf[4096];
  error = Platform_IdentifyByName((void*)old, old__len, &oldidentity);
  if (error == 0) {
    error = Platform_IdentifyByName((void*)new, new__len, &newidentity);
    if (error != 0 && !Platform_SameFile(oldidentity, newidentity)) {
      Files_Delete((void*)new, new__len, &error);
    }
    error = Platform_RenameFile((void*)old, old__len, (void*)new, new__len);
    if (!Platform_DifferentFilesystems(error)) {
      *res = error;
      return;
    } else {
      error = Platform_OldRO((void*)old, old__len, &fdold);
      if (error != 0) {
        *res = 2;
        return;
      }
      error = Platform_NewFile((void*)new, new__len, &fdnew);
      if (error != 0) {
        error = Platform_CloseFile(fdold);
        *res = 3;
        return;
      }
      error = Platform_Read(fdold, (SYSTEM_ADRINT)buf, 4096, &n);
      while (n > 0) {
        error = Platform_Write(fdnew, (SYSTEM_ADRINT)buf, n);
        if (error != 0) {
          ignore = Platform_CloseFile(fdold);
          ignore = Platform_CloseFile(fdnew);
          Files_Err((CHAR*)"cannot move file", 17, NIL, error);
        }
        error = Platform_Read(fdold, (SYSTEM_ADRINT)buf, 4096, &n);
      }
      ignore = Platform_CloseFile(fdold);
      ignore = Platform_CloseFile(fdnew);
      if (n == 0) {
        error = Platform_DeleteFile((void*)old, old__len);
        *res = 0;
      } else {
        Files_Err((CHAR*)"cannot move file", 17, NIL, error);
      }
    }
  } else {
    *res = 2;
  }
}

/*----------------------------------------------------------------------------*/
void Files_Register (Files_File f)
{
  INTEGER errcode;
  if ((INTEGER)f->state == 1 && f->registerName[0] != 0x00) {
    f->state = 2;
  }
  Files_Close(f);
  if (f->registerName[0] != 0x00) {
    Files_Deregister((void*)f->registerName, 256);
    errcode = Platform_CloseFile(f->fd);
    if (errcode == 0) {
      Files_Rename((void*)f->workName, 256, (void*)f->registerName, 256, &errcode);
      if (errcode == 0) {
        errcode = Platform_OldRW((void*)f->registerName, 256, &f->fd);
        if (errcode == 0) {
          __MOVE(f->registerName, f->workName, 256);
          f->registerName[0] = 0x00;
          f->tempFile = 0;
          return;
        }
      }
    }
    Files_Err((CHAR*)"Couldn\'t rename temp name as register name", 43, f, errcode);
  }
}

/*----------------------------------------------------------------------------*/
void Files_ChangeDirectory (CHAR *path, INTEGER path__len, INTEGER *res)
{
  *res = Platform_ChDir((void*)path, path__len);
}

/*----------------------------------------------------------------------------*/
static void Files_FlipBytes (BYTE *src, INTEGER src__len, BYTE *dest, INTEGER dest__len)
{
  INTEGER i, j;
  if (!Platform_LittleEndian) {
    i = src__len;
    j = 0;
    while (i > 0) {
      i -= 1;
      dest[__X(j, dest__len, (CHAR*)"Files", 157230)] = src[__X(i, src__len, (CHAR*)"Files", 157230)];
      j += 1;
    }
  } else {
    __MOVE((SYSTEM_ADRINT)src, (SYSTEM_ADRINT)dest, src__len);
  }
}

void Files_ReadBool (Files_Rider *R, void **R__typ, BOOLEAN *x)
{
  Files_ReadByte(R, R__typ, (BYTE*)x);
}

/*----------------------------------------------------------------------------*/
void Files_ReadSInt (Files_Rider *R, void **R__typ, SHORTINT *x)
{
  CHAR b[2];
  Files_ReadBytes(R, R__typ, (void*)(SYSTEM_ADRINT)b, 2, 2);
  *x = (SHORTINT)((INTEGER)b[0] + __ASHL((INTEGER)b[1], 8, INTEGER));
}

/*----------------------------------------------------------------------------*/
void Files_ReadInt (Files_Rider *R, void **R__typ, INTEGER *x)
{
  CHAR b[4];
  Files_ReadBytes(R, R__typ, (void*)(SYSTEM_ADRINT)b, 4, 4);
  *x = (((INTEGER)b[0] + __ASHL((INTEGER)b[1], 8, INTEGER)) + __ASHL((INTEGER)b[2], 16, INTEGER)) + __ASHL((INTEGER)b[3], 24, INTEGER);
}

/*----------------------------------------------------------------------------*/
void Files_ReadLInt (Files_Rider *R, void **R__typ, LONGINT *x)
{
  CHAR b[8];
  INTEGER n;
  LONGINT s;
  Files_ReadBytes(R, R__typ, (void*)(SYSTEM_ADRINT)b, 8, 8);
  *x = (SHORTINT)b[0];
  s = 256;
  n = 1;
  while (n <= 7) {
    *x += (LONGINT)b[__X(n, 8, (CHAR*)"Files", 163626)] * s;
    s = __ASHL(s, 8, LONGINT);
    n += 1;
  }
}

/*----------------------------------------------------------------------------*/
void Files_ReadSet (Files_Rider *R, void **R__typ, SET *x)
{
  CHAR b[4];
  Files_ReadBytes(R, R__typ, (void*)(SYSTEM_ADRINT)b, 4, 4);
  *x = (SET)((((INTEGER)b[0] + __ASHL((INTEGER)b[1], 8, INTEGER)) + __ASHL((INTEGER)b[2], 16, INTEGER)) + __ASHL((INTEGER)b[3], 24, INTEGER));
}

/*----------------------------------------------------------------------------*/
void Files_ReadReal (Files_Rider *R, void **R__typ, SHORTREAL *x)
{
  BYTE b[4];
  Files_ReadBytes(R, R__typ, (void*)b, 4, 4);
  Files_FlipBytes((void*)b, 4, (void*)(SYSTEM_ADRINT)x, 4);
}

/*----------------------------------------------------------------------------*/
void Files_ReadLReal (Files_Rider *R, void **R__typ, REAL *x)
{
  BYTE b[8];
  Files_ReadBytes(R, R__typ, (void*)b, 8, 8);
  Files_FlipBytes((void*)b, 8, (void*)(SYSTEM_ADRINT)x, 8);
}

/*----------------------------------------------------------------------------*/
void Files_ReadString (Files_Rider *R, void **R__typ, CHAR *x, INTEGER x__len)
{
  INTEGER i;
  CHAR ch;
  i = 0;
  do {
    Files_ReadChar(R, R__typ, &ch);
    x[__X(i, x__len, (CHAR*)"Files", 169766)] = ch;
    i += 1;
  } while (!(ch == 0x00));
}

/*----------------------------------------------------------------------------*/
void Files_ReadLine (Files_Rider *R, void **R__typ, CHAR *x, INTEGER x__len)
{
  INTEGER i;
  CHAR ch;
  BOOLEAN b;
  i = 0;
  b = 0;
  do {
    Files_ReadChar(R, R__typ, &ch);
    if ((ch == 0x00 || ch == 0x0a) || ch == 0x0d) {
      b = 1;
    } else {
      x[__X(i, x__len, (CHAR*)"Files", 173074)] = ch;
      i += 1;
    }
  } while (!b);
}

/*----------------------------------------------------------------------------*/
void Files_ReadNum (Files_Rider *R, void **R__typ, LONGINT *x)
{
  INTEGER s;
  CHAR ch;
  s = 0;
  *x = 0;
  Files_ReadChar(R, R__typ, &ch);
  while ((INTEGER)ch >= 128) {
    *x += __ASH((LONGINT)((INTEGER)ch - 128), s, LONGINT);
    s += 7;
    Files_ReadChar(R, R__typ, &ch);
  }
  *x += __ASH((LONGINT)(__MASK((INTEGER)ch, -64) - __ASHL(__ASHR((INTEGER)ch, 6, INTEGER), 6, INTEGER)), s, LONGINT);
}

/*----------------------------------------------------------------------------*/
void Files_WriteBool (Files_Rider *R, void **R__typ, BOOLEAN x)
{
  Files_WriteByte(R, R__typ, (BYTE)x);
}

/*----------------------------------------------------------------------------*/
void Files_WriteChar (Files_Rider *R, void **R__typ, CHAR x)
{
  Files_WriteByte(R, R__typ, (BYTE)x);
}

/*----------------------------------------------------------------------------*/
void Files_WriteSInt (Files_Rider *R, void **R__typ, SHORTINT x)
{
  CHAR b[2];
  b[0] = (CHAR)x;
  b[1] = (CHAR)__ASHR((INTEGER)x, 8, INTEGER);
  Files_WriteBytes(R, R__typ, (void*)(SYSTEM_ADRINT)b, 2, 2);
}

/*----------------------------------------------------------------------------*/
void Files_WriteInt (Files_Rider *R, void **R__typ, INTEGER x)
{
  CHAR b[4];
  b[0] = (CHAR)x;
  b[1] = (CHAR)__ASHR(x, 8, INTEGER);
  b[2] = (CHAR)__ASHR(x, 16, INTEGER);
  b[3] = (CHAR)__ASHR(x, 24, INTEGER);
  Files_WriteBytes(R, R__typ, (void*)(SYSTEM_ADRINT)b, 4, 4);
}

/*----------------------------------------------------------------------------*/
void Files_WriteLInt (Files_Rider *R, void **R__typ, LONGINT x)
{
  CHAR b[8];
  INTEGER n;
  LONGINT s;
  b[0] = (CHAR)x;
  s = 256;
  n = 0;
  while (n <= 7) {
    b[__X(n, 8, (CHAR*)"Files", 183090)] = (CHAR)__DIVFL(x, s);
    s = __ASHL(s, 8, LONGINT);
    n += 1;
  }
  Files_WriteBytes(R, R__typ, (void*)(SYSTEM_ADRINT)b, 8, 8);
}

/*----------------------------------------------------------------------------*/
void Files_WriteSet (Files_Rider *R, void **R__typ, SET x)
{
  CHAR b[4];
  INTEGER i;
  i = (INTEGER)x;
  b[0] = (CHAR)i;
  b[1] = (CHAR)__ASHR(i, 8, INTEGER);
  b[2] = (CHAR)__ASHR(i, 16, INTEGER);
  b[3] = (CHAR)__ASHR(i, 24, INTEGER);
  Files_WriteBytes(R, R__typ, (void*)(SYSTEM_ADRINT)b, 4, 4);
}

/*----------------------------------------------------------------------------*/
void Files_WriteReal (Files_Rider *R, void **R__typ, SHORTREAL x)
{
  BYTE b[4];
  Files_FlipBytes((void*)(SYSTEM_ADRINT)&x, 4, (void*)b, 4);
  Files_WriteBytes(R, R__typ, (void*)b, 4, 4);
}

/*----------------------------------------------------------------------------*/
void Files_WriteLReal (Files_Rider *R, void **R__typ, REAL x)
{
  BYTE b[8];
  Files_FlipBytes((void*)(SYSTEM_ADRINT)&x, 8, (void*)b, 8);
  Files_WriteBytes(R, R__typ, (void*)b, 8, 8);
}

/*----------------------------------------------------------------------------*/
void Files_WriteString (Files_Rider *R, void **R__typ, CHAR *x, INTEGER x__len)
{
  INTEGER i;
  i = 0;
  while (x[__X(i, x__len, (CHAR*)"Files", 189715)] != 0x00) {
    i += 1;
  }
  Files_WriteBytes(R, R__typ, (void*)(SYSTEM_ADRINT)x, x__len, i + 1);
}

/*----------------------------------------------------------------------------*/
void Files_WriteNum (Files_Rider *R, void **R__typ, LONGINT x)
{
  while (x < -64 || x > 63) {
    Files_WriteChar(R, R__typ, (CHAR)(__MASK((INTEGER)x, -128) + 128));
    x = __ASHR(x, 7, LONGINT);
  }
  Files_WriteChar(R, R__typ, (CHAR)__MASK((INTEGER)x, -128));
}

/*----------------------------------------------------------------------------*/
void Files_GetName (Files_File f, CHAR *name, INTEGER name__len)
{
  __STRCOPYCC(f->workName, name, __MIN(name__len, 256), (CHAR*)"Files", 193023);
}

/*----------------------------------------------------------------------------*/
static void Files_Finalize (SYSTEM_PTR o)
{
  Files_File f = NIL;
  INTEGER res;
  f = (Files_File)o;
  if (f->fd != Platform_InvalidHandleValue()) {
    Files_CloseOSFile(f);
    if (f->tempFile) {
      res = Platform_DeleteFile((void*)f->workName, 256);
    }
  }
}

void Files_SetSearchPath (CHAR *path, INTEGER path__len)
{
  INTEGER pathlen;
  pathlen = Strings_Length((void*)path, path__len);
  if (pathlen != 0) {
    Files_SearchPath = __NEWARR(NIL, 1, 1, 1, 1, (SYSTEM_ARRLEN)(pathlen + 1));
    __STRCOPYCC(path, Files_SearchPath->data, __MIN(Files_SearchPath->len[0], path__len), (CHAR*)"Files", 197631);
  } else {
    Files_SearchPath = NIL;
  }
}

/*----------------------------------------------------------------------------*/
static void EnumPtrs(void (*P)(void*))
{
  P(Files_SearchPath);
}

__TDESC(Files_FileDesc__desc, 2, 4) = {__TDFLDS("FileDesc", 576), {552, 556, 560, 564, -20}};
__TDESC(Files_BufDesc__desc, 2, 1) = {__TDFLDS("BufDesc", 4116), {0, -8}};
__TDESC(Files_Rider__desc, 2, 1) = {__TDFLDS("Rider", 24), {8, -8}};

export void *Files__init (void)
{
  __DEFMOD;
  __IMPORT(CmdArgs__init);
  __IMPORT(Console__init);
  __IMPORT(Heap__init);
  __IMPORT(Platform__init);
  __IMPORT(Strings__init);
  __REGMOD("Files", EnumPtrs);
  __INITYP(Files_FileDesc, Files_FileDesc, 0);
  __INITYP(Files_BufDesc, Files_BufDesc, 0);
  __INITYP(Files_Rider, Files_Rider, 0);
/* BEGIN */
  Files_tempno = -1;
  Heap_FileCount = 0;
  CmdArgs_GetEnv((CHAR*)"HOME", 5, (void*)Files_HOME, 1024);
  __ENDMOD;
}
