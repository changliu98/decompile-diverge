void mtxTranspose(float *out, const float *m) {
  out[0] = m[0];
  out[5] = m[5];
  out[10] = m[10];
  out[15] = m[15];
  out[1] = m[4];
  out[4] = m[1];
  out[2] = m[8];
  out[8] = m[2];
  out[3] = m[12];
  out[12] = m[3];
  out[6] = m[9];
  out[9] = m[6];
  out[7] = m[13];
  out[13] = m[7];
  out[11] = m[14];
  out[14] = m[11];
}