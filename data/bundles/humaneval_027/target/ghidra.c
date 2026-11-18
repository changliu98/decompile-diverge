void func0(char *str,char *out)

{
  size_t sVar1;
  char w;
  int i;
  int length;
  char *out_local;
  char *str_local;
  
  sVar1 = strlen(str);
  for (i = 0; i < (int)sVar1; i = i + 1) {
    w = str[i];
    if ((w < 'a') || ('z' < w)) {
      if (('@' < w) && (w < '[')) {
        w = w + ' ';
      }
    }
    else {
      w = w + -0x20;
    }
    out[i] = w;
  }
  out[(int)sVar1] = '\0';
  return;
}