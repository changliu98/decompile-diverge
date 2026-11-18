void to_roman(int number, char *result)
{
  char *romans[] = { "M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I" };
  int values[] = { 1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1 };
  int i = 0;
  result[0] = '\0';
  while (number > 0)
  {
    while (number >= values[i])
    {
      strcat(result, romans[i]);
      number -= values[i];
    }
    if (number > 0)
      i++;
  }
}