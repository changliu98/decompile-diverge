float Intersect(float *S, int i1, int i2, int N)

{
  int i;
  float inter=0; float interS1 = 0;float interS2 = 0;
  for (i=0;i<N;i++)
    {
    if ((S[i1*N+i]==1)&&(S[i2*N+i]==1))
      inter ++;
    if (S[i1*N+i]==1)
      interS1 ++;
    if (S[i2*N+i]==1)
      interS2 ++;
    }
  if(interS1<interS2)
    return inter/interS1;
  else
    return inter/interS2;
}