void mlVectorSubTo(float v1[4], float v2[4], float d[4])
{
  int i;
  for (i=0; i<4; i++) d[i]=v1[i]-v2[i];
}