void squeeze_alt(char *str1,char *str2)

{
  bool bVar1;
  int found;
  int k;
  int j;
  int i;
  char *str2_local;
  char *str1_local;
  
  j = 0;
  for (i = 0; str1[i] != '\0'; i = i + 1) {
    bVar1 = false;
    k = 0;
    while (str2[k] != '\0' && !bVar1) {
      if (str1[i] == str2[k]) {
        bVar1 = true;
      }
      k = k + 1;
    }
    if (!bVar1) {
      str1[j] = str1[i];
      j = j + 1;
    }
  }
  str1[j] = '\0';
  return;
}