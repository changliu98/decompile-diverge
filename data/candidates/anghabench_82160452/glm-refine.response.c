int __cdecl sdsll2str(char *s, __int64 value)
{
  unsigned __int64 abs_value;
  char *p = s;
  char *start = s;
  int length;

  // Convert the absolute value of the integer to a string (in reverse order)
  if (value >= 0)
    abs_value = value;
  else
    abs_value = -value;

  do
  {
    *p++ = (abs_value % 10) + '0';
    abs_value /= 10;
  }
  while (abs_value);

  // Append the minus sign if the original value was negative
  if (value < 0)
    *p++ = '-';

  // Null-terminate the string and calculate its length
  length = (int)(p - s);
  *p = '\0';

  // Reverse the string in-place to correct the digit order
  char *left = start;
  char *right = p - 1;
  while (left < right)
  {
    char temp = *left;
    *left = *right;
    *right = temp;
    
    left++;
    right--;
  }

  return length;
}