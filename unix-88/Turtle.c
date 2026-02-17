/* Ofront+ 1.0 -sC -88 */
#include "SYSTEM.oh"
#include "Graph.oh"
#include "SDL2.oh"
#include "Math.oh"


static Graph_Bitmap Turtle_screen;
export SHORTREAL Turtle_x, Turtle_y;
static SHORTREAL Turtle_angle;
static INTEGER Turtle_color;
static BOOLEAN Turtle_penstatus;
export INTEGER Turtle_Black, Turtle_Blue, Turtle_Green, Turtle_Cyan, Turtle_Red, Turtle_Magenta, Turtle_Brown, Turtle_LightGray, Turtle_DarkGray, Turtle_LightBlue, Turtle_LightGreen, Turtle_LightCyan, Turtle_LightRed, Turtle_LightMagenta, Turtle_Yellow, Turtle_White, Turtle_Orange;


export void Turtle_Back (SHORTREAL distance);
export void Turtle_Forward (SHORTREAL distance);
export void Turtle_Home (void);
export void Turtle_Left (SHORTREAL a);
export void Turtle_PenDown (void);
export void Turtle_PenUp (void);
export void Turtle_Quit (void);
export void Turtle_Right (SHORTREAL a);
static INTEGER Turtle_Round (SHORTREAL x);
export void Turtle_SetColor (INTEGER col);
export void Turtle_ShowTurtle (void);
static void Turtle_Triangle (SHORTREAL s);


/*============================================================================*/

void Turtle_Home (void)
{
  Turtle_x = (SHORTREAL)400;
  Turtle_y = (SHORTREAL)300;
  Turtle_angle = (SHORTREAL)0;
}

/*----------------------------------------------------------------------------*/
static INTEGER Turtle_Round (SHORTREAL x)
{
  return (INTEGER)__ENTIER(x + 0.5);
}

void Turtle_Forward (SHORTREAL distance)
{
  SHORTREAL newx, newy;
  newx = Turtle_x + distance * Math_cos((Turtle_angle * 3.1415927) / (SHORTREAL)(SHORTREAL)180);
  newy = Turtle_y + distance * Math_sin((Turtle_angle * 3.1415927) / (SHORTREAL)(SHORTREAL)180);
  if (Turtle_penstatus == 1) {
    Graph_Line(Turtle_screen, Turtle_Round(Turtle_x), Turtle_Round(Turtle_y), Turtle_Round(newx), Turtle_Round(newy), Turtle_color);
  }
  Turtle_x = newx;
  Turtle_y = newy;
}

/*----------------------------------------------------------------------------*/
void Turtle_Back (SHORTREAL distance)
{
  Turtle_Forward(-distance);
}

/*----------------------------------------------------------------------------*/
void Turtle_Left (SHORTREAL a)
{
  Turtle_angle = Turtle_angle - a;
}

/*----------------------------------------------------------------------------*/
void Turtle_Right (SHORTREAL a)
{
  Turtle_Left(-a);
}

/*----------------------------------------------------------------------------*/
void Turtle_PenDown (void)
{
  Turtle_penstatus = 1;
}

/*----------------------------------------------------------------------------*/
void Turtle_PenUp (void)
{
  Turtle_penstatus = 0;
}

/*----------------------------------------------------------------------------*/
void Turtle_SetColor (INTEGER col)
{
  Turtle_color = col;
}

/*----------------------------------------------------------------------------*/
static void Turtle_Triangle (SHORTREAL s)
{
  Turtle_Left((SHORTREAL)90);
  Turtle_Forward(s / (SHORTREAL)(SHORTREAL)3);
  Turtle_Right((SHORTREAL)110);
  Turtle_Forward(s);
  Turtle_Right((SHORTREAL)140);
  Turtle_Forward(s);
  Turtle_Right((SHORTREAL)110);
  Turtle_Forward(s / (SHORTREAL)(SHORTREAL)3);
  Turtle_Right((SHORTREAL)90);
}

void Turtle_ShowTurtle (void)
{
  INTEGER x;
  BOOLEAN oldpenstatus;
  oldpenstatus = Turtle_penstatus;
  Turtle_PenDown();
  Turtle_Triangle((SHORTREAL)30);
  Turtle_PenUp();
  Turtle_Left((SHORTREAL)3);
  Turtle_Forward((SHORTREAL)17);
  Turtle_PenDown();
  x = 1;
  while (x <= 10) {
    Turtle_Triangle(x);
    x += 1;
  }
  Turtle_Right((SHORTREAL)3);
  Turtle_penstatus = oldpenstatus;
}

/*----------------------------------------------------------------------------*/
void Turtle_Quit (void)
{
  Graph_Flip();
  Graph_Pause();
  Graph_Close();
}

/*----------------------------------------------------------------------------*/
static void EnumPtrs(void (*P)(void*))
{
  P(Turtle_screen);
}


export void *Turtle__init (void)
{
  __DEFMOD;
  __IMPORT(Graph__init);
  __IMPORT(Math__init);
  __REGMOD("Turtle", EnumPtrs);
  __REGCMD("Home", Turtle_Home);
  __REGCMD("PenDown", Turtle_PenDown);
  __REGCMD("PenUp", Turtle_PenUp);
  __REGCMD("Quit", Turtle_Quit);
  __REGCMD("ShowTurtle", Turtle_ShowTurtle);
/* BEGIN */
  Graph_Settings(800, 600, 0x04);
  Turtle_screen = Graph_Init();
  Graph_SetWindowTitle((CHAR*)"Turtle Demo", 12);
  Turtle_Home();
  Turtle_penstatus = 1;
  Turtle_Black = Graph_MakeCol(0, 0, 0);
  Turtle_Blue = Graph_MakeCol(0, 0, 128);
  Turtle_Green = Graph_MakeCol(0, 128, 0);
  Turtle_Cyan = Graph_MakeCol(0, 128, 128);
  Turtle_Red = Graph_MakeCol(128, 0, 0);
  Turtle_Magenta = Graph_MakeCol(128, 0, 128);
  Turtle_Brown = Graph_MakeCol(128, 128, 0);
  Turtle_LightGray = Graph_MakeCol(192, 192, 192);
  Turtle_DarkGray = Graph_MakeCol(128, 128, 128);
  Turtle_LightBlue = Graph_MakeCol(0, 0, 255);
  Turtle_LightGreen = Graph_MakeCol(0, 255, 0);
  Turtle_LightCyan = Graph_MakeCol(0, 255, 255);
  Turtle_LightRed = Graph_MakeCol(255, 0, 0);
  Turtle_LightMagenta = Graph_MakeCol(255, 0, 255);
  Turtle_Yellow = Graph_MakeCol(255, 255, 0);
  Turtle_White = Graph_MakeCol(255, 255, 255);
  Turtle_Orange = Graph_MakeCol(255, 128, 0);
  __ENDMOD;
}
