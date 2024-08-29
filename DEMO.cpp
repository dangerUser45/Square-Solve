#include <stdio.h>
#include <math.h>

double Rounding_doubles (double t);

int main (void)
  {
     double r = 0, n = 0;
     scanf("%lf", &n);
     r = Rounding_doubles (n);
     printf("%f", r);
     return 0;
  }
double Rounding_doubles (double t)
      {
        return (round(t * 1e5) / 1e5);
      }
