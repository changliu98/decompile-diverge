_Bool func0(int *test_tup1,int *test_tup2,int length)

{
  int i;
  int length_local;
  int *test_tup2_local;
  int *test_tup1_local;
  
  i = 0;
  while( true ) {
    if (length <= i) {
      return true;
    }
    if (test_tup2[i] <= test_tup1[i]) break;
    i = i + 1;
  }
  return false;
}