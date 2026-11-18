void __cdecl squeeze(unsigned int *a)
{
  unsigned int u; // [rsp+0h] [rbp-10h]
  unsigned int ub; // [rsp+0h] [rbp-10h]
  unsigned int uc; // [rsp+0h] [rbp-10h]
  unsigned int ua; // [rsp+0h] [rbp-10h]
  unsigned int ud; // [rsp+0h] [rbp-10h]
  unsigned int j; // [rsp+4h] [rbp-Ch]
  unsigned int ja; // [rsp+4h] [rbp-Ch]

  u = 0;
  for ( j = 0; j < 0x1F; ++j )
  {
    ub = u + a[j];
    a[j] = (unsigned __int8)ub;
    u = ub >> 8;
  }
  uc = u + a[31];
  a[31] = uc & 0x7F;
  ua = 19 * (uc >> 7);
  for ( ja = 0; ja < 0x1F; ++ja )
  {
    ud = ua + a[ja];
    a[ja] = (unsigned __int8)ud;
    ua = ud >> 8;
  }
  a[31] += ua;
}