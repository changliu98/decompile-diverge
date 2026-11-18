int
stringToInt(unsigned int *val, const char *buff)
{
  *val = 0;

  while (*buff != 0) {
    if (*buff < '0' || *buff > '9')
      return -1;

    else
      *val = *val * 10 + *buff - '0';

    buff++;
  }

  return 0;
}