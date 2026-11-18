void Mat4_vec3_mul_inv(float* v, Mat4* m, float* src)
{
 float x = src[0], y = src[1], z = src[2];
 float x_ = m->m00 * x + m->m10 * y + m->m20 * z;
 float y_ = m->m01 * x + m->m11 * y + m->m21 * z;
 float z_ = m->m02 * x + m->m12 * y + m->m22 * z;
 float w = m->m03 * x + m->m13 * y + m->m23 * z;
 v[0] = x_ - w * m->m03;
 v[1] = y_ - w * m->m13;
 v[2] = z_ - w * m->m23;
}