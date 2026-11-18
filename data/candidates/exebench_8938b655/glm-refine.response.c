int __cdecl itos(int i, char *s)
{
  int left;
  char temp;
  int right;
  int is_negative;
  int digit;
  int num;

  num = i;
  if ( i >= 0 )
  {
    right = -1;
    left = 0;
  }
  else
  {
    right = 0;
    num = -i;
    left = 1;
    *s = '-';
  }
  
  // Extract digits and write them in reverse order
  do
  {
    digit = num % 10;
    num /= 10;
    s[++right] = digit + '0';
  }
  while ( num );
  
  s[right + 1] = '\0';
  
  // Reverse the extracted digits in-place
  while ( left < right )
  {
    temp = s[left];
    s[left] = s[right];
    s[right] = temp;
    ++left;
    --right;
  }
  
  return right + 1; // Note: returns the length of the string
}