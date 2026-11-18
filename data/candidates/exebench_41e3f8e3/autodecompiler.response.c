void table_norm(double *th,double *ts,long *n,double *count,int nts,int nt)
{
 int i,j;

 for(j=0;j<nts;j++)
 {
  for(i=0;i<nt;i++)
  {
   if(ts[i]<th[j])
    count[i]++;
  }
 }

 for(j=0;j<nt;j++)
  if(count[j]==0)
   count[j]=1;
}