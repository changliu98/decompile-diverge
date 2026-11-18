char * func0(char *str)

{
  size_t sVar1;
  int i;
  int j;
  char *str_local;
  
  j = 0;
  i = 0;
  while( true ) {
    sVar1 = strlen(str);
    if (sVar1 <= (ulong)(long)i) break;
    if (i % 2 == 0) {
      func0::result[j] = str[i];
      j = j + 1;
    }
    i = i + 1;
  }
  func0::result[j] = '\0';
  return func0::result;
}