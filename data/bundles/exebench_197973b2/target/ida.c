void __cdecl computesizes(int *nums, int ntotal, int *narray, int *nhash)
{
  int v4; // eax
  int v5; // [rsp+0h] [rbp-38h]
  bool v6; // [rsp+7h] [rbp-31h]
  int n; // [rsp+8h] [rbp-30h]
  int na; // [rsp+Ch] [rbp-2Ch]
  int a; // [rsp+10h] [rbp-28h]
  int i; // [rsp+14h] [rbp-24h]

  a = *nums;
  na = *nums;
  v4 = 0;
  if ( !*nums )
    v4 = -1;
  n = v4;
  for ( i = 1; ; ++i )
  {
    v6 = 0;
    if ( a < *narray )
      v6 = *narray >= 1 << (i - 1);
    if ( !v6 )
      break;
    if ( nums[i] > 0 )
    {
      a += nums[i];
      if ( a >= 1 << (i - 1) )
      {
        n = i;
        na = a;
      }
    }
  }
  *nhash = ntotal - na;
  if ( n == -1 )
    v5 = 0;
  else
    v5 = 1 << n;
  *narray = v5;
}