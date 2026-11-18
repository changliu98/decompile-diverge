int func0(int a[],int n)
{
 int s=0,i,t;
 for(i=0;i<n;i++)
 {
  if((t=a[i])<0)t=-t;
  while(t>0)
  {
   s=s+t%10;
   t=t/10;
  }
 }
 return s;
}