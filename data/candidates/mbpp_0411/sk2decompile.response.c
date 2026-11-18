char *_c_str_camel_to_snake(const char *camel, char *snake) {
  int i, j, new_word;
  j = 0;
  new_word = 1;
  for (i = 0; camel[i] != '\0'; i++) {
    if (camel[i] == '_') {
      new_word = 1;
    } else if (new_word) {
      snake[j++] = toupper(camel[i]);
      new_word = 0;
    } else {
      snake[j++] = camel[i];
    }
  }
  snake[j] = '\0';
  return snake;
}