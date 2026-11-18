void rgb2hsv(double r,double g,double b,double *h,double *s,double *v)

{
  double dVar1;
  double dVar2;
  double dVar3;
  double local_b0;
  double local_a8;
  double local_a0;
  double local_90;
  double local_88;
  double local_80;
  double st;
  double ht;
  double gc;
  double bc;
  double rc;
  double rgbmax;
  double rgbmin;
  double *v_local;
  double *s_local;
  double *h_local;
  double b_local;
  double g_local;
  double r_local;
  
  ht = 0.0;
  st = 0.0;
  local_80 = b;
  if (g < b) {
    local_80 = g;
  }
  local_88 = r;
  if (local_80 <= r) {
    local_90 = b;
    if (g < b) {
      local_90 = g;
    }
    local_88 = local_90;
  }
  local_a0 = b;
  if (b < g) {
    local_a0 = g;
  }
  local_a8 = r;
  if (r <= local_a0) {
    local_b0 = b;
    if (b < g) {
      local_b0 = g;
    }
    local_a8 = local_b0;
  }
  if (0.0 < local_a8) {
    st = (local_a8 - local_88) / local_a8;
  }
  if (0.0 < st) {
    dVar1 = (local_a8 - r) / (local_a8 - local_88);
    dVar2 = (local_a8 - g) / (local_a8 - local_88);
    dVar3 = (local_a8 - b) / (local_a8 - local_88);
    if ((r != local_a8) || (NAN(r) || NAN(local_a8))) {
      if ((g != local_a8) || (NAN(g) || NAN(local_a8))) {
        if ((b == local_a8) && (!NAN(b) && !NAN(local_a8))) {
          ht = (DAT_00102010 + dVar2) - dVar1;
        }
      }
      else {
        ht = (DAT_00102018 + dVar1) - dVar3;
      }
    }
    else {
      ht = dVar3 - dVar2;
    }
    ht = DAT_00102020 * ht;
    if (ht < 0.0) {
      ht = DAT_00102028 + ht;
    }
  }
  *h = ht / DAT_00102028;
  *v = local_a8;
  *s = st;
  return;
}