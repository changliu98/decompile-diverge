_Bool func0(int *l,int size)

{
  int j;
  int i;
  int size_local;
  int *l_local;
  
  i = 0;
  do {
    j = i;
    if (size <= i) {
      return false;
    }
    while (j = j + 1, j < size) {
      if (l[i] + l[j] == 0) {
        return true;
      }
    }
    i = i + 1;
  } while( true );
}