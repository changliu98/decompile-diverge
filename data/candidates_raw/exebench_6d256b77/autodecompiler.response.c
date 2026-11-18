float jaccard_distance(float *vec, int i, int j, int n) {
  float n_12, n_01, n_10, n_00;
  float dist;
  n_12 = n_01 = n_10 = n_00 = 0;
  for (int k = 0; k < n; k++) {
    if (vec[i*n + k] == 1 && vec[j*n + k] == 1) {
      n_12++;
    }
    if (vec[i*n + k] == 1) {
      n_10++;
    }
    if (vec[j*n + k] == 1) {
      n_01++;
    }
  }
  if (n_01 > n_10) {
    dist = n_12 / n_01;
  } else {
    dist = n_12 / n_10;
  }
  return dist;
}