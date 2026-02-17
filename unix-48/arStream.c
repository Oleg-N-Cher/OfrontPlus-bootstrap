/* Ofront+ 1.0 -s2 -48 */
#include "SYSTEM.oh"
#include "arText.oh"

typedef
  struct arStream_FILE__rec *arStream_FILE;

typedef
  struct arStream_FILE__rec {
    char _prvt0[1];
  } arStream_FILE__rec;

typedef
  struct arStream_File { /* arText_StreamWriter */
    CHAR intFormat[8];
    CHAR hexFormat[8];
    CHAR realFormat[8];
    BOOLEAN quoteLiterals, setAsList;
    arText_StreamPtr stream;
  } arStream_File;

export void arStream_File_Close (arStream_File *self, void **self__typ);
export BOOLEAN arStream_File_Open (arStream_File *self, void **self__typ, CHAR *name, INTEGER name__len, CHAR *mode, INTEGER mode__len);
#define __arStream_File_Close(self, self__typ) __SEND(self__typ, arStream_File_Close, 12, void(*)(arStream_File*, void **), (self, self__typ))
#define __arStream_File_Open(self, self__typ, name, name__len, mode, mode__len) __SEND(self__typ, arStream_File_Open, 13, BOOLEAN(*)(arStream_File*, void **, CHAR*, INTEGER , CHAR*, INTEGER ), (self, self__typ, name, name__len, mode, mode__len))

typedef
  struct arStream_Stream { /* arText_Stream */
    arStream_FILE file;
  } arStream_Stream;

export void arStream_Stream_Char (arStream_Stream *self, void **self__typ, CHAR value);
export void arStream_Stream_Flush (arStream_Stream *self, void **self__typ);
export void arStream_Stream_String (arStream_Stream *self, void **self__typ, CHAR *value, INTEGER value__len);

typedef
  arStream_Stream *arStream_StreamPtr;


export arText_StreamWriter arStream_out, arStream_err;

export void **arStream_Stream__typ;
export void **arStream_File__typ;

static arStream_StreamPtr arStream_NewStream (arStream_FILE file);

#include <stdio.h>
#define arStream_fclose(file)  fclose((FILE *)file)
#define arStream_fflush(file)  fflush((FILE *)file)
#define arStream_fopen(name, name__len, mode, mode__len)  (arStream_FILE) fopen((const char *)name, (const char *)mode)
#define arStream_fputc(file, ch)  fputc(ch,(FILE *)file)
#define arStream_fputs(file, str, str__len)  fputs((const char *)str,(FILE *)file)
#define arStream_getStdErr()  (arStream_FILE) stderr
#define arStream_getStdOut()  (arStream_FILE) stdout

/*============================================================================*/

void arStream_Stream_Char (arStream_Stream *self, void **self__typ, CHAR value)
{
  arStream_fputc((*self).file, value);
}

/*----------------------------------------------------------------------------*/
void arStream_Stream_String (arStream_Stream *self, void **self__typ, CHAR *value, INTEGER value__len)
{
  arStream_fputs((*self).file, value, value__len);
}

/*----------------------------------------------------------------------------*/
void arStream_Stream_Flush (arStream_Stream *self, void **self__typ)
{
  arStream_fflush((*self).file);
}

/*----------------------------------------------------------------------------*/
static arStream_StreamPtr arStream_NewStream (arStream_FILE file)
{
  arStream_StreamPtr s = NIL;
  __NEW(s, arStream_Stream);
  s->file = file;
  return s;
}

void arStream_File_Close (arStream_File *self, void **self__typ)
{
  arStream_fclose((__GUARDP((*self).stream, arStream_Stream, 1))->file);
}

/*----------------------------------------------------------------------------*/
BOOLEAN arStream_File_Open (arStream_File *self, void **self__typ, CHAR *name, INTEGER name__len, CHAR *mode, INTEGER mode__len)
{
  arStream_FILE file = NIL;
  __DUP(name, name__len);
  __DUP(mode, mode__len);
  file = arStream_fopen(name, name__len, mode, mode__len);
  if (file == NIL) {
    return 0;
  }
  __arText_StreamWriter_Init((void*)self, self__typ, (void*)arStream_NewStream(file));
  return 1;
}

/*----------------------------------------------------------------------------*/
static void EnumPtrs(void (*P)(void*))
{
  __ENUMR(&arStream_out, arText_StreamWriter__typ, 32, 1, P);
  __ENUMR(&arStream_err, arText_StreamWriter__typ, 32, 1, P);
}

__TDESC(arStream_Stream__desc, 4, 0) = {__TDFLDS("Stream", 4), {-4}};
__TDESC(arStream_File__desc, 15, 1) = {__TDFLDS("File", 32), {28, -8}};

export void *arStream__init (void)
{
  __DEFMOD;
  __IMPORT(arText__init);
  __REGMOD("arStream", EnumPtrs);
  __INITYP(arStream_Stream, arText_Stream, 1);
  __INITBP(arStream_Stream, arStream_Stream_Char, 0);
  __INITBP(arStream_Stream, arStream_Stream_Flush, 1);
  __INITBP(arStream_Stream, arStream_Stream_String, 2);
  __INITYP(arStream_File, arText_StreamWriter, 3);
  __INITBP(arStream_File, arStream_File_Close, 12);
  __INITBP(arStream_File, arStream_File_Open, 13);
/* BEGIN */
  __arText_StreamWriter_Init(&arStream_out, arText_StreamWriter__typ, (void*)arStream_NewStream(arStream_getStdOut()));
  __arText_StreamWriter_Init(&arStream_err, arText_StreamWriter__typ, (void*)arStream_NewStream(arStream_getStdOut()));
  __ENDMOD;
}
