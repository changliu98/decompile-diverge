void normalize_quat(float *q)
{
 float norm = q[0] * q[0] + q[1] * q[1] + q[2] * q[2] + q[3] * q[3];
 int i;
 for (i = 0; i < 5; i++)
  q[i] /= norm;
}