#include <TXLib.h>
#include <stdio.h>
#include <math.h>
const int NOL = 0;
const int INF = -1;
const int ONE_1 = 11;
const int ONE_2 = 22;
const int ONE_3 = 33;

const double epsilon = 1e-12;


int SolveSquares (double a, double b, double c, double *x1, double *x2);

int main (void)
{

 double a = 0, b = 0, c = 0;
 double x1 = 0, x2 = 0;
 printf("������� �������� ������������ ����������� ���������:\n ");
 printf("(��� \"q\" ��� ������ �� ���������)  ");

 while ((scanf("%lf %lf %lf", &a, &b, &c)) == 3)
  {
    int roots = SolveSquares(a, b, c, &x1, &x2);



    switch (roots)
    {
       case NOL:
        printf ("��������� �� ����� ������\n");
        break;

       case ONE_1:
        printf("��������� ����� 1 ������ = 0\n");
        break;

       case ONE_2:
        printf("��������� ����� 1 ������ = %lf\n", x1) ;
        break;

       case ONE_3:
        printf("��������� ����� 1 ������ = %lf\n", x1) ;
        break;

       case 2:
        printf("��������� ����� 2 ����� = %lf � %lf\n",x1, x2);
        break;

      case INF:
        printf("��������� ����� ���������� ������\n");
        break;

      default:
        printf("������\n");
        break;
   }
    printf("������� ������������ ��� ���: ")
  }

 printf("��������� ���������");
  return 0;
}

int SolveSquares (double a, double b, double c, double *x1, double *x2)
{





  if (fabs(a) < epsilon) //a == 0
    {
      if (fabs(b) < epsilon) //b == 0
        {
         return (fabs(c) < epsilon) ? NOL : INF;
        }
      else
         return (fabs(c) < epsilon) ? ONE_1 : ONE_2;
         *x1 = *x2 = -c/a;
    }

   double D;
   D = (b*b) - (4*a*c);

   if (fabs(D) < epsilon)
    {
      *x1 = *x2 = (-b) /(2*a);
      return ONE_3;
    }

   else if (D<0)
   return -2;


   else
    {
      *x1 = ((-b) + sqrt(D)) / (2 * a);
      *x2 = ((-b) - sqrt(D)) / (2 * a);
      return 2;
    }
}

