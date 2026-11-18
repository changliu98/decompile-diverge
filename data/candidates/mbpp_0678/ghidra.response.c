char * func0(char *str1)

{
  size_t sVar1;
  int len;
  int j;
  int i;
  char *str1_local;
  
  j = 0;
  sVar1 = strlen(str1);
  for (i = 0; i < (int)sVar1; i = i + 1) {
    if (str1[i] != ' ') {
      str1[j] = str1[i];
      j = j + 1;
    }
  }
  str1[j] = '\0';
  return str1;
}