int max(char *str)
{
  int i; int j;
  int max = 0;
  char buf[256];
  for (i = j = 0; str[i]; i++) {
    if (str[i] >= '0' && str[i] <= '9')
      buf[j++] = str[i];
    else {
      if (j) {
        buf[j] = '\0';
        max = atoi(buf);
        if (max < i)
          max = i;
        j = 0;
      }
    }
  }
  if (j) {
    buf[j] = '\0';
    max = atoi(buf);
    if (max < i)
      max = i;
  }
  return (max);
}