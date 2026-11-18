int __cdecl func0(const char *str1)
{
  int i; 
  int length; 
  int match_count; 

  match_count = 0;
  length = strlen(str1);
  
  for ( i = 0; i < length; ++i )
  {
    // Check if the current character matches the index `i` when converted to a 0-based alphabet index.
    // 'A' is 65 in ASCII, so `str1[i] - 65` gives 0 for 'A', 1 for 'B', etc.
    // 'a' is 97 in ASCII, so `str1[i] - 97` gives 0 for 'a', 1 for 'b', etc.
    if ( i == str1[i] - 65 || i == str1[i] - 97 )
      ++match_count;
  }
  
  return match_count;
}