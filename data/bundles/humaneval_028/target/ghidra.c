char * func0(char **strings,int count)

{
  size_t sVar1;
  int i_1;
  char *out;
  int i;
  int length;
  int count_local;
  char **strings_local;
  char *local_10;
  
  length = 0;
  for (i = 0; i < count; i = i + 1) {
    sVar1 = strlen(strings[i]);
    length = length + (int)sVar1;
  }
  local_10 = malloc((long)(length + 1));
  if (local_10 == (char *)0x0) {
    local_10 = (char *)0x0;
  }
  else {
    *local_10 = '\0';
    for (i_1 = 0; i_1 < count; i_1 = i_1 + 1) {
      strcat(local_10,strings[i_1]);
    }
  }
  return local_10;
}