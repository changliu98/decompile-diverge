int fun(int n)
{
 int i,j;
 char flag=0;
 for(i=1;i*i<=n;i++)
 {
  for(j=1;j*j<=n;j++)
  {
   if((i*i)+(j*j)==n)
   {
    flag=1;
    break;
   }
  }
 }
 return flag;
}