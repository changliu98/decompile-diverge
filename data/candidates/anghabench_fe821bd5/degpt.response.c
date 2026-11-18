int ok_cp1251(char *input_string,int string_length)
{
  int current_index;
  current_index = 1;
  while( true ) {
    // Check if the current index has reached or exceeded the string length
    if (string_length <= current_index) {
      return 1;
    }
    // Check if the current character matches the byte value 0x98 (which is -0x68 in signed char)
    // This appears to be checking for a specific control character or delimiter in CP1251 encoding
    if (input_string[current_index] == -0x68) break;
    current_index = current_index + 1;
  }
  return 0;
}