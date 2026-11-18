void SwitchToChar(char *str, unsigned char data)
{
  str[0] = (data / 16 < 10 ? '0' : 'A' - 10) + (data / 16);
  str[1] = (data % 16 < 10 ? '0' : 'A' - 10) + (data % 16);
}