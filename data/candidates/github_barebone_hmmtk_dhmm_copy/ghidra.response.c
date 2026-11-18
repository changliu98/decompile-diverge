void dhmm_copy(DHMM *hmm1,DHMM *hmm2)

{
  char *pcVar1;
  double **ppdVar2;
  double *pdVar3;
  int k;
  int j;
  int i;
  DHMM *hmm2_local;
  DHMM *hmm1_local;
  
  hmm2->N = hmm1->N;
  pcVar1 = cvector(1,hmm2->N);
  hmm2->nN = pcVar1;
  for (i = 1; i <= hmm2->N; i = i + 1) {
    hmm2->nN[i] = hmm1->nN[i];
  }
  hmm2->M = hmm1->M;
  pcVar1 = cvector(1,hmm2->M);
  hmm2->nM = pcVar1;
  for (i = 1; i <= hmm2->M; i = i + 1) {
    hmm2->nM[i] = hmm1->nM[i];
  }
  ppdVar2 = dmatrix(1,hmm2->N,1,hmm2->N);
  hmm2->A = ppdVar2;
  for (i = 1; i <= hmm2->N; i = i + 1) {
    for (j = 1; j <= hmm2->N; j = j + 1) {
      hmm2->A[i][j] = hmm1->A[i][j];
    }
  }
  ppdVar2 = dmatrix(1,hmm2->N,1,hmm2->M);
  hmm2->B = ppdVar2;
  for (j = 1; j <= hmm2->N; j = j + 1) {
    for (k = 1; k <= hmm2->M; k = k + 1) {
      hmm2->B[j][k] = hmm1->B[j][k];
    }
  }
  pdVar3 = dvector(1,hmm2->N);
  hmm2->pi = pdVar3;
  for (i = 1; i <= hmm2->N; i = i + 1) {
    hmm2->pi[i] = hmm1->pi[i];
  }
  return;
}