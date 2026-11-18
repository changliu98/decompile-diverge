_Bool func0(int *list1,int size1,int *list2,int size2)

{
  bool bVar1;
  int j;
  _Bool found;
  int i;
  _Bool exist;
  int size2_local;
  int *list2_local;
  int size1_local;
  int *list1_local;
  
  i = 0;
  do {
    if (size2 <= i) {
      return true;
    }
    bVar1 = false;
    for (j = 0; j < size1; j = j + 1) {
      if (list2[i] == list1[j]) {
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