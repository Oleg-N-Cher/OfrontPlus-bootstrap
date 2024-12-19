/* Ofront+ 1.0 -sxtapC -48 */
#include "SYSTEM.oh"
#include "Heap.oh"
#include "Platform.oh"
#include "Console.oh"

typedef
  void (*Kernel_HaltProcedure)(INTEGER, INTEGER, INTEGER);

typedef
  void (*Kernel_SignalHandler)(INTEGER);


export INTEGER Kernel_HaltCode;


export void Kernel_Assert (INTEGER code, INTEGER mod, INTEGER pos);
static void Kernel_DisplayHaltCode (INTEGER code);
export void Kernel_Exit (INTEGER code);
export void Kernel_Halt (INTEGER code, INTEGER mod, INTEGER pos);
static void Kernel_OutModName (INTEGER s, INTEGER pos);
export void Kernel_SetAssert (Kernel_HaltProcedure p);
export void Kernel_SetHalt (Kernel_HaltProcedure p);

extern void (*SYSTEM_AssertHandler)(INTEGER code, SYSTEM_ADRINT mod, INTEGER pos);
extern void (*SYSTEM_HaltHandler)(INTEGER code, SYSTEM_ADRINT mod, INTEGER pos);
#define Kernel_SetAssertHandler(p)  SYSTEM_AssertHandler = p
#define Kernel_SetBadInstructionHandler(h)  SystemSetBadInstructionHandler(h)
#define Kernel_SetHaltHandler(p)  SYSTEM_HaltHandler = p
#define Kernel_SetInterruptHandler(h)  SystemSetInterruptHandler(h)
#define Kernel_SetQuitHandler(h)  SystemSetQuitHandler(h)

/*============================================================================*/

static void Kernel_DisplayHaltCode (INTEGER code)
{
  switch (code) {
    case -1: 
      Console_String((CHAR*)"Assertion failure.", 19);
      break;
    case -2: 
      Console_String((CHAR*)"Index out of range.", 20);
      break;
    case -3: 
      Console_String((CHAR*)"Reached end of function without reaching RETURN.", 49);
      break;
    case -4: 
      Console_String((CHAR*)"CASE statement: no matching label and no ELSE.", 47);
      break;
    case -5: 
      Console_String((CHAR*)"Type guard failed.", 19);
      break;
    case -6: 
      Console_String((CHAR*)"Implicit type guard in record assignment failed.", 49);
      break;
    case -7: 
      Console_String((CHAR*)"Invalid case in WITH statement.", 32);
      break;
    case -8: 
      Console_String((CHAR*)"Value out of range.", 20);
      break;
    case -9: 
      Console_String((CHAR*)"Heap interrupted while locked, but lockdepth = 0 at unlock.", 60);
      break;
    case -10: 
      Console_String((CHAR*)"NIL access.", 12);
      break;
    case -11: 
      Console_String((CHAR*)"Alignment error.", 17);
      break;
    case -12: 
      Console_String((CHAR*)"Divide by zero.", 16);
      break;
    case -13: 
      Console_String((CHAR*)"Arithmetic overflow/underflow.", 31);
      break;
    case -14: 
      Console_String((CHAR*)"Invalid function argument.", 27);
      break;
    case -15: 
      Console_String((CHAR*)"Internal error, e.g. Type descriptor size mismatch.", 52);
      break;
    case -20: 
      Console_String((CHAR*)"Too many, or negative number of, elements in dynamic array.", 60);
      break;
    case -25: 
      Console_String((CHAR*)"Memory allocation error.", 25);
      break;
    default: 
      break;
  }
}

static void Kernel_OutModName (INTEGER s, INTEGER pos)
{
  INTEGER i;
  CHAR ch;
  Console_Ln();
  i = 0;
  __GET(s, ch, CHAR);
  while (ch != 0x00) {
    Console_Char(ch);
    i += 1;
    __GET(s + i, ch, CHAR);
  }
  Console_Char(' ');
  if (pos > 0) {
    Console_Int(__ASHR(pos, 8, INTEGER), 0);
    Console_Char(':');
    Console_Int(__MASK(pos, -256) + 1, 0);
  } else {
    Console_Int(-pos, 0);
  }
}

void Kernel_Halt (INTEGER code, INTEGER mod, INTEGER pos)
{
  Heap_FINALL();
  Kernel_HaltCode = code;
  Kernel_OutModName(mod, pos);
  Console_String((CHAR*)" Terminated by Halt(", 21);
  Console_Int(code, 0);
  Console_String((CHAR*)"). ", 4);
  if (code < 0) {
    Kernel_DisplayHaltCode(code);
  }
  Console_Ln();
  Platform_ExitOS(code);
}

/*----------------------------------------------------------------------------*/
void Kernel_Assert (INTEGER code, INTEGER mod, INTEGER pos)
{
  Heap_FINALL();
  Kernel_OutModName(mod, pos);
  Console_String((CHAR*)" Assertion failure.", 20);
  if (code != 0) {
    Console_String((CHAR*)" ASSERT code ", 14);
    Console_Int(code, 0);
    Console_Char('.');
  }
  Console_Ln();
  Platform_ExitOS(code);
}

/*----------------------------------------------------------------------------*/
void Kernel_Exit (INTEGER code)
{
  Platform_ExitOS(code);
}

/*----------------------------------------------------------------------------*/
void Kernel_SetHalt (Kernel_HaltProcedure p)
{
  Kernel_SetHaltHandler(p);
}

/*----------------------------------------------------------------------------*/
void Kernel_SetAssert (Kernel_HaltProcedure p)
{
  Kernel_SetAssertHandler(p);
}

/*----------------------------------------------------------------------------*/

export void *Kernel__init (void)
{
  __DEFMOD;
  __IMPORT(Heap__init);
  __IMPORT(Console__init);
  __IMPORT(Platform__init);
  __REGMOD("Kernel", 0);
/* BEGIN */
  Kernel_HaltCode = -128;
  Kernel_SetHaltHandler(Kernel_Halt);
  Kernel_SetAssertHandler(Kernel_Assert);
  __ENDMOD;
}
