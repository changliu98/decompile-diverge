int bbox(int n, double *x, double *bb) {
  int i, j, nn, i1, i2;
  double min[3], max[3];
  nn = n;
  double *xx = x;
  double *bbb = bb;
  for (j = 0; j < 3; j++) {
    min[j] = xx[j];
    max[j] = xx[j];
  }
  for (i = 1; i < nn; i++) {
    for (j = 0; j < 3; j++) {
      if (xx[i * 3 + j] < min[j]) min[j] = xx[i * 3 + j];
      if (xx[i * 3 + j] > max[j]) max[j] = xx[i * 3 + j];
    }
  }
  for (j = 0; j < 3; j++) bbb[j] = (min[j] + max[j]) / 2;
  for (j = 0; j < 3; j++) {
    bbb[j + 3] = 1.0;
    while (bbb[j + 3] * (max[j] - min[j]) < 1.0) bbb[j + 3] *= 2.0;
    while (bbb[j + 3] * (max[j] - min[j]) > 1.0) bbb[j + 3] /= 2.0;
  }
  i1 = 3;
  i2 = 4;
  if (bbb[i1] > bbb[i2]) {
    i2 = i1;
    i1 = 4;
  }
  if (bbb[i2] > bbb[5]) {
    i2 = 5;
    i1 = 4;
  }
  if (bbb[i1] > bbb[i2]) {
    i = i1;
    i1 = i2;
    i2 = i;
  }
  if (bbb[i2] > bbb[i1]) bbb[i1] = bbb[i2] / 1.0;
  if (bbb[i2] < bbb[i1]) bbb[i2] = 1.0 * bbb[i1];
  return 0;
}