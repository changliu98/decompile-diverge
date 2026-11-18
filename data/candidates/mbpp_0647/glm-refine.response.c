char **__cdecl func0(const char *text, int *count)
{
  int word_length; 
  int i; 
  int start; 
  int current_word; 
  char **result; 
  int len; 

  len = strlen(text);
  
  // Allocate an array of pointers. 
  // Note: Allocating based on 'len' guarantees enough space for the worst-case 
  // scenario (e.g., "a b c d"), even though it may overallocate for normal text.
  result = (char **)malloc(8LL * len);
  if ( !result )
  {
    perror("Failed to allocate memory");
    exit(1);
  }
  
  current_word = 0;
  start = 0;
  
  // Loop from 1 up to and including len (to handle the implicit null terminator)
  for ( i = 1; i <= len; ++i )
  {
    // Check if the current character is a space or the null terminator
    // 0x100 in glibc's __ctype_b_loc corresponds to the 'space' (_ISspace) flag
    if ( ((*__ctype_b_loc())[text[i]] & 0x100) != 0 || !text[i] )
    {
      word_length = i - start;
      
      // Allocate memory for the current word + null terminator
      result[current_word] = (char *)malloc(word_length + 1);
      if ( !result[current_word] )
      {
        perror("Failed to allocate memory");
        exit(1);
      }
      
      // Copy the word and null-terminate it
      memcpy(result[current_word], &text[start], word_length);
      result[current_word][word_length] = 0;
      
      // Move start to the current index (the space/terminator itself)
      start = i;
      ++current_word;
    }
  }
  
  *count = current_word;
  return result;
}