#include "Square_proto.h"
int main (void)
  {
    setlocale(LC_ALL, "Russian");

    STRUCT_FOR_TEST run_test;
    ROOTS root_and_q;
    COEFFICIENT coef;

    Print_Meeting ();
    switch (Fix_Uncorrect_Entry (true))
      {
        case OUT_OF_PROG:
          return 0;

        case TEST:
          Unit_Testing ();
          printf("Programm exit");
          return 0;

        case SOLVE:
          while (true)
            {
              Processing_coefficients (&coef);
              Solve_common (coef, &root_and_q);
              Print_Solutions (&root_and_q);
              int ret_val = For_Return ();

              if(ret_val == RET_IN_STE)
                {
                  switch(Fix_Uncorrect_Entry (true))
                    {
                      case OUT_OF_PROG:
                        printf("Programm exit");
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
