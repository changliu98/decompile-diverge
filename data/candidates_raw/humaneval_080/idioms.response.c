int is_valid_name(char *name)
{
  int i;
  if (strlen(name) < 3)
    return 0;
  for (i = 2; i < strlen(name); i++)
    if (name[i] == name[i - 1] || name[i] == name[i - 2])
      return 0;
  return 1;
}