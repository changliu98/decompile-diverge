int isDivisor(int a, int b){
  int sum = divSum(a);
  return divSum(b) == sum;
}