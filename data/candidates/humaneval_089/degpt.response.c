void func0(char *s,char *out)

{
  int w;
  int i;
  char *out_local;
  char *s_local;
  
  for (i = 0; s[i] != '\0'; i = i + 1) {
    out[i] = (char)((s[i] + -0x5d) % 0x1a) + 'a';
  }
  out[i] = '\0';
  return;
}