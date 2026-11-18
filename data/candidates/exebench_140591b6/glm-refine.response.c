void __cdecl Q_ParseNewlines(char *dest, const char *src, int destsize)
{
  char c;

  // Continue copying as long as there are characters to read 
  // and there is enough space in the destination buffer (leaving room for the null terminator).
  while (*src && destsize > 1)
  {
    // Check for the escape sequence "\n" (backslash followed by 'n')
    if (*src == '\\' && src[1] == 'n')
    {
      c = '\n';       // Convert to an actual newline character
      src += 2;       // Skip both the backslash and the 'n'
    }
    else
    {
      c = *src;       // Copy the character as-is
      src++;          // Advance to the next character
    }

    *dest++ = c;      // Write the character to the destination buffer
    destsize--;       // Decrement the remaining destination space
  }

  *dest = '\0';       // Null-terminate the destination string
}