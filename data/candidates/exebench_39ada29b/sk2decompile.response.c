void rsQuat_preMult(float* quat, const float* other) {
  float qx = quat[0];
  float qy = quat[1];
  float qz = quat[2];
  float qw = quat[3];
  quat[0] = other[3] * qx - other[0] * qw + other[1] * qz - other[2] * qy;
  quat[1] = other[3] * qy - other[1] * qw + other[2] * qx - other[0] * qz;
  quat[2] = other[3] * qz - other[2] * qw + other[0] * qy - other[1] * qx;
  quat[3] = other[3] * qw - other[0] * qx - other[1] * qy - other[2] * qz;
}