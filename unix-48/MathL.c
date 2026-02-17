/* Ofront+ 1.0 -sC -48 */
#include "SYSTEM.oh"
#include "Math.oh"


static REAL MathL_a1[18];
static REAL MathL_a2[9];
static REAL MathL_em, MathL_LnInfinity, MathL_LnSmall, MathL_SqrtInfinity, MathL_TanhMax, MathL_t;
export REAL MathL_INF;


export BOOLEAN MathL_IsRMathException (void);
static REAL MathL_SinCos (REAL x, REAL y, REAL sign);
export REAL MathL_arccos (REAL x);
export REAL MathL_arccosh (REAL x);
export REAL MathL_arcsin (REAL x);
export REAL MathL_arcsinh (REAL x);
export REAL MathL_arctan (REAL x);
export REAL MathL_arctan2 (REAL xn, REAL xd);
export REAL MathL_arctanh (REAL x);
export REAL MathL_cos (REAL x);
export REAL MathL_cosh (REAL x);
static INTEGER MathL_div (INTEGER x, INTEGER y);
export REAL MathL_exp (REAL x);
export INTEGER MathL_exponent (REAL x);
export REAL MathL_fraction (REAL x);
export REAL MathL_ipower (REAL x, SHORTINT base);
static BOOLEAN MathL_isNaN (REAL x);
export REAL MathL_ln (REAL x);
export REAL MathL_log (REAL x, REAL base);
export REAL MathL_power (REAL base, REAL exp);
export REAL MathL_pred (REAL x);
export INTEGER MathL_round (REAL x);
export REAL MathL_scale (REAL x, INTEGER n);
export REAL MathL_sign (REAL x);
export REAL MathL_sin (REAL x);
export void MathL_sincos (REAL x, REAL *Sin, REAL *Cos);
export REAL MathL_sinh (REAL x);
export REAL MathL_sqrt (REAL x);
export REAL MathL_succ (REAL x);
export REAL MathL_tan (REAL x);
export REAL MathL_tanh (REAL x);
export REAL MathL_ulp (REAL x);


/*============================================================================*/

static BOOLEAN MathL_isNaN (REAL x)
{
  return (0x7ff80000 & ~(SET)((INTEGER)__ASHR(__VAL(LONGINT, x), 32, LONGINT))) == 0x0;
}

REAL MathL_fraction (REAL x)
{
  LONGINT k, msh;
  REAL a;
  INTEGER exp;
  if (MathL_isNaN(x)) {
    return 1.5;
  } else if (x == (REAL)0) {
    return (REAL)0;
  } else if (x == MathL_INF) {
    return (REAL)1;
  } else if (x == -MathL_INF) {
    return (REAL)-1;
  } else {
    a = __ABS(x);
    exp = (INTEGER)__ASHR(__VAL(LONGINT, a), 52, LONGINT);
    while (exp == 0) {
      x = x + x;
      a = __ABS(x);
      exp = (INTEGER)__ASHR(__VAL(LONGINT, a), 52, LONGINT);
    }
    k = __VAL(LONGINT, x);
    msh = (INTEGER)(((SET)((INTEGER)__ASHR(k, 32, LONGINT)) & 0x800fffff) | 0x3ff00000);
    k = __ASHL(msh, 32, LONGINT) + __MASK(k, -4294967296LL);
    return __VAL(REAL, k);
  }
  __RETCHK((CHAR*)"MathL", 39423);
}

/*----------------------------------------------------------------------------*/
INTEGER MathL_exponent (REAL x)
{
  INTEGER exp, offset;
  if (MathL_isNaN(x)) {
    return 2147483647;
  } else if (x == (REAL)0) {
    return 0;
  } else {
    x = __ABS(x);
    if (x == MathL_INF) {
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
  __RETCHK((CHAR*)"MathL", 45311);
}

/*----------------------------------------------------------------------------*/
REAL MathL_sign (REAL x)
{
  if (x < (REAL)0) {
    return (REAL)-1;
  } else {
    return (REAL)1;
  }
  __RETCHK((CHAR*)"MathL", 46638);
}

/*----------------------------------------------------------------------------*/
REAL MathL_scale (REAL x, INTEGER n)
{
  INTEGER exp;
  LONGINT s;
  if (x == (REAL)0) {
    return (REAL)0;
  }
  exp = MathL_exponent(x) + n;
  if (exp > 1023) {
    return (8.9884656743115738e+307 * 2) * MathL_sign(x);
  } else if (exp < -1022) {
    return 2.2250738585072017e-308 * MathL_sign(x);
  }
  s = __VAL(LONGINT, x);
  s -= __ASHL((LONGINT)((INTEGER)((SET)((INTEGER)__ASHR(s, 32, LONGINT)) & 0x7ff00000)), 32, LONGINT);
  s += __ASHL((LONGINT)(exp + 1023), 52, LONGINT);
  return __VAL(REAL, s);
}

/*----------------------------------------------------------------------------*/
REAL MathL_ulp (REAL x)
{
  return MathL_scale((REAL)1, (MathL_exponent(x) - 53) + 1);
}

/*----------------------------------------------------------------------------*/
REAL MathL_succ (REAL x)
{
  return x + MathL_ulp(x) * MathL_sign(x);
}

/*----------------------------------------------------------------------------*/
REAL MathL_pred (REAL x)
{
  return x - MathL_ulp(x) * MathL_sign(x);
}

/*----------------------------------------------------------------------------*/
static REAL MathL_SinCos (REAL x, REAL y, REAL sign)
{
  LONGINT n;
  REAL xn, f, x1, g;
  if (y >= (REAL)210828714) {
    (*Math_ErrorHandler)(10);
    return (REAL)0;
  }
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

static INTEGER MathL_div (INTEGER x, INTEGER y)
{
  if (x < 0) {
    return -__DIVF(__ABS(x), y);
  } else {
    return __DIVF(x, y);
  }
  __RETCHK((CHAR*)"MathL", 70456);
}

REAL MathL_sqrt (REAL x)
{
  REAL xMant, yEst, z;
  INTEGER xExp;
  if (x == (REAL)0) {
    return (REAL)0;
  }
  if (x < (REAL)0) {
    (*Math_ErrorHandler)(1);
    x = -x;
  }
  xMant = MathL_fraction(x) * 0.5;
  xExp = MathL_exponent(x) + 1;
  yEst = 0.41731000000000004 + 0.59015999999999997 * xMant;
  z = yEst + xMant / yEst;
  yEst = 0.25 * z + xMant / z;
  yEst = 0.5 * (yEst + xMant / yEst);
  if (__ODD(xExp)) {
    yEst = yEst * 0.70710678118654744;
    xExp += 1;
  }
  return MathL_scale(yEst, __ASHR(xExp, 1, INTEGER));
}

/*----------------------------------------------------------------------------*/
REAL MathL_exp (REAL x)
{
  REAL xn, g, p, q, z;
  INTEGER n;
  if (x > MathL_LnInfinity) {
    (*Math_ErrorHandler)(3);
    return (8.9884656743115738e+307 * 2);
  } else if (x < MathL_LnSmall) {
    return (REAL)0;
  } else if (__ABS(x) < 5.5511150999999995e-17) {
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
  return MathL_scale(0.5 + p / (REAL)(q - p), n + 1);
}

/*----------------------------------------------------------------------------*/
REAL MathL_ln (REAL x)
{
  REAL f, zn, zd, r, z, w, p, q, xn;
  INTEGER n;
  if (x <= (REAL)0) {
    (*Math_ErrorHandler)(2);
    return (-8.9884656743115738e+307 * 2);
  }
  f = MathL_fraction(x) * 0.5;
  n = MathL_exponent(x) + 1;
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
REAL MathL_sin (REAL x)
{
  if (x < (REAL)0) {
    return MathL_SinCos(x, -x, (REAL)-1);
  } else {
    return MathL_SinCos(x, x, (REAL)1);
  }
  __RETCHK((CHAR*)"MathL", 95231);
}

/*----------------------------------------------------------------------------*/
REAL MathL_cos (REAL x)
{
  return MathL_SinCos(x, __ABS(x) + 1.5707963267948965, (REAL)1);
}

/*----------------------------------------------------------------------------*/
REAL MathL_tan (REAL x)
{
  REAL Sin, Cos;
  MathL_sincos(x, &Sin, &Cos);
  if (__ABS(Cos) < 5.5626846462680078e-309) {
    (*Math_ErrorHandler)(6);
    return (8.9884656743115738e+307 * 2);
  } else {
    return Sin / Cos;
  }
  __RETCHK((CHAR*)"MathL", 99071);
}

/*----------------------------------------------------------------------------*/
REAL MathL_arcsin (REAL x)
{
  if (__ABS(x) > (REAL)1) {
    (*Math_ErrorHandler)(7);
    return (8.9884656743115738e+307 * 2);
  } else {
    return MathL_arctan2(x, MathL_sqrt((REAL)1 - x * x));
  }
  __RETCHK((CHAR*)"MathL", 101119);
}

/*----------------------------------------------------------------------------*/
REAL MathL_arccos (REAL x)
{
  if (__ABS(x) > (REAL)1) {
    (*Math_ErrorHandler)(7);
    return (8.9884656743115738e+307 * 2);
  } else {
    return MathL_arctan2(MathL_sqrt((REAL)1 - x * x), x);
  }
  __RETCHK((CHAR*)"MathL", 103167);
}

/*----------------------------------------------------------------------------*/
REAL MathL_arctan (REAL x)
{
  return MathL_arctan2(x, (REAL)1);
}

/*----------------------------------------------------------------------------*/
REAL MathL_power (REAL base, REAL exp)
{
  REAL z, g, R, v, u2, u1, w1, w2, y1, y2, w;
  INTEGER m, p, i, mp, pp, iw1;
  if (__ABS(exp) < 5.5626846462680078e-309) {
    return (REAL)1;
  } else if (base < (REAL)0) {
    (*Math_ErrorHandler)(4);
    return (-8.9884656743115738e+307 * 2);
  } else if (__ABS(base) < 5.5626846462680078e-309) {
    if (exp > (REAL)0) {
      return (REAL)0;
    } else {
      (*Math_ErrorHandler)(3);
      return (-8.9884656743115738e+307 * 2);
    }
  }
  g = MathL_fraction(base) * 0.5;
  m = MathL_exponent(base) + 1;
  p = 1;
  if (g <= MathL_a1[9]) {
    p = 9;
  }
  if (g <= MathL_a1[__X(p + 4, 18, (CHAR*)"MathL", 112934)]) {
    p += 4;
  }
  if (g <= MathL_a1[__X(p + 2, 18, (CHAR*)"MathL", 113190)]) {
    p += 2;
  }
  z = ((g - MathL_a1[__X(p + 1, 18, (CHAR*)"MathL", 113976)]) - MathL_a2[__X(__ASHR(p + 1, 1, INTEGER), 9, (CHAR*)"MathL", 113976)]) / (REAL)(g + MathL_a1[__X(p + 1, 18, (CHAR*)"MathL", 113976)]);
  z = z + z;
  v = z * z;
  R = ((((4.3445775672163118e-4 * v + 0.0022321421285924262) * v + 0.012500000000503799) * v + 0.083333333333333212) * v) * z;
  R = R + 0.44269504088896347 * R;
  u2 = (R + z * 0.44269504088896347) + z;
  u1 = (REAL)(__ASHL(m, 4, INTEGER) - p) * 0.0625;
  y1 = (REAL)(__ENTIERL((REAL)16 * exp)) * 0.0625;
  y2 = exp - y1;
  w = u2 * exp + u1 * y2;
  w1 = (REAL)(__ENTIERL((REAL)16 * w)) * 0.0625;
  w2 = w - w1;
  w = w1 + u1 * y1;
  w1 = (REAL)(__ENTIERL((REAL)16 * w)) * 0.0625;
  w2 = w2 + (w - w1);
  w = (REAL)(__ENTIERL((REAL)16 * w2)) * 0.0625;
  iw1 = (INTEGER)__ENTIER((REAL)16 * (w + w1));
  w2 = w2 - w;
  if (iw1 > 16367) {
    (*Math_ErrorHandler)(3);
    return (8.9884656743115738e+307 * 2);
  } else if (iw1 < -16351) {
    return (REAL)0;
  }
  if (w2 > (REAL)0) {
    iw1 += 1;
    w2 = w2 - 0.0625;
  }
  if (iw1 < 0) {
    i = 0;
  } else {
    i = 1;
  }
  mp = MathL_div(iw1, 16) + i;
  pp = __ASHL(mp, 4, INTEGER) - iw1;
  z = ((((((1.492885268059561e-5 * w2 + 1.5400290440989766e-4) * w2 + 0.0013333541313585783) * w2 + 0.0096181290595172413) * w2 + 0.055504108664085595) * w2 + 0.24022650695909538) * w2 + 0.69314718055994524) * w2;
  z = MathL_a1[__X(pp + 1, 18, (CHAR*)"MathL", 118888)] + MathL_a1[__X(pp + 1, 18, (CHAR*)"MathL", 118888)] * z;
  return MathL_scale(z, (SHORTINT)mp);
}

/*----------------------------------------------------------------------------*/
INTEGER MathL_round (REAL x)
{
  if (x < (REAL)0) {
    return -((INTEGER)__ENTIER(0.5 - x));
  } else {
    return (INTEGER)__ENTIER(x + 0.5);
  }
  __RETCHK((CHAR*)"MathL", 121087);
}

/*----------------------------------------------------------------------------*/
BOOLEAN MathL_IsRMathException (void)
{
  return 0;
}

/*----------------------------------------------------------------------------*/
REAL MathL_log (REAL x, REAL base)
{
  if (base <= (REAL)0) {
    (*Math_ErrorHandler)(5);
    return (-8.9884656743115738e+307 * 2);
  } else {
    return MathL_ln(x) / MathL_ln(base);
  }
  __RETCHK((CHAR*)"MathL", 127487);
}

/*----------------------------------------------------------------------------*/
static struct ipower__16 {
  REAL *x;
  SHORTINT *base;
  struct ipower__16 *lnk;
} *ipower__16_s;

static REAL __17 (REAL xadj);

static REAL __17 (REAL xadj)
{
  if ((*ipower__16_s->x) < (REAL)0 && __ODD((*ipower__16_s->base))) {
    return -xadj;
  } else {
    return xadj;
  }
  __RETCHK((CHAR*)"MathL", 129854);
}

REAL MathL_ipower (REAL x, SHORTINT base)
{
  REAL y;
  BOOLEAN neg;
  INTEGER Exp;
  struct ipower__16 _s;
  REAL __retval;
  _s.x = &x;
  _s.base = &base;
  _s.lnk = ipower__16_s;
  ipower__16_s = &_s;
  if ((INTEGER)base == 0) {
    __retval = (REAL)1;
    ipower__16_s = _s.lnk;
    ;
    return __retval;
  } else if (__ABS(x) < 5.5626846462680078e-309) {
    if ((INTEGER)base > 0) {
      __retval = (REAL)0;
      ipower__16_s = _s.lnk;
      ;
      return __retval;
    } else {
      (*Math_ErrorHandler)(3);
      __retval = __17((8.9884656743115738e+307 * 2));
      ipower__16_s = _s.lnk;
      ;
      return __retval;
    }
  }
  Exp = (MathL_exponent(x) + 1) * (INTEGER)base;
  y = MathL_LnInfinity * 1.4426950408889634;
  if ((REAL)Exp > y) {
    (*Math_ErrorHandler)(3);
    __retval = __17((8.9884656743115738e+307 * 2));
    ipower__16_s = _s.lnk;
    ;
    return __retval;
  } else if ((REAL)Exp < -y) {
    __retval = (REAL)0;
    ipower__16_s = _s.lnk;
    ;
    return __retval;
  }
  y = (REAL)1;
  if ((INTEGER)base < 0) {
    neg = 1;
    base = (SHORTINT)(-((INTEGER)base));
  } else {
    neg = 0;
  }
  for (;;) {
    if (__ODD(base)) {
      y = y * x;
    }
    base = (SHORTINT)__ASHR((INTEGER)base, 1, INTEGER);
    if ((INTEGER)base == 0) {
      break;
    }
    x = x * x;
  }
  if (neg) {
    __retval = (REAL)1 / y;
    ipower__16_s = _s.lnk;
    ;
    return __retval;
  } else {
    __retval = y;
    ipower__16_s = _s.lnk;
    ;
    return __retval;
  }
  __RETCHK((CHAR*)"MathL", 135976);
}

/*----------------------------------------------------------------------------*/
void MathL_sincos (REAL x, REAL *Sin, REAL *Cos)
{
  *Sin = MathL_sin(x);
  *Cos = MathL_sqrt((REAL)1 - *Sin * *Sin);
}

/*----------------------------------------------------------------------------*/
REAL MathL_arctan2 (REAL xn, REAL xd)
{
  REAL atan, z, z2, p, q;
  INTEGER xnExp, xdExp;
  BYTE Quadrant;
  if (__ABS(xd) < 5.5626846462680078e-309) {
    if (__ABS(xn) < 5.5626846462680078e-309) {
      (*Math_ErrorHandler)(7);
      atan = (REAL)0;
    } else {
      (*Math_ErrorHandler)(3);
      atan = 1.5707963267948965;
    }
  } else {
    xnExp = MathL_exponent(xn);
    xdExp = MathL_exponent(xd);
    if (xnExp - xdExp >= 1020) {
      (*Math_ErrorHandler)(3);
      atan = 1.5707963267948965;
    } else if (xnExp - xdExp < -1019) {
      atan = (REAL)0;
    } else {
      if (__ABS(xn) > __ABS(xd)) {
        z = __ABS(xd / xn);
        Quadrant = 2;
      } else {
        z = __ABS(xn / xd);
        Quadrant = 0;
      }
      if (z > 0.26794919243112281) {
        z = (z * 1.7320508075688772 - (REAL)1) / (REAL)(1.7320508075688772 + z);
        Quadrant += 1;
      }
      if (__ABS(z) < 1.0536712e-8) {
        atan = z;
      } else {
        z2 = z * z;
        p = (((12.88838303415728 * z2 + 132.70239816397675) * z2 + 322.6620700132512) * z2 + 216.06230789724254) * z;
        q = (((z2 + 38.501486508351195) * z2 + 221.05088302841768) * z2 + 394.68283931228297) * z2 + 216.06230789724264;
        atan = p / q;
      }
      if ((INTEGER)Quadrant > 1) {
        atan = -atan;
      }
      switch (Quadrant) {
        case 1: 
          atan = atan + 0.52359877559829886;
          break;
        case 2: 
          atan = atan + 1.5707963267948965;
          break;
        case 3: 
          atan = atan + 1.0471975511965977;
          break;
        default: 
          break;
      }
    }
    if (xd < (REAL)0) {
      atan = 3.1415926535897929 - atan;
    }
  }
  if (xn < (REAL)0) {
    atan = -atan;
  }
  return atan;
}

/*----------------------------------------------------------------------------*/
REAL MathL_sinh (REAL x)
{
  REAL y, f, p, q;
  y = __ABS(x);
  if (y <= (REAL)1) {
    if (y < 1.0536712e-8) {
      return x;
    }
    f = y * y;
    p = ((-0.78966127417357097 * f + -163.75798202630749) * f + -11563.521196851768) * f + -351812.8343017712;
    q = ((f + -277.73523119650702) * f + 36162.723109421836) * f + -2110877.0058106275;
    y = f * (p / q);
    return x + x * y;
  } else if (y > MathL_LnInfinity) {
    y = y - 0.6931610107421875;
    if (y > (MathL_LnInfinity - 0.6931610107421875) + 0.69) {
      (*Math_ErrorHandler)(3);
      if (x > (REAL)0) {
        return (8.9884656743115738e+307 * 2);
      } else {
        return (-8.9884656743115738e+307 * 2);
      }
    } else {
      f = MathL_exp(y);
      f = f + f * 1.3830277879601904e-5;
    }
  } else {
    f = MathL_exp(y);
    f = (f - (REAL)1 / f) * 0.5;
  }
  if (x > (REAL)0) {
    return f;
  } else {
    return -f;
  }
  __RETCHK((CHAR*)"MathL", 157994);
}

/*----------------------------------------------------------------------------*/
REAL MathL_cosh (REAL x)
{
  REAL y, f;
  y = __ABS(x);
  if (y > MathL_LnInfinity) {
    y = y - 0.6931610107421875;
    if (y > (MathL_LnInfinity - 0.6931610107421875) + 0.69) {
      (*Math_ErrorHandler)(3);
      if (x > (REAL)0) {
        return (8.9884656743115738e+307 * 2);
      } else {
        return (-8.9884656743115738e+307 * 2);
      }
    } else {
      f = MathL_exp(y);
      return f + f * 1.3830277879601904e-5;
    }
  } else {
    f = MathL_exp(y);
    return (f + (REAL)1 / f) * 0.5;
  }
  __RETCHK((CHAR*)"MathL", 161791);
}

/*----------------------------------------------------------------------------*/
REAL MathL_tanh (REAL x)
{
  REAL f, t;
  f = __ABS(x);
  if (f > 19.06154747) {
    t = (REAL)1;
  } else if (f > 0.54930614433405492) {
    t = (REAL)1 - (REAL)2 / (REAL)(MathL_exp((REAL)2 * f) + (REAL)1);
  } else if (f < 1.0536712e-8) {
    t = f;
  } else {
    t = f * f;
    t = t * (((-0.96437492777225475 * t + -99.225929672236089) * t + -1613.4119023996227) / (REAL)(((t + 112.7447438053495) * t + 2233.7720718962314) * t + 4840.2357071988689));
    t = f + f * t;
  }
  if (x < (REAL)0) {
    return -t;
  } else {
    return t;
  }
  __RETCHK((CHAR*)"MathL", 166442);
}

/*----------------------------------------------------------------------------*/
REAL MathL_arcsinh (REAL x)
{
  if (__ABS(x) > MathL_SqrtInfinity * 0.5) {
    (*Math_ErrorHandler)(8);
    if (x > (REAL)0) {
      return MathL_ln(MathL_SqrtInfinity);
    } else {
      return -MathL_ln(MathL_SqrtInfinity);
    }
  } else if (x < (REAL)0) {
    return -MathL_ln(-x + MathL_sqrt(x * x + (REAL)1));
  } else {
    return MathL_ln(x + MathL_sqrt(x * x + (REAL)1));
  }
  __RETCHK((CHAR*)"MathL", 168959);
}

/*----------------------------------------------------------------------------*/
REAL MathL_arccosh (REAL x)
{
  if (x < (REAL)1) {
    (*Math_ErrorHandler)(9);
    return (REAL)0;
  } else if (x > MathL_SqrtInfinity * 0.5) {
    (*Math_ErrorHandler)(8);
    return MathL_ln(MathL_SqrtInfinity);
  } else {
    return MathL_ln(x + MathL_sqrt(x * x - (REAL)1));
  }
  __RETCHK((CHAR*)"MathL", 171519);
}

/*----------------------------------------------------------------------------*/
REAL MathL_arctanh (REAL x)
{
  REAL t;
  t = __ABS(x);
  if (t >= (REAL)1 || t > (REAL)1 - (REAL)2 * MathL_em) {
    (*Math_ErrorHandler)(9);
    if (x < (REAL)0) {
      return -MathL_TanhMax;
    } else {
      return MathL_TanhMax;
    }
  } else if (t > 0.99998499100000004) {
    (*Math_ErrorHandler)(10);
  }
  return MathL_arcsinh(x / MathL_sqrt((REAL)1 - x * x));
}

/*----------------------------------------------------------------------------*/

export void *MathL__init (void)
{
  __DEFMOD;
  __IMPORT(Math__init);
  __REGMOD("MathL", 0);
/* BEGIN */
  MathL_INF = __VALR((LONGINT)9218868437227405312LL);
  MathL_em = MathL_ulp((REAL)1);
  MathL_LnInfinity = MathL_ln((8.9884656743115738e+307 * 2));
  MathL_LnSmall = MathL_ln(5.5626846462680078e-309);
  MathL_SqrtInfinity = MathL_sqrt((8.9884656743115738e+307 * 2));
  MathL_t = MathL_pred((REAL)1) / MathL_sqrt(MathL_em);
  MathL_TanhMax = MathL_ln(MathL_t + MathL_sqrt(MathL_t * MathL_t + (REAL)1));
  MathL_a1[1] = (REAL)1;
  MathL_a1[2] = __VALR((LONGINT)4606800543101522138LL);
  MathL_a1[3] = __VALR((LONGINT)4606434857679824007LL);
  MathL_a1[4] = __VALR((LONGINT)4606084676120302236LL);
  MathL_a1[5] = __VALR((LONGINT)4605749341110064045LL);
  MathL_a1[6] = __VALR((LONGINT)4605428223204126864LL);
  MathL_a1[7] = __VALR((LONGINT)4605120719643910363LL);
  MathL_a1[8] = __VALR((LONGINT)4604826253225820550LL);
  MathL_a1[9] = __VALR((LONGINT)4604544271217802188LL);
  MathL_a1[10] = __VALR((LONGINT)4604274244321825833LL);
  MathL_a1[11] = __VALR((LONGINT)4604015665680362023LL);
  MathL_a1[12] = __VALR((LONGINT)4603768049924977698LL);
  MathL_a1[13] = __VALR((LONGINT)4603530932265269013LL);
  MathL_a1[14] = __VALR((LONGINT)4603303867616420408LL);
  MathL_a1[15] = __VALR((LONGINT)4603086429763752314LL);
  MathL_a1[16] = __VALR((LONGINT)4602878210562689295LL);
  MathL_a1[17] = 0.5;
  MathL_a2[1] = __VALR((LONGINT)4364183676631777280LL);
  MathL_a2[2] = __VALR((LONGINT)4355280342925443072LL);
  MathL_a2[3] = __VALR((LONGINT)4353991582810112000LL);
  MathL_a2[4] = __VALR((LONGINT)4367078362456195072LL);
  MathL_a2[5] = __VALR((LONGINT)4361228591242280960LL);
  MathL_a2[6] = __VALR((LONGINT)4358035321924878336LL);
  MathL_a2[7] = __VALR((LONGINT)4362211772363964416LL);
  MathL_a2[8] = __VALR((LONGINT)4361918956862963712LL);
  __ENDMOD;
}
