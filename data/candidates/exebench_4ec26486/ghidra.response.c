void squeeze_all(char *s,char *b)

{
  bool bVar1;
  int badchar;
  int k;
  int j;
  int i;
  char *b_local;
  char *s_local;
  
  k = 0;
  for (i = 0; s[i] != '\0'; i = i + 1) {
    bVar1 = false;
    for (j = 0; b[j] != '\0'; j = j + 1) {
      if (s[i] == b[j]) {
        bVar1 = true;
      }
    }
    if (!bVar1) {
      s[k] = s[i];
      k = k + 1;
    }
  }
  s[k] = '\0';
  return;
}