char * func0(char *s,char c)

{
  size_t sVar1;
  char *pcVar2;
  int i_1;
  int j;
  char *result;
  int i;
  int counts;
  char c_local;
  char *s_local;
  
  counts = 0;
  for (i = 0; s[i] != '\0'; i = i + 1) {
    if (s[i] == c) {
      counts = counts + 1;
    }
  }
  sVar1 = strlen(s);
  pcVar2 = malloc((sVar1 - (long)counts) + 1);
  j = 0;
  for (i_1 = 0; s[i_1] != '\0'; i_1 = i_1 + 1) {
    if (s[i_1] != c) {
      pcVar2[j] = s[i_1];
      j = j + 1;
    }
  }
  pcVar2[j] = '\0';
  return pcVar2;
}