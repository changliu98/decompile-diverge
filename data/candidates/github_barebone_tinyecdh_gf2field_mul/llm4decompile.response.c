void gf2field_mul(uint32_t *z, const uint32_t *x, const uint32_t *y)
{
  int i;
  gf2elem_t tmp;

  do { if (!(z != y)) __assert_fail("z != y", "func.c", 450, "void gf2field_mul(uint32_t *, const uint32_t *, const uint32_t *)"); } while (0);

  bitvec_copy(tmp, x);
  if (bitvec_get_bit(y, 0))
    bitvec_copy(z, x);
  else
    bitvec_set_zero(z);

  for (i = 1; i < 163; i++) {
    bitvec_lshift(tmp, tmp, 1);
    if (bitvec_get_bit(tmp, 163))
      gf2field_add(tmp, tmp, polynomial);
    if (bitvec_get_bit(y, i))
      gf2field_add(z, z, tmp);
  }
}