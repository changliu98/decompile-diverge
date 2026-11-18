static inline void
bmp_iter_next (int *bi, int *bit_no)
{
  *bi >>= 1;
  *bit_no += 1;
}