void __cdecl func0(int *test_list, int n, int *result)
{
  int i; // [rsp+0h] [rbp-1Ch]

  *result = test_list[n - 1];
  for ( i = 1; i < n; ++i )
    result[i] = test_list[i - 1];
}