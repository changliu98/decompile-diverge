void RGBtoHSV(float r,float g,float b,float *h,float *s,float *v)

{
  float local_5c;
  float local_58;
  float local_54;
  float local_4c;
  float local_48;
  float local_44;
  float delta;
  float max;
  float min;
  float *v_local;
  float *s_local;
  float *h_local;
  float b_local;
  float g_local;
  float r_local;
  
  local_44 = b;
  if (g < b) {
    local_44 = g;
  }
  local_48 = r;
  if (local_44 <= r) {
    local_4c = b;
    if (g < b) {
      local_4c = g;
    }
    local_48 = local_4c;
  }
  local_54 = b;
  if (b < g) {
    local_54 = g;
  }
  local_58 = r;
  if (r <= local_54) {
    local_5c = b;
    if (b < g) {
      local_5c = g;
    }
    local_58 = local_5c;
  }
  *v = local_58;
  local_48 = local_58 - local_48;
  if ((local_58 != 0.0) || (NAN(local_58))) {
    *s = local_48 / local_58;
    if ((r != local_58) || (NAN(r) || NAN(local_58))) {
      if ((g != local_58) || (NAN(g) || NAN(local_58))) {
        *h = DAT_00102008 + (r - g) / local_48;
      }
      else {
        *h = DAT_0010200c + (b - r) / local_48;
      }
    }
    else {
      *h = (g - b) / local_48;
    }
    *h = DAT_00102010 * *h;
    if (*h <= 0.0 && *h != 0.0) {
      *h = DAT_00102014 + *h;
    }
  }
  else {
    *s = 0.0;
    *h = DAT_00102004;
  }
  return;
}