int parse_width(char *str, int *len_p)
{
  int i = 0; int val = 0;
  for (i = 0; str[i] != '\0' && str[i] >= '0' && str[i] <= '9'; i++)
    val = (val * 10) + (str[i] - '0');
  *len_p = i;
  return val;
}