float getUniform(int a, int b, int c, float *seed) {
  float temp;
  temp = (float)(a * (*seed) + b);
  temp = temp / c;
  temp = (int)temp;
  temp = temp * c;
  *seed = (a * (*seed) + b - temp) / c;
  return *seed;
}