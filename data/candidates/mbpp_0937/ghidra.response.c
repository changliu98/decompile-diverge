char func0(char *str1)

{
  size_t sVar1;
  int i;
  int len;
  char max_char;
  int max_freq;
  int frequency [256];
  char *str1_local;
  
  memset(frequency,0,0x400);
  max_freq = 0;
  max_char = '\0';
  sVar1 = strlen(str1);
  for (i = 0; i < (int)sVar1; i = i + 1) {
    frequency[(byte)str1[i]] = frequency[(byte)str1[i]] + 1;
    if (max_freq < frequency[(byte)str1[i]]) {
      max_freq = frequency[(byte)str1[i]];
      max_char = str1[i];
    }
  }
  return max_char;
}