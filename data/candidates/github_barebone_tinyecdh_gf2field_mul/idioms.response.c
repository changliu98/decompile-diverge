void gf2field_mul(uint32_t *z, uint32_t *x, uint32_t *y)
{
  int i;
  uint32_t tmp;
  uint32_t *za = z;
  uint32_t *xa = x;
  uint32_t *ya = y;
  ((void) sizeof ((z != y) ? 1 : 0), __extension__ ({ if (z != y) ; else __assert_fail ("z != y", "func.c", 450, __extension__ __PRETTY_FUNCTION__); }));
  gf2elem_copy(tmp, xa);
  if (gf2elem_iszero(ya, 0))
    gf2elem_copy(za, xa);
  else
    gf2elem_setzero(za);
  for (i = 1; i < (163); i++) {
    gf2elem_shiftl(tmp, tmp, 1);
    if (gf2elem_isone(tmp, 163 - 1 - 1))
      gf2elem_mul(tmp, tmp, polynomial);
    if (gf2elem_isone(ya, i))
      gf2elem_mul(za, za, tmp);
  }
}