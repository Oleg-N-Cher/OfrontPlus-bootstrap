/* Ofront+ 1.0 -swC -44 */
#include "SYSTEM.oh"


static REAL bbMath_a, bbMath_b, bbMath_eps, bbMath_LnInfinity, bbMath_LnSmall;


export REAL bbMath_ArcCos (REAL x);
export REAL bbMath_ArcCosh (REAL x);
export REAL bbMath_ArcSin (REAL x);
export REAL bbMath_ArcSinh (REAL x);
export REAL bbMath_ArcTan (REAL x);
export REAL bbMath_ArcTan2 (REAL y, REAL x);
export REAL bbMath_ArcTanh (REAL x);
export REAL bbMath_Ceiling (REAL x);
export REAL bbMath_CopySign (REAL x, REAL y);
export REAL bbMath_Cos (REAL x);
export REAL bbMath_Cosh (REAL x);
export REAL bbMath_Eps (void);
export REAL bbMath_Exp (REAL x);
export INTEGER bbMath_Exponent (REAL x);
export REAL bbMath_Floor (REAL x);
export REAL bbMath_Frac (REAL x);
export REAL bbMath_IntPower (REAL x, INTEGER n);
static BOOLEAN bbMath_IsNaN (REAL x);
export REAL bbMath_Ln (REAL x);
export REAL bbMath_Log (REAL x);
export REAL bbMath_Mantissa (REAL r);
export REAL bbMath_Mod1 (REAL x);
export REAL bbMath_Pi (void);
export REAL bbMath_Power (REAL x, REAL y);
export REAL bbMath_Real (REAL m, INTEGER e);
export REAL bbMath_Round (REAL x);
static REAL bbMath_Scale (REAL x, INTEGER n);
export REAL bbMath_Sign (REAL x);
export BOOLEAN bbMath_SignBit (REAL x);
export REAL bbMath_Sin (REAL x);
export void bbMath_SinCos (REAL x, REAL *sin, REAL *cos);
static REAL bbMath_SinCos0 (REAL x, REAL y, REAL sign);
export REAL bbMath_Sinh (REAL x);
export REAL bbMath_Sqrt (REAL x);
export REAL bbMath_Tan (REAL x);
export REAL bbMath_Tanh (REAL x);
export REAL bbMath_Trunc (REAL x);


/*============================================================================*/

static BOOLEAN bbMath_IsNaN (REAL x)
{
  return (0x7ff80000 & ~(SET)((INTEGER)__ASHR(__VAL(LONGINT, x), 32, LONGINT))) == 0x0;
}

REAL bbMath_Pi (void)
{
  return 3.1415926535897929;
}

/*----------------------------------------------------------------------------*/
REAL bbMath_Eps (void)
{
  return bbMath_eps;
}

/*----------------------------------------------------------------------------*/
static REAL bbMath_Scale (REAL x, INTEGER n)
{
  INTEGER exp;
  LONGINT lexp;
  if (x == (REAL)0) {
    return (REAL)0;
  } else {
    exp = bbMath_Exponent(x) + n;
    if (exp > 1023) {
      return bbMath_CopySign((8.9884656743115738e+307 * 2), x);
    } else if (exp < -1022) {
      return bbMath_CopySign(2.2250738585072017e-308, x);
    }
    lexp = __VAL(LONGINT, x);
    lexp -= __ASHL((LONGINT)((INTEGER)((SET)((INTEGER)__ASHR(lexp, 32, LONGINT)) & 0x7ff00000)), 32, LONGINT);
    lexp += __ASHL((LONGINT)(exp + 1023), 52, LONGINT);
    return __VAL(REAL, lexp);
  }
  __RETCHK((CHAR*)"bbMath", 21247);
}

REAL bbMath_Sqrt (REAL x)
{
  REAL xMant, yEst, z;
  INTEGER xExp;
  if (x == (REAL)0) {
    return x;
  } else {
    __ASSERT(x > (REAL)0, 0, (CHAR*)"bbMath", 24593);
    xMant = bbMath_Mantissa(x) * 0.5;
    xExp = bbMath_Exponent(x) + 1;
    yEst = 0.41731000000000004 + 0.59015999999999997 * xMant;
    z = yEst + xMant / yEst;
    yEst = 0.25 * z + xMant / z;
    yEst = 0.5 * (yEst + xMant / yEst);
    if (__ODD(xExp)) {
      yEst = yEst * 0.70710678118654744;
      xExp += 1;
    }
    return bbMath_Scale(yEst, __ASHR(xExp, 1, INTEGER));
  }
  __RETCHK((CHAR*)"bbMath", 27647);
}

/*----------------------------------------------------------------------------*/
REAL bbMath_Exp (REAL x)
{
  REAL xn, g, p, q, z;
  INTEGER n;
  __ASSERT(x <= bbMath_LnInfinity, 0, (CHAR*)"bbMath", 31769);
  if (x < bbMath_LnSmall) {
    return (REAL)0;
  } else if (__ABS(x) < bbMath_eps) {
    return (REAL)1;
  }
  if (x >= (REAL)0) {
    n = (INTEGER)__ENTIER(1.4426950408889634 * x + 0.5);
  } else {
    n = (INTEGER)__ENTIER(1.4426950408889634 * x - 0.5);
  }
  xn = n;
  g = (x - xn * 0.693359375) - xn * -2.1219444005469059e-4;
  z = g * g;
  p = ((1.6520330026827912e-5 * z + 0.0069436000151179292) * z + 0.25) * g;
  q = (4.9586288490544138e-4 * z + 0.055553866696900127) * z + 0.5;
  return bbMath_Scale(0.5 + p / (REAL)(q - p), n + 1);
}

/*----------------------------------------------------------------------------*/
REAL bbMath_Ln (REAL x)
{
  REAL f, zn, zd, r, z, w, p, q, xn;
  INTEGER n;
  __ASSERT(x > (REAL)0, 0, (CHAR*)"bbMath", 38672);
  f = bbMath_Mantissa(x) * 0.5;
  n = bbMath_Exponent(x) + 1;
  if (f > 0.70710678118654744) {
    zn = (f - 0.5) - 0.5;
    zd = f * 0.5 + 0.5;
  } else {
    zn = f - 0.5;
    zd = zn * 0.5 + 0.5;
    n -= 1;
  }
  z = zn / zd;
  w = z * z;
  q = ((w + -35.667977739034649) * w + 312.03222091924533) * w + -769.49932108494875;
  p = w * ((-0.78956112887491258 * w + 16.383943563021535) * w + -64.124943423745572);
  r = z + z * (p / q);
  xn = n;
  return (xn * -2.1219444005469059e-4 + r) + xn * 0.693359375;
}

/*----------------------------------------------------------------------------*/
REAL bbMath_Log (REAL x)
{
  return bbMath_Ln(x) / 2.3025850929940457;
}

/*----------------------------------------------------------------------------*/
REAL bbMath_Power (REAL x, REAL y)
{
  __ASSERT(x >= (REAL)0, 20, (CHAR*)"bbMath", 43796);
  __ASSERT(x != (REAL)0 || y != (REAL)0, 21, (CHAR*)"bbMath", 44068);
  __ASSERT(x != __INF || y != (REAL)0, 22, (CHAR*)"bbMath", 44324);
  __ASSERT(x != (REAL)1 || __ABS(y) != __INF, 23, (CHAR*)"bbMath", 44585);
  return bbMath_Exp(y * bbMath_Ln(x));
}

/*----------------------------------------------------------------------------*/
REAL bbMath_IntPower (REAL x, INTEGER n)
{
  REAL y;
  if (n == (-2147483647-1)) {
    return bbMath_IntPower(x, n + 1) / x;
  }
  y = (REAL)1;
  if (n < 0) {
    x = (REAL)1 / x;
    n = -n;
  }
  while (n > 0) {
    if (__ODD(n)) {
      y = y * x;
      n -= 1;
    } else {
      x = x * x;
      n = __ASHR(n, 1, INTEGER);
    }
  }
  return y;
}

/*----------------------------------------------------------------------------*/
static REAL bbMath_SinCos0 (REAL x, REAL y, REAL sign)
{
  LONGINT n;
  REAL xn, f, x1, g;
  __ASSERT(y < (REAL)210828714, 20, (CHAR*)"bbMath", 53270);
  n = __ENTIERL(y * 0.3183098861837907 + 0.5);
  xn = n;
  if (__ODD(n)) {
    sign = -sign;
  }
  x = __ABS(x);
  if (x != y) {
    xn = xn - 0.5;
  }
  x1 = __ENTIERL(x);
  f = ((x1 - xn * 3.1416015625) + (x - x1)) - xn * -8.9089102067615386e-6;
  if (__ABS(f) < 1.0536712e-8) {
    return sign * f;
  }
  g = f * f;
  g = (((((((2.7204790957888849e-15 * g + -7.642917806891046e-13) * g + 1.6058936490371591e-10) * g + -2.5052106798274585e-8) * g + 2.7557319210152755e-6) * g + -1.984126984120184e-4) * g + 0.0083333333333331655) * g + -0.16666666666666665) * g;
  g = f + f * g;
  return sign * g;
}

REAL bbMath_Sin (REAL x)
{
  if (x < (REAL)0) {
    return bbMath_SinCos0(x, -x, (REAL)-1);
  } else {
    return bbMath_SinCos0(x, x, (REAL)1);
  }
  __RETCHK((CHAR*)"bbMath", 58623);
}

/*----------------------------------------------------------------------------*/
REAL bbMath_Cos (REAL x)
{
  return bbMath_SinCos0(x, __ABS(x) + 1.5707963267948965, (REAL)1);
}

/*----------------------------------------------------------------------------*/
void bbMath_SinCos (REAL x, REAL *sin, REAL *cos)
{
  *sin = bbMath_Sin(x);
  *cos = bbMath_Cos(x);
}

/*----------------------------------------------------------------------------*/
REAL bbMath_Tan (REAL x)
{
  REAL sin, cos;
  bbMath_SinCos(x, &sin, &cos);
  __ASSERT(__ABS(cos) >= 5.5626846462680078e-309, 0, (CHAR*)"bbMath", 63002);
  return sin / cos;
}

/*----------------------------------------------------------------------------*/
REAL bbMath_ArcSin (REAL x)
{
  __ASSERT(__ABS(x) <= (REAL)1, 20, (CHAR*)"bbMath", 65050);
  return bbMath_ArcTan(x / bbMath_Sqrt((REAL)1 - x * x));
}

/*----------------------------------------------------------------------------*/
REAL bbMath_ArcCos (REAL x)
{
  __ASSERT(__ABS(x) <= (REAL)1, 20, (CHAR*)"bbMath", 66586);
  return bbMath_ArcTan(bbMath_Sqrt((REAL)1 - x * x) / x);
}

/*----------------------------------------------------------------------------*/
REAL bbMath_ArcTan (REAL x)
{
  REAL g;
  BOOLEAN neg;
  INTEGER n;
  if (x == (REAL)0) {
    return x;
  }
  neg = 0;
  if (x < (REAL)0) {
    neg = 1;
    x = -x;
  }
  if (x > (REAL)1) {
    x = (REAL)1 / x;
    n = 2;
  } else {
    n = 0;
  }
  if (x > 0.26794919243112267) {
    n += 1;
    x = (((0.7320508075688773 * x - 0.5) - 0.5) + x) / (REAL)(1.7320508075688772 + x);
  }
  g = x * x;
  x = x + ((x * g) * (((-0.83758299368150062 * g + -8.4946240351320682) * g + -20.505855195861654) * g + -13.688768894191928)) / (REAL)(((((REAL)1 * g + 15.024001160028574) * g + 59.578436142597343) * g + 86.157349597130235) * g + 41.066306682575777);
  if (n > 1) {
    x = -x;
  }
  switch (n) {
    case 1: 
      x = x + 0.52359877559829897;
      break;
    case 2: 
      x = x + 1.5707963267948965;
      break;
    case 3: 
      x = x + 1.0471975511965979;
      break;
    default: 
      break;
  }
  if (neg) {
    return -x;
  }
  return x;
}

/*----------------------------------------------------------------------------*/
REAL bbMath_ArcTan2 (REAL y, REAL x)
{
  if (x == (REAL)0) {
    if (__VAL(LONGINT, x) == 0) {
      return bbMath_Sign(y) * 1.5707963267948965;
    } else if (y == (REAL)0) {
      return bbMath_CopySign(3.1415926535897929, y);
    } else {
      return bbMath_CopySign(1.5707963267948965, y);
    }
  } else if (y == (REAL)0) {
    return ((REAL)1 - bbMath_Sign(x)) * bbMath_CopySign(1.5707963267948965, y);
  } else if (__ABS(x) == __INF && __ABS(y) == __INF) {
    return ((REAL)2 - bbMath_Sign(x)) * bbMath_CopySign(0.78539816339744823, y);
  } else {
    return bbMath_ArcTan(y / x) + ((REAL)1 - bbMath_Sign(x)) * bbMath_CopySign(1.5707963267948965, y);
  }
  __RETCHK((CHAR*)"bbMath", 82943);
}

/*----------------------------------------------------------------------------*/
REAL bbMath_Sinh (REAL x)
{
  if (x == (REAL)0) {
    return x;
  } else if (__ABS(x) < 36.043653389117151) {
    return (bbMath_Exp(x) - bbMath_Exp(-x)) / (REAL)(REAL)2;
  } else {
    return (bbMath_Sign(x) * bbMath_Exp(__ABS(x))) / (REAL)(REAL)2;
  }
  __RETCHK((CHAR*)"bbMath", 85503);
}

/*----------------------------------------------------------------------------*/
REAL bbMath_Cosh (REAL x)
{
  REAL expx;
  if (__ABS(x) < 36.043653389117151) {
    return (bbMath_Exp(x) + bbMath_Exp(-x)) / (REAL)(REAL)2;
  } else {
    return bbMath_Exp(__ABS(x)) / (REAL)(REAL)2;
  }
  __RETCHK((CHAR*)"bbMath", 87551);
}

/*----------------------------------------------------------------------------*/
REAL bbMath_Tanh (REAL x)
{
  REAL e1, e2;
  if (x == (REAL)0) {
    return x;
  } else if (__ABS(x) < 36.043653389117151) {
    e1 = bbMath_Exp(x);
    e2 = (REAL)1 / e1;
    return (e1 - e2) / (REAL)(e1 + e2);
  } else {
    return bbMath_Sign(x);
  }
  __RETCHK((CHAR*)"bbMath", 90623);
}

/*----------------------------------------------------------------------------*/
REAL bbMath_ArcSinh (REAL x)
{
  return bbMath_Sign(x) * bbMath_Ln(__ABS(x) + bbMath_Sqrt(x * x + (REAL)1));
}

/*----------------------------------------------------------------------------*/
REAL bbMath_ArcCosh (REAL x)
{
  return bbMath_Ln(x + bbMath_Sqrt(x * x - (REAL)1));
}

/*----------------------------------------------------------------------------*/
REAL bbMath_ArcTanh (REAL x)
{
  __ASSERT(__ABS(x) <= (REAL)1, 20, (CHAR*)"bbMath", 94490);
  if (x == (REAL)0) {
    return x;
  } else {
    return bbMath_Ln(((REAL)1 + x) / (REAL)((REAL)1 - x)) / (REAL)(REAL)2;
  }
  __RETCHK((CHAR*)"bbMath", 94786);
}

/*----------------------------------------------------------------------------*/
REAL bbMath_Floor (REAL x)
{
  if (__ABS(x) >= (REAL)10000000000000000LL) {
    return x;
  } else {
    return __ENTIERL(x);
  }
  __RETCHK((CHAR*)"bbMath", 96767);
}

/*----------------------------------------------------------------------------*/
REAL bbMath_Ceiling (REAL x)
{
  if (__ABS(x) >= (REAL)10000000000000000LL) {
    return x;
  } else {
    return -(__ENTIERL(-x));
  }
  __RETCHK((CHAR*)"bbMath", 98559);
}

/*----------------------------------------------------------------------------*/
REAL bbMath_Round (REAL x)
{
  if (__ABS(x) >= (REAL)10000000000000000LL) {
    return x;
  } else {
    return __ENTIERL(x + 0.5);
  }
  __RETCHK((CHAR*)"bbMath", 100351);
}

/*----------------------------------------------------------------------------*/
REAL bbMath_Trunc (REAL x)
{
  if (__ABS(x) >= (REAL)10000000000000000LL) {
    return x;
  } else if (x >= (REAL)0) {
    return __ENTIERL(x);
  } else {
    return -(__ENTIERL(-x));
  }
  __RETCHK((CHAR*)"bbMath", 102399);
}

/*----------------------------------------------------------------------------*/
REAL bbMath_Frac (REAL x)
{
  if (__ABS(x) >= (REAL)10000000000000000LL) {
    return (REAL)0;
  } else if (x >= (REAL)0) {
    return x - (REAL)(__ENTIERL(x));
  } else {
    return x + (REAL)(__ENTIERL(-x));
  }
  __RETCHK((CHAR*)"bbMath", 104447);
}

/*----------------------------------------------------------------------------*/
REAL bbMath_Mod1 (REAL x)
{
  if (__ABS(x) >= (REAL)10000000000000000LL) {
    return (REAL)0;
  } else {
    return x - (REAL)(__ENTIERL(x));
  }
  __RETCHK((CHAR*)"bbMath", 106239);
}

/*----------------------------------------------------------------------------*/
REAL bbMath_Sign (REAL x)
{
  if (x > (REAL)0) {
    return (REAL)1;
  } else if (x < (REAL)0) {
    return (REAL)-1;
  } else {
    return x;
  }
  __RETCHK((CHAR*)"bbMath", 108287);
}

/*----------------------------------------------------------------------------*/
BOOLEAN bbMath_SignBit (REAL x)
{
  return __IN(31, (SET)((INTEGER)__ASHR(__VAL(LONGINT, x), 32, LONGINT)));
}

/*----------------------------------------------------------------------------*/
REAL bbMath_CopySign (REAL x, REAL y)
{
  if (bbMath_SignBit(y)) {
    return -__ABS(x);
  } else {
    return __ABS(x);
  }
  __RETCHK((CHAR*)"bbMath", 110902);
}

/*----------------------------------------------------------------------------*/
REAL bbMath_Mantissa (REAL r)
{
  LONGINT k, msh;
  REAL a;
  INTEGER exp;
  if (bbMath_IsNaN(r)) {
    return bbMath_CopySign(1.5, r);
  } else if (r == (REAL)0) {
    return (REAL)0;
  } else if (r == __INF) {
    return (REAL)1;
  } else if (r == -__INF) {
    return (REAL)-1;
  } else {
    a = __ABS(r);
    exp = (INTEGER)__ASHR(__VAL(LONGINT, a), 52, LONGINT);
    while (exp == 0) {
      r = r + r;
      a = __ABS(r);
      exp = (INTEGER)__ASHR(__VAL(LONGINT, a), 52, LONGINT);
    }
    k = __VAL(LONGINT, r);
    msh = (INTEGER)(((SET)((INTEGER)__ASHR(k, 32, LONGINT)) & 0x800fffff) | 0x3ff00000);
    k = __ASHL(msh, 32, LONGINT) + __MASK(k, -4294967296LL);
    return __VAL(REAL, k);
  }
  __RETCHK((CHAR*)"bbMath", 116479);
}

/*----------------------------------------------------------------------------*/
INTEGER bbMath_Exponent (REAL x)
{
  INTEGER exp, offset;
  if (bbMath_IsNaN(x)) {
    return 2147483647;
  } else if (x == (REAL)0) {
    return 0;
  } else {
    x = __ABS(x);
    if (x == __INF) {
      return 2147483647;
    } else {
      exp = (INTEGER)__ASHR(__VAL(LONGINT, x), 52, LONGINT);
    }
    offset = 1023;
    while (exp == 0) {
      x = x + x;
      exp = (INTEGER)__ASHR(__VAL(LONGINT, x), 52, LONGINT);
      offset += 1;
    }
    return exp - offset;
  }
  __RETCHK((CHAR*)"bbMath", 121087);
}

/*----------------------------------------------------------------------------*/
REAL bbMath_Real (REAL m, INTEGER e)
{
  SET s;
  INTEGER i, _for__27, _for__26;
  if (m == (REAL)0) {
    return m;
  }
  __ASSERT((!bbMath_IsNaN(m) && (REAL)1 <= __ABS(m)) && __ABS(m) < (REAL)2, 20, (CHAR*)"bbMath", 123190);
  if (e == 2147483647) {
    __GET((SYSTEM_ADRINT)&m + 4, s, SET);
    __PUT((SYSTEM_ADRINT)&m + 4, s | 0x7ff00000, SET);
  } else {
    if (e > 0) {
      _for__27 = e;
      i = 1;
      while (i <= _for__27) {
        m = m * (REAL)2;
        i += 1;
      }
    } else if (e < 0) {
      _for__26 = -e;
      i = 1;
      while (i <= _for__26) {
        m = m / (REAL)(REAL)2;
        i += 1;
      }
    }
  }
  return m;
}

/*----------------------------------------------------------------------------*/

export void *bbMath__init (void)
{
  __DEFMOD;
  __REGMOD("bbMath", 0);
/* BEGIN */
  bbMath_LnInfinity = bbMath_Ln((8.9884656743115738e+307 * 2));
  bbMath_LnSmall = bbMath_Ln(5.5626846462680078e-309);
  bbMath_eps = (REAL)1;
  bbMath_a = (REAL)1;
  bbMath_b = (REAL)1;
  do {
    bbMath_eps = bbMath_eps / (REAL)(REAL)2;
    bbMath_a = bbMath_b + bbMath_eps / (REAL)(REAL)2;
  } while (!(bbMath_a <= bbMath_b));
  __ENDMOD;
}
