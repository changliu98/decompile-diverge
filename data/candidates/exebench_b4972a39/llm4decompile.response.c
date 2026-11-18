void sub3x3(double a[3][3], double b[3][3])
{
  int i,j;
  for(i=0; i<3; i++)
    for(j=0; j<3; j++)
      b[i][j] -= a[i][j];
}