/* WARNING: Restarted to delay deadcode elimination for space: stack */

void gui_combine_scissor(int *dst,int *src)

{
  int local_50;
  int local_4c;
  int local_48;
  int local_44;
  int c_1;
  int c;
  int sp [4];
  int dp [4];
  int *src_local;
  int *dst_local;
  
  if (src != (int *)0x0) {
    local_44 = *src;
    local_48 = src[1];
    local_4c = *src + src[2];
    local_50 = src[1] + src[3];
    if (local_44 < *dst) {
      local_44 = *dst;
    }
    if (local_48 < dst[1]) {
      local_48 = dst[1];
    }
    if (*dst + dst[2] < local_4c) {
      local_4c = *dst + dst[2];
    }
    if (dst[1] + dst[3] < local_50) {
      local_50 = dst[1] + dst[3];
    }
    *dst = local_44;
    dst[1] = local_48;
    dst[2] = local_4c - local_44;
    dst[3] = local_50 - local_48;
  }
  return;
}