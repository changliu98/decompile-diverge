long double func0(int n)
{
 long double fact=1;
 long double bfact=1;
 int i=1;

 while(1)
 {
  if(i<=n)
  {
   fact*=i;
   bfact*=fact;
   i++;
  }
  else
   return bfact;
 }
}