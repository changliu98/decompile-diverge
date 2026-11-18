float func0(float *data, int n) {
  float sum = 0;
  int i = 0;
  for (i = 0; ; i++) {
    if (i >= n)
      break;
    sum += data[i];
  }
  float avg = sum / n;
  float msum = 0;
  for (i = 0; ; i++) {
    if (i >= n)
      break;
    msum += fabsf(data[i] - avg);
  }
  return msum / n;
}