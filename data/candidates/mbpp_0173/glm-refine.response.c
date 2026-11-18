char *__cdecl func0(char *text)
{
  size_t text_len;
  char *filtered_buf;
  int j;
  int i;

  i = 0;
  j = 0;
  text_len = strlen(text);
  
  // Allocate a Variable Length Array (VLA) to temporarily hold the filtered string.
  // The original expression `&v6 - ((text_len + 16) & 0xFFFFFFFFFFFFFFF0LL)` is a 
  // standard compiler idiom for allocating a VLA on the stack aligned to 16 bytes.
  filtered_buf = (char *)alloca(text_len + 1);

  // Iterate through the original string and copy only printable characters.
  // The check `((*__ctype_b_loc())[text[i]] & 8) != 0` corresponds to the `isprint()` macro.
  while (text[i])
  {
    if (isprint(text[i]))
    {
      filtered_buf[j++] = text[i];
    }
    ++i;
  }
  
  // Null-terminate the filtered string.
  filtered_buf[j] = 0;
  
  // Copy the filtered string back over the original buffer.
  strcpy(text, filtered_buf);
  
  return text;
}