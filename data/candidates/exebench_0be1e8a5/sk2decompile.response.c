void short_to_string(char *str, unsigned short num) {
  unsigned short temp;
  unsigned char digit;
  temp = num / 10000;
  str[0] = temp + '0';
  digit = (num - temp * 10000) / 1000;
  temp = temp * 1000 + digit;
  str[1] = digit + '0';
  digit = (num - temp) / 100;
  temp = temp * 10 + digit;
  str[2] = digit + '0';
  digit = (num - temp) / 10;
  temp = temp * 10 + digit;
  str[3] = digit + '0';
  digit = num - temp;
  str[4] = digit + '0';
  str[5] = '\0';
}