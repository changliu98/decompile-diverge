minfft_aux *__cdecl minfft_mkaux_realdft_1d(int N)
{
    minfft_aux *a;

    // Check if N is positive and a power of two
    if (N > 0 && ((N - 1) & N) == 0)
    {
        a = (minfft_aux *)malloc(sizeof(minfft_aux));
        if (a)
        {
            a->N = N;
            
            // Base case for small N
            if (N < 4)
            {
                a->t = NULL;
                a->e = NULL;
                a->sub1 = NULL;
                a->sub2 = NULL;
                return a;
            }

            a->t = malloc(sizeof(minfft_real) * 2 * (N / 2)); // 16 bytes per element pair
            if (a->t)
            {
                a->e = malloc(sizeof(minfft_real) * 2 * (N / 4)); // 16 bytes per element pair
                if (a->e)
                {
                    minfft_real *e = (minfft_real *)a->e;
                    for (int n = 0; n < N / 4; ++n)
                    {
                        // Storing complex twiddle factors (cosine, -sine)
                        e[0] = ncos(-n, N);
                        e[1] = nsin(-n, N);
                        e += 2;
                    }
                    
                    a->sub1 = minfft_mkaux_dft_1d(N / 2);
                    a->sub2 = NULL;
                    return a;
                }
            }
        }
        minfft_free_aux(a);
    }
    
    return NULL;
}