int __cdecl func0(const char *str)
{
  int i;
  int maxcount = 0;
  int count = 0;
  size_t len = strlen(str);

  for (i = 0; i < len; ++i)
  {
    // Increment depth on '[' and decrement on ']'
    if (str[i] == '[')
      ++count;
    if (str[i] == ']')
      --count;

    // Depth cannot be negative
    if (count < 0)
      count = 0;

    // Track the maximum depth reached
    if (count > maxcount)
      maxcount = count;

    // If depth drops 2 or more levels below the maximum depth, return early
    if (count <= maxcount - 2)
      return 1;
  }
  
  return 0;
}