void func0(float *xs,int xs_size,float *out)

{
  int i;
  float *out_local;
  int xs_size_local;
  float *xs_local;
  
  for (i = 1; i < xs_size; i = i + 1) {
    out[i + -1] = (float)i * xs[i];
  }
  return;
}