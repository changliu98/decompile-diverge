Global buffer to hold the reversed string

char *__cdecl func0(char *s)
{
  char *words[10];
  int word_count = 0;
  char *token;

  // Split the string `s` by spaces and store up to 10 pointers
  for (token = strtok(s, " "); token != NULL; token = strtok(NULL, " "))
  {
    if (word_count < 10) // Implicit bound in original assembly
      words[word_count++] = token;
  }

  func0_result[0] = '\0'; // Reset the global result buffer

  // Iterate backwards through the collected words to reverse their order
  for (int i = word_count - 1; i >= 0; i--)
  {
    strcat(func0_result, words[i]);
    if (i > 0)
      strcat(func0_result, " ");
  }

  return func0_result;
}