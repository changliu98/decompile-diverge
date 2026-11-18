char *__cdecl func0(char *s, int offset)
{
  int i;
  char *rotated_str;
  int len;

  len = strlen(s);
  
  // Allocate memory for the new string, including space for the null terminator.
  rotated_str = (char *)malloc(len + 1);
  
  // Perform a left rotation by iterating through the new string and pulling
  // characters from the original string starting at 'offset'.
  for ( i = 0; i < len; ++i )
  {
    // The modulo operator ensures the index wraps around correctly.
    // Note: In C, if (offset + i) is negative, the result of % is implementation-defined,
    // but typically wraps safely on modern compilers (e.g., GCC/Clang).
    rotated_str[i] = s[(offset + i) % len];
  }
  
  // Null-terminate the newly created string.
  rotated_str[len] = '\0';
  
  return rotated_str;
}