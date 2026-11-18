void dhmm_copy(dhmm_t *hmm1, dhmm_t *hmm2) {
  int i, j;
  hmm2->N = hmm1->N;
  hmm2->pi = cvector(1, hmm2->N);
  for (j = 1; j <= hmm2->N; j++) hmm2->pi[j] = hmm1->pi[j];
  hmm2->M = hmm1->M;
  hmm2->syms = cvector(1, hmm2->M);
  for (j = 1; j <= hmm2->M; j++) hmm2->syms[j] = hmm1->syms[j];
  hmm2->a = dmatrix(1, hmm2->N, 1, hmm2->N);
  for (j = 1; j <= hmm2->N; j++)
    for (i = 1; i <= hmm2->N; i++) hmm2->a[j][i] = hmm1->a[j][i];
  hmm2->b = dmatrix(1, hmm2->N, 1, hmm2->M);
  for (i = 1; i <= hmm2->N; i++)
    for (j = 1; j <= hmm2->M; j++) hmm2->b[i][j] = hmm1->b[i][j];
  hmm2->scale = dvector(1, hmm2->N);
  for (j = 1; j <= hmm2->N; j++) hmm2->scale[j] = hmm1->scale[j];
}