void sort(char *a)

{
  char cVar1;
  int k;
  int j;
  int i;
  char *a_local;
  
  i = 0;
  while (a[i + 1] != '\0') {
    cVar1 = a[i + 1];
    for (j = i; cVar1 < a[j] && 0 < j; j = j + -1) {
      a[j + 1] = a[j];
    }
    a[j + 1] = cVar1;
    i = i + 1;
  }
  return;
}