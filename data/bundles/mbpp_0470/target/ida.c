void __cdecl func0(const int *test_tup, int size, int *result)
{
  int i; // [rsp+0h] [rbp-1Ch]

  for ( i = 0; i < size - 1; ++i )
    result[i] = test_tup[i + 1] + test_tup[i];
}