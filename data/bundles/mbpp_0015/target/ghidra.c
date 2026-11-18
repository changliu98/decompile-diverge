char ** func0(char *text,int *count)

{
  int iVar1;
  int iVar2;
  size_t sVar3;
  ushort **ppuVar4;
  char *__dest;
  bool bVar5;
  char *substr;
  int substr_len;
  int end;
  int start;
  int i;
  int len;
  char **result;
  int *count_local;
  char *text_local;
  
  result = (char **)0x0;
  *count = 0;
  sVar3 = strlen(text);
  i = 0;
  while (iVar1 = i, i < (int)sVar3) {
    ppuVar4 = __ctype_b_loc();
    if (((*ppuVar4)[(int)(uint)(byte)text[i]] & 0x200) == 0) {
      i = i + 1;
    }
    else {
      do {
        i = i + 1;
        bVar5 = false;
        if (i < (int)sVar3) {
          ppuVar4 = __ctype_b_loc();
          bVar5 = ((*ppuVar4)[(int)(uint)(byte)text[i]] & 0x200) == 0;
        }
      } while (bVar5);
      iVar2 = i - iVar1;
      __dest = malloc((long)(iVar2 + 1));
      strncpy(__dest,text + iVar1,(long)iVar2);
      __dest[iVar2] = '\0';
      result = realloc(result,(long)(*count + 1) << 3);
      result[*count] = __dest;
      *count = *count + 1;
    }
  }
  return result;
}