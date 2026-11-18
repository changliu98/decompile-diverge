char *__cdecl skip(char *s, char c)
{
  // Skip all occurrences of character 'c' until a different non-null character is found
  while (*s == c)
    ++s;

  // If we didn't reach the end of the string, null-terminate the current word
  // and return a pointer to the next character.
  if (*s)
  {
    *s = 0;
    ++s;
  }

  return s;
}