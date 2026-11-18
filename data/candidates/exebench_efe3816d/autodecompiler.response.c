int metric(double p1[3],double p2[3], double p3[3], double ret[10])
{
  int i;
  for(i=0;i<10;i++)
    ret[i]=0.0;

  ret[8]=1.0;
  ret[4]=ret[8];
  ret[0]=ret[8];

  return 0;
}