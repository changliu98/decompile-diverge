int __cdecl itoa(char *str, const int num)
{
  if (num == 0)
  {
    str[0] = '0';
    str[1] = '\0';
    return 2;
  }

  int abs_num = num;
  if (num < 0)
    abs_num = -num;

  // Calculate the number of digits in the absolute value
  int length = 0;
  int divisor = 1;
  while (abs_num % divisor != abs_num)
  {
    ++length;
    divisor *= 10;
  }

  // Reserve an extra character for the negative sign
  if (num < 0)
    ++length;

  // Extract digits from most significant to least significant
  divisor = 1;
  for (int i = length - 1; i >= 0; --i)
  {
    str[i] = (abs_num / divisor) % 10 + '0';
    divisor *= 10;
  }

  // Add the negative sign if necessary
  if (num < 0)
    str[0] = '-';

  str[length] = '\0';
  return length;
}