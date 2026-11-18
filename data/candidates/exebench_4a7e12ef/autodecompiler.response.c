void mat3mulv(float result[3], float m[9], const float v[3])
{
  int i, j;
  float v1[3];

  for (j=0; j<3; j++)
  {
    v1[j]=0.0f;
    for (i=0; i<3; i++) v1[j] += m[j*3+i] * v[i];
  }
  for (i=0; i<3; i++) result[i]=v1[i];
}