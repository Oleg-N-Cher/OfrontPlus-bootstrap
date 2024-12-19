/* Ofront+ 1.0 -mC -48 */
#include "SYSTEM.oh"
#include "Heap.oh"
#include "Kernel.oh"
#include "OfrontOPP.oh"
#include "OfrontOPT.oh"
#include "OfrontOPS.oh"
#include "OfrontOPB.oh"
#include "OfrontOPV.oh"
#include "OfrontOPC.oh"
#include "OfrontOPM.oh"




export void OfrontCmd_Module (BOOLEAN *done);
export void OfrontCmd_Translate (void);
static void OfrontCmd_Trap (INTEGER sig);


/*============================================================================*/

static void OfrontCmd_Trap (INTEGER sig)
{
  Heap_FINALL();
  if (sig == 3) {
    Kernel_Exit(1);
  } else {
    if (sig == 4 && Kernel_HaltCode == -15) {
      OfrontOPM_LogWStr((CHAR*)" --- Ofront+: internal error", 29);
      OfrontOPM_LogWLn();
    }
    Kernel_Exit(2);
  }
}

void OfrontCmd_Module (BOOLEAN *done)
{
  BOOLEAN ext, new, main;
  OfrontOPT_Node p = NIL;
  OfrontOPV_Init();
  OfrontOPP_Module(&p, OfrontOPM_opt);
  if (OfrontOPM_noerr) {
    OfrontOPV_AdrAndSize(OfrontOPT_topScope);
    main = __IN(10, OfrontOPM_opt) && __STRCMPCC(OfrontOPM_modName, (CHAR*)"SYSTEM", 7, (CHAR*)"OfrontCmd", 6719) != 0;
    if (!main) {
      OfrontOPT_Export(&ext, &new);
    }
    if (OfrontOPM_noerr) {
      OfrontOPM_OpenFiles((void*)OfrontOPT_SelfName, 48);
      OfrontOPV_Module(p);
      if (OfrontOPM_noerr) {
        if (main) {
          OfrontOPM_DeleteNewSym();
          OfrontOPM_LogWStr((CHAR*)"  main program", 15);
        } else {
          if (new) {
            OfrontOPM_LogWStr((CHAR*)"  new symbol file", 18);
            OfrontOPM_RegisterNewSym();
          } else if (ext) {
            OfrontOPM_LogWStr((CHAR*)"  extended symbol file", 23);
            OfrontOPM_RegisterNewSym();
          }
        }
      } else {
        OfrontOPM_DeleteNewSym();
      }
    }
  }
  OfrontOPM_CloseFiles();
  OfrontOPT_Close();
  OfrontOPM_LogWLn();
  *done = OfrontOPM_noerr;
  if (OfrontOPM_warning156) {
    OfrontOPM_Mark(-156, -1);
  }
}

/*----------------------------------------------------------------------------*/
void OfrontCmd_Translate (void)
{
  BOOLEAN done;
  OfrontOPM_OpenPar((CHAR*)"Ofront+ (TM) - Oberon family of languages to C Translator v1.0", 63, (CHAR*)"ofront+", 8);
  for (;;) {
    OfrontOPM_Init((CHAR*)"translating", 12, &done);
    if (!done) {
      if (!OfrontOPM_noerr) {
        Heap_FINALL();
        Kernel_Exit(1);
      }
      break;
    }
    OfrontOPM_InitOptions();
    Heap_GC(0);
    OfrontCmd_Module(&done);
    if (!done) {
      Heap_FINALL();
      Kernel_Exit(1);
    }
  }
}

/*----------------------------------------------------------------------------*/

int main (int argc, char **argv)
{
  __INIT(argc, argv);
  __IMPORT(Heap__init);
  __IMPORT(Kernel__init);
  __IMPORT(OfrontOPB__init);
  __IMPORT(OfrontOPC__init);
  __IMPORT(OfrontOPM__init);
  __IMPORT(OfrontOPP__init);
  __IMPORT(OfrontOPT__init);
  __IMPORT(OfrontOPV__init);
  __REGMAIN("OfrontCmd", 0);
  __REGCMD("Translate", OfrontCmd_Translate);
/* BEGIN */
  Kernel_SetInterruptHandler(OfrontCmd_Trap);
  Kernel_SetQuitHandler(OfrontCmd_Trap);
  Kernel_SetBadInstructionHandler(OfrontCmd_Trap);
  OfrontOPB_typSize = OfrontOPV_TypSize;
  OfrontOPT_typSize = OfrontOPV_TypSize;
  OfrontCmd_Translate();
  __FINI;
}
