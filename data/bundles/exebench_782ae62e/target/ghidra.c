void tosuper(char *a)

{
  int i;
  char *a_local;
  
  for (i = 0; a[i] != '\0'; i = i + 1) {
    if (('`' < a[i]) && (a[i] < '{')) {
      a[i] = a[i] + -0x20;
    }
  }
  return;
}