minfft_aux * minfft_mkaux_realdft_1d(int N)
{
     minfft_aux *a = NULL;
     int n;
     minfft_real *e;

     if(N <= 0 || (N & (N-1)))
          return NULL;

     a = malloc(sizeof(minfft_aux));
     if(a) {
          a->N = N;
          if(N > 3) {
               a->t = malloc(sizeof(minfft_real)*2*N/2);
               if(!a->t) goto fail;
               a->e = malloc(sizeof(minfft_real)*2*N/4);
               if(!a->e) goto fail;
               e = a->e;
               for(n = 0; n < N/4; n++) {
                    *e++ = ncos(-n, N);
                    *e++ = nsin(-n, N);
               }
               a->sub1 = minfft_mkaux_dft_1d(N/2);
          } else {
               a->t = NULL;
               a->e = NULL;
               a->sub1 = NULL;
          }
          a->sub2 = NULL;
     }
     return a;
fail:
     minfft_free_aux(a);
     return NULL;
}