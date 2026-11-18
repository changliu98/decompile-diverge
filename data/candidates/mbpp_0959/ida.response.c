double __cdecl func0(int *lst, int len)
{
  int i; // [rsp+0h] [rbp-14h]
  int sum; // [rsp+4h] [rbp-10h]

  sum = 0;
  for ( i = 0; i < len; ++i )
    sum += lst[i];
  return (double)sum / (double)len;
}