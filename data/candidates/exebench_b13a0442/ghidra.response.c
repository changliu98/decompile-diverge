void strrev(char *s)

{
  char cVar1;
  char c;
  int j;
  int i;
  char *s_local;
  
  for (i = 0; s[i] != '\0'; i = i + 1) {
  }
  for (j = 0; i = i + -1, j < i; j = j + 1) {
    cVar1 = s[i];
    s[i] = s[j];
    s[j] = cVar1;
  }
  return;
}