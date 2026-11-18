char * func0(char *str)

{
  bool bVar1;
  int iVar2;
  size_t sVar3;
  int is_palindrome;
  char *result;
  int j;
  int i;
  int len;
  char *str_local;
  char *local_10;
  
  sVar3 = strlen(str);
  iVar2 = (int)sVar3;
  local_10 = malloc((long)(iVar2 * 2 + 1));
  if (local_10 == (char *)0x0) {
    local_10 = (char *)0x0;
  }
  else {
    for (i = 0; i < iVar2; i = i + 1) {
      bVar1 = true;
      for (j = 0; j < (iVar2 - i) / 2; j = j + 1) {
        if (str[i + j] != str[(iVar2 + -1) - j]) {
          bVar1 = false;
          break;
        }
      }
      if (bVar1) {
        strncpy(local_10,str,(long)iVar2);
        for (j = 0; j < i; j = j + 1) {
          local_10[iVar2 + j] = str[(i - j) + -1];
        }
        local_10[iVar2 + i] = '\0';
        return local_10;
      }
    }
    strncpy(local_10,str,(long)iVar2);
    for (j = 0; j < iVar2; j = j + 1) {
      local_10[iVar2 + j] = str[(iVar2 - j) + -1];
    }
    local_10[iVar2 << 1] = '\0';
  }
  return local_10;
}