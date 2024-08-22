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
    int roots_right = 0;
    double x1_right = 0,
           x2_right = 0;
 };


struct ROOTS
{
   double x1 = 0,
          x2 = 0;
   int roots = 0;

};



const  int NOL = 0;
const  int INF = -1;

const double epsilon = 1e-12;

void Solve_common (COEFFICIENT coef_formal, ROOTS *root_formal_common);
void Print_Solutions (ROOTS *printr);
void Solve_Line (COEFFICIENT coef_formal_l, ROOTS *root_line);
void Solve_Square (COEFFICIENT coef_formal_s, ROOTS *root_sqr);
void Del_Minus (double *x1);
void Unit_Testing (STRUCT_FOR_TEST *adress_r_t, COEFFICIENT coef_test, ROOTS roots_test);
int Compare_doubles (double q, double r);



int main (void)
{
 setlocale(LC_ALL, "Russian");
 int input_code = -1;

 STRUCT_FOR_TEST run_test;
 ROOTS root_and_q;
 COEFFICIENT coef;

while (1)
 {



 printf("  ������� \"0\"            ������� \"1\"\n");
 printf("  ��� ����������   ���   ��� �������\n");
 printf("  ���������              ����������� ���������\n");


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



    printf("������� ������������ ����������� ���������: ");
    if (scanf("%lf %lf %lf", &coef.a, &coef.b, &coef.c) == 3)
     {
       Unit_Testing (&run_test, coef, root_and_q );
       Solve_common (coef, &root_and_q);
       Print_Solutions (&root_and_q);
     }

     else
      {
        while (getchar() != '\n')
         continue;
        printf("�� ����� �� ��, ���������� ��� ���\n\n");
      }

  }

 printf("��������� ���������");
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
         if (Compare_doubles(coef_formal_l.c, 0) == 1)
           (*root_line).roots = INF;               //return INF;
         else
           (*root_line).roots = NOL;               //return NOL;
        }
      else
       {
         (*root_line).x1 = (*root_line).x2 = -coef_formal_l.c/coef_formal_l.b;
         (*root_line).roots = 1;                     //return 0;
       }
}

 void Solve_Square (COEFFICIENT coef_formal_s, ROOTS *root_sqr)

 {
   double D = (coef_formal_s.b * coef_formal_s.b) - (4 * coef_formal_s.a * coef_formal_s.c);

   if (Compare_doubles(D, 0)) //D == 0
    {
      (*root_sqr).x1 = (*root_sqr).x2 = (-coef_formal_s.b) /(2*coef_formal_s.a);
      (*root_sqr).roots = 2;       //return 1;
    }

   else if (D < 0)
      (*root_sqr).roots = NOL;   //return NOL;
   else
     {
       (*root_sqr).x1 = (-coef_formal_s.b + sqrt(D)) / (2*coef_formal_s.a);
       (*root_sqr).x2 = (-coef_formal_s.b - sqrt(D)) / (2*coef_formal_s.a);
       (*root_sqr).roots = 2;                //return 2;
     }
 }


 void Print_Solutions (ROOTS *printr)
 {
   switch ((*printr).roots)
    {
       case NOL:
        printf ("\n��������� �� ����� ������\n");
        break;

       case 1:
        Del_Minus (&(printr->x1));
        printf("\n��������� ����� 1 ������ = %lg\n", (*printr).x1);
        break;

       case 2:
        Del_Minus (&(printr->x1));
        Del_Minus (&(printr->x2));
        printf("\n��������� ����� 2 ����� = %lg � %lg\n",(*printr).x1, (*printr).x2);
        break;

      case INF:
        printf("\n��������� ����� ���������� ������\n");
        break;

      default:
        printf("\n������\n");
        break;
   }
 }


  void Del_Minus (double *x1)
  {
    if (Compare_doubles(*x1, epsilon))
    *x1 = 0;
  }


 void Unit_Testing (STRUCT_FOR_TEST *adress_r_t, COEFFICIENT coef_test, ROOTS roots_test)
 {
   Solve_common (coef_test, &roots_test);
   if (roots_test.roots != (*adress_r_t).roots_right  || Compare_doubles(roots_test.x1, (*adress_r_t).x1_right) == 0 || Compare_doubles(roots_test.x2, (*adress_r_t).x2_right) == 0)
   printf ("������ �%d: a = %lg, b = %lg, c = %lg, roots = %d, x1 = %lg, x2 = %lg"
           "���������� ������: roots_right = %d, x1_right = %lg, x2_right = %lg",
            (*adress_r_t).n_Test, coef_test.a, coef_test.b, coef_test.c, roots_test.roots, roots_test.x1, roots_test.x2,
            (*adress_r_t).roots_right, (*adress_r_t).x1_right, (*adress_r_t).x2_right);
 }

int Compare_doubles (double q, double r)
{
  if (fabs(q - r) <= epsilon )
    return 1;
  return 0;
}
