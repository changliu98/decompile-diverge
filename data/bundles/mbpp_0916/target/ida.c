bool __cdecl func0(int *A, int arr_size, int sum, int *triplet)
{
  int k; // [rsp+0h] [rbp-2Ch]
  int j; // [rsp+4h] [rbp-28h]
  int i; // [rsp+8h] [rbp-24h]

  for ( i = 0; i < arr_size - 2; ++i )
  {
    for ( j = i + 1; j < arr_size - 1; ++j )
    {
      for ( k = j + 1; k < arr_size; ++k )
      {
        if ( A[k] + A[j] + A[i] == sum )
        {
          *triplet = A[i];
          triplet[1] = A[j];
          triplet[2] = A[k];
          return 1;
        }
      }
    }
  }
  return 0;
}