char * func0(char *str1)

{
  size_t sVar1;
  int i;
  int j;
  char *str1_local;
  
  j = 0;
  i = 1;
  while( true ) {
    sVar1 = strlen(str1);
    if (sVar1 < (ulong)(long)i) break;
    if (i % 2 != 0) {
      func0::str2[j] = str1[i + -1];
      j = j + 1;
    }
    i = i + 1;
  }
  func0::str2[j] = '\0';
  return func0::str2;
}