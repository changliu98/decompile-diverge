void norm(int *hi,int *lo,int base)

{
  int iVar1;
  int n;
  int base_local;
  int *lo_local;
  int *hi_local;
  
  if (*lo < 0) {
    iVar1 = (-1 - *lo) / base + 1;
    *hi = *hi - iVar1;
    *lo = iVar1 * base + *lo;
  }
  if (base <= *lo) {
    iVar1 = *lo;
    *hi = iVar1 / base + *hi;
    *lo = *lo - (iVar1 / base) * base;
  }
  return;
}