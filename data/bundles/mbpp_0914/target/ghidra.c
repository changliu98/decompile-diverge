_Bool func0(char *s)

{
  size_t sVar1;
  int i;
  int length;
  char *s_local;
  
  sVar1 = strlen(s);
  i = 0;
  while( true ) {
    if ((int)sVar1 + -2 <= i) {
      return *s != s[1];
    }
    if (s[i] != s[i + 2]) break;
    i = i + 1;
  }
  return false;
}