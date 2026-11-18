void xformSetTranslation(float *xform, float x, float y) {
  xform[0] = 1.0;
  xform[1] = 0.0;
  xform[2] = 0.0;
  xform[3] = 1.0;
  xform[4] = x;
  xform[5] = y;
}