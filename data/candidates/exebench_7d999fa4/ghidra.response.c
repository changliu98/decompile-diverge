int bkm_scale(long *x,int scale_factor)

{
  bool bVar1;
  long product;
  int scale_factor_local;
  long *x_local;
  undefined4 local_c;
  
  bVar1 = *x == (*x * (long)scale_factor) / (long)scale_factor;
  if (bVar1) {
    *x = *x * (long)scale_factor;
  }
  local_c = (uint)!bVar1;
  return local_c;
}