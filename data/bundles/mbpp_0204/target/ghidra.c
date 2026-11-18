int func0(char *s,char c)

{
  size_t sVar1;
  int i;
  int res;
  char c_local;
  char *s_local;
  
  res = 0;
  i = 0;
  while( true ) {
    sVar1 = strlen(s);
    if (sVar1 <= (ulong)(long)i) break;
    if (s[i] == c) {
      res = res + 1;
    }
    i = i + 1;
  }
  return res;
}