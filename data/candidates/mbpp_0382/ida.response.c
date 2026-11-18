int __cdecl func0(int *A, int n)
{
  int mid; // [rsp+8h] [rbp-20h]
  int right; // [rsp+Ch] [rbp-1Ch]
  int left; // [rsp+10h] [rbp-18h]

  left = 0;
  right = n - 1;
  while ( left <= right )
  {
    if ( A[left] <= A[right] )
      return left;
    mid = (right + left) / 2;
    if ( A[mid] <= A[(mid + 1) % n] && A[mid] <= A[(n + (right + left) / 2 - 1) % n] )
      return (right + left) / 2;
    if ( A[mid] > A[right] )
    {
      if ( A[mid] >= A[left] )
        left = mid + 1;
    }
    else
    {
      right = mid - 1;
    }
  }
  return -1;
}