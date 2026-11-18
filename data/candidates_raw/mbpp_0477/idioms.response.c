void tolowerstr(char *str, char *out)
{
  int i;
  for (i = 0; str[i]; i++)
    out[i] = tolower(str[i]);
  out[i] = '\0';
}