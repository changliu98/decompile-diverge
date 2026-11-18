double func0(int n){
  if (n < 0)
    return 0.0;
  return 1 / pow(2.0, n) + func0(n - 1);
}