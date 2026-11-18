char ** func0(char *text,int *count)

{
  int iVar1;
  int iVar2;
  size_t sVar3;
  char **ppcVar4;
  ushort **ppuVar5;
  char *pcVar6;
  int word_length;
  int i;
  int word_start;
  char **result;
  int n;
  int *count_local;
  char *text_local;
  
  sVar3 = strlen(text);
  iVar1 = (int)sVar3;
  ppcVar4 = malloc((long)iVar1 << 3);
  *count = 0;
  word_start = 0;
  i = 1;
  do {
    if (iVar1 < i) {
      return ppcVar4;
    }
    if (i == iVar1) {
LAB_001012b4:
      iVar2 = i - word_start;
      pcVar6 = malloc((long)(iVar2 + 1));
      ppcVar4[*count] = pcVar6;
      strncpy(ppcVar4[*count],text + word_start,(long)iVar2);
      ppcVar4[*count][iVar2] = '\0';
      *count = *count + 1;
      word_start = i;
    }
    else {
      ppuVar5 = __ctype_b_loc();
      if (((*ppuVar5)[(int)text[i]] & 0x100) != 0) {
        ppuVar5 = __ctype_b_loc();
        if (((*ppuVar5)[(int)text[i + -1]] & 0x100) == 0) goto LAB_001012b4;
      }
    }
    i = i + 1;
  } while( true );
}