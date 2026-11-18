int __cdecl add_char_to_string(char *const string, char c, const int size)
{
  int current_length;

  // Sanity check for null pointer
  if ( !string )
    return 0;

  // Calculate the current length of the string by finding the null terminator
  for ( current_length = 0; string[current_length]; ++current_length )
    ;

  // Check if there is enough space to append the character and a new null terminator
  // (size - 1) ensures we don't overflow the buffer
  if ( current_length >= size - 1 )
    return 0;

  // Append the character and update the null terminator
  string[current_length] = c;
  string[current_length + 1] = '\0';
  
  return 1;
}