int *__cdecl func0(int *l1, int size1, int *l2, int size2, int *out_size)
{
  int temp;
  int is_duplicate;
  int m;
  int j;
  int i;
  int k;
  int *out;

  // Allocate memory for the intersection, maximum possible size is size1
  out = (int *)malloc(4LL * size1);
  k = 0;
  
  // Find intersection of l1 and l2 without duplicates
  for ( i = 0; i < size1; ++i )
  {
    // Check if the element is already in the output array
    is_duplicate = 0;
    for ( m = 0; m < k; ++m )
    {
      if ( out[m] == l1[i] )
      {
        is_duplicate = 1;
        break;
      }
    }
    
    // If it's not a duplicate, check if it exists in l2
    if ( !is_duplicate )
    {
      for ( j = 0; j < size2; ++j )
      {
        if ( l1[i] == l2[j] )
        {
          out[k++] = l1[i];
          break;
        }
      }
    }
  }
  
  // Sort the output array using bubble sort
  for ( i = 0; i < k - 1; ++i )
  {
    for ( j = 0; j < k - i - 1; ++j )
    {
      if ( out[j] > out[j + 1] )
      {
        temp = out[j];
        out[j] = out[j + 1];
        out[j + 1] = temp;
      }
    }
  }
  
  *out_size = k;
  return out;
}