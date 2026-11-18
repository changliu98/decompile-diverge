void Perl_my_setenv(char *name, char *value)
{
  char *envstr;
  int nlen = strlen(name);
  int vlen = strlen(value);
  if (value == ((void *)0))
    value = "";
  vlen = strlen(value);
  envstr = (char *)malloc(nlen + vlen + 2);
  strncpy(envstr, name, nlen);
  envstr[nlen] = '=';
  strncpy(&envstr[nlen + 1], value, vlen);
  envstr[nlen + vlen + 1] = '\0';
  Perl_my_setenv(envstr);
  free(envstr);
}