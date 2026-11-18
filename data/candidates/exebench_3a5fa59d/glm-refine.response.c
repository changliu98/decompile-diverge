char *__cdecl strichr(char *str, int c)
{
  char *end;

  if (str)
  {
    // Find the null terminator
    end = str;
    while (*end)
      end++;

    // Shift the string to the right by 1 byte (including the null terminator)
    while (end >= str)
    {
      end[1] = *end;
      end--;
    }

    // Insert the new character at the beginning
    *str = c;
  }

  return str;
}