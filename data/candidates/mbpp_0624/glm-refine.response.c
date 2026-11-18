s a global buffer

char *__cdecl func0(const char *str)
{
  int i;

  // Iterate through the string until the null terminator is reached
  for ( i = 0; str[i]; ++i )
  {
    // Convert each character to uppercase and store it in the global buffer
    // Note: (unsigned __int8) prevents sign-extension issues with chars > 127
    g_func0_buffer[i] = toupper((unsigned char)str[i]);
  }
  
  // Null-terminate the resulting string
  g_func0_buffer[i] = '\0';
  
  return g_func0_buffer;
}