void limit2_i32(int *x,int lower,int upper)

{
  int upper_local;
  int lower_local;
  int *x_local;
  
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