char *intToString(char *str, unsigned int val)
{
  int i;
  str[9] = '\0';
  for (i = 8; i >= 0; i--)
  {
    str[i] = (val % 10) + '0';
    val /= 10;
    if (val == 0)
      break;
  }
  return str + i;
}