void rgb_2_hls(int r,int g,int b,int *h,int *l,int *s)

{
  int local_44;
  int local_40;
  int t;
  int max;
  int min;
  int *s_local;
  int *l_local;
  int *h_local;
  int b_local;
  int g_local;
  int r_local;
  
  local_40 = r;
  if (g < r) {
    local_40 = g;
  }
  min = local_40;
  if (b < local_40) {
    min = b;
  }
  local_44 = r;
  if (r < g) {
    local_44 = g;
  }
  max = local_44;
  if (local_44 < b) {
    max = b;
  }
  *l = (min + max) / 0x14;
  if (min == max) {
    *h = 0;
    *s = 0;
  }
  else {
    if (*l < 0x32) {
      *s = ((max - min) * 100) / (max + min);
    }
    else {
      *s = ((max - min) * 100) / ((2000 - max) - min);
    }
    if (r == max) {
      t = ((g - b) * 0x3c) / (max - min) + 0x78;
    }
    else if (g == max) {
      t = ((b - r) * 0x3c) / (max - min) + 0xf0;
    }
    else {
      t = ((r - g) * 0x3c) / (max - min) + 0x168;
    }
    *h = t % 0x168;
  }
  return;
}