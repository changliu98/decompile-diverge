int bkm_scale(long *val, int scale_factor)
{
  long newval = *val * scale_factor;
  if (newval / scale_factor == *val) {
    *val = newval;
    return 0;
  }
  return 1;
}