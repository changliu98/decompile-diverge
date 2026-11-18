char * func0(char *str1)

{
  int iVar1;
  size_t sVar2;
  size_t i;
  char *result;
  size_t len;
  char *str1_local;
  char *local_10;
  
  sVar2 = strlen(str1);
  local_10 = malloc(sVar2 + 1);
  if (local_10 == (char *)0x0) {
    local_10 = (char *)0x0;
  }
  else if (sVar2 != 0) {
    iVar1 = toupper((int)*str1);
    *local_10 = (char)iVar1;
    for (i = 1; i < sVar2; i = i + 1) {
      iVar1 = tolower((int)str1[i]);
      local_10[i] = (char)iVar1;
    }
    iVar1 = toupper((int)local_10[sVar2 - 1]);
    local_10[sVar2 - 1] = (char)iVar1;
    local_10[sVar2] = '\0';
  }
  return local_10;
}