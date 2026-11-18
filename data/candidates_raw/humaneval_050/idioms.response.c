void caesar(char *text, int encode)
{
  int shift = (encode ? 5 : 21);
  unsigned long i;
  unsigned long len = strlen(text);
  for (i = 0; i < len; i++)
    text[i] = (text[i] - 'a' + shift) % 26 + 'a';
}