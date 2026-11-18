bool __cdecl func0(const char *str)
{
  int j;
  int i;
  size_t len = strlen(str);

  // Iterate through each character in the string
  for ( i = 0; i < len; ++i )
  {
    // Compare the current character with all subsequent characters
    for ( j = i + 1; j < len; ++j )
    {
      // If a duplicate is found, the string does not have all unique characters
      if ( str[i] == str[j] )
        return 0;
    }
  }
  // No duplicates found
  return 1;
}