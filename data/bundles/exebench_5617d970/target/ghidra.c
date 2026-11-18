int arrayFind(int elem,int *list,int length)

{
  int j;
  int i;
  int length_local;
  int *list_local;
  int elem_local;
  
  i = 0;
  while( true ) {
    if (length <= i) {
      return -1;
    }
    if (list[i] == elem) break;
    i = i + 1;
  }
  for (j = 0; j < i; j = j + 1) {
    list[i - j] = list[(i - j) + -1];
  }
  *list = elem;
  return 0;
}