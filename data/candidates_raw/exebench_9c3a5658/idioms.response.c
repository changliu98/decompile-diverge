void set_to_vec(double m[3][3], double v1[], double v2[], double v3[])
{
  int i;
  for (i = 0; i < 3; i++)
  {
    m[i][0] = v1[i];
    m[i][1] = v2[i];
    m[i][2] = v3[i];
  }
}