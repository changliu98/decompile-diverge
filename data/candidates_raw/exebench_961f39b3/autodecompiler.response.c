void glmMultVectorByMatrix4f(float result[3], const float m[16], const float v[3])
{
  float t[3];
  t[0]=m[0]*v[0]+m[1]*v[1]+m[2]*v[2]+m[3];
  t[1]=m[4]*v[0]+m[5]*v[1]+m[6]*v[2]+m[7];
  t[2]=m[8]*v[0]+m[9]*v[1]+m[10]*v[2]+m[11];
  ((result)[0]=(t)[0];(result)[1]=(t)[1];(result)[2]=(t)[2]);
}