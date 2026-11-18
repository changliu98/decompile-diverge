long check(long n)
{
 long i;
 char c=0;

 if(n%2==0)
 {
  c=0;
 }
 else if(n==1)
 {
  c=1;
 }
 else
 {
  n++;
  for(i=0;i!=n;i++)
  {
   if(n%2==0)
   {
    n/=2;
    if(++i==n)
    {
     c=1;
     break;
    }
   }
   else
   {
    c=0;
    break;
   }
  }
 }

 return c&1;
}