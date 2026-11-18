void normalize_quat(float *quaternion)
{
  // Calculate the squared magnitude of the quaternion
  float magnitude_squared = quaternion[0] * quaternion[0] + quaternion[1] * quaternion[1] + quaternion[2] * quaternion[2] + quaternion[3] * quaternion[3];
  int index;
  // Normalize each component by dividing by the squared magnitude
  for (index = 0; index < 4; index++) {
    quaternion[index] /= magnitude_squared;
  }
}