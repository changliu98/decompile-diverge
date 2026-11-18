void int_to_str(uint16_t i, char *str)
{
  uint8_t j;
  for (j = 10; j > 0; j--) {
    str[j-1] = (i % 10) + '0';
    i /= 10;
  }
  str[10] = '\0';
}