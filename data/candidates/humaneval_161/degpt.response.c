char * func0(char *s)

{
  char cVar1;
  int iVar2;
  int iVar3;
  size_t sVar4;
  ushort **ppuVar5;
  char temp;
  int i_1;
  int i;
  int length;
  int nletter;
  char *s_local;
  
  nletter = 0;
  sVar4 = strlen(s);
  iVar2 = (int)sVar4;
  for (i = 0; i < iVar2; i = i + 1) {
    ppuVar5 = __ctype_b_loc();
    if (((*ppuVar5)[(int)(uint)(byte)s[i]] & 0x400) == 0) {
      nletter = nletter + 1;
    }
    else {
      ppuVar5 = __ctype_b_loc();
      if (((*ppuVar5)[(int)(uint)(byte)s[i]] & 0x100) == 0) {
        ppuVar5 = __ctype_b_loc();
        if (((*ppuVar5)[(int)(uint)(byte)s[i]] & 0x200) != 0) {
          iVar3 = toupper((uint)(byte)s[i]);
          s[i] = (char)iVar3;
        }
      }
      else {
        iVar3 = tolower((uint)(byte)s[i]);
        s[i] = (char)iVar3;
      }
    }
  }
  if (nletter == iVar2) {
    for (i_1 = 0; i_1 < iVar2 / 2; i_1 = i_1 + 1) {
      cVar1 = s[i_1];
      s[i_1] = s[(iVar2 - i_1) + -1];
      s[(iVar2 - i_1) + -1] = cVar1;
    }
  }
  return s;
}