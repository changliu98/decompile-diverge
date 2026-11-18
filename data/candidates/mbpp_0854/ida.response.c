void __cdecl func0(int *rawheap, int size)
{
  int temp; // [rsp+0h] [rbp-18h]
  int j; // [rsp+4h] [rbp-14h]
  int i; // [rsp+8h] [rbp-10h]

  for ( i = size / 2 - 1; i >= 0; --i )
  {
    for ( j = 2 * i + 1; j < size; j = 2 * j + 1 )
    {
      if ( j + 1 < size && rawheap[j] > rawheap[j + 1] )
        ++j;
      if ( rawheap[i] <= rawheap[j] )
        break;
      temp = rawheap[i];
      rawheap[i] = rawheap[j];
      rawheap[j] = temp;
      i = j - 1;
    }
  }
}