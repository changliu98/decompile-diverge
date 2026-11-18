bool __cdecl is_valid_sequence(const int *arr, int arr_size)
{
  int i;

  if ( !arr_size )
    return 1;
    
  for ( i = 1; i < arr_size; ++i )
  {
    if ( arr[i] < arr[i - 1] )
      return 0;
      
    if ( i >= 2 && arr[i] == arr[i - 1] && arr[i] == arr[i - 2] )
      return 0;
  }
  
  return 1;
}