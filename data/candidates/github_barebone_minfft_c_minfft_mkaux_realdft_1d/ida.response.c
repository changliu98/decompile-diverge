minfft_aux *__cdecl minfft_mkaux_realdft_1d(int N)
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
      if ( N < 4 )
      {
        a->t = 0LL;
        a->e = 0LL;
        a->sub1 = 0LL;
LABEL_13:
        a->sub2 = 0LL;
        return a;
      }
      a->t = malloc(16LL * (N / 2));
      if ( a->t )
      {
        a->e = malloc(16LL * (N / 4));
        if ( a->e )
        {
          e = (minfft_real *)a->e;
          for ( n = 0; n < N / 4; ++n )
          {
            *e = ncos(-n, N);
            v1 = nsin(-n, N);
            v2 = e + 1;
            e += 2;
            *v2 = v1;
          }
          a->sub1 = minfft_mkaux_dft_1d(N / 2);
          goto LABEL_13;
        }
      }
    }
    minfft_free_aux(a);
    return 0LL;
  }
  return 0LL;
}