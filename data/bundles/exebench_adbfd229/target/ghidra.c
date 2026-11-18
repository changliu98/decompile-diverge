void sort(char *str)

{
  char cVar1;
  bool bVar2;
  char t;
  int j;
  int i;
  char *str_local;
  
  for (j = 1; j < 10; j = j + 1) {
    i = 0;
    while( true ) {
      bVar2 = false;
      if (i < 10 - j) {
        bVar2 = str[i] != '\0';
      }
      if (!bVar2) break;
      if (str[i + 1] < str[i]) {
        cVar1 = str[i];
        str[i] = str[i + 1];
        str[i + 1] = cVar1;
      }
      i = i + 1;
    }
  }
  return;
}