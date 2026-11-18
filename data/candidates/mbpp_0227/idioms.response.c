int func0(int a, int b, int c){
  if (a <= b && a <= c)
    return a;
  if (b > a && b > c)
    return c;
  return b;
}