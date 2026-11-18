_Bool func0(int *test_tup,int size)

{
  int i;
  int size_local;
  int *test_tup_local;
  
  i = 0;
  while( true ) {
    if (size <= i) {
      return false;
    }
    if (test_tup[i] == 0) break;
    i = i + 1;
  }
  return true;
}