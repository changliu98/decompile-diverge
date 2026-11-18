void __cdecl reverse(char *s)
{
  char *p = s;
  char *q = s;

  // Find the end of the string (null terminator)
  while (*q)
    ++q;
  
  // Set q to the last character of the string
  --q;

  // Swap characters from the outside in
  while (p < q)
  {
    char temp = *p;
    *p = *q;
    *q = temp;
    
    ++p;
    --q;
  }
}