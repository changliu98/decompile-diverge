char *trim(char *str, char *trim_chars)
{
  char *endstr;
  int trim;
  if (!str)
    return ((void *)0);
  endstr = str + strlen(str) - 1;
  while (endstr >= str) {
    trim = 0;
    if (index(trim_chars, *endstr))
      trim = 1;
    if (!trim)
      break;
    *endstr = '\0';
    endstr--;
  }
  return str;
}