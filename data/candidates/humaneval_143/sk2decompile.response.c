void _split_prime_words(char *str, char *result) {
  int word_len = 0;
  int result_len = 0;
  int i;
  int j;
  int is_prime;
  for (i = 0; str[i] != '\0'; i++) {
    if (str[i] == ' ') {
      is_prime = 1;
      for (j = 2; j * j <= word_len; j++) {
        if (word_len % j == 0) {
          is_prime = 0;
          break;
        }
      }
      if (is_prime) {
        if (result_len > 0) {
          result[result_len++] = ' ';
        }
        memcpy(result + result_len, str + i - word_len, word_len);
        result_len += word_len;
      }
      word_len = 0;
    } else {
      word_len++;
    }
  }
  is_prime = 1;
  for (j = 2; j * j <= word_len; j++) {
    if (word_len % j == 0) {
      is_prime = 0;
      break;
    }
  }
  if (is_prime) {
    if (result_len > 0) {
      result[result_len++] = ' ';
    }
    memcpy(result + result_len, str + i - word_len, word_len);
    result_len += word_len;
  }
  result[result_len] = '\0';
}