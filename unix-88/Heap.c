/* Ofront+ 1.0 -sxapC -88 */
#include "SYSTEM.oh"

struct Heap__1 {
  CHAR ch;
  SYSTEM_PTR p;
};

typedef
  struct Heap_CmdDesc *Heap_Cmd;

typedef
  CHAR Heap_CmdName[24];

typedef
  void (*Heap_Command)(void);

typedef
  struct Heap_CmdDesc {
    Heap_Cmd next;
    Heap_CmdName name;
    Heap_Command cmd;
  } Heap_CmdDesc;

typedef
  void (*Heap_EnumProc)(void(*)(SYSTEM_PTR));

typedef
  struct Heap_FinDesc *Heap_FinNode;

typedef
  void (*Heap_Finalizer)(SYSTEM_PTR);

typedef
  struct Heap_FinDesc {
    Heap_FinNode next;
    LONGINT obj;
    BOOLEAN marked;
    Heap_Finalizer finalize;
  } Heap_FinDesc;

typedef
  struct Heap_ModuleDesc *Heap_Module;

typedef
  CHAR Heap_ModuleName[48];

typedef
  struct Heap_ModuleDesc {
    Heap_Module next;
    Heap_ModuleName name;
    INTEGER refcnt;
    Heap_Cmd cmds;
    SYSTEM_PTR types;
    Heap_EnumProc enumPtrs;
    LONGINT reserved1, reserved2;
  } Heap_ModuleDesc;


export SYSTEM_PTR Heap_modules;
static LONGINT Heap_freeList[10];
static LONGINT Heap_bigBlocks;
export LONGINT Heap_allocated;
static BOOLEAN Heap_firstTry;
export LONGINT Heap_heap;
static LONGINT Heap_heapMin, Heap_heapMax;
export LONGINT Heap_heapsize, Heap_heapMinExpand;
static Heap_FinNode Heap_fin;
export SHORTINT Heap_lockGC;
static SHORTINT Heap_lockdepth;
static BOOLEAN Heap_interrupted;
export INTEGER Heap_FileCount;

export void **Heap_ModuleDesc__typ;
export void **Heap_CmdDesc__typ;
export void **Heap_FinDesc__typ;
export void **Heap__1__typ;

static void Heap_CallMarkStack (void);
static void Heap_CheckFin (void);
export BOOLEAN Heap_DECREF (SYSTEM_PTR mod);
static void Heap_ExtendHeap (LONGINT blksz);
export void Heap_FINALL (void);
static void Heap_Finalize (void);
export INTEGER Heap_FreeModule (CHAR *name, INTEGER name__len);
export void Heap_GC (BOOLEAN markStack);
static void Heap_HeapSort (INTEGER n, LONGINT *a, INTEGER a__len);
export void Heap_INCREF (SYSTEM_PTR mod);
export void Heap_InitHeap (void);
export void Heap_Lock (void);
static void Heap_Mark (LONGINT q);
static void Heap_MarkCandidates (INTEGER n, LONGINT *cand, INTEGER cand__len);
static void Heap_MarkP (SYSTEM_PTR p);
export void Heap_MarkStack (void);
export void Heap_MarkStack0 (LONGINT sp);
export SYSTEM_PTR Heap_NEWBLK (LONGINT size);
export SYSTEM_PTR Heap_NEWREC (SYSTEM_PTR tag);
static LONGINT Heap_NewChunk (LONGINT blksz);
export void Heap_REGCMD (SYSTEM_PTR mod, CHAR *name, INTEGER name__len, Heap_Command cmd);
export SYSTEM_PTR Heap_REGMOD (CHAR *name, INTEGER name__len, Heap_EnumProc enumPtrs);
export void Heap_REGTYP (SYSTEM_PTR mod, SYSTEM_PTR typ);
export void Heap_RegisterFinalizer (SYSTEM_PTR obj, Heap_Finalizer finalize);
static void Heap_Scan (void);
static void Heap_Sift (INTEGER l, INTEGER r, LONGINT *a, INTEGER a__len);
export void Heap_Unlock (void);

extern void *Heap__init();
extern void *SYSTEM_MainStackFrame;
extern SYSTEM_ADRINT Platform_OSAllocate (SYSTEM_ADRINT size);
extern void Platform_OSFree (SYSTEM_ADRINT adr);
#define Heap_HeapModuleInit()  Heap__init()
#define Heap_OSAllocate(size)  Platform_OSAllocate(size)
#define Heap_OSFree(adr)  Platform_OSFree(adr)
#define Heap_SystemHalt(code, mod, mod__len, pos)  __HALT(code, mod, pos)
#define Heap_SystemMainStackFrame()  (SYSTEM_ADRINT)SYSTEM_MainStackFrame
#include <setjmp.h>
#define Heap_setjmp()  jmp_buf env; setjmp(env);
#define Heap_uLE(x, y)  ((__U_ADRINT)x <= (__U_ADRINT)y)
#define Heap_uLT(x, y)  ((__U_ADRINT)x <  (__U_ADRINT)y)

/*============================================================================*/

void Heap_Lock (void)
{
  Heap_lockdepth += 1;
}

/*----------------------------------------------------------------------------*/
void Heap_Unlock (void)
{
  Heap_lockdepth -= 1;
  if (Heap_interrupted && (INTEGER)Heap_lockdepth == 0) {
    Heap_SystemHalt(-9, (CHAR*)"Heap", 5, 122);
  }
}

/*----------------------------------------------------------------------------*/
SYSTEM_PTR Heap_REGMOD (CHAR *name, INTEGER name__len, Heap_EnumProc enumPtrs)
{
  Heap_Module m;
    if (__STRCMPCC(name, (CHAR*)"Heap", 5, (CHAR*)"Heap", 36359) == 0) {
    __SYSNEW(m, 104);
  } else {
    __NEW(m, Heap_ModuleDesc);
  }
  m->types = NIL;
  m->cmds = NIL;
  __STRCOPYCC(name, m->name, __MIN(48, name__len), (CHAR*)"Heap", 37139);
  m->refcnt = 0;
  m->enumPtrs = enumPtrs;
  m->next = (Heap_Module)Heap_modules;
  Heap_modules = (SYSTEM_PTR)m;
  return (void*)m;
}

/*----------------------------------------------------------------------------*/
INTEGER Heap_FreeModule (CHAR *name, INTEGER name__len)
{
  Heap_Module m, p;
  m = (Heap_Module)Heap_modules;
  while (m != NIL && __STRCMPCC(m->name, name, name__len, (CHAR*)"Heap", 39717) != 0) {
    p = m;
    m = m->next;
  }
  if (m != NIL && m->refcnt == 0) {
    if (m == (Heap_Module)Heap_modules) {
      Heap_modules = (SYSTEM_PTR)m->next;
    } else {
      p->next = m->next;
    }
    return 0;
  } else {
    if (m == NIL) {
      return -1;
    } else {
      return m->refcnt;
    }
  }
  __RETCHK((CHAR*)"Heap", 41524);
}

/*----------------------------------------------------------------------------*/
void Heap_REGCMD (SYSTEM_PTR mod, CHAR *name, INTEGER name__len, Heap_Command cmd)
{
  Heap_Cmd c;
  Heap_Module m;
    m = (Heap_Module)mod;
  if (__STRCMPCC(m->name, (CHAR*)"Heap", 5, (CHAR*)"Heap", 46087) == 0) {
    __SYSNEW(c, 40);
  } else {
    __NEW(c, Heap_CmdDesc);
  }
  __STRCOPYCC(name, c->name, __MIN(24, name__len), (CHAR*)"Heap", 46355);
  c->cmd = cmd;
  c->next = m->cmds;
  m->cmds = c;
}

/*----------------------------------------------------------------------------*/
void Heap_REGTYP (SYSTEM_PTR mod, SYSTEM_PTR typ)
{
  Heap_Module m;
  m = (Heap_Module)mod;
  __PUT(typ, m->types, SYSTEM_PTR);
  m->types = typ;
}

/*----------------------------------------------------------------------------*/
void Heap_INCREF (SYSTEM_PTR mod)
{
  Heap_Module m;
  m = (Heap_Module)mod;
  m->refcnt += 1;
}

/*----------------------------------------------------------------------------*/
BOOLEAN Heap_DECREF (SYSTEM_PTR mod)
{
  Heap_Module m;
  m = (Heap_Module)mod;
  m->refcnt -= 1;
  return m->refcnt == 0;
}

/*----------------------------------------------------------------------------*/
static LONGINT Heap_NewChunk (LONGINT blksz)
{
  LONGINT chnk, blk, end;
  chnk = Heap_OSAllocate(blksz + 24);
  if (chnk != 0) {
    blk = chnk + 24;
    end = blk + blksz;
    __PUT(chnk + 8, end, LONGINT);
    __PUT(blk, blk + 8, LONGINT);
    __PUT(blk + 8, blksz, LONGINT);
    __PUT(blk + 16, -8, LONGINT);
    __PUT(blk + 24, Heap_bigBlocks, LONGINT);
    Heap_bigBlocks = blk;
    Heap_heapsize += blksz;
    if (Heap_uLT(blk + 8, Heap_heapMin)) {
      Heap_heapMin = blk + 8;
    }
    if (Heap_uLT(Heap_heapMax, end)) {
      Heap_heapMax = end;
    }
  }
  return chnk;
}

static void Heap_ExtendHeap (LONGINT blksz)
{
  LONGINT size, chnk, j, next;
    if (Heap_uLT(Heap_heapMinExpand, blksz)) {
    size = blksz;
  } else {
    size = Heap_heapMinExpand;
  }
  chnk = Heap_NewChunk(size);
  if (chnk != 0) {
    if (Heap_uLT(chnk, Heap_heap)) {
      __PUT(chnk, Heap_heap, LONGINT);
      Heap_heap = chnk;
    } else {
      j = Heap_heap;
      __GET(j, next, LONGINT);
      while (next != 0 && Heap_uLT(next, chnk)) {
        j = next;
        __GET(j, next, LONGINT);
      }
      __PUT(chnk, next, LONGINT);
      __PUT(j, chnk, LONGINT);
    }
  } else if (!Heap_firstTry) {
    Heap_heapMinExpand = 32;
  }
}

SYSTEM_PTR Heap_NEWREC (SYSTEM_PTR tag)
{
  LONGINT i, i0, di, blksz, restsize, t, adr, end, next, prev;
  SYSTEM_PTR new;
  Heap_Lock();
  __GET(tag, blksz, LONGINT);
    i0 = __LSHR(blksz, 5, LONGINT);
  i = i0;
  if (i < 9) {
    adr = Heap_freeList[i];
    while (adr == 0) {
      i += 1;
      adr = Heap_freeList[i];
    }
  }
  if (i < 9) {
    __GET(adr + 24, next, LONGINT);
    Heap_freeList[i] = next;
    if (i != i0) {
      di = i - i0;
      restsize = __ASHL(di, 5, LONGINT);
      end = adr + restsize;
      __PUT(end + 8, blksz, LONGINT);
      __PUT(end + 16, -8, LONGINT);
      __PUT(end, end + 8, LONGINT);
      __PUT(adr + 8, restsize, LONGINT);
      __PUT(adr + 24, Heap_freeList[di], LONGINT);
      Heap_freeList[di] = adr;
      adr += restsize;
    }
  } else {
    adr = Heap_bigBlocks;
    prev = 0;
    for (;;) {
      if (adr == 0) {
        if (Heap_firstTry) {
          Heap_GC(1);
          blksz += 32;
          t = __LSHR(Heap_allocated + blksz, 7, LONGINT) * 160;
          if (Heap_uLT(Heap_heapsize, t)) {
            Heap_ExtendHeap(t - Heap_heapsize);
          }
          Heap_firstTry = 0;
          new = Heap_NEWREC(tag);
          if (new == NIL) {
            Heap_ExtendHeap(blksz);
            new = Heap_NEWREC(tag);
          }
          Heap_firstTry = 1;
          Heap_Unlock();
          return new;
        } else {
          Heap_Unlock();
          return NIL;
        }
      }
      __GET(adr + 8, t, LONGINT);
      if (Heap_uLE(blksz, t)) {
        break;
      }
      prev = adr;
      __GET(adr + 24, adr, LONGINT);
    }
    restsize = t - blksz;
    end = adr + restsize;
    __PUT(end + 8, blksz, LONGINT);
    __PUT(end + 16, -8, LONGINT);
    __PUT(end, end + 8, LONGINT);
    if (Heap_uLT(288, restsize)) {
      __PUT(adr + 8, restsize, LONGINT);
    } else {
      __GET(adr + 24, next, LONGINT);
      if (prev == 0) {
        Heap_bigBlocks = next;
      } else {
        __PUT(prev + 24, next, LONGINT);
      }
      if (restsize != 0) {
        di = __ASHR(restsize, 5, LONGINT);
        __PUT(adr + 8, restsize, LONGINT);
        __PUT(adr + 24, Heap_freeList[di], LONGINT);
        Heap_freeList[di] = adr;
      }
    }
    adr += restsize;
  }
  i = adr + 32;
  end = adr + blksz;
  while (Heap_uLT(i, end)) {
    __PUT(i, 0, LONGINT);
    __PUT(i + 8, 0, LONGINT);
    __PUT(i + 16, 0, LONGINT);
    __PUT(i + 24, 0, LONGINT);
    i += 32;
  }
  __PUT(adr + 24, 0, LONGINT);
  __PUT(adr, tag, SYSTEM_PTR);
  __PUT(adr + 8, 0, LONGINT);
  __PUT(adr + 16, 0, LONGINT);
  Heap_allocated += blksz;
  Heap_Unlock();
  return (SYSTEM_PTR)(adr + 8);
}

/*----------------------------------------------------------------------------*/
SYSTEM_PTR Heap_NEWBLK (LONGINT size)
{
  LONGINT blksz, tag;
  SYSTEM_PTR new;
  Heap_Lock();
  blksz = __ASHL(__ASHR(size + 63, 5, LONGINT), 5, LONGINT);
  new = Heap_NEWREC((SYSTEM_PTR)((SYSTEM_ADRINT)&blksz));
  tag = ((LONGINT)new + blksz) - 24;
  __PUT(tag - 8, 0, LONGINT);
  __PUT(tag, blksz, LONGINT);
  __PUT(tag + 8, -8, LONGINT);
  __PUT((LONGINT)new - 8, tag, LONGINT);
  Heap_Unlock();
  return new;
}

/*----------------------------------------------------------------------------*/
static void Heap_Mark (LONGINT q)
{
  LONGINT p, tag, offset, fld, n, tagbits;
  if (q != 0) {
    __GET(q - 8, tagbits, LONGINT);
    if (!__ODD(tagbits)) {
      __PUT(q - 8, tagbits + 1, LONGINT);
      p = 0;
      tag = tagbits + 8;
      for (;;) {
        __GET(tag, offset, LONGINT);
        if (offset < 0) {
          __PUT(q - 8, (tag + offset) + 1, LONGINT);
          if (p == 0) {
            break;
          }
          n = q;
          q = p;
          __GET(q - 8, tag, LONGINT);
          tag -= 1;
          __GET(tag, offset, LONGINT);
          fld = q + offset;
          __GET(fld, p, LONGINT);
          __PUT(fld, n, LONGINT);
        } else {
          fld = q + offset;
          __GET(fld, n, LONGINT);
          if (n != 0) {
            __GET(n - 8, tagbits, LONGINT);
            if (!__ODD(tagbits)) {
              __PUT(n - 8, tagbits + 1, LONGINT);
              __PUT(q - 8, tag + 1, LONGINT);
              __PUT(fld, p, LONGINT);
              p = q;
              q = n;
              tag = tagbits;
            }
          }
        }
        tag += 8;
      }
    }
  }
}

static void Heap_MarkP (SYSTEM_PTR p)
{
  Heap_Mark((LONGINT)p);
}

static void Heap_Scan (void)
{
  LONGINT chnk, prevChnk, nextChnk, adr, end, start, tag, i, size, freesize;
  Heap_bigBlocks = 0;
  i = 1;
  while (i < 9) {
    Heap_freeList[i] = 0;
    i += 1;
  }
  freesize = 0;
  Heap_allocated = 0;
  chnk = Heap_heap;
  prevChnk = 0;
  while (chnk != 0) {
    adr = chnk + 24;
    __GET(chnk + 8, end, LONGINT);
    while (Heap_uLT(adr, end)) {
      __GET(adr, tag, LONGINT);
      if (__ODD(tag)) {
        if (freesize != 0) {
          start = adr - freesize;
          __PUT(start, start + 8, LONGINT);
          __PUT(start + 8, freesize, LONGINT);
          __PUT(start + 16, -8, LONGINT);
          i = __LSHR(freesize, 5, LONGINT);
          freesize = 0;
          if (Heap_uLT(i, 9)) {
            __PUT(start + 24, Heap_freeList[i], LONGINT);
            Heap_freeList[i] = start;
          } else {
            __PUT(start + 24, Heap_bigBlocks, LONGINT);
            Heap_bigBlocks = start;
          }
        }
        tag -= 1;
        __PUT(adr, tag, LONGINT);
        __GET(tag, size, LONGINT);
        Heap_allocated += size;
        adr += size;
      } else {
        __GET(tag, size, LONGINT);
        freesize += size;
        adr += size;
      }
    }
    __GET(chnk, nextChnk, LONGINT);
    if (freesize != 0) {
      start = adr - freesize;
      if (start == chnk + 24 && prevChnk != nextChnk) {
        Heap_heapsize -= freesize;
        if (prevChnk == 0) {
          Heap_heap = nextChnk;
          Heap_heapMin = (nextChnk + 24) + 8;
        } else if (nextChnk != 0) {
          __PUT(prevChnk, nextChnk, LONGINT);
        } else {
          __PUT(prevChnk, nextChnk, LONGINT);
          Heap_heapMax = end;
        }
        Heap_OSFree(chnk);
      } else {
        __PUT(start, start + 8, LONGINT);
        __PUT(start + 8, freesize, LONGINT);
        __PUT(start + 16, -8, LONGINT);
        i = __LSHR(freesize, 5, LONGINT);
        if (Heap_uLT(i, 9)) {
          __PUT(start + 24, Heap_freeList[i], LONGINT);
          Heap_freeList[i] = start;
        } else {
          __PUT(start + 24, Heap_bigBlocks, LONGINT);
          Heap_bigBlocks = start;
        }
        prevChnk = chnk;
      }
      freesize = 0;
    } else {
      prevChnk = chnk;
    }
    chnk = nextChnk;
  }
}

static void Heap_Sift (INTEGER l, INTEGER r, LONGINT *a, INTEGER a__len)
{
  INTEGER i, j;
  LONGINT x;
  j = l;
  x = a[j];
  for (;;) {
    i = j;
    j = __ASHL(j, 1, INTEGER) + 1;
    if (j < r && Heap_uLT(a[j], a[j + 1])) {
      j += 1;
    }
    if (j > r || Heap_uLE(a[j], x)) {
      break;
    }
    a[i] = a[j];
  }
  a[i] = x;
}

static void Heap_HeapSort (INTEGER n, LONGINT *a, INTEGER a__len)
{
  INTEGER l, r;
  LONGINT x;
  l = __ASHR(n, 1, INTEGER);
  r = n - 1;
  while (l > 0) {
    l -= 1;
    Heap_Sift(l, r, (void*)a, a__len);
  }
  while (r > 0) {
    x = a[0];
    a[0] = a[r];
    a[r] = x;
    r -= 1;
    Heap_Sift(l, r, (void*)a, a__len);
  }
}

static void Heap_MarkCandidates (INTEGER n, LONGINT *cand, INTEGER cand__len)
{
  INTEGER i;
  LONGINT chnk, end, adr, tag, next, ptr, size;
    chnk = Heap_heap;
  i = 0;
  while (chnk != 0) {
    __GET(chnk + 8, end, LONGINT);
    adr = chnk + 24;
    while (Heap_uLT(adr, end)) {
      __GET(adr, tag, LONGINT);
      if (__ODD(tag)) {
        __GET(tag - 1, size, LONGINT);
        adr += size;
        ptr = adr + 8;
        while (Heap_uLT(cand[i], ptr)) {
          i += 1;
          if (i == n) {
            return;
          }
        }
      } else {
        __GET(tag, size, LONGINT);
        ptr = adr + 8;
        adr += size;
        while (Heap_uLT(cand[i], ptr)) {
          i += 1;
          if (i == n) {
            return;
          }
        }
        if (Heap_uLT(cand[i], adr)) {
          Heap_Mark(ptr);
        }
      }
      if (Heap_uLE(end, cand[i])) {
        adr = end;
      }
    }
    __GET(chnk, chnk, LONGINT);
  }
}

static void Heap_CheckFin (void)
{
  Heap_FinNode n;
  LONGINT tag;
  n = Heap_fin;
  while (n != NIL) {
    __GET(n->obj - 8, tag, LONGINT);
    if (!__ODD(tag)) {
      n->marked = 0;
      Heap_Mark(n->obj);
    } else {
      n->marked = 1;
    }
    n = n->next;
  }
}

static void Heap_Finalize (void)
{
  Heap_FinNode n, prev;
  n = Heap_fin;
  prev = NIL;
  while (n != NIL) {
    if (!n->marked) {
      if (n == Heap_fin) {
        Heap_fin = Heap_fin->next;
      } else {
        prev->next = n->next;
      }
      (*n->finalize)((SYSTEM_PTR)n->obj);
      if (prev == NIL) {
        n = Heap_fin;
      } else {
        n = n->next;
      }
    } else {
      prev = n;
      n = n->next;
    }
  }
}

void Heap_FINALL (void)
{
  Heap_FinNode n;
  while (Heap_fin != NIL) {
    n = Heap_fin;
    Heap_fin = Heap_fin->next;
    (*n->finalize)((SYSTEM_PTR)n->obj);
  }
}

/*----------------------------------------------------------------------------*/
void Heap_MarkStack0 (LONGINT sp)
{
  INTEGER nofcand;
  LONGINT inc, p, stack0;
  struct Heap__1 align;
  LONGINT cand[10000];
  nofcand = 0;
  stack0 = Heap_SystemMainStackFrame();
  inc = (SYSTEM_ADRINT)&align.p - (SYSTEM_ADRINT)&align;
  if (Heap_uLT(stack0, sp)) {
    inc = -inc;
  }
  while (sp != stack0) {
    __GET(sp, p, LONGINT);
    if (Heap_uLE(Heap_heapMin, p) && Heap_uLT(p, Heap_heapMax)) {
      if (nofcand == 10000) {
        Heap_HeapSort(nofcand, (void*)cand, 10000);
        Heap_MarkCandidates(nofcand, (void*)cand, 10000);
        nofcand = 0;
      }
      cand[nofcand] = p;
      nofcand += 1;
    }
    sp += inc;
  }
  if (nofcand > 0) {
    Heap_HeapSort(nofcand, (void*)cand, 10000);
    Heap_MarkCandidates(nofcand, (void*)cand, 10000);
  }
}

/*----------------------------------------------------------------------------*/
void Heap_MarkStack (void)
{
  LONGINT x;
  Heap_MarkStack0((SYSTEM_ADRINT)&x);
}

/*----------------------------------------------------------------------------*/
static void Heap_CallMarkStack (void)
{
  Heap_setjmp();
  Heap_MarkStack();
}

void Heap_GC (BOOLEAN markStack)
{
  Heap_Module m;
  if ((INTEGER)Heap_lockGC == 0 || ((INTEGER)Heap_lockGC == 1 && !markStack)) {
    Heap_Lock();
    m = (Heap_Module)Heap_modules;
    while (m != NIL) {
      if (m->enumPtrs != NIL) {
        (*m->enumPtrs)(Heap_MarkP);
      }
      m = m->next;
    }
    if (markStack) {
      Heap_CallMarkStack();
    }
    Heap_CheckFin();
    Heap_Scan();
    Heap_Finalize();
    Heap_Unlock();
  }
}

/*----------------------------------------------------------------------------*/
void Heap_RegisterFinalizer (SYSTEM_PTR obj, Heap_Finalizer finalize)
{
  Heap_FinNode f;
  __NEW(f, Heap_FinDesc);
  f->obj = (LONGINT)obj;
  f->finalize = finalize;
  f->marked = 1;
  f->next = Heap_fin;
  Heap_fin = f;
}

/*----------------------------------------------------------------------------*/
void Heap_InitHeap (void)
{
  Heap_heap = 0;
  Heap_heapsize = 0;
  Heap_allocated = 0;
  Heap_lockdepth = 0;
  Heap_heapMin = -1;
  Heap_heapMax = 0;
  Heap_bigBlocks = 0;
  Heap_heapMinExpand = 256000;
  Heap_heap = Heap_NewChunk(256000);
  __PUT(Heap_heap, 0, LONGINT);
  Heap_firstTry = 1;
  Heap_freeList[9] = 1;
  Heap_FileCount = 0;
  Heap_modules = NIL;
  Heap_fin = NIL;
  Heap_lockGC = 0;
  Heap_interrupted = 0;
  Heap_HeapModuleInit();
}

/*----------------------------------------------------------------------------*/
static void EnumPtrs(void (*P)(void*))
{
  P(Heap_modules);
  P(Heap_fin);
}

__TDESC(Heap_ModuleDesc__desc, 2, 3) = {__TDFLDS("ModuleDesc", 104), {0, 64, 72, -32}};
__TDESC(Heap_CmdDesc__desc, 2, 1) = {__TDFLDS("CmdDesc", 40), {0, -16}};
__TDESC(Heap_FinDesc__desc, 2, 1) = {__TDFLDS("FinDesc", 32), {0, -16}};
__TDESC(Heap__1__desc, 2, 1) = {__TDFLDS("", 16), {8, -16}};

export void *Heap__init (void)
{
  __DEFMOD;
  __REGMOD("Heap", EnumPtrs);
  __REGCMD("FINALL", Heap_FINALL);
  __REGCMD("InitHeap", Heap_InitHeap);
  __REGCMD("Lock", Heap_Lock);
  __REGCMD("MarkStack", Heap_MarkStack);
  __REGCMD("Unlock", Heap_Unlock);
  __INITYP(Heap_ModuleDesc, Heap_ModuleDesc, 0);
  __INITYP(Heap_CmdDesc, Heap_CmdDesc, 0);
  __INITYP(Heap_FinDesc, Heap_FinDesc, 0);
  __INITYP(Heap__1, Heap__1, 0);
/* BEGIN */
  __ENDMOD;
}
