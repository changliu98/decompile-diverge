void __cdecl poly1305_squeeze(unsigned __int8 *h, unsigned __int64 *hr)
{
  unsigned int i; // [rsp+0h] [rbp-1Ch]
  unsigned int ia; // [rsp+0h] [rbp-1Ch]
  unsigned __int64 u; // [rsp+4h] [rbp-18h]
  unsigned __int64 ub; // [rsp+4h] [rbp-18h]
  unsigned __int64 uc; // [rsp+4h] [rbp-18h]
  unsigned __int64 ua; // [rsp+4h] [rbp-18h]
  unsigned __int64 ud; // [rsp+4h] [rbp-18h]

  u = 0LL;
  for ( i = 0; i < 0x10; ++i )
  {
    ub = u + hr[i];
    h[i] = ub;
    u = ub >> 8;
  }
  uc = u + hr[16];
  h[16] = uc & 3;
  ua = 5 * (uc >> 2);
  for ( ia = 0; ia < 0x10; ++ia )
  {
    ud = ua + h[ia];
    h[ia] = ud;
    ua = ud >> 8;
  }
  h[16] += ua;
}