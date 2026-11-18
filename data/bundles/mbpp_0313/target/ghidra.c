int func0(int *list1,size_t size)

{
  int i;
  size_t size_local;
  int *list1_local;
  
  i = 0;
  while( true ) {
    if (size <= (ulong)(long)i) {
      return -1;
    }
    if (-1 < list1[i]) break;
    i = i + 1;
  }
  return list1[i];
}