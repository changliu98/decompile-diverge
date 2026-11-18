int func0(int n)

{
  int i;
  int res;
  int n_local;
  
  i = n;
  while( true ) {
    if (i < 1) {
      return 0;
    }
    if ((i & i - 1U) == 0) break;
    i = i + -1;
  }
  return i;
}