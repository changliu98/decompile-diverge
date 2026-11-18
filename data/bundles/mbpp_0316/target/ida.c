int __cdecl func0(int *A, int n, int x)
{
  int mid; // [rsp+0h] [rbp-20h]
  int result; // [rsp+4h] [rbp-1Ch]
  int right; // [rsp+8h] [rbp-18h]
  int left; // [rsp+Ch] [rbp-14h]

  left = 0;
  right = n - 1;
  result = -1;
  while ( left <= right )
  {
    mid = (right + left) / 2;
    if ( x == A[mid] )
    {
      result = (right + left) / 2;
      left = mid + 1;
    }
    else if ( x >= A[mid] )
    {
      left = mid + 1;
    }
    else
    {
      right = mid - 1;
    }
  }
  return result;
}