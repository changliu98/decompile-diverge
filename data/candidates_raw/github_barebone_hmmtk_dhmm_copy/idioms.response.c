void dhmmpcopy(struct _dhmm *src, struct _dhmm *dest)
{
  int i; int j; int k;
  dest->N = src->N;
  dest->nN = cvector(1, dest->N);
  for (i = 1; i <= dest->N; i++)
    dest->nN[i] = src->nN[i];
  dest->M = src->M;
  dest->nM = cvector(1, dest->M);
  for (i = 1; i <= dest->M; i++)
    dest->nM[i] = src->nM[i];
  dest->A = dmatrix(1, dest->N, 1, dest->N);
  for (i = 1; i <= dest->N; i++)
    for (j = 1; j <= dest->N; j++)
      dest->A[i][j] = src->A[i][j];
  dest->B = dmatrix(1, dest->N, 1, dest->M);
  for (i = 1; i <= dest->N; i++)
    for (k = 1; k <= dest->M; k++)
      dest->B[i][k] = src->B[i][k];
  dest->pi = dvector(1, dest->N);
  for (i = 1; i <= dest->N; i++)
    dest->pi[i] = src->pi[i];
}