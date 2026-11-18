int __cdecl func0(int *arr, int n)
{
  int v3; // [rsp+Ch] [rbp-24h]
  int v4; // [rsp+10h] [rbp-20h]
  int i; // [rsp+14h] [rbp-1Ch]
  int min_count; // [rsp+18h] [rbp-18h]
  int max_count; // [rsp+1Ch] [rbp-14h]
  int count; // [rsp+20h] [rbp-10h]

  sortArray(arr, n);
  count = 0;
  max_count = 0;
  min_count = n;
  for ( i = 0; i < n - 1; ++i )
  {
    if ( arr[i] == arr[i + 1] )
    {
      ++count;
    }
    else
    {
      if ( max_count <= count )
        v4 = count;
      else
        v4 = max_count;
      max_count = v4;
      if ( min_count >= count )
        v3 = count;
      else
        v3 = min_count;
      min_count = v3;
      count = 0;
    }
  }
  return max_count - min_count;
}