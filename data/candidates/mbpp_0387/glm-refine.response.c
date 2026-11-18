const char *__cdecl func0(const char *N)
{
  size_t l = strlen(N);
  char last_char = N[l - 1];

  // Check if the last character is an even digit (0, 2, 4, 6, 8) 
  // or an even hexadecimal letter (A, C, E)
  if (last_char == '0' || last_char == '2' || last_char == '4' || 
      last_char == '6' || last_char == '8' || 
      last_char == 'A' || last_char == 'C' || last_char == 'E')
  {
    return "Even";
  }
  
  return "Odd";
}