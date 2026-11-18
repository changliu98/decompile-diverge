char* func0(const char* string) {
  char* str = strdup(string);
  if (!str) return NULL;
  char* unique[100];
  int unique_count = 0;
  char* token = strtok(str, " ");
  while (token != NULL) {
    int found = 0;
    for (int i = 0; i < unique_count; i++) {
      if (strcmp(token, unique[i]) == 0) {
        found = 1;
        break;
      }
    }
    if (!found) {
      unique[unique_count++] = token;
    }
    token = strtok(NULL, " ");
  }
  int total_length = 0;
  for (int i = 0; i < unique_count; i++) {
    total_length += strlen(unique[i]) + 1;
  }
  char* result = malloc(total_length);
  if (!result) {
    free(str);
    return NULL;
  }
  result[0] = '\0';
  for (int i = 0; i < unique_count; i++) {
    strcat(result, unique[i]);
    if (i < unique_count - 1) {
      strcat(result, " ");
    }
  }
  free(str);
  return result;
}