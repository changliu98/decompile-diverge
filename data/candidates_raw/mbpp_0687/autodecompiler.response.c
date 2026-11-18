int gcd(int x, int y)
{
  int z;
  if (x < y) z = x; else z = y;
  int v2;
  if (x > y) v2 = x; else v2 = y;
  int v4;
  if (z == 0) v4 = v2; else
  if (z == 1) v4 = 1; else
  v4 = func0(z, v2 % z);
  return v4;
}