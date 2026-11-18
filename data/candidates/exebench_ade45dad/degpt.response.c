void zywrle_calc_size(int *w,int *h,int level)

{
  int level_local;
  int *h_local;
  int *w_local;
  
  *w = ((1 << ((byte)level & 0x1f)) - 1U ^ 0xffffffff) & *w;
  *h = ((1 << ((byte)level & 0x1f)) - 1U ^ 0xffffffff) & *h;
  return;
}