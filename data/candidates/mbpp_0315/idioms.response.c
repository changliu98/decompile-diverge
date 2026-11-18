char *func0(char *str)
{
  int len = strlen(str);
  int i = 0;
  int currlen = 0;
  int maxlen = 0;
  int start = -1;
  for (i = 0; i < len; i++)
  {
    if (str[i] == ' ')
    {
      if (currlen % 2 == 0 && maxlen < currlen)
      {
        maxlen = currlen;
        start = i - maxlen;
      }
      currlen = 0;
    }
    else
    {
      currlen++;
    }
  }
  if (currlen % 2 == 0 && maxlen < currlen)
  {
    maxlen = currlen;
    start = i - maxlen;
  }
  if (start == -1)
  {
    return "";
  }
  strncpy(result, &str[start], maxlen);
  result[maxlen] = '\0';
  return result;
}