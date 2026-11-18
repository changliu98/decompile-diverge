void chmm_copy(CHMM *hmm1, CHMM *hmm2)
{
	int i, j, k;

	hmm2->N = hmm1->N;
	hmm2->nN = (char *) cvector(1, hmm2->N);
	for (i = 1; i <= hmm2->N; i++) {
		hmm2->nN[i] = hmm1->nN[i];
	}

	hmm2->D = hmm1->D;
	hmm2->nD = (char *) cvector(1, hmm2->D);
	for (i = 1; i <= hmm2->D; i++) {
		hmm2->nD[i] = hmm1->nD[i];
	}

	hmm2->A = (double **) dmatrix(1, hmm2->N, 1, hmm2->N);

	for (i = 1; i <= hmm2->N; i++) {
		for (j = 1; j <= hmm2->N; j++) {
			hmm2->A[i][j] = hmm1->A[i][j];
		}
	}

	hmm2->B.miu = (double **) dmatrix(1, hmm2->N, 1, hmm2->D);
	hmm2->B.cov = (double **) dmatrix(1, hmm2->N, 1, hmm2->D);
	hmm2->B.cov_inv = (double **) dmatrix(1, hmm2->N, 1, hmm2->D);
	for (j = 1; j <= hmm2->N; j++) {
		for (k = 1; k <= hmm2->D; k++) {
			hmm2->B.miu[j][k] = hmm1->B.miu[j][k];
			hmm2->B.cov[j][k] = hmm1->B.cov[j][k];
			hmm2->B.cov_inv[j][k] = hmm1->B.cov_inv[j][k];
		}
	}

	hmm2->pi = (double *) dvector(1, hmm2->N);
	for (i = 1; i <= hmm2->N; i++) {
		hmm2->pi[i] = hmm1->pi[i];
	}
}