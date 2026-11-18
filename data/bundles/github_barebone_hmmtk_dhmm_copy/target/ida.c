void __cdecl dhmm_copy(DHMM *hmm1, DHMM *hmm2)
{
  int k; // [rsp+4h] [rbp-1Ch]
  int j; // [rsp+8h] [rbp-18h]
  int ja; // [rsp+8h] [rbp-18h]
  int i; // [rsp+Ch] [rbp-14h]
  int ia; // [rsp+Ch] [rbp-14h]
  int ib; // [rsp+Ch] [rbp-14h]
  int ic; // [rsp+Ch] [rbp-14h]

  hmm2->N = hmm1->N;
  hmm2->nN = cvector(1, hmm2->N);
  for ( i = 1; i <= hmm2->N; ++i )
    hmm2->nN[i] = hmm1->nN[i];
  hmm2->M = hmm1->M;
  hmm2->nM = cvector(1, hmm2->M);
  for ( ia = 1; ia <= hmm2->M; ++ia )
    hmm2->nM[ia] = hmm1->nM[ia];
  hmm2->A = dmatrix(1, hmm2->N, 1, hmm2->N);
  for ( ib = 1; ib <= hmm2->N; ++ib )
  {
    for ( j = 1; j <= hmm2->N; ++j )
      hmm2->A[ib][j] = hmm1->A[ib][j];
  }
  hmm2->B = dmatrix(1, hmm2->N, 1, hmm2->M);
  for ( ja = 1; ja <= hmm2->N; ++ja )
  {
    for ( k = 1; k <= hmm2->M; ++k )
      hmm2->B[ja][k] = hmm1->B[ja][k];
  }
  hmm2->pi = dvector(1, hmm2->N);
  for ( ic = 1; ic <= hmm2->N; ++ic )
    hmm2->pi[ic] = hmm1->pi[ic];
}