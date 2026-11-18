void SwitchToChar(char *str, unsigned char num) {
  unsigned char high, low;
  high = num / 16;
  low = num % 16;
  if (high >= 10)
    str[0] = high + 55;
  else
    str[0] = high + 48;
  if (low >= 10)
    str[1] = low + 55;
  else
    str[1] = low + 48;
}