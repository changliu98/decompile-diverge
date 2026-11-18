char *int2roman(int num)
{
  int i = num;
  int val[] = { 1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1 };
  char *syb[] = { "M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I" };
  char *ret = "";
  int j = 0;
  while (i > 0)
  {
    for (; i >= val[j]; i -= val[j])
    {
      strcat(ret, syb[j]);
    }
    j++;
  }
  return ret;
}