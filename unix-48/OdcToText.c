/* Ofront+ 1.0 -m3 -48 */
#include "SYSTEM.oh"
#include "Files.oh"
#include "Platform.oh"
#include "Console.oh"
#include "CmdArgs.oh"

typedef
  SHORTINT OdcToText_CP1251[128];

typedef
  struct INT16_ARRAY *OdcToText_Text16;


#ifndef INT16_ARRAY_DEF
#define INT16_ARRAY_DEF
typedef struct INT16_ARRAY {
  INTEGER len[1];
  SHORTINT data[1];
} INT16_ARRAY;
#endif 

#ifndef CHAR_ARRAY_DEF
#define CHAR_ARRAY_DEF
typedef struct CHAR_ARRAY {
  INTEGER len[1];
  CHAR data[1];
} CHAR_ARRAY;
#endif 

static __CONSTARR OdcToText_CP1251 OdcToText_Cp1251 =
  {1026,1027,8218,1107,8222,8230,8224,8225,8364,8240,
  1033,8249,1034,1036,1035,1039,1106,8216,8217,8220,
  8221,8226,8211,8212,63,8482,1113,8250,1114,1116,
  1115,1119,160,1038,1118,1032,164,1168,166,167,
  1025,169,1028,171,172,173,174,1031,176,177,
  1030,1110,1169,181,182,183,1105,8470,1108,187,
  1112,1029,1109,1111,1040,1041,1042,1043,1044,1045,
  1046,1047,1048,1049,1050,1051,1052,1053,1054,1055,
  1056,1057,1058,1059,1060,1061,1062,1063,1064,1065,
  1066,1067,1068,1069,1070,1071,1072,1073,1074,1075,
  1076,1077,1078,1079,1080,1081,1082,1083,1084,1085,
  1086,1087,1088,1089,1090,1091,1092,1093,1094,1095,
  1096,1097,1098,1099,1100,1101,1102,1103};
static CHAR OdcToText_pathname[1024], OdcToText_utf8name[1024];


static void OdcToText_CP1251ToWideChar (SHORTINT *ch);
static void OdcToText_HaltMsg (CHAR *msg, INTEGER msg__len, INTEGER n);
static void OdcToText_HaltStr (CHAR *msg, INTEGER msg__len, CHAR *str, INTEGER str__len);
static void OdcToText_OdcTo1251 (CHAR *pathname, INTEGER pathname__len);
static void OdcToText_OdcToUtf8 (CHAR *pathname, INTEGER pathname__len, CHAR *utf8name, INTEGER utf8name__len, BOOLEAN crlf);
static void OdcToText_ReadFile (Files_File f, OdcToText_Text16 *text, INTEGER *txtlen, BOOLEAN *bom);
export void OdcToText_StringToUtf8 (SHORTINT *in, INTEGER in__len, CHAR *out, INTEGER out__len, INTEGER *res);
static CHAR OdcToText_WideCharToCP1251 (SHORTINT ch);


/*============================================================================*/

static void OdcToText_HaltMsg (CHAR *msg, INTEGER msg__len, INTEGER n)
{
  INTEGER i;
  CHAR ch;
  i = 0;
  ch = msg[0];
  while (ch != 0x00) {
    if (ch == '#') {
      Console_Int(n, 0);
    } else {
      Console_Char(ch);
    }
    i += 1;
    ch = msg[__X(i, msg__len, (CHAR*)"OdcToText", 18943)];
  }
  Console_Ln();
  __HALT(1, (CHAR*)"OdcToText", 19455);
}

static void OdcToText_HaltStr (CHAR *msg, INTEGER msg__len, CHAR *str, INTEGER str__len)
{
  INTEGER i;
  CHAR ch;
  i = 0;
  ch = msg[0];
  while (ch != 0x00) {
    if (ch == '#') {
      Console_String((void*)str, str__len);
    } else {
      Console_Char(ch);
    }
    i += 1;
    ch = msg[__X(i, msg__len, (CHAR*)"OdcToText", 22015)];
  }
  Console_Ln();
  __HALT(1, (CHAR*)"OdcToText", 22527);
}

static void OdcToText_CP1251ToWideChar (SHORTINT *ch)
{
  if (*ch >= 128 && *ch <= 255) {
    *ch = OdcToText_Cp1251[__X(*ch - 128, 128, (CHAR*)"OdcToText", 23611)];
  }
}

static struct ReadFile__8 {
  Files_Rider *in;
  struct ReadFile__8 *lnk;
} *ReadFile__8_s;

static void __9 (INTEGER *next, INTEGER *down, INTEGER *end);
static void __11 (INTEGER *x);

static void __11 (INTEGER *x)
{
  BYTE b;
  Files_ReadByte(&(*ReadFile__8_s->in), Files_Rider__typ, &b);
  *x = __MASK((SHORTINT)b, -256);
  Files_ReadByte(&(*ReadFile__8_s->in), Files_Rider__typ, &b);
  *x = *x + (INTEGER)__ASHL(__MASK((SHORTINT)b, -256), 8, SHORTINT);
  Files_ReadByte(&(*ReadFile__8_s->in), Files_Rider__typ, &b);
  *x = *x + __ASHL((INTEGER)__MASK((SHORTINT)b, -256), 16, INTEGER);
  Files_ReadByte(&(*ReadFile__8_s->in), Files_Rider__typ, &b);
  *x = *x + __ASHL((INTEGER)b, 24, INTEGER);
}

static void __9 (INTEGER *next, INTEGER *down, INTEGER *end)
{
  BYTE b, t;
  INTEGER n;
  Files_ReadByte(&(*ReadFile__8_s->in), Files_Rider__typ, &b);
  do {
    Files_ReadByte(&(*ReadFile__8_s->in), Files_Rider__typ, &t);
    if (t == -14) {
      __11(&n);
    } else {
      do {
        Files_ReadByte(&(*ReadFile__8_s->in), Files_Rider__typ, &b);
      } while (!(b == 0));
    }
  } while (!(t != -15));
  __11(&n);
  __11(next);
  *next = *next + (INTEGER)Files_Pos(&(*ReadFile__8_s->in), Files_Rider__typ);
  __11(down);
  *down = *down + (INTEGER)Files_Pos(&(*ReadFile__8_s->in), Files_Rider__typ);
  __11(end);
  *end = *end + (INTEGER)Files_Pos(&(*ReadFile__8_s->in), Files_Rider__typ);
}

static void OdcToText_ReadFile (Files_File f, OdcToText_Text16 *text, INTEGER *txtlen, BOOLEAN *bom)
{
  INTEGER x, len, next, down, end;
  Files_Rider in = {0}, in1 = {0};
  SHORTINT ch16;
  BYTE b;
  struct ReadFile__8 _s;
  _s.in = &in;
  _s.lnk = ReadFile__8_s;
  ReadFile__8_s = &_s;
  *txtlen = 0;
  *bom = 0;
  if (f != NIL) {
    Files_Set(&in, Files_Rider__typ, f, 0);
    Files_Set(&in1, Files_Rider__typ, f, 0);
    Files_Set(&in, Files_Rider__typ, f, 8);
    __9(&next, &down, &end);
    Files_Set(&in, Files_Rider__typ, f, down);
    __9(&next, &down, &end);
    Files_Set(&in, Files_Rider__typ, f, down);
    __9(&next, &down, &end);
    Files_Set(&in, Files_Rider__typ, f, down);
    __9(&next, &down, &end);
    Files_ReadByte(&in, Files_Rider__typ, &b);
    Files_ReadByte(&in, Files_Rider__typ, &b);
    Files_ReadByte(&in, Files_Rider__typ, &b);
    Files_ReadByte(&in, Files_Rider__typ, &b);
    Files_ReadByte(&in, Files_Rider__typ, &b);
    Files_ReadByte(&in, Files_Rider__typ, &b);
    __11(&x);
    Files_Set(&in1, Files_Rider__typ, f, (INTEGER)Files_Pos(&in, Files_Rider__typ) + x);
    next = down;
    *text = __NEWARR(NIL, 2, 2, 1, 1, (SYSTEM_ARRLEN)(Files_Length(f)));
    Files_ReadByte(&in, Files_Rider__typ, &b);
    while (b != -1) {
      if (next == (INTEGER)Files_Pos(&in, Files_Rider__typ)) {
        __9(&next, &down, &end);
        Files_Set(&in, Files_Rider__typ, f, end);
      }
      __11(&len);
      if (len > 0) {
        while (len > 0) {
          Files_ReadByte(&in1, Files_Rider__typ, &b);
          ch16 = __MASK((SHORTINT)b, -256);
          if (ch16 > 127) {
            *bom = 1;
            OdcToText_CP1251ToWideChar(&ch16);
            ((*text)->data)[__X(*txtlen, (*text)->len[0], (CHAR*)"OdcToText", 40026)] = ch16;
            *txtlen += 1;
          } else if ((ch16 == 9 || ch16 == 13) || ch16 >= 32) {
            ((*text)->data)[__X(*txtlen, (*text)->len[0], (CHAR*)"OdcToText", 40286)] = ch16;
            *txtlen += 1;
          } else if (ch16 == 10 || ch16 == 14) {
          } else if (ch16 == 0) {
            ReadFile__8_s = _s.lnk;
            return;
          } else {
            OdcToText_HaltMsg((CHAR*)"Unknown SHORTCHAR code: [#]", 28, ch16);
          }
          len -= 1;
        }
      } else if (len < 0) {
        *bom = 1;
        while (len < 0) {
          Files_ReadByte(&in1, Files_Rider__typ, &b);
          x = __MASK((SHORTINT)b, -256);
          Files_ReadByte(&in1, Files_Rider__typ, &b);
          ch16 = (SHORTINT)(x + (INTEGER)__ASHL((SHORTINT)b + 128, 8, SHORTINT));
          ((*text)->data)[__X(*txtlen, (*text)->len[0], (CHAR*)"OdcToText", 43041)] = ch16;
          *txtlen += 1;
          len += 2;
        }
      } else {
        __11(&x);
        __11(&x);
        Files_ReadByte(&in1, Files_Rider__typ, &b);
      }
      if (next == (INTEGER)Files_Pos(&in, Files_Rider__typ)) {
        __9(&next, &down, &end);
        Files_Set(&in, Files_Rider__typ, f, end);
      }
      Files_ReadByte(&in, Files_Rider__typ, &b);
    }
  }
  ReadFile__8_s = _s.lnk;
}

static CHAR OdcToText_WideCharToCP1251 (SHORTINT ch)
{
  INTEGER n;
  if (ch <= 127) {
    return (CHAR)ch;
  }
  n = 127;
  while (n >= 0) {
    if (ch == OdcToText_Cp1251[__X(n, 128, (CHAR*)"OdcToText", 57087)]) {
      return (CHAR)(n + 128);
    }
    n += -1;
  }
  Console_String((CHAR*)"Can\'t convert character [", 26);
  Console_Int(ch, 0);
  Console_Char(']');
  Console_Ln();
  return '\?';
}

static void OdcToText_OdcTo1251 (CHAR *pathname, INTEGER pathname__len)
{
  OdcToText_Text16 text16 = NIL;
  Files_File f = NIL;
  SHORTINT ch16;
  INTEGER textlen, n;
  BOOLEAN bom;
  f = Files_Old((void*)pathname, pathname__len);
  if (f != NIL) {
    OdcToText_ReadFile(f, &text16, &textlen, &bom);
    if (text16 != NIL) {
      n = 0;
      while (n < textlen) {
        ch16 = (text16->data)[__X(n, text16->len[0], (CHAR*)"OdcToText", 60954)];
        if (ch16 != 13) {
          Console_Char(OdcToText_WideCharToCP1251(ch16));
        } else {
          Console_Ln();
        }
        n += 1;
      }
    } else {
      OdcToText_HaltStr((CHAR*)"Couldn\'t read \"#\"", 18, (void*)pathname, pathname__len);
    }
  } else {
    OdcToText_HaltStr((CHAR*)"Couldn\'t find \"#\"", 18, (void*)pathname, pathname__len);
  }
  Console_Flush();
}

void OdcToText_StringToUtf8 (SHORTINT *in, INTEGER in__len, CHAR *out, INTEGER out__len, INTEGER *res)
{
  INTEGER i, j, val, max;
  i = 0;
  j = 0;
  max = out__len - 3;
  while (in[__X(i, in__len, (CHAR*)"OdcToText", 65567)] != 0 && j < max) {
    val = in[__X(i, in__len, (CHAR*)"OdcToText", 65808)];
    i += 1;
    if (val < 128) {
      out[__X(j, out__len, (CHAR*)"OdcToText", 66328)] = (CHAR)val;
      j += 1;
    } else if (val < 2048) {
      out[__X(j, out__len, (CHAR*)"OdcToText", 66853)] = (CHAR)(__ASHR(val, 6, INTEGER) + 192);
      j += 1;
      out[__X(j, out__len, (CHAR*)"OdcToText", 67109)] = (CHAR)(__MASK(val, -64) + 128);
      j += 1;
    } else {
      out[__X(j, out__len, (CHAR*)"OdcToText", 67623)] = (CHAR)(__ASHR(val, 12, INTEGER) + 224);
      j += 1;
      out[__X(j, out__len, (CHAR*)"OdcToText", 67884)] = (CHAR)(__MASK(__ASHR(val, 6, INTEGER), -64) + 128);
      j += 1;
      out[__X(j, out__len, (CHAR*)"OdcToText", 68133)] = (CHAR)(__MASK(val, -64) + 128);
      j += 1;
    }
  }
  out[__X(j, out__len, (CHAR*)"OdcToText", 68878)] = 0x00;
  if (in[__X(i, in__len, (CHAR*)"OdcToText", 69375)] == 0) {
    *res = 0;
  } else {
    *res = 1;
  }
}

/*----------------------------------------------------------------------------*/
static struct OdcToUtf8__5 {
  BOOLEAN *emit;
  Files_Rider *src, *wr;
  struct OdcToUtf8__5 *lnk;
} *OdcToUtf8__5_s;

static void __6 (CHAR ch);

static void __6 (CHAR ch)
{
  CHAR in;
  if (!(*OdcToUtf8__5_s->emit)) {
    if (((*OdcToUtf8__5_s->src)).eof) {
      (*OdcToUtf8__5_s->emit) = 1;
    } else {
      Files_ReadChar(&(*OdcToUtf8__5_s->src), Files_Rider__typ, &in);
      if (in != ch) {
        (*OdcToUtf8__5_s->emit) = 1;
      }
    }
  }
  Files_WriteChar(&(*OdcToUtf8__5_s->wr), Files_Rider__typ, ch);
}

static void OdcToText_OdcToUtf8 (CHAR *pathname, INTEGER pathname__len, CHAR *utf8name, INTEGER utf8name__len, BOOLEAN crlf)
{
  OdcToText_Text16 text = NIL;
  INTEGER textlen, res;
  BOOLEAN bom, emit;
  CHAR byte;
  Files_File f = NIL;
  Files_File utf8file = NIL;
  Files_Rider src = {0}, wr = {0};
  struct CHAR_ARRAY *utf8text = NIL;
  CHAR tempname[1000];
  struct OdcToUtf8__5 _s;
  _s.emit = &emit;
  _s.src = &src;
  _s.wr = &wr;
  _s.lnk = OdcToUtf8__5_s;
  OdcToUtf8__5_s = &_s;
  f = Files_Old((void*)pathname, pathname__len);
  if (f != NIL) {
    OdcToText_ReadFile(f, &text, &textlen, &bom);
    if (text != NIL) {
      if (textlen == 0) {
        OdcToUtf8__5_s = _s.lnk;
        return;
      }
      utf8text = __NEWARR(NIL, 1, 1, 1, 1, (SYSTEM_ARRLEN)(__ASHL(textlen, 2, INTEGER) + 1));
      OdcToText_StringToUtf8((void*)text->data, text->len[0], (void*)utf8text->data, utf8text->len[0], &res);
      if (res == 0) {
        __STRCOPYCC(utf8name, tempname, __MIN(1000, utf8name__len), (CHAR*)"OdcToText", 76837);
        __STRAPNDCC((CHAR*)".tmp", 5, tempname, 1000, (CHAR*)"OdcToText", 76837);
        utf8file = Files_New((void*)tempname, 1000);
        if (utf8file != NIL) {
          f = Files_Old((void*)utf8name, utf8name__len);
          emit = f == NIL;
          if (!emit) {
            Files_Set(&src, Files_Rider__typ, f, 0);
          }
          Files_Set(&wr, Files_Rider__typ, utf8file, 0);
          if (bom) {
            __6(0xef);
            __6(0xbb);
            __6(0xbf);
          }
          res = 0;
          byte = (utf8text->data)[0];
          while (byte != 0x00) {
            if (byte != 0x0d) {
              __6(byte);
            } else {
              if (crlf) {
                __6(0x0d);
              }
              __6(0x0a);
            }
            res += 1;
            byte = (utf8text->data)[__X(res, utf8text->len[0], (CHAR*)"OdcToText", 80639)];
          }
          if (!emit) {
            Files_ReadChar(&src, Files_Rider__typ, &byte);
            emit = !src.eof || byte != 0x00;
          }
          if (emit) {
            Files_Register(utf8file);
            res = Platform_CloseFile(utf8file->fd);
            Files_Rename((void*)tempname, 1000, (void*)utf8name, utf8name__len, &res);
            if (res != 0) {
              res = Platform_CloseFile(f->fd);
              Files_Rename((void*)tempname, 1000, (void*)utf8name, utf8name__len, &res);
              if (res != 0) {
                OdcToText_HaltStr((CHAR*)"Couldn\'t save \"#\"", 18, (void*)utf8name, utf8name__len);
              }
            }
          }
        } else {
          OdcToText_HaltStr((CHAR*)"Couldn\'t create \"#\"", 20, (void*)utf8name, utf8name__len);
        }
      } else {
        OdcToText_HaltMsg((CHAR*)"StringToUtf8 fault: code [#]", 29, res);
      }
    } else {
      OdcToText_HaltStr((CHAR*)"Couldn\'t read \"#\"", 18, (void*)pathname, pathname__len);
    }
  } else {
    OdcToText_HaltStr((CHAR*)"Couldn\'t find \"#\"", 18, (void*)pathname, pathname__len);
  }
  OdcToUtf8__5_s = _s.lnk;
}


int main (int argc, char **argv)
{
  __INIT(argc, argv);
  __IMPORT(CmdArgs__init);
  __IMPORT(Files__init);
  __IMPORT(Console__init);
  __IMPORT(Platform__init);
  __REGMAIN("OdcToText", 0);
/* BEGIN */
  Files_SetSearchPath((CHAR*)".", 2);
  switch (CmdArgs_Count) {
    case 1: 
      CmdArgs_Get(1, (void*)OdcToText_pathname, 1024);
      OdcToText_OdcTo1251((void*)OdcToText_pathname, 1024);
      break;
    case 2: 
      CmdArgs_Get(1, (void*)OdcToText_pathname, 1024);
      CmdArgs_Get(2, (void*)OdcToText_utf8name, 1024);
      OdcToText_OdcToUtf8((void*)OdcToText_pathname, 1024, (void*)OdcToText_utf8name, 1024, 1);
      break;
    default: 
      Console_String((CHAR*)".odc to text Converter v1.0 (c) VEDAsoft Oberon Club", 53);
      Console_Ln();
      Console_Ln();
      Console_String((CHAR*)"  to UTF-8 (BOM, CRLF): odc2txt file.odc file.txt", 50);
      Console_Ln();
      Console_String((CHAR*)"  to 1251 (Windows): odc2txt file.odc > file.txt", 49);
      Console_Ln();
      break;
  }
  __FINI;
}
