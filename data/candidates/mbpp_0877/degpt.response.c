void func0(char *str)

{
  char cVar1;
  size_t sVar2;
  int j;
  int i;
  char temp;
  int n;
  char *str_local;
  
  sVar2 = strlen(str);
  for (i = 0; j = i, i < (int)sVar2 + -1; i = i + 1) {
    while (j = j + 1, j < (int)sVar2) {
      if (str[j] < str[i]) {
        cVar1 = str[i];
        str[i] = str[j];
        str[j] = cVar1;
      }
    }
  }
  return;
}