char *__cdecl maybeint(char *q, int *dst)
{
  char *qa = q;

  if (*q < '0' || *q > '9')
  {
    *dst = 0;
  }
  else
  {
    int num = 0;
    while (*qa >= '0' && *qa <= '9')
    {
      num = *qa - '0' + 10 * num;
      qa++;
    }
    *dst = num;
  }
  
  return qa;
}