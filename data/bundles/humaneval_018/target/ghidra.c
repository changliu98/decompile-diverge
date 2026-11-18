int func0(char *str,char *substring)

{
  int iVar1;
  size_t sVar2;
  size_t sVar3;
  int i;
  int sub_len;
  int str_len;
  int out;
  char *substring_local;
  char *str_local;
  int local_c;
  
  out = 0;
  sVar2 = strlen(str);
  sVar3 = strlen(substring);
  if ((int)sVar2 == 0) {
    local_c = 0;
  }
  else {
    for (i = 0; i <= (int)sVar2 - (int)sVar3; i = i + 1) {
      iVar1 = strncmp(str + i,substring,(long)(int)sVar3);
      if (iVar1 == 0) {
        out = out + 1;
      }
    }
    local_c = out;
  }
  return local_c;
}