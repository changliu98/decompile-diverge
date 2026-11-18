int __cdecl func0(int *arr, int n)
{
  int v2; // ecx
  int size_v; // [rsp+4h] [rbp-2Ch]
  int *v; // [rsp+8h] [rbp-28h]
  int temp; // [rsp+10h] [rbp-20h]
  int j; // [rsp+14h] [rbp-1Ch]
  int i; // [rsp+18h] [rbp-18h]
  int ia; // [rsp+18h] [rbp-18h]
  int ib; // [rsp+18h] [rbp-18h]
  int count; // [rsp+1Ch] [rbp-14h]
  int ans; // [rsp+20h] [rbp-10h]

  ans = 0;
  count = 0;
  for ( i = 0; i < n - 1; ++i )
  {
    for ( j = 0; j < n - i - 1; ++j )
    {
      if ( arr[j] > arr[j + 1] )
      {
        temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
    }
  }
  v = (int *)malloc(4LL * n);
  size_v = 1;
  *v = *arr;
  for ( ia = 1; ia < n; ++ia )
  {
    if ( arr[ia] != arr[ia - 1] )
    {
      v2 = size_v++;
      v[v2] = arr[ia];
    }
  }
  for ( ib = 0; ib < size_v; ++ib )
  {
    if ( ib > 0 && v[ib] == v[ib - 1] + 1 )
      ++count;
    else
      count = 1;
    if ( ans < count )
      ans = count;
  }
  free(v);
  return ans;
}