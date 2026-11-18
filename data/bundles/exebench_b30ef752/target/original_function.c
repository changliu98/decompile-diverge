void limit2_u16(unsigned short* x, unsigned short lower, unsigned short upper) {
  if (*x >= upper)
    *x = upper;
  else if (*x <= lower)
    *x = lower;
}