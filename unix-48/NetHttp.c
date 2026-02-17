/* Ofront+ 1.0 -sC -48 */
#include "SYSTEM.oh"
#include "libCurl.oh"

typedef
  struct CHAR8_ARRAY *NetHttp_Buffer;

typedef
  struct NetHttp_Socket {
    libCurl_PCURL hCurl;
    BOOLEAN ok;
    CHAR err[128];
    NetHttp_Buffer data;
    INTEGER datasize;
  } NetHttp_Socket;

export void NetHttp_Socket_Get (NetHttp_Socket *self, void **self__typ, CHAR *url, INTEGER url__len);
#define __NetHttp_Socket_Get(self, self__typ, url, url__len) __SEND(self__typ, NetHttp_Socket_Get, 1, void(*)(NetHttp_Socket*, void **, CHAR*, INTEGER ), (self, self__typ, url, url__len))


#ifndef CHAR8_ARRAY_DEF
#define CHAR8_ARRAY_DEF
typedef struct CHAR8_ARRAY {
  INTEGER len[1];
  CHAR data[1];
} CHAR8_ARRAY;
#endif 


export void **NetHttp_Socket__typ;

static INTEGER NetHttp_Length (INTEGER s);
static INTEGER NetHttp_write_callback (INTEGER ptr, INTEGER size, INTEGER nmemb, INTEGER userdata);

#include "libCurl.h0"

/*============================================================================*/

static INTEGER NetHttp_Length (INTEGER s)
{
  INTEGER len;
  CHAR ch;
  len = 0;
  __GET(s, ch, CHAR);
  while (ch != 0x00) {
    len += 1;
    __GET(s + len, ch, CHAR);
  }
  return len;
}

typedef
  NetHttp_Socket *__5;

static INTEGER NetHttp_write_callback (INTEGER ptr, INTEGER size, INTEGER nmemb, INTEGER userdata)
{
  __5 self = NIL;
  INTEGER cur_size, n;
  NetHttp_Buffer newbuf = NIL;
  self = (__5)userdata;
  cur_size = (INTEGER)size * (INTEGER)nmemb;
  if (self->datasize + cur_size >= self->data->len[0]) {
    newbuf = __NEWARR(NIL, 1, 1, 1, 1, (SYSTEM_ARRLEN)(__ASHR(((self->datasize + cur_size) + 1) * 3, 1, INTEGER)));
    __MOVE((SYSTEM_ADRINT)&(self->data->data)[0], (SYSTEM_ADRINT)&(newbuf->data)[0], self->datasize);
    self->data = newbuf;
  }
  __MOVE(ptr, (SYSTEM_ADRINT)&(self->data->data)[__X(self->datasize, self->data->len[0], (CHAR*)"NetHttp", 14658)], cur_size);
  self->datasize += cur_size;
  (self->data->data)[__X(self->datasize, self->data->len[0], (CHAR*)"NetHttp", 14910)] = 0x00;
  return cur_size;
}

void NetHttp_Socket_Get (NetHttp_Socket *self, void **self__typ, CHAR *url, INTEGER url__len)
{
  INTEGER msglen;
  CHAR ch;
  INTEGER res, syserr;
  (*self).hCurl = curl_easy_init();
  (*self).ok = (*self).hCurl != NIL;
  if ((*self).ok) {
    if (libCurl_curl_easy_setopt_A((*self).hCurl, 10002, (SYSTEM_ADRINT)url) != 0) {
      (*self).ok = 0;
      __MOVE((CHAR*)"CURLOPT_URL", (*self).err, 12);
      return;
    }
    if (libCurl_curl_easy_setopt_I((*self).hCurl, 52, 1) != 0) {
      (*self).ok = 0;
      __MOVE((CHAR*)"CURLOPT_FOLLOWLOCATION", (*self).err, 23);
      return;
    }
    if (libCurl_curl_easy_setopt_A((*self).hCurl, 10001, (SYSTEM_ADRINT)self) != 0) {
      (*self).ok = 0;
      __MOVE((CHAR*)"CURLOPT_WRITEDATA", (*self).err, 18);
      return;
    }
    if (libCurl_curl_easy_setopt_C((*self).hCurl, 20011, NetHttp_write_callback) != 0) {
      (*self).ok = 0;
      __MOVE((CHAR*)"CURLOPT_WRITEFUNCTION", (*self).err, 22);
      return;
    }
    (*self).datasize = 0;
    if ((*self).data == NIL) {
      (*self).data = __NEWARR(NIL, 1, 1, 1, 1, (SYSTEM_ARRLEN)32768);
    }
    res = curl_easy_perform((*self).hCurl);
    if (res != 0) {
      (*self).ok = 0;
      syserr = curl_easy_strerror(res);
      msglen = NetHttp_Length(syserr);
      if (msglen >= 128) {
        msglen = 127;
      }
      __MOVE(syserr, (SYSTEM_ADRINT)&(*self).err[0], msglen);
      (*self).err[__X(msglen, 128, (CHAR*)"NetHttp", 24348)] = 0x00;
    }
    curl_easy_cleanup((*self).hCurl);
  }
}

/*----------------------------------------------------------------------------*/
__TDESC(NetHttp_Socket__desc, 3, 1) = {__TDFLDS("Socket", 144), {136, -8}};

export void *NetHttp__init (void)
{
  __DEFMOD;
  __REGMOD("NetHttp", 0);
  __INITYP(NetHttp_Socket, NetHttp_Socket, 0);
  __INITBP(NetHttp_Socket, NetHttp_Socket_Get, 1);
/* BEGIN */
  __ENDMOD;
}
