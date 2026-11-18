_Bool func0(_Bool *test_tup,int size)

{
  int i;
  int size_local;
  _Bool *test_tup_local;
  
  i = 0;
  while( true ) {
    if (size <= i) {
      return true;
    }
    if ((test_tup[i] & 1U) == 0) break;
    i = i + 1;
  }
  return false;
}