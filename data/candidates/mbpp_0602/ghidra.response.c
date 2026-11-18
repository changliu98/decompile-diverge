char func0(char *str1)

{
  size_t sVar1;
  int j;
  int count;
  char c;
  int i;
  int length;
  char *str1_local;
  
  sVar1 = strlen(str1);
  i = 0;
  while( true ) {
    if ((int)sVar1 <= i) {
      return '0';
    }
    count = 0;
    for (j = 0; j <= i; j = j + 1) {
      if (str1[j] == str1[i]) {
        count = count + 1;
      }
    }
    if (1 < count) break;
    i = i + 1;
  }
  return str1[i];
}