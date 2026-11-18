bool __cdecl find_triplet_with_sum(int *arr, int arr_size, int target_sum, int *triplet)
{
  int k; 
  int j; 
  int i; 

  for ( i = 0; i < arr_size - 2; ++i )
  {
    for ( j = i + 1; j < arr_size - 1; ++j )
    {
      for ( k = j + 1; k < arr_size; ++k )
      {
        if ( arr[k] + arr[j] + arr[i] == target_sum )
        {
          triplet[0] = arr[i];
          triplet[1] = arr[j];
          triplet[2] = arr[k];
          return true;
        }
      }
    }
  }
  return false;
}