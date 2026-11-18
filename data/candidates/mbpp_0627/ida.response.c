int __cdecl func0(int *array, int start, int end)
{
  int mid; // [rsp+4h] [rbp-1Ch]

  if ( start > end )
    return end + 1;
  if ( start != array[start] )
    return start;
  mid = (end + start) / 2;
  if ( array[mid] == mid )
    return func0(array, mid + 1, end);
  else
    return func0(array, start, mid);
}