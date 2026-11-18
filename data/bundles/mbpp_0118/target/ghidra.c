char ** func0(char *string)

{
  char *__s;
  char *pcVar1;
  char *token;
  int index;
  char *str;
  char **list;
  char *ptr;
  int count;
  char *string_local;
  char **local_10;
  
  count = 1;
  for (ptr = string; *ptr != '\0'; ptr = ptr + 1) {
    if (*ptr == ' ') {
      count = count + 1;
    }
  }
  local_10 = malloc((long)(count + 1) << 3);
  if (local_10 == (char **)0x0) {
    local_10 = (char **)0x0;
  }
  else {
    __s = strdup(string);
    if (__s == (char *)0x0) {
      free(local_10);
      local_10 = (char **)0x0;
    }
    else {
      index = 0;
      token = strtok(__s," ");
      while (token != (char *)0x0) {
        pcVar1 = strdup(token);
        local_10[index] = pcVar1;
        token = strtok((char *)0x0," ");
        index = index + 1;
      }
      local_10[index] = (char *)0x0;
      free(__s);
    }
  }
  return local_10;
}