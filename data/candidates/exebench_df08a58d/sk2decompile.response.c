float abs_sf(float *x) {
  float y;
  int i;
  i = *(int *)x;
  i &= 0x7fffffff;
  y = *(float *)&i;
  return y;
}