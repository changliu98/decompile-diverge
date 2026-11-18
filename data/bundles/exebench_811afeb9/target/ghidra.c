int bbox(int nV,double *vertex,double *dv)

{
  int iVar1;
  int iVar2;
  int k;
  int k3;
  int k2;
  int k1;
  int j;
  int i;
  int t;
  double bmax [3];
  double bmin [3];
  double *dv_local;
  double *vertex_local;
  int nV_local;
  
  for (j = 0; j < 3; j = j + 1) {
    bmin[j] = vertex[j];
    bmax[j] = vertex[j];
  }
  for (i = 1; i < nV; i = i + 1) {
    for (j = 0; j < 3; j = j + 1) {
      if (vertex[i * 3 + j] <= bmin[j] && bmin[j] != vertex[i * 3 + j]) {
        bmin[j] = vertex[i * 3 + j];
      }
      if (bmax[j] < vertex[i * 3 + j]) {
        bmax[j] = vertex[i * 3 + j];
      }
    }
  }
  for (t = 0; t < 3; t = t + 1) {
    dv[t] = (bmin[t] + bmax[t]) / DAT_00102018;
  }
  for (t = 0; t < 3; t = t + 1) {
    dv[t + 3] = DAT_00102010;
    while (dv[t + 3] * (bmax[t] - bmin[t]) < DAT_00102010) {
      dv[t + 3] = DAT_00102018 * dv[t + 3];
    }
    while (DAT_00102010 < dv[t + 3] * (bmax[t] - bmin[t])) {
      dv[t + 3] = dv[t + 3] / DAT_00102018;
    }
  }
  k1 = 3;
  k2 = 4;
  k3 = 5;
  if (dv[4] <= dv[3] && dv[3] != dv[4]) {
    k1 = 4;
    k2 = 3;
  }
  iVar2 = k1;
  iVar1 = k2;
  if (dv[5] <= dv[k2] && dv[k2] != dv[5]) {
    k2 = 5;
    k3 = iVar1;
  }
  if (dv[k2] <= dv[k1] && dv[k1] != dv[k2]) {
    k1 = k2;
    k2 = iVar2;
  }
  if (dv[k1] < dv[k2]) {
    dv[k1] = dv[k2] / DAT_00102010;
  }
  if (dv[k2] <= dv[k3] && dv[k3] != dv[k2]) {
    dv[k3] = DAT_00102010 * dv[k2];
  }
  return 0;
}