void split(int number, int need, int remaining, struct split *result)
{
  if (need > remaining)
  {
    result->first = remaining + number;
    result->second = 0;
  }
  else
  {
    result->first = need + number;
    result->second = remaining - need;
  }
}