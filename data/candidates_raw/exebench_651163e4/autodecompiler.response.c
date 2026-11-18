int mat4_to_vec4d(double *m, double *v)
{
 v[0] = m[0];
 v[1] = m[1];
 v[2] = m[2];
 v[3] = 1.0;
 return 0;
}