char **split_command(char *command)
{
 char **result;
 int spots = 1;
 char *tmp;
 char *cp;
 char *token;
 int i;

 cp = command;
 while (1) {
  if (*cp == '\0')
   break;
  switch (*cp) {
  case ' ':
   spots++;
   break;
  }
  cp++;
 }

 result = malloc((spots + 1) * sizeof(char *));
 if (result == NULL) {
  return NULL;
 }

 tmp = strdup(command);
 if (tmp == NULL) {
  free(result);
  return NULL;
 }

 i = 0;
 token = strtok(tmp, " ");
 while (token != NULL) {
  result[i++] = strdup(token);
  token = strtok(NULL, " ");
 }
 result[i] = NULL;

 free(tmp);

 return result;
}