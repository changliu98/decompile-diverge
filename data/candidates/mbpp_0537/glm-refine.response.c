char *__cdecl func0(char *str)
{
  char *words[100];
  int word_count = 0;
  char *word;

  // Tokenize the string by spaces
  for (word = strtok(str, " "); word; word = strtok(NULL, " "))
  {
    // Check if the current word has already been seen
    for (int i = 0; i < word_count; ++i)
    {
      if (strcmp(words[i], word) == 0)
        return word;
    }
    
    // Store the new unique word
    words[word_count++] = word;
  }
  
  return "None";
}