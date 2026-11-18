int func0(int *l,int size)

{
  int i;
  int gcd;
  int num2;
  int num1;
  int size_local;
  int *l_local;
  
  gcd = find_gcd(*l,l[1]);
  for (i = 2; i < size; i = i + 1) {
    gcd = find_gcd(gcd,l[i]);
  }
  return gcd;
}