void _normalize(float *data, int n) {
  int i;
  float min = data[0];
  float max = data[0];
  for (i = 1; i < n; i++) {
    if (data[i] < min) min = data[i];
    if (data[i] > max) max = data[i];
  }
  for (i = 0; i < n; i++) {
    data[i] = (data[i] - min) / (max - min);
  }
}