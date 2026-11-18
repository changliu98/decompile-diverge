void itoa(unsigned long i, char *s)
{
  unsigned long shifter = i;
  do
  {
    ++s;
    shifter = shifter / 10;
  }
  while (shifter);
  *s = '\0';
  do
  {
    --s;
    *(s - 1) = (char)(i % 10 + '0');
    i = i / 10;
  }
  while (i);
}