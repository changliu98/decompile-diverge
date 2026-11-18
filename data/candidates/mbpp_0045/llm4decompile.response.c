int func0(int *l, int size)
{
 int i;
 int gcd = find_gcd(l[0], l[1]);

 for (i = 2; i < size; i++)
  gcd = find_gcd(gcd, l[i]);

 return gcd;
}