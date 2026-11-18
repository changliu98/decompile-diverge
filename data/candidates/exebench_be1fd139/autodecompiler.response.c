void r3sums(double result[3], const double v[3], double s1, const double s2[3], double s3)
{
  result[0]=v[0]*s1+s2[0]*s3;
  result[1]=v[1]*s1+s2[1]*s3;
  result[2]=v[2]*s1+s2[2]*s3;
}