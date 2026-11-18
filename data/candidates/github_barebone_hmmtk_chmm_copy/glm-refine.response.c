void __cdecl chmm_copy(CHMM *src, CHMM *dst)
{
  int i, j, k;

  // Copy scalar dimensions
  dst->N = src->N;
  dst->D = src->D;

  // Copy state array (nN)
  dst->nN = cvector(1, dst->N);
  for (i = 1; i <= dst->N; ++i)
    dst->nN[i] = src->nN[i];

  // Copy dimension array (nD)
  dst->nD = cvector(1, dst->D);
  for (i = 1; i <= dst->D; ++i)
    dst->nD[i] = src->nD[i];

  // Copy transition matrix (A)
  dst->A = dmatrix(1, dst->N, 1, dst->N);
  for (i = 1; i <= dst->N; ++i)
    for (j = 1; j <= dst->N; ++j)
      dst->A[i][j] = src->A[i][j];

  // Allocate and copy emission distribution matrices (B)
  dst->B.miu     = dmatrix(1, dst->N, 1, dst->D);
  dst->B.cov     = dmatrix(1, dst->N, 1, dst->D);
  dst->B.cov_inv = dmatrix(1, dst->N, 1, dst->D);
  
  for (i = 1; i <= dst->N; ++i)
  {
    for (k = 1; k <= dst->D; ++k)
    {
      dst->B.miu[i][k]     = src->B.miu[i][k];
      dst->B.cov[i][k]     = src->B.cov[i][k];
      dst->B.cov_inv[i][k] = src->B.cov_inv[i][k];
    }
  }

  // Copy initial state probabilities (pi)
  dst->pi = dvector(1, dst->N);
  for (i = 1; i <= dst->N; ++i)
    dst->pi[i] = src->pi[i];
}