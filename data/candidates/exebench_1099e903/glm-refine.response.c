void __cdecl count_segments(const char *s, char delimiter, int *count)
{
  int end = 0;
  int start = 0;

  while (s[start])
  {
    if (start == end && s[start] == delimiter)
    {
      // Both pointers are at the same delimiter. 
      // Skip over it to start evaluating a new segment.
      ++start;
      ++end;
    }
    else if (s[end] != delimiter && s[end] != '\0')
    {
      // The character at 'end' is part of the current segment.
      // Expand the segment by moving the 'end' pointer forward.
      ++end;
    }
    else
    {
      // We hit a delimiter or the end of the string.
      // A segment has been successfully traversed.
      ++(*count);
      
      // Move 'start' to where 'end' is to begin the next segment.
      start = end;
    }
  }
}