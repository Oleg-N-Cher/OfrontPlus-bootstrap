/* Ofront+ 1.0 -s2 -48 */
#include "SYSTEM.oh"
#include "Files.oh"
#include "Platform.oh"
#include "arStrings.oh"
#include "arOut.oh"
#include "arText.oh"
#include "arValue.oh"




export arValue_Object arJSON_ParseJSON (CHAR *text, INTEGER text__len, INTEGER *err, SET features);
export arValue_Object arJSON_ParseString (CHAR *text, INTEGER text__len);
export arValue_String arJSON_ReadFile (CHAR *name, INTEGER name__len);
export arValue_Object arJSON_ReadJSON (CHAR *name, INTEGER name__len);


/*============================================================================*/

static struct ParseJSON__1 {
  CHAR *text;
  INTEGER text__len;
  INTEGER *err;
  SET *features;
  INTEGER *pos, *length;
  CHAR *ch;
  struct ParseJSON__1 *lnk;
} *ParseJSON__1_s;

static void __2 (CHAR expect);
static void __4 (INTEGER code);
static arValue_String __6 (void);
static BOOLEAN __8 (CHAR ch);
static void __10 (void);
static void __12 (void);
static arValue_Object __14 (void);
static arValue_List __16 (void);
static arValue_Object __18 (void);
static arValue_Record __24 (void);
static arValue_String __29 (void);
static arValue_Object __31 (void);
static void __33 (void);
static void __35 (void);

static void __12 (void)
{
  if ((*ParseJSON__1_s->pos) < (*ParseJSON__1_s->length)) {
    (*ParseJSON__1_s->ch) = ParseJSON__1_s->text[__X((*ParseJSON__1_s->pos), ParseJSON__1_s->text__len, (CHAR*)"arJSON", 10258)];
    (*ParseJSON__1_s->pos) += 1;
  } else {
    (*ParseJSON__1_s->ch) = 0x00;
  }
  if (__IN(2, (*ParseJSON__1_s->features))) {
    arOut_Char((*ParseJSON__1_s->ch));
  }
}

static void __35 (void)
{
  while ((((*ParseJSON__1_s->ch) == 0x0d || (*ParseJSON__1_s->ch) == 0x0a) || (*ParseJSON__1_s->ch) == 0x09) || (*ParseJSON__1_s->ch) == ' ') {
    __12();
  }
}

static void __33 (void)
{
  CHAR chLast, chSafe;
  INTEGER posSafe;
  __35();
  for (;;) {
    if ((*ParseJSON__1_s->ch) != '/' || !__IN(0, (*ParseJSON__1_s->features))) {
      break;
    }
    chSafe = (*ParseJSON__1_s->ch);
    posSafe = (*ParseJSON__1_s->pos);
    __12();
    if ((*ParseJSON__1_s->ch) == '/') {
      __12();
      while ((*ParseJSON__1_s->ch) != 0x0a && (*ParseJSON__1_s->ch) != 0x00) {
        __12();
      }
      __35();
    } else if ((*ParseJSON__1_s->ch) == '*') {
      __12();
      chLast = 0x00;
      for (;;) {
        if ((*ParseJSON__1_s->ch) == 0x00 || ((*ParseJSON__1_s->ch) == '/' && chLast == '*')) {
          break;
        }
        chLast = (*ParseJSON__1_s->ch);
        __12();
      }
      __12();
      __35();
    } else {
      (*ParseJSON__1_s->ch) = chSafe;
      (*ParseJSON__1_s->pos) = posSafe;
      break;
    }
  }
}

static void __10 (void)
{
  __12();
  __33();
}

static void __4 (INTEGER code)
{
  arOut_String((CHAR*)"Error: ", 8);
  arOut_Int(code);
  arOut_String((CHAR*)" at position ", 14);
  arOut_Int((*ParseJSON__1_s->pos));
  arOut_Ln();
  *ParseJSON__1_s->err = code;
}

static void __2 (CHAR expect)
{
  if ((*ParseJSON__1_s->ch) == expect) {
    __10();
  } else {
    arOut_String((CHAR*)"Error: Expected \'", 18);
    arOut_Char(expect);
    arOut_String((CHAR*)"\' but found \'", 14);
    arOut_Char((*ParseJSON__1_s->ch));
    arOut_String((CHAR*)"\' at position ", 15);
    arOut_Int((*ParseJSON__1_s->pos));
    arOut_Ln();
    *ParseJSON__1_s->err = 7;
  }
}

static arValue_String __29 (void)
{
  arText_Buffer buffer = {0};
  __arText_Buffer_Init(&buffer, arText_Buffer__typ, 16);
  if ((*ParseJSON__1_s->ch) != '\"') {
    __4(2);
  } else {
    __12();
    for (;;) {
      if ((*ParseJSON__1_s->ch) == '\"') {
        break;
      } else if ((*ParseJSON__1_s->ch) < ' ') {
        __4(3);
        break;
      } else if ((*ParseJSON__1_s->ch) == '\\') {
        __12();
        switch ((*ParseJSON__1_s->ch)) {
          case '\"': case '\\': case '/': 
            break;
          case 'b': 
            (*ParseJSON__1_s->ch) = 0x08;
            break;
          case 'f': 
            (*ParseJSON__1_s->ch) = 0x0c;
            break;
          case 'n': 
            (*ParseJSON__1_s->ch) = 0x0a;
            break;
          case 'r': 
            (*ParseJSON__1_s->ch) = 0x0d;
            break;
          case 't': 
            (*ParseJSON__1_s->ch) = 0x09;
            break;
          default: 
            __4(4);
            break;
        }
      }
      __arText_Stream_Char((void*)&buffer, arText_Buffer__typ, (*ParseJSON__1_s->ch));
      __12();
    }
    __10();
  }
  return arValue_strb(&buffer, arText_Buffer__typ);
}

static struct __18__19 {
  arText_Buffer *buffer;
  struct __18__19 *lnk;
} *__18__19_s;

static void __22 (void);

static void __22 (void)
{
  while ((*ParseJSON__1_s->ch) >= '0' && (*ParseJSON__1_s->ch) <= '9') {
    __arText_Stream_Char((void*)&(*__18__19_s->buffer), arText_Buffer__typ, (*ParseJSON__1_s->ch));
    __12();
  }
}

static arValue_Object __18 (void)
{
  BOOLEAN negate, isReal;
  arText_Buffer buffer = {0};
  arValue_Object result = NIL;
  arText_String _ptr__21 = NIL;
  arText_String _ptr__20 = NIL;
  struct __18__19 _s;
  arValue_Object __retval;
  _s.buffer = &buffer;
  _s.lnk = __18__19_s;
  __18__19_s = &_s;
  __arText_Buffer_Init(&buffer, arText_Buffer__typ, 32);
  negate = (*ParseJSON__1_s->ch) == '-';
  if (negate) {
    __arText_Stream_Char((void*)&buffer, arText_Buffer__typ, (*ParseJSON__1_s->ch));
    __12();
  }
  __22();
  isReal = 0;
  if ((*ParseJSON__1_s->ch) == '.') {
    isReal = 1;
    __arText_Stream_Char((void*)&buffer, arText_Buffer__typ, (*ParseJSON__1_s->ch));
    __12();
    __22();
  }
  if ((*ParseJSON__1_s->ch) == 'E' || (*ParseJSON__1_s->ch) == 'e') {
    isReal = 1;
    __arText_Stream_Char((void*)&buffer, arText_Buffer__typ, 'E');
    __12();
    if ((*ParseJSON__1_s->ch) == '-' || (*ParseJSON__1_s->ch) == '+') {
      __arText_Stream_Char((void*)&buffer, arText_Buffer__typ, (*ParseJSON__1_s->ch));
      __12();
    }
    __22();
  }
  __33();
  __arText_Buffer_Terminate(&buffer, arText_Buffer__typ);
  if (isReal) {
    result = (arValue_Object)(_ptr__21 = buffer.value, 
      arValue_ParseReal((void*)_ptr__21->data, _ptr__21->len[0]));
  } else {
    result = (arValue_Object)(_ptr__20 = buffer.value, 
      arValue_ParseInt((void*)_ptr__20->data, _ptr__20->len[0]));
  }
  if (result == NIL) {
    __4(5);
    __retval = (void*)(arValue_strb(&buffer, arText_Buffer__typ));
    __18__19_s = _s.lnk;
    ;
    return __retval;
  }
  __retval = result;
  __18__19_s = _s.lnk;
  ;
  return __retval;
}

static BOOLEAN __8 (CHAR ch)
{
  return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

static arValue_String __6 (void)
{
  arText_Buffer buffer = {0};
  __arText_Buffer_Init(&buffer, arText_Buffer__typ, 32);
  while (__8((*ParseJSON__1_s->ch))) {
    __arText_Stream_Char((void*)&buffer, arText_Buffer__typ, (*ParseJSON__1_s->ch));
    __12();
  }
  __33();
  return arValue_strb(&buffer, arText_Buffer__typ);
}

static arValue_Object __14 (void)
{
  arValue_String i = NIL;
  i = __6();
  if (__STRCMPCC(i->value->data, (CHAR*)"true", 5, (CHAR*)"arJSON", 55557) == 0) {
    return (void*)(arValue_bool(1));
  } else if (__STRCMPCC(i->value->data, (CHAR*)"false", 6, (CHAR*)"arJSON", 54806) == 0) {
    return (void*)(arValue_bool(0));
  }
  __4(6);
  return (void*)i;
}

static struct __24__25 {
  arValue_Record *r;
  struct __24__25 *lnk;
} *__24__25_s;

static void __26 (void);

static void __26 (void)
{
  arValue_String key = NIL;
  arValue_Object value = NIL;
  arText_String _ptr__28 = NIL;
  if (__IN(1, (*ParseJSON__1_s->features)) && __8((*ParseJSON__1_s->ch))) {
    key = __6();
  } else {
    key = __29();
  }
  __2(':');
  value = __31();
  _ptr__28 = key->value;
  __arValue_Record_Set((*__24__25_s->r), (void*)_ptr__28->data, _ptr__28->len[0], value);
}

static arValue_Record __24 (void)
{
  arValue_Record r = NIL;
  struct __24__25 _s;
  arValue_Record __retval;
  _s.r = &r;
  _s.lnk = __24__25_s;
  __24__25_s = &_s;
  __10();
  r = arValue_record();
  if ((*ParseJSON__1_s->ch) != '}') {
    __26();
    while ((*ParseJSON__1_s->ch) == ',') {
      __10();
      __26();
    }
  }
  __2('}');
  __retval = r;
  __24__25_s = _s.lnk;
  ;
  return __retval;
}

static arValue_List __16 (void)
{
  arValue_List l = NIL;
  __10();
  l = arValue_list();
  if ((*ParseJSON__1_s->ch) != ']') {
    __arValue_List_Append(l, __31());
    while ((*ParseJSON__1_s->ch) == ',') {
      __10();
      __arValue_List_Append(l, __31());
    }
  }
  __2(']');
  return l;
}

static arValue_Object __31 (void)
{
  if (__8((*ParseJSON__1_s->ch))) {
    return __14();
  }
  switch ((*ParseJSON__1_s->ch)) {
    case '{': 
      return (void*)(__24());
      break;
    case '[': 
      return (void*)(__16());
      break;
    case '\"': 
      return (void*)(__29());
      break;
    case '0': case '1': case '2': case '3': case '4': 
    case '5': case '6': case '7': case '8': case '9': 
    case '-': 
      return __18();
      break;
    default: 
      __4(1);
      return NIL;
      break;
  }
  __RETCHK((CHAR*)"arJSON", 70167);
}

arValue_Object arJSON_ParseJSON (CHAR *text, INTEGER text__len, INTEGER *err, SET features)
{
  INTEGER pos, length;
  CHAR ch;
  struct ParseJSON__1 _s;
  arValue_Object __retval;
  _s.text = (void*)text; _s.text__len = text__len;
  _s.err = err;
  _s.features = &features;
  _s.pos = &pos;
  _s.length = &length;
  _s.ch = &ch;
  _s.lnk = ParseJSON__1_s;
  ParseJSON__1_s = &_s;
  length = arStrings_Length((void*)text, text__len);
  pos = 0;
  __10();
  *err = 0;
  __retval = __31();
  ParseJSON__1_s = _s.lnk;
  ;
  return __retval;
}

/*----------------------------------------------------------------------------*/
arValue_String arJSON_ReadFile (CHAR *name, INTEGER name__len)
{
  CHAR ch;
  Files_File f = NIL;
  Files_Rider r = {0};
  arText_Buffer s = {0};
  f = Files_Old((void*)name, name__len);
  if (f == NIL) {
    return NIL;
  }
  Files_Set(&r, Files_Rider__typ, f, 0);
  __arText_Buffer_Init(&s, arText_Buffer__typ, 128);
  for (;;) {
    Files_ReadChar(&r, Files_Rider__typ, &ch);
    if (ch == 0x00) {
      Files_Close(f);
      return arValue_strb(&s, arText_Buffer__typ);
    }
    __arText_Stream_Char((void*)&s, arText_Buffer__typ, ch);
  }
  __RETCHK((CHAR*)"arJSON", 77580);
}

/*----------------------------------------------------------------------------*/
arValue_Object arJSON_ParseString (CHAR *text, INTEGER text__len)
{
  arValue_Object result = NIL;
  INTEGER res;
  __DUP(text, text__len);
  result = arJSON_ParseJSON((void*)text, text__len, &res, 0x03);
  if (res != 0) {
    return NIL;
  }
  return result;
}

/*----------------------------------------------------------------------------*/
arValue_Object arJSON_ReadJSON (CHAR *name, INTEGER name__len)
{
  arValue_String text = NIL;
  text = arJSON_ReadFile((void*)name, name__len);
  if (text == NIL) {
    return NIL;
  }
  return arJSON_ParseString(text->value->data, text->value->len[0]);
}

/*----------------------------------------------------------------------------*/

export void *arJSON__init (void)
{
  __DEFMOD;
  __IMPORT(Files__init);
  __IMPORT(arOut__init);
  __IMPORT(arStrings__init);
  __IMPORT(arText__init);
  __IMPORT(arValue__init);
  __REGMOD("arJSON", 0);
/* BEGIN */
  __ENDMOD;
}
