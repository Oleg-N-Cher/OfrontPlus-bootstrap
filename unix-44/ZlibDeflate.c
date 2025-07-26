/* Ofront+ 1.0 -s2 -44 */
#include "SYSTEM.oh"
#include "Zlib.oh"
#include "ZlibBuffers.oh"

typedef
  CHAR ZlibDeflate_Window[65536];

typedef
  struct ZlibDeflate_PendingBuffer {
    CHAR (*buf)[65536];
    INTEGER beg, end;
  } ZlibDeflate_PendingBuffer;

typedef
  struct ZlibDeflate_Node_ARRAY *ZlibDeflate_Nodes;

typedef
  struct INT16_ARRAY *ZlibDeflate_Bits;

typedef
  struct ZlibDeflate_StaticTree {
    ZlibDeflate_Nodes node;
    ZlibDeflate_Bits bits;
    SHORTINT base, elems, maxLength;
  } ZlibDeflate_StaticTree;

typedef
  struct ZlibDeflate_Tree {
    ZlibDeflate_Nodes node;
    SHORTINT maxCode;
    ZlibDeflate_StaticTree static_;
  } ZlibDeflate_Tree;

typedef
  struct ZlibDeflate_Stream {
    ZlibBuffers_Buffer in, out;
    INTEGER res;
    BYTE level, strategy, dataType;
    BOOLEAN wrapper, open, trailerDone;
    BYTE lastFlush, status;
    INTEGER adler;
    ZlibDeflate_Window *window;
    INTEGER block, hash;
    INTEGER (*prev)[32768];
    INTEGER (*head)[32768];
    INTEGER string, lookAhead, match, matchLen, prevMatch, prevLen;
    BOOLEAN prevAvail;
    ZlibDeflate_PendingBuffer pend;
    ZlibDeflate_Tree ltree, dtree, btree;
    ZlibDeflate_Nodes lnode, dnode, bnode;
    SHORTINT bitLenCount[16];
    SHORTINT heap[573];
    SHORTINT heapLen, heapMax;
    SHORTINT depth[573];
    CHAR (*lbuf)[16384];
    SHORTINT (*dbuf)[16384];
    INTEGER lastLit, buf;
    SHORTINT bits, lastEobLen;
    INTEGER optLen, staticLen;
  } ZlibDeflate_Stream;

typedef
  BYTE (*ZlibDeflate_Compressor)(ZlibDeflate_Stream*, void **, BYTE);

struct ZlibDeflate__1 {
  SHORTINT GoodLen, MaxLazy, NiceLen, MaxChain;
  ZlibDeflate_Compressor Compress;
};

typedef
  struct ZlibDeflate_Node {
    SHORTINT freqOrCode, dadOrLen;
  } ZlibDeflate_Node;


#ifndef INT16_ARRAY_DEF
#define INT16_ARRAY_DEF
typedef struct INT16_ARRAY {
  INTEGER len[1];
  SHORTINT data[1];
} INT16_ARRAY;
#endif 

#ifndef ZlibDeflate_Node_ARRAY_DEF
#define ZlibDeflate_Node_ARRAY_DEF
typedef struct ZlibDeflate_Node_ARRAY {
  INTEGER len[1];
  ZlibDeflate_Node data[1];
} ZlibDeflate_Node_ARRAY;
#endif 

static ZlibDeflate_Bits ZlibDeflate_ExtraLenBits, ZlibDeflate_ExtraDistBits, ZlibDeflate_ExtraBitBits;
static ZlibDeflate_StaticTree ZlibDeflate_LTree, ZlibDeflate_DTree, ZlibDeflate_BTree;
static SHORTINT ZlibDeflate_BaseLength[29];
static SHORTINT ZlibDeflate_BaseDist[30];
static CHAR ZlibDeflate_LengthCode[256];
static CHAR ZlibDeflate_DistCode[512];
static BYTE ZlibDeflate_BitOrder[19];
static struct ZlibDeflate__1 ZlibDeflate_ConfigTable[10];

export void **ZlibDeflate_Node__typ;
export void **ZlibDeflate_StaticTree__typ;
export void **ZlibDeflate_Tree__typ;
export void **ZlibDeflate_PendingBuffer__typ;
export void **ZlibDeflate_Stream__typ;
export void **ZlibDeflate__1__typ;

static void ZlibDeflate_AlignTrees (ZlibDeflate_Stream *stream, void **stream__typ);
static SHORTINT ZlibDeflate_BuildBitLenTree (ZlibDeflate_Stream *stream, void **stream__typ);
static void ZlibDeflate_BuildTree (ZlibDeflate_Stream *stream, void **stream__typ, ZlibDeflate_Tree *tree, void **tree__typ);
static void ZlibDeflate_CheckMatch (ZlibDeflate_Stream *stream, void **stream__typ, INTEGER start, INTEGER match, INTEGER len);
static void ZlibDeflate_ClearHash (ZlibDeflate_Stream *stream, void **stream__typ);
export void ZlibDeflate_Close (ZlibDeflate_Stream *stream, void **stream__typ);
export void ZlibDeflate_Compress (CHAR *src, INTEGER src__len, CHAR *dst, INTEGER dst__len, INTEGER srcoffset, INTEGER srclen, INTEGER dstoffset, INTEGER dstlen, BYTE level, BYTE strategy, INTEGER *len, INTEGER *res);
static void ZlibDeflate_CompressBlock (ZlibDeflate_Stream *stream, void **stream__typ, ZlibDeflate_Nodes lnode, ZlibDeflate_Nodes dnode);
static BYTE ZlibDeflate_CompressFast (ZlibDeflate_Stream *stream, void **stream__typ, BYTE flush);
static BYTE ZlibDeflate_CompressSlow (ZlibDeflate_Stream *stream, void **stream__typ, BYTE flush);
static BYTE ZlibDeflate_CompressStored (ZlibDeflate_Stream *stream, void **stream__typ, BYTE flush);
static void ZlibDeflate_CopyBlock (ZlibDeflate_Stream *stream, void **stream__typ, CHAR *buf, INTEGER buf__len, INTEGER offset, INTEGER len, BOOLEAN header);
export void ZlibDeflate_Deflate (ZlibDeflate_Stream *stream, void **stream__typ, BYTE flush);
static void ZlibDeflate_FillWindow (ZlibDeflate_Stream *stream, void **stream__typ);
static void ZlibDeflate_FlushBits (ZlibDeflate_Stream *stream, void **stream__typ);
static void ZlibDeflate_FlushBlock (ZlibDeflate_Stream *stream, void **stream__typ, CHAR *buf, INTEGER buf__len, INTEGER pos, INTEGER len, BOOLEAN eof);
static void ZlibDeflate_FlushPending (ZlibDeflate_PendingBuffer *pend, void **pend__typ, ZlibBuffers_Buffer *out, void **out__typ);
static void ZlibDeflate_FreeTrees (ZlibDeflate_Stream *stream, void **stream__typ);
static void ZlibDeflate_GenBitLen (ZlibDeflate_Stream *stream, void **stream__typ, ZlibDeflate_Tree *tree, void **tree__typ);
static void ZlibDeflate_GenCodes (ZlibDeflate_Nodes *node, SHORTINT maxCode, SHORTINT *count, INTEGER count__len);
static void ZlibDeflate_InitBlock (ZlibDeflate_Stream *stream, void **stream__typ);
static void ZlibDeflate_InitMatches (ZlibDeflate_Stream *stream, void **stream__typ);
static void ZlibDeflate_InitStaticTrees (void);
static void ZlibDeflate_InitTrees (ZlibDeflate_Stream *stream, void **stream__typ);
static void ZlibDeflate_InsertString (ZlibDeflate_Stream *stream, void **stream__typ, INTEGER pos, INTEGER *head);
static INTEGER ZlibDeflate_LongestMatch (ZlibDeflate_Stream *stream, void **stream__typ, INTEGER cur);
export void ZlibDeflate_Open (ZlibDeflate_Stream *stream, void **stream__typ, BYTE level, BYTE strategy, BOOLEAN wrapper);
static void ZlibDeflate_Put16BitsLSB (ZlibDeflate_PendingBuffer *pend, void **pend__typ, INTEGER b);
static void ZlibDeflate_Put16BitsMSB (ZlibDeflate_PendingBuffer *pend, void **pend__typ, INTEGER b);
static void ZlibDeflate_Put32BitsMSB (ZlibDeflate_PendingBuffer *pend, void **pend__typ, INTEGER b);
static void ZlibDeflate_PutChar (ZlibDeflate_PendingBuffer *pend, void **pend__typ, CHAR c);
export void ZlibDeflate_Reset (ZlibDeflate_Stream *stream, void **stream__typ);
static SHORTINT ZlibDeflate_ReverseBits (SHORTINT code, SHORTINT len);
static void ZlibDeflate_ScanTree (ZlibDeflate_Stream *stream, void **stream__typ, ZlibDeflate_Nodes node, SHORTINT max);
static void ZlibDeflate_SendAllTrees (ZlibDeflate_Stream *stream, void **stream__typ, SHORTINT lcodes, SHORTINT dcodes, SHORTINT blcodes);
static void ZlibDeflate_SendBits (ZlibDeflate_Stream *stream, void **stream__typ, INTEGER val, SHORTINT len);
static void ZlibDeflate_SendCode (ZlibDeflate_Stream *stream, void **stream__typ, ZlibDeflate_Node *node, void **node__typ);
static void ZlibDeflate_SendTree (ZlibDeflate_Stream *stream, void **stream__typ, ZlibDeflate_Nodes node, SHORTINT max);
static void ZlibDeflate_SetDataType (ZlibDeflate_Stream *stream, void **stream__typ);
export void ZlibDeflate_SetDictionary (ZlibDeflate_Stream *stream, void **stream__typ, CHAR *dict, INTEGER dict__len, INTEGER len);
export void ZlibDeflate_SetParams (ZlibDeflate_Stream *stream, void **stream__typ, BYTE level, BYTE strategy);
static void ZlibDeflate_Sift (ZlibDeflate_Stream *stream, void **stream__typ, ZlibDeflate_Nodes *node, SHORTINT k);
static void ZlibDeflate_StoreBlock (ZlibDeflate_Stream *stream, void **stream__typ, CHAR *buf, INTEGER buf__len, INTEGER offset, INTEGER len, BOOLEAN eof);
static BOOLEAN ZlibDeflate_TallyDistLen (ZlibDeflate_Stream *stream, void **stream__typ, SHORTINT dist, SHORTINT len);
static BOOLEAN ZlibDeflate_TallyLit (ZlibDeflate_Stream *stream, void **stream__typ, CHAR ch);
static void ZlibDeflate_UpdateHash (INTEGER *h, CHAR ch);
static void ZlibDeflate_WindupBits (ZlibDeflate_Stream *stream, void **stream__typ);


/*============================================================================*/

static void ZlibDeflate_PutChar (ZlibDeflate_PendingBuffer *pend, void **pend__typ, CHAR c)
{
  (*(*pend).buf)[__X((*pend).end, 65536, (CHAR*)"ZlibDeflate", 41752)] = c;
  (*pend).end += 1;
}

static void ZlibDeflate_Put16BitsLSB (ZlibDeflate_PendingBuffer *pend, void **pend__typ, INTEGER b)
{
  ZlibDeflate_PutChar(pend, pend__typ, (CHAR)__MASK(b, -256));
  ZlibDeflate_PutChar(pend, pend__typ, (CHAR)__MASK(__ASHR(b, 8, INTEGER), -256));
}

static void ZlibDeflate_Put16BitsMSB (ZlibDeflate_PendingBuffer *pend, void **pend__typ, INTEGER b)
{
  ZlibDeflate_PutChar(pend, pend__typ, (CHAR)__MASK(__ASHR(b, 8, INTEGER), -256));
  ZlibDeflate_PutChar(pend, pend__typ, (CHAR)__MASK(b, -256));
}

static void ZlibDeflate_Put32BitsMSB (ZlibDeflate_PendingBuffer *pend, void **pend__typ, INTEGER b)
{
  ZlibDeflate_Put16BitsMSB(pend, pend__typ, __MASK(__ASHR(b, 16, INTEGER), -65536));
  ZlibDeflate_Put16BitsMSB(pend, pend__typ, __MASK(b, -65536));
}

static SHORTINT ZlibDeflate_ReverseBits (SHORTINT code, SHORTINT len)
{
  SHORTINT res;
  res = 0;
  do {
    res = __ASHL(res, 1, SHORTINT);
    res += __MASK(code, -2);
    code = __ASHR(code, 1, SHORTINT);
    len -= 1;
  } while (!(len == 0));
  return res;
}

static void ZlibDeflate_SendBits (ZlibDeflate_Stream *stream, void **stream__typ, INTEGER val, SHORTINT len)
{
  (*stream).buf += __ASH(val, (*stream).bits, INTEGER);
  (*stream).bits += len;
  if ((*stream).bits > 16) {
    ZlibDeflate_Put16BitsLSB(&(*stream).pend, ZlibDeflate_PendingBuffer__typ, (*stream).buf);
    (*stream).buf = __LSHR((*stream).buf, 16, INTEGER);
    (*stream).bits -= 16;
  }
}

static void ZlibDeflate_SendCode (ZlibDeflate_Stream *stream, void **stream__typ, ZlibDeflate_Node *node, void **node__typ)
{
  ZlibDeflate_SendBits(stream, stream__typ, (*node).freqOrCode, (*node).dadOrLen);
}

static void ZlibDeflate_FlushBits (ZlibDeflate_Stream *stream, void **stream__typ)
{
  if ((*stream).bits == 16) {
    ZlibDeflate_Put16BitsLSB(&(*stream).pend, ZlibDeflate_PendingBuffer__typ, (*stream).buf);
    (*stream).buf = 0;
    (*stream).bits = 0;
  } else if ((*stream).bits >= 8) {
    ZlibDeflate_PutChar(&(*stream).pend, ZlibDeflate_PendingBuffer__typ, (CHAR)(*stream).buf);
    (*stream).buf = __LSHR((*stream).buf, 8, INTEGER);
    (*stream).bits -= 8;
  }
}

static void ZlibDeflate_FlushPending (ZlibDeflate_PendingBuffer *pend, void **pend__typ, ZlibBuffers_Buffer *out, void **out__typ)
{
  INTEGER len;
  CHAR (*_ptr__30)[65536] = NIL;
  len = (*pend).end - (*pend).beg;
  if (len > (*out).avail) {
    len = (*out).avail;
  }
  if (len > 0) {
    _ptr__30 = (*pend).buf;
    ZlibBuffers_WriteBytes(out, out__typ, (void*)*_ptr__30, 65536, (*pend).beg, len);
    (*pend).beg += len;
    if ((*pend).beg == (*pend).end) {
      (*pend).beg = 0;
      (*pend).end = 0;
    }
  }
}

static void ZlibDeflate_WindupBits (ZlibDeflate_Stream *stream, void **stream__typ)
{
  if ((*stream).bits > 8) {
    ZlibDeflate_Put16BitsLSB(&(*stream).pend, ZlibDeflate_PendingBuffer__typ, (*stream).buf);
  } else if ((*stream).bits > 0) {
    ZlibDeflate_PutChar(&(*stream).pend, ZlibDeflate_PendingBuffer__typ, (CHAR)(*stream).buf);
  }
  (*stream).buf = 0;
  (*stream).bits = 0;
}

static void ZlibDeflate_SetDataType (ZlibDeflate_Stream *stream, void **stream__typ)
{
  INTEGER n, ascii, bin;
  while (n < 7) {
    bin += (INTEGER)((*stream).lnode->data)[__X(n, (*stream).lnode->len[0], (CHAR*)"ZlibDeflate", 66874)].freqOrCode;
    n += 1;
  }
  while (n < 128) {
    ascii += (INTEGER)((*stream).lnode->data)[__X(n, (*stream).lnode->len[0], (CHAR*)"ZlibDeflate", 67134)].freqOrCode;
    n += 1;
  }
  while (n < 256) {
    bin += (INTEGER)((*stream).lnode->data)[__X(n, (*stream).lnode->len[0], (CHAR*)"ZlibDeflate", 67393)].freqOrCode;
    n += 1;
  }
  if (__ASHL(bin, 2, INTEGER) > ascii) {
    (*stream).dataType = 0;
  } else {
    (*stream).dataType = 1;
  }
}

static void ZlibDeflate_GenCodes (ZlibDeflate_Nodes *node, SHORTINT maxCode, SHORTINT *count, INTEGER count__len)
{
  SHORTINT nextCode[16];
  SHORTINT code, bits, n, len, _for__34;
  code = 0;
  bits = 1;
  while (bits <= 15) {
    code = (SHORTINT)__ASHL((INTEGER)(code + count[__X(bits - 1, count__len, (CHAR*)"ZlibDeflate", 70447)]), 1, INTEGER);
    nextCode[__X(bits, 16, (CHAR*)"ZlibDeflate", 70911)] = code;
    bits += 1;
  }
  __ASSERT((code + count[__X(15, count__len, (CHAR*)"ZlibDeflate", 71229)]) - 1 == 32767, 110, (CHAR*)"ZlibDeflate", 71229);
  _for__34 = maxCode;
  n = 0;
  while (n <= _for__34) {
    len = ((*node)->data)[__X(n, (*node)->len[0], (CHAR*)"ZlibDeflate", 71705)].dadOrLen;
    if (len != 0) {
      ((*node)->data)[__X(n, (*node)->len[0], (CHAR*)"ZlibDeflate", 72248)].freqOrCode = ZlibDeflate_ReverseBits(nextCode[__X(len, 16, (CHAR*)"ZlibDeflate", 72248)], len);
      nextCode[__X(len, 16, (CHAR*)"ZlibDeflate", 72447)] += 1;
    }
    n += 1;
  }
}

static void ZlibDeflate_GenBitLen (ZlibDeflate_Stream *stream, void **stream__typ, ZlibDeflate_Tree *tree, void **tree__typ)
{
  ZlibDeflate_Nodes node = NIL;
  ZlibDeflate_StaticTree stree = {0};
  SHORTINT bits, h, n, m, overflow, xbits;
  INTEGER freq;
  node = (*tree).node;
  stree = (*tree).static_;
  overflow = 0;
  bits = 0;
  while (bits <= 15) {
    (*stream).bitLenCount[__X(bits, 16, (CHAR*)"ZlibDeflate", 76346)] = 0;
    bits += 1;
  }
  (node->data)[__X((*stream).heap[__X((*stream).heapMax, 573, (CHAR*)"ZlibDeflate", 76848)], node->len[0], (CHAR*)"ZlibDeflate", 76848)].dadOrLen = 0;
  h = (*stream).heapMax + 1;
  while (h <= 572) {
    n = (*stream).heap[__X(h, 573, (CHAR*)"ZlibDeflate", 77333)];
    bits = (node->data)[__X((node->data)[__X(n, node->len[0], (CHAR*)"ZlibDeflate", 77613)].dadOrLen, node->len[0], (CHAR*)"ZlibDeflate", 77613)].dadOrLen + 1;
    if (bits > stree.maxLength) {
      bits = stree.maxLength;
      overflow += 1;
    }
    (node->data)[__X(n, node->len[0], (CHAR*)"ZlibDeflate", 78618)].dadOrLen = bits;
    if (n <= (*tree).maxCode) {
      (*stream).bitLenCount[__X(bits, 16, (CHAR*)"ZlibDeflate", 79136)] += 1;
      if (n >= stree.base) {
        xbits = (stree.bits->data)[__X(n - stree.base, stree.bits->len[0], (CHAR*)"ZlibDeflate", 79422)];
      } else {
        xbits = 0;
      }
      freq = (node->data)[__X(n, node->len[0], (CHAR*)"ZlibDeflate", 79645)].freqOrCode;
      (*stream).optLen += freq * (INTEGER)(bits + xbits);
      if (stree.node != NIL) {
        (*stream).staticLen += freq * (INTEGER)((stree.node->data)[__X(n, stree.node->len[0], (CHAR*)"ZlibDeflate", 80218)].dadOrLen + xbits);
      }
    }
    h += 1;
  }
  if (overflow != 0) {
    do {
      bits = stree.maxLength - 1;
      while ((*stream).bitLenCount[__X(bits, 16, (CHAR*)"ZlibDeflate", 82213)] == 0) {
        bits -= 1;
      }
      (*stream).bitLenCount[__X(bits, 16, (CHAR*)"ZlibDeflate", 82464)] -= 1;
      (*stream).bitLenCount[__X(bits + 1, 16, (CHAR*)"ZlibDeflate", 82727)] += 2;
      (*stream).bitLenCount[__X(stree.maxLength, 16, (CHAR*)"ZlibDeflate", 82987)] -= 1;
      overflow -= 2;
    } while (!(overflow <= 0));
    bits = stree.maxLength;
    while (bits > 0) {
      n = (*stream).bitLenCount[__X(bits, 16, (CHAR*)"ZlibDeflate", 84512)];
      while (n != 0) {
        h -= 1;
        m = (*stream).heap[__X(h, 573, (CHAR*)"ZlibDeflate", 85023)];
        if (m <= (*tree).maxCode) {
          if ((node->data)[__X(m, node->len[0], (CHAR*)"ZlibDeflate", 86280)].dadOrLen != bits) {
            (*stream).optLen += (INTEGER)(bits - (node->data)[__X(m, node->len[0], (CHAR*)"ZlibDeflate", 85838)].dadOrLen) * (INTEGER)(node->data)[__X(m, node->len[0], (CHAR*)"ZlibDeflate", 85838)].freqOrCode;
            (node->data)[__X(m, node->len[0], (CHAR*)"ZlibDeflate", 86271)].dadOrLen = bits;
          }
          n -= 1;
        }
      }
      bits -= 1;
    }
  }
}

static struct Sift__68 {
  ZlibDeflate_Stream *stream;
  void **stream__typ;
  ZlibDeflate_Nodes *node;
  struct Sift__68 *lnk;
} *Sift__68_s;

static BOOLEAN __69 (SHORTINT n, SHORTINT m);

static BOOLEAN __69 (SHORTINT n, SHORTINT m)
{
  return ((*Sift__68_s->node)->data)[__X(n, (*Sift__68_s->node)->len[0], (CHAR*)"ZlibDeflate", 91391)].freqOrCode < ((*Sift__68_s->node)->data)[__X(m, (*Sift__68_s->node)->len[0], (CHAR*)"ZlibDeflate", 91391)].freqOrCode || (((*Sift__68_s->node)->data)[__X(n, (*Sift__68_s->node)->len[0], (CHAR*)"ZlibDeflate", 91391)].freqOrCode == ((*Sift__68_s->node)->data)[__X(m, (*Sift__68_s->node)->len[0], (CHAR*)"ZlibDeflate", 91391)].freqOrCode && (*Sift__68_s->stream).depth[__X(n, 573, (CHAR*)"ZlibDeflate", 91391)] <= (*Sift__68_s->stream).depth[__X(m, 573, (CHAR*)"ZlibDeflate", 91391)]);
}

static void ZlibDeflate_Sift (ZlibDeflate_Stream *stream, void **stream__typ, ZlibDeflate_Nodes *node, SHORTINT k)
{
  SHORTINT v, i;
  struct Sift__68 _s;
  _s.stream = stream; _s.stream__typ = stream__typ;
  _s.node = node;
  _s.lnk = Sift__68_s;
  Sift__68_s = &_s;
  v = (*stream).heap[__X(k, 573, (CHAR*)"ZlibDeflate", 92180)];
  i = __ASHL(k, 1, SHORTINT);
  while (i <= (*stream).heapLen) {
    if (i < (*stream).heapLen && __69((*stream).heap[__X(i + 1, 573, (CHAR*)"ZlibDeflate", 93015)], (*stream).heap[__X(i, 573, (CHAR*)"ZlibDeflate", 93015)])) {
      i += 1;
    }
    if (__69(v, (*stream).heap[__X(i, 573, (CHAR*)"ZlibDeflate", 94719)])) {
      (*stream).heap[__X(k, 573, (CHAR*)"ZlibDeflate", 93462)] = v;
      Sift__68_s = _s.lnk;
      return;
    } else {
      (*stream).heap[__X(k, 573, (CHAR*)"ZlibDeflate", 93987)] = (*stream).heap[__X(i, 573, (CHAR*)"ZlibDeflate", 93987)];
      k = i;
      i = __ASHL(i, 1, SHORTINT);
    }
  }
  (*stream).heap[__X(k, 573, (CHAR*)"ZlibDeflate", 95231)] = v;
  Sift__68_s = _s.lnk;
}

static void ZlibDeflate_BuildTree (ZlibDeflate_Stream *stream, void **stream__typ, ZlibDeflate_Tree *tree, void **tree__typ)
{
  ZlibDeflate_Nodes node = NIL;
  ZlibDeflate_StaticTree stree = {0};
  SHORTINT n, m, maxCode, next, _for__6;
  node = (*tree).node;
  stree = (*tree).static_;
  maxCode = -1;
  (*stream).heapLen = 0;
  (*stream).heapMax = 573;
  _for__6 = stree.elems - 1;
  n = 0;
  while (n <= _for__6) {
    if ((node->data)[__X(n, node->len[0], (CHAR*)"ZlibDeflate", 101375)].freqOrCode != 0) {
      maxCode = n;
      (*stream).heapLen += 1;
      (*stream).heap[__X((*stream).heapLen, 573, (CHAR*)"ZlibDeflate", 100152)] = n;
      (*stream).depth[__X(n, 573, (CHAR*)"ZlibDeflate", 100607)] = 0;
    } else {
      (node->data)[__X(n, node->len[0], (CHAR*)"ZlibDeflate", 101119)].dadOrLen = 0;
    }
    n += 1;
  }
  while ((*stream).heapLen < 2) {
    (*stream).heapLen += 1;
    if (maxCode < 2) {
      maxCode += 1;
      n = maxCode;
    } else {
      n = 0;
    }
    (*stream).heap[__X((*stream).heapLen, 573, (CHAR*)"ZlibDeflate", 102946)] = n;
    (node->data)[__X(n, node->len[0], (CHAR*)"ZlibDeflate", 103193)].freqOrCode = 1;
    (*stream).depth[__X(n, 573, (CHAR*)"ZlibDeflate", 103446)] = 0;
    (*stream).optLen -= 1;
    if (stree.node != NIL) {
      (*stream).staticLen -= (INTEGER)(stree.node->data)[__X(n, stree.node->len[0], (CHAR*)"ZlibDeflate", 104014)].dadOrLen;
    }
  }
  (*tree).maxCode = maxCode;
  n = __ASHR((*stream).heapLen, 1, SHORTINT);
  while (n >= 1) {
    ZlibDeflate_Sift(stream, stream__typ, &node, n);
    n += -1;
  }
  next = stree.elems;
  do {
    n = (*stream).heap[1];
    (*stream).heap[1] = (*stream).heap[__X((*stream).heapLen, 573, (CHAR*)"ZlibDeflate", 107311)];
    (*stream).heapLen -= 1;
    ZlibDeflate_Sift(stream, stream__typ, &node, 1);
    m = (*stream).heap[1];
    (*stream).heapMax -= 1;
    (*stream).heap[__X((*stream).heapMax, 573, (CHAR*)"ZlibDeflate", 108343)] = n;
    (*stream).heapMax -= 1;
    (*stream).heap[__X((*stream).heapMax, 573, (CHAR*)"ZlibDeflate", 108599)] = m;
    (node->data)[__X(next, node->len[0], (CHAR*)"ZlibDeflate", 108866)].freqOrCode = (node->data)[__X(n, node->len[0], (CHAR*)"ZlibDeflate", 108866)].freqOrCode + (node->data)[__X(m, node->len[0], (CHAR*)"ZlibDeflate", 108866)].freqOrCode;
    if ((*stream).depth[__X(n, 573, (CHAR*)"ZlibDeflate", 109573)] > (*stream).depth[__X(m, 573, (CHAR*)"ZlibDeflate", 109573)]) {
      (*stream).depth[__X(next, 573, (CHAR*)"ZlibDeflate", 109311)] = (*stream).depth[__X(n, 573, (CHAR*)"ZlibDeflate", 109311)] + 1;
    } else {
      (*stream).depth[__X(next, 573, (CHAR*)"ZlibDeflate", 109567)] = (*stream).depth[__X(m, 573, (CHAR*)"ZlibDeflate", 109567)] + 1;
    }
    (node->data)[__X(n, node->len[0], (CHAR*)"ZlibDeflate", 109850)].dadOrLen = next;
    (node->data)[__X(m, node->len[0], (CHAR*)"ZlibDeflate", 109876)].dadOrLen = next;
    (*stream).heap[1] = next;
    next += 1;
    ZlibDeflate_Sift(stream, stream__typ, &node, 1);
  } while (!((*stream).heapLen < 2));
  (*stream).heapMax -= 1;
  (*stream).heap[__X((*stream).heapMax, 573, (CHAR*)"ZlibDeflate", 111171)] = (*stream).heap[1];
  ZlibDeflate_GenBitLen(stream, stream__typ, tree, tree__typ);
  ZlibDeflate_GenCodes(&node, maxCode, (void*)(*stream).bitLenCount, 16);
}

static void ZlibDeflate_ScanTree (ZlibDeflate_Stream *stream, void **stream__typ, ZlibDeflate_Nodes node, SHORTINT max)
{
  SHORTINT n, prevLen, curLen, nextLen, count, maxCount, minCount, _for__52;
  prevLen = -1;
  nextLen = (node->data)[0].dadOrLen;
  count = 0;
  if (nextLen == 0) {
    maxCount = 138;
    minCount = 3;
  } else {
    maxCount = 7;
    minCount = 4;
  }
  (node->data)[__X(max + 1, node->len[0], (CHAR*)"ZlibDeflate", 115239)].dadOrLen = 32767;
  _for__52 = max;
  n = 0;
  while (n <= _for__52) {
    curLen = nextLen;
    nextLen = (node->data)[__X(n + 1, node->len[0], (CHAR*)"ZlibDeflate", 115764)].dadOrLen;
    count += 1;
    if (count >= maxCount || curLen != nextLen) {
      if (count < minCount) {
        ((*stream).bnode->data)[__X(curLen, (*stream).bnode->len[0], (CHAR*)"ZlibDeflate", 116783)].freqOrCode += count;
      } else if (curLen != 0) {
        if (curLen != prevLen) {
          ((*stream).bnode->data)[__X(curLen, (*stream).bnode->len[0], (CHAR*)"ZlibDeflate", 117313)].freqOrCode += 1;
        }
        ((*stream).bnode->data)[__X(16, (*stream).bnode->len[0], (CHAR*)"ZlibDeflate", 117759)].freqOrCode += 1;
      } else if (count <= 10) {
        ((*stream).bnode->data)[__X(17, (*stream).bnode->len[0], (CHAR*)"ZlibDeflate", 118271)].freqOrCode += 1;
      } else {
        ((*stream).bnode->data)[__X(18, (*stream).bnode->len[0], (CHAR*)"ZlibDeflate", 118783)].freqOrCode += 1;
      }
      count = 0;
      prevLen = curLen;
      if (nextLen == 0) {
        maxCount = 138;
        minCount = 3;
      } else if (curLen == nextLen) {
        maxCount = 6;
        minCount = 3;
      } else {
        maxCount = 7;
        minCount = 4;
      }
    }
    n += 1;
  }
}

static SHORTINT ZlibDeflate_BuildBitLenTree (ZlibDeflate_Stream *stream, void **stream__typ)
{
  SHORTINT max;
  ZlibDeflate_ScanTree(stream, stream__typ, (*stream).ltree.node, (*stream).ltree.maxCode);
  ZlibDeflate_ScanTree(stream, stream__typ, (*stream).dtree.node, (*stream).dtree.maxCode);
  ZlibDeflate_BuildTree(stream, stream__typ, &(*stream).btree, ZlibDeflate_Tree__typ);
  max = 18;
  while (max >= 3 && ((*stream).bnode->data)[__X(ZlibDeflate_BitOrder[__X(max, 19, (CHAR*)"ZlibDeflate", 124734)], (*stream).bnode->len[0], (CHAR*)"ZlibDeflate", 124734)].dadOrLen == 0) {
    max -= 1;
  }
  (*stream).optLen += (INTEGER)(((3 * (max + 1) + 5) + 5) + 4);
  return max;
}

static void ZlibDeflate_SendTree (ZlibDeflate_Stream *stream, void **stream__typ, ZlibDeflate_Nodes node, SHORTINT max)
{
  SHORTINT n, prevLen, curLen, nextLen, count, maxCount, minCount, _for__63;
  ZlibDeflate_Nodes _ptr__62 = NIL;
  ZlibDeflate_Nodes _ptr__61 = NIL;
  ZlibDeflate_Nodes _ptr__60 = NIL;
  ZlibDeflate_Nodes _ptr__59 = NIL;
  ZlibDeflate_Nodes _ptr__58 = NIL;
  prevLen = -1;
  nextLen = (node->data)[0].dadOrLen;
  count = 0;
  if (nextLen == 0) {
    maxCount = 138;
    minCount = 3;
  } else {
    maxCount = 7;
    minCount = 4;
  }
  (node->data)[__X(max + 1, node->len[0], (CHAR*)"ZlibDeflate", 128551)].dadOrLen = 32767;
  _for__63 = max;
  n = 0;
  while (n <= _for__63) {
    curLen = nextLen;
    nextLen = (node->data)[__X(n + 1, node->len[0], (CHAR*)"ZlibDeflate", 129076)].dadOrLen;
    count += 1;
    if (count >= maxCount || curLen != nextLen) {
      if (count < minCount) {
        do {
          _ptr__62 = (*stream).bnode;
          ZlibDeflate_SendCode(stream, stream__typ, &(_ptr__62->data)[__X(curLen, _ptr__62->len[0], (CHAR*)"ZlibDeflate", 117313)], ZlibDeflate_Node__typ);
          count -= 1;
        } while (!(count == 0));
      } else if (curLen != 0) {
        if (curLen != prevLen) {
          _ptr__61 = (*stream).bnode;
          ZlibDeflate_SendCode(stream, stream__typ, &(_ptr__61->data)[__X(curLen, _ptr__61->len[0], (CHAR*)"ZlibDeflate", 130815)], ZlibDeflate_Node__typ);
          count -= 1;
        }
        __ASSERT(3 <= count && count <= 6, 110, (CHAR*)"ZlibDeflate", 132140);
        _ptr__60 = (*stream).bnode;
        ZlibDeflate_SendCode(stream, stream__typ, &(_ptr__60->data)[__X(16, _ptr__60->len[0], (CHAR*)"ZlibDeflate", 132140)], ZlibDeflate_Node__typ);
        ZlibDeflate_SendBits(stream, stream__typ, count - 3, 2);
      } else if (count <= 10) {
        _ptr__59 = (*stream).bnode;
        ZlibDeflate_SendCode(stream, stream__typ, &(_ptr__59->data)[__X(17, _ptr__59->len[0], (CHAR*)"ZlibDeflate", 132607)], ZlibDeflate_Node__typ);
        ZlibDeflate_SendBits(stream, stream__typ, count - 3, 3);
      } else {
        _ptr__58 = (*stream).bnode;
        ZlibDeflate_SendCode(stream, stream__typ, &(_ptr__58->data)[__X(18, _ptr__58->len[0], (CHAR*)"ZlibDeflate", 133119)], ZlibDeflate_Node__typ);
        ZlibDeflate_SendBits(stream, stream__typ, count - 11, 7);
      }
      count = 0;
      prevLen = curLen;
      if (nextLen == 0) {
        maxCount = 138;
        minCount = 3;
      } else if (curLen == nextLen) {
        maxCount = 6;
        minCount = 3;
      } else {
        maxCount = 7;
        minCount = 4;
      }
    }
    n += 1;
  }
}

static void ZlibDeflate_SendAllTrees (ZlibDeflate_Stream *stream, void **stream__typ, SHORTINT lcodes, SHORTINT dcodes, SHORTINT blcodes)
{
  SHORTINT rank, _for__54;
  __ASSERT((lcodes >= 257 && dcodes >= 1) && blcodes >= 4, 100, (CHAR*)"ZlibDeflate", 138046);
  __ASSERT((lcodes <= 286 && dcodes <= 30) && blcodes <= 19, 101, (CHAR*)"ZlibDeflate", 138325);
  ZlibDeflate_SendBits(stream, stream__typ, lcodes - 257, 5);
  ZlibDeflate_SendBits(stream, stream__typ, dcodes - 1, 5);
  ZlibDeflate_SendBits(stream, stream__typ, blcodes - 4, 4);
  _for__54 = blcodes - 1;
  rank = 0;
  while (rank <= _for__54) {
    ZlibDeflate_SendBits(stream, stream__typ, ((*stream).bnode->data)[__X(ZlibDeflate_BitOrder[__X(rank, 19, (CHAR*)"ZlibDeflate", 139263)], (*stream).bnode->len[0], (CHAR*)"ZlibDeflate", 139263)].dadOrLen, 3);
    rank += 1;
  }
  ZlibDeflate_SendTree(stream, stream__typ, (*stream).lnode, lcodes - 1);
  ZlibDeflate_SendTree(stream, stream__typ, (*stream).dnode, dcodes - 1);
}

static void ZlibDeflate_InitStaticTrees (void)
{
  INTEGER n, code;
  SHORTINT length, dist;
  SHORTINT count[16];
  INTEGER _for__40, _for__39, _for__38;
  ZlibDeflate_ExtraLenBits = __NEWARR(NIL, 2, 2, 1, 1, (SYSTEM_ARRLEN)29);
  n = 0;
  while (n <= 3) {
    (ZlibDeflate_ExtraLenBits->data)[__X(n, ZlibDeflate_ExtraLenBits->len[0], (CHAR*)"ZlibDeflate", 142632)] = 0;
    n += 1;
  }
  n = 4;
  while (n <= 27) {
    (ZlibDeflate_ExtraLenBits->data)[__X(n, ZlibDeflate_ExtraLenBits->len[0], (CHAR*)"ZlibDeflate", 142921)] = (SHORTINT)__ASHR(n - 4, 2, INTEGER);
    n += 1;
  }
  (ZlibDeflate_ExtraLenBits->data)[__X(28, ZlibDeflate_ExtraLenBits->len[0], (CHAR*)"ZlibDeflate", 143139)] = 0;
  ZlibDeflate_ExtraDistBits = __NEWARR(NIL, 2, 2, 1, 1, (SYSTEM_ARRLEN)30);
  n = 0;
  while (n <= 1) {
    (ZlibDeflate_ExtraDistBits->data)[__X(n, ZlibDeflate_ExtraDistBits->len[0], (CHAR*)"ZlibDeflate", 143913)] = 0;
    n += 1;
  }
  n = 2;
  while (n <= 29) {
    (ZlibDeflate_ExtraDistBits->data)[__X(n, ZlibDeflate_ExtraDistBits->len[0], (CHAR*)"ZlibDeflate", 144200)] = (SHORTINT)__ASHR(n - 2, 1, INTEGER);
    n += 1;
  }
  ZlibDeflate_ExtraBitBits = __NEWARR(NIL, 2, 2, 1, 1, (SYSTEM_ARRLEN)19);
  n = 0;
  while (n <= 15) {
    (ZlibDeflate_ExtraBitBits->data)[__X(n, ZlibDeflate_ExtraBitBits->len[0], (CHAR*)"ZlibDeflate", 144947)] = 0;
    n += 1;
  }
  (ZlibDeflate_ExtraBitBits->data)[__X(16, ZlibDeflate_ExtraBitBits->len[0], (CHAR*)"ZlibDeflate", 145184)] = 2;
  (ZlibDeflate_ExtraBitBits->data)[__X(17, ZlibDeflate_ExtraBitBits->len[0], (CHAR*)"ZlibDeflate", 145217)] = 3;
  (ZlibDeflate_ExtraBitBits->data)[__X(18, ZlibDeflate_ExtraBitBits->len[0], (CHAR*)"ZlibDeflate", 145250)] = 7;
  ZlibDeflate_BitOrder[0] = 16;
  ZlibDeflate_BitOrder[1] = 17;
  ZlibDeflate_BitOrder[2] = 18;
  ZlibDeflate_BitOrder[3] = 0;
  ZlibDeflate_BitOrder[4] = 8;
  ZlibDeflate_BitOrder[5] = 7;
  ZlibDeflate_BitOrder[6] = 9;
  ZlibDeflate_BitOrder[7] = 6;
  ZlibDeflate_BitOrder[8] = 10;
  ZlibDeflate_BitOrder[9] = 5;
  ZlibDeflate_BitOrder[10] = 11;
  ZlibDeflate_BitOrder[11] = 4;
  ZlibDeflate_BitOrder[12] = 12;
  ZlibDeflate_BitOrder[13] = 3;
  ZlibDeflate_BitOrder[14] = 13;
  ZlibDeflate_BitOrder[15] = 2;
  ZlibDeflate_BitOrder[16] = 14;
  ZlibDeflate_BitOrder[17] = 1;
  ZlibDeflate_BitOrder[18] = 15;
  length = 0;
  code = 0;
  while (code <= 27) {
    ZlibDeflate_BaseLength[__X(code, 29, (CHAR*)"ZlibDeflate", 147484)] = length;
    _for__40 = __ASH(1, (ZlibDeflate_ExtraLenBits->data)[__X(code, ZlibDeflate_ExtraLenBits->len[0], (CHAR*)"ZlibDeflate", 147758)], INTEGER) - 1;
    n = 0;
    while (n <= _for__40) {
      ZlibDeflate_LengthCode[__X(length, 256, (CHAR*)"ZlibDeflate", 148002)] = (CHAR)code;
      length += 1;
      n += 1;
    }
    code += 1;
  }
  __ASSERT(length == 256, 110, (CHAR*)"ZlibDeflate", 148762);
  ZlibDeflate_LengthCode[__X(length - 1, 256, (CHAR*)"ZlibDeflate", 149540)] = (CHAR)code;
  dist = 0;
  code = 0;
  while (code <= 15) {
    ZlibDeflate_BaseDist[__X(code, 30, (CHAR*)"ZlibDeflate", 150808)] = dist;
    _for__39 = __ASH(1, (ZlibDeflate_ExtraDistBits->data)[__X(code, ZlibDeflate_ExtraDistBits->len[0], (CHAR*)"ZlibDeflate", 151087)], INTEGER) - 1;
    n = 0;
    while (n <= _for__39) {
      ZlibDeflate_DistCode[__X(dist, 512, (CHAR*)"ZlibDeflate", 151326)] = (CHAR)code;
      dist += 1;
      n += 1;
    }
    code += 1;
  }
  __ASSERT(dist == 256, 111, (CHAR*)"ZlibDeflate", 152088);
  dist = (SHORTINT)__ASHR((INTEGER)dist, 7, INTEGER);
  code = 16;
  while (code <= 29) {
    ZlibDeflate_BaseDist[__X(code, 30, (CHAR*)"ZlibDeflate", 153127)] = (SHORTINT)__ASHL((INTEGER)dist, 7, INTEGER);
    _for__38 = __ASH(1, (ZlibDeflate_ExtraDistBits->data)[__X(code, ZlibDeflate_ExtraDistBits->len[0], (CHAR*)"ZlibDeflate", 153395)] - 7, INTEGER) - 1;
    n = 0;
    while (n <= _for__38) {
      ZlibDeflate_DistCode[__X(256 + dist, 512, (CHAR*)"ZlibDeflate", 153636)] = (CHAR)code;
      dist += 1;
      n += 1;
    }
    code += 1;
  }
  __ASSERT(dist == 256, 112, (CHAR*)"ZlibDeflate", 154392);
  ZlibDeflate_LTree.node = __NEWARR(NIL, 4, 2, 1, 1, (SYSTEM_ARRLEN)288);
  ZlibDeflate_LTree.bits = ZlibDeflate_ExtraLenBits;
  ZlibDeflate_LTree.base = 257;
  ZlibDeflate_LTree.elems = 286;
  ZlibDeflate_LTree.maxLength = 15;
  n = 0;
  while (n <= 15) {
    count[__X(n, 16, (CHAR*)"ZlibDeflate", 155687)] = 0;
    n += 1;
  }
  n = 0;
  while (n <= 143) {
    (ZlibDeflate_LTree.node->data)[__X(n, ZlibDeflate_LTree.node->len[0], (CHAR*)"ZlibDeflate", 155953)].dadOrLen = 8;
    n += 1;
  }
  count[8] += 144;
  n = 144;
  while (n <= 255) {
    (ZlibDeflate_LTree.node->data)[__X(n, ZlibDeflate_LTree.node->len[0], (CHAR*)"ZlibDeflate", 156211)].dadOrLen = 9;
    n += 1;
  }
  count[9] += 112;
  n = 256;
  while (n <= 279) {
    (ZlibDeflate_LTree.node->data)[__X(n, ZlibDeflate_LTree.node->len[0], (CHAR*)"ZlibDeflate", 156467)].dadOrLen = 7;
    n += 1;
  }
  count[7] += 24;
  n = 280;
  while (n <= 287) {
    (ZlibDeflate_LTree.node->data)[__X(n, ZlibDeflate_LTree.node->len[0], (CHAR*)"ZlibDeflate", 156723)].dadOrLen = 8;
    n += 1;
  }
  count[8] += 8;
  ZlibDeflate_GenCodes(&ZlibDeflate_LTree.node, 287, (void*)count, 16);
  ZlibDeflate_DTree.node = __NEWARR(NIL, 4, 2, 1, 1, (SYSTEM_ARRLEN)30);
  ZlibDeflate_DTree.bits = ZlibDeflate_ExtraDistBits;
  ZlibDeflate_DTree.base = 0;
  ZlibDeflate_DTree.elems = 30;
  ZlibDeflate_DTree.maxLength = 15;
  n = 0;
  while (n <= 29) {
    (ZlibDeflate_DTree.node->data)[__X(n, ZlibDeflate_DTree.node->len[0], (CHAR*)"ZlibDeflate", 159005)].dadOrLen = 5;
    (ZlibDeflate_DTree.node->data)[__X(n, ZlibDeflate_DTree.node->len[0], (CHAR*)"ZlibDeflate", 159487)].freqOrCode = ZlibDeflate_ReverseBits((SHORTINT)n, 5);
    n += 1;
  }
  ZlibDeflate_BTree.node = NIL;
  ZlibDeflate_BTree.bits = ZlibDeflate_ExtraBitBits;
  ZlibDeflate_BTree.base = 0;
  ZlibDeflate_BTree.elems = 19;
  ZlibDeflate_BTree.maxLength = 7;
}

static void ZlibDeflate_InitBlock (ZlibDeflate_Stream *stream, void **stream__typ)
{
  INTEGER n;
  n = 0;
  while (n <= 285) {
    ((*stream).lnode->data)[__X(n, (*stream).lnode->len[0], (CHAR*)"ZlibDeflate", 162369)].freqOrCode = 0;
    n += 1;
  }
  n = 0;
  while (n <= 29) {
    ((*stream).dnode->data)[__X(n, (*stream).dnode->len[0], (CHAR*)"ZlibDeflate", 162623)].freqOrCode = 0;
    n += 1;
  }
  n = 0;
  while (n <= 18) {
    ((*stream).bnode->data)[__X(n, (*stream).bnode->len[0], (CHAR*)"ZlibDeflate", 162878)].freqOrCode = 0;
    n += 1;
  }
  ((*stream).lnode->data)[__X(256, (*stream).lnode->len[0], (CHAR*)"ZlibDeflate", 163111)].freqOrCode = 1;
  (*stream).optLen = 0;
  (*stream).staticLen = 0;
  (*stream).lastLit = 0;
}

static void ZlibDeflate_InitTrees (ZlibDeflate_Stream *stream, void **stream__typ)
{
  (*stream).lnode = __NEWARR(NIL, 4, 2, 1, 1, (SYSTEM_ARRLEN)573);
  (*stream).dnode = __NEWARR(NIL, 4, 2, 1, 1, (SYSTEM_ARRLEN)61);
  (*stream).bnode = __NEWARR(NIL, 4, 2, 1, 1, (SYSTEM_ARRLEN)39);
  (*stream).ltree.node = (*stream).lnode;
  (*stream).dtree.node = (*stream).dnode;
  (*stream).btree.node = (*stream).bnode;
  (*stream).ltree.static_ = ZlibDeflate_LTree;
  (*stream).dtree.static_ = ZlibDeflate_DTree;
  (*stream).btree.static_ = ZlibDeflate_BTree;
  (*stream).buf = 0;
  (*stream).bits = 0;
  (*stream).lastEobLen = 8;
  ZlibDeflate_InitBlock(stream, stream__typ);
}

static void ZlibDeflate_FreeTrees (ZlibDeflate_Stream *stream, void **stream__typ)
{
  (*stream).lnode = NIL;
  (*stream).dnode = NIL;
  (*stream).bnode = NIL;
}

static void ZlibDeflate_AlignTrees (ZlibDeflate_Stream *stream, void **stream__typ)
{
  ZlibDeflate_Nodes _ptr__3 = NIL;
  ZlibDeflate_Nodes _ptr__2 = NIL;
  ZlibDeflate_SendBits(stream, stream__typ, 2, 3);
  _ptr__3 = ZlibDeflate_LTree.node;
  ZlibDeflate_SendCode(stream, stream__typ, &(_ptr__3->data)[__X(256, _ptr__3->len[0], (CHAR*)"ZlibDeflate", 170032)], ZlibDeflate_Node__typ);
  ZlibDeflate_FlushBits(stream, stream__typ);
  if (((1 + (*stream).lastEobLen) + 10) - (*stream).bits < 9) {
    ZlibDeflate_SendBits(stream, stream__typ, 2, 3);
    _ptr__2 = ZlibDeflate_LTree.node;
    ZlibDeflate_SendCode(stream, stream__typ, &(_ptr__2->data)[__X(256, _ptr__2->len[0], (CHAR*)"ZlibDeflate", 171825)], ZlibDeflate_Node__typ);
    ZlibDeflate_FlushBits(stream, stream__typ);
  }
  (*stream).lastEobLen = 7;
}

static void ZlibDeflate_CopyBlock (ZlibDeflate_Stream *stream, void **stream__typ, CHAR *buf, INTEGER buf__len, INTEGER offset, INTEGER len, BOOLEAN header)
{
  ZlibDeflate_WindupBits(stream, stream__typ);
  (*stream).lastEobLen = 8;
  if (header) {
    ZlibDeflate_Put16BitsLSB(&(*stream).pend, ZlibDeflate_PendingBuffer__typ, len);
    ZlibDeflate_Put16BitsLSB(&(*stream).pend, ZlibDeflate_PendingBuffer__typ, -(len + 1));
  }
  while (len > 0) {
    ZlibDeflate_PutChar(&(*stream).pend, ZlibDeflate_PendingBuffer__typ, buf[__X(offset, buf__len, (CHAR*)"ZlibDeflate", 176419)]);
    offset += 1;
    len -= 1;
  }
}

static void ZlibDeflate_StoreBlock (ZlibDeflate_Stream *stream, void **stream__typ, CHAR *buf, INTEGER buf__len, INTEGER offset, INTEGER len, BOOLEAN eof)
{
  INTEGER value;
  value = 0;
  if (eof) {
    value += 1;
  }
  ZlibDeflate_SendBits(stream, stream__typ, value, 3);
  ZlibDeflate_CopyBlock(stream, stream__typ, (void*)buf, buf__len, offset, len, 1);
}

static void ZlibDeflate_CompressBlock (ZlibDeflate_Stream *stream, void **stream__typ, ZlibDeflate_Nodes lnode, ZlibDeflate_Nodes dnode)
{
  SHORTINT dist, lc, code, extra;
  INTEGER lx;
  if ((*stream).lastLit != 0) {
    lx = 0;
    do {
      dist = (*(*stream).dbuf)[__X(lx, 16384, (CHAR*)"ZlibDeflate", 183578)];
      lc = (SHORTINT)(*(*stream).lbuf)[__X(lx, 16384, (CHAR*)"ZlibDeflate", 183837)];
      lx += 1;
      if (dist == 0) {
        ZlibDeflate_SendCode(stream, stream__typ, &(lnode->data)[__X(lc, lnode->len[0], (CHAR*)"ZlibDeflate", 184607)], ZlibDeflate_Node__typ);
      } else {
        code = (SHORTINT)ZlibDeflate_LengthCode[__X(lc, 256, (CHAR*)"ZlibDeflate", 185119)];
        ZlibDeflate_SendCode(stream, stream__typ, &(lnode->data)[__X((code + 256) + 1, lnode->len[0], (CHAR*)"ZlibDeflate", 185392)], ZlibDeflate_Node__typ);
        extra = (ZlibDeflate_ExtraLenBits->data)[__X(code, ZlibDeflate_ExtraLenBits->len[0], (CHAR*)"ZlibDeflate", 185631)];
        if (extra != 0) {
          lc -= ZlibDeflate_BaseLength[__X(code, 29, (CHAR*)"ZlibDeflate", 186142)];
          ZlibDeflate_SendBits(stream, stream__typ, lc, extra);
        }
        dist -= 1;
        if (dist < 256) {
          code = (SHORTINT)ZlibDeflate_DistCode[__X(dist, 512, (CHAR*)"ZlibDeflate", 187186)];
        } else {
          code = (SHORTINT)ZlibDeflate_DistCode[__X(256 + __ASHR((INTEGER)dist, 7, INTEGER), 512, (CHAR*)"ZlibDeflate", 187647)];
        }
        __ASSERT(code < 30, 110, (CHAR*)"ZlibDeflate", 187937);
        ZlibDeflate_SendCode(stream, stream__typ, &(dnode->data)[__X(code, dnode->len[0], (CHAR*)"ZlibDeflate", 188193)], ZlibDeflate_Node__typ);
        extra = (ZlibDeflate_ExtraDistBits->data)[__X(code, ZlibDeflate_ExtraDistBits->len[0], (CHAR*)"ZlibDeflate", 188448)];
        if (extra != 0) {
          dist -= ZlibDeflate_BaseDist[__X(code, 30, (CHAR*)"ZlibDeflate", 188958)];
          ZlibDeflate_SendBits(stream, stream__typ, dist, extra);
        }
      }
    } while (!(lx == (*stream).lastLit));
  }
  ZlibDeflate_SendCode(stream, stream__typ, &(lnode->data)[__X(256, lnode->len[0], (CHAR*)"ZlibDeflate", 190754)], ZlibDeflate_Node__typ);
  (*stream).lastEobLen = (lnode->data)[__X(256, lnode->len[0], (CHAR*)"ZlibDeflate", 191231)].dadOrLen;
}

static void ZlibDeflate_FlushBlock (ZlibDeflate_Stream *stream, void **stream__typ, CHAR *buf, INTEGER buf__len, INTEGER pos, INTEGER len, BOOLEAN eof)
{
  SHORTINT max;
  INTEGER optLen, staticLen, value;
  if ((*stream).level > 0) {
    if ((*stream).dataType == 2) {
      ZlibDeflate_SetDataType(stream, stream__typ);
    }
    ZlibDeflate_BuildTree(stream, stream__typ, &(*stream).ltree, ZlibDeflate_Tree__typ);
    ZlibDeflate_BuildTree(stream, stream__typ, &(*stream).dtree, ZlibDeflate_Tree__typ);
    max = ZlibDeflate_BuildBitLenTree(stream, stream__typ);
    optLen = __ASHR(((*stream).optLen + 3) + 7, 3, INTEGER);
    staticLen = __ASHR(((*stream).staticLen + 3) + 7, 3, INTEGER);
    if (staticLen < optLen) {
      optLen = staticLen;
    }
  } else {
    __ASSERT(pos >= 0, 110, (CHAR*)"ZlibDeflate", 197655);
    optLen = len + 5;
    staticLen = optLen;
  }
  if (len + 4 <= optLen) {
    __ASSERT(pos >= 0, 111, (CHAR*)"ZlibDeflate", 198935);
    ZlibDeflate_StoreBlock(stream, stream__typ, (void*)buf, buf__len, pos, len, eof);
  } else if (staticLen == optLen) {
    value = 2;
    if (eof) {
      value += 1;
    }
    ZlibDeflate_SendBits(stream, stream__typ, value, 3);
    ZlibDeflate_CompressBlock(stream, stream__typ, ZlibDeflate_LTree.node, ZlibDeflate_DTree.node);
  } else {
    value = 4;
    if (eof) {
      value += 1;
    }
    ZlibDeflate_SendBits(stream, stream__typ, value, 3);
    ZlibDeflate_SendAllTrees(stream, stream__typ, (*stream).ltree.maxCode + 1, (*stream).dtree.maxCode + 1, max + 1);
    ZlibDeflate_CompressBlock(stream, stream__typ, (*stream).lnode, (*stream).dnode);
  }
  ZlibDeflate_InitBlock(stream, stream__typ);
  if (eof) {
    ZlibDeflate_WindupBits(stream, stream__typ);
  }
}

static BOOLEAN ZlibDeflate_TallyLit (ZlibDeflate_Stream *stream, void **stream__typ, CHAR ch)
{
  (*(*stream).lbuf)[__X((*stream).lastLit, 16384, (CHAR*)"ZlibDeflate", 204834)] = ch;
  (*(*stream).dbuf)[__X((*stream).lastLit, 16384, (CHAR*)"ZlibDeflate", 205089)] = 0;
  (*stream).lastLit += 1;
  ((*stream).lnode->data)[__X((SHORTINT)ch, (*stream).lnode->len[0], (CHAR*)"ZlibDeflate", 205606)].freqOrCode += 1;
  return (*stream).lastLit == 16383;
}

static BOOLEAN ZlibDeflate_TallyDistLen (ZlibDeflate_Stream *stream, void **stream__typ, SHORTINT dist, SHORTINT len)
{
  __ASSERT(len < 256, 99, (CHAR*)"ZlibDeflate", 207382);
  (*(*stream).lbuf)[__X((*stream).lastLit, 16384, (CHAR*)"ZlibDeflate", 207656)] = (CHAR)len;
  (*(*stream).dbuf)[__X((*stream).lastLit, 16384, (CHAR*)"ZlibDeflate", 207908)] = dist;
  (*stream).lastLit += 1;
  dist -= 1;
  ((*stream).lnode->data)[__X(((SHORTINT)ZlibDeflate_LengthCode[__X(len, 256, (CHAR*)"ZlibDeflate", 208706)] + 256) + 1, (*stream).lnode->len[0], (CHAR*)"ZlibDeflate", 208706)].freqOrCode += 1;
  if (dist < 256) {
    dist = (SHORTINT)ZlibDeflate_DistCode[__X(dist, 512, (CHAR*)"ZlibDeflate", 209151)];
  } else {
    dist = (SHORTINT)ZlibDeflate_DistCode[__X(256 + __ASHR((INTEGER)dist, 7, INTEGER), 512, (CHAR*)"ZlibDeflate", 209407)];
  }
  ((*stream).dnode->data)[__X(dist, (*stream).dnode->len[0], (CHAR*)"ZlibDeflate", 209699)].freqOrCode += 1;
  return (*stream).lastLit == 16383;
}

static void ZlibDeflate_ClearHash (ZlibDeflate_Stream *stream, void **stream__typ)
{
  INTEGER i;
  i = 0;
  while (i <= 32767) {
    (*(*stream).head)[__X(i, 32768, (CHAR*)"ZlibDeflate", 212735)] = 0;
    i += 1;
  }
}

static void ZlibDeflate_UpdateHash (INTEGER *h, CHAR ch)
{
  *h = __MASK((INTEGER)((SET)__ASHL(*h, 5, INTEGER) ^ (SET)((INTEGER)ch)), -32768);
}

static void ZlibDeflate_InsertString (ZlibDeflate_Stream *stream, void **stream__typ, INTEGER pos, INTEGER *head)
{
  ZlibDeflate_UpdateHash(&(*stream).hash, (*(*stream).window)[__X((pos + 3) - 1, 65536, (CHAR*)"ZlibDeflate", 217147)]);
  *head = (*(*stream).head)[__X((*stream).hash, 32768, (CHAR*)"ZlibDeflate", 217377)];
  (*(*stream).prev)[__X(__MASK(pos, -32768), 32768, (CHAR*)"ZlibDeflate", 217640)] = *head;
  (*(*stream).head)[__X((*stream).hash, 32768, (CHAR*)"ZlibDeflate", 218111)] = pos;
}

static void ZlibDeflate_InitMatches (ZlibDeflate_Stream *stream, void **stream__typ)
{
  ZlibDeflate_ClearHash(stream, stream__typ);
  (*stream).string = 0;
  (*stream).block = 0;
  (*stream).lookAhead = 0;
  (*stream).matchLen = 2;
  (*stream).prevLen = 2;
  (*stream).prevAvail = 0;
  (*stream).hash = 0;
}

static INTEGER ZlibDeflate_LongestMatch (ZlibDeflate_Stream *stream, void **stream__typ, INTEGER cur)
{
  INTEGER chainLen, scan, match, len, bestLen, niceLen, limit, strend;
  CHAR scanEnd1, scanEnd;
  bestLen = (*stream).prevLen;
  if (bestLen >= (INTEGER)ZlibDeflate_ConfigTable[__X((*stream).level, 10, (CHAR*)"ZlibDeflate", 226820)].GoodLen) {
    chainLen = __ASHR(ZlibDeflate_ConfigTable[__X((*stream).level, 10, (CHAR*)"ZlibDeflate", 226303)].MaxChain, 2, SHORTINT);
  } else {
    chainLen = ZlibDeflate_ConfigTable[__X((*stream).level, 10, (CHAR*)"ZlibDeflate", 226608)].MaxChain;
  }
  if ((INTEGER)ZlibDeflate_ConfigTable[__X((*stream).level, 10, (CHAR*)"ZlibDeflate", 228100)].NiceLen > (*stream).lookAhead) {
    niceLen = (*stream).lookAhead;
  } else {
    niceLen = ZlibDeflate_ConfigTable[__X((*stream).level, 10, (CHAR*)"ZlibDeflate", 228095)].NiceLen;
  }
  scan = (*stream).string;
  if (scan > 32506) {
    limit = scan - 32506;
  } else {
    limit = 0;
  }
  strend = scan + 258;
  scanEnd1 = (*(*stream).window)[__X((scan + bestLen) - 1, 65536, (CHAR*)"ZlibDeflate", 229166)];
  scanEnd = (*(*stream).window)[__X(scan + bestLen, 65536, (CHAR*)"ZlibDeflate", 229417)];
  __ASSERT(scan <= 65274, 110, (CHAR*)"ZlibDeflate", 229683);
  len = -1;
  do {
    __ASSERT(cur < (*stream).string, 111, (CHAR*)"ZlibDeflate", 230434);
    match = cur;
    if ((((*(*stream).window)[__X(match + bestLen, 65536, (CHAR*)"ZlibDeflate", 236293)] == scanEnd && (*(*stream).window)[__X((match + bestLen) - 1, 65536, (CHAR*)"ZlibDeflate", 236293)] == scanEnd1) && (*(*stream).window)[__X(match, 65536, (CHAR*)"ZlibDeflate", 236293)] == (*(*stream).window)[__X(scan, 65536, (CHAR*)"ZlibDeflate", 236293)]) && (*(*stream).window)[__X(match + 1, 65536, (CHAR*)"ZlibDeflate", 236293)] == (*(*stream).window)[__X(scan + 1, 65536, (CHAR*)"ZlibDeflate", 236293)]) {
      scan += 2;
      match += 2;
      __ASSERT((*(*stream).window)[__X(match, 65536, (CHAR*)"ZlibDeflate", 233018)] == (*(*stream).window)[__X(scan, 65536, (CHAR*)"ZlibDeflate", 233018)], 112, (CHAR*)"ZlibDeflate", 233018);
      do {
        match += 1;
        scan += 1;
      } while (!((*(*stream).window)[__X(match, 65536, (CHAR*)"ZlibDeflate", 233727)] != (*(*stream).window)[__X(scan, 65536, (CHAR*)"ZlibDeflate", 233727)] || scan >= strend));
      __ASSERT(scan <= 65535, 113, (CHAR*)"ZlibDeflate", 234026);
      len = 258 - (strend - scan);
      scan = strend - 258;
      if (len > bestLen) {
        (*stream).match = cur;
        bestLen = len;
        scanEnd1 = (*(*stream).window)[__X((scan + bestLen) - 1, 65536, (CHAR*)"ZlibDeflate", 235569)];
        scanEnd = (*(*stream).window)[__X(scan + bestLen, 65536, (CHAR*)"ZlibDeflate", 236031)];
      }
    }
    cur = (*(*stream).prev)[__X(__MASK(cur, -32768), 32768, (CHAR*)"ZlibDeflate", 236584)];
    chainLen -= 1;
  } while (!((len >= niceLen || cur <= limit) || chainLen == 0));
  if (bestLen > 258) {
    bestLen = 258;
  }
  if (bestLen <= (*stream).lookAhead) {
    return bestLen;
  } else {
    return (*stream).lookAhead;
  }
  __RETCHK((CHAR*)"ZlibDeflate", 238591);
}

static void ZlibDeflate_CheckMatch (ZlibDeflate_Stream *stream, void **stream__typ, INTEGER start, INTEGER match, INTEGER len)
{
  while (len != 0) {
    __ASSERT((*(*stream).window)[__X(match, 65536, (CHAR*)"ZlibDeflate", 240437)] == (*(*stream).window)[__X(start, 65536, (CHAR*)"ZlibDeflate", 240437)], 0, (CHAR*)"ZlibDeflate", 240437);
    match += 1;
    start += 1;
    len -= 1;
  }
}

static void ZlibDeflate_FillWindow (ZlibDeflate_Stream *stream, void **stream__typ)
{
  INTEGER n, len, more;
  ZlibDeflate_Window *_ptr__26 = NIL;
  ZlibDeflate_Window *_ptr__25 = NIL;
  more = 65536 - ((*stream).lookAhead + (*stream).string);
  do {
    if ((*stream).string >= 65274) {
      __MOVE((SYSTEM_ADRINT)&(*(*stream).window)[32768], (SYSTEM_ADRINT)&(*(*stream).window)[0], 32768);
      (*stream).match -= 32768;
      (*stream).string -= 32768;
      (*stream).block -= 32768;
      n = 32768;
      do {
        n -= 1;
        if ((*(*stream).head)[__X(n, 32768, (CHAR*)"ZlibDeflate", 247295)] >= 32768) {
          (*(*stream).head)[__X(n, 32768, (CHAR*)"ZlibDeflate", 246527)] -= 32768;
        } else {
          (*(*stream).head)[__X(n, 32768, (CHAR*)"ZlibDeflate", 247039)] = 0;
        }
      } while (!(n == 0));
      n = 32768;
      do {
        n -= 1;
        if ((*(*stream).prev)[__X(n, 32768, (CHAR*)"ZlibDeflate", 249599)] >= 32768) {
          (*(*stream).prev)[__X(n, 32768, (CHAR*)"ZlibDeflate", 248831)] -= 32768;
        } else {
          (*(*stream).prev)[__X(n, 32768, (CHAR*)"ZlibDeflate", 249343)] = 0;
        }
      } while (!(n == 0));
      more += 32768;
    }
    len = (*stream).in.avail;
    if (len == 0) {
      return;
    }
    __ASSERT(more >= 2, 110, (CHAR*)"ZlibDeflate", 250904);
    if (len > more) {
      len = more;
    }
    _ptr__26 = (*stream).window;
    ZlibBuffers_ReadBytes(&(*stream).in, ZlibBuffers_Buffer__typ, (void*)*_ptr__26, 65536, (*stream).string + (*stream).lookAhead, len);
    if ((*stream).wrapper) {
      (*stream).adler = (_ptr__25 = (*stream).window, 
        Zlib_Adler32((*stream).adler, (void*)*_ptr__25, 65536, (*stream).string + (*stream).lookAhead, len));
    }
    (*stream).lookAhead += len;
    more -= len;
    if ((*stream).lookAhead >= 3) {
      (*stream).hash = (INTEGER)(*(*stream).window)[__X((*stream).string, 65536, (CHAR*)"ZlibDeflate", 253241)];
      ZlibDeflate_UpdateHash(&(*stream).hash, (*(*stream).window)[__X((*stream).string + 1, 65536, (CHAR*)"ZlibDeflate", 253500)]);
    }
  } while (!((*stream).lookAhead >= 262 || (*stream).in.avail == 0));
}

static BYTE ZlibDeflate_CompressStored (ZlibDeflate_Stream *stream, void **stream__typ, BYTE flush)
{
  ZlibDeflate_Window *_ptr__21 = NIL;
  ZlibDeflate_Window *_ptr__20 = NIL;
  for (;;) {
    if ((*stream).lookAhead <= 1) {
      __ASSERT((*stream).string < 65274 || (*stream).block >= 32768, 111, (CHAR*)"ZlibDeflate", 258904);
      ZlibDeflate_FillWindow(stream, stream__typ);
      if ((*stream).lookAhead == 0) {
        if (flush == 0) {
          return 1;
        } else {
          break;
        }
      }
    }
    __ASSERT((*stream).block >= 0, 112, (CHAR*)"ZlibDeflate", 260896);
    (*stream).string += (*stream).lookAhead;
    (*stream).lookAhead = 0;
    __ASSERT((*stream).string < (*stream).block + 65531, 113, (CHAR*)"ZlibDeflate", 262458);
    if ((*stream).string - (*stream).block >= 32506) {
      _ptr__21 = (*stream).window;
      ZlibDeflate_FlushBlock(stream, stream__typ, (void*)*_ptr__21, 65536, (*stream).block, (*stream).string - (*stream).block, 0);
      (*stream).block = (*stream).string;
      ZlibDeflate_FlushPending(&(*stream).pend, ZlibDeflate_PendingBuffer__typ, &(*stream).out, ZlibBuffers_Buffer__typ);
      if ((*stream).out.avail == 0) {
        return 1;
      }
    }
  }
  _ptr__20 = (*stream).window;
  ZlibDeflate_FlushBlock(stream, stream__typ, (void*)*_ptr__20, 65536, (*stream).block, (*stream).string - (*stream).block, flush == 4);
  (*stream).block = (*stream).string;
  ZlibDeflate_FlushPending(&(*stream).pend, ZlibDeflate_PendingBuffer__typ, &(*stream).out, ZlibBuffers_Buffer__typ);
  if ((*stream).out.avail == 0 && flush == 4) {
    return 3;
  } else if ((*stream).out.avail == 0) {
    return 1;
  } else if (flush == 4) {
    return 4;
  } else {
    return 2;
  }
  __RETCHK((CHAR*)"ZlibDeflate", 267007);
}

static BYTE ZlibDeflate_CompressFast (ZlibDeflate_Stream *stream, void **stream__typ, BYTE flush)
{
  INTEGER head;
  BOOLEAN mustFlush;
  ZlibDeflate_Window *_ptr__14 = NIL;
  ZlibDeflate_Window *_ptr__13 = NIL;
  head = 0;
  for (;;) {
    if ((*stream).lookAhead < 262) {
      ZlibDeflate_FillWindow(stream, stream__typ);
      if ((*stream).lookAhead < 262 && flush == 0) {
        return 1;
      } else if ((*stream).lookAhead == 0) {
        break;
      }
    }
    if ((*stream).lookAhead >= 3) {
      ZlibDeflate_InsertString(stream, stream__typ, (*stream).string, &head);
    }
    if (head != 0 && (*stream).string - head <= 32506) {
      if ((*stream).strategy != 2) {
        (*stream).matchLen = ZlibDeflate_LongestMatch(stream, stream__typ, head);
      }
    }
    if ((*stream).matchLen >= 3) {
      ZlibDeflate_CheckMatch(stream, stream__typ, (*stream).string, (*stream).match, (*stream).matchLen);
      mustFlush = ZlibDeflate_TallyDistLen(stream, stream__typ, (SHORTINT)((*stream).string - (*stream).match), (SHORTINT)((*stream).matchLen - 3));
      (*stream).lookAhead -= (*stream).matchLen;
      if ((*stream).matchLen <= (INTEGER)ZlibDeflate_ConfigTable[__X((*stream).level, 10, (CHAR*)"ZlibDeflate", 280831)].MaxLazy && (*stream).lookAhead >= 3) {
        (*stream).matchLen -= 1;
        do {
          (*stream).string += 1;
          ZlibDeflate_InsertString(stream, stream__typ, (*stream).string, &head);
          (*stream).matchLen -= 1;
        } while (!((*stream).matchLen == 0));
        (*stream).string += 1;
      } else {
        (*stream).string += (*stream).matchLen;
        (*stream).matchLen = 0;
        (*stream).hash = (SHORTINT)(*(*stream).window)[__X((*stream).string, 65536, (CHAR*)"ZlibDeflate", 279604)];
        ZlibDeflate_UpdateHash(&(*stream).hash, (*(*stream).window)[__X((*stream).string + 1, 65536, (CHAR*)"ZlibDeflate", 280575)]);
      }
    } else {
      mustFlush = ZlibDeflate_TallyLit(stream, stream__typ, (*(*stream).window)[__X((*stream).string, 65536, (CHAR*)"ZlibDeflate", 281150)]);
      (*stream).lookAhead -= 1;
      (*stream).string += 1;
    }
    if (mustFlush) {
      _ptr__14 = (*stream).window;
      ZlibDeflate_FlushBlock(stream, stream__typ, (void*)*_ptr__14, 65536, (*stream).block, (*stream).string - (*stream).block, 0);
      (*stream).block = (*stream).string;
      ZlibDeflate_FlushPending(&(*stream).pend, ZlibDeflate_PendingBuffer__typ, &(*stream).out, ZlibBuffers_Buffer__typ);
      if ((*stream).out.avail == 0) {
        return 1;
      }
    }
  }
  _ptr__13 = (*stream).window;
  ZlibDeflate_FlushBlock(stream, stream__typ, (void*)*_ptr__13, 65536, (*stream).block, (*stream).string - (*stream).block, flush == 4);
  (*stream).block = (*stream).string;
  ZlibDeflate_FlushPending(&(*stream).pend, ZlibDeflate_PendingBuffer__typ, &(*stream).out, ZlibBuffers_Buffer__typ);
  if ((*stream).out.avail == 0 && flush == 4) {
    return 3;
  } else if ((*stream).out.avail == 0) {
    return 1;
  } else if (flush == 4) {
    return 4;
  } else {
    return 2;
  }
  __RETCHK((CHAR*)"ZlibDeflate", 285951);
}

static BYTE ZlibDeflate_CompressSlow (ZlibDeflate_Stream *stream, void **stream__typ, BYTE flush)
{
  INTEGER head, maxIns;
  BOOLEAN mustFlush;
  ZlibDeflate_Window *_ptr__18 = NIL;
  ZlibDeflate_Window *_ptr__17 = NIL;
  ZlibDeflate_Window *_ptr__16 = NIL;
  head = 0;
  for (;;) {
    if ((*stream).lookAhead < 262) {
      ZlibDeflate_FillWindow(stream, stream__typ);
      if ((*stream).lookAhead < 262 && flush == 0) {
        return 1;
      } else if ((*stream).lookAhead == 0) {
        break;
      }
    }
    if ((*stream).lookAhead >= 3) {
      ZlibDeflate_InsertString(stream, stream__typ, (*stream).string, &head);
    }
    (*stream).prevLen = (*stream).matchLen;
    (*stream).prevMatch = (*stream).match;
    (*stream).matchLen = 2;
    if ((head != 0 && (*stream).prevLen < (INTEGER)ZlibDeflate_ConfigTable[__X((*stream).level, 10, (CHAR*)"ZlibDeflate", 296197)].MaxLazy) && (*stream).string - head <= 32506) {
      if ((*stream).strategy != 2) {
        (*stream).matchLen = ZlibDeflate_LongestMatch(stream, stream__typ, head);
      }
      if ((*stream).matchLen <= 5 && ((*stream).strategy == 1 || ((*stream).matchLen == 3 && (*stream).string - (*stream).match > 4096))) {
        (*stream).matchLen = 2;
      }
    }
    if ((*stream).prevLen >= 3 && (*stream).matchLen <= (*stream).prevLen) {
      maxIns = ((*stream).string + (*stream).lookAhead) - 3;
      ZlibDeflate_CheckMatch(stream, stream__typ, (*stream).string - 1, (*stream).prevMatch, (*stream).prevLen);
      mustFlush = ZlibDeflate_TallyDistLen(stream, stream__typ, (SHORTINT)(((*stream).string - 1) - (*stream).prevMatch), (SHORTINT)((*stream).prevLen - 3));
      (*stream).lookAhead -= (*stream).prevLen - 1;
      (*stream).prevLen -= 2;
      do {
        (*stream).string += 1;
        if ((*stream).string <= maxIns) {
          ZlibDeflate_InsertString(stream, stream__typ, (*stream).string, &head);
        }
        (*stream).prevLen -= 1;
      } while (!((*stream).prevLen == 0));
      (*stream).prevAvail = 0;
      (*stream).matchLen = 2;
      (*stream).string += 1;
      if (mustFlush) {
        _ptr__18 = (*stream).window;
        ZlibDeflate_FlushBlock(stream, stream__typ, (void*)*_ptr__18, 65536, (*stream).block, (*stream).string - (*stream).block, 0);
        (*stream).block = (*stream).string;
        ZlibDeflate_FlushPending(&(*stream).pend, ZlibDeflate_PendingBuffer__typ, &(*stream).out, ZlibBuffers_Buffer__typ);
        if ((*stream).out.avail == 0) {
          return 1;
        }
      }
    } else if ((*stream).prevAvail) {
      mustFlush = ZlibDeflate_TallyLit(stream, stream__typ, (*(*stream).window)[__X((*stream).string - 1, 65536, (CHAR*)"ZlibDeflate", 304450)]);
      if (mustFlush) {
        _ptr__17 = (*stream).window;
        ZlibDeflate_FlushBlock(stream, stream__typ, (void*)*_ptr__17, 65536, (*stream).block, (*stream).string - (*stream).block, 0);
        (*stream).block = (*stream).string;
        ZlibDeflate_FlushPending(&(*stream).pend, ZlibDeflate_PendingBuffer__typ, &(*stream).out, ZlibBuffers_Buffer__typ);
      }
      (*stream).string += 1;
      (*stream).lookAhead -= 1;
      if ((*stream).out.avail == 0) {
        return 1;
      }
    } else {
      (*stream).prevAvail = 1;
      (*stream).string += 1;
      (*stream).lookAhead -= 1;
    }
  }
  __ASSERT(flush != 0, 110, (CHAR*)"ZlibDeflate", 308765);
  if ((*stream).prevAvail) {
    mustFlush = ZlibDeflate_TallyLit(stream, stream__typ, (*(*stream).window)[__X((*stream).string - 1, 65536, (CHAR*)"ZlibDeflate", 309313)]);
    (*stream).prevAvail = 0;
  }
  _ptr__16 = (*stream).window;
  ZlibDeflate_FlushBlock(stream, stream__typ, (void*)*_ptr__16, 65536, (*stream).block, (*stream).string - (*stream).block, flush == 4);
  (*stream).block = (*stream).string;
  ZlibDeflate_FlushPending(&(*stream).pend, ZlibDeflate_PendingBuffer__typ, &(*stream).out, ZlibBuffers_Buffer__typ);
  if ((*stream).out.avail == 0 && flush == 4) {
    return 3;
  } else if ((*stream).out.avail == 0) {
    return 1;
  } else if (flush == 4) {
    return 4;
  } else {
    return 2;
  }
  __RETCHK((CHAR*)"ZlibDeflate", 311807);
}

void ZlibDeflate_Reset (ZlibDeflate_Stream *stream, void **stream__typ)
{
  if (!(*stream).open) {
    (*stream).res = -2;
  } else {
    ZlibBuffers_Reset(&(*stream).in, ZlibBuffers_Buffer__typ);
    ZlibBuffers_Reset(&(*stream).out, ZlibBuffers_Buffer__typ);
    (*stream).dataType = 2;
    (*stream).pend.beg = 0;
    (*stream).pend.end = 0;
    (*stream).trailerDone = 0;
    if ((*stream).wrapper) {
      (*stream).status = 1;
    } else {
      (*stream).status = 2;
    }
    (*stream).adler = 1;
    (*stream).lastFlush = 0;
    ZlibDeflate_InitTrees(stream, stream__typ);
    ZlibDeflate_InitMatches(stream, stream__typ);
    (*stream).res = 0;
  }
}

/*----------------------------------------------------------------------------*/
void ZlibDeflate_Close (ZlibDeflate_Stream *stream, void **stream__typ)
{
  if ((*stream).open) {
    (*stream).window = NIL;
    (*stream).prev = NIL;
    (*stream).head = NIL;
    (*stream).pend.buf = NIL;
    (*stream).lbuf = NIL;
    (*stream).dbuf = NIL;
    ZlibDeflate_FreeTrees(stream, stream__typ);
    (*stream).open = 0;
    (*stream).res = 0;
  } else {
    (*stream).res = -2;
  }
}

/*----------------------------------------------------------------------------*/
void ZlibDeflate_Open (ZlibDeflate_Stream *stream, void **stream__typ, BYTE level, BYTE strategy, BOOLEAN wrapper)
{
  if (level == -1) {
    level = 6;
  }
  if (((0 <= level && level <= 9) && 0 <= strategy) && strategy <= 2) {
    (*stream).window = __NEWARR(NIL, 1, 1, 1, 0, (SYSTEM_ARRLEN)65536);
    (*stream).prev = __NEWARR(NIL, 4, 4, 1, 0, (SYSTEM_ARRLEN)32768);
    (*stream).head = __NEWARR(NIL, 4, 4, 1, 0, (SYSTEM_ARRLEN)32768);
    (*stream).pend.buf = __NEWARR(NIL, 1, 1, 1, 0, (SYSTEM_ARRLEN)65536);
    (*stream).lbuf = __NEWARR(NIL, 1, 1, 1, 0, (SYSTEM_ARRLEN)16384);
    (*stream).dbuf = __NEWARR(NIL, 2, 2, 1, 0, (SYSTEM_ARRLEN)16384);
    if ((((((*stream).window != NIL && (*stream).prev != NIL) && (*stream).head != NIL) && (*stream).pend.buf != NIL) && (*stream).lbuf != NIL) && (*stream).dbuf != NIL) {
      (*stream).level = level;
      (*stream).strategy = strategy;
      (*stream).wrapper = wrapper;
      (*stream).open = 1;
      ZlibDeflate_Reset(stream, stream__typ);
    } else {
      (*stream).open = 0;
      ZlibDeflate_Close(stream, stream__typ);
      (*stream).res = -4;
    }
  } else {
    (*stream).open = 0;
    (*stream).res = -2;
  }
}

/*----------------------------------------------------------------------------*/
void ZlibDeflate_SetDictionary (ZlibDeflate_Stream *stream, void **stream__typ, CHAR *dict, INTEGER dict__len, INTEGER len)
{
  INTEGER offset, i, head, _for__66;
  if (!(*stream).open || (*stream).status != 1) {
    (*stream).res = -2;
    return;
  }
  (*stream).adler = Zlib_Adler32((*stream).adler, (void*)dict, dict__len, 0, len);
  if (len >= 3) {
    if (len > 32506) {
      offset = len - 32506;
      len = 32506;
    } else {
      offset = 0;
    }
    __MOVE((SYSTEM_ADRINT)&dict[__X(offset, dict__len, (CHAR*)"ZlibDeflate", 333130)], (SYSTEM_ADRINT)&(*(*stream).window)[0], len);
    (*stream).string = len;
    (*stream).block = len;
    (*stream).hash = (SHORTINT)(*(*stream).window)[0];
    ZlibDeflate_UpdateHash(&(*stream).hash, (*(*stream).window)[1]);
    _for__66 = len - 3;
    i = 0;
    while (i <= _for__66) {
      ZlibDeflate_InsertString(stream, stream__typ, i, &head);
      i += 1;
    }
  }
  (*stream).res = 0;
}

/*----------------------------------------------------------------------------*/
void ZlibDeflate_Deflate (ZlibDeflate_Stream *stream, void **stream__typ, BYTE flush)
{
  BYTE lastFlush, bstate;
  INTEGER header;
  CHAR buf[1];
  if (((!(*stream).open || flush < 0) || flush > 4) || ((*stream).status == 3 && flush != 4)) {
    (*stream).res = -2;
    return;
  }
  if ((*stream).out.avail == 0) {
    (*stream).res = -5;
    return;
  }
  lastFlush = (*stream).lastFlush;
  (*stream).lastFlush = flush;
  if ((*stream).status == 1) {
    header = 30720;
    if ((*stream).level >= 7) {
      header += 192;
    } else if ((*stream).level >= 5) {
      header += 128;
    } else if ((*stream).level >= 3) {
      header += 64;
    }
    if ((*stream).string != 0) {
      header += 32;
    }
    header += 31 - __MOD(header, 31);
    (*stream).status = 2;
    ZlibDeflate_Put16BitsMSB(&(*stream).pend, ZlibDeflate_PendingBuffer__typ, header);
    if ((*stream).string != 0) {
      ZlibDeflate_Put32BitsMSB(&(*stream).pend, ZlibDeflate_PendingBuffer__typ, (*stream).adler);
    }
    (*stream).adler = 1;
  }
  if ((*stream).pend.end != 0) {
    ZlibDeflate_FlushPending(&(*stream).pend, ZlibDeflate_PendingBuffer__typ, &(*stream).out, ZlibBuffers_Buffer__typ);
    if ((*stream).out.avail == 0) {
      (*stream).lastFlush = -1;
      (*stream).res = 0;
      return;
    }
  } else if (((*stream).in.avail == 0 && flush <= lastFlush) && flush != 4) {
    (*stream).res = -5;
    return;
  }
  if ((*stream).status == 4 && (*stream).in.avail != 0) {
    (*stream).res = -5;
    return;
  }
  if (((*stream).in.avail != 0 || (*stream).lookAhead != 0) || (flush != 0 && (*stream).status != 3)) {
    bstate = (*ZlibDeflate_ConfigTable[__X((*stream).level, 10, (CHAR*)"ZlibDeflate", 353341)].Compress)(stream, stream__typ, flush);
    if (__IN(bstate, 0x18)) {
      (*stream).status = 3;
    }
    if (__IN(bstate, 0x0a)) {
      if ((*stream).out.avail == 0) {
        (*stream).lastFlush = -1;
      }
      (*stream).res = 0;
      return;
    } else if (bstate == 2) {
      if (flush == 1) {
        ZlibDeflate_AlignTrees(stream, stream__typ);
      } else {
        ZlibDeflate_StoreBlock(stream, stream__typ, (void*)buf, 1, 0, 0, 0);
        if (flush == 3) {
          ZlibDeflate_ClearHash(stream, stream__typ);
        }
      }
      ZlibDeflate_FlushPending(&(*stream).pend, ZlibDeflate_PendingBuffer__typ, &(*stream).out, ZlibBuffers_Buffer__typ);
      if ((*stream).out.avail == 0) {
        (*stream).lastFlush = -1;
        (*stream).res = 0;
        return;
      }
    }
  }
  __ASSERT((*stream).out.avail > 0, 111, (CHAR*)"ZlibDeflate", 360994);
  if (flush != 4) {
    (*stream).res = 0;
  } else if (!(*stream).wrapper || (*stream).trailerDone) {
    (*stream).res = 1;
  } else {
    ZlibDeflate_Put32BitsMSB(&(*stream).pend, ZlibDeflate_PendingBuffer__typ, (*stream).adler);
    ZlibDeflate_FlushPending(&(*stream).pend, ZlibDeflate_PendingBuffer__typ, &(*stream).out, ZlibBuffers_Buffer__typ);
    (*stream).trailerDone = 1;
    if ((*stream).pend.end == 0) {
      (*stream).res = 1;
    } else {
      (*stream).res = 0;
    }
  }
}

/*----------------------------------------------------------------------------*/
void ZlibDeflate_SetParams (ZlibDeflate_Stream *stream, void **stream__typ, BYTE level, BYTE strategy)
{
  if (level == -1) {
    level = 6;
  }
  if ((((!(*stream).open || level < 0) || 9 < level) || strategy < 0) || 2 < strategy) {
    (*stream).res = -2;
  } else {
    if (ZlibDeflate_ConfigTable[__X(level, 10, (CHAR*)"ZlibDeflate", 368901)].Compress != ZlibDeflate_ConfigTable[__X((*stream).level, 10, (CHAR*)"ZlibDeflate", 368901)].Compress && (*stream).in.totalIn != 0) {
      ZlibDeflate_Deflate(stream, stream__typ, 1);
    }
    (*stream).level = level;
    (*stream).strategy = strategy;
  }
}

/*----------------------------------------------------------------------------*/
void ZlibDeflate_Compress (CHAR *src, INTEGER src__len, CHAR *dst, INTEGER dst__len, INTEGER srcoffset, INTEGER srclen, INTEGER dstoffset, INTEGER dstlen, BYTE level, BYTE strategy, INTEGER *len, INTEGER *res)
{
  ZlibDeflate_Stream s = {0};
  ZlibBuffers_Init(&s.in, ZlibBuffers_Buffer__typ, (void*)src, src__len, srcoffset, srclen, srclen);
  ZlibBuffers_Init(&s.out, ZlibBuffers_Buffer__typ, (void*)dst, dst__len, dstoffset, dstlen, dstlen);
  ZlibDeflate_Open(&s, ZlibDeflate_Stream__typ, level, strategy, 1);
  if (s.res == 0) {
    ZlibDeflate_Deflate(&s, ZlibDeflate_Stream__typ, 4);
    if (s.res == 1) {
      *len = s.out.totalOut;
      ZlibDeflate_Close(&s, ZlibDeflate_Stream__typ);
      *res = s.res;
    } else {
      *res = s.res;
      if (*res == 0) {
        *res = -5;
      }
      ZlibDeflate_Close(&s, ZlibDeflate_Stream__typ);
    }
  } else {
    *res = s.res;
  }
}

/*----------------------------------------------------------------------------*/
static void EnumPtrs(void (*P)(void*))
{
  P(ZlibDeflate_ExtraLenBits);
  P(ZlibDeflate_ExtraDistBits);
  P(ZlibDeflate_ExtraBitBits);
  __ENUMR(&ZlibDeflate_LTree, ZlibDeflate_StaticTree__typ, 16, 1, P);
  __ENUMR(&ZlibDeflate_DTree, ZlibDeflate_StaticTree__typ, 16, 1, P);
  __ENUMR(&ZlibDeflate_BTree, ZlibDeflate_StaticTree__typ, 16, 1, P);
}

__TDESC(ZlibDeflate_Node__desc, 2, 0) = {__TDFLDS("Node", 4), {-4}};
__TDESC(ZlibDeflate_StaticTree__desc, 1, 2) = {__TDFLDS("StaticTree", 16), {0, 4, -12}};
__TDESC(ZlibDeflate_Tree__desc, 2, 3) = {__TDFLDS("Tree", 24), {0, 8, 12, -16}};
__TDESC(ZlibDeflate_PendingBuffer__desc, 2, 1) = {__TDFLDS("PendingBuffer", 12), {0, -8}};
__TDESC(ZlibDeflate_Stream__desc, 2, 18) = {__TDFLDS("Stream", 2564), {64, 76, 80, 112, 124, 132, 136, 148, 156, 160, 172, 180, 184, 196, 200, 204, 
  2536, 2540, -76}};
__TDESC(ZlibDeflate__1__desc, 2, 0) = {__TDFLDS("", 12), {-4}};

export void *ZlibDeflate__init (void)
{
  __DEFMOD;
  __IMPORT(Zlib__init);
  __IMPORT(ZlibBuffers__init);
  __REGMOD("ZlibDeflate", EnumPtrs);
  __INITYP(ZlibDeflate_Node, ZlibDeflate_Node, 0);
  __INITYP(ZlibDeflate_StaticTree, ZlibDeflate_StaticTree, 0);
  __INITYP(ZlibDeflate_Tree, ZlibDeflate_Tree, 0);
  __INITYP(ZlibDeflate_PendingBuffer, ZlibDeflate_PendingBuffer, 0);
  __INITYP(ZlibDeflate_Stream, ZlibDeflate_Stream, 0);
  __INITYP(ZlibDeflate__1, ZlibDeflate__1, 0);
/* BEGIN */
  ZlibDeflate_InitStaticTrees();
  ZlibDeflate_ConfigTable[0].GoodLen = 0;
  ZlibDeflate_ConfigTable[0].MaxLazy = 0;
  ZlibDeflate_ConfigTable[0].NiceLen = 0;
  ZlibDeflate_ConfigTable[0].MaxChain = 0;
  ZlibDeflate_ConfigTable[0].Compress = ZlibDeflate_CompressStored;
  ZlibDeflate_ConfigTable[1].GoodLen = 4;
  ZlibDeflate_ConfigTable[1].MaxLazy = 4;
  ZlibDeflate_ConfigTable[1].NiceLen = 8;
  ZlibDeflate_ConfigTable[1].MaxChain = 4;
  ZlibDeflate_ConfigTable[1].Compress = ZlibDeflate_CompressFast;
  ZlibDeflate_ConfigTable[2].GoodLen = 4;
  ZlibDeflate_ConfigTable[2].MaxLazy = 5;
  ZlibDeflate_ConfigTable[2].NiceLen = 16;
  ZlibDeflate_ConfigTable[2].MaxChain = 8;
  ZlibDeflate_ConfigTable[2].Compress = ZlibDeflate_CompressFast;
  ZlibDeflate_ConfigTable[3].GoodLen = 4;
  ZlibDeflate_ConfigTable[3].MaxLazy = 6;
  ZlibDeflate_ConfigTable[3].NiceLen = 32;
  ZlibDeflate_ConfigTable[3].MaxChain = 32;
  ZlibDeflate_ConfigTable[3].Compress = ZlibDeflate_CompressFast;
  ZlibDeflate_ConfigTable[4].GoodLen = 4;
  ZlibDeflate_ConfigTable[4].MaxLazy = 4;
  ZlibDeflate_ConfigTable[4].NiceLen = 16;
  ZlibDeflate_ConfigTable[4].MaxChain = 16;
  ZlibDeflate_ConfigTable[4].Compress = ZlibDeflate_CompressSlow;
  ZlibDeflate_ConfigTable[5].GoodLen = 8;
  ZlibDeflate_ConfigTable[5].MaxLazy = 16;
  ZlibDeflate_ConfigTable[5].NiceLen = 32;
  ZlibDeflate_ConfigTable[5].MaxChain = 32;
  ZlibDeflate_ConfigTable[5].Compress = ZlibDeflate_CompressSlow;
  ZlibDeflate_ConfigTable[6].GoodLen = 8;
  ZlibDeflate_ConfigTable[6].MaxLazy = 16;
  ZlibDeflate_ConfigTable[6].NiceLen = 128;
  ZlibDeflate_ConfigTable[6].MaxChain = 128;
  ZlibDeflate_ConfigTable[6].Compress = ZlibDeflate_CompressSlow;
  ZlibDeflate_ConfigTable[7].GoodLen = 8;
  ZlibDeflate_ConfigTable[7].MaxLazy = 32;
  ZlibDeflate_ConfigTable[7].NiceLen = 128;
  ZlibDeflate_ConfigTable[7].MaxChain = 256;
  ZlibDeflate_ConfigTable[7].Compress = ZlibDeflate_CompressSlow;
  ZlibDeflate_ConfigTable[8].GoodLen = 32;
  ZlibDeflate_ConfigTable[8].MaxLazy = 128;
  ZlibDeflate_ConfigTable[8].NiceLen = 258;
  ZlibDeflate_ConfigTable[8].MaxChain = 1024;
  ZlibDeflate_ConfigTable[8].Compress = ZlibDeflate_CompressSlow;
  ZlibDeflate_ConfigTable[9].GoodLen = 32;
  ZlibDeflate_ConfigTable[9].MaxLazy = 128;
  ZlibDeflate_ConfigTable[9].NiceLen = 258;
  ZlibDeflate_ConfigTable[9].MaxChain = 4096;
  ZlibDeflate_ConfigTable[9].Compress = ZlibDeflate_CompressSlow;
  __ENDMOD;
}
