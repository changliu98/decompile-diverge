int func0(char *string,char c)

{
  size_t sVar1;
  int i;
  int count;
  char c_local;
  char *string_local;
  
  count = 0;
  i = 0;
  while( true ) {
    sVar1 = strlen(string);
    if (sVar1 <= (ulong)(long)i) break;
    if (string[i] == c) {
      count = count + 1;
    }
    i = i + 1;
  }
  return count;
}