int func0(int x,int n)

{
  int count;
  int p;
  int n_local;
  int x_local;
  
  p = 1;
  count = 0;
  while( true ) {
    if (x < p || 99 < count) {
      return 0;
    }
    if (p == x) break;
    p = p * n;
    count = count + 1;
  }
  return 1;
}