int *__cdecl func0(int *numbers, int size)
{
  int i; // [rsp+8h] [rbp-28h]
  int max; // [rsp+Ch] [rbp-24h]
  int *out; // [rsp+10h] [rbp-20h]

  if ( size <= 0 )
    return 0LL;
  out = (int *)malloc(4LL * size);
  if ( !out )
    return 0LL;
  max = *numbers;
  for ( i = 0; i < size; ++i )
  {
    if ( numbers[i] > max )
      max = numbers[i];
    out[i] = max;
  }
  return out;
}