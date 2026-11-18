void itoa(int value, char *str)
{
  int i = 7;
  str[i--] = '\0';
  do
    str[i--] = (value % 10) + '0';
  while (value /= 10);
}