int fun(int a[],int n)
{
 int i,j,k,s;
 char t;
 for(i=0;i<n;i++)
  for(j=i+1;j<n;j++)
   for(k=j+1;k<n;k++)
   {
    s=a[i]+a[j]+a[k];
    if(s==0){t=1;break;}
   }
 return t;
}