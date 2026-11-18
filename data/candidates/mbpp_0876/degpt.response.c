int func0(int x,int y)

{
  int z;
  int y_local;
  int x_local;
  
  z = y;
  if (y < x) {
    z = x;
  }
  for (; (z % x != 0 || (z % y != 0)); z = z + 1) {
  }
  return z;
}