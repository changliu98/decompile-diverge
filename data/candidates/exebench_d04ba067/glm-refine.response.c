int __cdecl itochar(int num, char *strb)
{
  char tmp[16];      // Temporary buffer to store digits in reverse order
  int len = 0;       // Tracks the number of digits written
  int n = num;

  // Extract digits from least significant to most significant
  do
  {
    tmp[len++] = (n % 10) + '0';
    n /= 10;
  }
  while (n);

  // Reverse the extracted digits into the output buffer
  for (int j = 0; j < len; ++j)
  {
    strb[j] = tmp[len - j - 1];
  }

  return len;
}