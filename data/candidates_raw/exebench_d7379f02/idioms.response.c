void int2str(unsigned short i, char *str)
{
  unsigned short j = i;
  char tmp[16];
  unsigned short k = 0;
  if (i == 0) {
    str[0] = '0';
    str[1] = '\0';
  }
  else {
    while (j > 0) {
      tmp[k++] = (char)(j % 10 + '0');
      j /= 10;
    }
    unsigned short len = k;
    while (k > 0) {
      str[len - k] = tmp[k - 1];
      k--;
    }
    str[len] = '\0';
  }
}