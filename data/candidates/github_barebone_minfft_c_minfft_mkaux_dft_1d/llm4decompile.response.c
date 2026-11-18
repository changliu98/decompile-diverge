minfft_aux * minfft_mkaux_dft_1d(int N)
{
     minfft_aux *a;
     int s, n;
     minfft_real *e;

     if (N <= 0 || (N & (N - 1)))
          return NULL;

     a = (minfft_aux *) malloc(sizeof(minfft_aux));
     if (a == NULL)
          goto fail;

     a->N = N;

     if (N >= 16) {
          a->t = (minfft_real *) malloc(2 * N * sizeof(minfft_real));
          if (a->t == NULL)
               goto fail;

          a->e = (minfft_real *) malloc(2 * N * sizeof(minfft_real));
          if (a->e == NULL)
               goto fail;

          e = a->e;
          for (s = N; s >= 16; s >>= 1) {
               for (n = 0; n < s / 4; ++n) {
                    *e++ = ncos(-n, s);
                    *e++ = nsin(-n, s);
                    *e++ = ncos(-3 * n, s);
                    *e++ = nsin(-3 * n, s);
               }
          }
     } else {
          a->t = NULL;
          a->e = NULL;
     }

     a->sub1 = NULL;
     a->sub2 = NULL;

     return a;

fail:
     minfft_free_aux(a);
     return NULL;
}