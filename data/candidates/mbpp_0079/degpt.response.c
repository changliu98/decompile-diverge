int func0(char *s)

{
  char *__s;
  size_t sVar1;
  char *token;
  char *s_local;
  int local_c;
  
  __s = strtok(s," ");
  if (__s == (char *)0x0) {
    local_c = 0;
  }
  else {
    sVar1 = strlen(__s);
    if ((sVar1 & 1) == 0) {
      local_c = 0;
    }
    else {
      local_c = 1;
    }
  }
  return local_c;
}