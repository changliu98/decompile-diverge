char *__cdecl func0(const char *str)
{
  char digits[1024];
  int d_idx = 0;
  int r_idx = 0;

  // Iterate through the input string until the null terminator
  for (int i = 0; str[i]; ++i)
  {
    // Check if the character is a digit using the standard C library check
    if (isdigit((unsigned char)str[i]))
    {
      digits[d_idx++] = str[i];
    }
    else
    {
      func0_res[r_idx++] = str[i];
    }
  }
  
  // Null-terminate both the non-digits and digits arrays
  digits[d_idx] = '\0';
  func0_res[r_idx] = '\0';
  
  // Append the extracted digits to the end of the non-digits
  strcat(func0_res, digits);
  
  return func0_res;
}