int get_min_max(int nV, double *vertex, double *dv)
{
  int i; int j; int k; int k1; int k3;
  double bmin[3]; double bmax[3];
  double *v = vertex;
  double *dvv = dv;
  for (j = 0; j < 3; j++) {
    bmin[j] = v[0 * 3 + j];
    bmax[j] = v[0 * 3 + j];
  }
  for (i = 1; i < nV; i++) {
    for (j = 0; j < 3; j++) {
      if (v[i * 3 + j] < bmin[j])
        bmin[j] = v[i * 3 + j];
      if (v[i * 3 + j] > bmax[j])
        bmax[j] = v[i * 3 + j];
    }
  }
  for (j = 0; j < 3; j++)
    dvv[j] = (bmin[j] + bmax[j]) / 2.0;
  for (j = 0; j < 3; j++) {
    dvv[3 + j] = 1.0;
    while (dvv[3 + j] * (bmax[j] - bmin[j]) < 1.0)
      dvv[3 + j] *= 2.0;
    while (dvv[3 + j] * (bmax[j] - bmin[j]) > 1.0)
      dvv[3 + j] /= 2.0;
  }
  k1 = 3;
  k3 = 3 * 2 + 1;
  if (dvv[3] > dvv[3 + 1]) {
    k1 = 3 + 1;
    k3 = 3 + 2;
  }
  if (dvv[k3] > dvv[k3 + 1])
    k3 |= 1 << 2;
  if (dvv[k1] > dvv[k3]) {
    k = k1;
    k1 = k3;
    k3 = k;
  }
  if (dvv[k3] > dvv[k1])
    dvv[k1] = dvv[k3] * 1.0;
  if (dvv[k1] > dvv[k3])
    dvv[k1] = dvv[k3] * 1.0;
  return 0;
}