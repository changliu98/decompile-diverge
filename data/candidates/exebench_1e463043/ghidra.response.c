int c_insensitive(char *a,char *b)

{
  bool bVar1;
  int x;
  char *b_local;
  char *a_local;
  
  for (x = 0; a[x] != '\0'; x = x + 1) {
    if (('`' < a[x]) && (a[x] < '{')) {
      a[x] = a[x] + -0x20;
    }
  }
  for (x = 0; b[x] != '\0'; x = x + 1) {
    if (('`' < b[x]) && (b[x] < '{')) {
      b[x] = b[x] + -0x20;
    }
  }
  x = 0;
  while( true ) {
    bVar1 = false;
    if (a[x] != '\0') {
      bVar1 = b[x] != '\0';
    }
    if (!bVar1) {
      return 0;
    }
    if (b[x] < a[x]) {
      return 1;
    }
    if (a[x] < b[x]) break;
    x = x + 1;
  }
  return -1;
}