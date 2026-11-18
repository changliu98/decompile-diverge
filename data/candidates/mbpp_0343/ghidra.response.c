void func0(char *s,int *letters,int *digits)

{
  ushort **ppuVar1;
  int d;
  int l;
  int *digits_local;
  int *letters_local;
  char *s_local;
  
  l = 0;
  d = 0;
  for (s_local = s; *s_local != '\0'; s_local = s_local + 1) {
    ppuVar1 = __ctype_b_loc();
    if (((*ppuVar1)[(int)(uint)(byte)*s_local] & 0x800) == 0) {
      ppuVar1 = __ctype_b_loc();
      if (((*ppuVar1)[(int)(uint)(byte)*s_local] & 0x400) != 0) {
        l = l + 1;
      }
    }
    else {
      d = d + 1;
    }
  }
  *letters = l;
  *digits = d;
  return;
}