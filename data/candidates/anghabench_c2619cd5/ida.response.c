int __cdecl binary_search(int *array, int n, int value)
{
  int middle; // [rsp+0h] [rbp-24h]
  int right; // [rsp+4h] [rbp-20h]
  int left; // [rsp+8h] [rbp-1Ch]

  left = 0;
  right = n - 1;
  while ( left <= right )
  {
    middle = ((right - left) >> 1) + left;
    if ( array[middle] <= value )
    {
      if ( array[middle] >= value )
        return ((right - left) >> 1) + left;
      left = middle + 1;
    }
    else
    {
      right = middle - 1;
    }
  }
  return -1;
}