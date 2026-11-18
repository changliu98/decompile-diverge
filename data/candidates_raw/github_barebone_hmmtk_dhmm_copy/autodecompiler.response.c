void dhmm_copy(struct hmm_struc *old, struct hmm_struc *new)
{
 int k, l, m;

 new->M = old->M;
 new->del_state = (char *)cvector(1, new->M);
 for (m = 1; m <= new->M; m++)
  new->del_state[m] = old->del_state[m];

 new->N = old->N;
 new->ins_state = (char *)cvector(1, new->N);
 for (m = 1; m <= new->N; m++)
  new->ins_state[m] = old->ins_state[m];

 new->A = (double **)dmatrix(1, new->M, 1, new->M);
 for (m = 1; m <= new->M; m++)
  for (k = 1; k <= new->M; k++)
   new->A[m][k] = old->A[m][k];

 new->B = (double **)dmatrix(1, new->M, 1, new->N);
 for (k = 1; k <= new->M; k++)
  for (l = 1; l <= new->N; l++)
   new->B[k][l] = old->B[k][l];

 new->T = (double *)dvector(1, new->M);
 for (m = 1; m <= new->M; m++)
  new->T[m] = old->T[m];
}