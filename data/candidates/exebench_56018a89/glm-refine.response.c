void __cdecl util_word_to_dec(char *dst, unsigned int w)
{
  char dig_array[11];
  int i;
  int pos;
  int start;

  // Initialize the buffer with '0's and null-terminate it
  for (i = 0; i < 10; ++i)
    dig_array[i] = '0';
  dig_array[10] = '\0';

  // Convert the number to digits in reverse order (right to left)
  pos = 9;
  while (w)
  {
    dig_array[pos--] = (w % 10) + '0';
    w /= 10;
  }

  // Find the first non-'0' digit (skip leading zeros)
  // The condition `ib < 9` ensures we stop at the last digit, 
  // so a value of 0 prints as "0" instead of an empty string.
  start = 0;
  while (dig_array[start] == '0' && start < 9)
    start++;

  // Copy the resulting string to the destination
  while (dig_array[start])
  {
    *dst++ = dig_array[start++];
  }
  
  // Null-terminate the destination string
  *dst = '\0';
}