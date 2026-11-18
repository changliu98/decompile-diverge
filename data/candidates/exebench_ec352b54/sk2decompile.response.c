void swap(float *a, float *b) {
  float temp;
  if (*a > *b) {
    temp = *b;
    *b = *a;
    *a = temp;
  }
}