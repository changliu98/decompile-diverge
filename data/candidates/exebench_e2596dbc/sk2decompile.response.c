void load_xps(float *xps, const float *x) {
  xps[0] = x[0];
  xps[4] = x[1];
  xps[8] = x[2];
  xps[12] = x[3];
  xps[1] = x[4];
  xps[5] = x[5];
  xps[9] = x[6];
  xps[13] = x[7];
  xps[2] = x[8];
  xps[6] = x[9];
  xps[10] = x[10];
  xps[14] = x[11];
  xps[3] = x[12];
  xps[7] = x[13];
  xps[11] = x[14];
  xps[15] = x[15];
}