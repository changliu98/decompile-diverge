float interp_tri(float *z,float x,float y,int grid_scheme)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  double dVar5;
  double local_90;
  double local_88;
  double local_80;
  double local_78;
  double zc;
  double zb;
  double za;
  double z3;
  double z2;
  double z1;
  double z0;
  double yy;
  double xx;
  int grid_scheme_local;
  float y_local;
  float x_local;
  float *z_local;
  
  if (DAT_00102008 <= (double)x) {
    if ((double)x <= DAT_00102010) {
      local_80 = (double)x;
    }
    else {
      local_80 = DAT_00102018;
    }
    local_78 = local_80;
  }
  else {
    local_78 = 0.0;
  }
  xx = local_78;
  if (DAT_00102008 <= (double)y) {
    if ((double)y <= DAT_00102010) {
      local_90 = (double)y;
    }
    else {
      local_90 = DAT_00102018;
    }
    local_88 = local_90;
  }
  else {
    local_88 = 0.0;
  }
  yy = local_88;
  if ((local_78 != 0.0) || (NAN(local_78))) {
    if ((local_78 == DAT_00102018) && (!NAN(local_78) && !NAN(DAT_00102018))) {
      if ((local_88 == 0.0) && (!NAN(local_88))) {
        return z[1];
      }
      if ((local_88 == DAT_00102018) && (!NAN(local_88) && !NAN(DAT_00102018))) {
        return z[3];
      }
    }
  }
  else {
    if ((local_88 == 0.0) && (!NAN(local_88))) {
      return *z;
    }
    if ((local_88 == DAT_00102018) && (!NAN(local_88) && !NAN(DAT_00102018))) {
      return z[2];
    }
  }
  if (grid_scheme < 1) {
    xx = DAT_00102018 - local_78;
    fVar1 = z[1];
    fVar2 = *z;
    fVar3 = z[2];
    fVar4 = z[3];
  }
  else {
    fVar1 = *z;
    fVar2 = z[1];
    fVar3 = z[3];
    fVar4 = z[2];
  }
  z0 = (double)fVar1;
  z1 = (double)fVar2;
  z2 = (double)fVar3;
  z3 = (double)fVar4;
  if (xx < local_88) {
    za = z2;
    zb = z3;
    zc = z0;
    xx = DAT_00102018 - xx;
    yy = DAT_00102018 - local_88;
  }
  else {
    za = z0;
    zb = z1;
    zc = z2;
  }
  dVar5 = (zb - za) * xx + za;
  return (float)((((zc - za) * xx + za) - dVar5) * (yy / xx) + dVar5);
}