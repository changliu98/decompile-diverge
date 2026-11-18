void chmm_copy(struct _CHMM *src, struct _CHMM *dest)
{
  int i; int j; int k;
  dest->N = src->N;
  dest->nN = cvector(1, dest->N);
  for (i = 1; i <= dest->N; i++)
    dest->nN[i] = src->nN[i];
  dest->D = src->D;
  dest->nD = cvector(1, dest->D);
  for (i = 1; i <= dest->D; i++)
    dest->nD[i] = src->nD[i];
  dest->A = dmatrix(1, dest->N, 1, dest->N);
  for (i = 1; i <= dest->N; i++)
    for (j = 1; j <= dest->N; j++)
      dest->A[i][j] = src->A[i][j];
  dest->B.miu = dmatrix(1, dest->N, 1, dest->D);
  dest->B.cov = dmatrix(1, dest->N, 1, dest->D);
  dest->B.cov_inv = dmatrix(1, dest->N, 1, dest->D);
  for (i = 1; i <= dest->N; i++)
    for (k = 1; k <= dest->D; k++) {
      dest->B.miu[i][k] = src->B.miu[i][k];
      dest->B.cov[i][k] = src->B.cov[i][k];
      dest->B.cov_inv[i][k] = src->B.cov_inv[i][k];
    }
  dest->pi = dvector(1, dest->N);
  for (i = 1; i <= dest->N; i++)
    dest->pi[i] = src->pi[i];
}