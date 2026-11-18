minfft_aux *__cdecl minfft_mkaux_t2t3_1d(int N) {
    minfft_aux *a = NULL;

    // Check if N is positive and a power of two
    if (N > 0 && ((N - 1) & N) == 0) {
        a = (minfft_aux *)malloc(sizeof(minfft_aux));
        if (a) {
            a->N = N;
            
            if (N < 2) {
                a->t = NULL;
                a->e = NULL;
            } else {
                a->t = malloc(sizeof(minfft_real) * (N + 2));
                if (!a->t)
                    goto err;
                
                a->e = malloc(sizeof(minfft_real) * (2 * (N / 2))); // 16 * (N / 2)
                if (!a->e)
                    goto err;
                
                minfft_real *e = (minfft_real *)a->e;
                for (int n = 0; n < N / 2; ++n) {
                    e[0] = ncos(-n, 4 * N);
                    e[1] = nsin(-n, 4 * N);
                    e += 2;
                }
            }
            
            a->sub1 = minfft_mkaux_realdft_1d(N);
            if (a->sub1) {
                a->sub2 = NULL;
                return a;
            }
        }
err:
        minfft_free_aux(a);
        return NULL;
    }
    
    return NULL;
}