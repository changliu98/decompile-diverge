int __cdecl func0(const char *s, int n)
{
  char first_num[10] = {0};
  char second_num[10] = {0};
  int is_second_num = 0;
  int j = 0;

  for (int i = 0; s[i]; ++i)
  {
    if (isdigit(s[i]))
    {
      // Append the digit to the currently active number string
      char *target = is_second_num ? second_num : first_num;
      target[j++] = s[i];
    }
    else if (!is_second_num && j > 0)
    {
      // Transition from the first number to the second number
      is_second_num = 1;
      j = 0;
    }
  }

  return n - atoi(first_num) - atoi(second_num);
}