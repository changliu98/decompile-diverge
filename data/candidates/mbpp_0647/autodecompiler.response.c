char **func0(char *str, int *num_words) {
 int len = strlen(str);
 char **words = malloc(sizeof(char*) * len);
 if (words == NULL) {
  perror("Failed to allocate memory");
  exit(1);
 }
 int word_count = 0;
 int start = 0;
 int end = 1;
 while (end <= len) {
  if ((iswspace(str[end]) || str[end] == '\0')) {
   int length = end - start;
   words[word_count] = malloc(sizeof(char) * (length + 1));
   if (words[word_count] == NULL) {
    perror("Failed to allocate memory");
    exit(1);
   }
   memcpy(words[word_count], &str[start], length);
   words[word_count][length] = '\0';
   start = end;
   word_count++;
  }
  end++;
 }
 *num_words = word_count;
 return words;
}