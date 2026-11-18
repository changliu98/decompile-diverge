_Bool func0(int *l,int size,int t)

{
  int i;
  int t_local;
  int size_local;
  int *l_local;
  
  i = 0;
  while( true ) {
    if (size <= i) {
      return true;
    }
    if (t <= l[i]) break;
    i = i + 1;
  }
  return false;
}