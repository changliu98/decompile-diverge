void __cdecl mat3d_rotateQuatVec_new(double *matrix, const double *quat)
{
  // Unroll the quaternion components for readability.
  // Based on the math, the quaternion layout is (x, y, z, w).
  double x = quat[0];
  double y = quat[1];
  double z = quat[2];
  double w = quat[3];

  // Calculate the normalization scalar 's'
  double s = 2.0 / (x * x + y * y + z * z + w * w);

  // Precompute the products of quaternion components and 's'
  double xs = x * s;
  double ys = y * s;
  double zs = z * s;
  double wx = w * xs;
  double wy = w * ys;
  double wz = w * zs;
  double xx = x * xs;
  double xy = x * ys;
  double xz = x * zs;
  double yy = y * ys;
  double yz = y * zs;
  double zz = z * zs;

  // Populate the 3x3 rotation matrix (row-major order)
  matrix[0] = 1.0 - (yy + zz);
  matrix[1] = xy + wz;
  matrix[2] = xz - wy;

  matrix[3] = xy - wz;
  matrix[4] = 1.0 - (xx + zz);
  matrix[5] = yz + wx;

  matrix[6] = xz + wy;
  matrix[7] = yz - wx;
  matrix[8] = 1.0 - (xx + yy);
}