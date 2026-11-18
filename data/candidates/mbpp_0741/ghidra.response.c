_Bool func0(char *s)

{
  size_t sVar1;
  int i;
  int n;
  char *s_local;
  
  sVar1 = strlen(s);
  i = 1;
  while( true ) {
    if ((int)sVar1 <= i) {
      return true;
    }
    if (s[i] != *s) break;
    i = i + 1;
  }
  return false;
}