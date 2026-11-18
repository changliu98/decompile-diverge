void reverse(char *s)

{
  char cVar1;
  int len;
  int i;
  char c;
  char *s_local;
  
  i = 0;
  len = 0;
  while (s[i] != '\0') {
    len = len + 1;
    i = i + 1;
  }
  for (i = 0; i < len / 2; i = i + 1) {
    cVar1 = s[i];
    s[i] = s[(len + -1) - i];
    s[(len + -1) - i] = cVar1;
  }
  return;
}