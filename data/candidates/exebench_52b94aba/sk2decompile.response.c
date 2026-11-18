float qdot(float *q1, float *q2) {
  float dot;
  dot = q1[0] * q2[0] + q1[1] * q2[1] + q1[2] * q2[2] + q1[3] * q2[3];
  return dot;
}