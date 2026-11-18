minfft_aux * minfft_mkaux_t2t3_1d(int N)
{
     minfft_aux *a = NULL;
     int n;
     minfft_real *e;

     if (N <= 0 || (N&(N-1)))
          return NULL;

     a = (minfft_aux*)malloc(sizeof(minfft_aux));
     if (!a) goto fail;

     a->N = N;

     if (N > 1) {
          a->t = (minfft_real*)malloc(sizeof(minfft_real)*(N+2));
          if (!a->t) goto fail;

          a->e = (minfft_real*)malloc(sizeof(minfft_real)*N*2);
          if (!a->e) goto fail;

          e = a->e;
          for (n = 0; n < N/2; ++n) {
               *e++ = ncos(-n, 4*N);
               *e++ = nsin(-n, 4*N);
          }
     } else {
          a->t = NULL;
          a->e = NULL;
     }

     a->sub1 = minfft_mkaux_realdft_1d(N);
     if (!a->sub1) goto fail;

     a->sub2 = NULL;

     return a;

fail:
     minfft_free_aux(a);

     return NULL;
}