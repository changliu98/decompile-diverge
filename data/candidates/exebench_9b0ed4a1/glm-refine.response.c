float __cdecl binary_search(float value, float *array, int size)
{
  float ratio; 
  int mid; 
  int high; 
  int low; 

  // Boundary checks: return -1.0 if the target is out of bounds
  if ( value == array[0] )
    return 0.0;
  if ( array[0] > value )
    return -1.0;
  if ( value > array[size - 1] )
    return -1.0;
  if ( value == array[size - 1] )
    return (float)(size - 1);

  // Standard binary search
  low = 0;
  high = size - 1;
  while ( low <= high )
  {
    mid = (high + low) / 2;
    if ( array[mid] <= value )
    {
      // Equivalent to: if (value == array[mid])
      if ( value <= array[mid] )
        return (float)mid;
      low = mid + 1;
    }
    else
    {
      high = mid - 1;
    }
  }

  // If exact match is not found, perform linear interpolation 
  // between the closest lower (array[high]) and higher (array[low]) bounds
  ratio = (float)(value - array[high]) / (float)(array[low] - array[high]);
  
  return (double)high * (1.0 - ratio) + (float)((float)low * ratio);
}