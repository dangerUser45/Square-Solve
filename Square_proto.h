#include <locale.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>

struct COEFFICIENT
{
    double a = NAN,
           b = NAN,
           c = NAN;
};

struct ROOTS
{
   double x1 = NAN,
          x2 = NAN;
   int roots = 0;

};

struct STRUCT_FOR_TEST
 {
    COEFFICIENT coef = {};
    ROOTS data_right = {};
 };

enum root_quantity {ZERO_ROOTS, ONE_ROOTS, TWO_ROOTS, INF_ROOTS, N_OR_INF};
enum management {DEFAULT = -1, OUT_OF_PROG, TEST, SOLVE};
enum menu {RET_IN_STE, RET_CONTINUE_SOLVE};
const double epsilon = 1e-12;
const double test_precision = 1e5;

void Solve_common (const COEFFICIENT coef_formal, ROOTS * const root_formal_common);
void Print_Solutions (ROOTS * const printr);
void Solve_Line (const COEFFICIENT coef_formal_l, ROOTS * const root_line);
void Solve_Square (const COEFFICIENT coef_formal_s, ROOTS * const root_sqr);
void Del_Minus (double * const x1);
void Unit_Testing (void);
int Compare_doubles (const double q, const double r);
double Rounding_doubles (const double t);
bool Comparison_nan_inf (const double a, const double b, const double c);
int Fix_Uncorrect_Entry (const bool is_from_main);
void Print_Meeting (void);
void Print_Begin (void);
void Print_In_Solve (void);
void Buffer_clean (void);
void Processing_coefficients (COEFFICIENT * const var_for_adr_coef);
int For_Return (void);
