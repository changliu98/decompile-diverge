void bmp_iter_next(int *bi,int *bit_no)

{
  int *bit_no_local;
  int *bi_local;
  
  *bi = *bi >> 1;
  *bit_no = *bit_no + 1;
  return;
}