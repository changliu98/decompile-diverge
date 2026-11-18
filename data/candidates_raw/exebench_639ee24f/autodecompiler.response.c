int edflib_sprint_int_number_nonlocalized(char *str, int sz, int q)
{
  char *p, tmp, *s;

  int i=0, j;

  if(sz<1)
  {
    j = i;
    return(j);
  }

  if(q < 0)
  {
    *(str++) = '-';
    sz--;
    i++;
    q = -q;
  }

  if(sz<1)
  {
    j = i;
    return(j);
  }

  s = str;

  do
  {
    tmp = (char)('0' + (q % 10));

    *(str++) = tmp;
    i++;

    sz--;

    if(sz<1)
    {
      j = i;
      return(j);
    }

    q /= 10;
  } while(q > 0);

  if(sz>0)
  {
    *(str++) = 0;
  }

  str--;

  for(; s < str; s++)
  {
    tmp = *s;
    *s = *str;
    *str = tmp;

    s++;
    str--;
  }

  j = i;

  return(j);
}