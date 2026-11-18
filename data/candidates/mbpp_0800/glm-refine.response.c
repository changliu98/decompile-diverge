void __cdecl func0(const char *text, char *result)
{
  int i = 0;
  int j = 0;

  // Iterate through the input string until the null terminator is reached
  while (text[i] != '\0')
  {
    // Check if the current character is NOT a whitespace character.
    // The original decompiled expression `((*__ctype_b_loc())[(unsigned __int8)text[i]] & 0x2000) == 0`
    // is the glibc internal bit-mask check for `isspace()`. 
    // The 0x2000 bit corresponds to the `_ISspace` flag in the C locale.
    if (!isspace((unsigned char)text[i]))
    {
      result[j++] = text[i];
    }
    i++;
  }
  
  // Null-terminate the resulting string
  result[j] = '\0';
}