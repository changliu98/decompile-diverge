int func0(char *string,char c)

{
  size_t sVar1;
  int i;
  int length;
  int flag;
  char c_local;
  char *string_local;
  int local_c;
  
  flag = -1;
  sVar1 = strlen(string);
  for (i = 0; i < (int)sVar1; i = i + 1) {
    if (string[i] == c) {
      flag = i;
    }
  }
  if (flag == -1) {
    local_c = -1;
  }
  else {
    local_c = flag + 1;
  }
  return local_c;
}