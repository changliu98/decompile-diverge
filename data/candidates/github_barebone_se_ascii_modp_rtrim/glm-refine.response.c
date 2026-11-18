size_t __cdecl modp_rtrim(char *str, size_t len)
{
  char c;

  while (len > 0)
  {
    c = str[len - 1];
    
    // Check if the character is a space (' '), newline ('\n'), 
    // tab ('\t'), or carriage return ('\r')
    if (c != ' ' && c != '\n' && c != '\t' && c != '\r')
      break;
      
    // Null-terminate the trailing whitespace and decrement the length
    str[--len] = '\0';
  }
  
  return len;
}