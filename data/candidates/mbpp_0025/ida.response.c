int __cdecl func0(int *arr, int n)
{
  bool v3; // [rsp+1h] [rbp-1Dh]
  int prod; // [rsp+2h] [rbp-1Ch]
  int temp; // [rsp+6h] [rbp-18h]
  int j; // [rsp+Ah] [rbp-14h]
  int i; // [rsp+Eh] [rbp-10h]
  int ia; // [rsp+Eh] [rbp-10h]

  prod = 1;
  for ( i = 1; i < n; ++i )
  {
    temp = arr[i];
    for ( j = i - 1; ; --j )
    {
      v3 = 0;
      if ( j >= 0 )
        v3 = arr[j] > temp;
      if ( !v3 )
        break;
      arr[j + 1] = arr[j];
    }
    arr[j + 1] = temp;
  }
  for ( ia = 0; ia < n; ++ia )
  {
    if ( !ia || arr[ia - 1] != arr[ia] )
      prod *= arr[ia];
  }
  return prod;
}