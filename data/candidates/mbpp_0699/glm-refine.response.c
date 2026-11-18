int __cdecl func0(const char *str1, const char *str2)
{
  int i;
  int length;
  int mismatch_count;

  mismatch_count = 0;
  length = strlen(str1);
  
  // Count the number of mismatched characters between the two strings
  for ( i = 0; i < length; ++i )
  {
    if ( str1[i] != str2[i] )
      ++mismatch_count;
  }
  
  // If the number of mismatched characters is odd, return -1
  // Otherwise, return half the number of mismatched characters
  if ( mismatch_count % 2 )
    return -1;
  else
    return mismatch_count / 2;
}