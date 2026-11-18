void __cdecl split(int sx1, int sy1, int sx2, int sy2, int *uy1, int *uy2, int *ly1, int *ly2, int num_pixels)
{
  int w; // [rsp+4h] [rbp-24h]

  w = sx2 - sx1 + 1;
  if ( w > 0 )
  {
    *uy1 = sy1;
    *uy2 = num_pixels / w + sy1 - 1;
    *ly1 = num_pixels / w + sy1;
    *ly2 = sy2;
  }
}