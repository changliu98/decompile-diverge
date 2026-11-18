_Bool func0(char *str)

{
  size_t sVar1;
  int j;
  int i;
  char *str_local;
  
  i = 0;
  do {
    sVar1 = strlen(str);
    j = i;
    if (sVar1 <= (ulong)(long)i) {
      return true;
    }
    while( true ) {
      j = j + 1;
      sVar1 = strlen(str);
      if (sVar1 <= (ulong)(long)j) break;
      if (str[i] == str[j]) {
        return false;
      }
    }
    i = i + 1;
  } while( true );
}