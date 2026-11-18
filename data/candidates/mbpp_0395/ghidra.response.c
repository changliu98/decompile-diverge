char func0(char *str1)

{
  char cVar1;
  size_t sVar2;
  char c_1;
  int i_1;
  char c;
  int i;
  int length;
  int idx;
  char char_order [256];
  int ctr [256];
  char *str1_local;
  
  memset(ctr,0,0x400);
  idx = 0;
  sVar2 = strlen(str1);
  for (i = 0; i < (int)sVar2; i = i + 1) {
    cVar1 = str1[i];
    if (ctr[cVar1] == 0) {
      char_order[idx] = cVar1;
      idx = idx + 1;
    }
    ctr[cVar1] = ctr[cVar1] + 1;
  }
  i_1 = 0;
  while( true ) {
    if (idx <= i_1) {
      return '\0';
    }
    if (ctr[char_order[i_1]] == 1) break;
    i_1 = i_1 + 1;
  }
  return char_order[i_1];
}