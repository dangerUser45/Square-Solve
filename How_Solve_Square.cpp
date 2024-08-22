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
   int roots = 0;

};



const  int NOL = 0;
const  int INF = -1;

const double epsilon = 1e-12;

int Solve_common (COEFFICIENT coef_formal, ROOTS *root_formal_common.x1, ROOTS *root_formal_common.x2);
void Print_Solutions (ROOTS printr.roots, ROOT *printr.x1, ROOT *printr.x1 );
int Solve_Line (COEFFICIENT coef_formal.b, COEFFICIENT coef_formal.c, ROOTS *qwerty.x1, ROOTS *qwerty.x2);
int Solve_Square (COEFFICIENT coef_formal, ROOTS *qwerty.x1, ROOTS *qwerty.x2);
void Del_Minus (double *x1);
void Unit_f (STRUCT_FOR_TEST test);
int Compare_doubles (double q, double r);



int main (void)
{
 setlocale(LC_ALL, "Russian");
 double a = 0, b = 0, c = 0;
 double x1 = 0, x2 = 0;
 int roots = 0, input_code = -1;

 STRUCT_FOR_TEST test1;
 ROOTS root_and_q;


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
       roots = Solve_common (coef, &root_and_q.x1, &root_and_q.x2);
       root_and_q.roots = roots;
       /*Unit_f (1, 5, 0, 0, 1, 0, 0);*/
       Print_Solutions (root_and_q.roots, &root_and_q.x1, &root_and_q.x2);
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

int Solve_common (COEFFICIENT coef_formal, ROOTS *root_formal_common.x1, ROOTS *root_formal_common.x2)
{
    int roots = 0;
    if (Compare_doubles(coef_formal.a, epsilon))                                                     //a == 0
      roots = Solve_Line(coef_formal.b, coef_formal.c, root_formal_common.x1, root_formal_common.x2);
    else                                                                       //a != 0
      roots = Solve_Square(coef_formal, root_formal_common.x1, root_formal_common.x2);

    return roots;
}

int Solve_Line (COEFFICIENT coef_formal.b, COEFFICIENT coef_formal.c, ROOTS *qwerty.x1, ROOTS *qwerty.x2)
{
      if (Compare_doubles(coef_formal.b, epsilon)) //b == 0
        {
         return (Compare_doubles(coef_formal.c, epsilon)) ? INF : NOL;
        }
      else
       {
         (*qwerty).x1 = (*qwerty).x2 = -c/b;
         return 1;
       }
}

 int Solve_Square (COEFFICIENT coef_formal, ROOTS *qwerty.x1, ROOTS *qwerty.x2)

 {
   double D = (b*b) - (4*a*c);

   if (Compare_doubles(D, epsilon)) //D == 0
    {
      (*qwerty).x1 = (*qwerty).x2 = (-b) /(2*a);
      return 1;
    }

   else if (D < 0)
      return NOL;
   else
     {
       (*qwerty).x1 = (-coef_formal.b + sqrt(D)) / (2*coef_formal.a);
       (*qwerty).x2 = (-coef_formal.b - sqrt(D)) / (2*coef_formal.a);
       return 2;
     }
 }


 void Print_Solutions (ROOTS printr.roots, ROOT *printr.x1, ROOT *printr.x1)
 {
   switch (printr.roots)
    {
       case NOL:
        printf ("\n��������� �� ����� ������\n");
        break;

       case 1:
        Del_Minus (printr.x1);
        printf("\n��������� ����� 1 ������ = %lg\n", (*printr).x1);
        break;

       case 2:
        Del_Minus (printr.x1);
        Del_Minus (printr.x2);
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


 void Unit_f (STRUCT_FOR_TEST test)
 {
   double x1 = 0, x2 = 0;
   int roots = Solve_common (COEFFICIENT coef, ADRESS_ROOTS adr_roots);
   if (roots != STRUCT_FOR_TEST.roots_right || Compare_doubles(x1, x1_right)== 0 || Compare_doubles(x2, x2_right)== 0)
   printf ("������ �%d: a = %lg, b = %lg, c = %lg, roots = %d, x1 = %lg, x2 = %lg"
           "���������� ������: roots_right = %d, x1_right = %lg, x2_right = %lg",
            n_Test, a, b, c, roots, x1, x2,
            roots_right, x1_right, x2_right);
 }

int Compare_doubles (double q, double r)
{
  if (fabs(q - r) <= epsilon )
    return 1;
  return 0;
}
