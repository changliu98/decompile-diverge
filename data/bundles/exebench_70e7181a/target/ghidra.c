void split(int sx1,int sy1,int sx2,int sy2,int *uy1,int *uy2,int *ly1,int *ly2,int num_pixels)

{
  int iVar1;
  int cut_h;
  int w;
  int *uy2_local;
  int *uy1_local;
  int sy2_local;
  int sx2_local;
  int sy1_local;
  int sx1_local;
  
  iVar1 = (sx2 - sx1) + 1;
  if (0 < iVar1) {
    iVar1 = num_pixels / iVar1;
    *uy1 = sy1;
    *uy2 = sy1 + iVar1 + -1;
    *ly1 = sy1 + iVar1;
    *ly2 = sy2;
  }
  return;
}