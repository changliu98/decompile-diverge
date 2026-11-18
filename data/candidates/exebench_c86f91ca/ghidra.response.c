void remove_dupc2(char *str)

{
  bool bVar1;
  int j;
  int i;
  char *str_local;
  
  for (i = 0; str[i] != '\0'; i = i + 1) {
    j = i;
    if (str[i] != -1) {
      while (j = j + 1, str[j] != '\0') {
        if (str[i] == str[j]) {
          str[j] = -1;
        }
      }
    }
  }
  j = 0;
  while( true ) {
    bVar1 = false;
    if (str[j] != '\0') {
      bVar1 = str[j] != -1;
    }
    if (!bVar1) break;
    j = j + 1;
  }
  if (str[j] == '\0') {
    j = i + -1;
    i = j;
  }
  else {
    i = j;
  }
  while (j = j + 1, str[j] != '\0') {
    if (str[j] != -1) {
      str[i] = str[j];
      i = i + 1;
    }
  }
  str[i] = str[j];
  return;
}