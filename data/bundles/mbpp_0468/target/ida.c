int __cdecl func0(int *arr, int n)
{
  int *v3; // [rsp+0h] [rbp-40h] BYREF
  int i_1; // [rsp+Ch] [rbp-34h]
  int maxVal; // [rsp+10h] [rbp-30h]
  int j; // [rsp+14h] [rbp-2Ch]
  int i_0; // [rsp+18h] [rbp-28h]
  int i; // [rsp+1Ch] [rbp-24h]
  unsigned __int64 __vla_expr0; // [rsp+20h] [rbp-20h]
  int **v10; // [rsp+28h] [rbp-18h]
  int na; // [rsp+34h] [rbp-Ch]
  int *arra; // [rsp+38h] [rbp-8h]

  arra = arr;
  na = n;
  v10 = &v3;
  v3 = (int *)((char *)&v3 - ((4LL * (unsigned int)n + 15) & 0xFFFFFFFFFFFFFFF0LL));
  __vla_expr0 = (unsigned int)n;
  for ( i = 0; i < na; ++i )
    v3[i] = arra[i];
  for ( i_0 = 1; i_0 < na; ++i_0 )
  {
    for ( j = 0; j < i_0; ++j )
    {
      if ( arra[i_0] > arra[j] && v3[i_0] < arra[i_0] * v3[j] )
        v3[i_0] = arra[i_0] * v3[j];
    }
  }
  maxVal = *v3;
  for ( i_1 = 1; i_1 < na; ++i_1 )
  {
    if ( v3[i_1] > maxVal )
      maxVal = v3[i_1];
  }
  return maxVal;
}