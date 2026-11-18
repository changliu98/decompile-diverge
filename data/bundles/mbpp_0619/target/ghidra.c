char * func0(char *test_str)

{
  ushort **ppuVar1;
  int idx;
  int j;
  int i;
  char dig [1024];
  char *test_str_local;
  
  i = 0;
  j = 0;
  for (idx = 0; test_str[idx] != '\0'; idx = idx + 1) {
    ppuVar1 = __ctype_b_loc();
    if (((*ppuVar1)[(int)test_str[idx]] & 0x800) == 0) {
      func0::res[i] = test_str[idx];
      i = i + 1;
    }
    else {
      dig[j] = test_str[idx];
      j = j + 1;
    }
  }
  dig[j] = '\0';
  func0::res[i] = '\0';
  strcat(func0::res,dig);
  return func0::res;
}