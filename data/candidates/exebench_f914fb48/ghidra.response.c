void strupper(char *s)

{
  int i;
  char *s_local;
  
  for (i = 0; s[i] != '\0'; i = i + 1) {
    if (('`' < s[i]) && (s[i] < '{')) {
      s[i] = s[i] + -0x20;
    }
  }
  return;
}