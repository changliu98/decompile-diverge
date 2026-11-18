void dvec_rot(double *vec, double *ang)
{
  double tmp = vec[0]*ang[0]-vec[1]*ang[1];
  vec[1]=vec[0]*ang[1]+vec[1]*ang[0];
  vec[0]=tmp;
}