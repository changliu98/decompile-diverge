void func0(char *in, char *out)
{
  int i = 0;
  for (i = 0; in[i]; i++)
    out[i] = (in[i] - 'a' + 4) % 26 + 'a';
  out[i] = '\0';
}