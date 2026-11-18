int func0(int *l, int size) {
  int num1 = l[0];
  int num2 = l[1];
  int lcm = find_lcm(num1, num2);
  for (int i = 2; i < size; i++) {
    lcm = find_lcm(lcm, l[i]);
  }
  return lcm;
}