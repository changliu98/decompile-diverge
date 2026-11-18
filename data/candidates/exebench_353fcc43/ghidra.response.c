void copy_poly(int *dst,int *src)

{
  int i;
  int *src_local;
  int *dst_local;
  
  for (i = 0; i < 0x14; i = i + 1) {
    dst[i] = src[i];
  }
  return;
}