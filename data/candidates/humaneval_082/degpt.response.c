_Bool func0(char *str)

{
  int iVar1;
  size_t sVar2;
  int i;
  int l;
  char *str_local;
  _Bool local_9;
  
  sVar2 = strlen(str);
  iVar1 = (int)sVar2;
  if (iVar1 < 2) {
    local_9 = false;
  }
  else {
    for (i = 2; i * i <= iVar1; i = i + 1) {
      if (iVar1 % i == 0) {
        return false;
      }
    }
    local_9 = true;
  }
  return local_9;
}