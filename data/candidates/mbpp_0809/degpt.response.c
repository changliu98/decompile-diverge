_Bool func0(int *test_tup1,int *test_tup2,int size)

{
  int i;
  _Bool res;
  int size_local;
  int *test_tup2_local;
  int *test_tup1_local;
  
  i = 0;
  while( true ) {
    if (size <= i) {
      return true;
    }
    if (test_tup1[i] <= test_tup2[i]) break;
    i = i + 1;
  }
  return false;
}