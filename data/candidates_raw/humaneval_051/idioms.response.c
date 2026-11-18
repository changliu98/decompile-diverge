void remove_vowels(char *text)
{
  char *in = text;
  char *out = text;
  while (*in != '\0') {
    if (strchr("AEIOUaeiou", *in) == ((void *)0))
      *out++ = *in;
    in++;
  }
  *out = '\0';
}