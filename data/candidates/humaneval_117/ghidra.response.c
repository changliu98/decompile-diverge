char ** func0(char *s,int n,int *returnSize)

{
  size_t sVar1;
  char *__s;
  ushort **ppuVar2;
  size_t sVar3;
  char *pcVar4;
  int i;
  char *current;
  size_t length;
  int begin;
  int word_count;
  int numc;
  char **out;
  char *vowels;
  int *returnSize_local;
  int n_local;
  char *s_local;
  
  out = (char **)0x0;
  numc = 0;
  word_count = 0;
  begin = 0;
  sVar1 = strlen(s);
  __s = malloc(sVar1 + 1);
  for (i = 0; (ulong)(long)i <= sVar1; i = i + 1) {
    ppuVar2 = __ctype_b_loc();
    if ((((*ppuVar2)[(int)s[i]] & 0x2000) == 0) && (s[i] != '\0')) {
      __s[i - begin] = s[i];
      pcVar4 = strchr("aeiouAEIOU",(int)s[i]);
      if ((pcVar4 == (char *)0x0) &&
         (ppuVar2 = __ctype_b_loc(), ((*ppuVar2)[(int)(uint)(byte)s[i]] & 0x400) != 0)) {
        numc = numc + 1;
      }
    }
    else {
      if (numc == n) {
        __s[i - begin] = '\0';
        out = realloc(out,(long)(word_count + 1) << 3);
        sVar3 = strlen(__s);
        pcVar4 = malloc(sVar3 + 1);
        out[word_count] = pcVar4;
        strcpy(out[word_count],__s);
        word_count = word_count + 1;
      }
      begin = i + 1;
      numc = 0;
    }
  }
  free(__s);
  *returnSize = word_count;
  return out;
}