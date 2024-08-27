#include "Square_proto.h"
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
        if (data_solve.roots != data[i].data_right.roots ||
            Rounding_doubles(data_solve.x1) != Rounding_doubles(data[i].data_right.x1) ||
            Rounding_doubles(data_solve.x2) != Rounding_doubles(data[i].data_right.x2))
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
