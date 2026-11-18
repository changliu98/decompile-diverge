int __cdecl func0(int *arr, int n)
{
  int j; // [rsp+0h] [rbp-18h]
  int i; // [rsp+4h] [rbp-14h]
  int ans; // [rsp+8h] [rbp-10h]

  ans = 0;
  for ( i = 0; i < n; ++i )
  {
    for ( j = i + 1; j < n; ++j )
      ans += arr[j] ^ arr[i];
  }
  return ans;
}