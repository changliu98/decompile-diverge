int func0(int n)
{
 int i,fact=1;
 int result;

 if(n>=11)
 {
  result = 0;
 }
 else
 {
  for(i=1;i<=n;i++)
  {
   fact = (fact * i) % 100;
  }
  result = fact;
 }

 return result;
}