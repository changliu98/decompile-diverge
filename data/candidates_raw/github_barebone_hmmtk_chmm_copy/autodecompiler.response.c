void chmm_copy(struct hmm *hmm1, struct hmm *hmm2)
{
 int k, l, m;

 hmm2->M = hmm1->M;
 hmm2->states = (char *)cvector(1, hmm2->M);
 for (m = 1; m <= hmm2->M; m++)
  hmm2->states[m] = hmm1->states[m];

 hmm2->N = hmm1->N;
 hmm2->obs = (char *)cvector(1, hmm2->N);
 for (m = 1; m <= hmm2->N; m++)
  hmm2->obs[m] = hmm1->obs[m];

 hmm2->A = (double **)dmatrix(1, hmm2->M, 1, hmm2->M);
 for (k = 1; k <= hmm2->M; k++)
  for (l = 1; l <= hmm2->M; l++)
   hmm2->A[k][l] = hmm1->A[k][l];

 hmm2->E = (double **)dmatrix(1, hmm2->M, 1, hmm2->N);
 hmm2->T = (double **)dmatrix(1, hmm2->M, 1, hmm2->N);
 hmm2->R = (double **)dmatrix(1, hmm2->M, 1, hmm2->N);

 for (k = 1; k <= hmm2->M; k++)
  for (l = 1; l <= hmm2->N; l++) {
   hmm2->E[k][l] = hmm1->E[k][l];
   hmm2->T[k][l] = hmm1->T[k][l];
   hmm2->R[k][l] = hmm1->R[k][l];
  }

 hmm2->init = (double *)dvector(1, hmm2->M);
 for (k = 1; k <= hmm2->M; k++)
  hmm2->init[k] = hmm1->init[k];
}