char *
intToString(char *buff, unsigned int val)
{
  int i;

  buff[9] = 0;

  for (i = 8; i >= 0; i--) {
    buff[i] = (char)(val % 10 + '0');

    val /= 10;

    if (val == 0)
      break;
  }

  return buff + i;
}