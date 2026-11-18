float nabs_sf(float *x) {
  float y;
  int i;
  i = *(int *)x;
  i = i & 0x7fffffff;
  i = i ^ 0x80000000;
  y = *(float *)&i;
  return y;
}