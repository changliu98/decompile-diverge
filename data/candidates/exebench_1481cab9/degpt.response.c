void snake_upcase_char(char *character_ptr)
{
  // Check if the character is not a lowercase letter (a-z)
  if ((*character_ptr < 'a') || ('z' < *character_ptr)) {
    // If the character is a hyphen, convert it to an underscore
    if (*character_ptr == '-') {
      *character_ptr = '_';
    }
  }
  else {
    // Convert the lowercase letter to uppercase by clearing the 6th bit
    *character_ptr = *character_ptr & 0xdf;
  }
}