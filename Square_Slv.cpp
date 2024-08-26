#include "Square_proto.h"
void Solve_common (const COEFFICIENT coef_formal, ROOTS * const root_formal_common)
{
  assert(root_formal_common != NULL);
  if (Comparison_nan_inf (coef_formal.a, coef_formal.b, coef_formal.c))
    (*root_formal_common).roots = N_OR_INF;
  else if (Compare_doubles(coef_formal.a, 0))                                //a == 0
    Solve_Line(coef_formal, root_formal_common);
  else                                                                       //a != 0
    Solve_Square(coef_formal, root_formal_common);
}

void Solve_Line (const COEFFICIENT coef_formal_l, ROOTS * const root_line)
  {
    assert(root_line != NULL);
    if (Compare_doubles(coef_formal_l.b, 0)) //b == 0
      {
        if (Compare_doubles(coef_formal_l.c, 0))
          (*root_line).roots = INF_ROOTS;               //return INF;
        else
          (*root_line).roots = ZERO_ROOTS;               //return NOL;
      }
    else
      {
        (*root_line).x1 = (*root_line).x2 = -coef_formal_l.c / coef_formal_l.b;
        assert(isfinite((*root_line).x1));

        (*root_line).roots = ONE_ROOTS;                     //return 1;
      }
  }

 void Solve_Square (const COEFFICIENT coef_formal_s, ROOTS * const root_sqr)

 {
   assert(root_sqr != NULL);
   const double D = (coef_formal_s.b * coef_formal_s.b) - (4 * coef_formal_s.a * coef_formal_s.c);
     assert(isfinite(D));

   if (Compare_doubles(D, 0)) //D == 0
    {
      (*root_sqr).x1 = (*root_sqr).x2 = (-coef_formal_s.b) / (2*coef_formal_s.a);
      (*root_sqr).roots = ONE_ROOTS;       //return 1;
    }
   else if (D < 0)
      (*root_sqr).roots = ZERO_ROOTS;   //return NOL;
   else
     {
       double sqr_D = sqrt(D);
       (*root_sqr).x1 = (-coef_formal_s.b + sqr_D) / (2*coef_formal_s.a);
       (*root_sqr).x2 = (-coef_formal_s.b - sqr_D) / (2*coef_formal_s.a);
       (*root_sqr).roots = TWO_ROOTS;                //return 2;
     }
 }

int Compare_doubles (const double q, const double r)
  {
    assert (isfinite(q));
    assert (isfinite (r));
    if (fabs(q - r) < epsilon)
      return true;
    return false;
  }

double Rounding_doubles (const double t)
  {
    assert (isfinite(t));
    return (round(t * alpha) / alpha);
  }

bool Comparison_nan_inf (const double a, const double b, const double c)
  {
    if (isfinite(a) == false || isfinite(b) == false || isfinite(c) == false)
      return true;
    else
      return false;
  }

