void removeslave(int *slave,int n)

{
  int i;
  int n_local;
  int *slave_local;
  
  i = 9;
  n_local = n;
  while( true ) {
    if (i < 0) {
      return;
    }
    if (slave[i] != 0) {
      slave[i] = 0;
      n_local = n_local + -1;
    }
    if (n_local == 0) break;
    i = i + -1;
  }
  return;
}