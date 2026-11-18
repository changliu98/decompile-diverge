int __cdecl func0(const char *str1, const char *str2)
{
  int diff_count; // [rsp+Ch] [rbp-24h] - Counter for mismatched characters
  int len;        // [rsp+10h] [rbp-20h] - Length of str1
  int i;          // [rsp+14h] [rbp-1Ch] - Loop index

  diff_count = 0;
  len = strlen(str1);
  
  // Count the number of positions where the characters differ
  for ( i = 0; i < len; ++i )
  {
    if ( str1[i] != str2[i] )
      ++diff_count;
  }
  
  // If the number of differences is odd, they cannot be resolved by swaps
  if ( diff_count & 1 ) 
    return -1;
  
  // Each swap fixes two differences, so the number of swaps is diff_count / 2
  return diff_count / 2;
}