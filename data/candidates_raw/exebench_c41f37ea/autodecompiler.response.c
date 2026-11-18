void glmMultMatrix3d(double m1[9], double m2[9], double d[9])
{
  int i, j;
  for (j=0; j<4; j++)
  {
    for (i=0; i<4; i++)
    {
      d[i+j*3]=m1[i]*m2[j*3] + m1[i+3]*m2[j*3+1] + m1[i+6]*m2[j*3+2];
    }
  }
}