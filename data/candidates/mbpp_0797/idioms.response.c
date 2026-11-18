int func0(int l, int r){
  int sum = sum_Odd(r);
  return sum - sum_Odd(l-1);
}