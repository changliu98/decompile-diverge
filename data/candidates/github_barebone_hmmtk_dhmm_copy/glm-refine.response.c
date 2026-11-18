void __cdecl dhmm_copy(DHMM *hmm1, DHMM *hmm2)
{
  int i, j, k;

  // Copy and allocate state counts (N)
  hmm2->N = hmm1->N;
  hmm2->nN = cvector(1, hmm2->N);
  for (i = 1; i <= hmm2->N; ++i)
    hmm2->nN[i] = hmm1->nN[i];

  // Copy and allocate observation symbols (M)
  hmm2->M = hmm1->M;
  hmm2->nM = cvector(1, hmm2->M);
  for (i = 1; i <= hmm2->M; ++i)
    hmm2->nM[i] = hmm1->nM[i];

  // Copy and allocate state transition matrix (A)
  hmm2->A = dmatrix(1, hmm2->N, 1, hmm2->N);
  for (i = 1; i <= hmm2->N; ++i)
    for (j = 1; j <= hmm2->N; ++j)
      hmm2->A[i][j] = hmm1->A[i][j];

  // Copy and allocate emission probability matrix (B)
  hmm2->B = dmatrix(1, hmm2->N, 1, hmm2->M);
  for (i = 1; i <= hmm2->N; ++i)
    for (k = 1; k <= hmm2->M; ++k)
      hmm2->B[i][k] = hmm1->B[i][k];

  // Copy and allocate initial state distribution (pi)
  hmm2->pi = dvector(1, hmm2->N);
  for (i = 1; i <= hmm2->N; ++i)
    hmm2->pi[i] = hmm1->pi[i];
}