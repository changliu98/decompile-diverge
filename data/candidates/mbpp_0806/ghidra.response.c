int func0(char *test_str)

{
  size_t sVar1;
  ushort **ppuVar2;
  int idx;
  int length;
  int res;
  int cnt;
  char *test_str_local;
  
  cnt = 0;
  res = 0;
  sVar1 = strlen(test_str);
  for (idx = 0; idx < (int)sVar1; idx = idx + 1) {
    ppuVar2 = __ctype_b_loc();
    if (((*ppuVar2)[(int)test_str[idx]] & 0x100) == 0) {
      if (res < cnt) {
        res = cnt;
      }
      cnt = 0;
    }
    else {
      cnt = cnt + 1;
    }
  }
  ppuVar2 = __ctype_b_loc();
  if ((((*ppuVar2)[(int)test_str[(int)sVar1 + -1]] & 0x100) != 0) && (res < cnt)) {
    res = cnt;
  }
  return res;
}