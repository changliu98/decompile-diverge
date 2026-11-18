void mul_mat_vec_2(float *m, float *v, float *out) {
  out[0] = m[0] * v[0] + m[1] * v[1];
  out[1] = m[2] * v[0] + m[3] * v[1];
}