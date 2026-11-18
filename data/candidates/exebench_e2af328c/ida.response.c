void __cdecl bmp_iter_next(int *bi, int *bit_no)
{
  *bi >>= 1;
  ++*bit_no;
}