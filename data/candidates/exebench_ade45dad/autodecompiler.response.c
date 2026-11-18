void zywrle_calc_size(unsigned long *x, unsigned long *y, int size)
{
   *x = *x & (~((1 << size) - 1));
   *y = *y & ((1 << size) - 1);
}