float __cdecl binary_search(float value, float *array, int size)
{
  float x; // [rsp+0h] [rbp-24h]
  int mid; // [rsp+4h] [rbp-20h]
  int high; // [rsp+8h] [rbp-1Ch]
  int low; // [rsp+Ch] [rbp-18h]

  if ( value == *array )
    return 0.0;
  if ( *array > value )
    return -1.0;
  if ( value > array[size - 1] )
    return -1.0;
  if ( value == array[size - 1] )
    return (float)(size - 1);
  low = 0;
  high = size - 1;
  while ( low <= high )
  {
    mid = (high + low) / 2;
    if ( array[mid] <= value )
    {
      if ( value <= array[mid] )
        return (float)mid;
      low = mid + 1;
    }
    else
    {
      high = mid - 1;
    }
  }
  x = (float)(value - array[high]) / (float)(array[low] - array[high]);
  return (double)high * (1.0 - x) + (float)((float)low * x);
}