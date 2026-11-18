void geom_matTvec2d(double m[4], double v[2], double d[2])
{
 d[0] = m[0]*v[0] + m[1]*v[1];
 d[1] = m[2]*v[0] + m[3]*v[1];
}