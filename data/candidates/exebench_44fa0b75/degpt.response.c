void calculate_proportions(int src_w,int src_h,int *pdst_w,int *pdst_h)

{
  int local_30;
  int local_2c;
  int dst_h;
  int dst_w;
  int *pdst_h_local;
  int *pdst_w_local;
  int src_h_local;
  int src_w_local;
  
  if (pdst_w == (int *)0x0) {
    local_2c = 0;
  }
  else {
    local_2c = *pdst_w;
  }
  dst_w = local_2c;
  if (pdst_h == (int *)0x0) {
    local_30 = 0;
  }
  else {
    local_30 = *pdst_h;
  }
  dst_h = local_30;
  if (((src_w < 1) || (src_w < src_h)) || ((local_2c < 1 && (0 < local_30)))) {
    if (0 < src_h) {
      dst_w = (src_w * local_30) / src_h;
    }
  }
  else {
    dst_h = (src_h * local_2c) / src_w;
  }
  if (pdst_w != (int *)0x0) {
    *pdst_w = dst_w;
  }
  if (pdst_h != (int *)0x0) {
    *pdst_h = dst_h;
  }
  return;
}