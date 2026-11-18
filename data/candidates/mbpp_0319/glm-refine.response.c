letter words from the given text
char **__cdecl func0(const char *text, int *count)
{
  char pattern[16];
  regex_t regex;
  regmatch_t matches[1];
  char *p;
  int start, end;
  int word_count = 0;
  size_t text_len;

  strcpy(pattern, "\\b[a-zA-Z]{5}\\b");
  
  text_len = strlen(text);
  
  // Allocate a Variable Length Array (VLA) on the stack to copy the string.
  // The original assembly manually aligned the stack pointer (sub rbp, (len + 16) & ~0xF).
  char text_copy[text_len + 1];
  strcpy(text_copy, text);

  // REG_EXTENDED is typically 1 in <regex.h>
  regcomp(&regex, pattern, REG_EXTENDED);

  // Iterate through the copied text, finding all matches
  for (p = text_copy; !regexec(&regex, p, 1, matches, 0); p += end)
  {
    start = matches[0].rm_so;
    end = matches[0].rm_eo;

    // Allocate memory for the matched word (+1 for the null terminator)
    char *word = (char *)malloc(end - start + 1);
    strncpy(word, &p[start], end - start);
    word[end - start] = '\0';

    // Store the word pointer in the global array and increment the count
    func0_words[word_count++] = word;
  }

  regfree(&regex);
  *count = word_count;

  return func0_words;
}