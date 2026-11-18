int *_parse_string(char *string, int *count) {
  int *result = NULL;
  int result_count = 0;
  int result_size = 0;
  char current_char[3];
  memset(current_char, 0, 3);
  int string_length = strlen(string) + 1;
  char *string_copy = malloc(string_length + 1);
  strcpy(string_copy, string);
  strcat(string_copy, " ");
  for (int i = 0; i < string_length; i++) {
    if (string_copy[i] == ' ') {
      if (!strcmp(current_char, "o")) {
        if (result_count == result_size) {
          result_size = result_size > 0 ? result_size * 2 : 4;
          result = realloc(result, result_size * sizeof(int));
        }
        result[result_count++] = 4;
      }
      if (!strcmp(current_char, "o|")) {
        if (result_count == result_size) {
          result_size = result_size > 0 ? result_size * 2 : 4;
          result = realloc(result, result_size * sizeof(int));
        }
        result[result_count++] = 2;
      }
      if (!strcmp(current_char, ".|")) {
        if (result_count == result_size) {
          result_size = result_size > 0 ? result_size * 2 : 4;
          result = realloc(result, result_size * sizeof(int));
        }
        result[result_count++] = 1;
      }
      strcpy(current_char, "");
    } else {
      size_t current_char_length = strlen(current_char);
      if (current_char_length < 2) {
        current_char[current_char_length] = string_copy[i];
        current_char[current_char_length + 1] = '\0';
      }
    }
  }
  free(string_copy);
  *count = result_count;
  return result;
}