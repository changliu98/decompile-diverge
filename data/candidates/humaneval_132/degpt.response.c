int func0(char *str)

{
  size_t sVar1;
  int i;
  int maxcount;
  int count;
  char *str_local;
  
  count = 0;
  maxcount = 0;
  i = 0;
  while( true ) {
    sVar1 = strlen(str);
    if (sVar1 <= (ulong)(long)i) {
      return 0;
    }
    if (str[i] == '[') {
      count = count + 1;
    }
    if (str[i] == ']') {
      count = count + -1;
    }
    if (count < 0) {
      count = 0;
    }
    if (maxcount < count) {
      maxcount = count;
    }
    if (count <= maxcount + -2) break;
    i = i + 1;
  }
  return 1;
}