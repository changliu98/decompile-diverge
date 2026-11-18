int __cdecl func0(int n, int *arr)
{
  int i; // [rsp+0h] [rbp-1Ch]
  int freq; // [rsp+4h] [rbp-18h]
  int mn; // [rsp+8h] [rbp-14h]

  mn = *arr;
  freq = 1;
  for ( i = 1; i < n; ++i )
  {
    if ( arr[i] >= mn )
    {
      if ( arr[i] == mn )
        ++freq;
    }
    else
    {
      mn = arr[i];
      freq = 1;
    }
  }
  return freq;
}