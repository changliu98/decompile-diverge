void matrixApply(float *m, float x, float y, float z,
                 float *outx, float *outy, float *outz) {
  *outx = x*m[0] + y*m[1] + z*m[2] + m[3];
  *outy = x*m[4] + y*m[5] + z*m[6] + m[7];
  *outz = x*m[8] + y*m[9] + z*m[10] + m[11];
}