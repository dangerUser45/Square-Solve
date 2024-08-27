#include "Square_proto.h"
void Processing_coefficients (COEFFICIENT * const var_for_adr_coef)
  {
     assert (var_for_adr_coef != NULL);
     double a = NAN, b = NAN, c = NAN;
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
    int output_choice = Fix_Uncorrect_Entry (false);
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

int Fix_Uncorrect_Entry (const bool is_from_main)
  {

    int input_code = 0;
    int ch = 0;
    if (is_from_main)
      Print_Begin ();
    else
      Print_In_Solve ();
    input_code = getchar();


    while (true)
      {
        if ((input_code == 'e' || input_code == 'E') && ((ch = getchar()) == '\n' || ch == EOF))
          {
            return OUT_OF_PROG;
          }
        else if (is_from_main && (input_code == 't' || input_code == 'T') && ((ch = getchar()) == '\n' || ch == EOF))
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
            if (is_from_main)
              {
                printf ("You can only enter \"s\" or \"t\" or \"e\"\n");
                input_code = getchar();
              }
            else
              {
                printf ("You can only enter \"s\" or \"e\"\n");
                input_code = getchar();
              }
          }
      }


  }
