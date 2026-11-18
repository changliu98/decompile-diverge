void __cdecl split(int64_t *I, int64_t *V, int64_t start, int64_t len, int64_t h)
{
  int64_t kk; // [rsp+10h] [rbp-60h]
  int64_t kka; // [rsp+10h] [rbp-60h]
  int64_t jj; // [rsp+18h] [rbp-58h]
  int64_t jja; // [rsp+18h] [rbp-58h]
  int64_t tmpa; // [rsp+20h] [rbp-50h]
  int64_t tmp; // [rsp+20h] [rbp-50h]
  int64_t tmpb; // [rsp+20h] [rbp-50h]
  int64_t x; // [rsp+28h] [rbp-48h]
  int64_t xa; // [rsp+28h] [rbp-48h]
  int64_t k; // [rsp+30h] [rbp-40h]
  int64_t ka; // [rsp+30h] [rbp-40h]
  int64_t j; // [rsp+38h] [rbp-38h]
  int64_t ja; // [rsp+38h] [rbp-38h]
  int64_t i; // [rsp+40h] [rbp-30h]
  int64_t ia; // [rsp+40h] [rbp-30h]
  int64_t ib; // [rsp+40h] [rbp-30h]
  int64_t ic; // [rsp+40h] [rbp-30h]
  int64_t id; // [rsp+40h] [rbp-30h]

  if ( len >= 16 )
  {
    xa = V[h + I[len / 2 + start]];
    jj = 0LL;
    kk = 0LL;
    for ( ib = start; ib < len + start; ++ib )
    {
      if ( V[h + I[ib]] < xa )
        ++jj;
      if ( V[h + I[ib]] == xa )
        ++kk;
    }
    jja = jj + start;
    kka = kk + jja;
    ic = start;
    ja = 0LL;
    ka = 0LL;
    while ( ic < jja )
    {
      if ( V[h + I[ic]] >= xa )
      {
        tmp = I[ic];
        if ( V[h + tmp] == xa )
        {
          I[ic] = I[ja + jja];
          I[ja + jja] = tmp;
          ++ja;
        }
        else
        {
          I[ic] = I[ka + kka];
          I[ka + kka] = tmp;
          ++ka;
        }
      }
      else
      {
        ++ic;
      }
    }
    while ( ja + jja < kka )
    {
      if ( V[h + I[ja + jja]] == xa )
      {
        ++ja;
      }
      else
      {
        tmpb = I[ja + jja];
        I[ja + jja] = I[ka + kka];
        I[ka + kka] = tmpb;
        ++ka;
      }
    }
    if ( jja > start )
      split(I, V, start, jja - start, h);
    for ( id = 0LL; id < kka - jja; ++id )
      V[I[id + jja]] = kka - 1;
    if ( jja == kka - 1 )
      I[jja] = -1LL;
    if ( len + start > kka )
      split(I, V, kka, len + start - kka, h);
  }
  else
  {
    for ( k = start; k < len + start; k += j )
    {
      j = 1LL;
      x = V[h + I[k]];
      for ( i = 1LL; i + k < len + start; ++i )
      {
        if ( V[h + I[i + k]] < x )
        {
          x = V[h + I[i + k]];
          j = 0LL;
        }
        if ( V[h + I[i + k]] == x )
        {
          tmpa = I[j + k];
          I[j + k] = I[i + k];
          I[i + k] = tmpa;
          ++j;
        }
      }
      for ( ia = 0LL; ia < j; ++ia )
        V[I[ia + k]] = j + k - 1;
      if ( j == 1 )
        I[k] = -1LL;
    }
  }
}