bool __cdecl func0(int *test_tup1, int *test_tup2, int size)
{
  int i; // [rsp+0h] [rbp-1Ch]
  char res; // [rsp+7h] [rbp-15h]

  res = 1;
  for ( i = 0; i < size; ++i )
  {
    if ( test_tup1[i] <= test_tup2[i] )
      return 0;
  }
  return res;
}