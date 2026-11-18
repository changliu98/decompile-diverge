int func0(float a, float b, float c) {
  int ret = 1;
  if (fabs(a * a + b * b - c * c) < 0.0001) {
    ret = 0;
  } else if (fabs(a * a + c * c - b * b) < 0.0001) {
    ret = 0;
  } else if (fabs(b * b + c * c - a * a) < 0.0001) {
    ret = 0;
  }
  return ret;
}