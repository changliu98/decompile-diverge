char **__cdecl func0(const char *text, int *count)
{
  char **result_array; // Replaces len[4..7] (stored as QWORD at rbp-18h)
  int text_len;        // Replaces len[0..3] (stored as DWORD at rbp-1Ch)
  int start;
  int i;
  char *substr;

  text_len = strlen(text);
  result_array = NULL;
  *count = 0;

  for (i = 0; i < text_len; )
  {
    // Check if the current character is alphanumeric (matches ctype flag 0x200)
    if ( ((*__ctype_b_loc())[(unsigned char)text[i]] & 0x200) != 0 )
    {
      start = i++;
      
      // Consume all consecutive alphanumeric characters
      while ( i < text_len && ((*__ctype_b_loc())[(unsigned char)text[i]] & 0x200) != 0 )
      {
        ++i;
      }

      // Allocate and extract the matched word
      substr = (char *)malloc(i - start + 1);
      strncpy(substr, &text[start], i - start);
      substr[i - start] = '\0';

      // Expand the array of pointers and store the new word
      result_array = (char **)realloc(result_array, 8LL * (*count + 1));
      result_array[(*count)++] = substr;
    }
    else
    {
      // Skip non-alphanumeric characters
      ++i;
    }
  }

  return result_array;
}