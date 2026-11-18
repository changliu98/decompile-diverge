int func0(char *S)

{
  bool bVar1;
  bool bVar2;
  ushort **ppuVar3;
  int i;
  int sum;
  int isi;
  int isstart;
  char *S_local;
  
  bVar2 = true;
  bVar1 = false;
  sum = 0;
  for (i = 0; S[i] != '\0'; i = i + 1) {
    ppuVar3 = __ctype_b_loc();
    if ((((*ppuVar3)[(int)S[i]] & 0x2000) != 0) && (bVar1)) {
      bVar1 = false;
      sum = sum + 1;
    }
    if ((S[i] == 'I') && (bVar2)) {
      bVar1 = true;
    }
    else {
      ppuVar3 = __ctype_b_loc();
      if (((*ppuVar3)[(int)S[i]] & 0x2000) == 0) {
        bVar1 = false;
      }
    }
    ppuVar3 = __ctype_b_loc();
    if (((*ppuVar3)[(int)S[i]] & 0x2000) == 0) {
      bVar2 = false;
    }
    if (((S[i] == '.') || (S[i] == '?')) || (S[i] == '!')) {
      bVar2 = true;
    }
  }
  return sum;
}