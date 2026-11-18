char * func0(char *text)

{
  int iVar1;
  size_t sVar2;
  char *pcVar3;
  ushort **ppuVar4;
  int j;
  int i;
  char *result;
  size_t new_length;
  size_t length;
  char *text_local;
  
  sVar2 = strlen(text);
  pcVar3 = malloc(sVar2 << 1);
  j = 0;
  for (i = 0; (ulong)(long)i < sVar2; i = i + 1) {
    if (((i < 1) || (ppuVar4 = __ctype_b_loc(), ((*ppuVar4)[(int)text[i]] & 0x100) == 0)) ||
       ((ppuVar4 = __ctype_b_loc(), ((*ppuVar4)[(int)text[i + -1]] & 0x200) == 0 &&
        (ppuVar4 = __ctype_b_loc(), ((*ppuVar4)[(int)text[i + -1]] & 0x800) == 0)))) {
      if ((((i < 1) || (ppuVar4 = __ctype_b_loc(), ((*ppuVar4)[(int)text[i]] & 0x100) == 0)) ||
          (ppuVar4 = __ctype_b_loc(), ((*ppuVar4)[(int)text[i + -1]] & 0x100) == 0)) ||
         (ppuVar4 = __ctype_b_loc(), ((*ppuVar4)[(int)text[i + 1]] & 0x200) == 0)) {
        iVar1 = tolower((int)text[i]);
        pcVar3[j] = (char)iVar1;
        j = j + 1;
      }
      else {
        pcVar3[j] = '_';
        iVar1 = tolower((int)text[i]);
        pcVar3[j + 1] = (char)iVar1;
        j = j + 2;
      }
    }
    else {
      pcVar3[j] = '_';
      iVar1 = tolower((int)text[i]);
      pcVar3[j + 1] = (char)iVar1;
      j = j + 2;
    }
  }
  pcVar3[j] = '\0';
  return pcVar3;
}