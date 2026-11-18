int func0(int n)

{
  int i;
  int n_local;
  
  i = 2;
  while( true ) {
    if (n < i * i) {
      return 1;
    }
    if (n % i == 0) break;
    i = i + 1;
  }
  return n / i;
}