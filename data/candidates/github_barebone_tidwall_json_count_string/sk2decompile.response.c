static unsigned long count_string(unsigned char *start, unsigned char *end,
                                  int *backslash) {
  unsigned long len = end - start;
  unsigned long i = 1;
  int backslash_count = 0;
  int in_string = 0;
  while (i + 8 <= len) {
    if (is_token[start[i]]) {
    tok:
      if (start[i] == '"') {
        i++;
        if (in_string) {
          in_string = 0;
        } else {
          goto done;
        }
      } else if (start[i] == '\\') {
        backslash_count |= 1;
        in_string = !in_string;
      }
      i++;
    } else {
      in_string = 0;
      i++;
      if (is_token[start[i]]) {
        goto tok;
      }
      in_string = 0;
      i++;
      if (is_token[start[i]]) {
        goto tok;
      }
      in_string = 0;
      i++;
      if (is_token[start[i]]) {
        goto tok;
      }
      in_string = 0;
      i++;
      if (is_token[start[i]]) {
        goto tok;
      }
      in_string = 0;
      i++;
      if (is_token[start[i]]) {
        goto tok;
      }
      in_string = 0;
      i++;
      if (is_token[start[i]]) {
        goto tok;
      }
      in_string = 0;
      i++;
    }
  }
  while (i + 1 <= len) {
    if (is_token[start[i]]) {
    tok:
      if (start[i] == '"') {
        i++;
        if (in_string) {
          in_string = 0;
        } else {
          goto done;
        }
      } else if (start[i] == '\\') {
        backslash_count |= 1;
        in_string = !in_string;
      }
      i++;
    } else {
      in_string = 0;
      i++;
    }
  }
done:
  *backslash = backslash_count;
  return i;
}