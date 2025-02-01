/* Ofront+ 1.0 -s2 -48 */
#include "SYSTEM.oh"
#include "arText.oh"
#include "arFile.oh"
#include "arC.oh"


static arText_StreamWriter arOut_writer;


export void arOut_Bool (BOOLEAN value);
export void arOut_Char (CHAR value);
export void arOut_Flush (void);
export void arOut_Hex (INTEGER value);
export void arOut_Int (INTEGER value);
export void arOut_Ln (void);
export void arOut_Real (REAL value);
export void arOut_String (CHAR *text, INTEGER text__len);


/*============================================================================*/

void arOut_String (CHAR *text, INTEGER text__len)
{
  __arText_Stream_String((void*)&arOut_writer, arText_StreamWriter__typ, (void*)text, text__len);
}

/*----------------------------------------------------------------------------*/
void arOut_Int (INTEGER value)
{
  __arText_Writer_Integer((void*)&arOut_writer, arText_StreamWriter__typ, value);
}

/*----------------------------------------------------------------------------*/
void arOut_Hex (INTEGER value)
{
  __arText_Writer_Hex((void*)&arOut_writer, arText_StreamWriter__typ, value);
}

/*----------------------------------------------------------------------------*/
void arOut_Char (CHAR value)
{
  __arText_Stream_Char((void*)&arOut_writer, arText_StreamWriter__typ, value);
}

/*----------------------------------------------------------------------------*/
void arOut_Real (REAL value)
{
  __arText_Writer_Real((void*)&arOut_writer, arText_StreamWriter__typ, value);
}

/*----------------------------------------------------------------------------*/
void arOut_Ln (void)
{
  __arText_Writer_Ln((void*)&arOut_writer, arText_StreamWriter__typ);
}

/*----------------------------------------------------------------------------*/
void arOut_Flush (void)
{
  __arText_Stream_Flush((void*)&arOut_writer, arText_StreamWriter__typ);
}

/*----------------------------------------------------------------------------*/
void arOut_Bool (BOOLEAN value)
{
  __arText_Writer_Boolean((void*)&arOut_writer, arText_StreamWriter__typ, value);
}

/*----------------------------------------------------------------------------*/
static void EnumPtrs(void (*P)(void*))
{
  __ENUMR(&arOut_writer, arText_StreamWriter__typ, 32, 1, P);
}


export void *arOut__init (void)
{
  __DEFMOD;
  __IMPORT(arFile__init);
  __IMPORT(arText__init);
  __REGMOD("arOut", EnumPtrs);
  __REGCMD("Flush", arOut_Flush);
  __REGCMD("Ln", arOut_Ln);
/* BEGIN */
  __arText_StreamWriter_Init(&arOut_writer, arText_StreamWriter__typ, (void*)__arFile_File_GetStream(arFile_out));
  __ENDMOD;
}
