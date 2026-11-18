int func0(int a,int b,int c)

{
  int smallest;
  int c_local;
  int b_local;
  int a_local;
  
  if ((((b < a) || (smallest = a, c < a)) && (smallest = c, b <= a)) && (b <= c)) {
    smallest = b;
  }
  return smallest;
}