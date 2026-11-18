void func0(char* input, char* filter, char* output, char* is_palindrome_str) {
  int length = strlen(input);
  char* temp = malloc((length + 1) * sizeof(char));
  int j = 0;
  for (int i = 0;; ++i) {
    if (input[i] == '\0') {
      break;
    }
    char* p = filter;
    char should_filter = 0;
    while (1) {
      if (*p == '\0') {
        break;
      }
      if (input[i] == *p) {
        should_filter = 1;
        break;
      }
      ++p;
    }
    if (!should_filter) {
      temp[j++] = input[i];
    }
  }
  temp[j] = '\0';
  int output_length = strlen(temp);
  char is_palindrome = 1;
  for (int i = 0;; ++i) {
    if (i >= output_length / 2) {
      break;
    }
    if (temp[i] != temp[output_length - 1 - i]) {
      is_palindrome = 0;
      break;
    }
  }
  strcpy(output, temp);
  strcpy(is_palindrome_str, is_palindrome ? "True" : "False");
  free(temp);
}