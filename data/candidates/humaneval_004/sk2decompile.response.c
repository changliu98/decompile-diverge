float _std(float *data, int n) {
  int i;
  float sum = 0;
  for (i = 0; i < n; i++) {
    sum += data[i];
  }
  float mean = sum / n;
  float std = 0;
  for (i = 0; i < n; i++) {
    std += fabs(data[i] - mean);
  }
  return std / n;
}