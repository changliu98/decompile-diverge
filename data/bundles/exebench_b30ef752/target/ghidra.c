void limit2_u16(unsigned_short *x,unsigned_short lower,unsigned_short upper)

{
  unsigned_short upper_local;
  unsigned_short lower_local;
  unsigned_short *x_local;
  
  if (*x < upper) {
    if (*x <= lower) {
      *x = lower;
    }
  }
  else {
    *x = upper;
  }
  return;
}