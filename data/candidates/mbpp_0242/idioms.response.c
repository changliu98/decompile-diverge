int func0(char *str)
{
  int i = 0;
  for (i = 0; *str != '\0'; str++)
    i++;
  return i;
}