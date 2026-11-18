void __cdecl calculate_proportions(int src_w, int src_h, int *pdst_w, int *pdst_h)
{
  int v4; // [rsp+0h] [rbp-28h]
  int v5; // [rsp+4h] [rbp-24h]
  int dst_h; // [rsp+8h] [rbp-20h]
  int dst_w; // [rsp+Ch] [rbp-1Ch]

  if ( pdst_w )
    v5 = *pdst_w;
  else
    v5 = 0;
  dst_w = v5;
  if ( pdst_h )
    v4 = *pdst_h;
  else
    v4 = 0;
  dst_h = v4;
  if ( src_w <= 0 || src_w < src_h || v5 <= 0 && v4 > 0 )
  {
    if ( src_h > 0 )
      dst_w = v4 * src_w / src_h;
  }
  else
  {
    dst_h = v5 * src_h / src_w;
  }
  if ( pdst_w )
    *pdst_w = dst_w;
  if ( pdst_h )
    *pdst_h = dst_h;
}