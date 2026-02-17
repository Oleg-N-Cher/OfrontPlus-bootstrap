/* Ofront+ 1.0 -sC -88 */
#include "SYSTEM.oh"
#include "SDL2.oh"
#include "Strings.oh"
#include "Texts.oh"
#include "Files.oh"
#include "Platform.oh"
#include "Out.oh"

typedef
  struct Graph_BitmapDesc *Graph_Bitmap;

typedef
  struct Graph_BitmapDesc {
    SDL2_Surface surface;
    INTEGER w, h;
  } Graph_BitmapDesc;

export void Graph_Bitmap_Finalize (Graph_Bitmap bmp);
#define __Graph_Bitmap_Finalize(bmp) __SEND(__TYPEOF(bmp), Graph_Bitmap_Finalize, 1, void(*)(Graph_Bitmap), (bmp))

typedef
  struct Graph_CharGeo {
    INTEGER w, x, y;
  } Graph_CharGeo;

typedef
  void (*Graph_CloseBtnProc)(void);

typedef
  struct Graph_Key {
    INTEGER code, sym;
    SET mod;
    BOOLEAN repeat;
  } Graph_Key;

typedef
  struct Graph_Event {
    INTEGER type;
    Graph_Key key;
    INTEGER x, y, xRel, yRel, button;
    SET buttons;
    BOOLEAN down;
    CHAR s[32];
  } Graph_Event;

typedef
  struct Graph_EventQueue {
    Graph_Event buf[256];
    INTEGER first, last, len;
  } Graph_EventQueue;

typedef
  struct Graph_FontDesc *Graph_Font;

typedef
  struct Graph_FontDesc {
    Graph_Bitmap bmp;
    Graph_CharGeo geo[512];
    INTEGER geoCount, h;
  } Graph_FontDesc;

typedef
  struct Graph_MonoFontDesc *Graph_MonoFont;

typedef
  struct Graph_MonoFontDesc {
    Graph_Bitmap bmp;
    INTEGER charW, charH, charRows, charsInRow;
    struct SDL2_Rect_ARRAY_ARRAY *sprites;
  } Graph_MonoFontDesc;

typedef
  struct Graph_Region {
    INTEGER x, y, w, h;
  } Graph_Region;


#ifndef SDL2_Rect_ARRAY_ARRAY_DEF
#define SDL2_Rect_ARRAY_ARRAY_DEF
typedef struct SDL2_Rect_ARRAY_ARRAY {
  INTEGER len[2];
  SDL2_Rect data[1];
} SDL2_Rect_ARRAY_ARRAY;
#endif 

static SYSTEM_PTR Graph_window, Graph_renderer;
static Graph_Bitmap Graph_screen;
static SYSTEM_PTR Graph_screenTexture;
static Graph_EventQueue Graph_events;
static INTEGER Graph_keyPressed, Graph_sizeStepX, Graph_sizeStepY, Graph_wantW, Graph_wantH;
static BOOLEAN Graph_wantFullscreen, Graph_wantBuffer, Graph_wantSpread, Graph_wantSharpPixels, Graph_wantSoftware, Graph_wantMouse, Graph_wantSound, Graph_wantNet;
static INTEGER Graph_wantFPS;
static Graph_Bitmap Graph_buffer;
static INTEGER Graph_lastFlip, Graph_frames, Graph_framesT, Graph_screenAlpha;
static Graph_Region Graph_flipRegion;
static INTEGER Graph_mouseX, Graph_mouseY, Graph_mouseFocusX, Graph_mouseFocusY;
static BOOLEAN Graph_lastBlitMouseOutside;
static INTEGER Graph_lastBlitMouseX, Graph_lastBlitMouseY;
static BOOLEAN Graph_needRedrawMouse, Graph_showMouse;
static Graph_Bitmap Graph_stdMousePointer, Graph_mousePointer, Graph_underMouse;
export INTEGER Graph_randomSeed;

export void **Graph_BitmapDesc__typ;
export void **Graph_MonoFontDesc__typ;
export void **Graph_CharGeo__typ;
export void **Graph_FontDesc__typ;
export void **Graph_Key__typ;
export void **Graph_Region__typ;
export void **Graph_Event__typ;
export void **Graph_EventQueue__typ;

export void Graph_AddRegion (INTEGER x, INTEGER y, INTEGER w, INTEGER h);
export BOOLEAN Graph_AltPressed (void);
export void Graph_Blit (Graph_Bitmap src, Graph_Bitmap dest, INTEGER sx, INTEGER sy, INTEGER sw, INTEGER sh, INTEGER dx, INTEGER dy);
export void Graph_BlitWhole (Graph_Bitmap src, Graph_Bitmap dest, INTEGER x, INTEGER y);
export INTEGER Graph_BmpCol (Graph_Bitmap bmp, INTEGER r, INTEGER g, INTEGER b);
static void Graph_CheckWantedScreenSize (void);
export void Graph_Circle (Graph_Bitmap bmp, INTEGER x, INTEGER y, INTEGER r, INTEGER color);
export void Graph_CircleFill (Graph_Bitmap bmp, INTEGER x, INTEGER y, INTEGER r, INTEGER color);
export void Graph_ClearBitmap (Graph_Bitmap bmp);
export void Graph_ClearScreen (void);
export void Graph_ClearScreenToColor (INTEGER color);
export void Graph_ClearToColor (Graph_Bitmap bmp, INTEGER color);
export void Graph_Close (void);
export void Graph_ColorToRGB (INTEGER color, INTEGER *r, INTEGER *g, INTEGER *b);
export void Graph_ColorToRGBA (INTEGER color, INTEGER *r, INTEGER *g, INTEGER *b, INTEGER *a);
export Graph_Bitmap Graph_CreateBitmap (INTEGER w, INTEGER h);
export void Graph_CreateStdMousePointer (void);
export BOOLEAN Graph_CtrlPressed (void);
export void Graph_Delay (INTEGER n);
export void Graph_DestroyBitmap (Graph_Bitmap bmp);
export void Graph_DrawChar (Graph_Bitmap dest, Graph_Font font, INTEGER x, INTEGER y, INTEGER ch, INTEGER color, INTEGER *w);
export void Graph_DrawCharacter (Graph_Bitmap dest, Graph_MonoFont font, INTEGER x, INTEGER y, CHAR ch, INTEGER fg);
export void Graph_DrawCharacterEx (Graph_Bitmap dest, Graph_Bitmap sprite, INTEGER x, INTEGER y, INTEGER color, INTEGER bg);
export void Graph_DrawSpriteEx (Graph_Bitmap dest, Graph_Bitmap sprite, INTEGER x, INTEGER y, INTEGER mode, SET flip);
export void Graph_DrawString (Graph_Bitmap dest, Graph_MonoFont font, INTEGER x, INTEGER y, CHAR *s, INTEGER s__len, INTEGER fg);
export void Graph_DrawText (Graph_Bitmap dest, Graph_Font font, INTEGER x, INTEGER y, CHAR *s, INTEGER s__len, INTEGER color);
export void Graph_Ellipse (Graph_Bitmap bmp, INTEGER x, INTEGER y, INTEGER rx, INTEGER ry, INTEGER color);
export void Graph_EllipseFill (Graph_Bitmap bmp, INTEGER x, INTEGER y, INTEGER rx, INTEGER ry, INTEGER color);
export void Graph_FastLine (Graph_Bitmap bmp, INTEGER x1, INTEGER y1, INTEGER x2, INTEGER y2, INTEGER color);
export void Graph_Flip (void);
export void Graph_FlipBlit (Graph_Bitmap src, Graph_Bitmap dest, INTEGER sx, INTEGER sy, INTEGER sw, INTEGER sh, INTEGER dx, INTEGER dy, BOOLEAN hFlip);
export void Graph_FloodFill (Graph_Bitmap bmp, INTEGER x, INTEGER y, INTEGER color);
export void Graph_GetCharGeometry (Graph_Font font, INTEGER ch, INTEGER *fx, INTEGER *fy, INTEGER *w);
export void Graph_GetDesktopResolution (INTEGER *w, INTEGER *h);
export void Graph_GetError (CHAR *s, INTEGER s__len);
static SDL2_KeyArray Graph_GetKeyArray (void);
export SET Graph_GetMouseButtons (void);
export Graph_Bitmap Graph_GetMousePointer (void);
export void Graph_GetMousePos (INTEGER *x, INTEGER *y);
export INTEGER Graph_GetPixel (Graph_Bitmap bmp, INTEGER x, INTEGER y);
export INTEGER Graph_GetPixelFast (Graph_Bitmap bmp, INTEGER x, INTEGER y);
export void Graph_GetRealMousePos (INTEGER *x, INTEGER *y);
export INTEGER Graph_GetTextWidth (Graph_Font font, CHAR *s, INTEGER s__len);
export INTEGER Graph_GetTicks (void);
export void Graph_HLine (Graph_Bitmap bmp, INTEGER x1, INTEGER y, INTEGER x2, INTEGER color);
static void Graph_HandleMouseButton (SDL2_Event *event);
export Graph_Bitmap Graph_Init (void);
static void Graph_InitMouseData (void);
export BOOLEAN Graph_KeyDown (INTEGER key);
export BOOLEAN Graph_KeyPressed (void);
export void Graph_Line (Graph_Bitmap bmp, INTEGER x1, INTEGER y1, INTEGER x2, INTEGER y2, INTEGER color);
export Graph_Bitmap Graph_LoadBitmap (CHAR *filename, INTEGER filename__len);
static SDL2_Surface Graph_LoadBmp (CHAR *filename, INTEGER filename__len);
export Graph_Font Graph_LoadFont (CHAR *fname, INTEGER fname__len);
export Graph_MonoFont Graph_LoadMonoFont (CHAR *filename, INTEGER filename__len, INTEGER charW, INTEGER charH);
export void Graph_LockBitmap (Graph_Bitmap bmp);
export INTEGER Graph_MakeCol (INTEGER r, INTEGER g, INTEGER b);
export void Graph_MaskedBlit (Graph_Bitmap src, Graph_Bitmap dest, INTEGER sx, INTEGER sy, INTEGER dx, INTEGER dy, INTEGER w, INTEGER h);
export BOOLEAN Graph_MouseOnScreen (void);
static void Graph_NextRND (void);
export void Graph_Pause (void);
export BOOLEAN Graph_PollEvent (Graph_Event *event, void **event__typ);
static void Graph_PumpKeyDown (SDL2_Event *event);
static void Graph_PumpMouseButton (SDL2_Event *event, INTEGER type);
static void Graph_PumpMouseMove (SDL2_Event *event);
static void Graph_PumpQuit (void);
static void Graph_PumpTextEvent (SDL2_Event event);
export void Graph_PutPixel (Graph_Bitmap bmp, INTEGER x, INTEGER y, INTEGER color);
export void Graph_PutPixelFast (Graph_Bitmap bmp, INTEGER x, INTEGER y, INTEGER color);
export void Graph_PutSeed (INTEGER newSeed);
static void Graph_QueueEvent (void);
export INTEGER Graph_Random (INTEGER range);
export void Graph_Randomize (void);
export CHAR Graph_ReadKey (void);
export void Graph_Rect (Graph_Bitmap bmp, INTEGER x1, INTEGER y1, INTEGER x2, INTEGER y2, INTEGER color);
export void Graph_RectFill (Graph_Bitmap bmp, INTEGER x1, INTEGER y1, INTEGER x2, INTEGER y2, INTEGER color);
export void Graph_RepeatFlip (void);
export void Graph_SetAlpha (Graph_Bitmap bmp, INTEGER alpha);
export void Graph_SetClip (Graph_Bitmap bmp, INTEGER x, INTEGER y, INTEGER w, INTEGER h);
export void Graph_SetColorKey (Graph_Bitmap bmp, INTEGER color);
export void Graph_SetColorMod (Graph_Bitmap bmp, INTEGER r, INTEGER g, INTEGER b);
export void Graph_SetFPS (INTEGER fps);
export void Graph_SetMouseFocus (INTEGER x, INTEGER y);
export void Graph_SetMousePointer (Graph_Bitmap bmp, INTEGER x, INTEGER y);
export void Graph_SetRegion (INTEGER x, INTEGER y, INTEGER w, INTEGER h);
export void Graph_SetScreenAlpha (INTEGER alpha);
export void Graph_SetSizeStep (INTEGER w, INTEGER h);
export void Graph_SetStdMousePointer (void);
export void Graph_SetWindowIcon (Graph_Bitmap icon);
export void Graph_SetWindowTitle (CHAR *title, INTEGER title__len);
export void Graph_Settings (INTEGER w, INTEGER h, SET flags);
export BOOLEAN Graph_ShiftPressed (void);
export void Graph_ShowMouse (BOOLEAN show);
export void Graph_StartTextInput (void);
export void Graph_StopTextInput (void);
export void Graph_StretchBlit (Graph_Bitmap src, Graph_Bitmap dest, INTEGER sx, INTEGER sy, INTEGER sw, INTEGER sh, INTEGER dx, INTEGER dy, INTEGER dw, INTEGER dh);
export void Graph_SwitchToFullscreen (void);
export void Graph_SwitchToWindowed (void);
export INTEGER Graph_Time (void);
export void Graph_ToggleFullscreen (void);
export SHORTREAL Graph_Uniform (void);
export void Graph_UnlockBitmap (Graph_Bitmap bmp);
export void Graph_UnsetClip (Graph_Bitmap bmp);
export void Graph_UnsetRegion (void);
static void Graph_UpdateMousePos (SDL2_Event event);
export void Graph_VLine (Graph_Bitmap bmp, INTEGER x, INTEGER y1, INTEGER y2, INTEGER color);
export void Graph_WaitEvents (INTEGER timeout);
export BOOLEAN Graph_WindowShown (void);

#include "SDL2.h0"

/*============================================================================*/

static SDL2_Surface Graph_LoadBmp (CHAR *filename, INTEGER filename__len)
{
  return SDL2_LoadBmpRW(SDL2_RWFromFile(filename, filename__len, (CHAR*)"rb", 3), 1);
}

typedef
  CHAR (*__44)[10240];

void Graph_GetError (CHAR *s, INTEGER s__len)
{
  __44 p = NIL;
  p = (__44)SDL2_GetError();
  __STRCOPYCC(*p, s, __MIN(s__len, 10240), (CHAR*)"Graph", 83199);
}

/*----------------------------------------------------------------------------*/
void Graph_Settings (INTEGER w, INTEGER h, SET flags)
{
  Graph_wantW = w;
  Graph_wantH = h;
  Graph_wantFullscreen = __IN(0, flags);
  Graph_wantBuffer = __IN(1, flags);
  Graph_wantSpread = __IN(2, flags);
  Graph_wantSharpPixels = __IN(3, flags);
  Graph_wantSoftware = __IN(4, flags);
  Graph_wantMouse = __IN(8, flags);
  Graph_showMouse = Graph_wantMouse;
  Graph_wantNet = __IN(10, flags);
  Graph_wantSound = __IN(9, flags);
}

/*----------------------------------------------------------------------------*/
void Graph_SetSizeStep (INTEGER w, INTEGER h)
{
  Graph_sizeStepX = w;
  Graph_sizeStepY = h;
}

/*----------------------------------------------------------------------------*/
void Graph_SetFPS (INTEGER fps)
{
  if (fps <= 0) {
    fps = -1;
  }
  Graph_wantFPS = fps;
}

/*----------------------------------------------------------------------------*/
void Graph_GetDesktopResolution (INTEGER *w, INTEGER *h)
{
  SDL2_DisplayMode mode = {0};
  SDL2_GetDesktopDisplayMode(0, &mode);
  *w = mode.w;
  *h = mode.h;
}

/*----------------------------------------------------------------------------*/
static void Graph_CheckWantedScreenSize (void)
{
  if (Graph_wantW == -1 || Graph_wantH == -1) {
    Graph_GetDesktopResolution(&Graph_wantW, &Graph_wantH);
    if (!Graph_wantFullscreen) {
      Graph_wantW -= 20;
      Graph_wantH -= 50;
    }
  }
}

void Graph_SetRegion (INTEGER x, INTEGER y, INTEGER w, INTEGER h)
{
  Graph_flipRegion.x = x;
  Graph_flipRegion.y = y;
  Graph_flipRegion.w = w;
  Graph_flipRegion.h = h;
}

/*----------------------------------------------------------------------------*/
void Graph_UnsetRegion (void)
{
  Graph_flipRegion.w = -1;
}

/*----------------------------------------------------------------------------*/
void Graph_AddRegion (INTEGER x, INTEGER y, INTEGER w, INTEGER h)
{
  if (Graph_flipRegion.w == -1) {
    Graph_SetRegion(x, y, w, h);
  } else {
    if (x < Graph_flipRegion.x) {
      Graph_flipRegion.x = x;
    }
    if (y < Graph_flipRegion.y) {
      Graph_flipRegion.y = y;
    }
    if (x + w > Graph_flipRegion.x + Graph_flipRegion.w) {
      Graph_flipRegion.w = (w + x) - Graph_flipRegion.x;
    }
    if (y + h > Graph_flipRegion.y + Graph_flipRegion.h) {
      Graph_flipRegion.h = (h + y) - Graph_flipRegion.y;
    }
  }
}

/*----------------------------------------------------------------------------*/
INTEGER Graph_MakeCol (INTEGER r, INTEGER g, INTEGER b)
{
  r = (INTEGER)((SET)r & 0xff);
  g = (INTEGER)((SET)g & 0xff);
  b = (INTEGER)((SET)b & 0xff);
  return __LSHL(__LSHL(65280 + b, 8, INTEGER) + g, 8, INTEGER) + r;
}

/*----------------------------------------------------------------------------*/
void Graph_ColorToRGB (INTEGER color, INTEGER *r, INTEGER *g, INTEGER *b)
{
  *r = (INTEGER)((SET)color & 0xff);
  *g = (INTEGER)((SET)__LSHR(color, 8, INTEGER) & 0xff);
  *b = (INTEGER)((SET)__LSHR(color, 16, INTEGER) & 0xff);
}

/*----------------------------------------------------------------------------*/
void Graph_ColorToRGBA (INTEGER color, INTEGER *r, INTEGER *g, INTEGER *b, INTEGER *a)
{
  *r = (INTEGER)((SET)color & 0xff);
  *g = (INTEGER)((SET)__LSHR(color, 8, INTEGER) & 0xff);
  *b = (INTEGER)((SET)__LSHR(color, 16, INTEGER) & 0xff);
  *a = (INTEGER)((SET)__LSHR(color, 24, INTEGER) & 0xff);
}

/*----------------------------------------------------------------------------*/
INTEGER Graph_BmpCol (Graph_Bitmap bmp, INTEGER r, INTEGER g, INTEGER b)
{
  return SDL2_MapRGB(bmp->surface->format, (SHORTINT)r, (SHORTINT)g, (SHORTINT)b);
}

/*----------------------------------------------------------------------------*/
void Graph_ClearToColor (Graph_Bitmap bmp, INTEGER color)
{
  SDL2_FillRectNil(bmp->surface, color);
}

/*----------------------------------------------------------------------------*/
void Graph_ClearBitmap (Graph_Bitmap bmp)
{
  Graph_ClearToColor(bmp, Graph_MakeCol(0, 0, 0));
}

/*----------------------------------------------------------------------------*/
void Graph_ClearScreenToColor (INTEGER color)
{
  Graph_ClearToColor(Graph_screen, color);
}

/*----------------------------------------------------------------------------*/
void Graph_ClearScreen (void)
{
  Graph_ClearToColor(Graph_screen, Graph_MakeCol(0, 0, 0));
}

/*----------------------------------------------------------------------------*/
void Graph_LockBitmap (Graph_Bitmap bmp)
{
  SDL2_LockSurface(bmp->surface);
}

/*----------------------------------------------------------------------------*/
void Graph_UnlockBitmap (Graph_Bitmap bmp)
{
  SDL2_UnlockSurface(bmp->surface);
}

/*----------------------------------------------------------------------------*/
void Graph_PutPixelFast (Graph_Bitmap bmp, INTEGER x, INTEGER y, INTEGER color)
{
  LONGINT n;
  n = (LONGINT)bmp->surface->pixels;
  n += __ASHL(y * bmp->w + x, 2, INTEGER);
  __PUT(n, color, INTEGER);
}

/*----------------------------------------------------------------------------*/
void Graph_PutPixel (Graph_Bitmap bmp, INTEGER x, INTEGER y, INTEGER color)
{
  LONGINT n;
  if (((x >= 0 && x < bmp->w) && y >= 0) && y < bmp->h) {
    SDL2_LockSurface(bmp->surface);
    n = (LONGINT)bmp->surface->pixels;
    n += __ASHL(y * bmp->w + x, 2, INTEGER);
    __PUT(n, color, INTEGER);
    SDL2_UnlockSurface(bmp->surface);
  }
}

/*----------------------------------------------------------------------------*/
INTEGER Graph_GetPixelFast (Graph_Bitmap bmp, INTEGER x, INTEGER y)
{
  INTEGER color;
  LONGINT n;
  n = (LONGINT)bmp->surface->pixels;
  n += __ASHL(y * bmp->w + x, 2, INTEGER);
  __GET(n, color, INTEGER);
  return color;
}

/*----------------------------------------------------------------------------*/
INTEGER Graph_GetPixel (Graph_Bitmap bmp, INTEGER x, INTEGER y)
{
  INTEGER color;
  LONGINT n;
  if (((x >= 0 && x < bmp->w) && y >= 0) && y < bmp->h) {
    SDL2_LockSurface(bmp->surface);
    n = (LONGINT)bmp->surface->pixels;
    n += __ASHL(y * bmp->w + x, 2, INTEGER);
    __GET(n, color, INTEGER);
    SDL2_UnlockSurface(bmp->surface);
  } else {
    color = 0;
  }
  return color;
}

/*----------------------------------------------------------------------------*/
void Graph_HLine (Graph_Bitmap bmp, INTEGER x1, INTEGER y, INTEGER x2, INTEGER color)
{
  SDL2_Rect rect;
  INTEGER t;
  if (x1 > x2) {
    t = x1;
    x1 = x2;
    x2 = t;
  }
  rect.x = x1;
  rect.y = y;
  rect.w = (x2 - x1) + 1;
  rect.h = 1;
  SDL2_FillRect(bmp->surface, &rect, color);
}

/*----------------------------------------------------------------------------*/
void Graph_VLine (Graph_Bitmap bmp, INTEGER x, INTEGER y1, INTEGER y2, INTEGER color)
{
  SDL2_Rect rect;
  INTEGER t;
  if (y1 > y2) {
    t = y1;
    y1 = y2;
    y2 = t;
  }
  rect.x = x;
  rect.y = y1;
  rect.w = 1;
  rect.h = (y2 - y1) + 1;
  SDL2_FillRect(bmp->surface, &rect, color);
}

/*----------------------------------------------------------------------------*/
void Graph_Line (Graph_Bitmap bmp, INTEGER x1, INTEGER y1, INTEGER x2, INTEGER y2, INTEGER color)
{
  INTEGER x, y, i, dx, dy, sx, sy, e;
  BOOLEAN vert;
  INTEGER _for__61;
  if (x1 == x2) {
    Graph_VLine(bmp, x1, y1, y2, color);
  } else if (y1 == y2) {
    Graph_HLine(bmp, x1, y1, x2, color);
  } else {
    SDL2_LockSurface(bmp->surface);
    dx = __ABS(x1 - x2);
    dy = __ABS(y1 - y2);
    if (x2 > x1) {
      sx = 1;
    } else {
      sx = -1;
    }
    if (y2 > y1) {
      sy = 1;
    } else {
      sy = -1;
    }
    x = x1;
    y = y1;
    vert = dy > dx;
    if (vert) {
      i = dx;
      dx = dy;
      dy = i;
    }
    e = __ASHL(dy, 1, INTEGER) - dx;
    _for__61 = dx;
    i = 0;
    while (i <= _for__61) {
      if (((x >= 0 && x < bmp->w) && y >= 0) && y < bmp->h) {
        Graph_PutPixelFast(bmp, x, y, color);
      }
      if (e >= 0) {
        if (vert) {
          x += sx;
        } else {
          y += sy;
        }
        e -= __ASHL(dx, 1, INTEGER);
      }
      if (vert) {
        y += sy;
      } else {
        x += sx;
      }
      e += __ASHL(dy, 1, INTEGER);
      i += 1;
    }
    SDL2_UnlockSurface(bmp->surface);
  }
}

/*----------------------------------------------------------------------------*/
void Graph_FastLine (Graph_Bitmap bmp, INTEGER x1, INTEGER y1, INTEGER x2, INTEGER y2, INTEGER color)
{
}

/*----------------------------------------------------------------------------*/
void Graph_Rect (Graph_Bitmap bmp, INTEGER x1, INTEGER y1, INTEGER x2, INTEGER y2, INTEGER color)
{
  SDL2_Rect rect;
  rect.x = x1;
  rect.y = y1;
  rect.w = 1;
  rect.h = (y2 - y1) + 1;
  SDL2_FillRect(bmp->surface, &rect, color);
  rect.x = x2;
  SDL2_FillRect(bmp->surface, &rect, color);
  rect.x = x1;
  rect.w = (x2 - x1) + 1;
  rect.h = 1;
  SDL2_FillRect(bmp->surface, &rect, color);
  rect.y = y2;
  SDL2_FillRect(bmp->surface, &rect, color);
}

/*----------------------------------------------------------------------------*/
void Graph_RectFill (Graph_Bitmap bmp, INTEGER x1, INTEGER y1, INTEGER x2, INTEGER y2, INTEGER color)
{
  SDL2_Rect rect;
  rect.x = x1;
  rect.y = y1;
  rect.w = (x2 - x1) + 1;
  rect.h = (y2 - y1) + 1;
  SDL2_FillRect(bmp->surface, &rect, color);
}

/*----------------------------------------------------------------------------*/
void Graph_Circle (Graph_Bitmap bmp, INTEGER x, INTEGER y, INTEGER r, INTEGER color)
{
}

/*----------------------------------------------------------------------------*/
void Graph_CircleFill (Graph_Bitmap bmp, INTEGER x, INTEGER y, INTEGER r, INTEGER color)
{
}

/*----------------------------------------------------------------------------*/
void Graph_Ellipse (Graph_Bitmap bmp, INTEGER x, INTEGER y, INTEGER rx, INTEGER ry, INTEGER color)
{
}

/*----------------------------------------------------------------------------*/
void Graph_EllipseFill (Graph_Bitmap bmp, INTEGER x, INTEGER y, INTEGER rx, INTEGER ry, INTEGER color)
{
}

/*----------------------------------------------------------------------------*/
void Graph_FloodFill (Graph_Bitmap bmp, INTEGER x, INTEGER y, INTEGER color)
{
}

/*----------------------------------------------------------------------------*/
void Graph_Bitmap_Finalize (Graph_Bitmap bmp)
{
}

/*----------------------------------------------------------------------------*/
Graph_Bitmap Graph_CreateBitmap (INTEGER w, INTEGER h)
{
  Graph_Bitmap bmp = NIL;
  CHAR s[2560];
  __NEW(bmp, Graph_BitmapDesc);
  bmp->surface = SDL2_CreateRGBSurface(0, w, h, 32, 255, 65280, 16711680, -16777216);
  if (bmp->surface == NIL) {
    Graph_GetError((void*)s, 2560);
    Out_String((void*)s, 2560);
    Out_Ln();
  }
  bmp->w = w;
  bmp->h = h;
  return bmp;
}

/*----------------------------------------------------------------------------*/
void Graph_DestroyBitmap (Graph_Bitmap bmp)
{
  SDL2_FreeSurface(bmp->surface);
}

/*----------------------------------------------------------------------------*/
Graph_Bitmap Graph_LoadBitmap (CHAR *filename, INTEGER filename__len)
{
  Graph_Bitmap bmp = NIL;
  __NEW(bmp, Graph_BitmapDesc);
  bmp->surface = SDL2_ImgLoad(filename, filename__len);
  if (bmp->surface == NIL) {
    bmp = NIL;
  } else {
    bmp->w = bmp->surface->w;
    bmp->h = bmp->surface->h;
  }
  return bmp;
}

/*----------------------------------------------------------------------------*/
void Graph_Blit (Graph_Bitmap src, Graph_Bitmap dest, INTEGER sx, INTEGER sy, INTEGER sw, INTEGER sh, INTEGER dx, INTEGER dy)
{
  SDL2_Rect a, b;
  a.x = sx;
  a.y = sy;
  a.w = sw;
  a.h = sh;
  b.x = dx;
  b.y = dy;
  SDL2_BlitSurface(src->surface, &a, dest->surface, &b);
}

/*----------------------------------------------------------------------------*/
void Graph_FlipBlit (Graph_Bitmap src, Graph_Bitmap dest, INTEGER sx, INTEGER sy, INTEGER sw, INTEGER sh, INTEGER dx, INTEGER dy, BOOLEAN hFlip)
{
  INTEGER x, y, sx0, c1, c2, r1, r2, g1, g2, b1, b2, a1, a2, _for__39, _for__38;
  if (!hFlip) {
    Graph_Blit(src, dest, sx, sy, sw, sh, dx, dy);
  } else {
    if (sx < 0) {
      sw -= -sx;
      dx += -sx;
      sx = 0;
    } else if ((sx + sw) - 1 >= src->w) {
      sw -= ((sx + sw) - 1) - src->w;
    } else if ((dx + sw) - 1 >= dest->w) {
      sw -= ((dx + sw) - 1) - dest->w;
    }
    if (sy < 0) {
      sh -= -sy;
      dy += -sy;
      sy = 0;
    } else if ((sy + sh) - 1 >= src->h) {
      sh -= ((sy + sh) - 1) - src->h;
    } else if ((dy + sh) - 1 >= dest->h) {
      sh -= ((dy + sh) - 1) - dest->h;
    }
    Graph_LockBitmap(src);
    Graph_LockBitmap(dest);
    sx0 = (sx + sw) - 1;
    _for__39 = (dy + sh) - 1;
    y = dy;
    while (y <= _for__39) {
      sx = sx0;
      _for__38 = (dx + sw) - 1;
      x = dx;
      while (x <= _for__38) {
        c1 = Graph_GetPixelFast(src, sx, sy);
        Graph_ColorToRGBA(c1, &r1, &g1, &b1, &a1);
        if (a1 != 0) {
          c2 = Graph_GetPixelFast(dest, x, y);
          Graph_ColorToRGBA(c2, &r2, &g2, &b2, &a2);
          if (a1 != 255) {
            c1 = Graph_MakeCol(__ASHR(r1 * a1 + r2 * (255 - a1), 8, INTEGER), __ASHR(g1 * a1 + g2 * (255 - g1), 8, INTEGER), __ASHR(b1 * a1 + b2 * (255 - b1), 8, INTEGER));
          }
          Graph_PutPixelFast(dest, x, y, c1);
        }
        sx -= 1;
        x += 1;
      }
      sy += 1;
      y += 1;
    }
    Graph_UnlockBitmap(dest);
    Graph_UnlockBitmap(src);
  }
}

/*----------------------------------------------------------------------------*/
void Graph_BlitWhole (Graph_Bitmap src, Graph_Bitmap dest, INTEGER x, INTEGER y)
{
  SDL2_Rect b;
  b.x = x;
  b.y = y;
  SDL2_BlitSurfaceNil(src->surface, dest->surface, &b);
}

/*----------------------------------------------------------------------------*/
void Graph_StretchBlit (Graph_Bitmap src, Graph_Bitmap dest, INTEGER sx, INTEGER sy, INTEGER sw, INTEGER sh, INTEGER dx, INTEGER dy, INTEGER dw, INTEGER dh)
{
  SDL2_Rect a, b;
  a.x = sx;
  a.y = sy;
  a.w = sw;
  a.h = sh;
  b.x = dx;
  b.y = dy;
  b.w = dw;
  b.h = dh;
  SDL2_BlitScaled(src->surface, &a, dest->surface, &b);
}

/*----------------------------------------------------------------------------*/
void Graph_SetScreenAlpha (INTEGER alpha)
{
  Graph_screenAlpha = alpha;
}

/*----------------------------------------------------------------------------*/
void Graph_SetAlpha (Graph_Bitmap bmp, INTEGER alpha)
{
  if (SDL2_SetSurfaceAlphaMod(bmp->surface, (CHAR)alpha) == 0) {
  }
}

/*----------------------------------------------------------------------------*/
void Graph_SetClip (Graph_Bitmap bmp, INTEGER x, INTEGER y, INTEGER w, INTEGER h)
{
  SDL2_Rect r;
  r.x = x;
  r.y = y;
  r.w = w;
  r.h = h;
  if (SDL2_SetClipRect(bmp->surface, &r) == 0) {
  }
}

/*----------------------------------------------------------------------------*/
void Graph_UnsetClip (Graph_Bitmap bmp)
{
  if (SDL2_SetClipRectNil(bmp->surface) == 0) {
  }
}

/*----------------------------------------------------------------------------*/
void Graph_MaskedBlit (Graph_Bitmap src, Graph_Bitmap dest, INTEGER sx, INTEGER sy, INTEGER dx, INTEGER dy, INTEGER w, INTEGER h)
{
}

/*----------------------------------------------------------------------------*/
void Graph_DrawSpriteEx (Graph_Bitmap dest, Graph_Bitmap sprite, INTEGER x, INTEGER y, INTEGER mode, SET flip)
{
}

/*----------------------------------------------------------------------------*/
void Graph_DrawCharacterEx (Graph_Bitmap dest, Graph_Bitmap sprite, INTEGER x, INTEGER y, INTEGER color, INTEGER bg)
{
}

/*----------------------------------------------------------------------------*/
void Graph_SetColorKey (Graph_Bitmap bmp, INTEGER color)
{
  SDL2_SetColorKey(bmp->surface, 1, color);
}

/*----------------------------------------------------------------------------*/
void Graph_SetColorMod (Graph_Bitmap bmp, INTEGER r, INTEGER g, INTEGER b)
{
  SDL2_SetSurfaceColorMod(bmp->surface, r, g, b);
}

/*----------------------------------------------------------------------------*/
Graph_MonoFont Graph_LoadMonoFont (CHAR *filename, INTEGER filename__len, INTEGER charW, INTEGER charH)
{
  Graph_Bitmap bmp = NIL;
  Graph_MonoFont font = NIL;
  INTEGER x, y, sx, sy, tmp, _for__67, _for__66;
  bmp = Graph_LoadBitmap((void*)filename, filename__len);
  if (bmp == NIL) {
    font = NIL;
  } else {
    bmp->surface = SDL2_ConvertSurface(bmp->surface, Graph_screen->surface->format, 0);
    Graph_SetColorKey(bmp, Graph_BmpCol(bmp, 0, 0, 0));
    __NEW(font, Graph_MonoFontDesc);
    font->bmp = bmp;
    font->charW = charW;
    font->charH = charH;
    font->charsInRow = __DIVF(font->bmp->w, charW);
    font->charRows = __DIVF(font->bmp->h, charH);
    font->sprites = __NEWARR(NIL, 16, 4, 2, 2, (SYSTEM_ARRLEN)font->charRows, (SYSTEM_ARRLEN)font->charsInRow);
    sy = 0;
    _for__67 = font->charRows - 1;
    y = 0;
    while (y <= _for__67) {
      sx = 0;
      _for__66 = font->charsInRow - 1;
      x = 0;
      while (x <= _for__66) {
        (font->sprites->data)[__X(x, font->sprites->len[1], (CHAR*)"Graph", 193570) + font->sprites->len[1] * (__X(y, font->sprites->len[0], (CHAR*)"Graph", 193570))].x = sx;
        (font->sprites->data)[__X(x, font->sprites->len[1], (CHAR*)"Graph", 193826) + font->sprites->len[1] * (__X(y, font->sprites->len[0], (CHAR*)"Graph", 193826))].y = sy;
        (font->sprites->data)[__X(x, font->sprites->len[1], (CHAR*)"Graph", 194085) + font->sprites->len[1] * (__X(y, font->sprites->len[0], (CHAR*)"Graph", 194085))].w = charW;
        (font->sprites->data)[__X(x, font->sprites->len[1], (CHAR*)"Graph", 194341) + font->sprites->len[1] * (__X(y, font->sprites->len[0], (CHAR*)"Graph", 194341))].h = charH;
        sx += charW;
        x += 1;
      }
      sy += charH;
      y += 1;
    }
  }
  return font;
}

/*----------------------------------------------------------------------------*/
void Graph_DrawCharacter (Graph_Bitmap dest, Graph_MonoFont font, INTEGER x, INTEGER y, CHAR ch, INTEGER fg)
{
  INTEGER fx, fy, r, g, b;
  SDL2_Rect dstRect;
  dstRect.x = x;
  dstRect.y = y;
  fx = __MODF((INTEGER)ch, font->charsInRow);
  fy = __DIVF((INTEGER)ch, font->charsInRow);
  Graph_ColorToRGB(fg, &r, &g, &b);
  SDL2_SetSurfaceColorMod(font->bmp->surface, r, g, b);
  SDL2_BlitSurface(font->bmp->surface, &(font->sprites->data)[__X(fx, font->sprites->len[1], (CHAR*)"Graph", 199423) + font->sprites->len[1] * (__X(fy, font->sprites->len[0], (CHAR*)"Graph", 199423))], Graph_screen->surface, &dstRect);
}

/*----------------------------------------------------------------------------*/
void Graph_DrawString (Graph_Bitmap dest, Graph_MonoFont font, INTEGER x, INTEGER y, CHAR *s, INTEGER s__len, INTEGER fg)
{
  INTEGER i, cx;
  i = 0;
  cx = x;
  while (s[__X(i, s__len, (CHAR*)"Graph", 201251)] != 0x00 && cx < dest->w) {
    Graph_DrawCharacter(dest, font, cx, y, s[__X(i, s__len, (CHAR*)"Graph", 201518)], fg);
    i += 1;
    cx += font->charW;
  }
}

/*----------------------------------------------------------------------------*/
Graph_Font Graph_LoadFont (CHAR *fname, INTEGER fname__len)
{
  Texts_Text T = NIL;
  Texts_Scanner S = {0};
  INTEGER i;
  CHAR s[512];
  Graph_Font f = NIL;
  __NEW(f, Graph_FontDesc);
  __STRCOPYCC(fname, s, __MIN(512, fname__len), (CHAR*)"Graph", 205069);
  Strings_Append((CHAR*)".png", 5, (void*)s, 512);
  f->bmp = Graph_LoadBitmap((void*)s, 512);
  if (f->bmp == NIL) {
    f = NIL;
  } else {
    __STRCOPYCC(fname, s, __MIN(512, fname__len), (CHAR*)"Graph", 206095);
    Strings_Append((CHAR*)".dat", 5, (void*)s, 512);
    __NEW(T, Texts_TextDesc);
    Texts_Open(T, (void*)s, 512);
    Texts_OpenScanner(&S, Texts_Scanner__typ, T, 0);
    Texts_Scan(&S, Texts_Scanner__typ);
    if (S.eot) {
      f = NIL;
    } else {
      if ((INTEGER)S.class == 3) {
        f->h = (SHORTINT)S.i;
      } else {
        f->h = 0;
      }
      Texts_Scan(&S, Texts_Scanner__typ);
      i = 0;
      while (!S.eot && (INTEGER)S.class == 3) {
        f->geo[__X(i, 512, (CHAR*)"Graph", 208416)].w = (SHORTINT)S.i;
        Texts_Scan(&S, Texts_Scanner__typ);
        f->geo[__X(i, 512, (CHAR*)"Graph", 208672)].x = (SHORTINT)S.i;
        Texts_Scan(&S, Texts_Scanner__typ);
        f->geo[__X(i, 512, (CHAR*)"Graph", 208928)].y = (SHORTINT)S.i;
        Texts_Scan(&S, Texts_Scanner__typ);
        i += 1;
      }
      f->geoCount = i;
    }
  }
  return f;
}

/*----------------------------------------------------------------------------*/
void Graph_GetCharGeometry (Graph_Font font, INTEGER ch, INTEGER *fx, INTEGER *fy, INTEGER *w)
{
  INTEGER i;
  if (32 <= ch && ch <= 127) {
    i = ch - 32;
  } else if (1040 <= ch && ch <= 1103) {
    i = (ch - 1040) + 95;
  } else if (ch == 1025) {
    i = 159;
  } else if (ch == 1105) {
    i = 160;
  } else {
    i = font->geoCount;
  }
  if (i >= font->geoCount) {
    i = 31;
  }
  *w = font->geo[__X(i, 512, (CHAR*)"Graph", 213525)].w;
  *fx = font->geo[__X(i, 512, (CHAR*)"Graph", 213781)].x;
  *fy = font->geo[__X(i, 512, (CHAR*)"Graph", 214271)].y;
}

/*----------------------------------------------------------------------------*/
INTEGER Graph_GetTextWidth (Graph_Font font, CHAR *s, INTEGER s__len)
{
  INTEGER i, w, tw, maxTw, fx, fy;
  CHAR c1, c2;
  INTEGER ch;
  maxTw = 0;
  tw = 0;
  i = 0;
  if (font != NIL) {
    while (i < s__len - 1 && s[__X(i, s__len, (CHAR*)"Graph", 216616)] != 0x00) {
      c1 = s[__X(i, s__len, (CHAR*)"Graph", 216848)];
      c2 = s[__X(i + 1, s__len, (CHAR*)"Graph", 216864)];
      if (c1 < 0x80) {
        ch = (SHORTINT)c1;
        i += 1;
      } else {
        ch = __ASHL(__MASK((INTEGER)c1, -32), 6, INTEGER) + __MASK((INTEGER)c2, -64);
        i += 2;
      }
      if (ch == 10) {
        if (tw > maxTw) {
          maxTw = tw;
        }
        tw = 0;
      } else {
        Graph_GetCharGeometry(font, ch, &fx, &fy, &w);
        tw += w;
      }
    }
  }
  if (tw > maxTw) {
    maxTw = tw;
  }
  return maxTw;
}

/*----------------------------------------------------------------------------*/
void Graph_DrawChar (Graph_Bitmap dest, Graph_Font font, INTEGER x, INTEGER y, INTEGER ch, INTEGER color, INTEGER *w)
{
  INTEGER r, g, b, fx, fy;
  if (font != NIL) {
    Graph_GetCharGeometry(font, ch, &fx, &fy, w);
    if (ch != 32) {
      Graph_ColorToRGB(color, &r, &g, &b);
      Graph_SetColorMod(font->bmp, r, g, b);
      Graph_Blit(font->bmp, dest, fx, fy, *w, font->h, x, y);
    }
  }
}

/*----------------------------------------------------------------------------*/
void Graph_DrawText (Graph_Bitmap dest, Graph_Font font, INTEGER x, INTEGER y, CHAR *s, INTEGER s__len, INTEGER color)
{
  INTEGER x0, i, w;
  CHAR c1, c2;
  INTEGER ch;
  if (font != NIL) {
    x0 = x;
    i = 0;
    while (i < s__len - 1 && s[__X(i, s__len, (CHAR*)"Graph", 226600)] != 0x00) {
      c1 = s[__X(i, s__len, (CHAR*)"Graph", 226832)];
      c2 = s[__X(i + 1, s__len, (CHAR*)"Graph", 226848)];
      if (c1 < 0x80) {
        ch = (SHORTINT)c1;
        i += 1;
      } else {
        ch = __ASHL(__MASK((INTEGER)c1, -32), 6, INTEGER) + __MASK((INTEGER)c2, -64);
        i += 2;
      }
      if (ch == 10) {
        y += font->h;
        x = x0;
      } else {
        Graph_DrawChar(dest, font, x, y, ch, color, &w);
        x += w;
      }
    }
  }
}

/*----------------------------------------------------------------------------*/
void Graph_StartTextInput (void)
{
  SDL2_StartTextInput();
}

/*----------------------------------------------------------------------------*/
void Graph_StopTextInput (void)
{
  SDL2_StopTextInput();
}

/*----------------------------------------------------------------------------*/
static void Graph_QueueEvent (void)
{
  Graph_events.len += 1;
  Graph_events.last += 1;
  if (Graph_events.last == 256) {
    Graph_events.last = 0;
  }
}

static void Graph_PumpKeyDown (SDL2_Event *event)
{
  SDL2_KeyboardEvent e = NIL;
  INTEGER n;
  SET mod;
  if (Graph_events.len < 256) {
    e = (SDL2_KeyboardEvent)((SYSTEM_ADRINT)event);
    n = e->keysym.mod;
    mod = (SET)n;
    Graph_QueueEvent();
    Graph_events.buf[__X(Graph_events.last, 256, (CHAR*)"Graph", 235819)].type = 3;
    Graph_events.buf[__X(Graph_events.last, 256, (CHAR*)"Graph", 236089)].key.code = e->keysym.scancode;
    Graph_events.buf[__X(Graph_events.last, 256, (CHAR*)"Graph", 236339)].key.sym = e->keysym.sym;
    Graph_events.buf[__X(Graph_events.last, 256, (CHAR*)"Graph", 236586)].key.mod = mod;
    Graph_events.buf[__X(Graph_events.last, 256, (CHAR*)"Graph", 236854)].key.repeat = (INTEGER)e->repeat != 0;
    Graph_keyPressed += 1;
  }
}

static void Graph_PumpTextEvent (SDL2_Event event)
{
  INTEGER sym;
  SDL2_TextInputEvent e = NIL;
  if (Graph_events.len < 256) {
    e = (SDL2_TextInputEvent)((SYSTEM_ADRINT)&event);
    if (e->text[1] == 0x00) {
      sym = (SHORTINT)e->text[0];
    } else {
      sym = (SHORTINT)e->text[1];
      if (e->text[0] == 0xd0 || e->text[0] == 0xd1) {
        if (e->text[0] == 0xd0) {
          sym -= 144;
        } else {
          sym -= 80;
        }
        if (sym == 65) {
          sym = 241;
        } else if (sym == -15) {
          sym = 240;
        } else if (sym < 48) {
          sym += 128;
        } else {
          sym += 176;
        }
      }
    }
    Graph_QueueEvent();
    Graph_events.buf[__X(Graph_events.last, 256, (CHAR*)"Graph", 244269)].type = 5;
    Graph_events.buf[__X(Graph_events.last, 256, (CHAR*)"Graph", 244522)].key.sym = sym;
    __STRCOPYCC(e->text, Graph_events.buf[__X(Graph_events.last, 256, (CHAR*)"Graph", 244991)].s, 32, (CHAR*)"Graph", 244991);
  }
}

static void Graph_UpdateMousePos (SDL2_Event event)
{
  SDL2_MouseMotionEvent e = NIL;
  INTEGER newX, newY;
  e = (SDL2_MouseMotionEvent)((SYSTEM_ADRINT)&event);
  newX = e->x;
  newY = e->y;
  if (newX < 0) {
    newX = 0;
  } else if (newX >= Graph_screen->w) {
    newX = Graph_screen->w - 1;
  }
  if (newY < 0) {
    newY = 0;
  } else if (newY >= Graph_screen->h) {
    newY = Graph_screen->h - 1;
  }
  if (newX != Graph_mouseX || newY != Graph_mouseY) {
    Graph_mouseX = newX;
    Graph_mouseY = newY;
    Graph_needRedrawMouse = 1;
  }
}

static SDL2_KeyArray Graph_GetKeyArray (void)
{
  return (SDL2_KeyArray)SDL2_GetKeyboardStateNil();
}

BOOLEAN Graph_KeyDown (INTEGER key)
{
  SDL2_KeyArray keys = NIL;
  keys = Graph_GetKeyArray();
  return (*keys)[__X(key, 1024, (CHAR*)"Graph", 252671)];
}

/*----------------------------------------------------------------------------*/
BOOLEAN Graph_AltPressed (void)
{
  SDL2_KeyArray keys = NIL;
  keys = Graph_GetKeyArray();
  return (*keys)[226] || (*keys)[230];
}

/*----------------------------------------------------------------------------*/
BOOLEAN Graph_ShiftPressed (void)
{
  SDL2_KeyArray keys = NIL;
  keys = Graph_GetKeyArray();
  return (*keys)[225] || (*keys)[229];
}

/*----------------------------------------------------------------------------*/
BOOLEAN Graph_CtrlPressed (void)
{
  SDL2_KeyArray keys = NIL;
  keys = Graph_GetKeyArray();
  return (*keys)[224] || (*keys)[228];
}

/*----------------------------------------------------------------------------*/
BOOLEAN Graph_MouseOnScreen (void)
{
  SET flags;
  flags = SDL2_GetWindowFlags(Graph_window);
  return __IN(10, flags);
}

/*----------------------------------------------------------------------------*/
void Graph_ShowMouse (BOOLEAN show)
{
  Graph_showMouse = show;
}

/*----------------------------------------------------------------------------*/
void Graph_GetRealMousePos (INTEGER *x, INTEGER *y)
{
  if (SDL2_GetMouseState(x, y) == 0) {
  }
}

/*----------------------------------------------------------------------------*/
void Graph_GetMousePos (INTEGER *x, INTEGER *y)
{
  *x = Graph_mouseX;
  *y = Graph_mouseY;
}

/*----------------------------------------------------------------------------*/
SET Graph_GetMouseButtons (void)
{
  INTEGER x, y;
  return (SET)SDL2_GetMouseState(&x, &y);
}

/*----------------------------------------------------------------------------*/
void Graph_CreateStdMousePointer (void)
{
  Graph_Bitmap b = NIL;
  INTEGER fg, bg;
  b = Graph_CreateBitmap(12, 19);
  bg = Graph_MakeCol(255, 0, 255);
  fg = Graph_MakeCol(0, 0, 0);
  Graph_ClearToColor(b, bg);
  Graph_SetColorKey(b, bg);
  Graph_Line(b, 0, 0, 10, 10, fg);
  Graph_Line(b, 0, 0, 0, 14, fg);
  Graph_Line(b, 0, 14, 3, 11, fg);
  Graph_Line(b, 10, 10, 6, 10, fg);
  Graph_Line(b, 4, 12, 6, 17, fg);
  Graph_Line(b, 6, 11, 9, 17, fg);
  Graph_Line(b, 7, 18, 8, 18, fg);
  bg = Graph_MakeCol(255, 255, 255);
  Graph_VLine(b, 1, 2, 12, bg);
  Graph_VLine(b, 2, 3, 11, bg);
  Graph_VLine(b, 3, 4, 10, bg);
  Graph_VLine(b, 4, 5, 11, bg);
  Graph_VLine(b, 5, 6, 13, bg);
  Graph_VLine(b, 6, 7, 9, bg);
  Graph_VLine(b, 7, 8, 9, bg);
  Graph_VLine(b, 8, 9, 9, bg);
  Graph_VLine(b, 6, 12, 15, bg);
  Graph_VLine(b, 7, 14, 17, bg);
  Graph_VLine(b, 8, 16, 17, bg);
  Graph_stdMousePointer = b;
}

/*----------------------------------------------------------------------------*/
void Graph_SetMouseFocus (INTEGER x, INTEGER y)
{
  Graph_mouseFocusX = x;
  Graph_mouseFocusY = y;
  Graph_needRedrawMouse = 1;
}

/*----------------------------------------------------------------------------*/
void Graph_SetMousePointer (Graph_Bitmap bmp, INTEGER x, INTEGER y)
{
  if (bmp == NIL) {
    Graph_mousePointer = Graph_stdMousePointer;
    x = 0;
    y = 0;
  } else {
    Graph_mousePointer = bmp;
  }
  Graph_SetMouseFocus(x, y);
  Graph_underMouse = Graph_CreateBitmap(Graph_mousePointer->w, Graph_mousePointer->h);
  Graph_needRedrawMouse = 1;
}

/*----------------------------------------------------------------------------*/
Graph_Bitmap Graph_GetMousePointer (void)
{
  return Graph_mousePointer;
}

/*----------------------------------------------------------------------------*/
void Graph_SetStdMousePointer (void)
{
  Graph_SetMousePointer(Graph_stdMousePointer, 0, 0);
}

/*----------------------------------------------------------------------------*/
static void Graph_InitMouseData (void)
{
  Graph_CreateStdMousePointer();
  Graph_SetStdMousePointer();
  Graph_mouseX = -1;
}

void Graph_SetWindowTitle (CHAR *title, INTEGER title__len)
{
  SDL2_SetWindowTitle(Graph_window, title, title__len);
}

/*----------------------------------------------------------------------------*/
void Graph_SetWindowIcon (Graph_Bitmap icon)
{
  SDL2_SetWindowIcon(Graph_window, icon->surface);
}

/*----------------------------------------------------------------------------*/
void Graph_SwitchToWindowed (void)
{
  if (Graph_wantFullscreen) {
    SDL2_SetWindowSize(Graph_window, Graph_screen->w, Graph_screen->h);
    if (SDL2_SetWindowFullscreen(Graph_window, 0x0) == 0) {
      Graph_wantFullscreen = 0;
    }
  }
}

/*----------------------------------------------------------------------------*/
void Graph_SwitchToFullscreen (void)
{
  if (!Graph_wantFullscreen) {
    if (SDL2_SetWindowFullscreen(Graph_window, 0x1001) == 0) {
      Graph_wantFullscreen = 1;
    }
  }
}

/*----------------------------------------------------------------------------*/
void Graph_ToggleFullscreen (void)
{
  if (Graph_wantFullscreen) {
    Graph_SwitchToWindowed();
  } else {
    Graph_SwitchToFullscreen();
  }
}

/*----------------------------------------------------------------------------*/
void Graph_Delay (INTEGER n)
{
  SDL2_Delay(n);
}

/*----------------------------------------------------------------------------*/
static void Graph_HandleMouseButton (SDL2_Event *event)
{
  SDL2_MouseButtonEvent e = NIL;
}

static void Graph_PumpQuit (void)
{
  if (Graph_events.len < 256) {
    Graph_QueueEvent();
    Graph_events.buf[__X(Graph_events.last, 256, (CHAR*)"Graph", 293119)].type = 1;
  }
}

static void Graph_PumpMouseMove (SDL2_Event *event)
{
  SDL2_MouseMotionEvent e = NIL;
  INTEGER newX, newY;
  e = (SDL2_MouseMotionEvent)((SYSTEM_ADRINT)event);
  newX = e->x;
  newY = e->y;
  if (newX < 0) {
    newX = 0;
  } else if (newX >= Graph_screen->w) {
    newX = Graph_screen->w - 1;
  }
  if (newY < 0) {
    newY = 0;
  } else if (newY >= Graph_screen->h) {
    newY = Graph_screen->h - 1;
  }
  if (newX != Graph_mouseX || newY != Graph_mouseY) {
    Graph_mouseX = newX;
    Graph_mouseY = newY;
    Graph_needRedrawMouse = 1;
    if (Graph_events.len < 256) {
      Graph_QueueEvent();
      Graph_events.buf[__X(Graph_events.last, 256, (CHAR*)"Graph", 298287)].type = 6;
      Graph_events.buf[__X(Graph_events.last, 256, (CHAR*)"Graph", 298535)].x = newX;
      Graph_events.buf[__X(Graph_events.last, 256, (CHAR*)"Graph", 298791)].y = newY;
      Graph_events.buf[__X(Graph_events.last, 256, (CHAR*)"Graph", 299052)].xRel = e->xRel;
      Graph_events.buf[__X(Graph_events.last, 256, (CHAR*)"Graph", 299308)].yRel = e->yRel;
      Graph_events.buf[__X(Graph_events.last, 256, (CHAR*)"Graph", 299775)].buttons = (SET)e->state;
    }
  }
}

static void Graph_PumpMouseButton (SDL2_Event *event, INTEGER type)
{
  SDL2_MouseButtonEvent e = NIL;
  e = (SDL2_MouseButtonEvent)((SYSTEM_ADRINT)event);
  if (Graph_events.len < 256) {
    Graph_QueueEvent();
    Graph_events.buf[__X(Graph_events.last, 256, (CHAR*)"Graph", 302376)].type = type;
    Graph_events.buf[__X(Graph_events.last, 256, (CHAR*)"Graph", 302642)].button = (INTEGER)e->button - 1;
    Graph_events.buf[__X(Graph_events.last, 256, (CHAR*)"Graph", 302895)].down = (INTEGER)e->state != 0;
    if (e->x < 0) {
      e->x = 0;
    } else if (e->x >= Graph_screen->w) {
      e->x = Graph_screen->w - 1;
    }
    if (e->y < 0) {
      e->y = 0;
    } else if (e->y >= Graph_screen->h) {
      e->y = Graph_screen->h - 1;
    }
    Graph_events.buf[__X(Graph_events.last, 256, (CHAR*)"Graph", 304676)].x = e->x;
    Graph_events.buf[__X(Graph_events.last, 256, (CHAR*)"Graph", 304932)].y = e->y;
    Graph_events.buf[__X(Graph_events.last, 256, (CHAR*)"Graph", 305407)].key.mod = SDL2_GetModState();
  }
}

void Graph_RepeatFlip (void)
{
  if (Graph_screenTexture != NIL) {
    SDL2_SetRenderDrawColor(Graph_renderer, 0, 0, 0, 255);
    SDL2_RenderClear(Graph_renderer);
    SDL2_RenderCopyNil(Graph_renderer, Graph_screenTexture);
    SDL2_RenderPresent(Graph_renderer);
  }
}

/*----------------------------------------------------------------------------*/
void Graph_WaitEvents (INTEGER timeout)
{
  SDL2_Event event;
  INTEGER n;
  n = SDL2_PollEvent(&event);
  if (n != 0 || Graph_events.len == 0) {
    if (n == 0) {
      if (timeout > 0) {
        n = SDL2_WaitEventTimeout(&event, timeout);
      } else if (timeout < 0) {
        n = SDL2_WaitEvent(&event);
      }
    }
    if (n != 0) {
      do {
        if (event.type == 1024) {
          Graph_PumpMouseMove(&event);
        } else if (event.type == 1025) {
          Graph_PumpMouseButton(&event, 7);
        } else if (event.type == 1026) {
          Graph_PumpMouseButton(&event, 8);
        } else if (event.type == 768) {
          Graph_PumpKeyDown(&event);
        } else if (event.type == 771) {
          Graph_PumpTextEvent(event);
        } else if (event.type == 256) {
          Graph_PumpQuit();
        }
      } while (!(SDL2_PollEvent(&event) == 0));
    }
  }
}

/*----------------------------------------------------------------------------*/
BOOLEAN Graph_PollEvent (Graph_Event *event, void **event__typ)
{
  BOOLEAN hasEvent;
  if (Graph_events.len > 0) {
    __GUARDEQR(event, event__typ, Graph_Event) = Graph_events.buf[__X(Graph_events.first, 256, (CHAR*)"Graph", 317477)];
    if ((*event).type == 3) {
      Graph_keyPressed -= 1;
    }
    Graph_events.len -= 1;
    Graph_events.first += 1;
    if (Graph_events.first == 256) {
      Graph_events.first = 0;
    }
    hasEvent = 1;
  } else {
    hasEvent = 0;
  }
  return hasEvent;
}

/*----------------------------------------------------------------------------*/
BOOLEAN Graph_KeyPressed (void)
{
  Graph_WaitEvents(0);
  return Graph_keyPressed > 0;
}

/*----------------------------------------------------------------------------*/
CHAR Graph_ReadKey (void)
{
  Graph_Event event;
  BOOLEAN done;
  CHAR ch;
  done = 0;
  do {
    Graph_WaitEvents(-1);
    while (Graph_PollEvent(&event, Graph_Event__typ)) {
      switch (event.type) {
        case 3: 
          ch = (CHAR)event.key.sym;
          done = 1;
          break;
        case 1: 
          ch = 0x00;
          done = 1;
          break;
        default: 
          break;
      }
    }
  } while (!done);
  return ch;
}

/*----------------------------------------------------------------------------*/
void Graph_Pause (void)
{
  if (Graph_ReadKey() == 0x00) {
  }
}

/*----------------------------------------------------------------------------*/
BOOLEAN Graph_WindowShown (void)
{
  SET flags;
  flags = SDL2_GetWindowFlags(Graph_window);
  return __IN(2, flags);
}

/*----------------------------------------------------------------------------*/
INTEGER Graph_GetTicks (void)
{
  return SDL2_GetTicks();
}

/*----------------------------------------------------------------------------*/
static struct Flip__32 {
  INTEGER *mx, *my;
  struct Flip__32 *lnk;
} *Flip__32_s;

static void __33 (void);
static void __35 (void);

static void __35 (void)
{
  (*Flip__32_s->mx) = Graph_mouseX - Graph_mouseFocusX;
  (*Flip__32_s->my) = Graph_mouseY - Graph_mouseFocusY;
  Graph_Blit(Graph_screen, Graph_underMouse, (*Flip__32_s->mx), (*Flip__32_s->my), Graph_underMouse->w, Graph_underMouse->h, 0, 0);
  if (Graph_mouseX != -1) {
    Graph_Blit(Graph_mousePointer, Graph_screen, 0, 0, Graph_mousePointer->w, Graph_mousePointer->h, (*Flip__32_s->mx), (*Flip__32_s->my));
  }
}

static void __33 (void)
{
  if (Graph_mouseX != -1) {
    Graph_Blit(Graph_underMouse, Graph_screen, 0, 0, Graph_underMouse->w, Graph_underMouse->h, (*Flip__32_s->mx), (*Flip__32_s->my));
  }
  Graph_needRedrawMouse = 0;
}

void Graph_Flip (void)
{
  INTEGER mx, my;
  BOOLEAN blitMouse;
  INTEGER dt;
  struct Flip__32 _s;
  _s.mx = &mx;
  _s.my = &my;
  _s.lnk = Flip__32_s;
  Flip__32_s = &_s;
  if (Graph_wantFPS != -1) {
    if (Graph_lastFlip != -1) {
      dt = __DIVF(1000, Graph_wantFPS) - (Graph_GetTicks() - Graph_lastFlip);
      if (dt > 0 && dt < 1000) {
        Graph_Delay(dt);
      }
    }
    Graph_lastFlip = Graph_GetTicks();
  }
  if (Graph_WindowShown()) {
    mx = 0;
    my = 0;
    blitMouse = Graph_showMouse && Graph_MouseOnScreen();
    if (blitMouse) {
      __35();
    }
    SDL2_SetRenderDrawColor(Graph_renderer, 0, 0, 0, 255);
    SDL2_RenderClear(Graph_renderer);
    if (Graph_screenTexture != NIL) {
      SDL2_DestroyTexture(Graph_screenTexture);
      Graph_screenTexture = NIL;
    }
    Graph_screenTexture = SDL2_CreateTextureFromSurface(Graph_renderer, Graph_screen->surface);
    SDL2_SetTextureAlphaMod(Graph_screenTexture, Graph_screenAlpha);
    SDL2_RenderCopyNil(Graph_renderer, Graph_screenTexture);
    SDL2_RenderPresent(Graph_renderer);
    if (blitMouse) {
      __33();
    }
  }
  Flip__32_s = _s.lnk;
}

/*----------------------------------------------------------------------------*/
INTEGER Graph_Time (void)
{
  return (SHORTINT)Platform_Time();
}

/*----------------------------------------------------------------------------*/
void Graph_PutSeed (INTEGER newSeed)
{
  newSeed = __MOD(newSeed, 2147483647);
  if (newSeed == 0) {
    Graph_randomSeed = 1;
  } else {
    Graph_randomSeed = newSeed;
  }
}

/*----------------------------------------------------------------------------*/
static void Graph_NextRND (void)
{
  INTEGER lo, hi, test;
  hi = __DIV(Graph_randomSeed, 127773);
  lo = __MOD(Graph_randomSeed, 127773);
  test = 16807 * lo - 2836 * hi;
  if (test > 0) {
    Graph_randomSeed = test;
  } else {
    Graph_randomSeed = test + 2147483647;
  }
}

INTEGER Graph_Random (INTEGER range)
{
  Graph_NextRND();
  return __MODF(Graph_randomSeed, range);
}

/*----------------------------------------------------------------------------*/
SHORTREAL Graph_Uniform (void)
{
  Graph_NextRND();
  return (SHORTREAL)(Graph_randomSeed - 1) * 4.6566129e-10;
}

/*----------------------------------------------------------------------------*/
void Graph_Randomize (void)
{
  Graph_PutSeed(Graph_Time());
}

/*----------------------------------------------------------------------------*/
Graph_Bitmap Graph_Init (void)
{
  SET flags;
  BOOLEAN success;
  INTEGER w, h, nw, nh;
  CHAR s[2000];
  Graph_screen = NIL;
  if ((INTEGER)SDL2_Init(0x20) != 0) {
    Graph_GetError((void*)s, 2000);
    Out_String((void*)s, 2000);
    Out_Ln();
  } else {
    flags = 0x0;
    if (Graph_wantFullscreen) {
      flags = flags | 0x1001;
      if (Graph_wantW <= 0 || Graph_wantH <= 0) {
        Graph_GetDesktopResolution(&Graph_wantW, &Graph_wantH);
      } else if (Graph_wantSpread) {
        Graph_GetDesktopResolution(&w, &h);
        if (Graph_wantSharpPixels) {
          nw = __DIVF(w, Graph_wantW);
          nh = __DIVF(h, Graph_wantH);
          if (nw < nh) {
            Graph_wantW = __DIVF(w, nw);
            Graph_wantH = __DIVF(h, nw);
          } else {
            Graph_wantW = __DIVF(w, nh);
            Graph_wantH = __DIVF(h, nh);
          }
        }
        if ((REAL)w / (REAL)(REAL)h > (REAL)Graph_wantW / (REAL)(REAL)Graph_wantH) {
          Graph_wantW = __DIVF(w * Graph_wantH, h);
        } else {
          Graph_wantH = __DIVF(h * Graph_wantW, w);
        }
      }
    } else if (Graph_wantW <= 0 || Graph_wantH <= 0) {
      Graph_wantW = 640;
      Graph_wantH = 400;
    }
    if (Graph_sizeStepX != 1) {
      Graph_wantW = __DIVF(Graph_wantW, Graph_sizeStepX) * Graph_sizeStepX;
    }
    if (Graph_sizeStepY != 1) {
      Graph_wantH = __DIVF(Graph_wantH, Graph_sizeStepY) * Graph_sizeStepY;
    }
    Graph_window = SDL2_CreateWindow((CHAR*)"", 1, 536805376, 536805376, Graph_wantW, Graph_wantH, flags);
    if (Graph_window != NIL) {
      if (Graph_wantSoftware) {
        flags = 0x01;
      } else {
        flags = 0x02;
      }
      flags |= __SETOF(2);
      Graph_renderer = SDL2_CreateRenderer(Graph_window, -1, flags);
      if (Graph_wantSharpPixels) {
        SDL2_SetHint((CHAR*)"SDL_RENDER_SCALE_QUALITY", 25, (CHAR*)"0", 2);
      } else {
        SDL2_SetHint((CHAR*)"SDL_RENDER_SCALE_QUALITY", 25, (CHAR*)"1", 2);
      }
      SDL2_RenderSetLogicalSize(Graph_renderer, Graph_wantW, Graph_wantH);
      Graph_screen = Graph_CreateBitmap(Graph_wantW, Graph_wantH);
      Graph_screenTexture = NIL;
      Graph_UnsetRegion();
      SDL2_ShowCursor(0);
      if (Graph_wantMouse) {
        Graph_InitMouseData();
      }
      flags = 0x03;
      if ((flags & ~SDL2_ImgInit(flags)) != 0x0) {
        Out_String((CHAR*)"Could not initialize PNG or JPG: ", 34);
        Graph_GetError((void*)s, 2000);
        Out_String((void*)s, 2000);
        Out_Ln();
      }
      Graph_Randomize();
      Graph_keyPressed = 0;
      Graph_lastFlip = -1;
      Graph_screenAlpha = 255;
    }
  }
  return Graph_screen;
}

/*----------------------------------------------------------------------------*/
void Graph_Close (void)
{
  if (Graph_screenTexture != NIL) {
    SDL2_DestroyTexture(Graph_screenTexture);
    Graph_screenTexture = NIL;
  }
  SDL2_Quit();
}

/*----------------------------------------------------------------------------*/
static void EnumPtrs(void (*P)(void*))
{
  P(Graph_window);
  P(Graph_renderer);
  P(Graph_screen);
  P(Graph_screenTexture);
  P(Graph_buffer);
  P(Graph_stdMousePointer);
  P(Graph_mousePointer);
  P(Graph_underMouse);
}

__TDESC(Graph_BitmapDesc__desc, 3, 0) = {__TDFLDS("BitmapDesc", 16), {-8}};
__TDESC(Graph_MonoFontDesc__desc, 2, 2) = {__TDFLDS("MonoFontDesc", 32), {0, 24, -24}};
__TDESC(Graph_CharGeo__desc, 2, 0) = {__TDFLDS("CharGeo", 12), {-8}};
__TDESC(Graph_FontDesc__desc, 2, 1) = {__TDFLDS("FontDesc", 6160), {0, -16}};
__TDESC(Graph_Key__desc, 1, 0) = {__TDFLDS("Key", 16), {-8}};
__TDESC(Graph_Region__desc, 2, 0) = {__TDFLDS("Region", 16), {-8}};
__TDESC(Graph_Event__desc, 1, 0) = {__TDFLDS("Event", 80), {-8}};
__TDESC(Graph_EventQueue__desc, 2, 0) = {__TDFLDS("EventQueue", 20492), {-8}};

export void *Graph__init (void)
{
  __DEFMOD;
  __IMPORT(Out__init);
  __IMPORT(Platform__init);
  __IMPORT(Strings__init);
  __IMPORT(Texts__init);
  __REGMOD("Graph", EnumPtrs);
  __REGCMD("ClearScreen", Graph_ClearScreen);
  __REGCMD("Close", Graph_Close);
  __REGCMD("CreateStdMousePointer", Graph_CreateStdMousePointer);
  __REGCMD("Flip", Graph_Flip);
  __REGCMD("Pause", Graph_Pause);
  __REGCMD("Randomize", Graph_Randomize);
  __REGCMD("RepeatFlip", Graph_RepeatFlip);
  __REGCMD("SetStdMousePointer", Graph_SetStdMousePointer);
  __REGCMD("StartTextInput", Graph_StartTextInput);
  __REGCMD("StopTextInput", Graph_StopTextInput);
  __REGCMD("SwitchToFullscreen", Graph_SwitchToFullscreen);
  __REGCMD("SwitchToWindowed", Graph_SwitchToWindowed);
  __REGCMD("ToggleFullscreen", Graph_ToggleFullscreen);
  __REGCMD("UnsetRegion", Graph_UnsetRegion);
  __INITYP(Graph_BitmapDesc, Graph_BitmapDesc, 0);
  __INITBP(Graph_BitmapDesc, Graph_Bitmap_Finalize, 1);
  __INITYP(Graph_MonoFontDesc, Graph_MonoFontDesc, 0);
  __INITYP(Graph_CharGeo, Graph_CharGeo, 0);
  __INITYP(Graph_FontDesc, Graph_FontDesc, 0);
  __INITYP(Graph_Key, Graph_Key, 0);
  __INITYP(Graph_Region, Graph_Region, 0);
  __INITYP(Graph_Event, Graph_Event, 0);
  __INITYP(Graph_EventQueue, Graph_EventQueue, 0);
/* BEGIN */
  Graph_wantW = 640;
  Graph_wantH = 400;
  Graph_sizeStepX = 1;
  Graph_sizeStepY = 1;
  Graph_wantFullscreen = 1;
  Graph_wantSpread = 1;
  Graph_wantBuffer = 0;
  Graph_buffer = NIL;
  Graph_wantFPS = 60;
  Graph_wantSharpPixels = 1;
  Graph_mousePointer = NIL;
  Graph_lastBlitMouseOutside = 0;
  Graph_mouseFocusX = 0;
  Graph_mouseFocusY = 0;
  Graph_events.first = 0;
  Graph_events.last = -1;
  Graph_events.len = 0;
  Graph_randomSeed = 1;
  Graph_keyPressed = 0;
  __ENDMOD;
}
