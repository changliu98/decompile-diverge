
int sprint_int_number_nonlocalized(char *str, int q, int minimum, int sign)
{
  int flag=0, z, i, j=0, base = 1000000000;

  if(minimum < 0)
  {
    minimum = 0;
  }

  if(minimum > 9)
  {
    flag = 1;
  }

  if(q < 0)
  {
    str[j++] = '-';

    q = -q;
  }
  else
  {
    if(sign)
    {
      str[j++] = '+';
    }
  }

  for(i=10; i; i--)
  {
    if(minimum == i)
    {
      flag = 1;
    }

    z = q / base;

    q %= base;

    if(z || flag)
    {
      str[j++] = '0' + z;

      flag = 1;
    }

    base /= 10;
  }

  if(!flag)
  {
    str[j++] = '0';
  }

  str[j] = 0;

  return(j);
}
