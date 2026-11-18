int func0(int n)
{
 int x;
 int count;

 count = 0;
 for (x = 1; x <= n; x <<= 1)
  if (!(n & x))
   count++;
 return count;
}