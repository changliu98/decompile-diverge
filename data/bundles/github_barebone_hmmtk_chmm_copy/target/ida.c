void __cdecl chmm_copy(CHMM *hmm1, CHMM *hmm2)
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
  hmm2->D = hmm1->D;
  hmm2->nD = cvector(1, hmm2->D);
  for ( ia = 1; ia <= hmm2->D; ++ia )
    hmm2->nD[ia] = hmm1->nD[ia];
  hmm2->A = dmatrix(1, hmm2->N, 1, hmm2->N);
  for ( ib = 1; ib <= hmm2->N; ++ib )
  {
    for ( j = 1; j <= hmm2->N; ++j )
      hmm2->A[ib][j] = hmm1->A[ib][j];
  }
  hmm2->B.miu = dmatrix(1, hmm2->N, 1, hmm2->D);
  hmm2->B.cov = dmatrix(1, hmm2->N, 1, hmm2->D);
  hmm2->B.cov_inv = dmatrix(1, hmm2->N, 1, hmm2->D);
  for ( ja = 1; ja <= hmm2->N; ++ja )
  {
    for ( k = 1; k <= hmm2->D; ++k )
    {
      hmm2->B.miu[ja][k] = hmm1->B.miu[ja][k];
      hmm2->B.cov[ja][k] = hmm1->B.cov[ja][k];
      hmm2->B.cov_inv[ja][k] = hmm1->B.cov_inv[ja][k];
    }
  }
  hmm2->pi = dvector(1, hmm2->N);
  for ( ic = 1; ic <= hmm2->N; ++ic )
    hmm2->pi[ic] = hmm1->pi[ic];
}