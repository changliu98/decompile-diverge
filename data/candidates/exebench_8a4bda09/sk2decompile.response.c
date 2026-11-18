void rsQuat_toMat(const rsQuat quat, float *mat) {
  if (quat[0] == 0.0f && quat[1] == 0.0f && quat[2] == 0.0f) {
    mat[0] = 1.0f;
    mat[1] = 0.0f;
    mat[2] = 0.0f;
    mat[3] = 0.0f;
    mat[4] = 0.0f;
    mat[5] = 1.0f;
    mat[6] = 0.0f;
    mat[7] = 0.0f;
    mat[8] = 0.0f;
    mat[9] = 0.0f;
    mat[10] = 1.0f;
    mat[11] = 0.0f;
    mat[12] = 0.0f;
    mat[13] = 0.0f;
    mat[14] = 0.0f;
    mat[15] = 1.0f;
  } else {
    float s = 2.0f / (quat[0] * quat[0] + quat[1] * quat[1] + quat[2] * quat[2] +
                      quat[3] * quat[3]);
    float xs = quat[0] * s;
    float ys = quat[1] * s;
    float zs = quat[2] * s;
    float wx = quat[3] * xs;
    float wy = quat[3] * ys;
    float wz = quat[3] * zs;
    float xx = quat[0] * xs;
    float xy = quat[0] * ys;
    float xz = quat[0] * zs;
    float yy = quat[1] * ys;
    float yz = quat[1] * zs;
    float zz = quat[2] * zs;
    mat[0] = 1.0f - yy - zz;
    mat[1] = xy + wz;
    mat[2] = xz - wy;
    mat[3] = 0.0f;
    mat[4] = xy - wz;
    mat[5] = 1.0f - xx - zz;
    mat[6] = yz + wx;
    mat[7] = 0.0f;
    mat[8] = xz + wy;
    mat[9] = yz - wx;
    mat[10] = 1.0f - xx - yy;
    mat[11] = 0.0f;
    mat[12] = 0.0f;
    mat[13] = 0.0f;
    mat[14] = 0.0f;
    mat[15] = 1.0f;
  }
}