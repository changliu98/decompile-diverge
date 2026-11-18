char **split(char *str) {
 char **words = malloc((strlen(str)/2 + 1) * sizeof(char *));
 int i = 0;
 char *cpy = strdup(str);
 char *word = strtok(cpy, " ");
 while(1) {
  if(word == NULL)
   break;
  char *end = word + strlen(word) - 1;
  while(end > word && ({ char __ok__ = (*end == '.' || *end == ',' || *end == '!' || *end == '?' || *end == ';' || *end == ':'); __ok__; }))
   *end-- = '\0';
  if(strlen(word) >= 5)
   words[i++] = strdup(word);
  word = strtok(NULL, " ");
 }
 words[i] = NULL;
 free(cpy);
 return words;
}