void __cdecl tagcpy(char *dest, char *src, int tag_size)
{
  char *s1;
  char *s2;
  bool is_valid;

  s1 = src;
  s2 = &src[tag_size - 1];
  
  // Adjust the end boundary if the last character is non-null 
  // but the second to last is null (handles potentially malformed/unfilled buffers)
  if (*s2 && !src[tag_size - 2])
    s2 = &src[tag_size - 2];

  // Trim leading and trailing spaces
  while (s1 <= s2)
  {
    if (*s1 == ' ')
    {
      ++s1;
    }
    else
    {
      if (*s2 && *s2 != ' ')
        goto LABEL_10;
      --s2;
    }
  }

  // Copy the trimmed string
  while (true)
  {
LABEL_10:
    is_valid = false;
    if (*s1)
      is_valid = (s1 <= s2);
      
    if (!is_valid)
      break;

    *dest++ = *s1++;
  }

  *dest = '\0';
}