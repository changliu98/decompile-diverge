int func0(int x, int max, int limit)
{
 int y;
 int z;

 if ((max - 1) < limit)
  z = max - 1;
 else
  z = limit;

 y = (x * z) / max;

 return y;
}