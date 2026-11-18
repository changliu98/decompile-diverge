int func0(int *list1,int size)

{
  int i;
  int size_local;
  int *list1_local;
  
  i = 0;
  while( true ) {
    if (size <= i) {
      return 0;
    }
    if (list1[i] < 0) break;
    i = i + 1;
  }
  return list1[i];
}