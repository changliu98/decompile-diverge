char * func0(char *str1)

{
  size_t sVar1;
  ushort **ppuVar2;
  size_t i;
  size_t j;
  char *result;
  size_t len;
  char *str1_local;
  char *local_10;
  
  sVar1 = strlen(str1);
  local_10 = malloc(sVar1 + 1);
  if (local_10 == (char *)0x0) {
    local_10 = (char *)0x0;
  }
  else {
    j = 0;
    for (i = 0; i < sVar1; i = i + 1) {
      ppuVar2 = __ctype_b_loc();
      if (((*ppuVar2)[(int)(uint)(byte)str1[i]] & 0x100) == 0) {
        local_10[j] = str1[i];
        j = j + 1;
      }
    }
    local_10[j] = '\0';
  }
  return local_10;
}