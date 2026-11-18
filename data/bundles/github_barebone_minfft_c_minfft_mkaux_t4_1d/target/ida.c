minfft_aux *__cdecl minfft_mkaux_t4_1d(int N)
{
  minfft_real v1; // xmm0_8
  double *v2; // rax
  minfft_real v3; // xmm0_8
  double *v4; // rax
  minfft_real *e; // [rsp+8h] [rbp-28h]
  int n; // [rsp+14h] [rbp-1Ch]
  int na; // [rsp+14h] [rbp-1Ch]
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
        a->sub1 = 0LL;
LABEL_17:
        a->sub2 = 0LL;
        return a;
      }
      a->t = malloc(16LL * (N / 2));
      if ( a->t )
      {
        a->e = malloc(16LL * (N + N / 2));
        if ( a->e )
        {
          e = (minfft_real *)a->e;
          for ( n = 0; n < N / 2; ++n )
          {
            *e = ncos(-n, 2 * N);
            v1 = nsin(-n, 2 * N);
            v2 = e + 1;
            e += 2;
            *v2 = v1;
          }
          for ( na = 0; na < N; ++na )
          {
            *e = ncos(-(2 * na + 1), 8 * N);
            v3 = nsin(-(2 * na + 1), 8 * N);
            v4 = e + 1;
            e += 2;
            *v4 = v3;
          }
          a->sub1 = minfft_mkaux_dft_1d(N / 2);
          if ( a->sub1 )
            goto LABEL_17;
        }
      }
    }
    minfft_free_aux(a);
    return 0LL;
  }
  return 0LL;
}