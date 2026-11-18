int sboxCHECK(float *lb,float *ub,int m)
{
  int i;
  if(lb==NULL || ub==NULL)
    return 1;
  for(i=0;i<m;i++)
    if(lb[i]>ub[i])
      return 0;
  return 1;
}