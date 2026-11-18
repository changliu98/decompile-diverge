void copy_poly(poly_t *dst, poly_t *src)
{
  int i;
  for (i = 0; i < 20; i++)
    dst->coeffs[i] = src->coeffs[i];
}