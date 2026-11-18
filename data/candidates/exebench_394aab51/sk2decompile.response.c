void rsQuat_postMult(float* q, const float* q2) {
  float q0 = q[0], q1 = q[1], q2_ = q[2], q3 = q[3];
  q[0] = q2[3] * q0 + q2[0] * q3 + q2[1] * q2_ - q2[2] * q1;
  q[1] = q2[3] * q1 + q2[1] * q3 + q2[2] * q0 - q2[0] * q2_;
  q[2] = q2[3] * q2_ + q2[2] * q3 + q2[0] * q1 - q2[1] * q0;
  q[3] = q2[3] * q3 + q2[0] * q0 + q2[1] * q1 - q2[2] * q2_;
}