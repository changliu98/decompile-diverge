void rev(char *s)

{
  char cVar1;
  int i;
  char b;
  int l;
  char *s_local;
  
  for (l = 0; s[l] != '\0'; l = l + 1) {
  }
  for (i = 0; i < l / 2; i = i + 1) {
    cVar1 = s[i];
    s[i] = s[(l - i) + -1];
    s[(l - i) + -1] = cVar1;
  }
  return;
}