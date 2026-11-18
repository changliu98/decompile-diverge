int __cdecl count_hex_primes(const char *str)
{
  int count = 0;
  size_t len = strlen(str);

  for (size_t i = 0; i < len; ++i)
  {
    // Checks if the character is a prime digit in hexadecimal (2, 3, 5, 7, B, D)
    if (strchr("2357BD", str[i]))
    {
      ++count;
    }
  }

  return count;
}