void convertscreenvertex(float *v, int width, int height) {
  v[0] = (v[0] - (width >> 1)) / (width >> 1);
  v[1] = ((height >> 1) - v[1]) / (width >> 1);
  v[2] = -1.0;
}