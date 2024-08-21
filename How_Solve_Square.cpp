##include <TXLib.h>
#include <stdio.h>
#include <math.h>
const int NOL = 0;
const int INF = -1;

const double epsilon = 1e-12;

int Func (double a, double b, double c, double *x1, double *x2);
void Switch_f (int roots, double *x1, double *x2);
int Solve_Line (double b, double c, double *x1, double *x2);
int Solve_Square (double a, double b, double c, double *x1, double *x2);
void Del_Minus (double *x1);
void Unit_f (int n_Test, double a, double b, double c, int roots_right, double x1_right, double x2_right);
int Compare_doubles (double q, double r);


int main (void)
{

 double a = 0, b = 0, c = 0;
 double x1 = 0, x2 = 0;
 int roots = 0;
 printf("Введите числовые коэффициенты квадратного уравнения:\n ");
 printf("(или \"q\" для выхода из программы)  ");


 while ((scanf("%lf %lf %lf", &a, &b, &c)) == 3)
  {
    roots = Func(a, b, c, &x1, &x2);
    Del_Minus (&x1);
    Unit_f (1, 5, 0, 0, 1, 0, 0);
    Switch_f (roots, &x1, &x2);

    printf("Введите коэффициенты ещё раз: ");
  }

 printf("Программа завершена");
  return 0;
}

int Func (double a, double b, double c, double *x1, double *x2)
{
    int roots = 0;
    if (fabs(a) < epsilon)                       //a == 0
      roots = Solve_Line(b, c, x1, x2);
    else                                         //a != 0
      roots = Solve_Square(a, b, c, x1, x2);

    return roots;
}

int Solve_Line (double b, double c, double *x1, double *x2)
{
      if (fabs(b) < epsilon) //b == 0
        {
         return (fabs(c) < epsilon) ? INF : NOL;
        }
      else
         *x1 = *x2 = -c/b;
         return 1;
}

 int Solve_Square (double a, double b, double c, double *x1, double *x2)

 {
   double D;
   D = (b*b) - (4*a*c);

   if (fabs(D) < epsilon)
    {
      *x1 = *x2 = (-b) /(2*a);
      return 1;
    }

   else if (D < 0)
      return -2;
   else
     {
       *x1 = (-b + sqrt(D)) / (2*a);
       *x2 = (-b - sqrt(D)) / (2*a);
       return 2;
     }
 }


 void Switch_f (int roots, double *x1, double *x2)
 {
   switch (roots)
    {
       case NOL:
        printf ("Уравнение не имеет корней\n");
        break;

       case 1:
        printf("Уравнение имеет 1 корень = %lg\n", *x1);
        break;

       case 2:
        printf("Уравнение имеет 2 корня = %lg и %lg\n",*x1, *x2);
        break;

      case INF:
        printf("Уравнение имеет бесконечно корней\n");
        break;

      case -2:
        printf("Уравнение имеет отрицательный дискриминант\n");
        break;

      default:
        printf("Ошибка\n");
        break;
   }
 }


  void Del_Minus (double *x1)
  {
    if (fabs(*x1)<= epsilon)
    *x1 = 0;
  }


 void Unit_f (int n_Test, double a, double b, double c, int roots_right, double x1_right, double x2_right)
 {
   double x1 = 0, x2 = 0;
   int roots = Func (a, b, c, &x1, &x2);
   if (roots != roots_right || Compare_doubles(x1, x1_right)== 0 || Compare_doubles(x2, x2_right)== 0)
   printf ("Ошибка №%d: a = %lg, b = %lg, c = %lg, roots = %d, x1 = %lg, x2 = %lg"
           "Правильные данные: roots_right = %d, x1_right = %lg, x2_right = %lg",
            n_Test, a, b, c, roots, x1, x2,
            roots_right, x1_right, x2_right);
 }

int Compare_doubles (double q, double r)
{
  if (fabs(q - r) <= epsilon )
    return 1;
  else
    return 0;
}

