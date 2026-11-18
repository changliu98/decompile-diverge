int *__cdecl func0(const int *numbers, int size, int delimiter, int *out_size)
{
  int v4; // ecx
  int v6; // [rsp+4h] [rbp-2Ch]
  int j; // [rsp+8h] [rbp-28h]
  int i; // [rsp+Ch] [rbp-24h]
  int *out; // [rsp+10h] [rbp-20h]

  if ( size <= 0 )
    v6 = 0;
  else
    v6 = 2 * size - 1;
  *out_size = v6;
  out = (int *)malloc(4LL * *out_size);
  if ( size > 0 )
    *out = *numbers;
  i = 1;
  j = 1;
  while ( i < size )
  {
    out[j] = delimiter;
    v4 = j + 1;
    j += 2;
    out[v4] = numbers[i++];
  }
  return out;
}