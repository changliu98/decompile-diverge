char func0(char *str1)

{
  size_t sVar1;
  int i_1;
  int i;
  int length;
  char ch;
  int max;
  int ctr [256];
  int ASCII_SIZE;
  char *str1_local;
  
  memset(ctr,0,0x400);
  max = -1;
  ch = '\0';
  sVar1 = strlen(str1);
  for (i = 0; i < (int)sVar1; i = i + 1) {
    ctr[(int)str1[i]] = ctr[(int)str1[i]] + 1;
  }
  for (i_1 = 0; i_1 < (int)sVar1; i_1 = i_1 + 1) {
    if (max < ctr[(int)str1[i_1]]) {
      max = ctr[(int)str1[i_1]];
      ch = str1[i_1];
    }
  }
  return ch;
}