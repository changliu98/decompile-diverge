int __cdecl stb_combinations(int n, int t, int ***combinations)
{
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  double v7; // [rsp+0h] [rbp-40h]
  double v8; // [rsp+8h] [rbp-38h]
  int x; // [rsp+10h] [rbp-30h]
  int j; // [rsp+14h] [rbp-2Ch]
  int ja; // [rsp+14h] [rbp-2Ch]
  int jb; // [rsp+14h] [rbp-2Ch]
  int nCr; // [rsp+18h] [rbp-28h]
  int current; // [rsp+1Ch] [rbp-24h]
  int *c; // [rsp+20h] [rbp-20h]
  int **comb; // [rsp+28h] [rbp-18h] BYREF
  int ***combinationsa; // [rsp+30h] [rbp-10h]
  int ta; // [rsp+38h] [rbp-8h]
  int na; // [rsp+3Ch] [rbp-4h]

  na = n;
  ta = t;
  combinationsa = combinations;
  c = (int *)calloc(t + 3, 4uLL);
  current = 0;
  v8 = stb_factorial(n);
  v7 = stb_factorial(t);
  nCr = (int)(v8 / (v7 * stb_factorial(n - t)));
  comb = (int **)stb_allocmat(nCr, t, 4uLL);
  for ( j = 1; j <= ta; ++j )
    c[j] = j - 1;
  c[ta + 1] = na;
  c[ta + 2] = 0;
  for ( ja = ta; ; ja = jb - 1 )
  {
    v3 = current++;
    stb_visit(c, ta, &comb, v3);
    while ( ja > 0 )
    {
      c[ja] = ja;
      --ja;
      v4 = current++;
      stb_visit(c, ta, &comb, v4);
    }
    while ( c[1] + 1 < c[2] )
    {
      ++c[1];
      v5 = current++;
      stb_visit(c, ta, &comb, v5);
    }
    jb = 2;
    c[1] = 0;
    for ( x = c[2] + 1; x == c[jb + 1]; x = c[jb] + 1 )
    {
      ++jb;
      c[jb - 1] = jb - 2;
    }
    if ( jb > ta )
      break;
    c[jb] = x;
  }
  *combinationsa = comb;
  free(c);
  return nCr;
}