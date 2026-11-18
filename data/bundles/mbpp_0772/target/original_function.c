char* func0(const char* test_str, int K) {
  char temp_copy[1000];
  strncpy(temp_copy, test_str, sizeof(temp_copy));
  temp_copy[sizeof(temp_copy) - 1] = '\0';
  char* res = malloc(strlen(test_str) + 1);
  if (!res) {
    perror("malloc failed");
    exit(EXIT_FAILURE);
  }
  res[0] = '\0';
  char* token = strtok(temp_copy, " ");
  while (token != NULL) {
    if ((int)strlen(token) != K) {
      strcat(res, token);
      strcat(res, " ");
    }
    token = strtok(NULL, " ");
  }
  size_t len = strlen(res);
  if (len > 0 && res[len - 1] == ' ') {
    res[len - 1] = '\0';
  }
  return res;
}