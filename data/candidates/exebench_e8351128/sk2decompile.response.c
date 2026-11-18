float lib3ds_vector_dot(float a[3], float b[3]) {
  float c;
  c = a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
  return c;
}