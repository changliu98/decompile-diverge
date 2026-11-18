int __cdecl func0(int *arr, int n)
{
  int i; // [rsp+0h] [rbp-18h]
  int maxEle; // [rsp+4h] [rbp-14h]
  int minEle; // [rsp+8h] [rbp-10h]

  minEle = *arr;
  maxEle = *arr;
  for ( i = 1; i < n; ++i )
  {
    if ( arr[i] < minEle )
      minEle = arr[i];
    if ( arr[i] > maxEle )
      maxEle = arr[i];
  }
  return maxEle - minEle;
}