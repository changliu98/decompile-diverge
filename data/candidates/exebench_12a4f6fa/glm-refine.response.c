void __cdecl putoct(char *str, unsigned __int16 val)
{
  char *cp;
  unsigned __int16 vala = val;

  // Setup the right-aligned 8-character buffer
  str[6] = ' ';
  str[7] = '\0';
  
  // Extract the lowest 3 bits (first octal digit)
  cp = str + 5;
  *cp = (val & 7) + '0';

  // Fill the remaining 5 characters from right to left
  while (cp != str)
  {
    vala >>= 3;
    
    // If there are still bits left to process, convert to ASCII digit, 
    // otherwise pad with spaces for right-alignment.
    *--cp = vala ? (vala & 7) + '0' : ' ';
  }
}