char **func0(char *text, int *count)
{
 int i;
 int start;
 int word_length;
 int len;
 char **words;
 int current_word;

 len = strlen(text);

 words = (char **)malloc((size_t)len * sizeof(char *));
 if (words == NULL) {
  perror("Failed to allocate memory");
  exit(1);
 }

 current_word = 0;
 start = 0;
 for (i = 1; i <= len; i++) {
  if ((isspace(text[i]) || text[i] == '\0')) {
   word_length = i - start;
   words[current_word] = (char *)malloc(word_length + 1);
   if (words[current_word] == NULL) {
    perror("Failed to allocate memory");
    exit(1);
   }
   memcpy(words[current_word], text + start,
          (size_t)word_length);
   words[current_word][word_length] = '\0';
   start = i;
   current_word++;
  }
 }
 *count = current_word;
 return words;
}