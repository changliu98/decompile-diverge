void bmp_iter_next(int *val, int *bit_no)
{
  *val = *val>>1;
  *bit_no = *bit_no + 1;
}