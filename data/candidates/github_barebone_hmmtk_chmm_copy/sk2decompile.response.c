void chmm_copy(chmm *src, chmm *dst) {
  int i, j;
  dst->N = src->N;
  dst->pi = cvector(1, dst->N);
  for (j = 1; j <= dst->N; j++) dst->pi[j] = src->pi[j];
  dst->M = src->M;
  dst->sym = cvector(1, dst->M);
  for (j = 1; j <= dst->M; j++) dst->sym[j] = src->sym[j];
  dst->A = dmatrix(1, dst->N, 1, dst->N);
  for (j = 1; j <= dst->N; j++)
    for (i = 1; i <= dst->N; i++) dst->A[j][i] = src->A[j][i];
  dst->B.f = dmatrix(1, dst->N, 1, dst->M);
  dst->B.b = dmatrix(1, dst->N, 1, dst->M);
  dst->B.c = dmatrix(1, dst->N, 1, dst->M);
  for (j = 1; j <= dst->N; j++)
    for (i = 1; i <= dst->M; i++) {
      dst->B.f[j][i] = src->B.f[j][i];
      dst->B.b[j][i] = src->B.b[j][i];
      dst->B.c[j][i] = src->B.c[j][i];
    }
  dst->scale = dvector(1, dst->N);
  for (j = 1; j <= dst->N; j++) dst->scale[j] = src->scale[j];
}