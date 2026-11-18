char **__cdecl func0(const char *text, int *count)
{
  int i; 
  int word_start; 
  char **result; 
  int n; 

  n = strlen(text);
  
  // Allocate an array of pointers. 
  // Note: Allocating `8 * n` bytes guarantees enough space for the worst-case scenario 
  // where every character is a separate word (e.g., "a b c d").
  result = (char **)malloc(8LL * n);
  
  *count = 0;
  word_start = 0;
  
  // Iterate from 1 to n (inclusive). The `i == n` condition acts as an end-of-string trigger.
  for ( i = 1; i <= n; ++i )
  {
    // Condition triggers if we reach the end of the string, OR
    // if the current character is a space AND the previous character was NOT a space.
    // This effectively detects the end of a word.
    if ( i == n || (IS_SPACE(text[i]) && !IS_SPACE(text[i - 1])) )
    {
      int word_len = i - word_start;
      
      // Allocate memory for the word + 1 byte for the null terminator
      result[*count] = (char *)malloc(word_len + 1);
      
      // Copy the word and manually null-terminate it
      strncpy(result[*count], &text[word_start], word_len);
      result[*count][word_len] = 0;
      
      // Increment the word count and update the start index for the next word
      (*count)++;
      word_start = i;
    }
  }
  
  return result;
}