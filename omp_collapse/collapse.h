void collapse(double *A, double *B, int n)
{
#pragma omp parallel for firstprivate(A, B, n) collapse(2)
  for (int j = 0; j < n; ++j)
    for (int i = 0; i < n; ++i)
      B[i * n + j] = A[i * n + i];
}
