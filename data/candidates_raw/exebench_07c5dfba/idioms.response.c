void itoa_dec(unsigned int val, char *buf)
{
  unsigned int i;
  for (i = 0; i < 10; i++) {
    if (val == 0 && i != 0)
      buf[10 - i - 1] = ' ';
    else
      buf[10 - i - 1] = itoa_dec_dectab[val % 10];
    val /= 10;
  }
}