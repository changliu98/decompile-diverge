char **_parse_parentheses(const char *str, int *num_parentheses) {
  int len = strlen(str);
  int count = 0;
  int max_parentheses = 10;
  char **parentheses = malloc(max_parentheses * sizeof(char *));
  char *parenthesis = malloc(len + 1);
  int parenthesis_index = 0;
  *num_parentheses = 0;
  for (int i = 0; i < len; i++) {
    char c = str[i];
    if (c == '(') {
      count++;
      parenthesis[parenthesis_index++] = c;
    } else if (c == ')') {
      count--;
      parenthesis[parenthesis_index++] = c;
      if (count == 0) {
        parenthesis[parenthesis_index] = '\0';
        parentheses[*num_parentheses] = strdup(parenthesis);
        (*num_parentheses)++;
        if (*num_parentheses >= max_parentheses) {
          max_parentheses *= 2;
          parentheses =
              realloc(parentheses, max_parentheses * sizeof(char *));
        }
        parenthesis_index = 0;
      }
    }
  }
  free(parenthesis);
  return parentheses;
}