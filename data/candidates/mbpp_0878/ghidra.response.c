_Bool func0(int *test_tuple,int tuple_size,int *K,int K_size)

{
  bool bVar1;
  int j;
  _Bool found;
  int i;
  int K_size_local;
  int *K_local;
  int tuple_size_local;
  int *test_tuple_local;
  
  i = 0;
  do {
    if (tuple_size <= i) {
      return true;
    }
    bVar1 = false;
    for (j = 0; j < K_size; j = j + 1) {
      if (test_tuple[i] == K[j]) {
        bVar1 = true;
        break;
      }
    }
    if (!bVar1) {
      return false;
    }
    i = i + 1;
  } while( true );
}