int func0(int n)

{
  double dVar1;
  int i;
  int result;
  int n_local;
  
  result = 0;
  i = 2;
  while( true ) {
    dVar1 = sqrt((double)n);
    if ((int)dVar1 < i) break;
    if (n % i == 0) {
      result = 1;
    }
    i = i + 1;
  }
  return result;
}