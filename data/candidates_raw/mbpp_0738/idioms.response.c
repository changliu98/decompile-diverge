double f(int n){
  if (n < 0)
    return 0.0;
  return 1 / pow(2.0, n) + f(n - 1);
}