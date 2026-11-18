int descape(int *input_ptr, int *output_ptr)
{
  // Check if the current character is a backslash (escape character)
  if (*input_ptr == 0x5c) {
    // Process the next character to determine the escaped sequence
    switch(input_ptr[1]) {
    // Escape sequence for double quote: \"
    case 0x22:
      output_ptr[1] = 0x22;
      return 1;
    // Escape sequence for single quote: \'
    case 0x27:
      output_ptr[1] = 0x27;
      return 1;
    // Escape sequence for question mark: \?
    case 0x3f:
      output_ptr[1] = 0x3f;
      return 1;
    // Escape sequence for alert/bell: \a
    case 0x61:
      output_ptr[1] = 7;
      return 1;
    // Escape sequence for backspace: \b
    case 0x62:
      output_ptr[1] = 8;
      return 1;
    // Escape sequence for form feed: \f
    case 0x66:
      output_ptr[1] = 0xc;
      return 1;
    // Escape sequence for newline: \n
    case 0x6e:
      output_ptr[1] = 10;
      return 1;
    // Escape sequence for carriage return: \r
    case 0x72:
      output_ptr[1] = 0xd;
      return 1;
    // Escape sequence for horizontal tab: \t
    case 0x74:
      output_ptr[1] = 9;
      return 1;
    // Escape sequence for vertical tab: \v
    case 0x76:
      output_ptr[1] = 0xb;
      return 1;
    }
  }
  // If not an escape sequence, copy the current and next characters as-is
  *output_ptr = *input_ptr;
  output_ptr[1] = input_ptr[1];
  return 0;
}