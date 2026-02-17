/* Ofront+ 1.0 -s2 -48 */
#include "SYSTEM.oh"
#include "arStream.oh"
#include "arText.oh"
#include "arValue.oh"
#include "arCFormat.oh"
#include "arC.oh"
#include "arStrings.oh"




static BOOLEAN arFormat_ConvertOption (CHAR *options, INTEGER options__len, SHORTINT oPos, CHAR *output, INTEGER output__len, arValue_Object o);
export void arFormat_Format (arText_Writer *w, void **w__typ, CHAR *fmt, INTEGER fmt__len, arValue_Object *args, INTEGER args__len);
export arValue_String arFormat_Format0 (CHAR *fmt, INTEGER fmt__len);
export arValue_String arFormat_Format1 (CHAR *fmt, INTEGER fmt__len, arValue_Object p1);
export arValue_String arFormat_Format2 (CHAR *fmt, INTEGER fmt__len, arValue_Object p1, arValue_Object p2);
export arValue_String arFormat_Format3 (CHAR *fmt, INTEGER fmt__len, arValue_Object p1, arValue_Object p2, arValue_Object p3);
export arValue_String arFormat_Format4 (CHAR *fmt, INTEGER fmt__len, arValue_Object p1, arValue_Object p2, arValue_Object p3, arValue_Object p4);
export arValue_String arFormat_Format5 (CHAR *fmt, INTEGER fmt__len, arValue_Object p1, arValue_Object p2, arValue_Object p3, arValue_Object p4, arValue_Object p5);
export void arFormat_FormatList (arText_Writer w, CHAR *fmt, INTEGER fmt__len, arValue_List args);
export arValue_String arFormat_FormatString (CHAR *fmt, INTEGER fmt__len, arValue_Object *args, INTEGER args__len);
export void arFormat_Out0 (CHAR *fmt, INTEGER fmt__len);
export void arFormat_Out1 (CHAR *fmt, INTEGER fmt__len, arValue_Object p1);
export void arFormat_Out2 (CHAR *fmt, INTEGER fmt__len, arValue_Object p1, arValue_Object p2);
export void arFormat_Out3 (CHAR *fmt, INTEGER fmt__len, arValue_Object p1, arValue_Object p2, arValue_Object p3);
export void arFormat_Out4 (CHAR *fmt, INTEGER fmt__len, arValue_Object p1, arValue_Object p2, arValue_Object p3, arValue_Object p4);
export void arFormat_Out5 (CHAR *fmt, INTEGER fmt__len, arValue_Object p1, arValue_Object p2, arValue_Object p3, arValue_Object p4, arValue_Object p5);
export void arFormat_Show (arValue_Object o);
export void arFormat_ShowLn (arValue_Object o);


/*============================================================================*/

static BOOLEAN arFormat_ConvertOption (CHAR *options, INTEGER options__len, SHORTINT oPos, CHAR *output, INTEGER output__len, arValue_Object o)
{
  CHAR type;
  if (o == NIL) {
    return 0;
  }
  switch (options[__X(oPos - 1, options__len, (CHAR*)"arFormat", 10517)]) {
    case 'd': case 'i': case 'u': case 'x': case 'c': 
      if (__ISP(o, arValue_Integer__rec, 1)) {
        arCFormat_IntToString((void*)output, output__len, options, options__len, ((arValue_Integer)o)->value);
        return 1;
      }
      break;
    case 'e': case 'f': case 'g': 
      if (__ISP(o, arValue_Real__rec, 1)) {
        arCFormat_RealToString((void*)output, output__len, options, options__len, ((arValue_Real)o)->value);
        return 1;
      }
      break;
    case 's': 
      if (__ISP(o, arValue_String__rec, 1)) {
        arCFormat_StringToString((void*)output, output__len, options, options__len, ((arValue_String)o)->value->data, ((arValue_String)o)->value->len[0]);
        return 1;
      }
      break;
    default: 
      break;
  }
  return 0;
}

void arFormat_Format (arText_Writer *w, void **w__typ, CHAR *fmt, INTEGER fmt__len, arValue_Object *args, INTEGER args__len)
{
  INTEGER i, arg;
  CHAR ch;
  BOOLEAN inFormat;
  CHAR options[32];
  CHAR conversion[32];
  SHORTINT oPos;
  arValue_Object o = NIL;
  CHAR type;
  __DUP(fmt, fmt__len);
  i = 0;
  arg = 0;
  inFormat = 0;
  while (i < fmt__len && fmt[__X(i, fmt__len, (CHAR*)"arFormat", 19749)] != 0x00) {
    ch = fmt[__X(i, fmt__len, (CHAR*)"arFormat", 19982)];
    i += 1;
    if (inFormat) {
      if (ch == '}') {
        inFormat = 0;
        if (arg < args__len) {
          o = args[__X(arg, args__len, (CHAR*)"arFormat", 21267)];
          arg += 1;
          if (oPos > 0 && arFormat_ConvertOption((void*)options, 32, oPos, (void*)conversion, 32, o)) {
            __arText_Stream_String((void*)w, w__typ, (void*)conversion, 32);
          } else {
            arValue_Format(w, w__typ, o);
          }
        }
      } else {
        if (oPos < 31) {
          options[__X(oPos, 32, (CHAR*)"arFormat", 24088)] = ch;
          oPos += 1;
          options[__X(oPos, 32, (CHAR*)"arFormat", 24344)] = 0x00;
        }
      }
    } else {
      switch (ch) {
        case '{': 
          inFormat = 1;
          options[0] = '%';
          options[1] = 0x00;
          oPos = 1;
          break;
        case '\\': 
          if (i < fmt__len) {
            ch = fmt[__X(i, fmt__len, (CHAR*)"arFormat", 27409)];
            switch (ch) {
              case 'a': 
                ch = 0x07;
                break;
              case 'b': 
                ch = 0x08;
                break;
              case 't': 
                ch = 0x09;
                break;
              case 'n': 
                ch = 0x0a;
                break;
              case 'r': 
                ch = 0x0d;
                break;
              default: 
                break;
            }
            i += 1;
            __arText_Stream_Char((void*)w, w__typ, ch);
          }
          break;
        default: 
          __arText_Stream_Char((void*)w, w__typ, ch);
          break;
      }
    }
  }
}

/*----------------------------------------------------------------------------*/
arValue_String arFormat_FormatString (CHAR *fmt, INTEGER fmt__len, arValue_Object *args, INTEGER args__len)
{
  arText_Buffer result = {0};
  __arText_Buffer_Init(&result, arText_Buffer__typ, 32);
  arFormat_Format((void*)&result, arText_Buffer__typ, fmt, fmt__len, (void*)args, args__len);
  return arValue_strb(&result, arText_Buffer__typ);
}

/*----------------------------------------------------------------------------*/
arValue_String arFormat_Format0 (CHAR *fmt, INTEGER fmt__len)
{
  arValue_Object args[1] = {0};
  __DUP(fmt, fmt__len);
  args[0] = NIL;
  return arFormat_FormatString((void*)fmt, fmt__len, (void*)args, 1);
}

/*----------------------------------------------------------------------------*/
arValue_String arFormat_Format1 (CHAR *fmt, INTEGER fmt__len, arValue_Object p1)
{
  arValue_Object args[1] = {0};
  __DUP(fmt, fmt__len);
  args[0] = p1;
  return arFormat_FormatString((void*)fmt, fmt__len, (void*)args, 1);
}

/*----------------------------------------------------------------------------*/
arValue_String arFormat_Format2 (CHAR *fmt, INTEGER fmt__len, arValue_Object p1, arValue_Object p2)
{
  arValue_Object args[2] = {0};
  __DUP(fmt, fmt__len);
  args[0] = p1;
  args[1] = p2;
  return arFormat_FormatString((void*)fmt, fmt__len, (void*)args, 2);
}

/*----------------------------------------------------------------------------*/
arValue_String arFormat_Format3 (CHAR *fmt, INTEGER fmt__len, arValue_Object p1, arValue_Object p2, arValue_Object p3)
{
  arValue_Object args[3] = {0};
  __DUP(fmt, fmt__len);
  args[0] = p1;
  args[1] = p2;
  args[2] = p3;
  return arFormat_FormatString((void*)fmt, fmt__len, (void*)args, 3);
}

/*----------------------------------------------------------------------------*/
arValue_String arFormat_Format4 (CHAR *fmt, INTEGER fmt__len, arValue_Object p1, arValue_Object p2, arValue_Object p3, arValue_Object p4)
{
  arValue_Object args[4] = {0};
  __DUP(fmt, fmt__len);
  args[0] = p1;
  args[1] = p2;
  args[2] = p3;
  args[3] = p4;
  return arFormat_FormatString((void*)fmt, fmt__len, (void*)args, 4);
}

/*----------------------------------------------------------------------------*/
arValue_String arFormat_Format5 (CHAR *fmt, INTEGER fmt__len, arValue_Object p1, arValue_Object p2, arValue_Object p3, arValue_Object p4, arValue_Object p5)
{
  arValue_Object args[5] = {0};
  __DUP(fmt, fmt__len);
  args[0] = p1;
  args[1] = p2;
  args[2] = p3;
  args[3] = p4;
  args[4] = p5;
  return arFormat_FormatString((void*)fmt, fmt__len, (void*)args, 5);
}

/*----------------------------------------------------------------------------*/
void arFormat_FormatList (arText_Writer w, CHAR *fmt, INTEGER fmt__len, arValue_List args)
{
  arValue_ObjectArray argsArray = NIL;
  __DUP(fmt, fmt__len);
  argsArray = __arValue_List_ToObjectArray(args);
  arFormat_Format(&w, arText_Writer__typ, fmt, fmt__len, (void*)argsArray->data, argsArray->len[0]);
}

/*----------------------------------------------------------------------------*/
void arFormat_Out0 (CHAR *fmt, INTEGER fmt__len)
{
  arValue_Object args[1] = {0};
  __DUP(fmt, fmt__len);
  args[0] = NIL;
  arFormat_Format((void*)&arStream_out, arText_StreamWriter__typ, fmt, fmt__len, (void*)args, 1);
}

/*----------------------------------------------------------------------------*/
void arFormat_Out1 (CHAR *fmt, INTEGER fmt__len, arValue_Object p1)
{
  arValue_Object args[1] = {0};
  __DUP(fmt, fmt__len);
  args[0] = p1;
  arFormat_Format((void*)&arStream_out, arText_StreamWriter__typ, fmt, fmt__len, (void*)args, 1);
}

/*----------------------------------------------------------------------------*/
void arFormat_Out2 (CHAR *fmt, INTEGER fmt__len, arValue_Object p1, arValue_Object p2)
{
  arValue_Object args[2] = {0};
  __DUP(fmt, fmt__len);
  args[0] = p1;
  args[1] = p2;
  arFormat_Format((void*)&arStream_out, arText_StreamWriter__typ, fmt, fmt__len, (void*)args, 2);
}

/*----------------------------------------------------------------------------*/
void arFormat_Out3 (CHAR *fmt, INTEGER fmt__len, arValue_Object p1, arValue_Object p2, arValue_Object p3)
{
  arValue_Object args[3] = {0};
  __DUP(fmt, fmt__len);
  args[0] = p1;
  args[1] = p2;
  args[2] = p3;
  arFormat_Format((void*)&arStream_out, arText_StreamWriter__typ, fmt, fmt__len, (void*)args, 3);
}

/*----------------------------------------------------------------------------*/
void arFormat_Out4 (CHAR *fmt, INTEGER fmt__len, arValue_Object p1, arValue_Object p2, arValue_Object p3, arValue_Object p4)
{
  arValue_Object args[4] = {0};
  __DUP(fmt, fmt__len);
  args[0] = p1;
  args[1] = p2;
  args[2] = p3;
  args[3] = p4;
  arFormat_Format((void*)&arStream_out, arText_StreamWriter__typ, fmt, fmt__len, (void*)args, 4);
}

/*----------------------------------------------------------------------------*/
void arFormat_Out5 (CHAR *fmt, INTEGER fmt__len, arValue_Object p1, arValue_Object p2, arValue_Object p3, arValue_Object p4, arValue_Object p5)
{
  arValue_Object args[5] = {0};
  __DUP(fmt, fmt__len);
  args[0] = p1;
  args[1] = p2;
  args[2] = p3;
  args[3] = p4;
  args[4] = p5;
  arFormat_Format((void*)&arStream_out, arText_StreamWriter__typ, fmt, fmt__len, (void*)args, 5);
}

/*----------------------------------------------------------------------------*/
void arFormat_Show (arValue_Object o)
{
  arValue_Format((void*)&arStream_out, arText_StreamWriter__typ, o);
}

/*----------------------------------------------------------------------------*/
void arFormat_ShowLn (arValue_Object o)
{
  arValue_Format((void*)&arStream_out, arText_StreamWriter__typ, o);
  __arText_Writer_Ln((void*)&arStream_out, arText_StreamWriter__typ);
}

/*----------------------------------------------------------------------------*/

export void *arFormat__init (void)
{
  __DEFMOD;
  __IMPORT(arStrings__init);
  __IMPORT(arText__init);
  __IMPORT(arValue__init);
  __IMPORT(arStream__init);
  __REGMOD("arFormat", 0);
/* BEGIN */
  __ENDMOD;
}
