void dhmm_copy(DHMM *hmm1, DHMM *hmm2)
{
  int i,j,k;

  hmm2->N = hmm1->N;
  hmm2->nN = cvector(1,hmm2->N);
  for(i=1;i<=hmm2->N;i++) hmm2->nN[i] = hmm1->nN[i];

  hmm2->M = hmm1->M;
  hmm2->nM = cvector(1,hmm2->M);
  for(i=1;i<=hmm2->M;i++) hmm2->nM[i] = hmm1->nM[i];

  hmm2->A = dmatrix(1,hmm2->N,1,hmm2->N);
  for(i=1;i<=hmm2->N;i++)
    for(j=1;j<=hmm2->N;j++)
      hmm2->A[i][j] = hmm1->A[i][j];

  hmm2->B = dmatrix(1,hmm2->N,1,hmm2->M);
  for(j=1;j<=hmm2->N;j++)
    for(k=1;k<=hmm2->M;k++)
      hmm2->B[j][k] = hmm1->B[j][k];

  hmm2->pi = dvector(1,hmm2->N);
  for(i=1;i<=hmm2->N;i++) hmm2->pi[i] = hmm1->pi[i];
}