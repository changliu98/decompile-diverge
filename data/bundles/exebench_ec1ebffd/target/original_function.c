int slevmar_box_check(float *lb, float *ub, int m)
{
register int i;

  if(!lb || !ub) return 1;

  for(i=0; i<m; ++i)
    if(lb[i]>ub[i]) return 0;

  return 1;
}