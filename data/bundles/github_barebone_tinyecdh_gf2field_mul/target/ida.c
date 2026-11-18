void __cdecl gf2field_mul(uint32_t *z, const uint32_t *x, const uint32_t *y)
{
  gf2elem_t tmp; // [rsp+0h] [rbp-40h] BYREF
  int i; // [rsp+24h] [rbp-1Ch]
  const uint32_t *ya; // [rsp+28h] [rbp-18h]
  const uint32_t *xa; // [rsp+30h] [rbp-10h]
  uint32_t *za; // [rsp+38h] [rbp-8h]

  za = z;
  xa = x;
  ya = y;
  if ( z == y )
    _assert_fail("z != y", "func.c", 0x1C2u, "void gf2field_mul(uint32_t *, const uint32_t *, const uint32_t *)");
  bitvec_copy(tmp, xa);
  if ( bitvec_get_bit(ya, 0) )
    bitvec_copy(za, xa);
  else
    bitvec_set_zero(za);
  for ( i = 1; i < 163; ++i )
  {
    bitvec_lshift(tmp, tmp, 1);
    if ( bitvec_get_bit(tmp, 0xA3u) )
      gf2field_add(tmp, tmp, &polynomial);
    if ( bitvec_get_bit(ya, i) )
      gf2field_add(za, za, tmp);
  }
}