void rgb2hsv(int r,int g,int b,int *h,int *s,int *v)

{
  int local_40;
  int local_3c;
  int min;
  int max;
  int *v_local;
  int *s_local;
  int *h_local;
  int b_local;
  int g_local;
  int r_local;
  
  local_3c = g;
  if (g < r) {
    local_3c = r;
  }
  max = local_3c;
  if (local_3c < b) {
    max = b;
  }
  local_40 = g;
  if (r < g) {
    local_40 = r;
  }
  min = local_40;
  if (b < local_40) {
    min = b;
  }
  if (max == 0) {
    *v = 0;
    *h = 0;
    *s = 0;
  }
  else {
    if (max == min) {
      *h = 0;
    }
    else if ((max == r) && (b <= g)) {
      *h = ((g - b) * 600) / (max - min);
    }
    else if ((max == r) && (g < b)) {
      *h = (((g - b) * 0x3c) / (max - min) + 0x168) * 10;
    }
    else if (max == g) {
      *h = (((b - r) * 0x3c) / (max - min) + 0x78) * 10;
    }
    else {
      *h = (((r - g) * 0x3c) / (max - min) + 0xf0) * 10;
    }
    while (*h < 0) {
      *h = *h + 0xe10;
    }
    while (0xe0f < *h) {
      *h = *h + -0xe10;
    }
    *s = ((max - min) * 0xff) / max;
    *v = max;
  }
  return;
}