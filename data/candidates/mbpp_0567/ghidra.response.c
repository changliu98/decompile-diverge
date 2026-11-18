_Bool func0(int *list1,int size)

{
  int i;
  int size_local;
  int *list1_local;
  
  i = 0;
  while( true ) {
    if (size + -1 <= i) {
      return true;
    }
    if (list1[i + 1] < list1[i]) break;
    i = i + 1;
  }
  return false;
}