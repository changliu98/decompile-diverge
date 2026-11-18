void simplify(int *numerator, int *denominator)
{
  int lowestNum = 0;
  int commonNum = -1;
  if (*numerator < *denominator && *numerator > 0)
    lowestNum = *numerator;
  else if (*denominator > 0)
    lowestNum = *denominator;
  else
    lowestNum = *numerator;
  while (lowestNum > 0)
  {
    if ( *numerator % lowestNum == 0 && *denominator % lowestNum == 0 )
    {
      commonNum = lowestNum;
      lowestNum = 0;
    }
    else
    {
      if (lowestNum > 0)
        lowestNum--;
      else
        lowestNum++;
    }
  }
  if (commonNum == -1)
    commonNum = 1;
  *numerator = *numerator / commonNum;
  *denominator = *denominator / commonNum;
  return;
}