/* Ofront+ 1.0 -s2 -48 */
#include "SYSTEM.oh"
#include "Zlib.oh"
#include "ZlibBuffers.oh"

struct ZlibInflate__1 {
  INTEGER calc, stored;
};

struct ZlibInflate__2 {
  SHORTINT state, method, marker;
  struct ZlibInflate__1 check;
};

typedef
  struct ZlibInflate_Node_ARRAY *ZlibInflate_Nodes;

typedef
  struct ZlibInflate_Tree {
    ZlibInflate_Nodes node;
    INTEGER base;
    SHORTINT bits;
  } ZlibInflate_Tree;

struct ZlibInflate__3 {
  BYTE state;
  BOOLEAN last;
  INTEGER left;
  SHORTINT nlit;
  BYTE ndist, nclen;
  BYTE clen[319];
  SHORTINT index;
  ZlibInflate_Nodes nodes;
  ZlibInflate_Tree btree;
};

struct ZlibInflate__4 {
  BYTE state;
  ZlibInflate_Tree lltree, dtree, tree;
  SHORTINT lit, extra, len, dist;
};

typedef
  INTEGER (*ZlibInflate_CheckFunc)(INTEGER, CHAR*, INTEGER , INTEGER, INTEGER);

typedef
  struct ZlibInflate_Code {
    SHORTINT bits, offset, size, simple;
    BYTE extra[31];
    SHORTINT base[31];
  } ZlibInflate_Code;

typedef
  struct ZlibInflate_Node {
    SHORTINT base;
    BYTE exop, bits;
  } ZlibInflate_Node;

typedef
  struct ZlibInflate_Result {
    INTEGER code;
    struct CHAR8_ARRAY *msg;
  } ZlibInflate_Result;

typedef
  CHAR ZlibInflate_Window[32768];

typedef
  struct ZlibInflate_Stream {
    ZlibBuffers_Buffer in, out;
    ZlibInflate_Result res;
    BOOLEAN wrapper, open;
    ZlibInflate_Window *window;
    INTEGER read, write;
    ZlibInflate_CheckFunc checkFn;
    INTEGER check, buf, bits;
    struct ZlibInflate__2 inf;
    struct ZlibInflate__3 block;
    struct ZlibInflate__4 decode;
  } ZlibInflate_Stream;

typedef
  struct ZlibInflate_TreeNodes {
    ZlibInflate_Nodes node;
    INTEGER next;
  } ZlibInflate_TreeNodes;


#ifndef ZlibInflate_Node_ARRAY_DEF
#define ZlibInflate_Node_ARRAY_DEF
typedef struct ZlibInflate_Node_ARRAY {
  INTEGER len[1];
  ZlibInflate_Node data[1];
} ZlibInflate_Node_ARRAY;
#endif 

#ifndef CHAR8_ARRAY_DEF
#define CHAR8_ARRAY_DEF
typedef struct CHAR8_ARRAY {
  INTEGER len[1];
  CHAR data[1];
} CHAR8_ARRAY;
#endif 

static BOOLEAN ZlibInflate_FixedBuilt;
static ZlibInflate_Tree ZlibInflate_FixedLitLenTree, ZlibInflate_FixedDistTree;
static BYTE ZlibInflate_Order[19];

export void **ZlibInflate_Result__typ;
export void **ZlibInflate_Code__typ;
export void **ZlibInflate_Node__typ;
export void **ZlibInflate_TreeNodes__typ;
export void **ZlibInflate_Tree__typ;
export void **ZlibInflate__1__typ;
export void **ZlibInflate__2__typ;
export void **ZlibInflate__3__typ;
export void **ZlibInflate__4__typ;
export void **ZlibInflate_Stream__typ;

static BOOLEAN ZlibInflate_BlockSyncPoint (ZlibInflate_Stream *s, void **s__typ);
static void ZlibInflate_BuildTree (BYTE *clen, INTEGER clen__len, ZlibInflate_Code *code, void **code__typ, ZlibInflate_TreeNodes *tn, void **tn__typ, ZlibInflate_Tree *tree, void **tree__typ, INTEGER *res);
export void ZlibInflate_Close (ZlibInflate_Stream *stream, void **stream__typ);
static void ZlibInflate_Dump (ZlibInflate_Stream *s, void **s__typ, INTEGER bits);
static void ZlibInflate_Flush (ZlibInflate_Stream *s, void **s__typ);
static void ZlibInflate_FreeBlocks (ZlibInflate_Stream *s, void **s__typ);
static void ZlibInflate_FreeCodes (ZlibInflate_Stream *s, void **s__typ);
export void ZlibInflate_Inflate (ZlibInflate_Stream *stream, void **stream__typ, BYTE flush);
static void ZlibInflate_InflateBlocks (ZlibInflate_Stream *s, void **s__typ);
static void ZlibInflate_InflateCodes (ZlibInflate_Stream *s, void **s__typ);
static void ZlibInflate_InflateFast (ZlibInflate_Stream *s, void **s__typ, INTEGER *wavail);
static void ZlibInflate_MakeDistCode (ZlibInflate_Code *code, void **code__typ, SHORTINT bits, SHORTINT offset, SHORTINT size, SHORTINT simple);
static void ZlibInflate_MakeFixedDistCode (BYTE *len, INTEGER len__len, ZlibInflate_Code *code, void **code__typ);
static void ZlibInflate_MakeFixedLitLenCode (BYTE *len, INTEGER len__len, ZlibInflate_Code *code, void **code__typ);
static void ZlibInflate_MakeLitLenCode (ZlibInflate_Code *code, void **code__typ, SHORTINT bits, SHORTINT offset, SHORTINT size, SHORTINT simple);
static BOOLEAN ZlibInflate_Need (ZlibInflate_Stream *s, void **s__typ, INTEGER bits);
static BOOLEAN ZlibInflate_NeedOut (ZlibInflate_Stream *s, void **s__typ, INTEGER *wavail);
static void ZlibInflate_NewBlocks (ZlibInflate_Stream *s, void **s__typ, ZlibInflate_CheckFunc checkFn);
static void ZlibInflate_NewCodes (ZlibInflate_Stream *s, void **s__typ, ZlibInflate_Tree *lltree, void **lltree__typ, ZlibInflate_Tree *dtree, void **dtree__typ);
export void ZlibInflate_Open (ZlibInflate_Stream *stream, void **stream__typ, BOOLEAN wrapper);
export void ZlibInflate_Reset (ZlibInflate_Stream *stream, void **stream__typ);
static void ZlibInflate_Reset0 (ZlibInflate_Stream *stream, void **stream__typ);
static void ZlibInflate_ResetBlocks (ZlibInflate_Stream *s, void **s__typ, INTEGER *check);
static void ZlibInflate_SetBlockDict (ZlibInflate_Stream *s, void **s__typ, CHAR *dict, INTEGER dict__len, INTEGER offset, INTEGER len);
export void ZlibInflate_SetDictionary (ZlibInflate_Stream *stream, void **stream__typ, CHAR *dict, INTEGER dict__len, INTEGER dictLen);
static void ZlibInflate_SetMsg (ZlibInflate_Result *res, void **res__typ, CHAR *msg, INTEGER msg__len);
export void ZlibInflate_Sync (ZlibInflate_Stream *stream, void **stream__typ);
export BOOLEAN ZlibInflate_SyncPoint (ZlibInflate_Stream *stream, void **stream__typ);
export void ZlibInflate_Uncompress (CHAR *src, INTEGER src__len, CHAR *dst, INTEGER dst__len, INTEGER srcoffset, INTEGER srclen, INTEGER dstoffset, INTEGER dstlen, INTEGER *len, ZlibInflate_Result *res, void **res__typ);


/*============================================================================*/

static void ZlibInflate_SetMsg (ZlibInflate_Result *res, void **res__typ, CHAR *msg, INTEGER msg__len)
{
  INTEGER l;
  __DUP(msg, msg__len);
  l = 0;
  while (msg[__X(l, msg__len, (CHAR*)"ZlibInflate", 43035)] != 0x00) {
    l += 1;
  }
  (*res).msg = __NEWARR(NIL, 1, 1, 1, 1, (SYSTEM_ARRLEN)(l + 1));
  __COPY(msg, (*res).msg->data, __MIN((*res).msg->len[0], msg__len));
}

static void ZlibInflate_MakeLitLenCode (ZlibInflate_Code *code, void **code__typ, SHORTINT bits, SHORTINT offset, SHORTINT size, SHORTINT simple)
{
  (*code).bits = bits;
  (*code).offset = offset;
  (*code).size = size;
  (*code).simple = simple;
  if (simple < size) {
    (*code).extra[0] = 0;
    (*code).extra[1] = 0;
    (*code).extra[2] = 0;
    (*code).extra[3] = 0;
    (*code).extra[4] = 0;
    (*code).extra[5] = 0;
    (*code).extra[6] = 0;
    (*code).extra[7] = 0;
    (*code).extra[8] = 1;
    (*code).extra[9] = 1;
    (*code).extra[10] = 1;
    (*code).extra[11] = 1;
    (*code).extra[12] = 2;
    (*code).extra[13] = 2;
    (*code).extra[14] = 2;
    (*code).extra[15] = 2;
    (*code).extra[16] = 3;
    (*code).extra[17] = 3;
    (*code).extra[18] = 3;
    (*code).extra[19] = 3;
    (*code).extra[20] = 4;
    (*code).extra[21] = 4;
    (*code).extra[22] = 4;
    (*code).extra[23] = 4;
    (*code).extra[24] = 5;
    (*code).extra[25] = 5;
    (*code).extra[26] = 5;
    (*code).extra[27] = 5;
    (*code).extra[28] = 0;
    (*code).extra[29] = 112;
    (*code).extra[30] = 112;
    (*code).base[0] = 3;
    (*code).base[1] = 4;
    (*code).base[2] = 5;
    (*code).base[3] = 6;
    (*code).base[4] = 7;
    (*code).base[5] = 8;
    (*code).base[6] = 9;
    (*code).base[7] = 10;
    (*code).base[8] = 11;
    (*code).base[9] = 13;
    (*code).base[10] = 15;
    (*code).base[11] = 17;
    (*code).base[12] = 19;
    (*code).base[13] = 23;
    (*code).base[14] = 27;
    (*code).base[15] = 31;
    (*code).base[16] = 35;
    (*code).base[17] = 43;
    (*code).base[18] = 51;
    (*code).base[19] = 59;
    (*code).base[20] = 67;
    (*code).base[21] = 83;
    (*code).base[22] = 99;
    (*code).base[23] = 115;
    (*code).base[24] = 131;
    (*code).base[25] = 163;
    (*code).base[26] = 195;
    (*code).base[27] = 227;
    (*code).base[28] = 258;
    (*code).base[29] = 0;
    (*code).base[30] = 0;
  }
}

static void ZlibInflate_MakeDistCode (ZlibInflate_Code *code, void **code__typ, SHORTINT bits, SHORTINT offset, SHORTINT size, SHORTINT simple)
{
  (*code).bits = bits;
  (*code).offset = offset;
  (*code).size = size;
  (*code).simple = simple;
  if (simple < size) {
    (*code).extra[0] = 0;
    (*code).extra[1] = 0;
    (*code).extra[2] = 0;
    (*code).extra[3] = 0;
    (*code).extra[4] = 1;
    (*code).extra[5] = 1;
    (*code).extra[6] = 2;
    (*code).extra[7] = 2;
    (*code).extra[8] = 3;
    (*code).extra[9] = 3;
    (*code).extra[10] = 4;
    (*code).extra[11] = 4;
    (*code).extra[12] = 5;
    (*code).extra[13] = 5;
    (*code).extra[14] = 6;
    (*code).extra[15] = 6;
    (*code).extra[16] = 7;
    (*code).extra[17] = 7;
    (*code).extra[18] = 8;
    (*code).extra[19] = 8;
    (*code).extra[20] = 9;
    (*code).extra[21] = 9;
    (*code).extra[22] = 10;
    (*code).extra[23] = 10;
    (*code).extra[24] = 11;
    (*code).extra[25] = 11;
    (*code).extra[26] = 12;
    (*code).extra[27] = 12;
    (*code).extra[28] = 13;
    (*code).extra[29] = 13;
    (*code).base[0] = 1;
    (*code).base[1] = 2;
    (*code).base[2] = 3;
    (*code).base[3] = 4;
    (*code).base[4] = 5;
    (*code).base[5] = 7;
    (*code).base[6] = 9;
    (*code).base[7] = 13;
    (*code).base[8] = 17;
    (*code).base[9] = 25;
    (*code).base[10] = 33;
    (*code).base[11] = 49;
    (*code).base[12] = 65;
    (*code).base[13] = 97;
    (*code).base[14] = 129;
    (*code).base[15] = 193;
    (*code).base[16] = 257;
    (*code).base[17] = 385;
    (*code).base[18] = 513;
    (*code).base[19] = 769;
    (*code).base[20] = 1025;
    (*code).base[21] = 1537;
    (*code).base[22] = 2049;
    (*code).base[23] = 3073;
    (*code).base[24] = 4097;
    (*code).base[25] = 6145;
    (*code).base[26] = 8193;
    (*code).base[27] = 12289;
    (*code).base[28] = 16385;
    (*code).base[29] = 24577;
  }
}

static void ZlibInflate_MakeFixedLitLenCode (BYTE *len, INTEGER len__len, ZlibInflate_Code *code, void **code__typ)
{
  INTEGER i;
  __ASSERT(len__len >= 288, 100, (CHAR*)"ZlibInflate", 57374);
  i = 0;
  while (i <= 143) {
    len[__X(i, len__len, (CHAR*)"ZlibInflate", 57634)] = 8;
    i += 1;
  }
  i = 144;
  while (i <= 255) {
    len[__X(i, len__len, (CHAR*)"ZlibInflate", 57892)] = 9;
    i += 1;
  }
  i = 256;
  while (i <= 279) {
    len[__X(i, len__len, (CHAR*)"ZlibInflate", 58148)] = 7;
    i += 1;
  }
  i = 280;
  while (i <= 287) {
    len[__X(i, len__len, (CHAR*)"ZlibInflate", 58404)] = 8;
    i += 1;
  }
  ZlibInflate_MakeLitLenCode(code, code__typ, 9, 0, 288, 257);
}

static void ZlibInflate_MakeFixedDistCode (BYTE *len, INTEGER len__len, ZlibInflate_Code *code, void **code__typ)
{
  INTEGER i;
  __ASSERT(len__len >= 30, 100, (CHAR*)"ZlibInflate", 60189);
  i = 0;
  while (i <= 29) {
    len[__X(i, len__len, (CHAR*)"ZlibInflate", 60449)] = 5;
    i += 1;
  }
  ZlibInflate_MakeDistCode(code, code__typ, 5, 0, 30, 0);
}

static void ZlibInflate_BuildTree (BYTE *clen, INTEGER clen__len, ZlibInflate_Code *code, void **code__typ, ZlibInflate_TreeNodes *tn, void **tn__typ, ZlibInflate_Tree *tree, void **tree__typ, INTEGER *res)
{
  INTEGER l, lbits, min, max, dbits, len, bits, b, c, idx;
  SHORTINT codes[16];
  INTEGER unused, size, count, entries;
  SHORTINT offset[16];
  SHORTINT off;
  SHORTINT index[288];
  INTEGER backup[15];
  INTEGER pat, p, inc, tab, t, level;
  INTEGER table[15];
  ZlibInflate_Node node;
  INTEGER _for__5, _for__4, _for__3;
  l = 0;
  while (l <= 15) {
    codes[__X(l, 16, (CHAR*)"ZlibInflate", 67071)] = 0;
    l += 1;
  }
  _for__5 = (*code).size - 1;
  c = 0;
  while (c <= _for__5) {
    codes[__X(clen[__X((INTEGER)(*code).offset + c, clen__len, (CHAR*)"ZlibInflate", 67839)], 16, (CHAR*)"ZlibInflate", 67839)] += 1;
    c += 1;
  }
  if (codes[0] == (*code).size) {
    (*tree).node = NIL;
    (*tree).base = 0;
    (*tree).bits = 0;
    *res = 0;
    return;
  }
  lbits = (*code).bits;
  l = 1;
  while (l <= 15 && codes[__X(l, 16, (CHAR*)"ZlibInflate", 69678)] == 0) {
    l += 1;
  }
  min = l;
  if (lbits < min) {
    lbits = (SHORTINT)min;
  }
  l = 15;
  while (l > 0 && codes[__X(l, 16, (CHAR*)"ZlibInflate", 70189)] == 0) {
    l -= 1;
  }
  max = l;
  if (lbits > max) {
    lbits = (SHORTINT)max;
  }
  (*tree).bits = (SHORTINT)lbits;
  l = min;
  unused = __ASH(1, min, INTEGER);
  for (;;) {
    unused -= (INTEGER)codes[__X(l, 16, (CHAR*)"ZlibInflate", 71966)];
    if (unused < 0) {
      *res = -3;
      return;
    }
    if (l == max) {
      break;
    }
    l += 1;
    unused = __ASHL(unused, 1, INTEGER);
  }
  codes[__X(max, 16, (CHAR*)"ZlibInflate", 73248)] += (SHORTINT)unused;
  l = 1;
  offset[1] = 0;
  off = 0;
  while (l < max) {
    off += codes[__X(l, 16, (CHAR*)"ZlibInflate", 74517)];
    l += 1;
    offset[__X(l, 16, (CHAR*)"ZlibInflate", 74751)] = off;
  }
  _for__4 = (*code).size - 1;
  c = 0;
  while (c <= _for__4) {
    l = clen[__X((INTEGER)(*code).offset + c, clen__len, (CHAR*)"ZlibInflate", 75805)];
    if (l != 0) {
      index[__X(offset[__X(l, 16, (CHAR*)"ZlibInflate", 76320)], 288, (CHAR*)"ZlibInflate", 76320)] = (SHORTINT)c;
      offset[__X(l, 16, (CHAR*)"ZlibInflate", 76543)] += 1;
    }
    c += 1;
  }
  size = offset[__X(max, 16, (CHAR*)"ZlibInflate", 77077)];
  backup[0] = 0;
  pat = 0;
  idx = 0;
  dbits = -lbits;
  level = -1;
  _for__3 = max;
  len = min;
  while (len <= _for__3) {
    count = codes[__X(len, 16, (CHAR*)"ZlibInflate", 78614)];
    while (count > 0) {
      while (len > dbits + lbits) {
        level += 1;
        dbits += lbits;
        bits = max - dbits;
        if (bits > lbits) {
          bits = lbits;
        }
        b = len - dbits;
        entries = __ASH(1, b, INTEGER);
        if (entries > count) {
          entries -= count;
          if (b < bits) {
            l = len;
            for (;;) {
              b += 1;
              if (b == bits) {
                break;
              }
              entries = __ASHL(entries, 1, INTEGER);
              l += 1;
              if (entries <= (INTEGER)codes[__X(l, 16, (CHAR*)"ZlibInflate", 83756)]) {
                break;
              }
              entries -= (INTEGER)codes[__X(l, 16, (CHAR*)"ZlibInflate", 84223)];
            }
          }
        }
        entries = __ASH(1, b, INTEGER);
        if ((*tn).next + entries > (*tn).node->len[0]) {
          *res = -4;
          return;
        }
        tab = (*tn).next;
        table[__X(level, 15, (CHAR*)"ZlibInflate", 86568)] = tab;
        (*tn).next += entries;
        if (level > 0) {
          backup[__X(level, 15, (CHAR*)"ZlibInflate", 87578)] = pat;
          node.bits = (BYTE)lbits;
          node.exop = -128 + (BYTE)b;
          t = __ASH(pat, -(dbits - lbits), INTEGER);
          node.base = (SHORTINT)((tab - table[__X(level - 1, 15, (CHAR*)"ZlibInflate", 88626)]) - t);
          ((*tn).node->data)[__X(table[__X(level - 1, 15, (CHAR*)"ZlibInflate", 89087)] + t, (*tn).node->len[0], (CHAR*)"ZlibInflate", 89087)] = node;
        } else {
          (*tree).node = (*tn).node;
          (*tree).base = tab;
        }
      }
      node.bits = (BYTE)(len - dbits);
      if (idx >= size) {
        node.exop = 64;
      } else if (index[__X(idx, 288, (CHAR*)"ZlibInflate", 91391)] < (*code).simple) {
        if (index[__X(idx, 288, (CHAR*)"ZlibInflate", 91751)] < 256) {
          node.exop = -128;
        } else {
          node.exop = -32;
        }
        node.base = index[__X(idx, 288, (CHAR*)"ZlibInflate", 91932)];
        idx += 1;
      } else {
        node.exop = -48 + (*code).extra[__X(index[__X(idx, 288, (CHAR*)"ZlibInflate", 92757)] - (*code).simple, 31, (CHAR*)"ZlibInflate", 92757)];
        node.base = (*code).base[__X(index[__X(idx, 288, (CHAR*)"ZlibInflate", 92981)] - (*code).simple, 31, (CHAR*)"ZlibInflate", 92981)];
        idx += 1;
      }
      p = __ASH(pat, -dbits, INTEGER);
      inc = __ASH(1, len - dbits, INTEGER);
      while (p < entries) {
        ((*tn).node->data)[__X(tab + p, (*tn).node->len[0], (CHAR*)"ZlibInflate", 94749)] = node;
        p += inc;
      }
      l = len - 1;
      while (__ODD(__ASH(pat, -l, INTEGER))) {
        pat -= __ASH(1, l, INTEGER);
        l -= 1;
      }
      pat += __ASH(1, l, INTEGER);
      while (__MODF(pat, __ASH(1, dbits, INTEGER)) != backup[__X(level, 15, (CHAR*)"ZlibInflate", 97839)]) {
        level -= 1;
        dbits -= lbits;
      }
      count -= 1;
    }
    len += 1;
  }
  if (unused != 0 && max != 1) {
    *res = -5;
  } else {
    *res = 0;
  }
}

static void ZlibInflate_Flush (ZlibInflate_Stream *s, void **s__typ)
{
  INTEGER n;
  ZlibInflate_Window *_ptr__12 = NIL;
  ZlibInflate_Window *_ptr__11 = NIL;
  ZlibInflate_Window *_ptr__10 = NIL;
  ZlibInflate_Window *_ptr__9 = NIL;
  if ((*s).read <= (*s).write) {
    n = (*s).write - (*s).read;
  } else {
    n = 32768 - (*s).read;
  }
  if (n > (*s).out.avail) {
    n = (*s).out.avail;
  }
  if (n > 0) {
    if ((*s).res.code == -5) {
      (*s).res.code = 0;
    }
    if ((*s).checkFn != NIL) {
      (*s).check = (_ptr__12 = (*s).window, 
        (*(*s).checkFn)((*s).check, (void*)*_ptr__12, 32768, (*s).read, n));
    }
    _ptr__11 = (*s).window;
    ZlibBuffers_WriteBytes(&(*s).out, ZlibBuffers_Buffer__typ, (void*)*_ptr__11, 32768, (*s).read, n);
    (*s).read += n;
  }
  if ((*s).read == 32768) {
    (*s).read = 0;
    if ((*s).write == 32768) {
      (*s).write = 0;
    }
    n = (*s).write - (*s).read;
    if (n > (*s).out.avail) {
      n = (*s).out.avail;
    }
    if (n > 0) {
      if ((*s).res.code == -5) {
        (*s).res.code = 0;
      }
      if ((*s).checkFn != NIL) {
        (*s).check = (_ptr__10 = (*s).window, 
          (*(*s).checkFn)((*s).check, (void*)*_ptr__10, 32768, (*s).read, n));
      }
      _ptr__9 = (*s).window;
      ZlibBuffers_WriteBytes(&(*s).out, ZlibBuffers_Buffer__typ, (void*)*_ptr__9, 32768, (*s).read, n);
      (*s).read += n;
    }
  }
}

static BOOLEAN ZlibInflate_Need (ZlibInflate_Stream *s, void **s__typ, INTEGER bits)
{
  CHAR byte;
  while ((*s).bits < bits) {
    if ((*s).in.avail == 0) {
      ZlibInflate_Flush(s, s__typ);
      return 0;
    }
    ZlibBuffers_Read(&(*s).in, ZlibBuffers_Buffer__typ, &byte);
    (*s).buf += __ASH((INTEGER)byte, (*s).bits, INTEGER);
    (*s).bits += 8;
  }
  return 1;
}

static void ZlibInflate_Dump (ZlibInflate_Stream *s, void **s__typ, INTEGER bits)
{
  (*s).buf = __LSH((*s).buf, -bits, INTEGER);
  (*s).bits -= bits;
}

static BOOLEAN ZlibInflate_NeedOut (ZlibInflate_Stream *s, void **s__typ, INTEGER *wavail)
{
  if (*wavail == 0) {
    if ((*s).write == 32768 && (*s).read != 0) {
      (*s).write = 0;
      *wavail = (*s).read - 1;
    }
    if (*wavail == 0) {
      ZlibInflate_Flush(s, s__typ);
      if ((*s).write == 32768 && (*s).read != 0) {
        (*s).write = 0;
        *wavail = (*s).read - 1;
      }
      if (*wavail == 0) {
        return 0;
      }
    }
  }
  return 1;
}

static void ZlibInflate_NewCodes (ZlibInflate_Stream *s, void **s__typ, ZlibInflate_Tree *lltree, void **lltree__typ, ZlibInflate_Tree *dtree, void **dtree__typ)
{
  (*s).decode.lltree = *lltree;
  (*s).decode.dtree = *dtree;
  (*s).decode.state = 0;
}

static void ZlibInflate_FreeCodes (ZlibInflate_Stream *s, void **s__typ)
{
  (*s).decode.lltree.node = NIL;
  (*s).decode.dtree.node = NIL;
  (*s).decode.tree.node = NIL;
}

static void ZlibInflate_InflateFast (ZlibInflate_Stream *s, void **s__typ, INTEGER *wavail)
{
  INTEGER inavail, base, len, dist, index;
  CHAR byte;
  ZlibInflate_Node node;
  SHORTINT exop;
  inavail = (*s).in.avail;
  do {
    while ((*s).bits < 20) {
      ZlibBuffers_Read(&(*s).in, ZlibBuffers_Buffer__typ, &byte);
      (*s).buf += __ASH((INTEGER)byte, (*s).bits, INTEGER);
      (*s).bits += 8;
    }
    base = (*s).decode.lltree.base;
    node.base = 0;
    exop = (*s).decode.lltree.bits;
    do {
      base = (base + (INTEGER)node.base) + __MODF((*s).buf, __ASH(1, exop, INTEGER));
      node = ((*s).decode.lltree.node->data)[__X(base, (*s).decode.lltree.node->len[0], (CHAR*)"ZlibInflate", 129574)];
      ZlibInflate_Dump(s, s__typ, node.bits);
      exop = (SHORTINT)node.exop - -128;
    } while (!(exop == 0 || __ODD(__ASHR(exop, 6, SHORTINT))));
    if (exop == 0) {
      (*(*s).window)[__X((*s).write, 32768, (CHAR*)"ZlibInflate", 130855)] = (CHAR)node.base;
      (*s).write += 1;
      *wavail -= 1;
    } else if (__ODD(__ASHR(exop, 4, SHORTINT))) {
      exop = __MASK(exop, -16);
      len = (INTEGER)node.base + __MODF((*s).buf, __ASH(1, exop, INTEGER));
      ZlibInflate_Dump(s, s__typ, exop);
      while ((*s).bits < 15) {
        ZlibBuffers_Read(&(*s).in, ZlibBuffers_Buffer__typ, &byte);
        (*s).buf += __ASH((INTEGER)byte, (*s).bits, INTEGER);
        (*s).bits += 8;
      }
      base = (*s).decode.dtree.base;
      node.base = 0;
      exop = (*s).decode.dtree.bits;
      do {
        base = (base + (INTEGER)node.base) + __MODF((*s).buf, __ASH(1, exop, INTEGER));
        node = ((*s).decode.dtree.node->data)[__X(base, (*s).decode.dtree.node->len[0], (CHAR*)"ZlibInflate", 133926)];
        ZlibInflate_Dump(s, s__typ, node.bits);
        exop = (SHORTINT)node.exop - -128;
      } while (!__ODD(__ASHR(exop, 6, SHORTINT)));
      if (__ODD(__ASHR(exop, 4, SHORTINT))) {
        exop = __MASK(exop, -16);
        while ((*s).bits < (INTEGER)exop) {
          ZlibBuffers_Read(&(*s).in, ZlibBuffers_Buffer__typ, &byte);
          (*s).buf += __ASH((INTEGER)byte, (*s).bits, INTEGER);
          (*s).bits += 8;
        }
        dist = (INTEGER)node.base + __MODF((*s).buf, __ASH(1, exop, INTEGER));
        ZlibInflate_Dump(s, s__typ, exop);
        *wavail -= len;
        index = (*s).write - dist;
        if (index < 0) {
          if (-index < len) {
            len += index;
            if ((*s).write - index <= 32768 + index) {
              __MOVE((SYSTEM_ADRINT)&(*(*s).window)[__X(32768 + index, 32768, (CHAR*)"ZlibInflate", 138596)], (SYSTEM_ADRINT)&(*(*s).window)[__X((*s).write, 32768, (CHAR*)"ZlibInflate", 138596)], -index);
              (*s).write -= index;
            } else {
              index = 32768 + index;
              do {
                (*(*s).window)[__X((*s).write, 32768, (CHAR*)"ZlibInflate", 139821)] = (*(*s).window)[__X(index, 32768, (CHAR*)"ZlibInflate", 139821)];
                (*s).write += 1;
                index += 1;
              } while (!(index == 32768));
            }
            index = 0;
          } else {
            index += 32768;
          }
        }
        if (len > 0) {
          if (index + len <= (*s).write) {
            __MOVE((SYSTEM_ADRINT)&(*(*s).window)[__X(index, 32768, (CHAR*)"ZlibInflate", 142419)], (SYSTEM_ADRINT)&(*(*s).window)[__X((*s).write, 32768, (CHAR*)"ZlibInflate", 142419)], len);
            (*s).write += len;
          } else {
            do {
              (*(*s).window)[__X((*s).write, 32768, (CHAR*)"ZlibInflate", 143404)] = (*(*s).window)[__X(index, 32768, (CHAR*)"ZlibInflate", 143404)];
              (*s).write += 1;
              index += 1;
              len -= 1;
            } while (!(len == 0));
          }
        }
      } else {
        ZlibInflate_SetMsg(&(*s).res, ZlibInflate_Result__typ, (CHAR*)"invalid distance code", 22);
        (*s).res.code = -3;
        len = inavail - (*s).in.avail;
        if (__ASHR((*s).bits, 3, INTEGER) < len) {
          len = __ASHR((*s).bits, 3, INTEGER);
        }
        ZlibBuffers_Reread(&(*s).in, ZlibBuffers_Buffer__typ, len);
        (*s).bits -= __ASHL(len, 3, INTEGER);
        (*s).buf = __MODF((*s).buf, __ASH(1, (*s).bits, INTEGER));
        return;
      }
    } else {
      len = inavail - (*s).in.avail;
      if (__ASHR((*s).bits, 3, INTEGER) < len) {
        len = __ASHR((*s).bits, 3, INTEGER);
      }
      ZlibBuffers_Reread(&(*s).in, ZlibBuffers_Buffer__typ, len);
      (*s).bits -= __ASHL(len, 3, INTEGER);
      (*s).buf = __MODF((*s).buf, __ASH(1, (*s).bits, INTEGER));
      if (__ODD(__ASHR(exop, 5, SHORTINT))) {
        (*s).res.code = 1;
      } else {
        ZlibInflate_SetMsg(&(*s).res, ZlibInflate_Result__typ, (CHAR*)"invalid literal/length code", 28);
        (*s).res.code = -3;
      }
      return;
    }
  } while (!(*wavail < 258 || (*s).in.avail < 10));
  len = inavail - (*s).in.avail;
  if (__ASHR((*s).bits, 3, INTEGER) < len) {
    len = __ASHR((*s).bits, 3, INTEGER);
  }
  ZlibBuffers_Reread(&(*s).in, ZlibBuffers_Buffer__typ, len);
  (*s).bits -= __ASHL(len, 3, INTEGER);
  (*s).buf = __MODF((*s).buf, __ASH(1, (*s).bits, INTEGER));
  (*s).res.code = 0;
}

static void ZlibInflate_InflateCodes (ZlibInflate_Stream *s, void **s__typ)
{
  INTEGER wavail, base, index;
  ZlibInflate_Node node;
  SHORTINT exop;
  if ((*s).write < (*s).read) {
    wavail = ((*s).read - (*s).write) - 1;
  } else {
    wavail = 32768 - (*s).write;
  }
  for (;;) {
    switch ((*s).decode.state) {
      case 0: 
        if (wavail >= 258 && (*s).in.avail >= 10) {
          ZlibInflate_InflateFast(s, s__typ, &wavail);
          if ((*s).res.code != 0) {
            if ((*s).res.code == 1) {
              (*s).decode.state = 7;
            } else {
              (*s).decode.state = 9;
            }
            goto exit__0;
          }
        }
        (*s).decode.tree = (*s).decode.lltree;
        (*s).decode.state = 1;
        break;
      case 1: 
        if (!ZlibInflate_Need(s, s__typ, (*s).decode.tree.bits)) {
          goto exit__0;
        }
        base = (*s).decode.tree.base + __MODF((*s).buf, __ASH(1, (*s).decode.tree.bits, INTEGER));
        node = ((*s).decode.tree.node->data)[__X(base, (*s).decode.tree.node->len[0], (CHAR*)"ZlibInflate", 157220)];
        ZlibInflate_Dump(s, s__typ, node.bits);
        exop = (SHORTINT)node.exop - -128;
        if (exop == 0) {
          (*s).decode.lit = node.base;
          (*s).decode.state = 6;
        } else if (__ODD(__ASHR(exop, 4, SHORTINT))) {
          (*s).decode.extra = __MASK(exop, -16);
          (*s).decode.len = node.base;
          (*s).decode.state = 2;
        } else if (!__ODD(__ASHR(exop, 6, SHORTINT))) {
          (*s).decode.tree.bits = exop;
          (*s).decode.tree.base = base + (INTEGER)node.base;
        } else if (__ODD(__ASHR(exop, 5, SHORTINT))) {
          (*s).decode.state = 7;
        } else {
          ZlibInflate_SetMsg(&(*s).res, ZlibInflate_Result__typ, (CHAR*)"invalid literal/length code", 28);
          (*s).res.code = -3;
          (*s).decode.state = 9;
          ZlibInflate_Flush(s, s__typ);
          goto exit__0;
        }
        break;
      case 2: 
        if (!ZlibInflate_Need(s, s__typ, (*s).decode.extra)) {
          goto exit__0;
        }
        (*s).decode.len += (SHORTINT)__MODF((*s).buf, __ASH(1, (*s).decode.extra, INTEGER));
        ZlibInflate_Dump(s, s__typ, (*s).decode.extra);
        (*s).decode.tree = (*s).decode.dtree;
        (*s).decode.state = 3;
        break;
      case 3: 
        if (!ZlibInflate_Need(s, s__typ, (*s).decode.tree.bits)) {
          goto exit__0;
        }
        base = (*s).decode.tree.base + __MODF((*s).buf, __ASH(1, (*s).decode.tree.bits, INTEGER));
        node = ((*s).decode.tree.node->data)[__X(base, (*s).decode.tree.node->len[0], (CHAR*)"ZlibInflate", 165412)];
        ZlibInflate_Dump(s, s__typ, node.bits);
        exop = (SHORTINT)node.exop - -128;
        if (__ODD(__ASHR(exop, 4, SHORTINT))) {
          (*s).decode.extra = __MASK(exop, -16);
          (*s).decode.dist = node.base;
          (*s).decode.state = 4;
        } else if (!__ODD(__ASHR(exop, 6, SHORTINT))) {
          (*s).decode.tree.bits = exop;
          (*s).decode.tree.base = base + (INTEGER)node.base;
        } else {
          ZlibInflate_SetMsg(&(*s).res, ZlibInflate_Result__typ, (CHAR*)"invalid distance code", 22);
          (*s).res.code = -3;
          (*s).decode.state = 9;
          ZlibInflate_Flush(s, s__typ);
          goto exit__0;
        }
        break;
      case 4: 
        if (!ZlibInflate_Need(s, s__typ, (*s).decode.extra)) {
          goto exit__0;
        }
        (*s).decode.dist += (SHORTINT)__MODF((*s).buf, __ASH(1, (*s).decode.extra, INTEGER));
        ZlibInflate_Dump(s, s__typ, (*s).decode.extra);
        (*s).decode.state = 5;
        break;
      case 5: 
        index = __MASK((*s).write - (INTEGER)(*s).decode.dist, -32768);
        while ((*s).decode.len != 0) {
          if (!ZlibInflate_NeedOut(s, s__typ, &wavail)) {
            goto exit__0;
          }
          (*(*s).window)[__X((*s).write, 32768, (CHAR*)"ZlibInflate", 172329)] = (*(*s).window)[__X(index, 32768, (CHAR*)"ZlibInflate", 172329)];
          (*s).write += 1;
          wavail -= 1;
          index = __MASK(index + 1, -32768);
          (*s).decode.len -= 1;
        }
        (*s).decode.state = 0;
        break;
      case 6: 
        if (!ZlibInflate_NeedOut(s, s__typ, &wavail)) {
          goto exit__0;
        }
        (*(*s).window)[__X((*s).write, 32768, (CHAR*)"ZlibInflate", 174378)] = (CHAR)(*s).decode.lit;
        (*s).write += 1;
        wavail -= 1;
        (*s).decode.state = 0;
        break;
      case 7: 
        if ((*s).bits > 7) {
          __ASSERT((*s).bits < 16, 110, (CHAR*)"ZlibInflate", 175645);
          (*s).bits -= 8;
          (*s).buf = __MODF((*s).buf, __ASH(1, (*s).bits, INTEGER));
          ZlibBuffers_Reread(&(*s).in, ZlibBuffers_Buffer__typ, 1);
        }
        ZlibInflate_Flush(s, s__typ);
        if ((*s).read != (*s).write) {
          goto exit__0;
        } else {
          (*s).decode.state = 8;
        }
        break;
      case 8: 
        (*s).res.code = 1;
        goto exit__0;
        break;
      case 9: 
        (*s).res.code = -3;
        goto exit__0;
        break;
      default: 
        (*s).res.code = -2;
        goto exit__0;
        break;
    }
  }
  exit__0:;
}

static void ZlibInflate_ResetBlocks (ZlibInflate_Stream *s, void **s__typ, INTEGER *check)
{
  CHAR buf[1];
  *check = (*s).check;
  (*s).block.state = 0;
  (*s).buf = 0;
  (*s).bits = 0;
  (*s).read = 0;
  (*s).write = 0;
  if ((*s).checkFn != NIL) {
    (*s).check = (*(*s).checkFn)(0, (void*)buf, 1, 0, -1);
  }
}

static void ZlibInflate_NewBlocks (ZlibInflate_Stream *s, void **s__typ, ZlibInflate_CheckFunc checkFn)
{
  (*s).block.nodes = __NEWARR(NIL, 4, 2, 1, 1, (SYSTEM_ARRLEN)1440);
  (*s).window = __NEWARR(NIL, 1, 1, 1, 0, (SYSTEM_ARRLEN)32768);
  if ((*s).block.nodes == NIL || (*s).window == NIL) {
    (*s).block.nodes = NIL;
    (*s).window = NIL;
    (*s).res.code = -4;
  } else {
    (*s).checkFn = checkFn;
    ZlibInflate_ResetBlocks(s, s__typ, &(*s).check);
    (*s).res.code = 0;
  }
}

static void ZlibInflate_FreeBlocks (ZlibInflate_Stream *s, void **s__typ)
{
  ZlibInflate_ResetBlocks(s, s__typ, &(*s).check);
  (*s).block.nodes = NIL;
  (*s).window = NIL;
}

static void ZlibInflate_InflateBlocks (ZlibInflate_Stream *s, void **s__typ)
{
  INTEGER wavail, t, cnt, len;
  ZlibInflate_TreeNodes tn = {0};
  BYTE clen[288];
  ZlibInflate_Code code;
  INTEGER res;
  ZlibInflate_Node node;
  ZlibInflate_Tree lltree = {0}, dtree = {0};
  ZlibInflate_Window *_ptr__17 = NIL;
  if ((*s).write < (*s).read) {
    wavail = ((*s).read - (*s).write) - 1;
  } else {
    wavail = 32768 - (*s).write;
  }
  for (;;) {
    switch ((*s).block.state) {
      case 0: 
        if (!ZlibInflate_Need(s, s__typ, 3)) {
          goto exit__1;
        }
        t = __MASK((*s).buf, -8);
        (*s).block.last = __ODD(t);
        ZlibInflate_Dump(s, s__typ, 3);
        switch (__ASHR(t, 1, INTEGER)) {
          case 0: 
            ZlibInflate_Dump(s, s__typ, __MASK((*s).bits, -8));
            (*s).block.state = 1;
            break;
          case 1: 
            if (!ZlibInflate_FixedBuilt) {
              tn.node = __NEWARR(NIL, 4, 2, 1, 1, (SYSTEM_ARRLEN)544);
              tn.next = 0;
              ZlibInflate_MakeFixedLitLenCode((void*)clen, 288, &code, ZlibInflate_Code__typ);
              ZlibInflate_BuildTree((void*)clen, 288, &code, ZlibInflate_Code__typ, &tn, ZlibInflate_TreeNodes__typ, &ZlibInflate_FixedLitLenTree, ZlibInflate_Tree__typ, &res);
              __ASSERT(res == 0, 110, (CHAR*)"ZlibInflate", 196123);
              ZlibInflate_MakeFixedDistCode((void*)clen, 288, &code, ZlibInflate_Code__typ);
              ZlibInflate_BuildTree((void*)clen, 288, &code, ZlibInflate_Code__typ, &tn, ZlibInflate_TreeNodes__typ, &ZlibInflate_FixedDistTree, ZlibInflate_Tree__typ, &res);
              __ASSERT(res == 0 || res == -5, 111, (CHAR*)"ZlibInflate", 196913);
              ZlibInflate_FixedBuilt = 1;
            }
            ZlibInflate_NewCodes(s, s__typ, &ZlibInflate_FixedLitLenTree, ZlibInflate_Tree__typ, &ZlibInflate_FixedDistTree, ZlibInflate_Tree__typ);
            (*s).block.state = 6;
            break;
          case 2: 
            (*s).block.state = 3;
            break;
          case 3: 
            ZlibInflate_SetMsg(&(*s).res, ZlibInflate_Result__typ, (CHAR*)"invalid block type", 19);
            (*s).block.state = 9;
            (*s).res.code = -3;
            ZlibInflate_Flush(s, s__typ);
            goto exit__1;
            break;
          default: __CASECHK((CHAR*)"ZlibInflate", 199935);
        }
        break;
      case 1: 
        if (!ZlibInflate_Need(s, s__typ, 32)) {
          goto exit__1;
        }
        if (__MASK(__ASHR(-((*s).buf + 1), 16, INTEGER), -65536) != __MASK((*s).buf, -65536)) {
          ZlibInflate_SetMsg(&(*s).res, ZlibInflate_Result__typ, (CHAR*)"invalid stored block lengths", 29);
          (*s).block.state = 9;
          (*s).res.code = -3;
          ZlibInflate_Flush(s, s__typ);
          goto exit__1;
        }
        (*s).block.left = __MASK((*s).buf, -65536);
        (*s).buf = 0;
        (*s).bits = 0;
        if ((*s).block.left != 0) {
          (*s).block.state = 2;
        } else if ((*s).block.last) {
          (*s).block.state = 7;
        } else {
          (*s).block.state = 0;
        }
        break;
      case 2: 
        if ((*s).in.avail == 0) {
          ZlibInflate_Flush(s, s__typ);
          goto exit__1;
        }
        if (!ZlibInflate_NeedOut(s, s__typ, &wavail)) {
          goto exit__1;
        }
        t = (*s).block.left;
        if (t > (*s).in.avail) {
          t = (*s).in.avail;
        }
        if (t > wavail) {
          t = wavail;
        }
        if ((*s).write + t > 32768) {
          t = 32768 - (*s).write;
        }
        if (t > 0) {
          _ptr__17 = (*s).window;
          ZlibBuffers_ReadBytes(&(*s).in, ZlibBuffers_Buffer__typ, (void*)*_ptr__17, 32768, (*s).write, t);
        } else {
          ZlibInflate_Flush(s, s__typ);
          goto exit__1;
        }
        (*s).write += t;
        wavail -= t;
        (*s).block.left -= t;
        if ((*s).block.left == 0) {
          if ((*s).block.last) {
            (*s).block.state = 7;
          } else {
            (*s).block.state = 0;
          }
        }
        break;
      case 3: 
        if (!ZlibInflate_Need(s, s__typ, 14)) {
          goto exit__1;
        }
        t = __MASK((*s).buf, -16384);
        (*s).block.nlit = (SHORTINT)(257 + __MASK(t, -32));
        t = __ASHR(t, 5, INTEGER);
        (*s).block.ndist = (BYTE)(1 + __MASK(t, -32));
        t = __ASHR(t, 5, INTEGER);
        (*s).block.nclen = (BYTE)(4 + t);
        if ((*s).block.nlit > 286 || (*s).block.ndist > 30) {
          ZlibInflate_SetMsg(&(*s).res, ZlibInflate_Result__typ, (CHAR*)"too many length or distance symbols", 36);
          (*s).block.state = 9;
          (*s).res.code = -3;
          ZlibInflate_Flush(s, s__typ);
          goto exit__1;
        }
        ZlibInflate_Dump(s, s__typ, 14);
        (*s).block.index = 0;
        (*s).block.state = 4;
        break;
      case 4: 
        while ((*s).block.index < (SHORTINT)(*s).block.nclen) {
          if (!ZlibInflate_Need(s, s__typ, 3)) {
            goto exit__1;
          }
          (*s).block.clen[__X(ZlibInflate_Order[__X((*s).block.index, 19, (CHAR*)"ZlibInflate", 215364)], 319, (CHAR*)"ZlibInflate", 215364)] = (BYTE)__MASK((*s).buf, -8);
          (*s).block.index += 1;
          ZlibInflate_Dump(s, s__typ, 3);
        }
        while ((*s).block.index < 19) {
          (*s).block.clen[__X(ZlibInflate_Order[__X((*s).block.index, 19, (CHAR*)"ZlibInflate", 216620)], 319, (CHAR*)"ZlibInflate", 216620)] = 0;
          (*s).block.index += 1;
        }
        tn.node = (*s).block.nodes;
        tn.next = 0;
        code.bits = 7;
        code.offset = 0;
        code.size = 19;
        code.simple = 19;
        ZlibInflate_BuildTree((void*)(*s).block.clen, 319, &code, ZlibInflate_Code__typ, &tn, ZlibInflate_TreeNodes__typ, &(*s).block.btree, ZlibInflate_Tree__typ, &res);
        if (res == -3) {
          ZlibInflate_SetMsg(&(*s).res, ZlibInflate_Result__typ, (CHAR*)"oversubscribed dynamic bit lengths tree", 40);
          (*s).block.state = 9;
        } else if (res == -5 || (*s).block.btree.bits == 0) {
          ZlibInflate_SetMsg(&(*s).res, ZlibInflate_Result__typ, (CHAR*)"incomplete dynamic bit lengths tree", 36);
          res = -3;
          (*s).block.state = 9;
        }
        if (res != 0) {
          (*s).res.code = res;
          ZlibInflate_Flush(s, s__typ);
          goto exit__1;
        }
        (*s).block.index = 0;
        (*s).block.state = 5;
        break;
      case 5: 
        while ((*s).block.index < (*s).block.nlit + (SHORTINT)(*s).block.ndist) {
          if (!ZlibInflate_Need(s, s__typ, (*s).block.btree.bits)) {
            goto exit__1;
          }
          t = (*s).block.btree.base + __MODF((*s).buf, __ASH(1, (*s).block.btree.bits, INTEGER));
          node = ((*s).block.btree.node->data)[__X(t, (*s).block.btree.node->len[0], (CHAR*)"ZlibInflate", 223010)];
          if (node.base < 16) {
            ZlibInflate_Dump(s, s__typ, node.bits);
            (*s).block.clen[__X((*s).block.index, 319, (CHAR*)"ZlibInflate", 223797)] = (BYTE)node.base;
            (*s).block.index += 1;
          } else {
            switch (node.base) {
              case 16: 
                if (!ZlibInflate_Need(s, s__typ, node.bits + 2)) {
                  goto exit__1;
                }
                ZlibInflate_Dump(s, s__typ, node.bits);
                cnt = 3 + __MASK((*s).buf, -4);
                ZlibInflate_Dump(s, s__typ, 2);
                if ((*s).block.index == 0) {
                  ZlibInflate_SetMsg(&(*s).res, ZlibInflate_Result__typ, (CHAR*)"invalid bit length repeat (no previous code length)", 52);
                  (*s).res.code = -3;
                  (*s).block.state = 9;
                  ZlibInflate_Flush(s, s__typ);
                  goto exit__1;
                }
                len = (*s).block.clen[__X((*s).block.index - 1, 319, (CHAR*)"ZlibInflate", 227327)];
                break;
              case 17: 
                if (!ZlibInflate_Need(s, s__typ, node.bits + 3)) {
                  goto exit__1;
                }
                ZlibInflate_Dump(s, s__typ, node.bits);
                cnt = 3 + __MASK((*s).buf, -8);
                ZlibInflate_Dump(s, s__typ, 3);
                len = 0;
                break;
              case 18: 
                if (!ZlibInflate_Need(s, s__typ, node.bits + 7)) {
                  goto exit__1;
                }
                ZlibInflate_Dump(s, s__typ, node.bits);
                cnt = 11 + __MASK((*s).buf, -128);
                ZlibInflate_Dump(s, s__typ, 7);
                len = 0;
                break;
              default: __CASECHK((CHAR*)"ZlibInflate", 228863);
            }
            if ((INTEGER)(*s).block.index + cnt > (INTEGER)((*s).block.nlit + (SHORTINT)(*s).block.ndist)) {
              ZlibInflate_SetMsg(&(*s).res, ZlibInflate_Result__typ, (CHAR*)"invalid bit length repeat", 26);
              (*s).res.code = -3;
              (*s).block.state = 9;
              ZlibInflate_Flush(s, s__typ);
              goto exit__1;
            }
            do {
              (*s).block.clen[__X((*s).block.index, 319, (CHAR*)"ZlibInflate", 230967)] = (BYTE)len;
              (*s).block.index += 1;
              cnt -= 1;
            } while (!(cnt == 0));
          }
        }
        tn.node = (*s).block.nodes;
        tn.next = 0;
        ZlibInflate_MakeLitLenCode(&code, ZlibInflate_Code__typ, 9, 0, (*s).block.nlit, 257);
        ZlibInflate_BuildTree((void*)(*s).block.clen, 319, &code, ZlibInflate_Code__typ, &tn, ZlibInflate_TreeNodes__typ, &lltree, ZlibInflate_Tree__typ, &res);
        if (res != 0 || lltree.bits == 0) {
          if (res == -3) {
            ZlibInflate_SetMsg(&(*s).res, ZlibInflate_Result__typ, (CHAR*)"oversubscribed literal/length tree", 35);
          } else if (res != -4) {
            ZlibInflate_SetMsg(&(*s).res, ZlibInflate_Result__typ, (CHAR*)"incomplete literal/length tree", 31);
            res = -3;
          }
        } else {
          ZlibInflate_MakeDistCode(&code, ZlibInflate_Code__typ, 6, (*s).block.nlit, (*s).block.ndist, 0);
          ZlibInflate_BuildTree((void*)(*s).block.clen, 319, &code, ZlibInflate_Code__typ, &tn, ZlibInflate_TreeNodes__typ, &dtree, ZlibInflate_Tree__typ, &res);
          if (res != 0 || (dtree.bits == 0 && (*s).block.nlit > 257)) {
            if (res == -3) {
              ZlibInflate_SetMsg(&(*s).res, ZlibInflate_Result__typ, (CHAR*)"oversubscribed distance tree", 29);
            } else if (res == -5) {
              ZlibInflate_SetMsg(&(*s).res, ZlibInflate_Result__typ, (CHAR*)"incomplete distance tree", 25);
              res = -3;
            } else if (res != -4) {
              ZlibInflate_SetMsg(&(*s).res, ZlibInflate_Result__typ, (CHAR*)"empty distance tree with lengths", 33);
              res = -3;
            }
          }
        }
        if (res != 0) {
          if (res == -3) {
            (*s).block.state = 9;
          }
          (*s).res.code = res;
          ZlibInflate_Flush(s, s__typ);
          goto exit__1;
        }
        ZlibInflate_NewCodes(s, s__typ, &lltree, ZlibInflate_Tree__typ, &dtree, ZlibInflate_Tree__typ);
        (*s).block.state = 6;
        break;
      case 6: 
        ZlibInflate_InflateCodes(s, s__typ);
        if ((*s).res.code != 1) {
          ZlibInflate_Flush(s, s__typ);
          goto exit__1;
        }
        (*s).res.code = 0;
        ZlibInflate_FreeCodes(s, s__typ);
        if ((*s).block.last) {
          (*s).block.state = 7;
        } else {
          (*s).block.state = 0;
        }
        break;
      case 7: 
        ZlibInflate_Flush(s, s__typ);
        if ((*s).read != (*s).write) {
          goto exit__1;
        }
        (*s).block.state = 8;
        break;
      case 8: 
        (*s).res.code = 1;
        goto exit__1;
        break;
      case 9: 
        (*s).res.code = -3;
        goto exit__1;
        break;
      default: 
        (*s).res.code = -2;
        goto exit__1;
        break;
    }
  }
  exit__1:;
}

static void ZlibInflate_SetBlockDict (ZlibInflate_Stream *s, void **s__typ, CHAR *dict, INTEGER dict__len, INTEGER offset, INTEGER len)
{
  __ASSERT(len <= 32768 && offset + len <= dict__len, 100, (CHAR*)"ZlibInflate", 249408);
  __MOVE((SYSTEM_ADRINT)&dict[0], (SYSTEM_ADRINT)&(*(*s).window)[0], len);
  (*s).read = len;
  (*s).write = len;
}

static BOOLEAN ZlibInflate_BlockSyncPoint (ZlibInflate_Stream *s, void **s__typ)
{
  return (*s).block.state == 1;
}

static void ZlibInflate_Reset0 (ZlibInflate_Stream *stream, void **stream__typ)
{
  INTEGER check;
  if ((*stream).open) {
    (*stream).res.msg = NIL;
    if ((*stream).wrapper) {
      (*stream).inf.state = 0;
    } else {
      (*stream).inf.state = 7;
    }
    ZlibInflate_ResetBlocks(stream, stream__typ, &check);
    (*stream).res.code = 0;
  } else {
    (*stream).res.code = -2;
  }
}

void ZlibInflate_Reset (ZlibInflate_Stream *stream, void **stream__typ)
{
  ZlibInflate_Reset0(stream, stream__typ);
  if ((*stream).open) {
    ZlibBuffers_Reset(&(*stream).in, ZlibBuffers_Buffer__typ);
    ZlibBuffers_Reset(&(*stream).out, ZlibBuffers_Buffer__typ);
  }
}

/*----------------------------------------------------------------------------*/
void ZlibInflate_Open (ZlibInflate_Stream *stream, void **stream__typ, BOOLEAN wrapper)
{
  ZlibInflate_CheckFunc checkFn = NIL;
  (*stream).res.msg = NIL;
  (*stream).wrapper = wrapper;
  (*stream).open = 1;
  if (wrapper) {
    checkFn = Zlib_Adler32;
  } else {
    checkFn = NIL;
  }
  ZlibInflate_NewBlocks(stream, stream__typ, checkFn);
  if ((*stream).res.code == 0) {
    ZlibInflate_Reset(stream, stream__typ);
  }
}

/*----------------------------------------------------------------------------*/
void ZlibInflate_Close (ZlibInflate_Stream *stream, void **stream__typ)
{
  ZlibInflate_FreeBlocks(stream, stream__typ);
  (*stream).res.code = 0;
}

/*----------------------------------------------------------------------------*/
void ZlibInflate_Inflate (ZlibInflate_Stream *stream, void **stream__typ, BYTE flush)
{
  INTEGER res;
  CHAR byte;
  if (!(*stream).open) {
    (*stream).res.code = -2;
  } else {
    if (flush == 4) {
      res = -5;
    } else {
      res = 0;
    }
    (*stream).res.code = -5;
    for (;;) {
      if (__IN((*stream).inf.state, 0x0f3f)) {
        if ((*stream).in.avail == 0) {
          break;
        }
        (*stream).res.code = res;
        ZlibBuffers_Read(&(*stream).in, ZlibBuffers_Buffer__typ, &byte);
      }
      switch ((*stream).inf.state) {
        case 0: 
          (*stream).inf.method = (SHORTINT)byte;
          if (__MASK((*stream).inf.method, -16) != 8) {
            (*stream).inf.state = 13;
            (*stream).inf.marker = 5;
            ZlibInflate_SetMsg(&(*stream).res, ZlibInflate_Result__typ, (CHAR*)"unknown compression method", 27);
          } else if (__ASHR((*stream).inf.method, 4, SHORTINT) + 8 > 15) {
            (*stream).inf.state = 13;
            (*stream).inf.marker = 5;
            ZlibInflate_SetMsg(&(*stream).res, ZlibInflate_Result__typ, (CHAR*)"invalid window size", 20);
          } else {
            (*stream).inf.state = 1;
          }
          break;
        case 1: 
          if (__MOD(__ASHL((INTEGER)(*stream).inf.method, 8, INTEGER) + (INTEGER)byte, 31) != 0) {
            (*stream).inf.state = 13;
            (*stream).inf.marker = 5;
            ZlibInflate_SetMsg(&(*stream).res, ZlibInflate_Result__typ, (CHAR*)"incorrect header check", 23);
          } else if (__ODD(__ASHR((SHORTINT)byte, 5, SHORTINT))) {
            (*stream).inf.state = 2;
          } else {
            (*stream).inf.state = 7;
          }
          break;
        case 2: 
          (*stream).inf.check.stored = __ASHL((INTEGER)byte, 24, INTEGER);
          (*stream).inf.state = 3;
          break;
        case 3: 
          (*stream).inf.check.stored += __ASHL((INTEGER)byte, 16, INTEGER);
          (*stream).inf.state = 4;
          break;
        case 4: 
          (*stream).inf.check.stored += __ASHL((INTEGER)byte, 8, INTEGER);
          (*stream).inf.state = 5;
          break;
        case 5: 
          (*stream).inf.check.stored += (INTEGER)byte;
          (*stream).inf.state = 6;
          (*stream).res.code = 2;
          goto exit__2;
          break;
        case 6: 
          (*stream).inf.state = 13;
          (*stream).inf.marker = 0;
          ZlibInflate_SetMsg(&(*stream).res, ZlibInflate_Result__typ, (CHAR*)"need dictionary", 16);
          (*stream).res.code = -2;
          goto exit__2;
          break;
        case 7: 
          ZlibInflate_InflateBlocks(stream, stream__typ);
          if ((*stream).res.code == -3) {
            (*stream).inf.state = 13;
            (*stream).inf.marker = 0;
          } else if ((*stream).res.code == 1) {
            (*stream).res.code = res;
            ZlibInflate_ResetBlocks(stream, stream__typ, &(*stream).inf.check.calc);
            if ((*stream).wrapper) {
              (*stream).inf.state = 8;
            } else {
              (*stream).inf.state = 12;
            }
          } else {
            if ((*stream).res.code == 0) {
              (*stream).res.code = res;
            }
            goto exit__2;
          }
          break;
        case 8: 
          (*stream).inf.check.stored = __ASHL((INTEGER)byte, 24, INTEGER);
          (*stream).inf.state = 9;
          break;
        case 9: 
          (*stream).inf.check.stored += __ASHL((INTEGER)byte, 16, INTEGER);
          (*stream).inf.state = 10;
          break;
        case 10: 
          (*stream).inf.check.stored += __ASHL((INTEGER)byte, 8, INTEGER);
          (*stream).inf.state = 11;
          break;
        case 11: 
          (*stream).inf.check.stored += (INTEGER)byte;
          if ((*stream).inf.check.stored != (*stream).inf.check.calc) {
            (*stream).inf.state = 13;
            (*stream).inf.marker = 5;
            ZlibInflate_SetMsg(&(*stream).res, ZlibInflate_Result__typ, (CHAR*)"incorrect data check", 21);
          } else {
            (*stream).inf.state = 12;
          }
          break;
        case 12: 
          (*stream).res.code = 1;
          goto exit__2;
          break;
        case 13: 
          (*stream).res.code = -3;
          goto exit__2;
          break;
        default: __CASECHK((CHAR*)"ZlibInflate", 289023);
      }
    }
    exit__2:;
  }
}

/*----------------------------------------------------------------------------*/
void ZlibInflate_SetDictionary (ZlibInflate_Stream *stream, void **stream__typ, CHAR *dict, INTEGER dict__len, INTEGER dictLen)
{
  INTEGER len, idx;
  if ((*stream).open && (*stream).inf.state == 6) {
    if (Zlib_Adler32(1, (void*)dict, dict__len, 0, dictLen) == (*stream).inf.check.stored) {
      len = dictLen;
      idx = 0;
      if (len >= 32768) {
        len = 32767;
        idx = dictLen - len;
      }
      ZlibInflate_SetBlockDict(stream, stream__typ, (void*)dict, dict__len, idx, len);
      (*stream).inf.state = 7;
      (*stream).res.code = 0;
    } else {
      (*stream).res.code = -3;
    }
  } else {
    (*stream).res.code = -2;
  }
}

/*----------------------------------------------------------------------------*/
void ZlibInflate_Sync (ZlibInflate_Stream *stream, void **stream__typ)
{
  INTEGER m;
  CHAR mark[4];
  CHAR byte;
  if (!(*stream).open) {
    (*stream).res.code = -2;
  } else {
    if ((*stream).inf.state != 13) {
      (*stream).inf.state = 13;
      (*stream).inf.marker = 0;
    }
    if ((*stream).in.avail == 0) {
      (*stream).res.code = -5;
    } else {
      mark[0] = 0x00;
      mark[1] = 0x00;
      mark[2] = 0xff;
      mark[3] = 0xff;
      m = (*stream).inf.marker;
      while ((*stream).in.avail > 0 && m < 4) {
        ZlibBuffers_Read(&(*stream).in, ZlibBuffers_Buffer__typ, &byte);
        if (byte == mark[__X(m, 4, (CHAR*)"ZlibInflate", 301064)]) {
          m += 1;
        } else if (byte == 0x00) {
          m = 0;
        } else {
          m = 4 - m;
        }
      }
      (*stream).inf.marker = (SHORTINT)m;
      if (m != 4) {
        (*stream).res.code = -3;
      } else {
        ZlibInflate_Reset0(stream, stream__typ);
        (*stream).inf.state = 7;
        (*stream).res.code = 0;
      }
    }
  }
}

/*----------------------------------------------------------------------------*/
BOOLEAN ZlibInflate_SyncPoint (ZlibInflate_Stream *stream, void **stream__typ)
{
  if ((*stream).open) {
    return ZlibInflate_BlockSyncPoint(stream, stream__typ);
  } else {
    (*stream).res.code = -2;
    return 0;
  }
  __RETCHK((CHAR*)"ZlibInflate", 306943);
}

/*----------------------------------------------------------------------------*/
void ZlibInflate_Uncompress (CHAR *src, INTEGER src__len, CHAR *dst, INTEGER dst__len, INTEGER srcoffset, INTEGER srclen, INTEGER dstoffset, INTEGER dstlen, INTEGER *len, ZlibInflate_Result *res, void **res__typ)
{
  ZlibInflate_Stream s = {0};
  ZlibBuffers_Init(&s.in, ZlibBuffers_Buffer__typ, (void*)src, src__len, srcoffset, srclen, srclen);
  ZlibBuffers_Init(&s.out, ZlibBuffers_Buffer__typ, (void*)dst, dst__len, dstoffset, dstlen, dstlen);
  ZlibInflate_Open(&s, ZlibInflate_Stream__typ, 1);
  if (s.res.code == 0) {
    ZlibInflate_Inflate(&s, ZlibInflate_Stream__typ, 4);
    if (s.res.code == 1) {
      *len = s.out.totalOut;
      ZlibInflate_Close(&s, ZlibInflate_Stream__typ);
      __GUARDEQR(res, res__typ, ZlibInflate_Result) = s.res;
    } else {
      __GUARDEQR(res, res__typ, ZlibInflate_Result) = s.res;
      if ((*res).code == 0) {
        (*res).code = -5;
      }
      ZlibInflate_Close(&s, ZlibInflate_Stream__typ);
    }
  } else {
    __GUARDEQR(res, res__typ, ZlibInflate_Result) = s.res;
  }
}

/*----------------------------------------------------------------------------*/
static void EnumPtrs(void (*P)(void*))
{
  __ENUMR(&ZlibInflate_FixedLitLenTree, ZlibInflate_Tree__typ, 12, 1, P);
  __ENUMR(&ZlibInflate_FixedDistTree, ZlibInflate_Tree__typ, 12, 1, P);
}

__TDESC(ZlibInflate_Result__desc, 2, 1) = {__TDFLDS("Result", 8), {4, -8}};
__TDESC(ZlibInflate_Code__desc, 2, 0) = {__TDFLDS("Code", 102), {-4}};
__TDESC(ZlibInflate_Node__desc, 2, 0) = {__TDFLDS("Node", 4), {-4}};
__TDESC(ZlibInflate_TreeNodes__desc, 2, 1) = {__TDFLDS("TreeNodes", 8), {0, -8}};
__TDESC(ZlibInflate_Tree__desc, 1, 1) = {__TDFLDS("Tree", 12), {0, -8}};
__TDESC(ZlibInflate__1__desc, 2, 0) = {__TDFLDS("", 8), {-4}};
__TDESC(ZlibInflate__2__desc, 2, 0) = {__TDFLDS("", 16), {-4}};
__TDESC(ZlibInflate__3__desc, 2, 2) = {__TDFLDS("", 352), {336, 340, -12}};
__TDESC(ZlibInflate__4__desc, 2, 3) = {__TDFLDS("", 48), {4, 16, 28, -16}};
__TDESC(ZlibInflate_Stream__desc, 2, 7) = {__TDFLDS("Stream", 504), {52, 60, 440, 444, 460, 472, 484, -32}};

export void *ZlibInflate__init (void)
{
  __DEFMOD;
  __IMPORT(Zlib__init);
  __IMPORT(ZlibBuffers__init);
  __REGMOD("ZlibInflate", EnumPtrs);
  __INITYP(ZlibInflate_Result, ZlibInflate_Result, 0);
  __INITYP(ZlibInflate_Code, ZlibInflate_Code, 0);
  __INITYP(ZlibInflate_Node, ZlibInflate_Node, 0);
  __INITYP(ZlibInflate_TreeNodes, ZlibInflate_TreeNodes, 0);
  __INITYP(ZlibInflate_Tree, ZlibInflate_Tree, 0);
  __INITYP(ZlibInflate__1, ZlibInflate__1, 0);
  __INITYP(ZlibInflate__2, ZlibInflate__2, 0);
  __INITYP(ZlibInflate__3, ZlibInflate__3, 0);
  __INITYP(ZlibInflate__4, ZlibInflate__4, 0);
  __INITYP(ZlibInflate_Stream, ZlibInflate_Stream, 0);
/* BEGIN */
  ZlibInflate_FixedBuilt = 0;
  ZlibInflate_Order[0] = 16;
  ZlibInflate_Order[1] = 17;
  ZlibInflate_Order[2] = 18;
  ZlibInflate_Order[3] = 0;
  ZlibInflate_Order[4] = 8;
  ZlibInflate_Order[5] = 7;
  ZlibInflate_Order[6] = 9;
  ZlibInflate_Order[7] = 6;
  ZlibInflate_Order[8] = 10;
  ZlibInflate_Order[9] = 5;
  ZlibInflate_Order[10] = 11;
  ZlibInflate_Order[11] = 4;
  ZlibInflate_Order[12] = 12;
  ZlibInflate_Order[13] = 3;
  ZlibInflate_Order[14] = 13;
  ZlibInflate_Order[15] = 2;
  ZlibInflate_Order[16] = 14;
  ZlibInflate_Order[17] = 1;
  ZlibInflate_Order[18] = 15;
  __ENDMOD;
}
