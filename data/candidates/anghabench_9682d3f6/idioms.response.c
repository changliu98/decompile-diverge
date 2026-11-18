void bn_reverse(char *str, int len)
{
  int i = 0;
  int j = len - 1;
  char tmp;
  for (i = 0, j = len - 1; i < j; i++, j--) {
    tmp = str[i];
    str[i] = str[j];
    str[j] = tmp;
  }
}