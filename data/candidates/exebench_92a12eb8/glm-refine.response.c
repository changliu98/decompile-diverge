void __cdecl itoa(int value, char *str)
{
  char *start = str;
  unsigned int uvalue;

  // Handle negative integers
  if (value >= 0)
  {
    uvalue = value;
  }
  else
  {
    uvalue = -value;
    *str = '-';
    start = str + 1;
  }

  // Convert the integer to a reversed string
  char *end = start;
  do
  {
    *end = (uvalue % 10) + '0';
    uvalue /= 10;
    ++end;
  } while (uvalue);
  *end = '\0';

  // Reverse the string in-place to correct the order
  --end;
  while (start < end)
  {
    char temp = *start;
    *start = *end;
    *end = temp;
    ++start;
    --end;
  }
}