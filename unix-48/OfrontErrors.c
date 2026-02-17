/* Ofront+ 1.0 -sC -48 */
#include "SYSTEM.oh"
#include "Console.oh"




export void OfrontErrors_LogErrMsg (SHORTINT n);


/*============================================================================*/

void OfrontErrors_LogErrMsg (SHORTINT n)
{
  switch (n) {
    case 0: 
      Console_String((CHAR*)"undeclared identifier", 22);
      break;
    case 1: 
      Console_String((CHAR*)"multiply defined identifier", 28);
      break;
    case 2: 
      Console_String((CHAR*)"illegal character in number", 28);
      break;
    case 3: 
      Console_String((CHAR*)"illegal character in string", 28);
      break;
    case 4: 
      Console_String((CHAR*)"identifier does not match procedure name", 41);
      break;
    case 5: 
      Console_String((CHAR*)"comment not closed", 19);
      break;
    case 11: 
      Console_String((CHAR*)"\"=\" expected", 13);
      break;
    case 12: 
      Console_String((CHAR*)"type definition starts with incorrect symbol", 45);
      break;
    case 13: 
      Console_String((CHAR*)"factor starts with incorrect symbol", 36);
      break;
    case 14: 
      Console_String((CHAR*)"statement starts with incorrect symbol", 39);
      break;
    case 15: 
      Console_String((CHAR*)"declaration followed by incorrect symbol", 41);
      break;
    case 16: 
      Console_String((CHAR*)"MODULE expected", 16);
      break;
    case 20: 
      Console_String((CHAR*)"\".\" missing", 12);
      break;
    case 21: 
      Console_String((CHAR*)"\",\" missing", 12);
      break;
    case 22: 
      Console_String((CHAR*)"\":\" missing", 12);
      break;
    case 24: 
      Console_String((CHAR*)"\")\" missing", 12);
      break;
    case 25: 
      Console_String((CHAR*)"\"]\" missing", 12);
      break;
    case 26: 
      Console_String((CHAR*)"\"}\" missing", 12);
      break;
    case 27: 
      Console_String((CHAR*)"OF missing", 11);
      break;
    case 28: 
      Console_String((CHAR*)"THEN missing", 13);
      break;
    case 29: 
      Console_String((CHAR*)"DO missing", 11);
      break;
    case 30: 
      Console_String((CHAR*)"TO missing", 11);
      break;
    case 32: 
      Console_String((CHAR*)"\"(\" missing", 12);
      break;
    case 33: 
      Console_String((CHAR*)"CONST, TYPE, VAR, PROCEDURE, BEGIN, or END missing", 51);
      break;
    case 34: 
      Console_String((CHAR*)"PROCEDURE, BEGIN, or END missing", 33);
      break;
    case 35: 
      Console_String((CHAR*)"\",\" or OF expected", 19);
      break;
    case 36: 
      Console_String((CHAR*)"\":=\" missing", 13);
      break;
    case 39: 
      Console_String((CHAR*)"this is not a VAR-parameter", 28);
      break;
    case 40: 
      Console_String((CHAR*)"identifier expected", 20);
      break;
    case 41: 
      Console_String((CHAR*)"\";\" missing", 12);
      break;
    case 42: 
      Console_String((CHAR*)"\"@\" missing", 12);
      break;
    case 43: 
      Console_String((CHAR*)"END missing", 12);
      break;
    case 46: 
      Console_String((CHAR*)"UNTIL missing", 14);
      break;
    case 47: 
      Console_String((CHAR*)"EXIT not within loop statement", 31);
      break;
    case 48: 
      Console_String((CHAR*)"illegally marked identifier", 28);
      break;
    case 49: 
      Console_String((CHAR*)"incorrect use of RETURN", 24);
      break;
    case 50: 
      Console_String((CHAR*)"expression should be constant", 30);
      break;
    case 51: 
      Console_String((CHAR*)"constant not an integer", 24);
      break;
    case 52: 
      Console_String((CHAR*)"identifier does not denote a type", 34);
      break;
    case 53: 
      Console_String((CHAR*)"identifier does not denote a record type", 41);
      break;
    case 54: 
      Console_String((CHAR*)"result type of procedure is not a basic type", 45);
      break;
    case 55: 
      Console_String((CHAR*)"procedure call of a function", 29);
      break;
    case 56: 
      Console_String((CHAR*)"assignment to non-variable", 27);
      break;
    case 57: 
      Console_String((CHAR*)"pointer not bound to record or array type", 42);
      break;
    case 58: 
      Console_String((CHAR*)"recursive type definition", 26);
      break;
    case 59: 
      Console_String((CHAR*)"illegal open array parameter", 29);
      break;
    case 60: 
      Console_String((CHAR*)"wrong type of case label", 25);
      break;
    case 61: 
      Console_String((CHAR*)"inadmissible type of case label", 32);
      break;
    case 62: 
      Console_String((CHAR*)"case label defined more than once", 34);
      break;
    case 63: 
      Console_String((CHAR*)"illegal value of constant", 26);
      break;
    case 64: 
      Console_String((CHAR*)"more actual than formal parameters", 35);
      break;
    case 65: 
      Console_String((CHAR*)"fewer actual than formal parameters", 36);
      break;
    case 66: 
      Console_String((CHAR*)"element types of actual array and formal open array differ", 59);
      break;
    case 67: 
      Console_String((CHAR*)"actual parameter corresponding to open array is not an array", 61);
      break;
    case 68: 
      Console_String((CHAR*)"control variable must be integer", 33);
      break;
    case 69: 
      Console_String((CHAR*)"parameter must be an integer constant", 38);
      break;
    case 70: 
      Console_String((CHAR*)"pointer or VAR / IN record required as formal receiver", 55);
      break;
    case 71: 
      Console_String((CHAR*)"pointer expected as actual receiver", 36);
      break;
    case 72: 
      Console_String((CHAR*)"procedure must be bound to a record of the same scope", 54);
      break;
    case 73: 
      Console_String((CHAR*)"procedure must have level 0", 28);
      break;
    case 74: 
      Console_String((CHAR*)"procedure unknown in base type", 31);
      break;
    case 75: 
      Console_String((CHAR*)"invalid call of base procedure", 31);
      break;
    case 76: 
      Console_String((CHAR*)"this variable (field) is read only", 35);
      break;
    case 77: 
      Console_String((CHAR*)"object is not a record", 23);
      break;
    case 78: 
      Console_String((CHAR*)"dereferenced object is not a variable", 38);
      break;
    case 79: 
      Console_String((CHAR*)"indexed object is not a variable", 33);
      break;
    case 80: 
      Console_String((CHAR*)"index expression is not an integer", 35);
      break;
    case 81: 
      Console_String((CHAR*)"index out of specified bounds", 30);
      break;
    case 82: 
      Console_String((CHAR*)"indexed variable is not an array", 33);
      break;
    case 83: 
      Console_String((CHAR*)"undefined record field", 23);
      break;
    case 84: 
      Console_String((CHAR*)"dereferenced variable is not a pointer", 39);
      break;
    case 85: 
      Console_String((CHAR*)"guard or test type is not an extension of variable type", 56);
      break;
    case 86: 
      Console_String((CHAR*)"guard or testtype is not a pointer", 35);
      break;
    case 87: 
      Console_String((CHAR*)"guarded or tested variable is neither a pointer nor a VAR- or IN-parameter record", 82);
      break;
    case 88: 
      Console_String((CHAR*)"open array not allowed as variable, record field or array element", 66);
      break;
    case 90: 
      Console_String((CHAR*)"dereferenced variable is not a character array", 47);
      break;
    case 91: 
      Console_String((CHAR*)"control variable must be local", 31);
      break;
    case 92: 
      Console_String((CHAR*)"operand of IN not an integer, or not a set", 43);
      break;
    case 93: 
      Console_String((CHAR*)"set element type is not an integer", 35);
      break;
    case 94: 
      Console_String((CHAR*)"operand of & is not of type BOOLEAN", 36);
      break;
    case 95: 
      Console_String((CHAR*)"operand of OR is not of type BOOLEAN", 37);
      break;
    case 96: 
      Console_String((CHAR*)"operand not applicable to (unary) +", 36);
      break;
    case 97: 
      Console_String((CHAR*)"operand not applicable to (unary) -", 36);
      break;
    case 98: 
      Console_String((CHAR*)"operand of ~ is not of type BOOLEAN", 36);
      break;
    case 99: 
      Console_String((CHAR*)"ASSERT fault", 13);
      break;
    case 100: 
      Console_String((CHAR*)"incompatible operands of dyadic operator", 41);
      break;
    case 101: 
      Console_String((CHAR*)"operand type inapplicable to *", 31);
      break;
    case 102: 
      Console_String((CHAR*)"operand type inapplicable to /", 31);
      break;
    case 103: 
      Console_String((CHAR*)"operand type inapplicable to DIV", 33);
      break;
    case 104: 
      Console_String((CHAR*)"operand type inapplicable to MOD", 33);
      break;
    case 105: 
      Console_String((CHAR*)"operand type inapplicable to +", 31);
      break;
    case 106: 
      Console_String((CHAR*)"operand type inapplicable to -", 31);
      break;
    case 107: 
      Console_String((CHAR*)"operand type inapplicable to = or #", 36);
      break;
    case 108: 
      Console_String((CHAR*)"operand type inapplicable to relation", 38);
      break;
    case 110: 
      Console_String((CHAR*)"operand is not a type", 22);
      break;
    case 111: 
      Console_String((CHAR*)"operand inapplicable to (this) function", 40);
      break;
    case 112: 
      Console_String((CHAR*)"operand is not a variable", 26);
      break;
    case 113: 
      Console_String((CHAR*)"incompatible assignment", 24);
      break;
    case 114: 
      Console_String((CHAR*)"string too long to be assigned", 31);
      break;
    case 115: 
      Console_String((CHAR*)"parameter doesn\'t match", 24);
      break;
    case 116: 
      Console_String((CHAR*)"number of parameters doesn\'t match", 35);
      break;
    case 117: 
      Console_String((CHAR*)"result type doesn\'t match", 26);
      break;
    case 118: 
      Console_String((CHAR*)"export mark doesn\'t match with forward declaration", 51);
      break;
    case 119: 
      Console_String((CHAR*)"redefinition textually precedes procedure bound to base type", 61);
      break;
    case 120: 
      Console_String((CHAR*)"type of expression following IF, WHILE, UNTIL or ASSERT is not BOOLEAN", 71);
      break;
    case 121: 
      Console_String((CHAR*)"called object is not a procedure (or is an interrupt procedure)", 64);
      break;
    case 122: 
      Console_String((CHAR*)"actual VAR-, IN-, or OUT-parameter is not a variable", 53);
      break;
    case 123: 
      Console_String((CHAR*)"type is not identical with that of formal VAR-, IN-, or OUT-parameter", 70);
      break;
    case 124: 
      Console_String((CHAR*)"type of result expression differs from that of procedure", 57);
      break;
    case 125: 
      Console_String((CHAR*)"type of case expression is neither INTEGER nor CHAR", 52);
      break;
    case 126: 
      Console_String((CHAR*)"this expression cannot be a type or a procedure", 48);
      break;
    case 127: 
      Console_String((CHAR*)"illegal use of object", 22);
      break;
    case 128: 
      Console_String((CHAR*)"unsatisfied forward reference", 30);
      break;
    case 129: 
      Console_String((CHAR*)"unsatisfied forward procedure", 30);
      break;
    case 130: 
      Console_String((CHAR*)"WITH clause does not specify a variable", 40);
      break;
    case 131: 
      Console_String((CHAR*)"LEN not applied to array", 25);
      break;
    case 132: 
      Console_String((CHAR*)"dimension in LEN too large or negative", 39);
      break;
    case 133: 
      Console_String((CHAR*)"function without RETURN", 24);
      break;
    case 134: 
      Console_String((CHAR*)"system flag doesn\'t match forward declaration", 46);
      break;
    case 135: 
      Console_String((CHAR*)"SYSTEM not imported", 20);
      break;
    case 136: 
      Console_String((CHAR*)"LEN applied to untagged array", 30);
      break;
    case 137: 
      Console_String((CHAR*)"unknown array length", 21);
      break;
    case 138: 
      Console_String((CHAR*)"NEW not allowed for untagged structures", 40);
      break;
    case 139: 
      Console_String((CHAR*)"test applied to untagged record", 32);
      break;
    case 140: 
      Console_String((CHAR*)"operand type inapplicable to DIV0", 34);
      break;
    case 141: 
      Console_String((CHAR*)"operand type inapplicable to REM0", 34);
      break;
    case 142: 
      Console_String((CHAR*)"tagged structures not allowed for NIL compatible var parameters", 64);
      break;
    case 145: 
      Console_String((CHAR*)"untagged open array not allowed as value parameter", 51);
      break;
    case 150: 
      Console_String((CHAR*)"key inconsistency of imported module", 37);
      break;
    case 151: 
      Console_String((CHAR*)"incorrect symbol file", 22);
      break;
    case 152: 
      Console_String((CHAR*)"symbol file of imported module not found", 41);
      break;
    case 153: 
      Console_String((CHAR*)"object or symbol file not opened (disk full\?)", 46);
      break;
    case 154: 
      Console_String((CHAR*)"recursive import not allowed", 29);
      break;
    case 155: 
      Console_String((CHAR*)"generation of new symbol file not allowed", 42);
      break;
    case 156: 
      Console_String((CHAR*)"default target machine address size and alignment used", 55);
      break;
    case 157: 
      Console_String((CHAR*)"syntax error in parameter file", 31);
      break;
    case 177: 
      Console_String((CHAR*)"IN only allowed for records and arrays", 39);
      break;
    case 178: 
      Console_String((CHAR*)"illegal attribute", 18);
      break;
    case 179: 
      Console_String((CHAR*)"abstract methods of exported records must be exported", 54);
      break;
    case 180: 
      Console_String((CHAR*)"illegal receiver type", 22);
      break;
    case 181: 
      Console_String((CHAR*)"base type is not extensible", 28);
      break;
    case 182: 
      Console_String((CHAR*)"base procedure is not extensible", 33);
      break;
    case 183: 
      Console_String((CHAR*)"non-matching export", 20);
      break;
    case 184: 
      Console_String((CHAR*)"attribute does not match with forward declaration", 50);
      break;
    case 185: 
      Console_String((CHAR*)"missing NEW attribute", 22);
      break;
    case 186: 
      Console_String((CHAR*)"illegal NEW attribute", 22);
      break;
    case 187: 
      Console_String((CHAR*)"new empty procedure in non extensible record", 45);
      break;
    case 188: 
      Console_String((CHAR*)"extensible procedure in non extensible record", 46);
      break;
    case 189: 
      Console_String((CHAR*)"illegal attribute change", 25);
      break;
    case 190: 
      Console_String((CHAR*)"record must be abstract", 24);
      break;
    case 191: 
      Console_String((CHAR*)"base type must be abstract", 27);
      break;
    case 192: 
      Console_String((CHAR*)"unimplemented abstract procedures in base types", 48);
      break;
    case 193: 
      Console_String((CHAR*)"abstract or limited records may not be allocated", 49);
      break;
    case 194: 
      Console_String((CHAR*)"no supercall allowed to abstract or empty procedures", 53);
      break;
    case 195: 
      Console_String((CHAR*)"empty procedures may not have out parameters or return a value", 63);
      break;
    case 196: 
      Console_String((CHAR*)"procedure is implement-only exported", 37);
      break;
    case 197: 
      Console_String((CHAR*)"extension of limited type must be limited", 42);
      break;
    case 200: 
      Console_String((CHAR*)"not yet implemented", 20);
      break;
    case 201: 
      Console_String((CHAR*)"lower bound of set range greater than higher bound", 51);
      break;
    case 202: 
      Console_String((CHAR*)"set element greater than MAX(SET) or less than 0", 49);
      break;
    case 203: 
      Console_String((CHAR*)"number too large", 17);
      break;
    case 204: 
      Console_String((CHAR*)"product too large", 18);
      break;
    case 205: 
      Console_String((CHAR*)"division by zero", 17);
      break;
    case 206: 
      Console_String((CHAR*)"sum too large", 14);
      break;
    case 207: 
      Console_String((CHAR*)"difference too large", 21);
      break;
    case 208: 
      Console_String((CHAR*)"overflow in arithmetic shift", 29);
      break;
    case 209: 
      Console_String((CHAR*)"case range too large", 21);
      break;
    case 210: 
      Console_String((CHAR*)"overflow in logical shift", 26);
      break;
    case 213: 
      Console_String((CHAR*)"too many cases in case statement", 33);
      break;
    case 214: 
      Console_String((CHAR*)"name collision", 15);
      break;
    case 218: 
      Console_String((CHAR*)"illegal value of parameter  (0 <= p < 256)", 43);
      break;
    case 220: 
      Console_String((CHAR*)"illegal value of parameter", 27);
      break;
    case 221: 
      Console_String((CHAR*)"too many pointers in a record", 30);
      break;
    case 222: 
      Console_String((CHAR*)"too many global pointers", 25);
      break;
    case 223: 
      Console_String((CHAR*)"too many record types", 22);
      break;
    case 225: 
      Console_String((CHAR*)"address of pointer variable too large (move forward in text)", 61);
      break;
    case 226: 
      Console_String((CHAR*)"too many exported procedures", 29);
      break;
    case 227: 
      Console_String((CHAR*)"too many imported modules", 26);
      break;
    case 228: 
      Console_String((CHAR*)"too many exported structures", 29);
      break;
    case 229: 
      Console_String((CHAR*)"too many nested records for import", 35);
      break;
    case 230: 
      Console_String((CHAR*)"too many constants (strings) in module", 39);
      break;
    case 231: 
      Console_String((CHAR*)"too many link table entries (external procedures)", 50);
      break;
    case 232: 
      Console_String((CHAR*)"too many commands in module", 28);
      break;
    case 233: 
      Console_String((CHAR*)"record extension hierarchy too high", 36);
      break;
    case 234: 
      Console_String((CHAR*)"export of recursive type not allowed", 37);
      break;
    case 240: 
      Console_String((CHAR*)"identifier too long", 20);
      break;
    case 241: 
      Console_String((CHAR*)"string too long", 16);
      break;
    case 242: 
      Console_String((CHAR*)"address overflow", 17);
      break;
    case 244: 
      Console_String((CHAR*)"cyclic type definition not allowed", 35);
      break;
    case 245: 
      Console_String((CHAR*)"guarded pointer variable may be manipulated by non-local operations; use auxiliary pointer variable", 100);
      break;
    case 265: 
      Console_String((CHAR*)"unsupported string operation", 29);
      break;
    case 301: 
      Console_String((CHAR*)"implicit type cast", 19);
      break;
    case 302: 
      Console_String((CHAR*)"guarded variable can be side-effected", 38);
      break;
    case 303: 
      Console_String((CHAR*)"GPCP extension used", 20);
      break;
    case 304: 
      Console_String((CHAR*)"Oakwood Guidelines extension used", 34);
      break;
    case 306: 
      Console_String((CHAR*)"inappropriate symbol file ignored", 34);
      break;
    case 308: 
      Console_String((CHAR*)"SYSTEM.VAL result includes memory past end of source variable", 62);
      break;
    default: __CASECHK((CHAR*)"OfrontErrors", 73983);
  }
}

/*----------------------------------------------------------------------------*/

export void *OfrontErrors__init (void)
{
  __DEFMOD;
  __IMPORT(Console__init);
  __REGMOD("OfrontErrors", 0);
/* BEGIN */
  __ENDMOD;
}
