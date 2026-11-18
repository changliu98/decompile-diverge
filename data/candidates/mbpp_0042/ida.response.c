int __cdecl func0(int *arr, int n)
{
  int j; // [rsp+0h] [rbp-1Ch]
  int count; // [rsp+4h] [rbp-18h]
  int i; // [rsp+8h] [rbp-14h]
  int sum; // [rsp+Ch] [rbp-10h]

  sum = 0;
  for ( i = 0; i < n; ++i )
  {
    count = 1;
    for ( j = 0; j < n; ++j )
    {
      if ( arr[j] == arr[i] && j != i )
        ++count;
    }
    if ( count > 1 )
      sum += arr[i];
  }
  return sum;
}