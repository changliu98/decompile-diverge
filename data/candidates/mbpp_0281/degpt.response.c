_Bool func0(int *test_list,int length)

{
  int j;
  int i;
  int length_local;
  int *test_list_local;
  
  i = 0;
  do {
    j = i;
    if (length + -1 <= i) {
      return true;
    }
    while (j = j + 1, j < length) {
      if (test_list[i] == test_list[j]) {
        return false;
      }
    }
    i = i + 1;
  } while( true );
}