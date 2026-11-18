int __cdecl bkm_scale(long *x, int scale_factor)
{
  long product; // [rsp+8h] [rbp-20h]

  product = scale_factor * *x;
  if ( *x != product / scale_factor )
    return 1;
  *x = product;
  return 0;
}