void __cdecl reverse(char *s)
{
  int len; 
  int i; 
  char c; 

  // Calculate the length of the string
  for ( len = 0; s[len]; ++len )
    ;

  // Reverse the string in-place by swapping characters from the ends
  for ( i = 0; i < len / 2; ++i )
  {
    c = s[i];
    s[i] = s[len - 1 - i];
    s[len - 1 - i] = c;
  }
}