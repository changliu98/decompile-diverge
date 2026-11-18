minfft_aux *__cdecl minfft_mkaux_dft_1d(int N)
{
  minfft_real v1; // xmm0_8
  double *v2; // rax
  minfft_real *e; // [rsp+8h] [rbp-28h]
  int n; // [rsp+14h] [rbp-1Ch]
  minfft_aux *a; // [rsp+18h] [rbp-18h]
  int Na; // [rsp+24h] [rbp-Ch]

  Na = N;
  if ( N > 0 && ((N - 1) & N) == 0 )
  {
    a = (minfft_aux *)malloc(0x28uLL);
    if ( a )
    {
      a->N = N;
      if ( N < 16 )
      {
        a->t = 0LL;
        a->e = 0LL;
LABEL_16:
        a->sub2 = 0LL;
        a->sub1 = 0LL;
        return a;
      }
      a->t = malloc(16LL * N);
      if ( a->t )
      {
        a->e = malloc(16LL * N);
        if ( a->e )
        {
          e = (minfft_real *)a->e;
          while ( Na >= 16 )
          {
            for ( n = 0; n < Na / 4; ++n )
            {
              *e = ncos(-n, Na);
              e[1] = nsin(-n, Na);
              e[2] = ncos(-3 * n, Na);
              v1 = nsin(-3 * n, Na);
              v2 = e + 3;
              e += 4;
              *v2 = v1;
            }
            Na /= 2;
          }
          goto LABEL_16;
        }
      }
    }
    minfft_free_aux(a);
    return 0LL;
  }
  return 0LL;
}