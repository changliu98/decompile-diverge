float v_inner(float *v1, float *v2, int n) {
  int i;
  float sum;
  i = 0;
  sum = 0.0;
  while (i < n) {
    sum += v1[i] * v2[i];
    i++;
  }
  return sum;
}