int func0(int a, int b, int c)
{
  int median;

  if (a > b)
    {
      if (a > c)
 median = a;
      else
 median = c;
    }
  else
    {
      if (b > c)
 median = b;
      else
 median = c;
    }

  if (median > b)
    {
      if (median > c)
 median = c;
      else
 median = b;
    }
  else
    {
      if (median > a)
 median = a;
      else
 median = c;
    }

  return median;
}