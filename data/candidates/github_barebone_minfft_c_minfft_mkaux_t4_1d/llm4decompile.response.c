minfft_aux * minfft_mkaux_t4_1d(int N)
{
     minfft_aux *a = NULL;
     int s;

     if(N < 1 || (N & (N - 1))) return NULL;

     a = malloc(sizeof(minfft_aux));
     if(a) {
          a->N = N;
          if(N > 1) {
               a->t = malloc(sizeof(minfft_real) * N / 2);
               if(!a->t) goto fail;
               a->e = malloc(sizeof(minfft_real) * (N + N / 2));
               if(!a->e) goto fail;

               minfft_real *e = a->e;
               for(s = 0; s < N / 2; s++) {
                    *e++ = ncos(-s, 2 * N);
                    *e++ = nsin(-s, 2 * N);
               }
               for(s = 0; s < N; s++) {
                    *e++ = ncos(-(2 * s + 1), 4 * N);
                    *e++ = nsin(-(2 * s + 1), 4 * N);
               }

               a->sub1 = minfft_mkaux_dft_1d(N / 2);
               if(!a->sub1) goto fail;
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