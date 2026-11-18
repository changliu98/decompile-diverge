int __cdecl func0(int *arr, int N, int P)
{
  int i; // [rsp+0h] [rbp-18h]
  int current_element; // [rsp+4h] [rbp-14h]

  current_element = 0;
  for ( i = 0; i < N; ++i )
  {
    if ( arr[i] * arr[i] % P == 1 )
      ++current_element;
  }
  return current_element;
}