int func0(char *text)

{
  ushort **ppuVar1;
  int i;
  char *text_local;
  
  i = 0;
  while( true ) {
    if (text[i] == '\0') {
      return -1;
    }
    ppuVar1 = __ctype_b_loc();
    if (((*ppuVar1)[(int)text[i]] & 0x800) != 0) break;
    i = i + 1;
  }
  return i;
}