int __cdecl bkm_scale(long *x, int scale_factor)
{
  long product = (long)scale_factor * *x;

  // Standard integer overflow check:
  // If the multiplication overflowed, dividing the product by the scale_factor
  // will not yield the original value (*x).
  if (*x != product / scale_factor)
    return 1; // Overflow detected

  *x = product;
  return 0; // Success
}