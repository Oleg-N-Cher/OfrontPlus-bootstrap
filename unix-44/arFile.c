/* Ofront+ 1.0 -s2 -44 */
#include "SYSTEM.oh"
#include "arC.oh"
#include "arText.oh"

typedef
  struct arFile_FILE__rec *arFile_FILE;

typedef
  struct arFile_FILE__rec {
    char _prvt0[1];
  } arFile_FILE__rec;

typedef
  struct arFile_File__rec *arFile_File;

typedef
  struct arFile_File__rec {
    arFile_FILE file;
    BOOLEAN success;
  } arFile_File__rec;

export void arFile_File_Close (arFile_File self);
export BOOLEAN arFile_File_EOF (arFile_File self);
static INTEGER arFile_File_Error (arFile_File self);
static void arFile_File_Flush (arFile_File self);
typedef
  struct arFile_Stream *arFile_StreamPtr;

export arFile_StreamPtr arFile_File_GetStream (arFile_File self);
static void arFile_File_Init (arFile_File self, arFile_FILE file);
export void arFile_File_PutC (arFile_File self, CHAR ch);
export INTEGER arFile_File_PutS (arFile_File self, CHAR *str, INTEGER str__len);
export INTEGER arFile_File_Seek (arFile_File self, LONGINT offset, INTEGER whence);
export LONGINT arFile_File_Tell (arFile_File self);
#define __arFile_File_Close(self) __SEND(__TYPEOF(self), arFile_File_Close, 0, void(*)(arFile_File), (self))
#define __arFile_File_EOF(self) __SEND(__TYPEOF(self), arFile_File_EOF, 1, BOOLEAN(*)(arFile_File), (self))
#define __arFile_File_Error(self) __SEND(__TYPEOF(self), arFile_File_Error, 2, INTEGER(*)(arFile_File), (self))
#define __arFile_File_Flush(self) __SEND(__TYPEOF(self), arFile_File_Flush, 3, void(*)(arFile_File), (self))
#define __arFile_File_GetStream(self) __SEND(__TYPEOF(self), arFile_File_GetStream, 4, arFile_StreamPtr(*)(arFile_File), (self))
#define __arFile_File_Init(self, file) __SEND(__TYPEOF(self), arFile_File_Init, 5, void(*)(arFile_File, arFile_FILE), (self, file))
#define __arFile_File_PutC(self, ch) __SEND(__TYPEOF(self), arFile_File_PutC, 6, void(*)(arFile_File, CHAR), (self, ch))
#define __arFile_File_PutS(self, str, str__len) __SEND(__TYPEOF(self), arFile_File_PutS, 7, INTEGER(*)(arFile_File, CHAR*, INTEGER ), (self, str, str__len))
#define __arFile_File_Seek(self, offset, whence) __SEND(__TYPEOF(self), arFile_File_Seek, 8, INTEGER(*)(arFile_File, LONGINT, INTEGER), (self, offset, whence))
#define __arFile_File_Tell(self) __SEND(__TYPEOF(self), arFile_File_Tell, 9, LONGINT(*)(arFile_File), (self))

typedef
  struct arFile_Stream { /* arText_Stream */
    arFile_FILE file;
  } arFile_Stream;

export void arFile_Stream_Char (arFile_Stream *self, void **self__typ, CHAR value);
export void arFile_Stream_Flush (arFile_Stream *self, void **self__typ);
export void arFile_Stream_String (arFile_Stream *self, void **self__typ, CHAR *value, INTEGER value__len);


export arFile_File arFile_out, arFile_err;

export void **arFile_Stream__typ;
export void **arFile_File__rec__typ;

static arFile_File arFile_NewFile (arFile_FILE f);
static arFile_StreamPtr arFile_NewStream (arFile_FILE file);
export arFile_File arFile_Open (CHAR *name, INTEGER name__len, CHAR *mode, INTEGER mode__len);

#include <errno.h>
#include <stdio.h>
#define arFile_errno()  errno
#define arFile_fclose(file)  fclose((FILE *)file)
#define arFile_feof(file)  feof((FILE *)file)
#define arFile_fflush(file)  fflush((FILE *)file)
#define arFile_fopen(name, name__len, mode, mode__len)  (arFile_FILE) fopen((const char *)name, (const char *)mode)
#define arFile_fputc(file, ch)  fputc(ch,(FILE *)file)
#define arFile_fputs(file, str, str__len)  fputs((const char *)str,(FILE *)file)
#define arFile_fseek(file, offset, whence)  fseek((FILE *)file, offset, whence)
#define arFile_ftell(file)  ftell((FILE *)file)
#define arFile_getStdErr()  (arFile_FILE) stderr
#define arFile_getStdOut()  (arFile_FILE) stdout

/*============================================================================*/

void arFile_Stream_Char (arFile_Stream *self, void **self__typ, CHAR value)
{
  INTEGER result;
  result = arFile_fputc((*self).file, value);
}

/*----------------------------------------------------------------------------*/
void arFile_Stream_String (arFile_Stream *self, void **self__typ, CHAR *value, INTEGER value__len)
{
  INTEGER result;
  result = arFile_fputs((*self).file, value, value__len);
}

/*----------------------------------------------------------------------------*/
void arFile_Stream_Flush (arFile_Stream *self, void **self__typ)
{
  INTEGER result;
  result = arFile_fflush((*self).file);
}

/*----------------------------------------------------------------------------*/
static arFile_StreamPtr arFile_NewStream (arFile_FILE file)
{
  arFile_StreamPtr s = NIL;
  __NEW(s, arFile_Stream);
  s->file = file;
  return s;
}

static void arFile_File_Init (arFile_File self, arFile_FILE file)
{
  self->file = file;
  self->success = 1;
}

void arFile_File_Close (arFile_File self)
{
  self->success = arFile_fclose(self->file) == 0;
}

/*----------------------------------------------------------------------------*/
static void arFile_File_Flush (arFile_File self)
{
  self->success = arFile_fflush(self->file) == 0;
}

INTEGER arFile_File_Seek (arFile_File self, LONGINT offset, INTEGER whence)
{
  self->success = arFile_fseek(self->file, offset, whence) == 0;
  return 0;
}

/*----------------------------------------------------------------------------*/
LONGINT arFile_File_Tell (arFile_File self)
{
  LONGINT result;
  result = arFile_ftell(self->file);
  self->success = result >= 0;
  return 0;
}

/*----------------------------------------------------------------------------*/
void arFile_File_PutC (arFile_File self, CHAR ch)
{
  self->success = arFile_fputc(self->file, ch) == 0;
}

/*----------------------------------------------------------------------------*/
INTEGER arFile_File_PutS (arFile_File self, CHAR *str, INTEGER str__len)
{
  __DUP(str, str__len);
  self->success = arFile_fputs(self->file, str, str__len) == 0;
  return 0;
}

/*----------------------------------------------------------------------------*/
BOOLEAN arFile_File_EOF (arFile_File self)
{
  return arFile_feof(self->file) != 0;
}

/*----------------------------------------------------------------------------*/
static INTEGER arFile_File_Error (arFile_File self)
{
  return arFile_errno();
}

static arFile_File arFile_NewFile (arFile_FILE f)
{
  arFile_File file = NIL;
  __NEW(file, arFile_File__rec);
  file->file = f;
  return file;
}

arFile_StreamPtr arFile_File_GetStream (arFile_File self)
{
  return arFile_NewStream(self->file);
}

/*----------------------------------------------------------------------------*/
arFile_File arFile_Open (CHAR *name, INTEGER name__len, CHAR *mode, INTEGER mode__len)
{
  arFile_FILE f = NIL;
  arFile_File file = NIL;
  __DUP(name, name__len);
  __DUP(mode, mode__len);
  f = arFile_fopen(name, name__len, mode, mode__len);
  if (f == NIL) {
    return NIL;
  }
  return arFile_NewFile(f);
}

/*----------------------------------------------------------------------------*/
static void EnumPtrs(void (*P)(void*))
{
  P(arFile_out);
  P(arFile_err);
}

__TDESC(arFile_Stream__desc, 4, 0) = {__TDFLDS("Stream", 4), {-4}};
__TDESC(arFile_File__rec__desc, 11, 0) = {__TDFLDS("File__rec", 8), {-4}};

export void *arFile__init (void)
{
  __DEFMOD;
  __IMPORT(arText__init);
  __REGMOD("arFile", EnumPtrs);
  __INITYP(arFile_Stream, arText_Stream, 1);
  __INITBP(arFile_Stream, arFile_Stream_Char, 0);
  __INITBP(arFile_Stream, arFile_Stream_Flush, 1);
  __INITBP(arFile_Stream, arFile_Stream_String, 2);
  __INITYP(arFile_File__rec, arFile_File__rec, 0);
  __INITBP(arFile_File__rec, arFile_File_Close, 0);
  __INITBP(arFile_File__rec, arFile_File_EOF, 1);
  __INITBP(arFile_File__rec, arFile_File_Error, 2);
  __INITBP(arFile_File__rec, arFile_File_Flush, 3);
  __INITBP(arFile_File__rec, arFile_File_GetStream, 4);
  __INITBP(arFile_File__rec, arFile_File_Init, 5);
  __INITBP(arFile_File__rec, arFile_File_PutC, 6);
  __INITBP(arFile_File__rec, arFile_File_PutS, 7);
  __INITBP(arFile_File__rec, arFile_File_Seek, 8);
  __INITBP(arFile_File__rec, arFile_File_Tell, 9);
/* BEGIN */
  arFile_out = arFile_NewFile(arFile_getStdOut());
  arFile_err = arFile_NewFile(arFile_getStdErr());
  __ENDMOD;
}
