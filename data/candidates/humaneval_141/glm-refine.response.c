const char *func0(const char *file_name)
{
  int num_digit = 0;
  int num_dot = 0;
  int length = strlen(file_name);

  // 1. Check minimum length
  if (length < 5)
    return "No";

  // 2. Check if the first character is an alphabetic letter
  char first_char = file_name[0];
  if (!isalpha(first_char))
    return "No";

  // 3. Check if the file extension is valid
  const char *extension = &file_name[length - 4];
  if (strcmp(extension, ".txt") != 0 && 
      strcmp(extension, ".exe") != 0 && 
      strcmp(extension, ".dll") != 0)
    return "No";

  // 4. Count the number of digits and dots in the filename
  for (int i = 0; i < length; ++i)
  {
    if (isdigit(file_name[i]))
      ++num_digit;
    if (file_name[i] == '.')
      ++num_dot;
  }

  // 5. Final validation: at most 3 digits and exactly 1 dot
  if (num_digit <= 3 && num_dot == 1)
    return "Yes";
  else
    return "No";
}