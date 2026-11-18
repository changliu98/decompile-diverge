int func0(int *l,int size)

{
  int i;
  int lcm;
  int num2;
  int num1;
  int size_local;
  int *l_local;
  
  lcm = find_lcm(*l,l[1]);
  for (i = 2; i < size; i = i + 1) {
    lcm = find_lcm(lcm,l[i]);
  }
  return lcm;
}