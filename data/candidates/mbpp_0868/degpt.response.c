int func0(char *a)

{
  size_t sVar1;
  int i;
  char *x;
  int l;
  char *a_local;
  
  l = 0;
  for (x = a; *x == ' '; x = x + 1) {
  }
  i = 0;
  while( true ) {
    sVar1 = strlen(x);
    if (sVar1 <= (ulong)(long)i) break;
    if (x[i] == ' ') {
      l = 0;
    }
    else {
      l = l + 1;
    }
    i = i + 1;
  }
  return l;
}