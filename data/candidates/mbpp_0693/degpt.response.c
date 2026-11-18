char * func0(char *text1)

{
  bool bVar1;
  size_t sVar2;
  int space_found;
  size_t j;
  size_t i;
  char *result;
  size_t len;
  char *text1_local;
  char *local_10;
  
  if (text1 == (char *)0x0) {
    local_10 = (char *)0x0;
  }
  else {
    sVar2 = strlen(text1);
    local_10 = malloc(sVar2 + 1);
    if (local_10 == (char *)0x0) {
      local_10 = (char *)0x0;
    }
    else {
      j = 0;
      bVar1 = false;
      for (i = 0; text1[i] != '\0'; i = i + 1) {
        if (text1[i] == ' ') {
          if (!bVar1) {
            local_10[j] = ' ';
            bVar1 = true;
            j = j + 1;
          }
        }
        else {
          local_10[j] = text1[i];
          bVar1 = false;
          j = j + 1;
        }
      }
      local_10[j] = '\0';
    }
  }
  return local_10;
}