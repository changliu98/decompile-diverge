minfft_aux *__cdecl minfft_mkaux_dft_1d(int N) {
    // Return NULL if N is not a positive power of 2
    if (N <= 0 || ((N - 1) & N) != 0)
        return NULL;

    minfft_aux *a = (minfft_aux *)malloc(sizeof(minfft_aux));
    if (!a)
        return NULL;

    a->N = N;
    a->t = NULL;
    a->e = NULL;
    a->sub1 = NULL;
    a->sub2 = NULL;

    // Base case: no twiddle factors needed for very small sizes
    if (N < 16)
        return a;

    a->t = malloc(16 * N);
    if (!a->t) {
        minfft_free_aux(a);
        return NULL;
    }

    a->e = malloc(16 * N);
    if (!a->e) {
        minfft_free_aux(a);
        return NULL;
    }

    minfft_real *e = a->e;
    int Na = N;

    // Precompute twiddle factors for each level of the FFT
    while (Na >= 16) {
        for (int n = 0; n < Na / 4; ++n) {
            e[0] = ncos(-n, Na);
            e[1] = nsin(-n, Na);
            e[2] = ncos(-3 * n, Na);
            e[3] = nsin(-3 * n, Na);
            e += 4;
        }
        Na /= 2;
    }

    return a;
}