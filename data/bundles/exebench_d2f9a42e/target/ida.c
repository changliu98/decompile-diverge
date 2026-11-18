void __cdecl sub(unsigned int *out, const unsigned int *a, const unsigned int *b)
{
  unsigned int u; // [rsp+0h] [rbp-20h]
  unsigned int ua; // [rsp+0h] [rbp-20h]
  unsigned int j; // [rsp+4h] [rbp-1Ch]

  u = 218;
  for ( j = 0; j < 0x1F; ++j )
  {
    ua = u + a[j] + 65280 - b[j];
    out[j] = (unsigned __int8)ua;
    u = ua >> 8;
  }
  out[31] = u + a[31] - b[31];
}