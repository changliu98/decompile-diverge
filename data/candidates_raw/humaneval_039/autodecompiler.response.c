int prime(int n)
{
 int f1=1,f2=2;
 int i,j;
 int temp;
 int num=0;
 int isprime;
 while(1)
 {
  if(num<n)
  {
   temp=f1+f2;
   f1=f2;
   f2=temp;

   isprime=1;
   for(j=2;j*j<=f1;j++)
   {
    if(f1%j==0)
    {
     isprime=0;
     break;
    }
   }
   if(isprime) num++;
   if(num==n)
   {
    return f1;
   }
  }
  else
  {
   return 0;
  }
 }
}