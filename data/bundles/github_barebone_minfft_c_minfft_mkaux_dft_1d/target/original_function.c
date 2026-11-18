minfft_aux*
minfft_mkaux_dft_1d (int N) {
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
	if (N>=16) {
		a->t=malloc(N*sizeof(minfft_cmpl));
		if (a->t==NULL)
			goto err;
		a->e=malloc(N*sizeof(minfft_cmpl));
		if (a->e==NULL)
			goto err;
		e=(minfft_real*)a->e;
		while (N>=16) {
			for (n=0;n<N/4;++n) {
				*e++=ncos(-n,N);
				*e++=nsin(-n,N);
				*e++=ncos(-3*n,N);
				*e++=nsin(-3*n,N);
			}
			N/=2;
		}
	} else {
		a->t=NULL;
		a->e=NULL;
	}
	a->sub1=a->sub2=NULL;
	return a;
err:	/* memory allocation error */
	minfft_free_aux(a);
	return NULL;
}