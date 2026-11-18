void __cdecl reverse(char *str)
{
  char *p = str;
  char *end = str;

  // Find the null terminator
  while (*end)
    ++end;

  // Point to the last character of the string
  --end;

  // Swap characters using arithmetic XOR-swap equivalent
  while (p < end)
  {
    *p -= *end;
    *end += *p;
    *p = *end - *p;

    ++p;
    --end;
  }
}