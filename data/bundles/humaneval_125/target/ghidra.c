char ** func0(char *txt,int *returnSize)

{
  int iVar1;
  size_t sVar2;
  char *pcVar3;
  ushort **ppuVar4;
  char current [101];
  char **out;
  int len;
  int count;
  int num;
  int j;
  int i;
  int *returnSize_local;
  char *txt_local;
  
  j = 0;
  num = 0;
  count = 0;
  sVar2 = strlen(txt);
  iVar1 = (int)sVar2;
  memset(current,0,0x65);
  pcVar3 = strchr(txt,0x20);
  if ((pcVar3 == (char *)0x0) && (pcVar3 = strchr(txt,0x2c), pcVar3 == (char *)0x0)) {
    for (i = 0; i < iVar1; i = i + 1) {
      ppuVar4 = __ctype_b_loc();
      if ((((*ppuVar4)[(int)txt[i]] & 0x200) != 0) && ((txt[i] + -0x61) % 2 == 1)) {
        num = num + 1;
      }
    }
    out = malloc(8);
    pcVar3 = malloc(0xc);
    *out = pcVar3;
    sprintf(*out,"%d",(ulong)(uint)num);
    count = 1;
  }
  else {
    out = malloc((long)(iVar1 + 1) << 3);
    for (i = 0; i <= iVar1; i = i + 1) {
      if (((txt[i] == ' ') || (txt[i] == ',')) || (txt[i] == '\0')) {
        if (0 < j) {
          current[j] = '\0';
          pcVar3 = strdup(current);
          out[count] = pcVar3;
          count = count + 1;
          j = 0;
        }
      }
      else {
        current[j] = txt[i];
        j = j + 1;
      }
    }
  }
  *returnSize = count;
  return out;
}