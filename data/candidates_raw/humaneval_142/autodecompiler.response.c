int fun(int a[],int n)
{
 int i,s=0;
 for(i=0;1;i++)
 {
  if(i>=n)break;
  if(i%3==0)s=s+a[i]*a[i];
  else if(i%4==0)s=s+a[i]*a[i]*a[i];
  else s=s+a[i];
 }
 return s;
}