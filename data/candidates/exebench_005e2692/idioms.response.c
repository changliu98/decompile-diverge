void geom_matvec2f(float m[2][2], float v[2], float r[2])
{
  r[0] = m[0][0]*v[0] + m[0][1]*v[1];
  r[1] = m[1][0]*v[0] + m[1][1]*v[1];
}