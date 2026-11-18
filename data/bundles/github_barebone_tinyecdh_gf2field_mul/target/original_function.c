static void gf2field_mul(gf2elem_t z, const gf2elem_t x, const gf2elem_t y)
{
  int i;
  gf2elem_t tmp;
#if defined(CONST_TIME) && (CONST_TIME == 1)
  gf2elem_t blind;
  bitvec_set_zero(blind);
#endif
  assert(z != y);

  bitvec_copy(tmp, x);

  /* LSB set? Then start with x */
  if (bitvec_get_bit(y, 0) != 0)
  {
    bitvec_copy(z, x);
  }
  else /* .. or else start with zero */
  {
    bitvec_set_zero(z);
  }

  /* Then add 2^i * x for the rest */
  for (i = 1; i < CURVE_DEGREE; ++i)
  {
    /* lshift 1 - doubling the value of tmp */
    bitvec_lshift(tmp, tmp, 1);

    /* Modulo reduction polynomial if degree(tmp) > CURVE_DEGREE */
    if (bitvec_get_bit(tmp, CURVE_DEGREE))
    {
      gf2field_add(tmp, tmp, polynomial);
    }
#if defined(CONST_TIME) && (CONST_TIME == 1)
    else /* blinding operation */
    {
      gf2field_add(tmp, tmp, blind);
    }
#endif

    /* Add 2^i * tmp if this factor in y is non-zero */
    if (bitvec_get_bit(y, i))
    {
      gf2field_add(z, z, tmp);
    }
#if defined(CONST_TIME) && (CONST_TIME == 1)
    else /* blinding operation */
    {
      gf2field_add(z, z, blind);
    }
#endif
  }
}