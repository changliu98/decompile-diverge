minfft_aux *__cdecl minfft_mkaux_t2t3_1d(int N)
{
  minfft_real v1; // xmm0_8
  double *v2; // rax
  minfft_real *e; // [rsp+8h] [rbp-28h]
  int n; // [rsp+14h] [rbp-1Ch]
  minfft_aux *a; // [rsp+18h] [rbp-18h]

  if ( N > 0 && ((N - 1) & N) == 0 )
  {
    a = (minfft_aux *)malloc(0x28uLL);
    if ( a )
    {
      a->N = N;
      if ( N < 2 )
      {
        a->t = 0LL;
        a->e = 0LL;
      }
      else
      {
        a->t = malloc(8LL * (N + 2));
        if ( !a->t )
          goto err;
        a->e = malloc(16LL * (N / 2));
        if ( !a->e )
          goto err;
        e = (minfft_real *)a->e;
        for ( n = 0; n < N / 2; ++n )
        {
          *e = ncos(-n, 4 * N);
          v1 = nsin(-n, 4 * N);
          v2 = e + 1;
          e += 2;
          *v2 = v1;
        }
      }
      a->sub1 = minfft_mkaux_realdft_1d(N);
      if ( a->sub1 )
      {
        a->sub2 = 0LL;
        return a;
      }
    }
err:
    minfft_free_aux(a);
    return 0LL;
  }
  return 0LL;
}