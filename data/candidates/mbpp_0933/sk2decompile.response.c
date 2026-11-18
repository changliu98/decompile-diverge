char *_camel_to_snake(const char *camel) {
  size_t len = strlen(camel);
  char *snake = malloc(len * 2);
  int j = 0;
  int i;
  for (i = 0; i < len; i++) {
    if (i > 0 && isupper(camel[i]) &&
            (islower(camel[i - 1]) || isdigit(camel[i - 1])) ||
        i > 0 && isupper(camel[i]) && isupper(camel[i - 1]) &&
            islower(camel[i + 1])) {
      snake[j++] = '_';
      snake[j++] = tolower(camel[i]);
    } else {
      snake[j++] = tolower(camel[i]);
    }
  }
  snake[j] = '\0';
  return snake;
}