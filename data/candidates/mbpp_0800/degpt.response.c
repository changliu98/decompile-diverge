void func0(char *text,char *result)

{
  ushort **ppuVar1;
  int j;
  int i;
  char *result_local;
  char *text_local;
  
  j = 0;
  for (i = 0; text[i] != '\0'; i = i + 1) {
    ppuVar1 = __ctype_b_loc();
    if (((*ppuVar1)[(int)(uint)(byte)text[i]] & 0x2000) == 0) {
      result[j] = text[i];
      j = j + 1;
    }
  }
  result[j] = '\0';
  return;
}