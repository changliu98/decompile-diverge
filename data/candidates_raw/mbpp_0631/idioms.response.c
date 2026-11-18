void to_underscore(char *name)
{
  int i;
  for (i = 0; name[i]; i++)
    if (name[i] == ' ')
      name[i] = '_';
}