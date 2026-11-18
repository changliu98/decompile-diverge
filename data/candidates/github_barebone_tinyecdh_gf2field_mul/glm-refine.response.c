163 in decimal

void __cdecl gf2field_mul(uint32_t *z, const uint32_t *x, const uint32_t *y)
{
  gf2elem_t tmp;
  int i;

  // Assert that z and y do not alias the same memory space
  if (z == y)
    _assert_fail("z != y", "func.c", 0x1C2u, "void gf2field_mul(uint32_t *, const uint32_t *, const uint32_t *)");

  // Initialize tmp with the value of x
  bitvec_copy(tmp, x);

  // z = x if the least significant bit of y is 1, else z = 0
  if (bitvec_get_bit(y, 0))
    bitvec_copy(z, x);
  else
    bitvec_set_zero(z);

  // Standard binary field multiplication (shift-and-add)
  for (i = 1; i < FIELD_BITS; ++i)
  {
    // Shift tmp left by 1
    bitvec_lshift(tmp, tmp, 1);

    // Modular reduction: if the shifted value exceeds the field size (163 bits),
    // XOR it with the irreducible polynomial
    if (bitvec_get_bit(tmp, FIELD_MSB_INDEX))
      gf2field_add(tmp, tmp, &polynomial);

    // If the i-th bit of y is set, add (XOR) tmp to the result z
    if (bitvec_get_bit(y, i))
      gf2field_add(z, z, tmp);
  }
}