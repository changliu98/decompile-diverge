static int
bkm_scale (long int *x, int scale_factor)
{
  long int product = *x * scale_factor;
  if (*x != product / scale_factor)
    return 1;
  *x = product;
  return 0;
}