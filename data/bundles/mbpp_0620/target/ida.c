int __cdecl func0(int *a, int n)
{
  int *v3; // [rsp+0h] [rbp-40h] BYREF
  int i_0; // [rsp+Ch] [rbp-34h]
  int max_val; // [rsp+10h] [rbp-30h]
  int j; // [rsp+14h] [rbp-2Ch]
  int mxm; // [rsp+18h] [rbp-28h]
  int i; // [rsp+1Ch] [rbp-24h]
  unsigned __int64 __vla_expr0; // [rsp+20h] [rbp-20h]
  int **v10; // [rsp+28h] [rbp-18h]
  int na; // [rsp+34h] [rbp-Ch]
  int *aa; // [rsp+38h] [rbp-8h]

  aa = a;
  na = n;
  v10 = &v3;
  v3 = (int *)((char *)&v3 - ((4LL * (unsigned int)n + 15) & 0xFFFFFFFFFFFFFFF0LL));
  __vla_expr0 = (unsigned int)n;
  v3[n - 1] = 1;
  for ( i = na - 2; i >= 0; --i )
  {
    mxm = 0;
    for ( j = i + 1; j < na; ++j )
    {
      if ( (!(aa[j] % aa[i]) || !(aa[i] % aa[j])) && mxm < v3[j] )
        mxm = v3[j];
    }
    v3[i] = mxm + 1;
  }
  max_val = *v3;
  for ( i_0 = 1; i_0 < na; ++i_0 )
  {
    if ( max_val < v3[i_0] )
      max_val = v3[i_0];
  }
  return max_val;
}