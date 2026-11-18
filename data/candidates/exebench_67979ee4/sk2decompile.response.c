void quaternionComposition(float q1w, float q1x, float q1y, float q1z,
                           float q2w, float q2x, float q2y, float q2z,
                           float *qw, float *qx, float *qy, float *qz) {
  *qw = q1w * q2w + q1x * q2x - q1y * q2y - q1z * q2z;
  *qx = q1w * q2x + q1x * q2y - q1y * q2z - q1z * q2w;
  *qy = q1w * q2y + q1x * q2z - q1y * q2w - q1z * q2x;
  *qz = q1w * q2z + q1x * q2w - q1y * q2x - q1z * q2y;
}