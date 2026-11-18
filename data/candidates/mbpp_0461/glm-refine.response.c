int __cdecl func0(const char *str)
{
  // If the string is empty, return an uninitialized value (undefined behavior in original code)
  if ( !*str ) {
    int uninitialized_var; 
    return uninitialized_var;
  }

  // Check if the first character is an uppercase letter ('A' to 'Z')
  if ( *str >= 'A' )
    return *str <= 'Z';

  return 0;
}