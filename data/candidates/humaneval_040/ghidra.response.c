_Bool func0(int *l,int size)

{
  int iVar1;
  int k;
  int j;
  int i;
  int size_local;
  int *l_local;
  
  i = 0;
  do {
    iVar1 = i;
    if (size <= i) {
      return false;
    }
    while (j = iVar1 + 1, j < size) {
      for (k = iVar1 + 2; iVar1 = j, k < size; k = k + 1) {
        if (l[i] + l[j] + l[k] == 0) {
          return true;
        }
      }
    }
    i = i + 1;
  } while( true );
}