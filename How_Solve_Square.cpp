#include <locale.h>
#include <stdio.h>
#include <math.h>


struct COEFFICIENT
{
    double a = 0,
           b = 0,
           c = 0;
};

struct STRUCT_FOR_TEST
 {
    int n_Test = 0;
    struct COEFFICIENT coef;
    int roots_right = 0;
    double x1_right = 0,
           x2_right = 0;
 };


struct ROOTS
{
   double x1 = 0,
          x2 = 0;
   int n_roots = 0;

};



  int NOL = 0;
  int INF = -1;

const double epsilon = 1e-12;

int Solve_common (double a, double b, double c, double *x1, double *x2);
void Print_Solutions (int roots, double *x1, double *x2);
int Solve_Line (double b, double c, double *x1, double *x2);
int Solve_Square (double a, double b, double c, double *x1, double *x2);
void Del_Minus (double *x1);
void Unit_f (int n_Test, double a, double b, double c, int roots_right, double x1_right, double x2_right);
int Compare_doubles (double q, double r);



int main (void)
{
 setlocale(LC_ALL, "Russian");
 double a = 0, b = 0, c = 0;
 double x1 = 0, x2 = 0;
 int roots = 0, input_code = -1;

while (1)
 {
 printf("  Введите \"0\"            Введите \"1\"\n");
 printf("  для завершения   или   для решения\n");
 printf("  программы              квадратного уравнения\n");


   scanf("%d", &input_code);
   if (input_code == 0)
    {
      break;
    }

   else if (input_code != 1)
    {
      while (getchar() != '\n');
      continue;
    }



    printf("Введите коэффициенты квадратного уравнения: ");
    if (scanf("%lf %lf %lf", &a, &b, &c) == 3)
     {
       roots = Solve_common (a, b, c, &x1, &x2);
       Unit_f (1, 5, 0, 0, 1, 0, 0);
       Print_Solutions (roots, &x1, &x2);
     }

     else
      {
        while (getchar() != '\n')
         continue;
        printf("Вы ввели не то, попробуйте ещё раз\n\n");
      }

  }

 printf("Программа завершена");
  return 0;
}

int Solve_common (const double a, double b, double c, double *x1, double *x2)
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
      if (Compare_doubles(b, epsilon)) //b == 0
        {
         return (fabs(c) < epsilon) ? INF : NOL;
        }
      else
       {
         *x1 = *x2 = -c/b;
         return 1;
       }
}

 int Solve_Square (double a, double b, double c, double *x1, double *x2)

 {
   const double D = (b*b) - (4*a*c);

   if (Compare_doubles(b, epsilon)) //D == 0
    {
      *x1 = *x2 = (-b) /(2*a);
      return 1;
    }

   else if (D < 0)
      return NOL;
   else
     {
       *x1 = (-b + sqrt(D)) / (2*a);
       *x2 = (-b - sqrt(D)) / (2*a);
       return 2;
     }
 }


 void Print_Solutions (int roots, double *x1, double *x2)
 {
   switch (roots)
    {
       case NOL:
        printf ("\nУравнение не имеет корней\n");
        break;

       case 1:
        Del_Minus (x1);
        printf("\nУравнение имеет 1 корень = %lg\n", *x1);
        break;

       case 2:
        Del_Minus (x1);
        Del_Minus (x2);
        printf("\nУравнение имеет 2 корня = %lg и %lg\n",*x1, *x2);
        break;

      case INF:
        printf("\nУравнение имеет бесконечно корней\n");
        break;

      default:
        printf("\nОшибка\n");
        break;
   }
 }


  void Del_Minus (double *x1)
  {
    if (fabs(*x1)<= epsilon)
    *x1 = 0;
  }


 void Unit_f (STRUCT_FOR_TEST test)
 {
   double x1 = 0, x2 = 0;
   int roots = Solve_common (COEFFICIENT coef, ADRESS_ROOTS adr_roots);
   if (roots != STRUCT_FOR_TEST.roots_right || Compare_doubles(x1, x1_right)== 0 || Compare_doubles(x2, x2_right)== 0)
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
