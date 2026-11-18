char * func0(char *text)

{
  int iVar1;
  ushort **ppuVar2;
  int j;
  int i;
  char *text_local;
  
  i = 0;
  j = 0;
  do {
    if (text[i] == '\0') {
      func0::buffer[j] = '\0';
      return func0::buffer;
    }
    ppuVar2 = __ctype_b_loc();
    if (((*ppuVar2)[(int)text[i]] & 0x100) == 0) {
      func0::buffer[j] = text[i];
    }
    else {
      if (i != 0) {
        ppuVar2 = __ctype_b_loc();
        if (((*ppuVar2)[(int)text[i + -1]] & 0x200) == 0) {
          ppuVar2 = __ctype_b_loc();
          if (((*ppuVar2)[(int)text[i + -1]] & 0x800) == 0) goto LAB_001012c7;
        }
        func0::buffer[j] = '_';
        j = j + 1;
      }
LAB_001012c7:
      iVar1 = tolower((int)text[i]);
      func0::buffer[j] = (char)iVar1;
    }
    j = j + 1;
    i = i + 1;
  } while( true );
}