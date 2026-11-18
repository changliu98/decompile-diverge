_Bool func0(int *test_tup,int n,int K)

{
  int i;
  _Bool res;
  int K_local;
  int n_local;
  int *test_tup_local;
  
  i = 0;
  while( true ) {
    if (n <= i) {
      return false;
    }
    if (test_tup[i] == K) break;
    i = i + 1;
  }
  return true;
}