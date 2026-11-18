void func0(char *string,int *alphabets,int *digits,int *special)

{
  ushort **ppuVar1;
  int i;
  int *special_local;
  int *digits_local;
  int *alphabets_local;
  char *string_local;
  
  *special = 0;
  *digits = 0;
  *alphabets = 0;
  for (i = 0; string[i] != '\0'; i = i + 1) {
    ppuVar1 = __ctype_b_loc();
    if (((*ppuVar1)[(int)string[i]] & 0x400) == 0) {
      ppuVar1 = __ctype_b_loc();
      if (((*ppuVar1)[(int)string[i]] & 0x800) == 0) {
        *special = *special + 1;
      }
      else {
        *digits = *digits + 1;
      }
    }
    else {
      *alphabets = *alphabets + 1;
    }
  }
  return;
}