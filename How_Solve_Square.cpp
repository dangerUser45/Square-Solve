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
enum managment {DEFAULT = -1, OUT_OF_PROG, TEST, SOLVE};
enum menu {RET_IN_STE, RET_CONTINUE_SOLVE};
const double epsilon = 1e-3;

void Solve_common (COEFFICIENT coef_formal, ROOTS *root_formal_common);
void Print_Solutions (ROOTS *printr);
void Solve_Line (COEFFICIENT coef_formal_l, ROOTS *root_line);
void Solve_Square (COEFFICIENT coef_formal_s, ROOTS *root_sqr);
void Del_Minus (double *x1);
void Unit_Testing (void);
int Compare_doubles (double q, double r);
int Fix_Uncorrect_Entry (void);
void Print_Beggin (void);
void Buffer_clean (void);
void Processing_coefficients (COEFFICIENT *var_for_adr_coef);
int Choice_Solve (void);
int For_Return (void);



int main (void)
{
 setlocale(LC_ALL, "Russian");

 STRUCT_FOR_TEST run_test;
 ROOTS root_and_q;
 COEFFICIENT coef;


       switch (Fix_Uncorrect_Entry ())
        {
          case OUT_OF_PROG:
            return 0;

          case TEST:
            Unit_Testing ();
            printf("Programm exit");
             return 0;

          case SOLVE:
            while (true)
              {     Processing_coefficients (&coef);
                    Solve_common (coef, &root_and_q);
                    Print_Solutions (&root_and_q);
                    int ret_val = For_Return ();

                    if(ret_val == RET_IN_STE)
                      {
                        switch(Fix_Uncorrect_Entry ())
                        {

                          case OUT_OF_PROG:
                           return 0;

                          case SOLVE:
                           continue;

                          case TEST:
                           Unit_Testing ();
                           return 0;

                         default:
                           printf("Error !!!");

                        }
                      }
                    else if (ret_val == RET_CONTINUE_SOLVE)
                      continue;
                    else
                    {
                        printf("Error return value in Processing_coefficients ()");
                        break;
                    }
              }
            break;

          default:
            printf("An error has occurred");
         }
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
       case ZERO_ROOTS:
        printf ("The equation has no roots\n");
        break;

       case ONE_ROOTS:
        Del_Minus (&(printr->x1));
        printf("The equation has 1 root = %lg\n", (*printr).x1);
        break;

       case TWO_ROOTS:
        Del_Minus (&(printr->x1));
        Del_Minus (&(printr->x2));
        printf("The equation has 2 root = %lg and %lg\n",(*printr).x1, (*printr).x2);
        break;

      case INF_ROOTS:
        printf("The equation has infinite roots.\n");
        break;

      default:
        printf("Error\n");
        break;
   }
 }


  void Del_Minus (double *x1)
  {
    if (Compare_doubles(*x1, 0))
    *x1 = 0;
  }


 void Unit_Testing (void)
 {

    const int n_Test = 4;
    ROOTS data_solve = {};
    const STRUCT_FOR_TEST data[] = { //coef         data_right
                                     {{1, -7, 12}, {4, 3, 2}},
                                     {{1.5, -7, 2}, {4.36092, 0.305746, 2}},
                                     {{78,58.86, -300}, {1.61982, -2.37443, 2}},
                                     {{0.783, -0.855, 0.05}, {1.02995, 0.0619998, 2}}
                                   };

    for (int i = 0; i < n_Test; i++)
     {
      Solve_common (data[i].coef, &data_solve);
      if (data_solve.roots != data[i].data_right.roots
       || (Compare_doubles(data_solve.x1, data[i].data_right.x1) == 0)
       || (Compare_doubles(data_solve.x2, data[i].data_right.x2) == 0))
       {
         printf ("Error in test %d:\n"
                 "a = %lg, b = %lg, c = %lg\n"
                 "Correct data     Solve data\n"
                 " roots = %d       roots = %d\n"
                 " x1 = %lf    x1 = %lf\n"
                 " x2 = %lf    x2 = %lf\n",
                 i+1,
                 data[i].coef.a, data[i].coef.b, data[i].coef.c,
                 data[i].data_right.roots,data_solve.roots,
                 data[i].data_right.x1, data_solve.x1,
                 data[i].data_right.x2, data_solve.x2);
       }
       else printf("Test [%d] success !\n", i+1);
     }

 }

int Compare_doubles (double q, double r)
{
  if (fabs(q - r) <= epsilon)
    return true;
  return false;
}

void Print_Beggin (void)
{
  printf("Hello! You are welcomed by the program for solving the quadratic equation\n"
         "What do you want to do?\n"
         "Enter:\n");
  printf("\"s\" - for solve equation\n"
         "\"t\" - for testing programm\n"
         "\"e\" - for exit\n");

}

int Fix_Uncorrect_Entry (void)
 {

     int input_code = 0;
     int ch = 0;
     Print_Beggin ();
     input_code = getchar();


     while (true)
      {
       if ((input_code == 'e' || input_code == 'E') && ((ch = getchar()) == '\n' || ch == EOF))
        {
          printf("Programm exit");
          return OUT_OF_PROG;
        }
       else if ((input_code == 't' || input_code == 'T') && ((ch = getchar()) == '\n' || ch == EOF))
        {
          return TEST;
        }
       else if ((input_code == 's' || input_code == 'S') && ((ch = getchar()) == '\n' || ch == EOF))
        {
          return SOLVE;
        }

       else
        {
          Buffer_clean();
          printf ("You can only enter \"s\" or \"t\" or \"e\"\n");
          input_code = getchar();
        }
      }


 }

void Buffer_clean (void)
 {
   while (getchar() != '\n');
 }

void Processing_coefficients (COEFFICIENT *var_for_adr_coef)
 {
   double a = 0.0, b = 0.0, c = 0.0;
   char ch = 0;
   int ret_val = 0;

   while(true)
           {
             printf("Enter the coefficients of the equation\n");
             ret_val = scanf("%lf %lf %lf%c", &a, &b, &c, &ch);
             if (ret_val == 4 && (ch =='\n' || ch == ' '))
                  {
                    var_for_adr_coef->a = a;
                    var_for_adr_coef->b = b;
                    var_for_adr_coef->c = c;
                    break;
                  }
             else
                  {
                    Buffer_clean();
                    printf("The data is entered incorrectly!\n");
                  }
           }
 }

 int For_Return (void)
 {

  int output_choice = Choice_Solve();
  if (output_choice == OUT_OF_PROG)
    {
        return RET_IN_STE;
    }
  else if (output_choice == SOLVE)
    {
        return RET_CONTINUE_SOLVE;
    }
  else printf("Erorr in return value in Choice_Solve");
        return DEFAULT;
 }





 int Choice_Solve (void)
 {
   printf("Would you like to go to the main menu?\n"
          "Enter \"e\" to exit and \"s\" to continue solving\n");
    int input_code = 0;
     int ch = 0;
     input_code = getchar();

     while (true)
      {
       if ((input_code == 'e' || input_code == 'E') && ((ch = getchar()) == '\n' || ch == EOF))
        {
          return OUT_OF_PROG;
        }

       else if ((input_code == 's' || input_code == 'S') && ((ch = getchar()) == '\n' || ch == EOF))
        {
          return SOLVE;
        }
       else
        {
          Buffer_clean();
          printf ("You can only enter \"e\" or \"s\"\n");
          input_code = getchar();
        }
      }
 }
