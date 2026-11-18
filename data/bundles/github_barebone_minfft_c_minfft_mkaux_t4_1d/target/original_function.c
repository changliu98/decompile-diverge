minfft_aux*
minfft_mkaux_t4_1d (int N) {
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
		a->t=malloc((N/2)*sizeof(minfft_cmpl));
		if (a->t==NULL)
			goto err;
		a->e=malloc((N/2+N)*sizeof(minfft_cmpl));
		if (a->e==NULL)
			goto err;
		e=(minfft_real*)a->e;
		for (n=0;n<N/2;++n) {
			*e++=ncos(-n,2*N);
			*e++=nsin(-n,2*N);
		}
		for (n=0;n<N;++n) {
			*e++=ncos(-(2*n+1),8*N);
			*e++=nsin(-(2*n+1),8*N);
		}
		a->sub1=minfft_mkaux_dft_1d(N/2);
		if (a->sub1==NULL)
			goto err;
	} else {
		a->t=NULL;
		a->e=NULL;
		a->sub1=NULL;
	}
	a->sub2=NULL;
	return a;
err:	/* memory allocation error */
	minfft_free_aux(a);
	return NULL;
}