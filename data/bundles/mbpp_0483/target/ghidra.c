int func0(int x)

{
  int fact;
  int i;
  int x_local;
  
  fact = 1;
  i = 1;
  while( true ) {
    if (x <= i) {
      return i + -1;
    }
    fact = fact * i;
    if (fact % x == 0) break;
    i = i + 1;
  }
  return i;
}