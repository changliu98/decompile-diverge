char *func0(char *str)
{
  int i;
  for (i = 0; str[i]; i++)
    strtoupper_result[i] = toupper((unsigned char)str[i]);
  strtoupper_result[i] = '\0';
  return (strtoupper_result);
}