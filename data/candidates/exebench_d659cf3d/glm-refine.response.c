int __cdecl tt_unesc(char *str, char esc)
{
  int escape_count; // Tracks the number of escaped characters processed
  char *dst;        // Destination pointer for the unescaped string

  escape_count = 0;
  
  // Find the first occurrence of the escape character.
  // If the string ends before finding it, return 0 (no escapes processed).
  while (*str != esc)
  {
    if (!*str)
      return 0;
    ++str;
  }
  
  // Start writing the unescaped string from the first occurrence of the escape character.
  dst = str;
  
  // Iterate through the rest of the string, copying characters and skipping escape characters.
  while (*str)
  {
    if (*str == esc)
    {
      ++str;          // Skip the escape character
      ++escape_count; // Increment the count of unescaped characters
    }
    *dst++ = *str++;  // Copy the current character and advance both pointers
  }
  
  // Note: The original string is modified in-place. The caller should null-terminate 
  // the string at `dst` if necessary, although this function relies on the existing 
  // null terminator being copied over.
  return escape_count;
}