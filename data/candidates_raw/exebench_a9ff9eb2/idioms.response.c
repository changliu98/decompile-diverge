void tohex(int value, char *str)
{
  int i;
  char *hex = "0123456789ABCDEF";
  for (i = 0; i < 8; i++) {
    str[9 - i] = hex[value & 0xf];
    value >>= 4;
  }
  str[0] = '0';
  str[1] = 'x';
  str[10] = '\n';
  str[11] = '\0';
}