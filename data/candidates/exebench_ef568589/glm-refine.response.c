void __cdecl mat3f_rotateQuatVec_new(float *matrix, const float *quat)
{
  // Unpack quaternion components for readability
  float x = quat[0];
  float y = quat[1];
  float z = quat[2];
  float w = quat[3];

  // Compute the squared magnitude of the quaternion
  float sq_magnitude = (x * x) + (y * y) + (z * z) + (w * w);

  // Calculate the scaling factor
  float s = 2.0f / sq_magnitude;

  // Compute intermediate products
  float xs = x * s;
  float ys = y * s;
  float zs = z * s;

  float wx = w * xs;
  float wy = w * ys;
  float wz = w * zs;

  float xx = x * xs;
  float xy = x * ys;
  float xz = x * zs;

  float yy = y * ys;
  float yz = y * zs;
  float zz = z * zs;

  // Build the 3x3 rotation matrix (row-major)
  matrix[0] = 1.0f - (yy + zz);
  matrix[1] = xy + wz;
  matrix[2] = xz - wy;

  matrix[3] = xy - wz;
  matrix[4] = 1.0f - (xx + zz);
  matrix[5] = yz + wx;

  matrix[6] = xz + wy;
  matrix[7] = yz - wx;
  matrix[8] = 1.0f - (xx + yy);
}