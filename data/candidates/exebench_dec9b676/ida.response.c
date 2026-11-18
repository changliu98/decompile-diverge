void __cdecl mult121665(unsigned int *out, const unsigned int *a)
{
  unsigned int u; // [rsp+0h] [rbp-18h]
  unsigned int ub; // [rsp+0h] [rbp-18h]
  unsigned int uc; // [rsp+0h] [rbp-18h]
  unsigned int ua; // [rsp+0h] [rbp-18h]
  unsigned int ud; // [rsp+0h] [rbp-18h]
  unsigned int j; // [rsp+4h] [rbp-14h]
  unsigned int ja; // [rsp+4h] [rbp-14h]

  u = 0;
  for ( j = 0; j < 0x1F; ++j )
  {
    ub = u + 121665 * a[j];
    out[j] = (unsigned __int8)ub;
    u = ub >> 8;
  }
  uc = u + 121665 * a[31];
  out[31] = uc & 0x7F;
  ua = 19 * (uc >> 7);
  for ( ja = 0; ja < 0x1F; ++ja )
  {
    ud = ua + out[ja];
    out[ja] = (unsigned __int8)ud;
    ua = ud >> 8;
  }
  out[ja] += ua;
}