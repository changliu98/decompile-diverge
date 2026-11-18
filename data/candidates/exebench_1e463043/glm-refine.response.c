int __cdecl c_insensitive(char *str1, char *str2)
{
  bool both_not_null;
  int i;

  // Convert str1 to uppercase
  for ( i = 0; str1[i]; ++i )
  {
    if ( str1[i] > 'a' - 1 && str1[i] < 'z' + 1 ) // equivalent to: >= 'a' && <= 'z'
      str1[i] -= 32; // 'a' - 'A' = 32
  }

  // Convert str2 to uppercase
  for ( i = 0; str2[i]; ++i )
  {
    if ( str2[i] > 'a' - 1 && str2[i] < 'z' + 1 )
      str2[i] -= 32;
  }

  // Compare the two uppercase strings
  for ( i = 0; ; ++i )
  {
    both_not_null = false;
    if ( str1[i] )
      both_not_null = (str2[i] != 0);
      
    if ( !both_not_null )
      break;

    if ( str1[i] > str2[i] )
      return 1;   // str1 is greater than str2

    if ( str1[i] < str2[i] )
      return -1;  // str1 is less than str2
  }
  
  // If we exit the loop, at least one string has reached the null terminator.
  // If both are null, they are equal (returns 0).
  // Note: If they are of different lengths, the original code returns 0 instead 
  // of 1 or -1. This is a common bug in custom comparison functions.
  return 0;
}