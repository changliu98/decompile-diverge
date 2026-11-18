void __cdecl uppercase(int *chptr)
{
  int ch = *chptr;
  
  // Check if the character is a lowercase ASCII letter ('a' to 'z')
  if (ch >= 'a' && ch <= 'z')
  {
    // Convert to uppercase
    *chptr = ch - ('a' - 'A'); 
  }
}