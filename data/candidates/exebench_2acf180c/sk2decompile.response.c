void unpackFloat(float f, int *exponent, int *mantissa) {
  unsigned int u = *(unsigned int *)&f;
  *exponent = (int)((u & 0x7F800000) >> 23) - 127;
  *mantissa = (int)(u & 0x007FFFFF) + 0x00800000;
  if (f < 0) *mantissa = -*mantissa;
}