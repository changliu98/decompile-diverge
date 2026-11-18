void __cdecl poly1305_add(unsigned __int8 *h, const unsigned __int8 *c)
{
  unsigned int i; // [rsp+0h] [rbp-18h]
  unsigned __int16 u; // [rsp+6h] [rbp-12h]
  unsigned __int16 ua; // [rsp+6h] [rbp-12h]

  u = 0;
  for ( i = 0; i < 0x11; ++i )
  {
    ua = c[i] + h[i] + u;
    h[i] = ua;
    u = (int)ua >> 8;
  }
}