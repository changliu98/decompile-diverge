int __cdecl sdsull2str(char *str, unsigned __int64 value)
{
  char *end_ptr;
  char *left_ptr;
  char temp;
  int length;
  char *curr_ptr;

  // 1. Convert the number to a string in reverse order
  curr_ptr = str;
  do
  {
    *curr_ptr++ = (char)(value % 10) + '0';
    value /= 10;
  }
  while (value);

  // 2. Calculate the length of the resulting string and null-terminate it
  length = (int)(curr_ptr - str);
  *curr_ptr = '\0';

  // 3. Reverse the string in-place to correct the digit order
  left_ptr = str;
  for (end_ptr = curr_ptr - 1; left_ptr < end_ptr; --end_ptr)
  {
    temp = *left_ptr;
    *left_ptr = *end_ptr;
    *end_ptr = temp;
    ++left_ptr;
  }

  return length;
}