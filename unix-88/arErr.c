/* Ofront+ 1.0 -s2 -88 */
#include "SYSTEM.oh"
#include "arText.oh"
#include "arFile.oh"
#include "arC.oh"


static arText_StreamWriter arErr_writer;


export void arErr_Bool (BOOLEAN value);
export void arErr_Char (CHAR value);
export void arErr_Flush (void);
export void arErr_Hex (INTEGER value);
export void arErr_Int (INTEGER value);
export void arErr_Ln (void);
export void arErr_Real (REAL value);
export void arErr_String (CHAR *text, INTEGER text__len);


/*============================================================================*/

void arErr_String (CHAR *text, INTEGER text__len)
{
  __arText_Stream_String((void*)&arErr_writer, arText_StreamWriter__typ, (void*)text, text__len);
}

/*----------------------------------------------------------------------------*/
void arErr_Int (INTEGER value)
{
  __arText_Writer_Integer((void*)&arErr_writer, arText_StreamWriter__typ, value);
}

/*----------------------------------------------------------------------------*/
void arErr_Hex (INTEGER value)
{
  __arText_Writer_Hex((void*)&arErr_writer, arText_StreamWriter__typ, value);
}

/*----------------------------------------------------------------------------*/
void arErr_Char (CHAR value)
{
  __arText_Stream_Char((void*)&arErr_writer, arText_StreamWriter__typ, value);
}

/*----------------------------------------------------------------------------*/
void arErr_Real (REAL value)
{
  __arText_Writer_Real((void*)&arErr_writer, arText_StreamWriter__typ, value);
}

/*----------------------------------------------------------------------------*/
void arErr_Ln (void)
{
  __arText_Writer_Ln((void*)&arErr_writer, arText_StreamWriter__typ);
}

/*----------------------------------------------------------------------------*/
void arErr_Flush (void)
{
  __arText_Stream_Flush((void*)&arErr_writer, arText_StreamWriter__typ);
}

/*----------------------------------------------------------------------------*/
void arErr_Bool (BOOLEAN value)
{
  __arText_Writer_Boolean((void*)&arErr_writer, arText_StreamWriter__typ, value);
}

/*----------------------------------------------------------------------------*/
static void EnumPtrs(void (*P)(void*))
{
  __ENUMR(&arErr_writer, arText_StreamWriter__typ, 40, 1, P);
}


export void *arErr__init (void)
{
  __DEFMOD;
  __IMPORT(arFile__init);
  __IMPORT(arText__init);
  __REGMOD("arErr", EnumPtrs);
  __REGCMD("Flush", arErr_Flush);
  __REGCMD("Ln", arErr_Ln);
/* BEGIN */
  __arText_StreamWriter_Init(&arErr_writer, arText_StreamWriter__typ, (void*)__arFile_File_GetStream(arFile_err));
  __ENDMOD;
}
