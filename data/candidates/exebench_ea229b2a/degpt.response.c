char * convert_set_sign(char *str,int *sign_value)
{
  // Initialize the sign to positive
  *sign_value = 1;
  // Check if the string pointer is not null
  if (str != (char *)0x0) {
    // If the first character is '+', set sign to positive and skip the '+' character
    if (*str == '+') {
      *sign_value = 1;
      return str + 1;
    }
    // If the first character is '-', set sign to negative and skip the '-' character
    else if (*str == '-') {
      *sign_value = -1;
      return str + 1;
    }
  }
  // Return the original string if no sign character was found or if the string was null
  return str;
}