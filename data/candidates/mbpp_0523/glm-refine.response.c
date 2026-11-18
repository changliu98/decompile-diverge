char *__cdecl func0(const char *str1)
{
  int length = strlen(str1);
  int has_upper = 0;
  int has_lower = 0;
  int has_digit = 0;

  // Iterate through the string to check character types
  for (int i = 0; i < length; ++i)
  {
    unsigned char c = str1[i];
    if (isupper(c))
      has_upper = 1;
    if (islower(c))
      has_lower = 1;
    if (isdigit(c))
      has_digit = 1;
  }

  func0_result[0] = '\0';

  // Append error messages if requirements are not met
  if (!has_upper)
    strcat(func0_result, "String must have 1 upper case character,");
  if (!has_lower)
    strcat(func0_result, "String must have 1 lower case character,");
  if (!has_digit)
    strcat(func0_result, "String must have 1 number,");
  if (length < 8)
    strcat(func0_result, "String length should be atleast 8,");

  // Check if all password constraints are satisfied
  if (has_upper && has_lower && has_digit && length >= 8)
  {
    strcpy(func0_result, "Valid string.");
  }
  else
  {
    // Remove the trailing comma from the accumulated error messages
    int lastIdx = strlen(func0_result) - 1;
    if (func0_result[lastIdx] == ',')
      func0_result[lastIdx] = '\0';
  }

  return func0_result;
}