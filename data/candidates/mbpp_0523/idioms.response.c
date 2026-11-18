char *func0(char *str)
{
  int has_upper = 0;
  int has_lower = 0;
  int has_digit = 0;
  int i; int length = strlen(str);
  for (i = 0; i < length; i++)
  {
    if (((*__ctype_b_loc ())[(int) ((str[i]))] & (unsigned short) _ISupper))
      has_upper = 1;
    if (((*__ctype_b_loc ())[(int) ((str[i]))] & (unsigned short) _ISlower))
      has_lower = 1;
    if (((*__ctype_b_loc ())[(int) ((str[i]))] & (unsigned short) _ISdigit))
      has_digit = 1;
  }
  strcpy(validate_password_result, "");
  if (!has_upper)
    strcat(validate_password_result,
           "String must have 1 upper case character,");
  if (!has_lower)
    strcat(validate_password_result,
           "String must have 1 lower case character,");
  if (!has_digit)
    strcat(validate_password_result, "String must have 1 number,");
  if (length < 8)
    strcat(validate_password_result, "String length should be atleast 8,");
  if (has_upper && has_lower && has_digit && length >= 8)
    strcpy(validate_password_result, "Valid string.");
  else
  {
    int lastIdx = strlen(validate_password_result) - 1;
    if (validate_password_result[lastIdx] == ',')
      validate_password_result[lastIdx] = '\0';
  }
  return validate_password_result;
}