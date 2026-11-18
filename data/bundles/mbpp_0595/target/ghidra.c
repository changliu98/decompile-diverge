int func0(char *str1,char *str2)

{
  size_t sVar1;
  int i;
  int len;
  int count;
  char *str2_local;
  char *str1_local;
  int local_c;
  
  count = 0;
  sVar1 = strlen(str1);
  for (i = 0; i < (int)sVar1; i = i + 1) {
    if (str1[i] != str2[i]) {
      count = count + 1;
    }
  }
  if (count % 2 == 0) {
    local_c = count / 2;
  }
  else {
    local_c = -1;
  }
  return local_c;
}