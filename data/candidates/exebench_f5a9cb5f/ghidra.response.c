void reverse(char *s)

{
  char cVar1;
  int j;
  int i;
  int c;
  char *s_local;
  
  for (j = 0; s[j] != '\0'; j = j + 1) {
  }
  for (i = 0; j = j + -1, i < j; i = i + 1) {
    cVar1 = s[i];
    s[i] = s[j];
    s[j] = cVar1;
  }
  return;
}