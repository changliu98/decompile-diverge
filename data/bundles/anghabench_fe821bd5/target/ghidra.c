int ok_cp1251(char *s,int n)

{
  int i;
  int n_local;
  char *s_local;
  
  i = 1;
  while( true ) {
    if (n <= i) {
      return 1;
    }
    if (s[i] == -0x68) break;
    i = i + 1;
  }
  return 0;
}