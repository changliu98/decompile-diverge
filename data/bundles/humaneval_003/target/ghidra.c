int func0(int *operations,int size)

{
  int i;
  int num;
  int size_local;
  int *operations_local;
  
  num = 0;
  i = 0;
  while( true ) {
    if (size <= i) {
      return 0;
    }
    num = operations[i] + num;
    if (num < 0) break;
    i = i + 1;
  }
  return 1;
}