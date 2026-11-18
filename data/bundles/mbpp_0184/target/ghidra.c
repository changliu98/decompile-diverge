_Bool func0(int *list,int count,int num)

{
  int i;
  int num_local;
  int count_local;
  int *list_local;
  
  i = 0;
  while( true ) {
    if (count <= i) {
      return true;
    }
    if (list[i] < num) break;
    i = i + 1;
  }
  return false;
}