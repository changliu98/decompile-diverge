char * func0(char *text1)

{
  ushort **ppuVar1;
  int j;
  int i;
  char *text1_local;
  
  j = 0;
  for (i = 0; text1[i] != '\0'; i = i + 1) {
    ppuVar1 = __ctype_b_loc();
    if (((*ppuVar1)[(int)(uint)(byte)text1[i]] & 0x2000) == 0) {
      text1[j] = text1[i];
      j = j + 1;
    }
  }
  text1[j] = '\0';
  return text1;
}