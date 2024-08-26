#include "Square_proto.h"

void Print_Meeting (void)
  {
    printf("Hello! You are welcomed by the program for solving the quadratic equation\n"
           "What do you want to do?\n");
  }

void Print_Begin (void)
  {
    printf("Enter:\n"
           "\"s\" - for solve equation\n"
           "\"t\" - for testing programm\n"
           "\"e\" - for exit\n");

  }

void Buffer_clean (void)
  {
    int ch = 0;
    while ((ch = getchar()) != '\n' && ch != EOF);
  }

void Print_Solutions (ROOTS *printr)
  {
    assert(printr != NULL);
    switch ((*printr).roots)
      {
        case ZERO_ROOTS:
          printf ("The equation has no roots\n");
          break;

        case ONE_ROOTS:
          Del_Minus (&(printr->x1));
          printf("The equation has 1 root = %lg\n", Rounding_doubles((*printr).x1));
          break;

        case TWO_ROOTS:
          Del_Minus (&(printr->x1));
          Del_Minus (&(printr->x2));
          printf("The equation has 2 root = %lg and %lg\n",Rounding_doubles((*printr).x1), Rounding_doubles((*printr).x2));
          break;

        case INF_ROOTS:
          printf("The equation has infinite roots.\n");
          break;

        case N_OR_INF:
          printf("This data type cannot be used for coefficients\n");
          break;

        default:
          printf("Error\n");
          break;
      }
  }

void Del_Minus (double * const x1)
  {
    assert(x1 != NULL);
    if (Compare_doubles(*x1, 0))
    *x1 = 0;
  }

void Print_In_Solve (void)
  {
    printf("Would you like to go to the main menu?\n"
           "Enter \"e\" to exit and \"s\" to continue solving\n");
  }
