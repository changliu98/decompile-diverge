double func0(int n)
{
 double res;
 if(n<0)
 {
  res=0;
 }
 else
 {
  res=1.0/pow(2.0,(double)n)+func0(n-1);
 }
 return res;
}