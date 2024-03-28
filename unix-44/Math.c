/* Ofront+ 1.0 -sC -44 */
#include "SYSTEM.oh"


export void (*Math_ErrorHandler)(SHORTINT);
export SHORTINT Math_err;
static SHORTREAL Math_a1[18];
static SHORTREAL Math_a2[9];
static SHORTREAL Math_em, Math_LnInfinity, Math_LnSmall, Math_SqrtInfinity, Math_TanhMax, Math_t;


export void Math_ClearError (void);
static void Math_DefaultErrorHandler (SHORTINT errno);
export BOOLEAN Math_IsRMathException (void);
static SHORTREAL Math_SinCos (SHORTREAL x, SHORTREAL y, SHORTREAL sign);
export SHORTREAL Math_arccos (SHORTREAL x);
export SHORTREAL Math_arccosh (SHORTREAL x);
export SHORTREAL Math_arcsin (SHORTREAL x);
export SHORTREAL Math_arcsinh (SHORTREAL x);
export SHORTREAL Math_arctan (SHORTREAL x);
export SHORTREAL Math_arctan2 (SHORTREAL xn, SHORTREAL xd);
export SHORTREAL Math_arctanh (SHORTREAL x);
static void Math_asincos (SHORTREAL x, INTEGER flag, INTEGER *i, SHORTREAL *res);
static SHORTREAL Math_atan (SHORTREAL f);
export SHORTREAL Math_cos (SHORTREAL x);
export SHORTREAL Math_cosh (SHORTREAL x);
static INTEGER Math_div (INTEGER x, INTEGER y);
export SHORTREAL Math_exp (SHORTREAL x);
export SHORTINT Math_exponent (SHORTREAL x);
export SHORTREAL Math_fraction (SHORTREAL x);
export SHORTREAL Math_ipower (SHORTREAL x, SHORTINT base);
export SHORTREAL Math_ln (SHORTREAL x);
export SHORTREAL Math_log (SHORTREAL x, SHORTREAL base);
export SHORTREAL Math_power (SHORTREAL base, SHORTREAL exp);
export SHORTREAL Math_pred (SHORTREAL x);
export INTEGER Math_round (SHORTREAL x);
export SHORTREAL Math_scale (SHORTREAL x, SHORTINT n);
export SHORTREAL Math_sign (SHORTREAL x);
export SHORTREAL Math_sin (SHORTREAL x);
export void Math_sincos (SHORTREAL x, SHORTREAL *Sin, SHORTREAL *Cos);
export SHORTREAL Math_sinh (SHORTREAL x);
export SHORTREAL Math_sqrt (SHORTREAL x);
export SHORTREAL Math_succ (SHORTREAL x);
export SHORTREAL Math_tan (SHORTREAL x);
export SHORTREAL Math_tanh (SHORTREAL x);
export SHORTREAL Math_ulp (SHORTREAL x);


/*============================================================================*/

static void Math_DefaultErrorHandler (SHORTINT errno)
{
  Math_err = errno;
}

void Math_ClearError (void)
{
  Math_err = 0;
}

/*----------------------------------------------------------------------------*/
SHORTREAL Math_fraction (SHORTREAL x)
{
  SET s;
  if (x == (SHORTREAL)0) {
    return (REAL)0;
  } else {
    s = (__VAL(SET, x) & 0x807fffff) | 0x3f000000;
    return __VAL(SHORTREAL, s) * (SHORTREAL)2;
  }
  __RETCHK((CHAR*)"Math", 39209);
}

/*----------------------------------------------------------------------------*/
SHORTINT Math_exponent (SHORTREAL x)
{
  if (x == (SHORTREAL)0) {
    return 0;
  } else {
    return (SHORTINT)(__MASK(__LSHR(__VAL(INTEGER, x), 23, INTEGER), -256) - 127);
  }
  __RETCHK((CHAR*)"Math", 42751);
}

/*----------------------------------------------------------------------------*/
SHORTREAL Math_sign (SHORTREAL x)
{
  if (x < (SHORTREAL)0) {
    return (REAL)-1;
  } else {
    return (REAL)1;
  }
  __RETCHK((CHAR*)"Math", 45358);
}

/*----------------------------------------------------------------------------*/
SHORTREAL Math_scale (SHORTREAL x, SHORTINT n)
{
  INTEGER exp;
  SET lexp;
  if (x == (SHORTREAL)0) {
    return (REAL)0;
  }
  exp = (INTEGER)Math_exponent(x) + (INTEGER)n;
  if (exp > 127) {
    return 3.4028235e+38 * Math_sign(x);
  } else if (exp < -126) {
    return 1.1754944e-38 * Math_sign(x);
  }
  lexp = (__VAL(SET, x) & 0x807fffff) | (SET)__LSHL(exp + 127, 23, INTEGER);
  return __VAL(SHORTREAL, lexp);
}

/*----------------------------------------------------------------------------*/
SHORTREAL Math_ulp (SHORTREAL x)
{
  return Math_scale((REAL)1, (SHORTINT)(((INTEGER)Math_exponent(x) - 24) + 1));
}

/*----------------------------------------------------------------------------*/
SHORTREAL Math_succ (SHORTREAL x)
{
  return x + Math_ulp(x) * Math_sign(x);
}

/*----------------------------------------------------------------------------*/
SHORTREAL Math_pred (SHORTREAL x)
{
  return x - Math_ulp(x) * Math_sign(x);
}

/*----------------------------------------------------------------------------*/
static SHORTREAL Math_SinCos (SHORTREAL x, SHORTREAL y, SHORTREAL sign)
{
  INTEGER n;
  SHORTREAL xn, f, g;
  if (y >= (SHORTREAL)9099) {
    (*Math_ErrorHandler)(10);
    return (REAL)0;
  }
  n = (INTEGER)__ENTIER(y * 0.31830987 + 0.5);
  xn = n;
  if (__ODD(n)) {
    sign = -sign;
  }
  x = __ABS(x);
  if (x != y) {
    xn = xn - 0.5;
  }
  f = (SHORTREAL)(__ABS((REAL)x) - (REAL)xn * 3.1415926535897929);
  if (__ABS(f) < 2.4414062e-4) {
    return sign * f;
  }
  g = f * f;
  g = (((2.6019031e-6 * g + -1.9807418e-4) * g + 0.0083330255) * g + -0.16666657) * g;
  g = f + f * g;
  return sign * g;
}

static INTEGER Math_div (INTEGER x, INTEGER y)
{
  if (x < 0) {
    return -__DIVF(__ABS(x), y);
  } else {
    return __DIVF(x, y);
  }
  __RETCHK((CHAR*)"Math", 68095);
}

INTEGER Math_round (SHORTREAL x)
{
  if (x < (SHORTREAL)0) {
    return -((INTEGER)__ENTIER(0.5 - x));
  } else {
    return (INTEGER)__ENTIER(x + 0.5);
  }
  __RETCHK((CHAR*)"Math", 71423);
}

/*----------------------------------------------------------------------------*/
SHORTREAL Math_sqrt (SHORTREAL x)
{
  SHORTREAL xMant, yEst, z;
  SHORTINT xExp;
  if (x == (SHORTREAL)0) {
    return (REAL)0;
  }
  if (x < (SHORTREAL)0) {
    (*Math_ErrorHandler)(1);
    x = -x;
  }
  xMant = Math_fraction(x) * 0.5;
  xExp = (SHORTINT)((INTEGER)Math_exponent(x) + 1);
  yEst = 0.41731 + 0.59016001 * xMant;
  z = yEst + xMant / yEst;
  yEst = 0.25 * z + xMant / z;
  if (__ODD(xExp)) {
    yEst = yEst * 0.70710677;
    xExp += 1;
  }
  return Math_scale(yEst, (SHORTINT)__ASHR((INTEGER)xExp, 1, INTEGER));
}

/*----------------------------------------------------------------------------*/
SHORTREAL Math_exp (SHORTREAL x)
{
  SHORTREAL xn, g, p, q, z;
  INTEGER n;
  if (x >= Math_LnInfinity) {
    (*Math_ErrorHandler)(3);
    return 3.4028235e+38;
  } else if (x < Math_LnSmall) {
    (*Math_ErrorHandler)(11);
    return (REAL)0;
  } else if (__ABS(x) < 2.9802322e-8) {
    return (REAL)1;
  }
  n = Math_round(1.442695 * x);
  xn = n;
  g = (SHORTREAL)((REAL)x - (REAL)xn * 0.69314718055994524);
  z = g * g;
  p = (0.0041602887 * z + 0.25) * g;
  q = 0.049987178 * z + 0.5;
  return Math_scale(0.5 + p / (SHORTREAL)(q - p), (SHORTINT)(n + 1));
}

/*----------------------------------------------------------------------------*/
SHORTREAL Math_ln (SHORTREAL x)
{
  SHORTREAL f, zn, zd, r, z, w, xn;
  SHORTINT n;
  if (x <= (SHORTREAL)0) {
    (*Math_ErrorHandler)(2);
    return -3.4028235e+38;
  }
  f = Math_fraction(x) * 0.5;
  n = (SHORTINT)((INTEGER)Math_exponent(x) + 1);
  if (f > 0.70710677) {
    zn = (f - 0.5) - 0.5;
    zd = f * 0.5 + 0.5;
  } else {
    zn = f - 0.5;
    zd = zn * 0.5 + 0.5;
    n -= 1;
  }
  z = zn / zd;
  w = z * z;
  r = z + z * ((w * -0.55270749) / (SHORTREAL)(w + -6.6327181));
  xn = n;
  return (xn * -2.1219444e-4 + r) + xn * 0.69335937;
}

/*----------------------------------------------------------------------------*/
SHORTREAL Math_sin (SHORTREAL x)
{
  if (x < (SHORTREAL)0) {
    return Math_SinCos(x, -x, (REAL)-1);
  } else {
    return Math_SinCos(x, x, (REAL)1);
  }
  __RETCHK((CHAR*)"Math", 92671);
}

/*----------------------------------------------------------------------------*/
SHORTREAL Math_cos (SHORTREAL x)
{
  return Math_SinCos(x, __ABS(x) + 1.5707964, (REAL)1);
}

/*----------------------------------------------------------------------------*/
SHORTREAL Math_tan (SHORTREAL x)
{
  INTEGER n;
  SHORTREAL y, xn, f, xnum, xden, g;
  y = __ABS(x);
  if (y > (SHORTREAL)6434) {
    (*Math_ErrorHandler)(10);
    return (REAL)0;
  }
  n = Math_round(x * 0.63661975);
  xn = n;
  f = (SHORTREAL)((REAL)x - (REAL)xn * 1.5707963267948965);
  if (__ABS(f) < 2.4414062e-4) {
    xnum = f;
    xden = (REAL)1;
  } else {
    g = f * f;
    xnum = (-0.095801771 * g) * f + f;
    xden = ((0.0097168582 * g + -0.42913577) * g + 0.5) + 0.5;
  }
  if (__ODD(n)) {
    return xden / (SHORTREAL)-xnum;
  } else {
    return xnum / xden;
  }
  __RETCHK((CHAR*)"Math", 101631);
}

/*----------------------------------------------------------------------------*/
static void Math_asincos (SHORTREAL x, INTEGER flag, INTEGER *i, SHORTREAL *res)
{
  SHORTREAL y, g, r;
  y = __ABS(x);
  if (y > 0.5) {
    *i = 1 - flag;
    if (y > (SHORTREAL)1) {
      (*Math_ErrorHandler)(7);
      *res = 3.4028235e+38;
      return;
    }
    g = ((SHORTREAL)1 - y) * 0.5;
    r = -Math_sqrt(g);
    y = r + r;
    r = ((-0.50440055 * g + 0.93393582) * g) / (SHORTREAL)((g + -5.5484672) * g + 5.6036301);
    *res = y + y * r;
  } else {
    *i = flag;
    if (y < 2.4414062e-4) {
      *res = y;
    } else {
      g = y * y;
      g = ((-0.50440055 * g + 0.93393582) * g) / (SHORTREAL)((g + -5.5484672) * g + 5.6036301);
      *res = y + y * g;
    }
  }
}

SHORTREAL Math_arcsin (SHORTREAL x)
{
  SHORTREAL res;
  INTEGER i;
  Math_asincos(x, 0, &i, &res);
  if ((INTEGER)Math_err != 0) {
    return res;
  }
  if (i == 1) {
    res = 0.78539819 + (0.78539819 + res);
  }
  if (x < (SHORTREAL)0) {
    res = -res;
  }
  return res;
}

/*----------------------------------------------------------------------------*/
SHORTREAL Math_arccos (SHORTREAL x)
{
  SHORTREAL res;
  INTEGER i;
  Math_asincos(x, 1, &i, &res);
  if ((INTEGER)Math_err != 0) {
    return res;
  }
  if (x < (SHORTREAL)0) {
    if (i == 0) {
      res = 1.5707964 + (1.5707964 + res);
    } else {
      res = 0.78539819 + (0.78539819 + res);
    }
  } else {
    if (i == 1) {
      res = 0.78539819 + (0.78539819 - res);
    } else {
      res = -res;
    }
  }
  return res;
}

/*----------------------------------------------------------------------------*/
static SHORTREAL Math_atan (SHORTREAL f)
{
  INTEGER n;
  SHORTREAL res, g;
  if (f > (SHORTREAL)1) {
    f = (SHORTREAL)1 / f;
    n = 2;
  } else {
    n = 0;
  }
  if (f > 0.26794919) {
    f = (((0.73205084 * f - 0.5) - 0.5) + f) / (SHORTREAL)(1.7320508 + f);
    n += 1;
  }
  if (__ABS(f) < 2.4414062e-4) {
    res = f;
  } else {
    g = f * f;
    res = ((-0.050909583 * g + -0.47083253) * g) / (SHORTREAL)(g + 1.4125007);
    res = f + f * res;
  }
  if (n > 1) {
    res = -res;
  }
  switch (n) {
    case 1: 
      res = res + 0.52359879;
      break;
    case 2: 
      res = res + 1.5707964;
      break;
    case 3: 
      res = res + 1.0471976;
      break;
    default: 
      break;
  }
  return res;
}

SHORTREAL Math_arctan (SHORTREAL x)
{
  if (x < (SHORTREAL)0) {
    return -Math_atan(-x);
  } else {
    return Math_atan(x);
  }
  __RETCHK((CHAR*)"Math", 129279);
}

/*----------------------------------------------------------------------------*/
SHORTREAL Math_power (SHORTREAL base, SHORTREAL exp)
{
  SHORTREAL z, g, R, v, u2, u1, w1, w2;
  REAL w;
  SHORTINT m, p, i;
  INTEGER mp, pp, iw1;
  if (base <= (SHORTREAL)0) {
    if (base != (SHORTREAL)0) {
      (*Math_ErrorHandler)(4);
      base = -base;
    } else if (exp > (SHORTREAL)0) {
      return (REAL)0;
    } else {
      (*Math_ErrorHandler)(4);
      return 3.4028235e+38;
    }
  }
  g = Math_fraction(base) * 0.5;
  m = (SHORTINT)((INTEGER)Math_exponent(base) + 1);
  p = 1;
  if (g <= Math_a1[9]) {
    p = 9;
  }
  if (g <= Math_a1[__X((INTEGER)p + 4, 18, (CHAR*)"Math", 136742)]) {
    p += 4;
  }
  if (g <= Math_a1[__X((INTEGER)p + 2, 18, (CHAR*)"Math", 136998)]) {
    p += 2;
  }
  z = ((g - Math_a1[__X((INTEGER)p + 1, 18, (CHAR*)"Math", 137788)]) - Math_a2[__X(__ASHR((INTEGER)p + 1, 1, INTEGER), 9, (CHAR*)"Math", 137788)]) / (SHORTREAL)(g + Math_a1[__X((INTEGER)p + 1, 18, (CHAR*)"Math", 137788)]);
  z = z + z;
  v = z * z;
  R = (0.083357543 * v) * z;
  R = R + 0.44269505 * R;
  u2 = (R + z * 0.44269505) + z;
  u1 = (SHORTREAL)(__ASHL((INTEGER)m, 4, INTEGER) - (INTEGER)p) * 0.0625;
  w = (REAL)exp * ((REAL)u1 + (REAL)u2);
  iw1 = (INTEGER)__ENTIER((REAL)16 * w);
  w1 = (SHORTREAL)iw1 * 0.0625;
  w2 = (SHORTREAL)(w - (REAL)w1);
  if (iw1 > 2047) {
    (*Math_ErrorHandler)(3);
    return 3.4028235e+38;
  } else if (iw1 < -2016) {
    (*Math_ErrorHandler)(11);
    return (REAL)0;
  }
  if (w2 > (SHORTREAL)0) {
    iw1 += 1;
    w2 = w2 - 0.0625;
  }
  if (iw1 < 0) {
    i = 0;
  } else {
    i = 1;
  }
  mp = Math_div(iw1, 16) + (INTEGER)i;
  pp = __ASHL(mp, 4, INTEGER) - iw1;
  z = ((0.054360382 * w2 + 0.2401851) * w2 + 0.69314677) * w2;
  z = Math_a1[__X(pp + 1, 18, (CHAR*)"Math", 142626)] + Math_a1[__X(pp + 1, 18, (CHAR*)"Math", 142626)] * z;
  return Math_scale(z, (SHORTINT)mp);
}

/*----------------------------------------------------------------------------*/
BOOLEAN Math_IsRMathException (void)
{
  return 0;
}

/*----------------------------------------------------------------------------*/
SHORTREAL Math_log (SHORTREAL x, SHORTREAL base)
{
  if (base <= (SHORTREAL)0) {
    (*Math_ErrorHandler)(5);
    return -3.4028235e+38;
  } else {
    return Math_ln(x) / Math_ln(base);
  }
  __RETCHK((CHAR*)"Math", 149247);
}

/*----------------------------------------------------------------------------*/
static struct ipower__20 {
  SHORTREAL *x;
  SHORTINT *base;
  struct ipower__20 *lnk;
} *ipower__20_s;

static SHORTREAL __21 (SHORTREAL xadj);

static SHORTREAL __21 (SHORTREAL xadj)
{
  if ((*ipower__20_s->x) < (SHORTREAL)0 && __ODD((*ipower__20_s->base))) {
    return -xadj;
  } else {
    return xadj;
  }
  __RETCHK((CHAR*)"Math", 151614);
}

SHORTREAL Math_ipower (SHORTREAL x, SHORTINT base)
{
  SHORTINT Exp;
  SHORTREAL y;
  BOOLEAN neg;
  struct ipower__20 _s;
  SHORTREAL __retval;
  _s.x = &x;
  _s.base = &base;
  _s.lnk = ipower__20_s;
  ipower__20_s = &_s;
  if ((INTEGER)base == 0) {
    __retval = (REAL)1;
    ipower__20_s = _s.lnk;
    ;
    return __retval;
  } else if (__ABS(x) < 2.9387359e-39) {
    if ((INTEGER)base > 0) {
      __retval = (REAL)0;
      ipower__20_s = _s.lnk;
      ;
      return __retval;
    } else {
      (*Math_ErrorHandler)(3);
      __retval = __21(3.4028235e+38);
      ipower__20_s = _s.lnk;
      ;
      return __retval;
    }
  }
  Exp = (SHORTINT)(((INTEGER)Math_exponent(x) + 1) * (INTEGER)base);
  y = Math_LnInfinity * 1.442695;
  if ((SHORTREAL)Exp > y) {
    (*Math_ErrorHandler)(3);
    __retval = __21(3.4028235e+38);
    ipower__20_s = _s.lnk;
    ;
    return __retval;
  } else if ((SHORTREAL)Exp < -y) {
    __retval = (REAL)0;
    ipower__20_s = _s.lnk;
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
    __retval = (SHORTREAL)1 / y;
    ipower__20_s = _s.lnk;
    ;
    return __retval;
  } else {
    __retval = y;
    ipower__20_s = _s.lnk;
    ;
    return __retval;
  }
  __RETCHK((CHAR*)"Math", 157736);
}

/*----------------------------------------------------------------------------*/
void Math_sincos (SHORTREAL x, SHORTREAL *Sin, SHORTREAL *Cos)
{
  *Sin = Math_sin(x);
  *Cos = Math_sqrt((SHORTREAL)1 - *Sin * *Sin);
}

/*----------------------------------------------------------------------------*/
SHORTREAL Math_arctan2 (SHORTREAL xn, SHORTREAL xd)
{
  SHORTREAL res;
  INTEGER xpdiff;
  if (xd == (SHORTREAL)0) {
    if (xn == (SHORTREAL)0) {
      (*Math_ErrorHandler)(6);
      return (REAL)0;
    } else if (xn < (SHORTREAL)0) {
      return -1.5707963267948965;
    } else {
      return 1.5707963267948965;
    }
  } else {
    xpdiff = (INTEGER)Math_exponent(xn) - (INTEGER)Math_exponent(xd);
    if (__ABS(xpdiff) >= 124) {
      if (xn < (SHORTREAL)0) {
        return -1.5707963267948965;
      } else {
        return 1.5707963267948965;
      }
    } else {
      res = __ABS(xn / xd);
      if (res != (SHORTREAL)0) {
        res = Math_atan(res);
      }
      if (xd < (SHORTREAL)0) {
        res = 3.1415927 - res;
      }
      if (xn < (SHORTREAL)0) {
        return -res;
      } else {
        return res;
      }
    }
  }
  __RETCHK((CHAR*)"Math", 166655);
}

/*----------------------------------------------------------------------------*/
SHORTREAL Math_sinh (SHORTREAL x)
{
  SHORTREAL y, f;
  y = __ABS(x);
  if (y <= (SHORTREAL)1) {
    if (y < 2.4414062e-4) {
      return x;
    }
    f = y * y;
    y = f * ((f * -0.1903334 + -7.1379318) / (SHORTREAL)(f + -42.827709));
    return x + x * y;
  } else if (y > Math_LnInfinity) {
    y = y - 0.69316101;
    if (y > (Math_LnInfinity - 0.69316101) + 0.69) {
      (*Math_ErrorHandler)(3);
      if (x > (SHORTREAL)0) {
        return 3.4028235e+38;
      } else {
        return -3.4028235e+38;
      }
    } else {
      f = Math_exp(y);
      f = f + f * 1.3830278e-5;
    }
  } else {
    f = Math_exp(y);
    f = (f - (SHORTREAL)1 / f) * 0.5;
  }
  if (x > (SHORTREAL)0) {
    return f;
  } else {
    return -f;
  }
  __RETCHK((CHAR*)"Math", 173354);
}

/*----------------------------------------------------------------------------*/
SHORTREAL Math_cosh (SHORTREAL x)
{
  SHORTREAL y, f;
  y = __ABS(x);
  if (y > Math_LnInfinity) {
    y = y - 0.69316101;
    if (y > (Math_LnInfinity - 0.69316101) + 0.69) {
      (*Math_ErrorHandler)(3);
      if (x > (SHORTREAL)0) {
        return 3.4028235e+38;
      } else {
        return -3.4028235e+38;
      }
    } else {
      f = Math_exp(y);
      return f + f * 1.3830278e-5;
    }
  } else {
    f = Math_exp(y);
    return (f + (SHORTREAL)1 / f) * 0.5;
  }
  __RETCHK((CHAR*)"Math", 177151);
}

/*----------------------------------------------------------------------------*/
SHORTREAL Math_tanh (SHORTREAL x)
{
  SHORTREAL f, t;
  f = __ABS(x);
  if (f > 9.0109129) {
    t = (REAL)1;
  } else if (f > 0.54930615) {
    t = (SHORTREAL)1 - (SHORTREAL)2 / (SHORTREAL)(Math_exp((SHORTREAL)2 * f) + (SHORTREAL)1);
  } else if (f < 2.4414062e-4) {
    t = f;
  } else {
    t = f * f;
    t = (t * (-0.0038310108 * t + -0.82377279)) / (SHORTREAL)(t + 2.4713197);
    t = f + f * t;
  }
  if (x < (SHORTREAL)0) {
    return -t;
  } else {
    return t;
  }
  __RETCHK((CHAR*)"Math", 181034);
}

/*----------------------------------------------------------------------------*/
SHORTREAL Math_arcsinh (SHORTREAL x)
{
  if (__ABS(x) > Math_SqrtInfinity * 0.5) {
    (*Math_ErrorHandler)(8);
    if (x > (SHORTREAL)0) {
      return Math_ln(Math_SqrtInfinity);
    } else {
      return -Math_ln(Math_SqrtInfinity);
    }
  } else if (x < (SHORTREAL)0) {
    return -Math_ln(-x + Math_sqrt(x * x + (SHORTREAL)1));
  } else {
    return Math_ln(x + Math_sqrt(x * x + (SHORTREAL)1));
  }
  __RETCHK((CHAR*)"Math", 183551);
}

/*----------------------------------------------------------------------------*/
SHORTREAL Math_arccosh (SHORTREAL x)
{
  if (x < (SHORTREAL)1) {
    (*Math_ErrorHandler)(9);
    return (REAL)0;
  } else if (x > Math_SqrtInfinity * 0.5) {
    (*Math_ErrorHandler)(8);
    return Math_ln(Math_SqrtInfinity);
  } else {
    return Math_ln(x + Math_sqrt(x * x - (SHORTREAL)1));
  }
  __RETCHK((CHAR*)"Math", 186111);
}

/*----------------------------------------------------------------------------*/
SHORTREAL Math_arctanh (SHORTREAL x)
{
  SHORTREAL t;
  t = __ABS(x);
  if (t >= (SHORTREAL)1 || t > (SHORTREAL)1 - (SHORTREAL)2 * Math_em) {
    (*Math_ErrorHandler)(9);
    if (x < (SHORTREAL)0) {
      return -Math_TanhMax;
    } else {
      return Math_TanhMax;
    }
  } else if (t > 0.99998498) {
    (*Math_ErrorHandler)(10);
  }
  return Math_arcsinh(x / Math_sqrt((SHORTREAL)1 - x * x));
}

/*----------------------------------------------------------------------------*/

export void *Math__init (void)
{
  __DEFMOD;
  __REGMOD("Math", 0);
  __REGCMD("ClearError", Math_ClearError);
/* BEGIN */
  Math_ErrorHandler = Math_DefaultErrorHandler;
  Math_em = Math_ulp((REAL)1);
  Math_LnInfinity = Math_ln(3.4028235e+38);
  Math_LnSmall = Math_ln(2.938736052218037e-39);
  Math_SqrtInfinity = Math_sqrt(3.4028235e+38);
  Math_t = Math_pred((REAL)1) / Math_sqrt(Math_em);
  Math_TanhMax = Math_ln(Math_t + Math_sqrt(Math_t * Math_t + (SHORTREAL)1));
  Math_a1[1] = (REAL)1;
  Math_a1[2] = __VALSR((INTEGER)1064641917);
  Math_a1[3] = __VALSR((INTEGER)1063960775);
  Math_a1[4] = __VALSR((INTEGER)1063308511);
  Math_a1[5] = __VALSR((INTEGER)1062683901);
  Math_a1[6] = __VALSR((INTEGER)1062085772);
  Math_a1[7] = __VALSR((INTEGER)1061513002);
  Math_a1[8] = __VALSR((INTEGER)1060964516);
  Math_a1[9] = __VALSR((INTEGER)1060439283);
  Math_a1[10] = __VALSR((INTEGER)1059936319);
  Math_a1[11] = __VALSR((INTEGER)1059454679);
  Math_a1[12] = __VALSR((INTEGER)1058993458);
  Math_a1[13] = __VALSR((INTEGER)1058551792);
  Math_a1[14] = __VALSR((INTEGER)1058128851);
  Math_a1[15] = __VALSR((INTEGER)1057723842);
  Math_a1[16] = __VALSR((INTEGER)1057336003);
  Math_a1[17] = 0.5;
  Math_a2[1] = __VALSR((INTEGER)833168438);
  Math_a2[2] = __VALSR((INTEGER)862726805);
  Math_a2[3] = __VALSR((INTEGER)833158180);
  Math_a2[4] = __VALSR((INTEGER)857692172);
  Math_a2[5] = __VALSR((INTEGER)862601889);
  Math_a2[6] = __VALSR((INTEGER)851518274);
  Math_a2[7] = __VALSR((INTEGER)854021668);
  Math_a2[8] = __VALSR((INTEGER)852465808);
  __ENDMOD;
}
