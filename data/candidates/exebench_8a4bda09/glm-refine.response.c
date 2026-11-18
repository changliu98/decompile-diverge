void __cdecl rsQuat_toMat(float *q, float *mat)
{
  float x = q[0];
  float y = q[1];
  float z = q[2];
  float w = q[3];

  // If the quaternion is a zero vector, return the identity matrix
  if (x == 0.0 && y == 0.0 && z == 0.0)
  {
    mat[0]  = 1.0; mat[1]  = 0.0; mat[2]  = 0.0; mat[3]  = 0.0;
    mat[4]  = 0.0; mat[5]  = 1.0; mat[6]  = 0.0; mat[7]  = 0.0;
    mat[8]  = 0.0; mat[9]  = 0.0; mat[10] = 1.0; mat[11] = 0.0;
    mat[12] = 0.0; mat[13] = 0.0; mat[14] = 0.0; mat[15] = 1.0;
    return;
  }

  // Calculate the normalization scale factor
  float s = 2.0 / (x * x + y * y + z * z + w * w);

  // Scale the vector and precompute products for matrix elements
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

  // Build the 4x4 rotation matrix (column-major layout)
  mat[0]  = 1.0 - (yy + zz);
  mat[1]  = xy + wz;
  mat[2]  = xz - wy;
  mat[3]  = 0.0;

  mat[4]  = xy - wz;
  mat[5]  = 1.0 - (xx + zz);
  mat[6]  = yz + wx;
  mat[7]  = 0.0;

  mat[8]  = xz + wy;
  mat[9]  = yz - wx;
  mat[10] = 1.0 - (xx + yy);
  mat[11] = 0.0;

  mat[12] = 0.0;
  mat[13] = 0.0;
  mat[14] = 0.0;
  mat[15] = 1.0;
}