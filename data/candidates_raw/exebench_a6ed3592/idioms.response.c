void int2str(int i, char *str)
{
  int j; int k;
  if (i == 0) {
    str[0] = '0';
    str[1] = '\0';
  }
  else {
    for (j = k = 0; k = k / 10; j++)
      ;
    str[j] = '\0';
    for (j--, k = i; j >= 0; j--) {
      str[j] = (char)(k % 10 + '0');
      k = k / 10;
    }
  }
}