_Bool func0(char *str1,char *str2)

{
  size_t sVar1;
  size_t sVar2;
  int i;
  int M;
  int N;
  char *str2_local;
  char *str1_local;
  _Bool local_9;
  
  sVar1 = strlen(str1);
  sVar2 = strlen(str2);
  if ((int)sVar1 % (int)sVar2 == 0) {
    for (i = 0; i < (int)sVar1; i = i + 1) {
      if (str1[i] != str2[i % (int)sVar2]) {
        return false;
      }
    }
    local_9 = true;
  }
  else {
    local_9 = false;
  }
  return local_9;
}