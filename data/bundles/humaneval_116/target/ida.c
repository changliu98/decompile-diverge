void __cdecl func0(int *arr, int size)
{
  int j; // [rsp+0h] [rbp-24h]
  int i; // [rsp+4h] [rbp-20h]
  int temp; // [rsp+8h] [rbp-1Ch]
  int y; // [rsp+Ch] [rbp-18h]
  int x; // [rsp+10h] [rbp-14h]
  int xa; // [rsp+10h] [rbp-14h]
  int count_ones; // [rsp+14h] [rbp-10h]
  int count_onesa; // [rsp+14h] [rbp-10h]

  for ( i = 0; i < size; ++i )
  {
    for ( j = i + 1; j < size; ++j )
    {
      count_ones = 0;
      x = arr[i];
      y = arr[j];
      while ( x > 0 )
      {
        count_ones += x & 1;
        x >>= 1;
      }
      xa = count_ones;
      count_onesa = 0;
      while ( y > 0 )
      {
        count_onesa += y & 1;
        y >>= 1;
      }
      if ( count_onesa < xa || count_onesa == xa && arr[j] < arr[i] )
      {
        temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
      }
    }
  }
}