_Bool func0(char *s)

{
  size_t sVar1;
  int i;
  char *s_local;
  _Bool local_9;
  
  sVar1 = strlen(s);
  if (sVar1 < 3) {
    local_9 = false;
  }
  else {
    for (i = 2; sVar1 = strlen(s), (ulong)(long)i < sVar1; i = i + 1) {
      if ((s[i] == s[i + -1]) || (s[i] == s[i + -2])) {
        return false;
      }
    }
    local_9 = true;
  }
  return local_9;
}