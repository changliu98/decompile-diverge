void itoa(unsigned int value, char* buffer)
{
  int idx = 7;
  buffer[idx] = 0;
  do {
    buffer[--idx] = '0' + (value % 10);
    value /= 10;
  } while (value != 0);
}