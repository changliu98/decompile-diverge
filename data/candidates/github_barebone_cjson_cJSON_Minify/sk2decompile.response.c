void cJSON_Minify(char *json) {
  char *read = json;
  char *write = json;
  if (json == NULL) {
    return;
  }
  while (*read) {
    switch (*read) {
      case ' ':
      case '\t':
      case '\r':
      case '\n':
        read++;
        break;
      case '\"':
        minify_string(&read, &write);
        break;
      case '/':
        if (read[1] == '/') {
          skip_oneline_comment(&read);
        } else if (read[1] == '*') {
          skip_multiline_comment(&read);
        } else {
          *write = *read;
          read++;
          write++;
        }
        break;
      default:
        *write = *read;
        read++;
        write++;
        break;
    }
  }
  *write = 0;
}