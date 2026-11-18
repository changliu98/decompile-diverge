void __cdecl remove_line_ending(char *text, char ending)
{
  char *last_occurrence;

  // Find the last occurrence of 'ending' in the string 'text'
  last_occurrence = strrchr(text, ending);
  
  // If found, truncate the string at that position
  if ( last_occurrence )
    *last_occurrence = '\0';
}