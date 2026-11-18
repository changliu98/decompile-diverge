__int64 __cdecl func0(int n, int *primes, int primesSize)
{
  __int64 v3; // rdx
  int v4; // ecx
  __int64 result; // [rsp+8h] [rbp-48h]
  __int64 next_ugly; // [rsp+10h] [rbp-40h]
  int j; // [rsp+18h] [rbp-38h]
  int ja; // [rsp+18h] [rbp-38h]
  int i; // [rsp+1Ch] [rbp-34h]
  int ia; // [rsp+1Ch] [rbp-34h]
  __int64 *values; // [rsp+20h] [rbp-30h]
  int *indices; // [rsp+28h] [rbp-28h]
  __int64 *uglies; // [rsp+30h] [rbp-20h]

  uglies = (__int64 *)malloc(8LL * n);
  indices = (int *)calloc(primesSize, 4uLL);
  values = (__int64 *)malloc(8LL * primesSize);
  *uglies = 1LL;
  for ( i = 0; i < primesSize; ++i )
    values[i] = primes[i];
  for ( ia = 1; ia < n; ++ia )
  {
    next_ugly = *values;
    for ( j = 1; j < primesSize; ++j )
    {
      if ( values[j] < next_ugly )
        next_ugly = values[j];
    }
    uglies[ia] = next_ugly;
    for ( ja = 0; ja < primesSize; ++ja )
    {
      if ( values[ja] == next_ugly )
      {
        v3 = primes[ja];
        v4 = indices[ja] + 1;
        indices[ja] = v4;
        values[ja] = uglies[v4] * v3;
      }
    }
  }
  result = uglies[n - 1];
  free(uglies);
  free(indices);
  free(values);
  return result;
}