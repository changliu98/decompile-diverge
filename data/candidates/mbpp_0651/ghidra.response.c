_Bool func0(int *test_tup1,int n1,int *test_tup2,int n2)

{
  bool bVar1;
  int j;
  _Bool found;
  int i;
  int n2_local;
  int *test_tup2_local;
  int n1_local;
  int *test_tup1_local;
  
  i = 0;
  do {
    if (n2 <= i) {
      return true;
    }
    bVar1 = false;
    for (j = 0; j < n1; j = j + 1) {
      if (test_tup2[i] == test_tup1[j]) {
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