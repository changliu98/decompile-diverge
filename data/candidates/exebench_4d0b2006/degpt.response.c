void squeeze(char *s1,char *s2)

{
  bool bVar1;
  int contains;
  int k;
  int j;
  int i;
  char *s2_local;
  char *s1_local;
  
  k = 0;
  for (i = 0; s1[i] != '\0'; i = i + 1) {
    bVar1 = false;
    for (j = 0; s2[j] != '\0'; j = j + 1) {
      if (s1[i] == s2[j]) {
        bVar1 = true;
      }
    }
    if (!bVar1) {
      s1[k] = s1[i];
      k = k + 1;
    }
  }
  s1[k] = '\0';
  return;
}