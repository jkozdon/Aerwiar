void manually(double *A, double *B, int n)
{
#pragma omp parallel for firstprivate(A, B, n)
  for (int ij = 0; ij < n * n; ++ij)
  {
    int j = ij / n;
    int i = ij % n;
    B[i * n + j] = A[i * n + i];
  }
}
