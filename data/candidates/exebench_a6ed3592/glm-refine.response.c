void __cdecl intToString(int n, char *str)
{
  if (n != 0)
  {
    // Calculate the number of digits in the integer
    int length = 0;
    for (int temp = n; temp != 0; temp /= 10)
      ++length;

    // Null-terminate the string
    str[length] = '\0';

    // Fill the string buffer with digits from right to left
    int index = length - 1;
    int temp_val = n;
    while (index >= 0)
    {
      str[index--] = (temp_val % 10) + '0';
      temp_val /= 10;
    }
  }
  else
  {
    // Handle the zero case
    str[0] = '0';
    str[1] = '\0';
  }
}