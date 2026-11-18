_Bool func0(int *dict,int size,int n)

{
  int i;
  int n_local;
  int size_local;
  int *dict_local;
  
  i = 0;
  while( true ) {
    if (size <= i) {
      return true;
    }
    if (dict[i] != n) break;
    i = i + 1;
  }
  return false;
}