// Checks if all characters in the string are identical to the first character.
// Returns true if the string is empty or consists of the same repeating character, false otherwise.
bool __cdecl is_uniform_string(const char *str)
{
  size_t length = strlen(str);
  
  for (size_t i = 1; i < length; ++i)
  {
    if (str[i] != str[0])
      return false;
  }
  
  return true;
}