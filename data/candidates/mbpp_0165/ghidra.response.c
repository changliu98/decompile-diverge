int func0(char *str1)

{
  size_t sVar1;
  int i;
  int length;
  int count_chars;
  char *str1_local;
  
  count_chars = 0;
  sVar1 = strlen(str1);
  for (i = 0; i < (int)sVar1; i = i + 1) {
    if ((i == str1[i] + -0x41) || (i == str1[i] + -0x61)) {
      count_chars = count_chars + 1;
    }
  }
  return count_chars;
}