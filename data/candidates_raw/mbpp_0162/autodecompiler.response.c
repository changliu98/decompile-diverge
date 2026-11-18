int func0(int n)
{
 int k;
 int i;

 if (n < 2)
  k = 0;
 else {
  k = n + func0(n-2);
 }
 return k;
}