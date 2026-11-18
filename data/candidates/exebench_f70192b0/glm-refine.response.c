int __cdecl i_to_str(int val, char *str)
{
  char *start = str;
  int abs_val = val;

  // Handle negative numbers
  if (val < 0)
  {
    *str++ = '-';
    abs_val = -val;
  }

  char *end = str;

  // Extract digits in reverse order (least significant first)
  do
  {
    *end++ = (abs_val % 10) + '0';
    abs_val /= 10;
  } while (abs_val != 0);

  *end = '\0'; // Null-terminate the string

  // Calculate the length of the generated digit sequence
  int len = (int)(end - str);

  // Reverse the digit sequence in-place to correct the order
  for (int i = 0; i < len / 2; ++i)
  {
    char temp = str[i];
    str[i] = str[len - 1 - i];
    str[len - 1 - i] = temp;
  }

  // Return the total length of the string, including the '-' sign if present
  return (int)(end - start);
}