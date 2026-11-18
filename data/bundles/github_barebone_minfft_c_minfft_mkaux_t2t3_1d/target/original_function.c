minfft_aux*
minfft_mkaux_t2t3_1d (int N) {
	minfft_aux *a;
	int n;
	minfft_real *e;
	if (N<=0 || N&(N-1))
		/* error if N is negative or not a power of two */
		return NULL;
	a=malloc(sizeof(minfft_aux));
	if (a==NULL)
		goto err;
	a->N=N;
	if (N>=2) {
		a->t=malloc((N+2)*sizeof(minfft_real)); /* for in-place real DFT */
		if (a->t==NULL)
			goto err;
		a->e=malloc((N/2)*sizeof(minfft_cmpl));
		if (a->e==NULL)
			goto err;
		e=(minfft_real*)a->e;
		for (n=0;n<N/2;++n) {
			*e++=ncos(-n,4*N);
			*e++=nsin(-n,4*N);
		}
	} else {
		a->t=NULL;
		a->e=NULL;
	}
	a->sub1=minfft_mkaux_realdft_1d(N);
	if (a->sub1==NULL)
		goto err;
	a->sub2=NULL;
	return a;
err:	/* memory allocation error */
	minfft_free_aux(a);
	return NULL;
}