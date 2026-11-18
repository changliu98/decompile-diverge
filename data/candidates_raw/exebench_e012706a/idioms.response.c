void get_mat_vec(double m[3][3], double v1[3], double v2[3], double v3[3])
{
  int i;
  for (i = 0; i < 3; i++)
  {
    v1[i] = m[i][0];
    v2[i] = m[i][1];
    v3[i] = m[i][2];
  }
}