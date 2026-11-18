void squeeze(char *s1,char *s2)

{
  bool bVar1;
  uint k;
  uint j;
  uint i;
  char *s2_local;
  char *s1_local;
  
  i = 0;
  for (j = 0; s1[j] != '\0'; j = j + 1) {
    k = 0;
    while( true ) {
      bVar1 = false;
      if (s2[k] != '\0') {
        bVar1 = s1[j] != s2[k];
      }
      if (!bVar1) break;
      k = k + 1;
    }
    if (s2[k] == '\0') {
      s1[i] = s1[j];
      i = i + 1;
    }
  }
  s1[i] = '\0';
  return;
}