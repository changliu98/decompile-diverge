int __cdecl func0(int *arr, int n, int sum)
{
  int j; // [rsp+0h] [rbp-1Ch]
  int i; // [rsp+4h] [rbp-18h]
  int count; // [rsp+8h] [rbp-14h]

  count = 0;
  for ( i = 0; i < n; ++i )
  {
    for ( j = i + 1; j < n; ++j )
    {
      if ( arr[j] + arr[i] == sum )
        ++count;
    }
  }
  return count;
}