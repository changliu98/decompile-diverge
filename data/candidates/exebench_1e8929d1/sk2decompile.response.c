void convert2ASCII(unsigned char value, char *str) {
  unsigned char temp;
  temp = value >> 4;
  if (temp < 10)
    str[0] = temp + '0';
  else
    str[0] = temp - 10 + 'a';
  temp = value & 0x0F;
  if (temp < 10)
    str[1] = temp + '0';
  else
    str[1] = temp - 10 + 'a';
}