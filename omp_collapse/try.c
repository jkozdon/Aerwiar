#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "collapse.h"
#include "manually.h"

int main(int argc, char **argv)
{
  int n = 999;
  int iterations = 100;

  if (argc > 1)
    n = atoi(argv[1]);

  if (argc > 2)
    iterations = atoi(argv[2]);

  int inforate = iterations > 10 ? iterations / 10 : 1;
  if (argc > 3)
    inforate = atoi(argv[2]);

  if (argc < 1 || n < 1 || iterations < 1)
  {
    printf("Usage: %s [n] [iterations] [inforate]\n\n", argv[0]);
    printf("Perform an n x n matrix multiplication\n");
    printf("    n               matrix size (default: %d)\n", n);
    printf("    iterations      number of iterations "
           "(default: %d)\n",
           iterations);
    printf("    inforate        how often to output info "
           "(default: iterations / 10)\n");
    return 1;
  }

  printf("Test Configuration\n");
  printf("    Matrix size:              %d x %d\n", n, n);
  printf("    Number of iterations:     %d\n", iterations);
  printf("\n");

  printf("Allocating matrices...\n");
  double *A = (double *)malloc(n * n * sizeof(double));
  double *B00 = (double *)malloc(n * n * sizeof(double));
  double *B01 = (double *)malloc(n * n * sizeof(double));

  printf("Filling matrices...\n");
#pragma omp parallel for firstprivate(A, n)
  for (int i = 0; i < n * n; ++i)
    A[i] = (double)rand() / RAND_MAX;

  printf("Performing matrix multiplication...\n");
  for (int iter = 0; iter < iterations; ++iter)
  {
    if (iter % inforate == 1)
      printf("    iterations %5d of %5d\n", iter, iterations);

    collapse(A, B00, n);
    manually(A, B01, n);
  }

  int check_00 = 0 == 0;
  for (int j = 0; j < n; ++j)
    for (int i = 0; i < n; ++i)
      check_00 = check_00 && B00[i * n + j] == A[i * n + i];

  int check_01 = 0 == 0;
  for (int j = 0; j < n; ++j)
    for (int i = 0; i < n; ++i)
      check_01 = check_01 && B01[i * n + j] == A[i * n + i];

  printf("collapse: %s\n", check_00 ? "passed" : "failed");
  printf("manually: %s\n", check_01 ? "passed" : "failed");

  free(A);
  free(B00);
  free(B01);

  return 0;
}
