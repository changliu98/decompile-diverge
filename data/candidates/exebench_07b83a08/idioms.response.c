void Mat4_Translate(struct mat4 *mat, struct vec3 *vec) {
  mat->m[12] = mat->m[0]*vec->x + mat->m[4]*vec->y + mat->m[8]*vec->z + mat->m[12];
  mat->m[13] = mat->m[1]*vec->x + mat->m[5]*vec->y + mat->m[9]*vec->z + mat->m[13];
  mat->m[14] = mat->m[2]*vec->x + mat->m[6]*vec->y + mat->m[10]*vec->z + mat->m[14];
}