int __cdecl func0(int *arr, int x, int n)
{
  int mid; // [rsp+0h] [rbp-20h]
  int res; // [rsp+4h] [rbp-1Ch]
  int high; // [rsp+8h] [rbp-18h]
  int low; // [rsp+Ch] [rbp-14h]

  low = 0;
  high = n - 1;
  res = -1;
  while ( low <= high )
  {
    mid = (high + low) / 2;
    if ( arr[mid] <= x )
    {
      if ( arr[mid] >= x )
      {
        res = (high + low) / 2;
        high = mid - 1;
      }
      else
      {
        low = mid + 1;
      }
    }
    else
    {
      high = mid - 1;
    }
  }
  return res;
}