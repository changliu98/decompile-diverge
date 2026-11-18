minfft_aux *__cdecl minfft_mkaux_t4_1d(int N)
{
  minfft_aux *a;
  minfft_real *e;
  int n;

  // Check if N is a positive power of two
  if ( N > 0 && ((N - 1) & N) == 0 )
  {
    a = (minfft_aux *)malloc(sizeof(minfft_aux));
    if ( a )
    {
      a->N = N;
      
      // Base case: N == 1
      if ( N < 2 )
      {
        a->t = NULL;
        a->e = NULL;
        a->sub1 = NULL;
        a->sub2 = NULL;
        return a;
      }
      
      // Allocate temporary buffer
      a->t = malloc(sizeof(minfft_real) * 2 * (N / 2));
      if ( a->t )
      {
        // Allocate twiddle factors (N/2 + N pairs of reals)
        a->e = malloc(sizeof(minfft_real) * 2 * (N + N / 2));
        if ( a->e )
        {
          e = (minfft_real *)a->e;
          
          // First set of twiddle factors
          for ( n = 0; n < N / 2; ++n )
          {
            e[0] = ncos(-n, 2 * N);
            e[1] = nsin(-n, 2 * N);
            e += 2;
          }
          
          // Second set of twiddle factors
          for ( n = 0; n < N; ++n )
          {
            e[0] = ncos(-(2 * n + 1), 8 * N);
            e[1] = nsin(-(2 * n + 1), 8 * N);
            e += 2;
          }
          
          // Allocate recursive sub-transform
          a->sub1 = minfft_mkaux_dft_1d(N / 2);
          if ( a->sub1 )
          {
            a->sub2 = NULL;
            return a;
          }
        }
      }
    }
    // Cleanup and return NULL on any allocation failure
    minfft_free_aux(a);
  }
  return NULL;
}