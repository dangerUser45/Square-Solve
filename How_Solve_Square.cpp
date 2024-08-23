#include <locale.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

struct COEFFICIENT
{
    double a = 0,
           b = 0,
           c = 0;
};

struct ROOTS
{
   double x1 = 0,
          x2 = 0;
   int roots = 0;

};

struct STRUCT_FOR_TEST
 {
    COEFFICIENT coef = {};
    ROOTS data_right = {};
 };


enum root_quality {ZERO_ROOTS, ONE_ROOTS, TWO_ROOTS, INF_ROOTS};
const double epsilon = 1e-6;

void Solve_common (COEFFICIENT coef_formal, ROOTS *root_formal_common);
void Print_Solutions (ROOTS *printr);
void Solve_Line (COEFFICIENT coef_formal_l, ROOTS *root_line);
void Solve_Square (COEFFICIENT coef_formal_s, ROOTS *root_sqr);
void Del_Minus (double *x1);
//void Unit_Testing (STRUCT_FOR_TEST *adress_r_t, COEFFICIENT coef_test, ROOTS roots_test);
int Compare_doubles (double q, double r);
void Fix_Uncorrect_Entry (COEFFICIENT *adrs_coef);
void Print_Beggin (void);



int main (void)
{
 setlocale(LC_ALL, "Russian");

 STRUCT_FOR_TEST run_test;
 ROOTS root_and_q;
 COEFFICIENT coef;

       Fix_Uncorrect_Entry (&coef);
       Solve_common (coef, &root_and_q);
       //Unit_Testing (&run_test, coef, root_and_q );
       Print_Solutions (&root_and_q);


 printf("Программа завершена");
  return 0;
}

void Solve_common (COEFFICIENT coef_formal, ROOTS *root_formal_common)
{
    if (Compare_doubles(coef_formal.a, 0))                                                     //a == 0
      Solve_Line(coef_formal, root_formal_common);
    else                                                                       //a != 0
      Solve_Square(coef_formal, root_formal_common);
}

void Solve_Line (COEFFICIENT coef_formal_l, ROOTS *root_line)
{
      if (Compare_doubles(coef_formal_l.b, 0)) //b == 0
        {
         if (Compare_doubles(coef_formal_l.c, 0))
           (*root_line).roots = INF_ROOTS;               //return INF;
         else
           (*root_line).roots = ZERO_ROOTS;               //return NOL;
        }
      else
       {
         (*root_line).x1 = (*root_line).x2 = -coef_formal_l.c/coef_formal_l.b;
         (*root_line).roots = ONE_ROOTS;                     //return 1;
       }
}

 void Solve_Square (COEFFICIENT coef_formal_s, ROOTS *root_sqr)

 {
   double D = (coef_formal_s.b * coef_formal_s.b) - (4 * coef_formal_s.a * coef_formal_s.c);

   if (Compare_doubles(D, 0)) //D == 0
    {
      (*root_sqr).x1 = (*root_sqr).x2 = (-coef_formal_s.b) /(2*coef_formal_s.a);
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


 void Print_Solutions (ROOTS *printr)
 {
   switch ((*printr).roots)
    {
       case NOL:
        printf ("\nУравнение не имеет корней\n");
        break;

       case 1:
        Del_Minus (&(printr->x1));
        printf("\nУравнение имеет 1 корень = %lg\n", (*printr).x1);
        break;

       case 2:
        Del_Minus (&(printr->x1));
        Del_Minus (&(printr->x2));
        printf("\nУравнение имеет 2 корня = %lg и %lg\n",(*printr).x1, (*printr).x2);
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
    if (Compare_doubles(*x1, 0))
    *x1 = 0;
  }


 /*void Unit_Testing (STRUCT_FOR_TEST *adress_str_test)
 {

    const int n_Test = 20;
    STRUCT_FOR_TEST data[n_Test] = {
                                     {1, 1, 1, NAN, NAN, 0},
                                     {1, 0, 0, 0, NAN, 1},
                                     {1, 0, 1, NAN, NAN, 0},
                                     {1, 1, 0, -1, 0, 2},
                                     {0, 0, 0, NAN, NAN, INF},
                                     {0, 1, 0, 0, NAN, 1},
                                     {0, 0, 1, NAN,NAN, 0},
                                     {0, 1, 1, -1, NAN, 1},
                                     {-1, -1, -1, NAN,NAN, 0},
                                     {-1, 0, 0, 0, NAN, 1},
                                     {0, -1, 0, 0, NAN, 1},
                                     {0, 0, -1, NAN,NAN, 0},
                                     {12, 12, 12, NAN,NAN, 0},
                                     {1, -2, 1, 1, NAN, 1},
                                     {1, 78414.6345, 138444.1542, 1.7655, -78416.4 2},
                                     {2.5, -78, 88, 1.17225, 30.02775, 2},
                                     {17500, 999999, -17835343, 14.27119, -71.41399, 2},
                                     {0.00008, -0.46191, 0.46441, 1.00559, 5772,86941, 2},
                                     {17, -12.5, -0.5, -0.0380328, 0.773327, 2},
                                     {-79.46, 1.2, 7941, -9.989311, 10.00441, 2},
                                    };

   Solve_common (coef_test, &roots_test);
   if (roots_test.roots != (*adress_r_t).roots_right  || Compare_doubles(roots_test.x1, (*adress_r_t).x1_right) == 0 || Compare_doubles(roots_test.x2, (*adress_r_t).x2_right) == 0)
   printf ("Ошибка №%d: a = %lg, b = %lg, c = %lg, roots = %d, x1 = %lg, x2 = %lg"
           "Правильные данные: roots_right = %d, x1_right = %lg, x2_right = %lg",
            (*adress_r_t).n_Test, coef_test.a, coef_test.b, coef_test.c, roots_test.roots, roots_test.x1, roots_test.x2,
            (*adress_r_t).roots_right, (*adress_r_t).x1_right, (*adress_r_t).x2_right);
 } */

int Compare_doubles (double q, double r)
{
  if (fabs(q - r) <= epsilon )
    return true;
  return false;
}

void Print_Beggin (void)
{
  printf("  Введите \"0\"            Введите \"1\"\n");
  printf("  для завершения   или   для решения\n");
  printf("  программы              квадратного уравнения\n");
}

void Fix_Uncorrect_Entry (COEFFICIENT *adrs_coef)
{
  while (1)
   {
     int input_code = -1;
     double a = 0, b = 0, c = 0;
     char ch = 0;
     Print_Beggin ();
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
      if (scanf("%lf %lf %lf%c", &a, &b, &c, &ch) != 3)
       {
          while (getchar() != '\n');
          printf("Вы ввели не то, попробуйте ещё раз\n\n");
        }
      else
       {
          adrs_coef->a = a;
          adrs_coef->b = b;
          adrs_coef->c = c;
       }
    }
}
