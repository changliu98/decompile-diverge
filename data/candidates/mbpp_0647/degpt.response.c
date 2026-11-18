char ** func0(char *text,int *count)

{
  int iVar1;
  size_t sVar2;
  char **ppcVar3;
  ushort **ppuVar4;
  char *pcVar5;
  int word_length;
  int i;
  int start;
  int current_word;
  char **result;
  int len;
  int *count_local;
  char *text_local;
  
  sVar2 = strlen(text);
  ppcVar3 = malloc((long)(int)sVar2 << 3);
  if (ppcVar3 == (char **)0x0) {
    perror("Failed to allocate memory");
                    /* WARNING: Subroutine does not return */
    exit(1);
  }
  current_word = 0;
  start = 0;
  i = 1;
  do {
    if ((int)sVar2 < i) {
      *count = current_word;
      return ppcVar3;
    }
    ppuVar4 = __ctype_b_loc();
    if ((((*ppuVar4)[(int)text[i]] & 0x100) != 0) || (text[i] == '\0')) {
      iVar1 = i - start;
      pcVar5 = malloc((long)(iVar1 + 1));
      ppcVar3[current_word] = pcVar5;
      if (ppcVar3[current_word] == (char *)0x0) {
        perror("Failed to allocate memory");
                    /* WARNING: Subroutine does not return */
        exit(1);
      }
      memcpy(ppcVar3[current_word],text + start,(long)iVar1);
      ppcVar3[current_word][iVar1] = '\0';
      start = i;
      current_word = current_word + 1;
    }
    i = i + 1;
  } while( true );
}