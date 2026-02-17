/* Ofront+ 1.0 -sxtapC -88 */
#include "SYSTEM.oh"

typedef
  CHAR (*Platform_EnvPtr)[1024];

typedef
  struct Platform_FileIdentity {
    LONGINT volume, index, mtime;
  } Platform_FileIdentity;


export BOOLEAN Platform_LittleEndian;
export INTEGER Platform_PID;
export CHAR Platform_CWD[4096];
export INTEGER Platform_SeekSet, Platform_SeekCur, Platform_SeekEnd;


export BOOLEAN Platform_Absent (INTEGER e);
export INTEGER Platform_ChDir (CHAR *n, INTEGER n__len);
export INTEGER Platform_CloseFile (INTEGER handle);
export BOOLEAN Platform_ConnectionFailed (INTEGER e);
static void Platform_ConvertFromUTF16 (LONGCHAR *in, INTEGER in__len, INTEGER inLen, CHAR *out, INTEGER out__len, INTEGER *outLen);
static INTEGER Platform_CopyFile (CHAR *oldname, INTEGER oldname__len, CHAR *newname, INTEGER newname__len);
static INTEGER Platform_CopyFileFd (INTEGER from, INTEGER to);
export void Platform_Delay (INTEGER ms);
export INTEGER Platform_DeleteFile (CHAR *n, INTEGER n__len);
export BOOLEAN Platform_DifferentFilesystems (INTEGER e);
export BOOLEAN Platform_DirExists (CHAR *path, INTEGER path__len);
export INTEGER Platform_Error (void);
export void Platform_ExitOS (INTEGER code);
export BOOLEAN Platform_FileExists (CHAR *pathname, INTEGER pathname__len);
export INTEGER Platform_FileSize (INTEGER h, LONGINT *len);
export void Platform_GetAppDir (CHAR *dir, INTEGER dir__len);
export void Platform_GetAppDirW (LONGCHAR *dir, INTEGER dir__len);
export void Platform_GetClock (INTEGER *t, INTEGER *d);
export void Platform_GetLang (CHAR *lang, INTEGER lang__len);
export void Platform_GetTempPath (CHAR *path, INTEGER path__len);
export INTEGER Platform_Identify (INTEGER h, Platform_FileIdentity *identity);
export INTEGER Platform_IdentifyByName (CHAR *n, INTEGER n__len, Platform_FileIdentity *identity);
export BOOLEAN Platform_Inaccessible (INTEGER e);
export BOOLEAN Platform_IsConsole (INTEGER h);
export void Platform_MTimeAsClock (Platform_FileIdentity i, INTEGER *t, INTEGER *d);
export INTEGER Platform_MaxNameLength (void);
export INTEGER Platform_MaxPathLength (void);
export INTEGER Platform_NewDir (CHAR *pathname, INTEGER pathname__len, INTEGER *h);
export INTEGER Platform_NewFile (CHAR *pathname, INTEGER pathname__len, INTEGER *h);
export BOOLEAN Platform_NoSuchDirectory (INTEGER e);
export LONGINT Platform_OSAllocate (LONGINT size);
export void Platform_OSFree (LONGINT address);
export INTEGER Platform_OldRO (CHAR *pathname, INTEGER pathname__len, INTEGER *h);
export INTEGER Platform_OldRW (CHAR *pathname, INTEGER pathname__len, INTEGER *h);
export INTEGER Platform_Read (INTEGER h, LONGINT p, INTEGER l, INTEGER *n);
export INTEGER Platform_ReadBuf (INTEGER h, BYTE *b, INTEGER b__len, INTEGER *n);
export INTEGER Platform_ReadBufW (INTEGER h, LONGCHAR *b, INTEGER b__len, INTEGER *n);
export INTEGER Platform_RenameFile (CHAR *oldname, INTEGER oldname__len, CHAR *newname, INTEGER newname__len);
export BOOLEAN Platform_SameFile (Platform_FileIdentity i1, Platform_FileIdentity i2);
export BOOLEAN Platform_SameFileTime (Platform_FileIdentity i1, Platform_FileIdentity i2);
export INTEGER Platform_Seek (INTEGER h, LONGINT offset, INTEGER whence);
export void Platform_SetMTime (Platform_FileIdentity *target, Platform_FileIdentity source);
export INTEGER Platform_Sync (INTEGER h);
export INTEGER Platform_System (CHAR *cmd, INTEGER cmd__len);
static void Platform_TestLittleEndian (void);
export INTEGER Platform_Time (void);
export BOOLEAN Platform_TimedOut (INTEGER e);
export BOOLEAN Platform_TooManyFiles (INTEGER e);
export INTEGER Platform_TruncateFile (INTEGER h, LONGINT limit);
export INTEGER Platform_Write (INTEGER h, LONGINT p, INTEGER l);
export INTEGER Platform_WriteW (LONGCHAR *s, INTEGER s__len, INTEGER len);
static void Platform_YMDHMStoClock (INTEGER ye, INTEGER mo, INTEGER da, INTEGER ho, INTEGER mi, INTEGER se, INTEGER *t, INTEGER *d);
static void Platform_getEnv (CHAR *var, INTEGER var__len, CHAR *val, INTEGER val__len);

#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#define Platform_EACCES()  EACCES
#define Platform_EAGAIN()  EAGAIN
#define Platform_ECONNABORTED()  ECONNABORTED
#define Platform_ECONNREFUSED()  ECONNREFUSED
#define Platform_EHOSTUNREACH()  EHOSTUNREACH
#define Platform_EMFILE()  EMFILE
#define Platform_ENETUNREACH()  ENETUNREACH
#define Platform_ENFILE()  ENFILE
#define Platform_ENOENT()  ENOENT
#define Platform_EROFS()  EROFS
#define Platform_ETIMEDOUT()  ETIMEDOUT
#define Platform_EXDEV()  EXDEV
#define Platform_InvalidHandleValue()  (-1)
#define Platform_NAMEMAX()  NAME_MAX
#define Platform_PATHMAX()  PATH_MAX
#define Platform_SystemHalt(code, mod, mod__len, pos)  __HALT(code, mod, pos)
#define Platform_allocate(size)  ((SYSTEM_ADRINT)malloc((size_t)(size)))
#define Platform_chdir(n, n__len)  chdir((char*)n)
#define Platform_closefile(fd)  close(fd)
#define Platform_err()  errno
#define Platform_exit(code)  exit(code)
#define Platform_free(address)  free((void*)(address))
#define Platform_fstat(fd)  fstat(fd, &s)
#define Platform_fsync(fd)  fsync(fd)
#define Platform_ftruncate(fd, length)  ftruncate(fd, length)
#define Platform_getcwd(cwd, cwd__len)  {char *dummy = getcwd((char*)cwd, cwd__len);}
#define Platform_getenv(var, var__len)  (Platform_EnvPtr)getenv((char*)var)
#define Platform_getpid()  (INTEGER)getpid()
#define Platform_gettimeval()  struct timeval tv; gettimeofday(&tv, 0)
#define Platform_isatty(fd)  isatty(fd)
#define Platform_lseek(fd, offset, whence)  lseek(fd, offset, whence)
#define Platform_mkdir(pathname, pathname__len)  mkdir((char*)pathname, 0775)
#define Platform_nanosleep(s, ns)  struct timespec req, rem; req.tv_sec = (time_t)s; req.tv_nsec = ns; nanosleep(&req, &rem)
#define Platform_opennew(n, n__len)  open((char*)n, O_CREAT | O_TRUNC | O_RDWR, 0664)
#define Platform_openro(n, n__len)  open((char*)n, O_RDONLY)
#define Platform_openrw(n, n__len)  open((char*)n, O_RDWR)
#define Platform_readfile(fd, p, l)  read(fd, (void*)(p), l)
#define Platform_rename(o, o__len, n, n__len)  rename((char*)o, (char*)n)
#define Platform_sectotm(s)  struct tm *time = localtime((time_t*)&s)
#define Platform_seekcur()  SEEK_CUR
#define Platform_seekend()  SEEK_END
#define Platform_seekset()  SEEK_SET
#define Platform_stat(n, n__len)  stat((char*)n, &s)
#define Platform_statdev()  (LONGINT)s.st_dev
#define Platform_statino()  (SYSTEM_ADRINT)s.st_ino
#define Platform_statisdir()  S_ISDIR(s.st_mode)
#define Platform_statisreg()  S_ISREG(s.st_mode)
#define Platform_statmtime()  (SYSTEM_ADRINT)s.st_mtime
#define Platform_statsize()  (LONGINT)s.st_size
#define Platform_structstats()  struct stat s
#define Platform_system(str, str__len)  system((char*)str)
#define Platform_timeint(time)  ((INTEGER)(time))
#define Platform_tmhour()  time->tm_hour
#define Platform_tmmday()  time->tm_mday
#define Platform_tmmin()  time->tm_min
#define Platform_tmmon()  time->tm_mon
#define Platform_tmsec()  time->tm_sec
#define Platform_tmyear()  time->tm_year
#define Platform_tvsec()  tv.tv_sec
#define Platform_tvusec()  (INTEGER)tv.tv_usec
#define Platform_unlink(n, n__len)  unlink((char*)n)
#define Platform_write(fd, p, l)  write(fd, (void*)(p), l)

/*============================================================================*/

BOOLEAN Platform_TooManyFiles (INTEGER e)
{
  return e == Platform_EMFILE() || e == Platform_ENFILE();
}

/*----------------------------------------------------------------------------*/
BOOLEAN Platform_NoSuchDirectory (INTEGER e)
{
  return e == Platform_ENOENT();
}

/*----------------------------------------------------------------------------*/
BOOLEAN Platform_DifferentFilesystems (INTEGER e)
{
  return e == Platform_EXDEV();
}

/*----------------------------------------------------------------------------*/
BOOLEAN Platform_Inaccessible (INTEGER e)
{
  return (e == Platform_EACCES() || e == Platform_EROFS()) || e == Platform_EAGAIN();
}

/*----------------------------------------------------------------------------*/
BOOLEAN Platform_Absent (INTEGER e)
{
  return e == Platform_ENOENT();
}

/*----------------------------------------------------------------------------*/
BOOLEAN Platform_TimedOut (INTEGER e)
{
  return e == Platform_ETIMEDOUT();
}

/*----------------------------------------------------------------------------*/
BOOLEAN Platform_ConnectionFailed (INTEGER e)
{
  return ((e == Platform_ECONNREFUSED() || e == Platform_ECONNABORTED()) || e == Platform_ENETUNREACH()) || e == Platform_EHOSTUNREACH();
}

/*----------------------------------------------------------------------------*/
LONGINT Platform_OSAllocate (LONGINT size)
{
  if (size > 0) {
    return Platform_allocate(size);
  }
  Platform_SystemHalt(-25, (CHAR*)"Platform", 9, 121);
  return 0;
}

/*----------------------------------------------------------------------------*/
void Platform_OSFree (LONGINT address)
{
  Platform_free(address);
}

/*----------------------------------------------------------------------------*/
static void Platform_getEnv (CHAR *var, INTEGER var__len, CHAR *val, INTEGER val__len)
{
  Platform_EnvPtr p;
  p = Platform_getenv(var, var__len);
  if (p != NIL) {
    __STRCOPYCC(*p, val, __MIN(val__len, 1024), (CHAR*)"Platform", 34844);
  } else {
    val[0] = 0x00;
  }
}

void Platform_GetLang (CHAR *lang, INTEGER lang__len)
{
  Platform_getEnv((CHAR*)"LANGUAGE", 9, (void*)lang, lang__len);
  if (lang[0] == 0x00) {
    Platform_getEnv((CHAR*)"LC_ALL", 7, (void*)lang, lang__len);
    if (lang[0] == 0x00) {
      Platform_getEnv((CHAR*)"LANG", 5, (void*)lang, lang__len);
    }
  }
}

/*----------------------------------------------------------------------------*/
static void Platform_YMDHMStoClock (INTEGER ye, INTEGER mo, INTEGER da, INTEGER ho, INTEGER mi, INTEGER se, INTEGER *t, INTEGER *d)
{
  *d = (__ASHL(__MOD(ye, 100), 9, INTEGER) + __ASHL(mo + 1, 5, INTEGER)) + da;
  *t = (__ASHL(ho, 12, INTEGER) + __ASHL(mi, 6, INTEGER)) + se;
}

void Platform_GetClock (INTEGER *t, INTEGER *d)
{
  Platform_gettimeval();
  Platform_sectotm(Platform_tvsec());
  Platform_YMDHMStoClock(Platform_tmyear(), Platform_tmmon(), Platform_tmmday(), Platform_tmhour(), Platform_tmmin(), Platform_tmsec(), t, d);
}

/*----------------------------------------------------------------------------*/
INTEGER Platform_Time (void)
{
  Platform_gettimeval();
  return __MODF(__DIVF(Platform_tvusec(), 1000) + Platform_timeint(Platform_tvsec()) * 1000, 2147483647);
}

/*----------------------------------------------------------------------------*/
void Platform_Delay (INTEGER ms)
{
  INTEGER s, ns;
  s = __DIV(ms, 1000);
  ns = __MOD(ms, 1000) * 1000000;
  Platform_nanosleep(s, ns);
}

/*----------------------------------------------------------------------------*/
INTEGER Platform_System (CHAR *cmd, INTEGER cmd__len)
{
  return Platform_system(cmd, cmd__len);
}

/*----------------------------------------------------------------------------*/
INTEGER Platform_Error (void)
{
  return Platform_err();
}

/*----------------------------------------------------------------------------*/
INTEGER Platform_MaxNameLength (void)
{
  return Platform_NAMEMAX();
}

/*----------------------------------------------------------------------------*/
INTEGER Platform_MaxPathLength (void)
{
  return Platform_PATHMAX();
}

/*----------------------------------------------------------------------------*/
INTEGER Platform_OldRO (CHAR *pathname, INTEGER pathname__len, INTEGER *h)
{
  INTEGER fd;
  fd = Platform_openro(pathname, pathname__len);
  if (fd == Platform_InvalidHandleValue()) {
    return Platform_err();
  } else {
    *h = fd;
    return 0;
  }
  __RETCHK((CHAR*)"Platform", 65863);
}

/*----------------------------------------------------------------------------*/
INTEGER Platform_OldRW (CHAR *pathname, INTEGER pathname__len, INTEGER *h)
{
  INTEGER fd;
  fd = Platform_openrw(pathname, pathname__len);
  if (fd == Platform_InvalidHandleValue()) {
    return Platform_err();
  } else {
    *h = fd;
    return 0;
  }
  __RETCHK((CHAR*)"Platform", 67655);
}

/*----------------------------------------------------------------------------*/
INTEGER Platform_NewFile (CHAR *pathname, INTEGER pathname__len, INTEGER *h)
{
  INTEGER fd;
  fd = Platform_opennew(pathname, pathname__len);
  if (fd == Platform_InvalidHandleValue()) {
    return Platform_err();
  } else {
    *h = fd;
    return 0;
  }
  __RETCHK((CHAR*)"Platform", 69447);
}

/*----------------------------------------------------------------------------*/
INTEGER Platform_NewDir (CHAR *pathname, INTEGER pathname__len, INTEGER *h)
{
  if (Platform_mkdir(pathname, pathname__len) != 0) {
    return Platform_err();
  } else {
    return 0;
  }
  __RETCHK((CHAR*)"Platform", 70712);
}

/*----------------------------------------------------------------------------*/
INTEGER Platform_CloseFile (INTEGER handle)
{
  if (Platform_closefile(handle) < 0) {
    return Platform_err();
  } else {
    return 0;
  }
  __RETCHK((CHAR*)"Platform", 72762);
}

/*----------------------------------------------------------------------------*/
INTEGER Platform_Identify (INTEGER h, Platform_FileIdentity *identity)
{
  Platform_structstats();
  if (Platform_fstat(h) < 0) {
    return Platform_err();
  }
  (*identity).volume = Platform_statdev();
  (*identity).index = Platform_statino();
  (*identity).mtime = Platform_statmtime();
  return 0;
}

/*----------------------------------------------------------------------------*/
INTEGER Platform_IdentifyByName (CHAR *n, INTEGER n__len, Platform_FileIdentity *identity)
{
  Platform_structstats();
  if (Platform_stat(n, n__len) < 0) {
    return Platform_err();
  }
  (*identity).volume = Platform_statdev();
  (*identity).index = Platform_statino();
  (*identity).mtime = Platform_statmtime();
  return 0;
}

/*----------------------------------------------------------------------------*/
BOOLEAN Platform_SameFile (Platform_FileIdentity i1, Platform_FileIdentity i2)
{
  return i1.index == i2.index && i1.volume == i2.volume;
}

/*----------------------------------------------------------------------------*/
BOOLEAN Platform_SameFileTime (Platform_FileIdentity i1, Platform_FileIdentity i2)
{
  return i1.mtime == i2.mtime;
}

/*----------------------------------------------------------------------------*/
void Platform_SetMTime (Platform_FileIdentity *target, Platform_FileIdentity source)
{
  (*target).mtime = source.mtime;
}

/*----------------------------------------------------------------------------*/
void Platform_MTimeAsClock (Platform_FileIdentity i, INTEGER *t, INTEGER *d)
{
  Platform_sectotm(i.mtime);
  Platform_YMDHMStoClock(Platform_tmyear(), Platform_tmmon(), Platform_tmmday(), Platform_tmhour(), Platform_tmmin(), Platform_tmsec(), t, d);
}

/*----------------------------------------------------------------------------*/
INTEGER Platform_FileSize (INTEGER h, LONGINT *len)
{
  Platform_structstats();
  if (Platform_fstat(h) < 0) {
    return Platform_err();
  }
  *len = Platform_statsize();
  return 0;
}

/*----------------------------------------------------------------------------*/
void Platform_GetTempPath (CHAR *path, INTEGER path__len)
{
  CHAR s[1024];
  INTEGER i;
  Platform_getEnv((CHAR*)"TMPDIR", 7, (void*)s, 1024);
  i = 0;
  while (s[i] != 0x00) {
    i += 1;
  }
  if (i != 0 && s[i - 1] != '/') {
    s[i] = '/';
    i += 1;
    s[i] = 0x00;
  }
  if (i != 0 && i < path__len) {
    __STRCOPYCC(s, path, __MIN(path__len, 1024), (CHAR*)"Platform", 91694);
  } else {
    __STRCOPYCC((CHAR*)"/tmp/", path, path__len, (CHAR*)"Platform", 91715);
  }
}

/*----------------------------------------------------------------------------*/
INTEGER Platform_Read (INTEGER h, LONGINT p, INTEGER l, INTEGER *n)
{
  *n = Platform_readfile(h, p, l);
  if (*n < 0) {
    *n = 0;
    return Platform_err();
  } else {
    return 0;
  }
  __RETCHK((CHAR*)"Platform", 94002);
}

/*----------------------------------------------------------------------------*/
INTEGER Platform_ReadBuf (INTEGER h, BYTE *b, INTEGER b__len, INTEGER *n)
{
  *n = Platform_readfile(h, (SYSTEM_ADRINT)b, b__len);
  if (*n < 0) {
    *n = 0;
    return Platform_err();
  } else {
    return 0;
  }
  __RETCHK((CHAR*)"Platform", 95538);
}

/*----------------------------------------------------------------------------*/
INTEGER Platform_ReadBufW (INTEGER h, LONGCHAR *b, INTEGER b__len, INTEGER *n)
{
  return 105;
}

/*----------------------------------------------------------------------------*/
INTEGER Platform_Write (INTEGER h, LONGINT p, INTEGER l)
{
  INTEGER written;
  written = Platform_write(h, p, l);
  if (written < 0) {
    return Platform_err();
  } else {
    return 0;
  }
  __RETCHK((CHAR*)"Platform", 99376);
}

/*----------------------------------------------------------------------------*/
static void Platform_ConvertFromUTF16 (LONGCHAR *in, INTEGER in__len, INTEGER inLen, CHAR *out, INTEGER out__len, INTEGER *outLen)
{
  INTEGER i, j, val, lim;
  BOOLEAN ok;
  i = 0;
  j = 0;
  lim = out__len - 1;
  ok = 1;
  if (inLen < 0) {
    inLen = in__len;
  }
  while (((ok && i != inLen) && in[i] != 0x00) && j < lim) {
    val = (INTEGER)in[i];
    i += 1;
    if (val < 128) {
      out[j] = (CHAR)val;
      j += 1;
    } else if (val < 2048 && j < lim - 1) {
      out[j] = (CHAR)(__ASHR(val, 6, INTEGER) + 192);
      j += 1;
      out[j] = (CHAR)(__MASK(val, -64) + 128);
      j += 1;
    } else if (j < lim - 2) {
      out[j] = (CHAR)(__ASHR(val, 12, INTEGER) + 224);
      j += 1;
      out[j] = (CHAR)(__MASK(__ASHR(val, 6, INTEGER), -64) + 128);
      j += 1;
      out[j] = (CHAR)(__MASK(val, -64) + 128);
      j += 1;
    } else {
      ok = 0;
    }
  }
  out[j] = 0x00;
  *outLen = j;
  if (i != inLen && in[i] != 0x00) {
    ok = 0;
  }
}

INTEGER Platform_WriteW (LONGCHAR *s, INTEGER s__len, INTEGER len)
{
  INTEGER error;
  CHAR u[40960];
  INTEGER ulen;
  LONGINT p;
  Platform_ConvertFromUTF16((void*)s, s__len, len, (void*)u, 40960, &ulen);
  if (Platform_write(1, (SYSTEM_ADRINT)u, ulen) != ulen) {
    error = Platform_err();
  } else {
    error = 0;
  }
  return error;
}

/*----------------------------------------------------------------------------*/
INTEGER Platform_Sync (INTEGER h)
{
  if (Platform_fsync(h) < 0) {
    return Platform_err();
  } else {
    return 0;
  }
  __RETCHK((CHAR*)"Platform", 110641);
}

/*----------------------------------------------------------------------------*/
INTEGER Platform_Seek (INTEGER h, LONGINT offset, INTEGER whence)
{
  if (Platform_lseek(h, offset, whence) < 0) {
    return Platform_err();
  } else {
    return 0;
  }
  __RETCHK((CHAR*)"Platform", 113473);
}

/*----------------------------------------------------------------------------*/
INTEGER Platform_TruncateFile (INTEGER h, LONGINT limit)
{
  if (Platform_ftruncate(h, limit) < 0) {
    return Platform_err();
  } else {
    return 0;
  }
  __RETCHK((CHAR*)"Platform", 115516);
}

/*----------------------------------------------------------------------------*/
INTEGER Platform_DeleteFile (CHAR *n, INTEGER n__len)
{
  if (Platform_unlink(n, n__len) < 0) {
    return Platform_err();
  } else {
    return 0;
  }
  __RETCHK((CHAR*)"Platform", 117554);
}

/*----------------------------------------------------------------------------*/
INTEGER Platform_ChDir (CHAR *n, INTEGER n__len)
{
  INTEGER r;
  r = Platform_chdir(n, n__len);
  Platform_getcwd((void*)Platform_CWD, 4096);
  if (r < 0) {
    return Platform_err();
  } else {
    return 0;
  }
  __RETCHK((CHAR*)"Platform", 120362);
}

/*----------------------------------------------------------------------------*/
void Platform_GetAppDir (CHAR *dir, INTEGER dir__len)
{
  __STRCOPYCC((CHAR*)"./", dir, dir__len, (CHAR*)"Platform", 122111);
}

/*----------------------------------------------------------------------------*/
void Platform_GetAppDirW (LONGCHAR *dir, INTEGER dir__len)
{
  __STRCOPYLL(((LONGCHAR[]){46, 47, 0}), dir, dir__len, (CHAR*)"Platform", 123647);
}

/*----------------------------------------------------------------------------*/
BOOLEAN Platform_FileExists (CHAR *pathname, INTEGER pathname__len)
{
  Platform_structstats();
  if (Platform_stat(pathname, pathname__len) != 0) {
    return 0;
  }
  return Platform_statisreg();
}

/*----------------------------------------------------------------------------*/
BOOLEAN Platform_DirExists (CHAR *path, INTEGER path__len)
{
  Platform_structstats();
  if (Platform_stat(path, path__len) != 0) {
    return 0;
  }
  return Platform_statisdir();
}

/*----------------------------------------------------------------------------*/
static INTEGER Platform_CopyFileFd (INTEGER from, INTEGER to)
{
  BYTE buf[32768];
  INTEGER n, err;
  err = Platform_ReadBuf(from, (void*)buf, 32768, &n);
  while (err == 0 && n > 0) {
    err = Platform_Write(to, (SYSTEM_ADRINT)buf, n);
    if (err == 0) {
      err = Platform_ReadBuf(from, (void*)buf, 32768, &n);
    }
  }
  return err;
}

static INTEGER Platform_CopyFile (CHAR *oldname, INTEGER oldname__len, CHAR *newname, INTEGER newname__len)
{
  INTEGER from, to, res;
  from = Platform_openro(oldname, oldname__len);
  if (from != -1) {
    to = Platform_opennew(newname, newname__len);
    if (to != -1) {
      res = Platform_CopyFileFd(from, to);
      if (Platform_closefile(to) == -1) {
        res = Platform_err();
      }
    } else {
      res = -101;
    }
    if (Platform_closefile(from) == -1) {
      res = Platform_err();
    }
  } else {
    res = -102;
  }
  return res;
}

INTEGER Platform_RenameFile (CHAR *oldname, INTEGER oldname__len, CHAR *newname, INTEGER newname__len)
{
  INTEGER res;
  res = Platform_rename(oldname, oldname__len, newname, newname__len);
  if (res < 0) {
    res = Platform_err();
    if (res == Platform_EXDEV()) {
      res = Platform_CopyFile((void*)oldname, oldname__len, (void*)newname, newname__len);
      if (res == 0) {
        res = Platform_DeleteFile((void*)oldname, oldname__len);
      }
    }
  }
  return res;
}

/*----------------------------------------------------------------------------*/
void Platform_ExitOS (INTEGER code)
{
  Platform_exit(code);
}

/*----------------------------------------------------------------------------*/
BOOLEAN Platform_IsConsole (INTEGER h)
{
  return Platform_isatty(h) != 0;
}

/*----------------------------------------------------------------------------*/
static void Platform_TestLittleEndian (void)
{
  INTEGER i;
  i = 1;
  __GET((SYSTEM_ADRINT)&i, Platform_LittleEndian, BOOLEAN);
}


export void *Platform__init (void)
{
  __DEFMOD;
  __REGMOD("Platform", 0);
/* BEGIN */
  Platform_TestLittleEndian();
  Platform_CWD[0] = 0x00;
  Platform_getcwd((void*)Platform_CWD, 4096);
  Platform_PID = Platform_getpid();
  Platform_SeekSet = Platform_seekset();
  Platform_SeekCur = Platform_seekcur();
  Platform_SeekEnd = Platform_seekend();
  __ENDMOD;
}
