void chmm_copy(CHMM *hmm1,CHMM *hmm2)

{
  char *pcVar1;
  double **ppdVar2;
  double *pdVar3;
  int k;
  int j;
  int i;
  CHMM *hmm2_local;
  CHMM *hmm1_local;
  
  hmm2->N = hmm1->N;
  pcVar1 = cvector(1,hmm2->N);
  hmm2->nN = pcVar1;
  for (i = 1; i <= hmm2->N; i = i + 1) {
    hmm2->nN[i] = hmm1->nN[i];
  }
  hmm2->D = hmm1->D;
  pcVar1 = cvector(1,hmm2->D);
  hmm2->nD = pcVar1;
  for (i = 1; i <= hmm2->D; i = i + 1) {
    hmm2->nD[i] = hmm1->nD[i];
  }
  ppdVar2 = dmatrix(1,hmm2->N,1,hmm2->N);
  hmm2->A = ppdVar2;
  for (i = 1; i <= hmm2->N; i = i + 1) {
    for (j = 1; j <= hmm2->N; j = j + 1) {
      hmm2->A[i][j] = hmm1->A[i][j];
    }
  }
  ppdVar2 = dmatrix(1,hmm2->N,1,hmm2->D);
  (hmm2->B).miu = ppdVar2;
  ppdVar2 = dmatrix(1,hmm2->N,1,hmm2->D);
  (hmm2->B).cov = ppdVar2;
  ppdVar2 = dmatrix(1,hmm2->N,1,hmm2->D);
  (hmm2->B).cov_inv = ppdVar2;
  for (j = 1; j <= hmm2->N; j = j + 1) {
    for (k = 1; k <= hmm2->D; k = k + 1) {
      (hmm2->B).miu[j][k] = (hmm1->B).miu[j][k];
      (hmm2->B).cov[j][k] = (hmm1->B).cov[j][k];
      (hmm2->B).cov_inv[j][k] = (hmm1->B).cov_inv[j][k];
    }
  }
  pdVar3 = dvector(1,hmm2->N);
  hmm2->pi = pdVar3;
  for (i = 1; i <= hmm2->N; i = i + 1) {
    hmm2->pi[i] = hmm1->pi[i];
  }
  return;
}