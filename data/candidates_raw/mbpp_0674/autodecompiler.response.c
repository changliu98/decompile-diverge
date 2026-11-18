char *str_unique(char *string)
{
 char *temp;
 char *token;
 char *result;
 char *unique[100];
 int unique_count;
 int i, j, k;
 int length;
 int total_length;
 int found;

 temp = strdup(string);
 if (!temp) {
  return NULL;
 }

 unique_count = 0;
 token = strtok(temp, " ");
 while (token) {
  found = 0;
  for (j = 0; j < unique_count; j++) {
   if (strcmp(token, unique[j]) == 0) {
    found = 1;
    break;
   }
  }
  if (!found) {
   unique[unique_count++] = token;
  }
  token = strtok(NULL, " ");
 }

 total_length = 0;
 for (i = 0; i < unique_count; i++) {
  total_length += strlen(unique[i]) + 1;
 }

 result = malloc(total_length);
 if (!result) {
  free(temp);
  return NULL;
 }

 result[0] = '\0';
 for (i = 0; i < unique_count; i++) {
  strcat(result, unique[i]);
  if (i < unique_count - 1) {
   strcat(result, " ");
  }
 }

 free(temp);

 return result;
}