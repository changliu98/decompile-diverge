char **func0(char *text)
{
 char **result = malloc(sizeof(char *) * (strlen(text) / 2 + 1));
 int count = 0;
 char *copy = strdup(text);
 char *token = strtok(copy, " ");
 while (token != NULL) {
  char *end = token + strlen(token) - 1;
  while (end > token) {
   if (*end == '.' || *end == ',' || *end == '!' || *end == '?' || *end == ';' || *end == ':') {
    *end = '\0';
   } else {
    break;
   }
   end--;
  }
  if (strlen(token) >= 4) {
   result[count++] = strdup(token);
  }
  token = strtok(NULL, " ");
 }
 result[count] = NULL;
 free(copy);
 return result;
}