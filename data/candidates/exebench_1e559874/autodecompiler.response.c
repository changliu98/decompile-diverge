void convolve_4(double result[4], const double q1[4], const double q2[4])
{
  double w, x, y, z;
  w = q1[0] * q2[0] - q1[1] * q2[1] - q1[2] * q2[2] - q1[3] * q2[3];
  x = q1[0] * q2[1] + q1[1] * q2[0] + q1[2] * q2[3] - q1[3] * q2[2];
  y = q1[0] * q2[2] + q1[2] * q2[0] + q1[3] * q2[1] - q1[1] * q2[3];
  z = q1[0] * q2[3] + q1[3] * q2[0] + q1[1] * q2[2] - q1[2] * q2[1];

  memcpy(result, &w, sizeof(double));
  memcpy(result+1, &x, sizeof(double));
  memcpy(result+2, &y, sizeof(double));
  memcpy(result+3, &z, sizeof(double));
}