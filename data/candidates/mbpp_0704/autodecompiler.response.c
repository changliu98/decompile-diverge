double func0(int n)
{
 double x;
 if(n<3)
 {
  x=1.0;
 }
 else
 {
  x=1.0/(double)n+func0(n-1);
 }
 return x;
}