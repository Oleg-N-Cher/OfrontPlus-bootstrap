/* Ofront+ 1.0 -sC -48 */
#include "SYSTEM.oh"

typedef
  struct CHAR8_ARRAY *ecoParser_StrPtr;

typedef
  struct ecoParser_CtxNode *ecoParser_CtxPtr;

typedef
  struct ecoParser_Node *ecoParser_NodePtr;

typedef
  struct ecoParser_Parser {
    ecoParser_StrPtr inpBuf;
    INTEGER inpIdx, inpAvl;
    ecoParser_CtxPtr ctxNow;
    struct ecoParser_CtxNode_PTR_ARRAY *ctxStk;
    INTEGER ctxIdx;
    ecoParser_NodePtr nodFnd;
  } ecoParser_Parser;

export void ecoParser_Parser_Exec (ecoParser_Parser *prs, void **prs__typ);
export void ecoParser_Parser_Init (ecoParser_Parser *prs, void **prs__typ, ecoParser_StrPtr buf, INTEGER bufLen, INTEGER ctxDeep);
export void ecoParser_Parser_PopContext (ecoParser_Parser *prs, void **prs__typ);
export void ecoParser_Parser_PushContext (ecoParser_Parser *prs, void **prs__typ, ecoParser_CtxPtr ctx);
export void ecoParser_Parser_SetContextByPtr (ecoParser_Parser *prs, void **prs__typ, ecoParser_CtxPtr ctx);
#define __ecoParser_Parser_Exec(prs, prs__typ) __SEND(prs__typ, ecoParser_Parser_Exec, 1, void(*)(ecoParser_Parser*, void **), (prs, prs__typ))
#define __ecoParser_Parser_Init(prs, prs__typ, buf, bufLen, ctxDeep) __SEND(prs__typ, ecoParser_Parser_Init, 2, void(*)(ecoParser_Parser*, void **, ecoParser_StrPtr, INTEGER, INTEGER), (prs, prs__typ, buf, bufLen, ctxDeep))
#define __ecoParser_Parser_PopContext(prs, prs__typ) __SEND(prs__typ, ecoParser_Parser_PopContext, 3, void(*)(ecoParser_Parser*, void **), (prs, prs__typ))
#define __ecoParser_Parser_PushContext(prs, prs__typ, ctx) __SEND(prs__typ, ecoParser_Parser_PushContext, 4, void(*)(ecoParser_Parser*, void **, ecoParser_CtxPtr), (prs, prs__typ, ctx))
#define __ecoParser_Parser_SetContextByPtr(prs, prs__typ, ctx) __SEND(prs__typ, ecoParser_Parser_SetContextByPtr, 5, void(*)(ecoParser_Parser*, void **, ecoParser_CtxPtr), (prs, prs__typ, ctx))

typedef
  BOOLEAN (*ecoParser_Comparer)(ecoParser_Parser*, void **);

typedef
  void (*ecoParser_Method)(ecoParser_Parser*, void **);

typedef
  struct ecoParser_Node {
    ecoParser_NodePtr nextNode;
    ecoParser_Comparer comparer;
    INTEGER nameLen;
    ecoParser_StrPtr name;
    ecoParser_Method method;
  } ecoParser_Node;

typedef
  struct ecoParser_CtxNode { /* ecoParser_Node */
    ecoParser_NodePtr nextNode;
    ecoParser_Comparer comparer;
    INTEGER nameLen;
    ecoParser_StrPtr name;
    ecoParser_Method method;
    ecoParser_NodePtr chldNode;
    ecoParser_Method NotFound;
  } ecoParser_CtxNode;

export void ecoParser_CtxNode_AddContext (ecoParser_CtxNode *ctx, void **ctx__typ, ecoParser_Comparer cmp, CHAR *name, INTEGER name__len, ecoParser_Method notfound);
#define __ecoParser_CtxNode_AddContext(ctx, ctx__typ, cmp, name, name__len, notfound) __SEND(ctx__typ, ecoParser_CtxNode_AddContext, 1, void(*)(ecoParser_CtxNode*, void **, ecoParser_Comparer, CHAR*, INTEGER , ecoParser_Method), (ctx, ctx__typ, cmp, name, name__len, notfound))

typedef
  struct ecoParser_MethodNode { /* ecoParser_Node */
    ecoParser_NodePtr nextNode;
    ecoParser_Comparer comparer;
    INTEGER nameLen;
    ecoParser_StrPtr name;
    ecoParser_Method method;
  } ecoParser_MethodNode;

typedef
  ecoParser_Parser *ecoParser_ParserPtr;

typedef
  struct ecoParser_SetCtxNode { /* ecoParser_Node */
    ecoParser_NodePtr nextNode;
    ecoParser_Comparer comparer;
    INTEGER nameLen;
    ecoParser_StrPtr name;
    ecoParser_Method method;
    ecoParser_CtxPtr setCtx;
  } ecoParser_SetCtxNode;

typedef
  struct ecoParser_Tree {
    ecoParser_CtxPtr root, this, addTo;
  } ecoParser_Tree;

export void ecoParser_Tree_AddContext (ecoParser_Tree *tree, void **tree__typ, ecoParser_Comparer cmp, CHAR *name, INTEGER name__len, ecoParser_Method notfound);
export void ecoParser_Tree_AddMethod (ecoParser_Tree *tree, void **tree__typ, ecoParser_Comparer cmp, CHAR *name, INTEGER name__len, ecoParser_Method meth);
export void ecoParser_Tree_AddPushContext (ecoParser_Tree *tree, void **tree__typ, ecoParser_Comparer cmp, CHAR *name, INTEGER name__len, ecoParser_Method notfound);
export void ecoParser_Tree_AddSetContext (ecoParser_Tree *tree, void **tree__typ, ecoParser_Comparer cmp, CHAR *name, INTEGER name__len, ecoParser_CtxPtr setContext);
export void ecoParser_Tree_Init (ecoParser_Tree *tree, void **tree__typ);
export void ecoParser_Tree_To (ecoParser_Tree *tree, void **tree__typ, ecoParser_CtxPtr ctx);
#define __ecoParser_Tree_AddContext(tree, tree__typ, cmp, name, name__len, notfound) __SEND(tree__typ, ecoParser_Tree_AddContext, 1, void(*)(ecoParser_Tree*, void **, ecoParser_Comparer, CHAR*, INTEGER , ecoParser_Method), (tree, tree__typ, cmp, name, name__len, notfound))
#define __ecoParser_Tree_AddMethod(tree, tree__typ, cmp, name, name__len, meth) __SEND(tree__typ, ecoParser_Tree_AddMethod, 2, void(*)(ecoParser_Tree*, void **, ecoParser_Comparer, CHAR*, INTEGER , ecoParser_Method), (tree, tree__typ, cmp, name, name__len, meth))
#define __ecoParser_Tree_AddPushContext(tree, tree__typ, cmp, name, name__len, notfound) __SEND(tree__typ, ecoParser_Tree_AddPushContext, 3, void(*)(ecoParser_Tree*, void **, ecoParser_Comparer, CHAR*, INTEGER , ecoParser_Method), (tree, tree__typ, cmp, name, name__len, notfound))
#define __ecoParser_Tree_AddSetContext(tree, tree__typ, cmp, name, name__len, setContext) __SEND(tree__typ, ecoParser_Tree_AddSetContext, 4, void(*)(ecoParser_Tree*, void **, ecoParser_Comparer, CHAR*, INTEGER , ecoParser_CtxPtr), (tree, tree__typ, cmp, name, name__len, setContext))
#define __ecoParser_Tree_Init(tree, tree__typ) __SEND(tree__typ, ecoParser_Tree_Init, 5, void(*)(ecoParser_Tree*, void **), (tree, tree__typ))
#define __ecoParser_Tree_To(tree, tree__typ, ctx) __SEND(tree__typ, ecoParser_Tree_To, 6, void(*)(ecoParser_Tree*, void **, ecoParser_CtxPtr), (tree, tree__typ, ctx))


#ifndef CHAR8_ARRAY_DEF
#define CHAR8_ARRAY_DEF
typedef struct CHAR8_ARRAY {
  INTEGER len[1];
  CHAR data[1];
} CHAR8_ARRAY;
#endif 

#ifndef ecoParser_CtxNode_PTR_ARRAY_DEF
#define ecoParser_CtxNode_PTR_ARRAY_DEF
typedef struct ecoParser_CtxNode_PTR_ARRAY {
  INTEGER len[1];
  ecoParser_CtxNode *data[1];
} ecoParser_CtxNode_PTR_ARRAY;
#endif 


export void **ecoParser_Tree__typ;
export void **ecoParser_Parser__typ;
export void **ecoParser_Node__typ;
export void **ecoParser_CtxNode__typ;
export void **ecoParser_MethodNode__typ;
export void **ecoParser_SetCtxNode__typ;

export BOOLEAN ecoParser_Always (ecoParser_Parser *prs, void **prs__typ);
export CHAR ecoParser_Cap (CHAR c);
export BOOLEAN ecoParser_Contains (ecoParser_Parser *prs, void **prs__typ);
static void ecoParser_Ctxt (ecoParser_Parser *prs, void **prs__typ);
export BOOLEAN ecoParser_EquAbs (ecoParser_Parser *prs, void **prs__typ);
export BOOLEAN ecoParser_EquCap (ecoParser_Parser *prs, void **prs__typ);
export BOOLEAN ecoParser_IsData (ecoParser_Parser *prs, void **prs__typ);
export BOOLEAN ecoParser_IsNull (ecoParser_Parser *prs, void **prs__typ);
export INTEGER ecoParser_Length (CHAR *str, INTEGER str__len);
export BOOLEAN ecoParser_Never (ecoParser_Parser *prs, void **prs__typ);
export ecoParser_CtxPtr ecoParser_NewContext (ecoParser_Comparer cmp, CHAR *name, INTEGER name__len, ecoParser_Method notfound);
export ecoParser_ParserPtr ecoParser_NewParser (ecoParser_StrPtr buf, INTEGER bufLen, INTEGER ctxDeep);
export void ecoParser_None (ecoParser_Parser *prs, void **prs__typ);
export INTEGER ecoParser_Pos (CHAR *str, INTEGER str__len, CHAR *subStr, INTEGER subStr__len, INTEGER pos);
export void ecoParser_Push (ecoParser_Parser *prs, void **prs__typ);
static void ecoParser_SetCtx (ecoParser_Parser *prs, void **prs__typ);


/*============================================================================*/

void ecoParser_Parser_SetContextByPtr (ecoParser_Parser *prs, void **prs__typ, ecoParser_CtxPtr ctx)
{
  (*prs).ctxNow = ctx;
}

/*----------------------------------------------------------------------------*/
void ecoParser_Parser_PushContext (ecoParser_Parser *prs, void **prs__typ, ecoParser_CtxPtr ctx)
{
  __ASSERT((*prs).ctxIdx < (*prs).ctxStk->len[0], 0, (CHAR*)"ecoParser", 15164);
  ((*prs).ctxStk->data)[__X((*prs).ctxIdx, (*prs).ctxStk->len[0], (CHAR*)"ecoParser", 15397)] = (*prs).ctxNow;
  (*prs).ctxIdx += 1;
  (*prs).ctxNow = ctx;
}

/*----------------------------------------------------------------------------*/
void ecoParser_Parser_PopContext (ecoParser_Parser *prs, void **prs__typ)
{
  __ASSERT((*prs).ctxIdx != 0, 0, (CHAR*)"ecoParser", 17198);
  (*prs).ctxIdx -= 1;
  (*prs).ctxNow = ((*prs).ctxStk->data)[__X((*prs).ctxIdx, (*prs).ctxStk->len[0], (CHAR*)"ecoParser", 17701)];
}

/*----------------------------------------------------------------------------*/
INTEGER ecoParser_Length (CHAR *str, INTEGER str__len)
{
  INTEGER len, maxLen;
  maxLen = (SHORTINT)str__len;
  len = 0;
  while (len < maxLen && str[__X(len, str__len, (CHAR*)"ecoParser", 21031)] != 0x00) {
    len += 1;
  }
  return len;
}

/*----------------------------------------------------------------------------*/
CHAR ecoParser_Cap (CHAR c)
{
  return __CAP(c);
}

/*----------------------------------------------------------------------------*/
INTEGER ecoParser_Pos (CHAR *str, INTEGER str__len, CHAR *subStr, INTEGER subStr__len, INTEGER pos)
{
  INTEGER i;
  if (pos == 0 || pos <= ecoParser_Length(str, str__len) - ecoParser_Length(subStr, subStr__len)) {
    while (str[__X(pos, str__len, (CHAR*)"ecoParser", 24853)] != 0x00) {
      i = 0;
      while (str[__X(pos + i, str__len, (CHAR*)"ecoParser", 25396)] == subStr[__X(i, subStr__len, (CHAR*)"ecoParser", 25396)] && subStr[__X(i, subStr__len, (CHAR*)"ecoParser", 25396)] != 0x00) {
        i += 1;
      }
      if (subStr[__X(i, subStr__len, (CHAR*)"ecoParser", 25640)] == 0x00) {
        return pos;
      }
      pos += 1;
    }
  }
  return -1;
}

/*----------------------------------------------------------------------------*/
void ecoParser_None (ecoParser_Parser *prs, void **prs__typ)
{
}

/*----------------------------------------------------------------------------*/
static void ecoParser_Ctxt (ecoParser_Parser *prs, void **prs__typ)
{
  (*prs).ctxNow = __GUARDP((*prs).nodFnd, ecoParser_CtxNode, 1);
}

typedef
  ecoParser_SetCtxNode *__31;

static void ecoParser_SetCtx (ecoParser_Parser *prs, void **prs__typ)
{
  (*prs).ctxNow = (__GUARDP((*prs).nodFnd, ecoParser_SetCtxNode, 1))->setCtx;
}

void ecoParser_Push (ecoParser_Parser *prs, void **prs__typ)
{
  __ecoParser_Parser_PushContext(prs, prs__typ, (*prs).ctxNow);
  (*prs).ctxNow = __GUARDP((*prs).nodFnd, ecoParser_CtxNode, 1);
}

/*----------------------------------------------------------------------------*/
void ecoParser_Tree_Init (ecoParser_Tree *tree, void **tree__typ)
{
  (*tree).root = NIL;
  (*tree).this = NIL;
  (*tree).addTo = NIL;
}

/*----------------------------------------------------------------------------*/
void ecoParser_Tree_To (ecoParser_Tree *tree, void **tree__typ, ecoParser_CtxPtr ctx)
{
  (*tree).addTo = ctx;
}

/*----------------------------------------------------------------------------*/
void ecoParser_Tree_AddContext (ecoParser_Tree *tree, void **tree__typ, ecoParser_Comparer cmp, CHAR *name, INTEGER name__len, ecoParser_Method notfound)
{
  ecoParser_CtxPtr newCtx = NIL;
  __NEW(newCtx, ecoParser_CtxNode);
  if ((*tree).addTo != NIL) {
    newCtx->nextNode = (*tree).addTo->chldNode;
    (*tree).addTo->chldNode = (ecoParser_NodePtr)newCtx;
  } else {
    newCtx->nextNode = NIL;
  }
  newCtx->comparer = cmp;
  newCtx->nameLen = ecoParser_Length(name, name__len);
  newCtx->name = __NEWARR(NIL, 1, 1, 1, 1, (SYSTEM_ARRLEN)(name__len));
  __STRCOPYCC(name, newCtx->name->data, __MIN(newCtx->name->len[0], name__len), (CHAR*)"ecoParser", 40471);
  newCtx->method = ecoParser_Ctxt;
  newCtx->chldNode = NIL;
  newCtx->NotFound = notfound;
  if ((*tree).this == NIL) {
    (*tree).root = newCtx;
  }
  (*tree).this = newCtx;
}

/*----------------------------------------------------------------------------*/
void ecoParser_CtxNode_AddContext (ecoParser_CtxNode *ctx, void **ctx__typ, ecoParser_Comparer cmp, CHAR *name, INTEGER name__len, ecoParser_Method notfound)
{
  ecoParser_CtxPtr newCtx = NIL;
  __NEW(newCtx, ecoParser_CtxNode);
  newCtx->nextNode = (*ctx).chldNode;
  (*ctx).chldNode = (ecoParser_NodePtr)newCtx;
  newCtx->comparer = cmp;
  newCtx->nameLen = ecoParser_Length(name, name__len);
  newCtx->name = __NEWARR(NIL, 1, 1, 1, 1, (SYSTEM_ARRLEN)(name__len));
  __STRCOPYCC(name, newCtx->name->data, __MIN(newCtx->name->len[0], name__len), (CHAR*)"ecoParser", 45847);
  newCtx->method = ecoParser_Ctxt;
  newCtx->chldNode = NIL;
  newCtx->NotFound = notfound;
}

/*----------------------------------------------------------------------------*/
ecoParser_CtxPtr ecoParser_NewContext (ecoParser_Comparer cmp, CHAR *name, INTEGER name__len, ecoParser_Method notfound)
{
  ecoParser_CtxPtr newCtx = NIL;
  __NEW(newCtx, ecoParser_CtxNode);
  newCtx->comparer = cmp;
  newCtx->nameLen = ecoParser_Length(name, name__len);
  newCtx->name = __NEWARR(NIL, 1, 1, 1, 1, (SYSTEM_ARRLEN)(name__len));
  __STRCOPYCC(name, newCtx->name->data, __MIN(newCtx->name->len[0], name__len), (CHAR*)"ecoParser", 49687);
  newCtx->method = ecoParser_Ctxt;
  newCtx->chldNode = NIL;
  newCtx->NotFound = notfound;
  return newCtx;
}

/*----------------------------------------------------------------------------*/
void ecoParser_Tree_AddPushContext (ecoParser_Tree *tree, void **tree__typ, ecoParser_Comparer cmp, CHAR *name, INTEGER name__len, ecoParser_Method notfound)
{
  __ecoParser_Tree_AddContext(tree, tree__typ, cmp, name, name__len, notfound);
  (*tree).this->method = ecoParser_Push;
}

/*----------------------------------------------------------------------------*/
void ecoParser_Tree_AddMethod (ecoParser_Tree *tree, void **tree__typ, ecoParser_Comparer cmp, CHAR *name, INTEGER name__len, ecoParser_Method meth)
{
  ecoParser_MethodNode *newMeth = NIL;
  __NEW(newMeth, ecoParser_MethodNode);
  newMeth->nextNode = (*tree).addTo->chldNode;
  (*tree).addTo->chldNode = (ecoParser_NodePtr)newMeth;
  newMeth->comparer = cmp;
  newMeth->nameLen = ecoParser_Length(name, name__len);
  newMeth->name = __NEWARR(NIL, 1, 1, 1, 1, (SYSTEM_ARRLEN)(name__len));
  __STRCOPYCC(name, newMeth->name->data, __MIN(newMeth->name->len[0], name__len), (CHAR*)"ecoParser", 56089);
  newMeth->method = meth;
}

/*----------------------------------------------------------------------------*/
void ecoParser_Tree_AddSetContext (ecoParser_Tree *tree, void **tree__typ, ecoParser_Comparer cmp, CHAR *name, INTEGER name__len, ecoParser_CtxPtr setContext)
{
  ecoParser_SetCtxNode *newSetCtx = NIL;
  __NEW(newSetCtx, ecoParser_SetCtxNode);
  newSetCtx->nextNode = (*tree).addTo->chldNode;
  (*tree).addTo->chldNode = (ecoParser_NodePtr)newSetCtx;
  newSetCtx->comparer = cmp;
  newSetCtx->nameLen = ecoParser_Length(name, name__len);
  newSetCtx->name = __NEWARR(NIL, 1, 1, 1, 1, (SYSTEM_ARRLEN)(name__len));
  __STRCOPYCC(name, newSetCtx->name->data, __MIN(newSetCtx->name->len[0], name__len), (CHAR*)"ecoParser", 59930);
  newSetCtx->method = ecoParser_SetCtx;
  newSetCtx->setCtx = setContext;
}

/*----------------------------------------------------------------------------*/
BOOLEAN ecoParser_Never (ecoParser_Parser *prs, void **prs__typ)
{
  return 0;
}

/*----------------------------------------------------------------------------*/
BOOLEAN ecoParser_Always (ecoParser_Parser *prs, void **prs__typ)
{
  return 1;
}

/*----------------------------------------------------------------------------*/
BOOLEAN ecoParser_IsNull (ecoParser_Parser *prs, void **prs__typ)
{
  if ((*prs).inpAvl > 0 && ((*prs).inpBuf->data)[__X((*prs).inpIdx, (*prs).inpBuf->len[0], (CHAR*)"ecoParser", 65796)] == 0x00) {
    (*prs).inpIdx += 1;
    (*prs).inpAvl -= 1;
    return 1;
  }
  return 0;
}

/*----------------------------------------------------------------------------*/
BOOLEAN ecoParser_IsData (ecoParser_Parser *prs, void **prs__typ)
{
  return (*prs).inpAvl > 0;
}

/*----------------------------------------------------------------------------*/
BOOLEAN ecoParser_Contains (ecoParser_Parser *prs, void **prs__typ)
{
  INTEGER pos;
  ecoParser_StrPtr _ptr__17 = NIL;
  ecoParser_StrPtr _ptr__16 = NIL;
  if ((*prs).nodFnd->nameLen > (*prs).inpAvl) {
    return 0;
  }
  return (_ptr__17 = (*prs).inpBuf, 
    _ptr__16 = (*prs).nodFnd->name, 
    ecoParser_Pos(_ptr__17->data, _ptr__17->len[0], _ptr__16->data, _ptr__16->len[0], 0)) != -1;
}

/*----------------------------------------------------------------------------*/
BOOLEAN ecoParser_EquAbs (ecoParser_Parser *prs, void **prs__typ)
{
  INTEGER wrdLength, tmpInpIdx, tmpNodeIdx;
  if ((*prs).nodFnd->nameLen > (*prs).inpAvl) {
    return 0;
  }
  wrdLength = (*prs).nodFnd->nameLen;
  tmpInpIdx = (*prs).inpIdx;
  tmpNodeIdx = 0;
  while (wrdLength > 0) {
    if (((*prs).inpBuf->data)[__X(tmpInpIdx, (*prs).inpBuf->len[0], (CHAR*)"ecoParser", 72728)] != ((*prs).nodFnd->name->data)[__X(tmpNodeIdx, (*prs).nodFnd->name->len[0], (CHAR*)"ecoParser", 72728)]) {
      return 0;
    }
    tmpInpIdx += 1;
    tmpNodeIdx += 1;
    wrdLength -= 1;
  }
  (*prs).inpIdx = tmpInpIdx;
  (*prs).inpAvl -= (*prs).nodFnd->nameLen;
  return 1;
}

/*----------------------------------------------------------------------------*/
BOOLEAN ecoParser_EquCap (ecoParser_Parser *prs, void **prs__typ)
{
  INTEGER wrdLength, tmpInpIdx, tmpNodeIdx;
  if ((*prs).nodFnd->nameLen > (*prs).inpAvl) {
    return 0;
  }
  wrdLength = (*prs).nodFnd->nameLen;
  tmpInpIdx = (*prs).inpIdx;
  tmpNodeIdx = 0;
  while (wrdLength > 0) {
    if (ecoParser_Cap(((*prs).inpBuf->data)[__X(tmpInpIdx, (*prs).inpBuf->len[0], (CHAR*)"ecoParser", 77848)]) != ((*prs).nodFnd->name->data)[__X(tmpNodeIdx, (*prs).nodFnd->name->len[0], (CHAR*)"ecoParser", 77848)]) {
      return 0;
    }
    tmpInpIdx += 1;
    tmpNodeIdx += 1;
    wrdLength -= 1;
  }
  (*prs).inpIdx = tmpInpIdx;
  (*prs).inpAvl -= (*prs).nodFnd->nameLen;
  return 1;
}

/*----------------------------------------------------------------------------*/
void ecoParser_Parser_Init (ecoParser_Parser *prs, void **prs__typ, ecoParser_StrPtr buf, INTEGER bufLen, INTEGER ctxDeep)
{
  (*prs).inpBuf = buf;
  (*prs).inpIdx = 0;
  if (buf == NIL) {
    (*prs).inpAvl = 0;
  } else if (bufLen <= buf->len[0]) {
    (*prs).inpAvl = bufLen;
  } else {
    (*prs).inpAvl = (SHORTINT)buf->len[0];
  }
  if (ctxDeep != 0) {
    (*prs).ctxStk = __NEWARR(POINTER__typ, 4, 4, 1, 1, (SYSTEM_ARRLEN)ctxDeep);
    (*prs).ctxIdx = 0;
  }
}

/*----------------------------------------------------------------------------*/
void ecoParser_Parser_Exec (ecoParser_Parser *prs, void **prs__typ)
{
  (*prs).nodFnd = (*prs).ctxNow->chldNode;
  while ((*prs).nodFnd != NIL && !(*(*prs).nodFnd->comparer)(prs, prs__typ)) {
    (*prs).nodFnd = (*prs).nodFnd->nextNode;
  }
  if ((*prs).nodFnd != NIL) {
    (*(*prs).nodFnd->method)(prs, prs__typ);
  } else {
    (*(*prs).ctxNow->NotFound)(prs, prs__typ);
  }
}

/*----------------------------------------------------------------------------*/
ecoParser_ParserPtr ecoParser_NewParser (ecoParser_StrPtr buf, INTEGER bufLen, INTEGER ctxDeep)
{
  ecoParser_ParserPtr prsPtr = NIL;
  __NEW(prsPtr, ecoParser_Parser);
  __ecoParser_Parser_Init(prsPtr, __TYPEOF(prsPtr), buf, bufLen, ctxDeep);
  return prsPtr;
}

/*----------------------------------------------------------------------------*/
__TDESC(ecoParser_Tree__desc, 8, 3) = {__TDFLDS("Tree", 12), {0, 4, 8, -16}};
__TDESC(ecoParser_Parser__desc, 7, 4) = {__TDFLDS("Parser", 28), {0, 12, 16, 24, -20}};
__TDESC(ecoParser_Node__desc, 2, 2) = {__TDFLDS("Node", 20), {0, 12, -12}};
__TDESC(ecoParser_CtxNode__desc, 3, 3) = {__TDFLDS("CtxNode", 28), {0, 12, 20, -16}};
__TDESC(ecoParser_MethodNode__desc, 2, 2) = {__TDFLDS("MethodNode", 20), {0, 12, -12}};
__TDESC(ecoParser_SetCtxNode__desc, 2, 3) = {__TDFLDS("SetCtxNode", 24), {0, 12, 20, -16}};

export void *ecoParser__init (void)
{
  __DEFMOD;
  __REGMOD("ecoParser", 0);
  __INITYP(ecoParser_Tree, ecoParser_Tree, 0);
  __INITBP(ecoParser_Tree, ecoParser_Tree_AddContext, 1);
  __INITBP(ecoParser_Tree, ecoParser_Tree_AddMethod, 2);
  __INITBP(ecoParser_Tree, ecoParser_Tree_AddPushContext, 3);
  __INITBP(ecoParser_Tree, ecoParser_Tree_AddSetContext, 4);
  __INITBP(ecoParser_Tree, ecoParser_Tree_Init, 5);
  __INITBP(ecoParser_Tree, ecoParser_Tree_To, 6);
  __INITYP(ecoParser_Parser, ecoParser_Parser, 0);
  __INITBP(ecoParser_Parser, ecoParser_Parser_Exec, 1);
  __INITBP(ecoParser_Parser, ecoParser_Parser_Init, 2);
  __INITBP(ecoParser_Parser, ecoParser_Parser_PopContext, 3);
  __INITBP(ecoParser_Parser, ecoParser_Parser_PushContext, 4);
  __INITBP(ecoParser_Parser, ecoParser_Parser_SetContextByPtr, 5);
  __INITYP(ecoParser_Node, ecoParser_Node, 0);
  __INITYP(ecoParser_CtxNode, ecoParser_Node, 1);
  __INITBP(ecoParser_CtxNode, ecoParser_CtxNode_AddContext, 1);
  __INITYP(ecoParser_MethodNode, ecoParser_Node, 1);
  __INITYP(ecoParser_SetCtxNode, ecoParser_Node, 1);
/* BEGIN */
  __ENDMOD;
}
