int __cdecl Fibonacci_search(int *a, int n, int key)
{
  int k; // [rsp+Ch] [rbp-64h]
  int i; // [rsp+10h] [rbp-60h]
  int mid; // [rsp+14h] [rbp-5Ch]
  int high; // [rsp+18h] [rbp-58h]
  int low; // [rsp+1Ch] [rbp-54h]
  int F[13]; // [rsp+20h] [rbp-50h] BYREF
  int keya; // [rsp+58h] [rbp-18h]
  int na; // [rsp+5Ch] [rbp-14h]
  int *aa; // [rsp+60h] [rbp-10h]

  aa = a;
  na = n;
  keya = key;
  memcpy(F, &unk_2010, sizeof(F));
  low = 1;
  high = na;
  for ( k = 0; na > F[k] - 1; ++k )
    ;
  for ( i = na; i < F[k] - 1; ++i )
    aa[i] = aa[na];
  while ( 1 )
  {
    while ( 1 )
    {
      if ( low > high )
        return 0;
      mid = F[k - 1] + low - 1;
      if ( keya >= aa[mid] )
        break;
      high = F[--k] + low - 2;
    }
    if ( keya <= aa[mid] )
      break;
    low += F[k - 1];
    k -= 2;
  }
  if ( mid > na )
    return na;
  else
    return F[k - 1] + low - 1;
}