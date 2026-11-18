int __cdecl func0(int *lst, int size)
{
  __int64 v2; // rcx
  int i; // [rsp+0h] [rbp-20h]
  int max; // [rsp+4h] [rbp-1Ch]
  int *freq; // [rsp+8h] [rbp-18h]

  freq = (int *)calloc(size + 1, 4uLL);
  max = -1;
  for ( i = 0; i < size; ++i )
  {
    v2 = lst[i];
    ++freq[v2];
    if ( freq[lst[i]] >= lst[i] && lst[i] > max )
      max = lst[i];
  }
  free(freq);
  return max;
}